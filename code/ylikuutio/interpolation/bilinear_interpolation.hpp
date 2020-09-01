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

#ifndef __YLIKUUTIO_INTERPOLATION_BILINEAR_INTERPOLATION_HPP_INCLUDED
#define __YLIKUUTIO_INTERPOLATION_BILINEAR_INTERPOLATION_HPP_INCLUDED

#include "bilinear_interpolation_struct.hpp"

// Include standard headers
#include <cmath>    // NAN, std::ceil, std::floor, std::isnan
#include <cstddef>  // std::ptrdiff_t, std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <limits>   // std::numeric_limits
#include <memory>   // std::make_shared, std::shared_ptr
#include <vector>   // std::vector

namespace yli::interpolation
{
    template<class T1>
        float sample2D(
                const T1* source_image,
                const float image_width,
                const float image_height,
                const float x,
                const float z)
        {
            // (x,z) coordinates.
            // First texel extends from (0, 0) to (1, 1).
            // Sampling is always done from the center of the texel.

            const float floor_x = std::floor(x);
            const float floor_z = std::floor(z);

            const float weight_x0 = (x - floor_x >= 0.5f ? 1.0f - (x - floor_x - 0.5f) : 0.5f - (x - floor_x)); // 0 <= weight_x0 <= 1
            const float weight_x1 = 1.0f - weight_x0;                                                           // 0 <= weight_x1 <= 1

            const float weight_z0 = (z - floor_z >= 0.5f ? 1.0f - (z - floor_z - 0.5f) : 0.5f - (z - floor_z)); // 0 <= weight_z0 <= 1
            const float weight_z1 = 1.0f - weight_z0;                                                           // 0 <= weight_z1 <= 1

            const std::size_t x0 = (x - floor_x >= 0.5f ? static_cast<std::size_t>(floor_x) : static_cast<std::size_t>(floor_x - 1));
            const std::size_t x1 = (x - floor_x <= 0.5f ? static_cast<std::size_t>(floor_x) : static_cast<std::size_t>(floor_x + 1));

            const std::size_t z0 = (z - floor_z >= 0.5f ? static_cast<std::size_t>(floor_z) : static_cast<std::size_t>(floor_z - 1));
            const std::size_t z1 = (z - floor_z <= 0.5f ? static_cast<std::size_t>(floor_z) : static_cast<std::size_t>(floor_z + 1));

            const std::ptrdiff_t data_sw_ptrdiff_t = static_cast<ptrdiff_t>(image_width * z0 + x0); // southwest.
            const std::ptrdiff_t data_se_ptrdiff_t = static_cast<ptrdiff_t>(image_width * z0 + x1); // southeast.
            const std::ptrdiff_t data_nw_ptrdiff_t = static_cast<ptrdiff_t>(image_width * z1 + x0); // northwest.
            const std::ptrdiff_t data_ne_ptrdiff_t = static_cast<ptrdiff_t>(image_width * z1 + x1); // northeast.
            const float data_sw = static_cast<float>(*(source_image + data_sw_ptrdiff_t));
            const float data_se = static_cast<float>(*(source_image + data_se_ptrdiff_t));
            const float data_nw = static_cast<float>(*(source_image + data_nw_ptrdiff_t));
            const float data_ne = static_cast<float>(*(source_image + data_ne_ptrdiff_t));

            // Interpolate.
            return weight_x0 * weight_z0 * data_sw + weight_x1 * weight_z0 * data_se + weight_x0 * weight_z1 * data_nw + weight_x1 * weight_z1 * data_ne;
        }

    template<class T1>
        std::shared_ptr<std::vector<float>> interpolate_bilinearly(
                const T1* source_image,
                const yli::interpolation::BilinearInterpolationStruct& bilinear_interpolation_struct)
        {
            const std::size_t& input_image_width = bilinear_interpolation_struct.input_image_width;

            if (input_image_width == 0)
            {
                std::cerr << "ERROR: `yli::interpolation::interpolate_bilinearly2D`: the value of `input_image_width` is 0.\n";
                return nullptr;
            }

            const std::size_t& input_image_height = bilinear_interpolation_struct.input_image_height;

            if (input_image_height == 0)
            {
                std::cerr << "ERROR: `yli::interpolation::interpolate_bilinearly2D`: the value of `input_image_height` is 0.\n";
                return nullptr;
            }

            const std::size_t& output_image_width = bilinear_interpolation_struct.output_image_width;

            if (output_image_width == 0)
            {
                std::cerr << "ERROR: `yli::interpolation::interpolate_bilinearly2D`: the value of `output_image_width` is 0.\n";
                return nullptr;
            }

            const std::size_t& output_image_height = bilinear_interpolation_struct.output_image_height;

            if (output_image_height == 0)
            {
                std::cerr << "ERROR: `yli::interpolation::interpolate_bilinearly2D`: the value of `output_image_height` is 0.\n";
                return nullptr;
            }

            if (output_image_width > input_image_width || output_image_height > input_image_height)
            {
                std::cerr << "ERROR: `yli::interpolation::interpolate_bilinearly2D`: enlarging is not currently supported!\n";
                return nullptr;
            }

            const std::size_t n_output_vertices = output_image_width * output_image_height;
            const std::ptrdiff_t n_output_vertices_ptrdiff_t = static_cast<std::ptrdiff_t>(n_output_vertices);

            std::shared_ptr<std::vector<float>> output_vector = std::make_shared<std::vector<float>>();
            output_vector->reserve(n_output_vertices);

            const float delta_x = static_cast<float>(input_image_width) / static_cast<float>(output_image_width);
            const float delta_z = static_cast<float>(input_image_height) / static_cast<float>(output_image_height);

            float z = delta_z / 2.0f;

            for (std::size_t z_index = 0; z_index < output_image_height; z_index++, z += delta_z)
            {
                float x = delta_x / 2.0f;

                for (std::size_t x_index = 0; x_index < output_image_width; x_index++, x += delta_x)
                {
                    const float value = yli::interpolation::sample2D(source_image, input_image_width, input_image_height, x, z);

                    output_vector->emplace_back(value);
                }
            }

            return output_vector;
        }
}

#endif
