// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2026 Antti Nuortimo.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "read_fbx_mesh.hpp"
#include "fbx_mesh.hpp"
#include "fbx_mesh_vertex.hpp"
#include "fbx_skin_vertex.hpp"
#include <ufbx.h>

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <algorithm> // std::max, std::min
#include <cstdint>   // std::int32_t, std::uint32_t
#include <iostream>  // std::cerr, std::cout
#include <limits>    // std::numeric_limits
#include <optional>  // std::nullopt, std::optional
#include <vector>    // std::vector

namespace yli::load
{
    std::optional<FbxMesh> read_fbx_mesh(ufbx_mesh& mesh)
    {
        // Count the maximum number of parts and maximum number of triangles.
        std::size_t max_parts { 0 };
        std::size_t max_triangles { 0 };

        for (std::size_t part_i = 0; part_i < mesh.material_parts.count; part_i++)
        {
            if (const ufbx_mesh_part* const part = &mesh.material_parts.data[part_i]; part->num_triangles > 0)
            {
                max_parts++;
                max_triangles = std::max(max_triangles, part->num_triangles);
            }
        }

        // Temporary buffers.
        const std::size_t num_triangle_indices = 3 * mesh.max_face_triangles;

        std::vector<std::uint32_t> triangle_indices;
        triangle_indices.resize(num_triangle_indices);

        std::vector<FbxMeshVertex> vertices;
        vertices.resize(3 * max_triangles);

        std::vector<FbxSkinVertex> skin_vertices;
        skin_vertices.resize(3 * max_triangles);

        std::vector<FbxSkinVertex> mesh_skin_vertices;
        mesh_skin_vertices.resize(mesh.num_vertices);
        std::cout << "mesh.num_vertices: " << mesh.num_vertices << "\n";

        std::vector<std::uint32_t> indices;
        indices.reserve(3 * max_triangles);

        // Result buffers.
        std::vector<FbxMeshPart> parts;
        parts.resize(max_parts);
        std::cout << "max_parts: " << max_parts << "\n";

        std::size_t num_parts { 0 };

        // In FBX files a single mesh can be instanced by multiple nodes.
        // According to `viewer.c`, ufbx handles these connections in 2 ways:
        // 1. `ufbx_node.mesh/light/camera/etc` contains pointer to the data "attribute".
        // 2. each element that can be connected to a node contains a list of
        //    `ufbx_node*` instances eg. `ufbx_mesh.instances`.

        FbxMesh fbx_mesh;
        fbx_mesh.instance_node_indices.reserve(mesh.instances.count);
        std::cout << "mesh.instances.count: " << mesh.instances.count << "\n";

        for (std::size_t i = 0; i < mesh.instances.count; i++)
        {
            fbx_mesh.instance_node_indices.emplace_back(mesh.instances.data[i]->typed_id);
        }

        // Create the vertex buffers.
        std::size_t num_blend_shapes { 0 };
        std::vector<ufbx_blend_channel*> blend_channels;
        constexpr std::size_t max_blend_shapes { 64 };
        blend_channels.reserve(max_blend_shapes);

        ufbx_skin_deformer* skin { nullptr };
        std::cout << "mesh.skin_deformers.count: " << mesh.skin_deformers.count << "\n";

        if (mesh.skin_deformers.count > 0)
        {
            std::size_t num_bones { 0 };
            fbx_mesh.skinned = true;

            // Pick the first skin deformer.
            // TODO: deal with multiple attached skin deformers in some useful way!
            skin = mesh.skin_deformers.data[0];

            // Take `max_bones` bones.
            constexpr std::size_t max_bones { 64 };

            for (std::size_t cluster_i = 0; cluster_i < skin->clusters.count; cluster_i++)
            {
                ufbx_skin_cluster* cluster = skin->clusters.data[cluster_i];

                if (num_bones < max_bones)
                {
                    fbx_mesh.bone_indices.emplace_back(static_cast<int32_t>(cluster->bone_node->typed_id));
                    fbx_mesh.bone_matrices.emplace_back(static_cast<int32_t>(cluster->bone_node->typed_id));
                    num_bones++;
                }
            }
            fbx_mesh.num_bones = num_bones;

            std::cout << "fbx_mesh.num_bones: " << fbx_mesh.num_bones << "\n";
            std::cout << "fbx_mesh.bone_indices.size(): " << fbx_mesh.bone_indices.size() << "\n";
            std::cout << "fbx_mesh.bone_matrices.size(): " << fbx_mesh.bone_matrices.size() << "\n";

            // Pre-calculate the skinned vertex bones/weights for each vertex as they will probably
            // be shared by multiple indices.
            for (std::size_t vertex_i = 0; vertex_i < mesh.num_vertices; vertex_i++)
            {
                std::size_t num_weights { 0 };
                float total_weight { 0.0f };
                std::vector<float> weights;
                std::vector<std::uint32_t> clusters;

                // `ufbx_skin_vertex` contains the offset and number of weights that deform the vertex
                // in a descending weight order so we can pick the first N weights and get
                // a reasonable approximation of the skinning.
                ufbx_skin_vertex vertex_weights = skin->vertices.data[vertex_i];

                for (std::size_t weight_i = 0; weight_i < vertex_weights.num_weights; weight_i++)
                {
                    // TODO: limit processing to n weights here as in `viewer.c`, if needed.

                    if (const auto [cluster_index, ufbx_weight] =
                                skin->weights.data[vertex_weights.weight_begin + weight_i];
                        cluster_index < max_bones)
                    {
                        const auto weight = static_cast<float>(ufbx_weight);
                        total_weight += weight;
                        clusters.emplace_back(cluster_index);
                        weights.emplace_back(weight);
                        num_weights++;
                    }
                }

                // Weights.
                if (total_weight > 0.0f)
                {
                    FbxSkinVertex* my_skin_vertex = &mesh_skin_vertices.at(vertex_i);
                    float normalized_sum { 0.0f };

                    for (std::size_t weight_i = 0; weight_i < num_weights; weight_i++)
                    {
                        const float normalized_weight = weights.at(weight_i) / total_weight;
                        normalized_sum += normalized_weight;
                        my_skin_vertex->bone_indices.emplace_back(clusters.at(weight_i));
                        my_skin_vertex->bone_weights.emplace_back(normalized_weight);
                    }

                    my_skin_vertex->bone_weights.at(0) += 1.0f - normalized_sum;
                }
            }
        }

        std::cout << "mesh.blend_deformers.count: " << mesh.blend_deformers.count << "\n";

        // Fetch blend channels from all attached blend deformers.
        for (std::size_t deformer_i = 0; deformer_i < mesh.blend_deformers.count; deformer_i++)
        {
            ufbx_blend_deformer* deformer = mesh.blend_deformers.data[deformer_i];

            for (std::size_t channel_i = 0; channel_i < deformer->channels.count; channel_i++)
            {
                if (ufbx_blend_channel* channel = deformer->channels.data[channel_i]; channel->keyframes.count > 0)
                {
                    // TODO: add check for max blend shapes here as in `viewer.c`, if needed!
                    blend_channels.emplace_back(channel);
                    fbx_mesh.blend_channel_indices.emplace_back(static_cast<int32_t>(channel->typed_id));
                    num_blend_shapes++;
                }
            }
        }

        if (num_blend_shapes > 0)
        {
            // TODO: compute blend shape image as needed! See `pack_blend_channels_to_image` function of `viewer.c.`!
        }

        std::cout << "mesh.material_parts.count: " << mesh.material_parts.count << "\n";

        // Split the mesh into parts by material. See `ufbx_mesh_part` data structure.
        for (std::size_t part_i = 0; part_i < mesh.material_parts.count; part_i++)
        {
            ufbx_mesh_part* mesh_part = &mesh.material_parts.data[part_i];
            std::cout << "mesh_part->num_triangles: " << mesh_part->num_triangles << "\n";
            std::cout << "mesh_part->num_faces: " << mesh_part->num_faces << "\n";

            if (mesh_part->num_triangles == 0)
            {
                continue;
            }

            FbxMeshPart& part = parts.at(num_parts++);
            std::size_t num_indices { 0 };

            // Fetch all vertices into a flat non-indexed buffer.
            for (std::size_t face_i = 0; face_i < mesh_part->num_faces; face_i++)
            {
                ufbx_face face = mesh.faces.data[mesh_part->face_indices.data[face_i]];
                std::size_t num_triangles = ufbx_triangulate_face(triangle_indices.data(), num_triangle_indices, &mesh,
                                                                  face);

                // Iterate through every vertex of every triangle in the triangulated result.
                for (std::size_t vertex_i = 0; vertex_i < 3 * num_triangles; vertex_i++)
                {
                    ufbx_vec2 default_uv { .x = 0.0f, .y = 0.0f };
                    std::uint32_t triangle_index = triangle_indices.at(vertex_i);
                    FbxMeshVertex& vertex = vertices.at(num_indices);

                    ufbx_vec3 position = ufbx_get_vertex_vec3(&mesh.vertex_position, triangle_index);
                    ufbx_vec3 normal = ufbx_get_vertex_vec3(&mesh.vertex_normal, triangle_index);
                    ufbx_vec2 uv = mesh.vertex_uv.exists
                                       ? ufbx_get_vertex_vec2(&mesh.vertex_uv, triangle_index)
                                       : default_uv;

                    vertex.position = { position.x, position.y, position.z };
                    vertex.normal = glm::normalize(glm::vec3 { normal.x, normal.y, normal.z });
                    vertex.uv = { uv.x, uv.y };
                    vertex.f_vertex_index = static_cast<float>(mesh.vertex_indices.data[triangle_index]);

                    if (skin != nullptr)
                    {
                        skin_vertices.at(num_indices) = mesh_skin_vertices[mesh.vertex_indices.data[triangle_index]];
                    }

                    num_indices++;
                }
            }

            // Vertex streams.
            ufbx_vertex_stream streams[2];
            std::size_t num_streams { 1 };

            streams[0].data = vertices.data();
            streams[0].vertex_count = num_indices;
            streams[0].vertex_size = sizeof(FbxMeshVertex);

            if (skin != nullptr)
            {
                streams[1].data = skin_vertices.data();
                streams[1].vertex_count = num_indices;
                streams[1].vertex_size = sizeof(FbxSkinVertex);
                num_streams = 2;
            }

            // Optimize the flat vertex buffer into an indexed one.
            ufbx_error error;

            // Generate the indices.
            std::size_t num_vertices =
                    ufbx_generate_indices(streams, num_streams, indices.data(), num_indices, nullptr, &error);
            std::cout << "num_vertices: " << num_vertices << "\n";

            if (error.type != UFBX_ERROR_NONE)
            {
                std::cerr << "ERROR: `yli::load::read_fbx_mesh`: failed to generate index buffer!\n";
                return std::nullopt;
            }

            part.num_indices = num_indices;
            std::cout << "part.num_indices: " << part.num_indices << "\n";

            if (mesh_part->index < mesh.materials.count)
            {
                ufbx_material* material = mesh.materials.data[mesh_part->index];
                part.material_index = static_cast<int32_t>(material->typed_id);
            }
            else
            {
                part.material_index = -1;
            }

            // TODO: create the GPU buffers from the temporary `vertices` and `indices` arrays? See `viewer.c`!
            // 1. index buffer for `part`.
            // 2. vertex buffer for `part`.
            // 2. skin buffer for `part`.
        }

        // Compute bounds from the vertices.
        fbx_mesh.aabb_is_local = mesh.skinned_is_local;
        fbx_mesh.aabb_min = glm::vec3 { std::numeric_limits<float>::infinity() };
        fbx_mesh.aabb_max = glm::vec3 { -1.0f * std::numeric_limits<float>::infinity() };

        std::cout << "mesh.num_vertices: " << mesh.num_vertices << "\n";

        for (std::size_t vertex_i = 0; vertex_i < mesh.num_vertices; vertex_i++)
        {
            auto ufbx_pos = mesh.skinned_position.values.data[vertex_i];
            glm::vec3 pos { ufbx_pos.x, ufbx_pos.y, ufbx_pos.z };
            fbx_mesh.aabb_min = {
                std::min(fbx_mesh.aabb_min.x, pos.x),
                std::min(fbx_mesh.aabb_min.y, pos.y),
                std::min(fbx_mesh.aabb_min.z, pos.z)
            };
            fbx_mesh.aabb_max = {
                std::max(fbx_mesh.aabb_max.x, pos.x),
                std::max(fbx_mesh.aabb_max.y, pos.y),
                std::max(fbx_mesh.aabb_max.z, pos.z)
            };
        }

        fbx_mesh.parts = parts;
        fbx_mesh.num_parts = num_parts;

        fbx_mesh.vertices = vertices; // This might not be needed later if vertex streams are used instead.

        std::cout << "fbx_mesh.num_parts: " << fbx_mesh.num_parts << "\n";
        std::cout << "fbx_mesh.parts.size(): " << fbx_mesh.parts.size() << "\n";
        return fbx_mesh;
    }
}
