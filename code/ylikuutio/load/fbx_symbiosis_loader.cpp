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

#include "fbx_symbiosis_loader.hpp"
#include "load_fbx_struct.hpp"
#include "create_fbx_scene.hpp"
#include "fbx_material.hpp"
#include "fbx_mesh.hpp"
#include <ufbx.h>

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>       // std::size_t
#include <ios>           // std::dec, std::hex
#include <iostream>      // std::cout, std::cerr
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

namespace yli::load
{
    bool load_fbx(
        const std::string& filename,
        std::vector<std::vector<glm::vec3>>& out_vertices,
        std::vector<std::vector<glm::vec2>>& out_uvs,
        std::vector<std::vector<glm::vec3>>& out_normals,
        std::unordered_map<std::size_t, std::vector<std::size_t>>& fbx_material_mesh_map,
        std::vector<FbxMaterial>& fbx_materials,
        std::vector<FbxMesh>& fbx_meshes,
        std::size_t& mesh_count,
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

        mesh_count = fbx_scene.meshes.size();
        std::cout << "mesh_count: " << mesh_count << "\n";
        fbx_meshes.reserve(mesh_count);

        // NOTE: The material count is from scene, not from mesh.
        const std::size_t material_count = fbx_scene.materials.size();
        std::cout << "material_count: " << material_count << "\n";

        std::cout << "fbx_scene.nodes.size(): " << fbx_scene.nodes.size() << "\n";

        for (std::size_t mesh_i = 0; mesh_i < mesh_count; mesh_i++)
        {
            const FbxMesh& mesh = fbx_scene.meshes.at(mesh_i);
            fbx_meshes.emplace_back(mesh);

            const std::size_t mesh_vertex_count = mesh.vertices.size();
            std::cout << "Mesh " << mesh_i << " has " << mesh_vertex_count << " vertices.\n";

            {
                std::vector<glm::vec3> mesh_out_vertices;
                std::vector<glm::vec2> mesh_out_uvs;
                std::vector<glm::vec3> mesh_out_normals;

                for (std::size_t mesh_vertex_i = 0; mesh_vertex_i < mesh_vertex_count; mesh_vertex_i++)
                {
                    const glm::vec3 vertex = {
                        mesh.vertices[mesh_vertex_i].position.x,
                        mesh.vertices[mesh_vertex_i].position.y,
                        mesh.vertices[mesh_vertex_i].position.z
                    };
                    mesh_out_vertices.emplace_back(vertex);

                    const glm::vec2 uv = {
                        mesh.vertices[mesh_vertex_i].uv.x,
                        mesh.vertices[mesh_vertex_i].uv.y
                    };
                    mesh_out_uvs.emplace_back(uv);

                    const glm::vec3 normal = {
                        mesh.vertices[mesh_vertex_i].normal.x,
                        mesh.vertices[mesh_vertex_i].normal.y,
                        mesh.vertices[mesh_vertex_i].normal.z
                    };
                    mesh_out_normals.emplace_back(normal);
                }

                out_vertices.emplace_back(mesh_out_vertices);
                out_uvs.emplace_back(mesh_out_uvs);
                out_normals.emplace_back(mesh_out_normals);
            }

            for (std::size_t material_i = 0; material_i < material_count; material_i++)
            {
                const FbxMaterial& material = fbx_scene.materials.at(material_i);
                fbx_materials.emplace_back(material);

                if (!fbx_material_mesh_map.contains(material_i))
                {
                    fbx_material_mesh_map[material_i] = std::vector<std::size_t> {};
                }
                if (material.has_alpha)
                {
                    std::cout << "Material " << material_i << " has alpha.\n";
                }
                if (material.has_metallic)
                {
                    std::cout << "Material " << material_i << " has metallic.\n";
                }
                if (material.has_specular)
                {
                    std::cout << "Material " << material_i << " has specular.\n";
                }

                if (material.cast_shadows)
                {
                    std::cout << "Material " << material_i << " casts shadows.\n";
                }
                else
                {
                    std::cout << "Material " << material_i << " does not cast shadows.\n";
                }

                // TODO: rest of material!
            }

            if (mesh.material_i < std::numeric_limits<std::size_t>::max())
            {
                if (mesh.material_i >= material_count)
                {
                    std::cerr << "ERROR: `yli::load::load_fbx`: invalid `mesh.material_i`!\n";
                }
                else
                {
                    if (load_fbx_struct.is_debug_mode)
                    {
                        std::cout << "Adding mesh " << mesh_i << " to material " << mesh.material_i << ".\n";
                    }

                    fbx_material_mesh_map.at(mesh.material_i).emplace_back(mesh_i);
                }
            }
        }

        // TODO: Compute the world-space bounding box!

        // TODO: rest of FBX loading!

        ufbx_free_scene(original_scene);
        return true;
    }
}
