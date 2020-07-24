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

#ifndef __TRIANGULATION_TEMPLATES_HPP_INCLUDED
#define __TRIANGULATION_TEMPLATES_HPP_INCLUDED

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <vector>   // std::vector

namespace yli::triangulation
{
    template<class T1>
        T1 get_y(
                const T1* const vertex_data,
                const std::size_t x,
                const std::size_t z,
                const std::size_t image_width)
        {
            // This function returns the altitude value based on x & z coordinates.
            // This works only for a raw heightmap data (for a 2D array of altitudes).
            const T1* const vertex_pointer = vertex_data + z * image_width + x;
            return static_cast<T1>(*vertex_pointer);
        }

    // for bilinear interpolation.
    template<class T1>
        float southwest_y(const std::size_t x, const std::size_t z, const T1* const input_vertex_pointer, const std::size_t image_width, const std::size_t x_step, const std::size_t z_step)
        {
            return static_cast<float>(yli::triangulation::get_y(input_vertex_pointer, x - x_step, z - z_step, image_width));
        }
    template<class T1>
        float southeast_y(const std::size_t x, const std::size_t z, const T1* const input_vertex_pointer, const std::size_t image_width, const std::size_t x_step, const std::size_t z_step)
        {
            return static_cast<float>(yli::triangulation::get_y(input_vertex_pointer, x, z - z_step, image_width));
        }
    template<class T1>
        float northwest_y(const std::size_t x, const std::size_t z, const T1* const input_vertex_pointer, const std::size_t image_width, const std::size_t x_step, const std::size_t z_step)
        {
            return static_cast<float>(yli::triangulation::get_y(input_vertex_pointer, x - x_step, z, image_width));
        }
    template<class T1>
        float northeast_y(const std::size_t x, const std::size_t z, const T1* const input_vertex_pointer, const std::size_t image_width, const std::size_t x_step, const std::size_t z_step)
        {
            return static_cast<float>(yli::triangulation::get_y(input_vertex_pointer, x, z, image_width));
        }
    template<class T1>
        float center_y(const std::size_t x, const std::size_t z, const T1* const input_vertex_pointer, const std::size_t image_width, const std::size_t x_step, const std::size_t z_step)
        {
            return static_cast<float>(southwest_y(x, z, input_vertex_pointer, image_width, x_step, z_step) +
                    southeast_y(x, z, input_vertex_pointer, image_width, x_step, z_step) +
                    northwest_y(x, z, input_vertex_pointer, image_width, x_step, z_step) +
                    northeast_y(x, z, input_vertex_pointer, image_width, x_step, z_step)) / 4.0f;
        }

    template<class T1>
        bool compute_range(
                const T1* const input_vertex_pointer,
                const std::size_t image_width,
                const std::size_t image_height,
                const std::size_t x_step,
                const std::size_t z_step,
                float& min_y_value,
                float& max_y_value,
                float& divisor)
        {
            for (std::size_t z = 0; z < image_height; z += z_step)
            {
                for (std::size_t x = 0; x < image_width; x += x_step)
                {
                    const T1& vertex_height = input_vertex_pointer[image_width * z + x];

                    if (std::isnan(min_y_value) || vertex_height < min_y_value)
                    {
                        min_y_value = vertex_height;
                    }

                    if (std::isnan(max_y_value) || vertex_height > max_y_value)
                    {
                        max_y_value = vertex_height;
                    }
                }
            }

            divisor = max_y_value - min_y_value;

            if (std::isnan(divisor))
            {
                std::cerr << "ERROR: the value of `divisor` is `NAN`.\n";
                return false;
            }

            if (divisor == 0)
            {
                std::cerr << "ERROR: the value of `divisor` is 0.\n";
                return false;
            }

            return true;
        }

