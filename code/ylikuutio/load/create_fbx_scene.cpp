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

#include "create_fbx_scene.hpp"
#include "read_fbx_anim_stack.hpp"
#include "read_fbx_blend_channel.hpp"
#include "read_fbx_mesh.hpp"
#include "read_fbx_node.hpp"
#include "setup_fbx_texture.hpp"
#include "fbx_scene.hpp"
#include "fbx_triangle.hpp"
#include "fbx_triangle_info.hpp"
#include "fbx_mesh.hpp"
#include "fbx_mesh_vertex.hpp"
#include "fbx_pixel_16.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <cstdint>  // std::uint32_t
#include <iostream> // std::cerr
#include <limits>   // std::numeric_limits
#include <optional> // std::nullopt, std::optional

namespace yli::load
{
    std::optional<FbxScene> create_fbx_scene(const ufbx_scene& original_scene,
                                             const std::size_t subdivision_level,
                                             const bool needs_subdivision,
                                             const bool is_debug_mode)
    {
        // See `create_scene` of `picort.cpp` for a reference.

        if (is_debug_mode)
        {
            std::cout << "original_scene.nodes.count: " << original_scene.nodes.count << "\n";
        }

        FbxScene fbx_scene;
        fbx_scene.nodes.reserve(original_scene.nodes.count);

        // Read FBX nodes.
        for (std::size_t node_i = 0; node_i < original_scene.nodes.count; node_i++)
        {
            const auto& node = *original_scene.nodes.data[node_i];
            if (is_debug_mode)
            {
                std::cout << "node.element.type: " << node.element.type << "\n";
            }

            fbx_scene.nodes.emplace_back(read_fbx_node(node));
        }

        fbx_scene.blend_channels.reserve(original_scene.blend_channels.count);

        if (is_debug_mode)
        {
            std::cout << "original_scene.blend_channels.count: " << original_scene.blend_channels.count << "\n";
            std::cout << "original_scene.materials.count: " << original_scene.materials.count << "\n";
        }

        // Read FBX materials.

        // Reserve one undefined material.
        {
            FbxMaterial undefined_fbx_material {};
            undefined_fbx_material.base_color.filename = "";
            undefined_fbx_material.base_factor.value.x = 1.0f;
            undefined_fbx_material.base_color.value = glm::vec3 { 0.0f };
            undefined_fbx_material.roughness.value.x = 0.5f;
            undefined_fbx_material.metallic.value.x = 0.5f;
            // fbx_scene.materials.emplace_back(undefined_fbx_material);
        }

        // Process fBX materials.

        for (std::size_t material_i = 0; material_i < original_scene.materials.count; material_i++)
        {
            const ufbx_material* const source_material = original_scene.materials.data[material_i];

            FbxMaterial dest_material {};
            dest_material.base_factor.value.x = 1.0f;
            setup_fbx_texture(dest_material.base_factor, source_material->pbr.base_factor);
            setup_fbx_texture(dest_material.base_color, source_material->pbr.base_color);
            setup_fbx_texture(dest_material.specular_factor, source_material->pbr.specular_factor);
            setup_fbx_texture(dest_material.specular_color, source_material->pbr.specular_color);
            setup_fbx_texture(dest_material.roughness, source_material->pbr.roughness);
            setup_fbx_texture(dest_material.metallic, source_material->pbr.metalness);
            setup_fbx_texture(dest_material.emission_factor, source_material->pbr.emission_factor);
            setup_fbx_texture(dest_material.emission_color, source_material->pbr.emission_color);
            dest_material.has_metallic = source_material->features.metalness.enabled;
            dest_material.has_specular = source_material->features.specular.enabled;
            dest_material.base_color.image.srgb = true;
            dest_material.emission_color.image.srgb = true;

            // TODO: implement shadows! See `picort.cpp`!
            dest_material.cast_shadows = false;

            // TODO: implement alpha! See `picort.cpp`!
            if (dest_material.base_color.image.width > 0 && dest_material.base_color.image.height > 0)
            {
                const std::size_t num_pixels =
                        dest_material.base_color.image.width * dest_material.base_color.image.height;
                const std::vector<FbxPixel16>& pixels = dest_material.base_color.image.pixels;

                if (is_debug_mode)
                {
                    std::cout << "Specular color filename: " << dest_material.specular_color.filename << "\n";
                    std::cout << "Base color image width: " << dest_material.base_color.image.width << "\n";
                    std::cout << "Base color image height: " << dest_material.base_color.image.height << "\n";
                    std::cout << "num_pixels: " << num_pixels << "\n";
                    std::cout << "pixels.size(): " << pixels.size() << "\n";
                }

                if (num_pixels != pixels.size())
                {
                    std::cerr << "ERROR: `yli::load::create_fbx_scene`: `num_pixels` does not match `pixels.size()`!\n";
                    return std::nullopt;
                }

                for (std::size_t pixel_i = 0; pixel_i < num_pixels; pixel_i++)
                {
                    if (pixels.at(pixel_i).alpha < 0xffff)
                    {
                        dest_material.has_alpha = true;
                        break;
                    }
                }
            }

            fbx_scene.materials.emplace_back(dest_material);;
        }

        if (is_debug_mode)
        {
            std::cout << "original_scene.meshes.count: " << original_scene.meshes.count << "\n";
        }

        fbx_scene.meshes.reserve(original_scene.meshes.count);

        // Process FBX meshes.

        std::vector<std::uint32_t> indices;
        std::vector<FbxTriangle> triangles;

        for (std::size_t mesh_i = 0; mesh_i < original_scene.meshes.count; mesh_i++)
        {
            ufbx_mesh* original_mesh = original_scene.meshes[mesh_i];

            if (original_mesh->instances.count == 0)
            {
                continue;
            }

            ufbx_mesh* mesh = (needs_subdivision
                                   ? ufbx_subdivide_mesh(original_mesh, subdivision_level, nullptr, nullptr)
                                   : original_mesh);

            if (mesh == nullptr)
            {
                std::cerr << "ERROR: `yli::load::create_fbx_scene`: mesh subdivision failed: `mesh` is `nullptr`!\n";
                return std::nullopt;
            }

            if (indices.size() < 3 * mesh->max_face_triangles)
            {
                indices.resize(3 * mesh->max_face_triangles);
            }

            FbxMesh fbx_mesh {};
            fbx_mesh.num_instances = mesh->instances.count;

            // Iterate over all instances of the mesh.
            for (const ufbx_node* const node : mesh->instances)
            {
                if (!node->visible)
                {
                    continue;
                }

                ufbx_matrix normal_to_world = ufbx_matrix_for_normals(&node->geometry_to_world);

                // Iterate over all n-gon faces of the mesh.
                for (std::size_t face_i = 0; face_i < mesh->num_faces; face_i++)
                {
                    // Split the face into triangles.
                    const std::size_t num_triangles = ufbx_triangulate_face(indices.data(), indices.size(), mesh,
                                                                            mesh->faces[face_i]);

                    // Iterate over all split triangles.
                    for (std::size_t triangle_i = 0; triangle_i < num_triangles; triangle_i++)
                    {
                        FbxTriangle triangle;
                        FbxTriangleInfo triangle_info;
                        triangle.index = fbx_scene.triangles.size();

                        if (mesh->face_material.count > 0)
                        {
                            const ufbx_material* const material = mesh->materials.data[mesh->face_material[face_i]];
                            triangle_info.material = material->element.typed_id;

                            if (fbx_mesh.material_i == std::numeric_limits<std::size_t>::max())
                            {
                                // Use the first listed material of the mesh.
                                fbx_mesh.material_i = material->element.typed_id;
                            }
                        }

                        for (std::size_t corner_i = 0; corner_i < 3; corner_i++)
                        {
                            const std::uint32_t index = indices[3 * triangle_i + corner_i];

                            // Load the skinned vertex position at `index`.
                            ufbx_vec3 vertex = ufbx_get_vertex_vec3(&mesh->skinned_position, index);

                            ufbx_vec2 uv = mesh->vertex_uv.exists
                                               ? ufbx_get_vertex_vec2(&mesh->vertex_uv, index)
                                               : ufbx_vec2 {};
                            ufbx_vec3 normal = ufbx_get_vertex_vec3(&mesh->skinned_normal, index);

                            // If the skinned positions are local, we must apply 'to root' to get world coordinates.
                            if (mesh->skinned_is_local)
                            {
                                // TODO: use these ufbx functions if needed there is need later on!
                                // vertex = ufbx_transform_position(&node->geometry_to_world, vertex);
                                // normal = ufbx_transform_direction(&normal_to_world, normal);
                            }

                            FbxMeshVertex fbx_mesh_vertex {};
                            fbx_mesh_vertex.position = {
                                static_cast<float>(vertex.x),
                                static_cast<float>(vertex.y),
                                static_cast<float>(vertex.z)
                            };
                            fbx_mesh_vertex.normal = glm::normalize(
                                glm::vec3 {
                                    static_cast<float>(normal.x),
                                    static_cast<float>(normal.y),
                                    static_cast<float>(normal.z)
                                });
                            fbx_mesh_vertex.uv = { uv.x, uv.y };
                            fbx_mesh_vertex.f_vertex_index = static_cast<float>(mesh->vertex_indices.data[triangle_i]);

                            fbx_mesh.vertices.emplace_back(fbx_mesh_vertex);

                            triangle_info.vertices[corner_i] = fbx_mesh_vertex.position;
                            triangle_info.uvs[corner_i] = fbx_mesh_vertex.uv;
                            triangle_info.normals[corner_i] = fbx_mesh_vertex.normal;

                            triangle.vertices[corner_i] = fbx_mesh_vertex.position;
                        }

                        triangles.emplace_back(triangle);
                        fbx_scene.triangles.emplace_back(triangle_info);
                    }
                }
            }

            fbx_scene.meshes.emplace_back(fbx_mesh);

            if (mesh != original_mesh)
            {
                ufbx_free_mesh(mesh);
            }
        }

        for (std::size_t light_i = 0; light_i < original_scene.lights.count; light_i++)
        {
            // TODO: process lights!
        }

        // Read FBX blend channels.
        for (std::size_t blend_channel_i = 0; blend_channel_i < original_scene.blend_channels.count; blend_channel_i++)
        {
            const ufbx_blend_channel* const blend_channel = original_scene.blend_channels.data[blend_channel_i];

            if (blend_channel == nullptr)
            {
                std::cerr << "ERROR: `blend_channel` " << blend_channel_i << " is `nullptr`!\n";
                return std::nullopt;
            }
            fbx_scene.blend_channels.emplace_back(read_fbx_blend_channel(*blend_channel));
        }

        std::cout << "original_scene.anim_stacks.count: " << original_scene.anim_stacks.count << "\n";
        fbx_scene.animations.reserve(original_scene.anim_stacks.count);

        // Read FBX animations.
        for (std::size_t animation_i = 0; animation_i < original_scene.anim_stacks.count; animation_i++)
        {
            fbx_scene.animations.emplace_back(
                read_fbx_anim_stack(*original_scene.anim_stacks.data[animation_i], original_scene));
        }

        // Return complete FBX original_scene.
        return fbx_scene;
    }
}
