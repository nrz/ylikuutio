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

#include "fbx_model_loader.hpp"
#include "load_fbx_struct.hpp"
#include "create_fbx_scene.hpp"
#include "fbx_scene.hpp"
#include "fbx_mesh.hpp"
#include "fbx_mesh_vertex.hpp"
#include <ufbx.h>

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cerr
#include <optional> // std::optional
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::load
{
    bool load_fbx(
        const std::string& filename,
        const std::size_t mesh_i,
        std::vector<glm::vec3>& out_vertices,
        std::vector<glm::vec2>& out_uvs,
        std::vector<glm::vec3>& out_normals,
        const LoadFbxStruct& load_fbx_struct)
    {
        ufbx_error error;
        ufbx_scene* const original_scene = ufbx_load_file(filename.c_str(), &load_fbx_struct.load_opts, &error);

        if (original_scene == nullptr)
        {
            std::cerr << "ERROR: `yli::load::load_fbx`: loading FBX file " << filename << " failed!\n";
            char buffer[4096];
            ufbx_format_error(buffer, sizeof(buffer), &error);
            std::cerr << buffer << "\n";
            return false;
        }

        const std::optional<FbxScene> maybe_fbx_scene = create_fbx_scene(
            *original_scene, load_fbx_struct);

        if (!maybe_fbx_scene.has_value())
        {
            std::cerr << "ERROR: `yli::load::load_fbx`: reading scene of FBX file " << filename << " failed!\n";
            ufbx_free_scene(original_scene);
            return false;
        }

        const FbxScene& fbx_scene = maybe_fbx_scene.value();

        std::cout << "fbx_scene.nodes.size(): " << fbx_scene.nodes.size() << "\n";

        // Process the mesh indexed by argument `mesh_i`.
        const auto mesh_count = fbx_scene.meshes.size();
        std::cout << "mesh_count: " << mesh_count << "\n";

        if (mesh_i >= mesh_count)
        {
            std::cerr << "ERROR: `mesh_i` >= `mesh_count`\n";
            ufbx_free_scene(original_scene);
            return false;
        }

        const FbxMesh& mesh = fbx_scene.meshes.at(mesh_i);
        const std::size_t mesh_vertex_count = mesh.vertices.size();

        if (load_fbx_struct.is_debug_mode)
        {
            std::cout << filename << ": fbx_mesh " << mesh_i << "\n";
            std::cout << "mesh.blend_channel_indices.size(): " << mesh.blend_channel_indices.size() <<
                    "\n";
            std::cout << "mesh.num_bones: " << mesh.num_bones << "\n";
            std::cout << "mesh.bone_indices.size(): " << mesh.bone_indices.size() << "\n";
            std::cout << "mesh.bone_matrices.size(): " << mesh.bone_matrices.size() << "\n";
            std::cout << "mesh.instance_node_indices.size(): " << mesh.instance_node_indices.size() << "\n";
            std::cout << "mesh.num_parts: " << mesh.num_parts << "\n";
            std::cout << "mesh.parts.size(): " << mesh.parts.size() << "\n";
            std::cout << "Mesh " << mesh_i << " has " << mesh_vertex_count << " vertices.\n";
        }

        for (std::size_t mesh_vertex_i = 0; mesh_vertex_i < mesh_vertex_count; mesh_vertex_i++)
        {
            glm::vec3 vertex = {
                mesh.vertices[mesh_vertex_i].position.x,
                mesh.vertices[mesh_vertex_i].position.y,
                mesh.vertices[mesh_vertex_i].position.z
            };
            out_vertices.emplace_back(vertex);

            glm::vec2 uv = {
                mesh.vertices[mesh_vertex_i].uv.x,
                mesh.vertices[mesh_vertex_i].uv.y
            };
            out_uvs.emplace_back(uv);

            glm::vec3 normal = {
                mesh.vertices[mesh_vertex_i].normal.x,
                mesh.vertices[mesh_vertex_i].normal.y,
                mesh.vertices[mesh_vertex_i].normal.z
            };
            out_normals.emplace_back(normal);
        }

        // TODO: Compute the world-space bounding box!

        // TODO: rest of FBX loading!

        ufbx_free_scene(original_scene);
        return true;
    }
}
