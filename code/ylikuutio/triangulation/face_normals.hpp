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

#ifndef YLIKUUTIO_TRIANGULATION_FACE_NORMALS_HPP_INCLUDED
#define YLIKUUTIO_TRIANGULATION_FACE_NORMALS_HPP_INCLUDED

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif

#include "triangulation_enums.hpp"

// Include GLM
#ifndef GLM_GLM_HPP_INCLUDED
#define GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <vector>   // std::vector

namespace yli::triangulation
{
    bool compute_face_normals(
            std::vector<glm::vec3>& temp_vertices,
            std::vector<glm::vec3>& face_normal_vector_vec3,
            const std::size_t actual_image_width,
            const std::size_t actual_image_height,
            const bool is_bilinear_interpolation_in_use,
            const bool is_southwest_northeast_edges_in_use,
            const bool is_southeast_northwest_edges_in_use);

    const glm::vec3& get_face_normal(
            const std::vector<glm::vec3>& face_normal_data,
            const std::size_t x,
            const std::size_t z,
            const yli::triangulation::BilinearDirections compass_point_code,
            const std::size_t actual_image_width);

    // for bilinear interpolation.
    // These functions exist to avoid need to remember
    // the array order when calling `yli::geometry::get_face_normal`.
    const glm::vec3& s_face_normal(
            const std::vector<glm::vec3>& face_normal_vector_vec3,
            const std::size_t x,
            const std::size_t z,
            const std::size_t image_width);
    const glm::vec3& w_face_normal(
            const std::vector<glm::vec3>& face_normal_vector_vec3,
            const std::size_t x,
            const std::size_t z,
            const std::size_t image_width);
    const glm::vec3& n_face_normal(
            const std::vector<glm::vec3>& face_normal_vector_vec3,
            const std::size_t x,
            const std::size_t z,
            const std::size_t image_width);
    const glm::vec3& e_face_normal(
            const std::vector<glm::vec3>& face_normal_vector_vec3,
            const std::size_t x,
            const std::size_t z,
            const std::size_t image_width);

    // for southeast-northwest edges.
    glm::vec3 get_face_normal_for_se_nw(
            const std::vector<glm::vec3>& face_normal_data,
            const std::size_t x,
            const std::size_t z,
            const SoutheastNorthwestEdgesDirections compass_point_code,
            const std::size_t image_width);

    // for southwest-northeast edges.
    glm::vec3 get_face_normal_for_sw_ne(
            const std::vector<glm::vec3>& face_normal_data,
            const std::size_t x,
            const std::size_t z,
            const SouthwestNortheastEdgesDirections compass_point_code,
            const std::size_t image_width);
}

#endif
