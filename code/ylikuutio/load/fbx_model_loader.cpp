// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2022 Antti Nuortimo.
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
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <memory>   // std::make_shared, std::shared_ptr
#include <optional> // std::optional
#include <stdint.h> // uint32_t etc.
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
        const std::optional<std::vector<unsigned char>> data_vector = yli::file::binary_slurp(filename);

        if (!data_vector || data_vector->empty())
        {
            std::cerr << filename << " could not be opened, or the file is empty.\n";
            return false;
        }

        // OpenFBX wants `u8` == `unsigned char`.
        const u8* data = reinterpret_cast<const u8*>(data_vector->data());
        int size = data_vector->size();

        if (is_debug_mode)
        {
            std::cout << "Loaded FBX data vector size: " << size << "\n";
        }

        const uint64_t flags = (uint64_t) ofbx::LoadFlags::TRIANGULATE;
        ofbx::IScene* ofbx_iscene = ofbx::load(data, size, flags);

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

        const std::size_t mesh_count = static_cast<std::size_t>(temp_mesh_count);

        if (mesh_i >= mesh_count)
        {
            std::cerr << "ERROR: `mesh_i` >= `mesh_count`\n";
            return false;
        }

        const ofbx::Mesh* mesh = ofbx_iscene->getMesh(mesh_i);

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

        const int material_count = mesh->getMaterialCount();

        if (is_debug_mode)
        {
            std::cout << filename << ": mesh " << mesh_i << ": getMaterialCount(): " << material_count << "\n";
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

        for (std::size_t i = 0; i < vertex_count; i++)
        {
            // vertices.
            glm::vec3 vertex = { vertices[i].x, vertices[i].y, vertices[i].z };
            out_vertices.emplace_back(vertex);
        }

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
                out_uvs.emplace_back(uv);
            }
        }

        for (std::size_t i = 0; i < vertex_count; i++)
        {
            // Normals.
            glm::vec3 normal = { normals[i].x, normals[i].y, normals[i].z };
            out_normals.emplace_back(normal);
        }

        return true;
    }
}
