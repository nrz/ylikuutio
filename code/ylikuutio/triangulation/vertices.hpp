// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
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

#ifndef __YLIKUUTIO_TRIANGULATION_VERTICES_HPP_INCLUDED
#define __YLIKUUTIO_TRIANGULATION_VERTICES_HPP_INCLUDED

#include "triangulate_quads_struct.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace yli::triangulation
{
    void output_triangle_vertices(
            const std::vector<glm::vec3>& temp_vertices,
            const std::vector<glm::vec2>& temp_uvs,
            const std::vector<glm::vec3>& temp_normals,
            const uint32_t vertex_index[3],
            const uint32_t uv_index[3],
            const uint32_t normal_index[3],
            std::vector<glm::vec3>& out_vertices,
            std::vector<glm::vec2>& out_uvs,
            std::vector<glm::vec3>& out_normals);

    bool define_vertices_uvs_and_normals(
            const yli::triangulation::TriangulateQuadsStruct& triangulate_quads_struct,
            const std::vector<glm::vec3>& temp_vertices,
            const std::vector<glm::vec2>& temp_uvs,
            const std::vector<glm::vec3>& temp_normals,
            std::vector<glm::vec3>& out_vertices,
            std::vector<glm::vec2>& out_uvs,
            std::vector<glm::vec3>& out_normals,
            const std::size_t actual_image_width,
            const std::size_t actual_image_height,
            const bool is_bilinear_interpolation_in_use,
            const bool is_southwest_northeast_edges_in_use,
            const bool is_southeast_northwest_edges_in_use);
}

#endif
