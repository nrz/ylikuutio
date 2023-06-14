// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2023 Antti Nuortimo.
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
#include "code/ylikuutio/file/file_loader.hpp"
#include <ofbx.h>

// OpenFBX wants `u8` == `unsigned char`.
typedef unsigned char u8;

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>       // std::size_t
#include <ios>           // std::defaultfloat, std::dec, std::fixed, std::hex, std::ios
#include <iostream>      // std::cout, std::cin, std::cerr
#include <stdint.h>      // uint32_t etc.
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
            std::unordered_map<const ofbx::Texture*, std::vector<int32_t>>& ofbx_diffuse_texture_mesh_map,
            std::vector<const ofbx::Mesh*>& ofbx_meshes,
            std::vector<const ofbx::Texture*>& ofbx_diffuse_texture_vector,
            std::vector<const ofbx::Texture*>& ofbx_normal_texture_vector,
            std::vector<const ofbx::Texture*>& ofbx_count_texture_vector,
            std::size_t& mesh_count,
            const bool is_debug_mode)
    {
        // Functions and data of interest in OpenFBX:
        // struct TakeInfo
        // {
        //     DataView name;
        //     DataView filename;
        //     double local_time_from;
        //     double local_time_to;
        //     double reference_time_from;
        //     double reference_time_to;
        // };
        //
        // IScene* load(const u8* data, int size)
        const std::optional<std::vector<uint8_t>> data_vector = yli::file::binary_slurp(filename);

        if (!data_vector || data_vector->empty())
        {
            std::cerr << filename << " could not be opened, or the file is empty.\n";
            return false;
        }

        // OpenFBX wants `u8` == `unsigned char`.
        const u8* data = reinterpret_cast<const u8*>(data_vector->data());
        const int64_t size = data_vector->size();

        if (is_debug_mode)
        {
            std::cout << "Loaded FBX data vector size: " << size << "\n";
        }

        const uint64_t flags = (uint64_t) ofbx::LoadFlags::TRIANGULATE;
        const ofbx::IScene* ofbx_iscene = ofbx::load(data, size, flags);

        if (ofbx_iscene == nullptr)
        {
            std::cerr << "ERROR: `ofbx_iscene` is `nullptr`!\n";
            return false;
        }

        const int temp_mesh_count = ofbx_iscene->getMeshCount(); // `getMeshCount()` returns `int`.

        if (temp_mesh_count < 0)
        {
            std::cerr << "ERROR: mesh count is negative!\n";
            return false;
        }

        mesh_count = static_cast<std::size_t>(temp_mesh_count);

        ofbx_meshes.reserve(mesh_count);

        for (std::size_t mesh_i = 0; mesh_i < mesh_count; mesh_i++)
        {
            const ofbx::Mesh* mesh = ofbx_iscene->getMesh(mesh_i);
            ofbx_meshes[mesh_i] = mesh;

            if (mesh == nullptr)
            {
                std::cerr << "ERROR: `mesh` is `nullptr`!\n";
                return false;
            }

            const ofbx::Geometry* geometry = mesh->getGeometry();

            if (geometry == nullptr)
            {
                std::cerr << "ERROR: `geometry` is `nullptr`!\n";
                return false;
            }

            // TODO: finalize the implementation of `yli::ontology::Symbiosis`
            // to be able to support for different materials!
            const int temp_material_count = mesh->getMaterialCount(); // TODO: use this in  `yli::ontology::Symbiosis` entities!

            if (is_debug_mode)
            {
                std::cout << filename << ": mesh " << mesh_i << ": getMaterialCount(): " << temp_material_count << "\n";
            }

            if (temp_material_count < 0)
            {
                std::cerr << "ERROR: material count is negative!\n";
                return false;
            }

            const std::size_t material_count = static_cast<std::size_t>(temp_material_count);

            for (std::size_t material_i = 0; material_i < material_count; material_i++)
            {
                if (is_debug_mode)
                {
                    std::cout << "mesh " << mesh_i << ", material " << material_i << "\n";
                }

                const ofbx::Material* material = mesh->getMaterial(material_i);

                if (material == nullptr)
                {
                    // Material should not be `nullptr`.
                    continue;
                }

                const ofbx::Texture* diffuse_texture = material->getTexture(ofbx::Texture::DIFFUSE);

                if (diffuse_texture == nullptr)
                {
                    if (is_debug_mode)
                    {
                        std::cout << "mesh " << mesh_i << ", DIFFUSE texture is `nullptr`\n";
                    }
                }
                else
                {
                    if (is_debug_mode)
                    {
                        std::cout << "mesh " << mesh_i << ", DIFFUSE texture at " << std::hex << reinterpret_cast<std::uintptr_t>(diffuse_texture) << std::dec << "\n";
                    }

                    // Add new texture to map.
                    if (ofbx_diffuse_texture_mesh_map.count(diffuse_texture) != 1)
                    {
                        // This `const ofbx::Material*` is not in `ofbx_diffuse_texture_mesh_map` yet.
                        ofbx_diffuse_texture_mesh_map[diffuse_texture] = std::vector<int32_t>();
                    }

                    if (is_debug_mode)
                    {
                        std::cout << "Adding mesh " << mesh_i << " to DIFFUSE texture at " << std::hex << reinterpret_cast<std::uintptr_t>(diffuse_texture) << std::dec << "\n";
                    }

                    ofbx_diffuse_texture_mesh_map[diffuse_texture].emplace_back(mesh_i);

                    if (is_debug_mode)
                    {
                        std::cout << "Adding mesh " << mesh_i << " to DIFFUSE textures.\n";
                    }

                    ofbx_diffuse_texture_vector.emplace_back(diffuse_texture);
                }

                const ofbx::Texture* normal_texture = material->getTexture(ofbx::Texture::NORMAL);

                if (normal_texture == nullptr)
                {
                    if (is_debug_mode)
                    {
                        std::cout << "Mesh " << mesh_i << ", NORMAL texture is `nullptr`\n";
                    }
                }
                else
                {
                    if (is_debug_mode)
                    {
                        std::cout << "Mesh " << mesh_i << ", NORMAL texture at " << std::hex << (void*) normal_texture << std::dec << "\n";
                    }

                    // TODO: store NORMAL textures similarly as DIFFUSE textures.

                    if (is_debug_mode)
                    {
                        std::cout << "Adding mesh " << mesh_i << " to NORMAL textures.\n";
                    }

                    ofbx_normal_texture_vector.emplace_back(normal_texture);
                }

                const ofbx::Texture* count_texture = material->getTexture(ofbx::Texture::COUNT);

                if (count_texture == nullptr)
                {
                    if (is_debug_mode)
                    {
                        std::cout << "Mesh " << mesh_i << ", COUNT texture is `nullptr`\n";
                    }
                }
                else
                {
                    if (is_debug_mode)
                    {
                        std::cout << "Mesh " << mesh_i << ", COUNT texture at " << std::hex << (void*) count_texture << std::dec << "\n";
                    }

                    // TODO: store COUNT textures similarly as DIFFUSE textures.

                    if (is_debug_mode)
                    {
                        std::cout << "Adding mesh " << mesh_i << " to COUNT textures.\n";
                    }
                    ofbx_count_texture_vector.emplace_back(count_texture);
                }
            }

            const int temp_vertex_count = geometry->getVertexCount();

            if (is_debug_mode)
            {
                std::cout << filename << ": mesh " << mesh_i << ": getVertexCount(): " << temp_vertex_count << "\n";
            }

            if (temp_vertex_count < 0)
            {
                std::cerr << "ERROR: vertex count is negative!\n";
                return false;
            }

            const std::size_t vertex_count = static_cast<std::size_t>(temp_vertex_count);

            const ofbx::Vec3* vertices = geometry->getVertices();

            if (vertices == nullptr)
            {
                std::cerr << "ERROR: `vertices` is `nullptr`!\n";
                return false;
            }

            const ofbx::Vec3* normals = geometry->getNormals();

            if (normals == nullptr)
            {
                std::cerr << "ERROR: `normals` is `nullptr`!\n";
                return false;
            }

            std::vector<glm::vec3> mesh_out_vertices;

            for (std::size_t i = 0; i < vertex_count; i++)
            {
                // vertices.
                glm::vec3 vertex = { vertices[i].x, vertices[i].y, vertices[i].z };
                mesh_out_vertices.emplace_back(vertex);
            }

            out_vertices.emplace_back(mesh_out_vertices);

            std::vector<glm::vec2> mesh_out_uvs;

            const ofbx::Vec2* uvs = geometry->getUVs();

            if (uvs == nullptr)
            {
                // `uvs` should not be `nullptr`.
                std::cerr << "ERROR: `uvs` is `nullptr`!\n";
            }
            else
            {
                for (std::size_t vertex_i = 0; vertex_i < vertex_count; vertex_i++)
                {
                    // UVs.
                    glm::vec2 uv = { uvs[vertex_i].x, uvs[vertex_i].y };
                    mesh_out_uvs.emplace_back(uv);
                }
            }

            out_uvs.emplace_back(mesh_out_uvs);

            std::vector<glm::vec3> mesh_out_normals;

            for (std::size_t i = 0; i < vertex_count; i++)
            {
                // Normals.
                glm::vec3 normal = { normals[i].x, normals[i].y, normals[i].z };
                mesh_out_normals.emplace_back(normal);
            }

            out_normals.emplace_back(mesh_out_normals);
        }

        return true;
    }
}
