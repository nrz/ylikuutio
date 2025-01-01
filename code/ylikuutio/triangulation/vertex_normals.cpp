// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2025 Antti Nuortimo.
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

#include "vertex_normals.hpp"
#include "face_normals.hpp"
#include "triangulation_enums.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <vector>   // std::vector

namespace yli::triangulation
{
    bool compute_vertex_normals(
            std::vector<glm::vec3>& temp_normals,
            std::vector<glm::vec3>& face_normal_vector_vec3,
            const std::size_t actual_image_width,
            const std::size_t actual_image_height)
    {
        // 5. Compute the vertex normals for vertices loaded from file, `emplace_back` to `temp_normals`.

        if (actual_image_width < 2 || actual_image_height < 2)
        {
            // If width or height is < 2, there are no faces.
            return false;
        }

        if (face_normal_vector_vec3.size() != 4 * (actual_image_width - 1) * (actual_image_height - 1))
        {
            // If number of face normals is not 4 * width * height, then the number of vertices is incorrect.
            return false;
        }

        const std::size_t number_of_interpolated_vertices = (actual_image_width - 1) * (actual_image_height - 1);
        temp_normals.reserve(actual_image_width * actual_image_height + number_of_interpolated_vertices);

        std::size_t x = 0;
        std::size_t z = 0;

        // Compute the normal of the southwesternmost vertex.
        // Number of adjacent faces: 2.
        temp_normals.emplace_back(glm::normalize(
                    get_face_normal(face_normal_vector_vec3, x, z, yli::triangulation::BilinearDirections::NNE, actual_image_width) +
                    get_face_normal(face_normal_vector_vec3, x, z, yli::triangulation::BilinearDirections::ENE, actual_image_width)));

        // Compute the normals of southern vertices.
        for (x = 1; x < actual_image_width - 1; x++)
        {
            // Compute the normal of a southern vertex.
            // Number of adjacent faces: 4.
            temp_normals.emplace_back(glm::normalize(
                        get_face_normal(face_normal_vector_vec3, x, z, yli::triangulation::BilinearDirections::WNW, actual_image_width) +
                        get_face_normal(face_normal_vector_vec3, x, z, yli::triangulation::BilinearDirections::NNW, actual_image_width) +
                        get_face_normal(face_normal_vector_vec3, x, z, yli::triangulation::BilinearDirections::NNE, actual_image_width) +
                        get_face_normal(face_normal_vector_vec3, x, z, yli::triangulation::BilinearDirections::ENE, actual_image_width)));
        }

        // Compute the normal of the southeasternmost vertex.
        // Number of adjacent faces: 2.
        x = actual_image_width - 1;
        temp_normals.emplace_back(glm::normalize(
                    get_face_normal(face_normal_vector_vec3, x, z, yli::triangulation::BilinearDirections::WNW, actual_image_width) +
                    get_face_normal(face_normal_vector_vec3, x, z, yli::triangulation::BilinearDirections::NNW, actual_image_width)));

        // Then, define most normals in a double loop.
        for (z = 1; z < actual_image_height - 1; z++)
        {
            // Compute the normal of a western vertex.
            // Number of adjacent faces: 4.
            x = 0;
            temp_normals.emplace_back(glm::normalize(
                        get_face_normal(face_normal_vector_vec3, x, z, yli::triangulation::BilinearDirections::NNE, actual_image_width) +
                        get_face_normal(face_normal_vector_vec3, x, z, yli::triangulation::BilinearDirections::ENE, actual_image_width) +
                        get_face_normal(face_normal_vector_vec3, x, z, yli::triangulation::BilinearDirections::ESE, actual_image_width) +
                        get_face_normal(face_normal_vector_vec3, x, z, yli::triangulation::BilinearDirections::SSE, actual_image_width)));

            for (x = 1; x < actual_image_width - 1; x++)
            {
                // Compute the normal of a central vertex.
                // Number of adjacent faces: 8.
                temp_normals.emplace_back(glm::normalize(
                            get_face_normal(face_normal_vector_vec3, x, z, yli::triangulation::BilinearDirections::SSW, actual_image_width) +
                            get_face_normal(face_normal_vector_vec3, x, z, yli::triangulation::BilinearDirections::WSW, actual_image_width) +
                            get_face_normal(face_normal_vector_vec3, x, z, yli::triangulation::BilinearDirections::WNW, actual_image_width) +
                            get_face_normal(face_normal_vector_vec3, x, z, yli::triangulation::BilinearDirections::NNW, actual_image_width) +
                            get_face_normal(face_normal_vector_vec3, x, z, yli::triangulation::BilinearDirections::NNE, actual_image_width) +
                            get_face_normal(face_normal_vector_vec3, x, z, yli::triangulation::BilinearDirections::ENE, actual_image_width) +
                            get_face_normal(face_normal_vector_vec3, x, z, yli::triangulation::BilinearDirections::ESE, actual_image_width) +
                            get_face_normal(face_normal_vector_vec3, x, z, yli::triangulation::BilinearDirections::SSE, actual_image_width)));
            }

            x = actual_image_width - 1;

            // Compute the normal of an eastern vertex.
            // Number of adjacent faces: 4.
            temp_normals.emplace_back(glm::normalize(
                        get_face_normal(face_normal_vector_vec3, x, z, yli::triangulation::BilinearDirections::SSW, actual_image_width) +
                        get_face_normal(face_normal_vector_vec3, x, z, yli::triangulation::BilinearDirections::WSW, actual_image_width) +
                        get_face_normal(face_normal_vector_vec3, x, z, yli::triangulation::BilinearDirections::WNW, actual_image_width) +
                        get_face_normal(face_normal_vector_vec3, x, z, yli::triangulation::BilinearDirections::NNW, actual_image_width)));
        }

        // Compute the normal of the northwesternmost vertex.
        // Number of adjacent faces: 2.
        x = 0;
        temp_normals.emplace_back(glm::normalize(
                    get_face_normal(face_normal_vector_vec3, x, z, yli::triangulation::BilinearDirections::SSE, actual_image_width) +
                    get_face_normal(face_normal_vector_vec3, x, z, yli::triangulation::BilinearDirections::ESE, actual_image_width)));

        // Compute the normals of northern vertices.
        for (x = 1; x < actual_image_width - 1; x++)
        {
            // Compute the normal of a northern vertex.
            // Number of adjacent faces: 4.
            temp_normals.emplace_back(glm::normalize(
                        get_face_normal(face_normal_vector_vec3, x, z, yli::triangulation::BilinearDirections::SSW, actual_image_width) +
                        get_face_normal(face_normal_vector_vec3, x, z, yli::triangulation::BilinearDirections::WSW, actual_image_width) +
                        get_face_normal(face_normal_vector_vec3, x, z, yli::triangulation::BilinearDirections::ESE, actual_image_width) +
                        get_face_normal(face_normal_vector_vec3, x, z, yli::triangulation::BilinearDirections::SSE, actual_image_width)));
        }

        // Compute the normal of the northeasternmost vertex.
        // Number of adjacent faces: 2.
        x = actual_image_width - 1;
        temp_normals.emplace_back(glm::normalize(
                    get_face_normal(face_normal_vector_vec3, x, z, yli::triangulation::BilinearDirections::SSW, actual_image_width) +
                    get_face_normal(face_normal_vector_vec3, x, z, yli::triangulation::BilinearDirections::WSW, actual_image_width)));

        // 6. Compute the vertices between, `emplace_back` to `temp_normals`.
        // Number of adjacent faces: 4.

        for (z = 1; z < actual_image_height; z++)
        {
            for (x = 1; x < actual_image_width; x++)
            {
                temp_normals.emplace_back(glm::normalize(
                            s_face_normal(face_normal_vector_vec3, x, z, actual_image_width) +
                            w_face_normal(face_normal_vector_vec3, x, z, actual_image_width) +
                            n_face_normal(face_normal_vector_vec3, x, z, actual_image_width) +
                            e_face_normal(face_normal_vector_vec3, x, z, actual_image_width)));
            }
        }

        return true;
    }
}
