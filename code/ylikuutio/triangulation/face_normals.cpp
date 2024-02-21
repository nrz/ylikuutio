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

#include "face_normals.hpp"
#include "triangulation_enums.hpp"
#include "indexing.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cerr
#include <vector>   // std::vector

namespace yli::triangulation
{
    bool compute_face_normals(
            std::vector<glm::vec3>& temp_vertices,
            std::vector<glm::vec3>& face_normal_vector_vec3,
            const std::size_t actual_image_width,
            const std::size_t actual_image_height)
    {
        std::size_t current_interpolated_vertex_i = actual_image_width * actual_image_height;

        if (actual_image_width < 2)
        {
            // If width is < 2, there are no faces.
            std::cerr << "ERROR: `actual_image_width` is less than 2.\n";
            return false;
        }

        if (actual_image_height < 2)
        {
            // If height is < 2, there are no faces.
            std::cerr << "ERROR: `actual_image_height` is less than 2.\n";
            return false;
        }

        if (temp_vertices.size() != actual_image_width * actual_image_height + (actual_image_width - 1) * (actual_image_height - 1))
        {
            // Number of vertices must be correct.
            std::cerr << "ERROR: incorrect number of vertices.\n";
            return false;
        }

        // If bilinear interpolation is in use, then number of faces is:
        // 4 * (actual_image_width - 1) * (actual_image_height - 1)
        face_normal_vector_vec3.reserve(4 * (actual_image_width - 1) * (actual_image_height - 1));

        for (std::size_t z = 1; z < actual_image_height; z++)
        {
            for (std::size_t x = 1; x < actual_image_width; x++)
            {
                std::size_t current_vertex_i = actual_image_width * z + x;

                const glm::vec3& southeast_edge = temp_vertices[southeast(current_vertex_i, actual_image_width)] - temp_vertices[current_interpolated_vertex_i];
                const glm::vec3& southwest_edge = temp_vertices[southwest(current_vertex_i, actual_image_width)] - temp_vertices[current_interpolated_vertex_i];
                const glm::vec3& northwest_edge = temp_vertices[northwest(current_vertex_i, actual_image_width)] - temp_vertices[current_interpolated_vertex_i];
                const glm::vec3& northeast_edge = temp_vertices[northeast(current_vertex_i, actual_image_width)] - temp_vertices[current_interpolated_vertex_i];

                // Compute the normal of S face.
                face_normal_vector_vec3.emplace_back(glm::normalize(glm::cross(southeast_edge, southwest_edge)));

                // Compute the normal of W face.
                face_normal_vector_vec3.emplace_back(glm::normalize(glm::cross(southwest_edge, northwest_edge)));

                // Compute the normal of N face.
                face_normal_vector_vec3.emplace_back(glm::normalize(glm::cross(northwest_edge, northeast_edge)));

                // Compute the normal of E face.
                face_normal_vector_vec3.emplace_back(glm::normalize(glm::cross(northeast_edge, southeast_edge)));

                current_interpolated_vertex_i++;
            }
        }
        return true;
    }

    // for bilinear interpolation.
    const glm::vec3& get_face_normal(
            const std::vector<glm::vec3>& face_normal_data,
            const std::size_t x,
            const std::size_t z,
            const yli::triangulation::BilinearDirections compass_point_code,
            const std::size_t actual_image_width)
    {
        const std::size_t face_normal_i = get_face_normal_i(x, z, compass_point_code, actual_image_width);
        return face_normal_data[face_normal_i];
    }

    // for bilinear interpolation.
    // These functions exist to avoid need to remember
    // the array order when calling `yli::triangulation::get_face_normal`.
    const glm::vec3& s_face_normal(
            const std::vector<glm::vec3>& face_normal_vector_vec3,
            const std::size_t x,
            const std::size_t z,
            const std::size_t image_width)
    {
        return yli::triangulation::get_face_normal(face_normal_vector_vec3, x - 1, z - 1, yli::triangulation::BilinearDirections::ENE, image_width);
    }
    const glm::vec3& w_face_normal(
            const std::vector<glm::vec3>& face_normal_vector_vec3,
            const std::size_t x,
            const std::size_t z,
            const std::size_t image_width)
    {
        return yli::triangulation::get_face_normal(face_normal_vector_vec3, x - 1, z - 1, yli::triangulation::BilinearDirections::NNE, image_width);
    }
    const glm::vec3& n_face_normal(
            const std::vector<glm::vec3>& face_normal_vector_vec3,
            const std::size_t x,
            const std::size_t z,
            const std::size_t image_width)
    {
        return yli::triangulation::get_face_normal(face_normal_vector_vec3, x, z, yli::triangulation::BilinearDirections::WSW, image_width);
    }
    const glm::vec3& e_face_normal(
            const std::vector<glm::vec3>& face_normal_vector_vec3,
            const std::size_t x,
            const std::size_t z,
            const std::size_t image_width)
    {
        return yli::triangulation::get_face_normal(face_normal_vector_vec3, x, z, yli::triangulation::BilinearDirections::SSW, image_width);
    }
}