    template<class T1>
        bool define_vertices(
                const T1* const input_vertex_pointer,
                const std::size_t image_width,
                const std::size_t image_height,
                const std::size_t x_step,
                const std::size_t z_step,
                const bool use_real_texture_coordinates,
                std::vector<glm::vec3>& temp_vertices,
                std::vector<glm::vec2>& temp_uvs)
        {
            if (image_width < 2 || image_height < 2)
            {
                // Can not define vertices if image width < 2 or image height < 2.
                return false;
            }

            if (x_step <= 0 || z_step <= 0)
            {
                // Can not define vertices if x_step <= 0 or z_step <= 0.
                return false;
            }

            // Elevation maps are created using a mapping from [min_y_value, max_y_value] to [0, 1].
            // `min_y_value` & `max_y_value` are needed only for elevation maps.
            float min_y_value = NAN;
            float max_y_value = NAN;
            float divisor = NAN;

            if (!use_real_texture_coordinates)
            {
                bool result = yli::triangulation::compute_range(
                        input_vertex_pointer,
                        image_width,
                        image_height,
                        x_step,
                        z_step,
                        min_y_value,
                        max_y_value,
                        divisor);

                if (!result)
                {
                    return false;
                }
            }

            const std::size_t actual_image_width = image_width / x_step;
            const std::size_t actual_image_height = image_height / z_step;
            std::size_t number_of_vertices = actual_image_width * actual_image_height;
            temp_vertices.reserve(number_of_vertices);
            temp_uvs.reserve(number_of_vertices);

            // Define the temporary vertices in a double loop.
            std::size_t texture_y = 0;

            for (std::size_t z = 0; z < image_height; z += z_step)
            {
                std::size_t texture_x = 0;

                for (std::size_t x = 0; x < image_width; x += x_step)
                {
                    // current x,z coordinates).
                    float y = static_cast<float>(yli::triangulation::get_y(input_vertex_pointer, x, z, image_width));

                    // This corresponds to "v": specify one vertex.
                    glm::vec3 vertex;
                    vertex.x = static_cast<float>(x);
                    vertex.y = static_cast<float>(y);
                    vertex.z = static_cast<float>(z);
                    temp_vertices.emplace_back(vertex);

                    // This corresponds to "vt": specify texture coordinates of one vertex.
                    glm::vec2 uv;

                    if (use_real_texture_coordinates)
                    {
                        uv.x = round(static_cast<float>(texture_x));
                        uv.y = round(static_cast<float>(texture_y));
                    }
                    else
                    {
                        uv.x = static_cast<float>(y - min_y_value) / divisor;
                        uv.y = 0.0f;
                    }

                    temp_uvs.emplace_back(uv);

                    // `uv.x` is repeated 0, 1, 0, 1 ... when moving eastward.
                    // this causes the texture be mirrored horizontally for every other quad.
                    texture_x ^= 1;
                }

                // `uv.y` is repeated 0, 1, 0, 1 ... when moving southward.
                // this causes the texture be mirrored vertically for every other quad.
                texture_y ^= 1;
            }

            return true;
        }

    template<class T1>
        bool interpolate_and_define_vertices_using_bilinear_interpolation(
                const T1* const input_vertex_pointer,
                const std::size_t image_width,
                const std::size_t image_height,
                const std::size_t x_step,
                const std::size_t z_step,
                const bool use_real_texture_coordinates,
                std::vector<glm::vec3>& temp_vertices,
                std::vector<glm::vec2>& temp_uvs)
        {
            std::cout << "Interpolating center vertices.\n";

            if (image_width < 2 || image_height < 2)
            {
                // Can not interpolate center vertices if image width < 2 or image height < 2.
                return false;
            }

            if (x_step <= 0 || z_step <= 0)
            {
                // Can not interpolate center vertices if x_step <= 0 or z_step <= 0.
                return false;
            }

            // Elevation maps are created using a mapping from [min_y_value, max_y_value] to [0, 1].
            // `min_y_value` & `max_y_value` are needed only for elevation maps.
            float min_y_value = NAN;
            float max_y_value = NAN;
            float divisor = NAN;

            if (!use_real_texture_coordinates)
            {
                bool result = yli::triangulation::compute_range(
                        input_vertex_pointer,
                        image_width,
                        image_height,
                        x_step,
                        z_step,
                        min_y_value,
                        max_y_value,
                        divisor);

                if (!result)
                {
                    return false;
                }
            }

            // Then, define the faces in a double loop.
            // Begin from index `z_step`.
            for (std::size_t z = z_step; z < image_height; z += z_step)
            {
                // Begin from index `x_step`.
                for (std::size_t x = x_step; x < image_width; x += x_step)
                {
                    // This corresponds to "f": specify a face (but here we specify 2 faces instead!).

                    // Interpolate y coordinate (altitude).
                    const float y = center_y(x, z, input_vertex_pointer, image_width, x_step, z_step);

                    // Create a new vertex using bilinear interpolation.
                    // This corresponds to "v": specify one vertex.
                    glm::vec3 vertex;
                    vertex.x = static_cast<float>(x) - 0.5f * x_step;
                    vertex.y = static_cast<float>(y);
                    vertex.z = static_cast<float>(z) - 0.5f * z_step;
                    temp_vertices.emplace_back(vertex);

                    // This corresponds to "vt": specify texture coordinates of one vertex.
                    glm::vec2 uv;

                    if (use_real_texture_coordinates)
                    {
                        uv.x = 0.5f;
                        uv.y = 0.5f;
                    }
                    else
                    {
                        uv.x = static_cast<float>(y - min_y_value) / divisor;
                        uv.y = 0.0f;
                    }

                    temp_uvs.emplace_back(uv);
                }
            }

            return true;
        }
}

#endif
