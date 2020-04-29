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

#ifndef __BILINEAR_INTERPOLATION2D_HPP_INCLUDED
#define __BILINEAR_INTERPOLATION2D_HPP_INCLUDED

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <math.h>   // ceil, floor etc.

namespace yli::interpolation
{
    template<class T1>
        bool interpolate_bilinearly2D(
                T1* input_vertex_pointer,
                float* output_vertex_pointer,
                uint32_t image_width,
                uint32_t image_height,
                float start_x,
                float start_z,
                float end_x,
                float end_z,
                float delta_x,
                float delta_z)
        {
            if (start_x < 0.0f || start_x > static_cast<float>(image_width) ||
                    end_x < 0.0f || end_x > static_cast<float>(image_width) ||
                    start_z < 0.0f || start_z > static_cast<float>(image_height) ||
                    end_z < 0.0f || end_z > static_cast<float>(image_height))
            {
                // invalid value in some input variable.
                return false;
            }

            // If `start_x` > `end_x` or if `start_z` > `end_z`, then no output will be produced.
            if (start_x > end_x || start_z > end_z)
            {
                return false;
            }

            // `start_x`, `end_x`, `start_z`, and `end_z` are all inclusive.
            // With inclusive coordinates it's easier to eg. keep the original data.

            for (float z = start_z; z <= end_z; z += delta_z)
            {
                const float floor_z = floor(z);
                const float ceil_z = ceil(z);
                const float rel_z = z - floor_z; // 0 <= rel_z <= 1
                const float inv_rel_z = 1.0f - rel_z;
                const uint32_t z0 = static_cast<uint32_t>(floor_z);
                const uint32_t z1 = static_cast<uint32_t>(ceil_z);

                // Interpolate along z axis.
                for (float x = start_x; x <= end_x; x += delta_x)
                {
                    // https://en.wikipedia.org/wiki/Bilinear_interpolation#Unit_Square
                    const float floor_x = floor(x);
                    const float ceil_x = ceil(x);
                    const float rel_x = x - floor_x; // 0 <= rel_x <= 1
                    const float inv_rel_x = 1.0f - rel_x;
                    const uint32_t x0 = static_cast<uint32_t>(floor_x);
                    const uint32_t x1 = static_cast<uint32_t>(ceil_x);

                    const float data_0_0 = static_cast<float>(*(input_vertex_pointer + image_width * z0 + x0));
                    const float data_0_1 = static_cast<float>(*(input_vertex_pointer + image_width * z1 + x0));
                    const float data_1_0 = static_cast<float>(*(input_vertex_pointer + image_width * z0 + x1));
                    const float data_1_1 = static_cast<float>(*(input_vertex_pointer + image_width * z1 + x1));

                    const float value = inv_rel_x * inv_rel_z * data_0_0 + rel_x * inv_rel_z * data_1_0 + inv_rel_x * rel_z * data_0_1 + rel_x * rel_z * data_1_1;
                    *output_vertex_pointer++ = value;
                }
            }

            return true;
        }
}

#endif
