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

#include "vboindexer.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <cstring>  // std::memcmp, std::strcmp, std::strlen, std::strncmp
#include <map>      // std::map
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

// Returns true iif v1 can be considered equal to v2
bool is_near(float v1, float v2)
{
    return (fabs(v1 - v2) < 0.01f);
}

// Searches through all already-exported vertices
// for a similar one.
// Similar = same position + same UVs + same normal
bool getSimilarVertexIndex(
        const glm::vec3& in_vertex,
        const glm::vec2& in_uv,
        const glm::vec3& in_normal,
        std::vector<glm::vec3>& out_vertices,
        std::vector<glm::vec2>& out_uvs,
        std::vector<glm::vec3>& out_normals,
        uint32_t &result)
{
    // Lame linear search
    for (std::size_t i = 0; i < out_vertices.size(); i++)
    {
        if (is_near(in_vertex.x, out_vertices[i].x) &&
                is_near(in_vertex.y, out_vertices[i].y) &&
                is_near(in_vertex.z, out_vertices[i].z) &&
                is_near(in_uv.x, out_uvs[i].x) &&
                is_near(in_uv.y, out_uvs[i].y) &&
                is_near(in_normal.x, out_normals [i].x) &&
                is_near(in_normal.y, out_normals [i].y) &&
                is_near(in_normal.z, out_normals [i].z))
        {
            result = i;
            return true;
        }
    }

    // No other vertex could be used instead.
    // Looks like we'll have to add it to the VBO.
    return false;
}

namespace yli::opengl
{
    struct PackedVertex
    {
        glm::vec3 position;
        glm::vec2 uv;
        glm::vec3 normal;
        bool operator < (const PackedVertex that) const
        {
            return (std::memcmp((void*) this, (void*) &that, sizeof(PackedVertex)) > 0);
        };
    };

    bool getSimilarVertexIndex_fast(
            const PackedVertex& packed,
            const std::map<PackedVertex, uint32_t>& VertexToOutIndex,
            uint32_t& result)
    {
        const std::map<PackedVertex, uint32_t>::const_iterator it = VertexToOutIndex.find(packed);
        if (it == VertexToOutIndex.end())
        {
            return false;
        }
        else
        {
            result = it->second;
            return true;
        }
    }

    void indexVBO(
            const std::vector<glm::vec3>& in_vertices,
            const std::vector<glm::vec2>& in_UVs,
            const std::vector<glm::vec3>& in_normals,
            std::vector<uint32_t>& out_indices,
            std::vector<glm::vec3>& out_vertices,
            std::vector<glm::vec2>& out_uvs,
            std::vector<glm::vec3>& out_normals)
    {
        std::map<PackedVertex, uint32_t> VertexToOutIndex;

        // For each input vertex
        for (std::size_t i = 0; i < in_vertices.size() && i < in_UVs.size() && i < in_normals.size(); i++)
        {
            PackedVertex packed = { in_vertices[i], in_UVs[i], in_normals[i] };

            // Try to find a similar vertex in out_XXXX
            uint32_t index;
            bool found = getSimilarVertexIndex_fast(packed, VertexToOutIndex, index);

            if (found)
            {
                // A similar vertex is already in the VBO, use it instead !
                out_indices.emplace_back(index);
            }
            else
            {
                // If not, it needs to be added in the output data.
                out_vertices.emplace_back(in_vertices[i]);
                out_uvs.emplace_back(in_UVs[i]);
                out_normals.emplace_back(in_normals[i]);
                uint32_t newindex = (uint32_t) out_vertices.size() - 1;
                out_indices.emplace_back(newindex);
                VertexToOutIndex[packed] = newindex;
            }
        }
    }
}
