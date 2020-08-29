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

#include "gtest/gtest.h"
#include "code/ylikuutio/interpolation/bilinear_interpolation.hpp"

// Include standard headers
#include <stdint.h> // uint32_t etc.

TEST(a_1x1_terrain_must_be_interpolated_appropriately, no_change)
{
    uint32_t image_width = 1;
    uint32_t image_height = 1;
    float* input_vertex_data = new float[image_width * image_height];
    float* input_vertex_pointer = input_vertex_data;

    // 0x63e01fff = 01100011 11100000 00011111 11111111
    uint32_t IEEE_754_0x63e01fff_int = 0x63e01fff;
    float* IEEE_754_0x63e01fff_pointer = reinterpret_cast<float*>(&IEEE_754_0x63e01fff_int);
    *input_vertex_pointer = *IEEE_754_0x63e01fff_pointer;
    ASSERT_EQ(*input_vertex_pointer, *(reinterpret_cast<float*>(&IEEE_754_0x63e01fff_int)));
    ASSERT_TRUE(*input_vertex_pointer == 8.26875246809035309056e21);
    ASSERT_TRUE(*input_vertex_pointer > 8.26875246809035e21);
    ASSERT_TRUE(*input_vertex_pointer < 8.26875246809036e21);

    float* output_vertex_pointer = new float[image_width * image_height];

    float x1 = 0.0f;
    float z1 = 0.0f;
    float x2 = 0.0f;
    float z2 = 0.0f;
    float delta_x = 1.0f;
    float delta_z = 1.0f;

    ASSERT_TRUE(yli::interpolation::interpolate_bilinearly(input_vertex_data, output_vertex_pointer, image_width, image_height, x1, z1, x2, z2, delta_x, delta_z));

    ASSERT_TRUE(*output_vertex_pointer == 8.26875246809035309056e21);
    ASSERT_TRUE(*output_vertex_pointer > 8.26875246809035e21);
    ASSERT_TRUE(*output_vertex_pointer < 8.26875246809036e21);
}

TEST(a_2x2_terrain_must_be_interpolated_appropriately, no_change)
{
    uint32_t image_width = 2;
    uint32_t image_height = 2;
    float* input_vertex_data = new float[image_width * image_height];
    float* input_vertex_pointer = input_vertex_data;

    *input_vertex_pointer++ = 123.25f;
    *input_vertex_pointer++ = 234.25f;
    *input_vertex_pointer++ = 345.25f;
    *input_vertex_pointer++ = 456.25f;

    float* output_vertex_pointer = new float[image_width * image_height];

    float x1 = 0.0f;
    float z1 = 0.0f;
    float x2 = 1.0f;
    float z2 = 1.0f;
    float delta_x = 1.0f;
    float delta_z = 1.0f;

    ASSERT_TRUE(yli::interpolation::interpolate_bilinearly(input_vertex_data, output_vertex_pointer, image_width, image_height, x1, z1, x2, z2, delta_x, delta_z));
    ASSERT_TRUE(*output_vertex_pointer++ == 123.25f);
    ASSERT_TRUE(*output_vertex_pointer++ == 234.25f);
    ASSERT_TRUE(*output_vertex_pointer++ == 345.25f);
    ASSERT_TRUE(*output_vertex_pointer++ == 456.25f);
}

TEST(a_2x2_terrain_must_be_interpolated_appropriately, halfway_points)
{
    uint32_t image_width = 2;
    uint32_t image_height = 2;
    float* input_vertex_data = new float[image_width * image_height];
    float* input_vertex_pointer = input_vertex_data;

    *input_vertex_pointer++ = 123.25f;
    *input_vertex_pointer++ = 234.25f;
    *input_vertex_pointer++ = 345.25f;
    *input_vertex_pointer++ = 456.25f;

    uint32_t interpolated_image_width = 3;
    uint32_t interpolated_image_height = 3;
    float* output_vertex_pointer = new float[interpolated_image_width * interpolated_image_height];

    float x1 = 0.0f;
    float z1 = 0.0f;
    float x2 = 1.0f;
    float z2 = 1.0f;
    float delta_x = 0.5f;
    float delta_z = 0.5f;

    ASSERT_TRUE(yli::interpolation::interpolate_bilinearly(input_vertex_data, output_vertex_pointer, image_width, image_height, x1, z1, x2, z2, delta_x, delta_z));
    ASSERT_TRUE(*output_vertex_pointer++ == 123.25f);                                        // 0.0, 0.0
    ASSERT_TRUE(*output_vertex_pointer++ == (123.25f + 234.25f) / 2.0f);                     // 0.5, 0.0
    ASSERT_TRUE(*output_vertex_pointer++ == 234.25f);                                        // 1.0, 0.0
    ASSERT_TRUE(*output_vertex_pointer++ == (123.25f + 345.25f) / 2.0f);                     // 0.0, 0.5
    ASSERT_TRUE(*output_vertex_pointer++ == (123.25f + 234.25f + 345.25f + 456.25f) / 4.0f); // 0.5, 0.5
    ASSERT_TRUE(*output_vertex_pointer++ == (234.25f + 456.25f) / 2.0f);                     // 1.0, 0.5
    ASSERT_TRUE(*output_vertex_pointer++ == 345.25f);                                        // 0.0, 1.0
    ASSERT_TRUE(*output_vertex_pointer++ == (345.25f + 456.25f) / 2.0f);                     // 0.5, 1.0
    ASSERT_TRUE(*output_vertex_pointer++ == 456.25f);                                        // 1.0, 1.0
}

TEST(a_2x2_terrain_must_be_interpolated_appropriately, quarter_points)
{
    uint32_t image_width = 2;
    uint32_t image_height = 2;
    float* input_vertex_data = new float[image_width * image_height];
    float* input_vertex_pointer = input_vertex_data;

    *input_vertex_pointer++ = 123.25f;
    *input_vertex_pointer++ = 234.25f;
    *input_vertex_pointer++ = 345.25f;
    *input_vertex_pointer++ = 456.25f;

    uint32_t interpolated_image_width = 5;
    uint32_t interpolated_image_height = 5;
    float* output_vertex_pointer = new float[interpolated_image_width * interpolated_image_height];

    float x1 = 0.0f;
    float z1 = 0.0f;
    float x2 = 1.0f;
    float z2 = 1.0f;
    float delta_x = 0.25f;
    float delta_z = 0.25f;

    ASSERT_TRUE(yli::interpolation::interpolate_bilinearly(input_vertex_data, output_vertex_pointer, image_width, image_height, x1, z1, x2, z2, delta_x, delta_z));
    ASSERT_TRUE(*output_vertex_pointer++ == 123.25f);                                                                                   // 0.00, 0.00
    ASSERT_TRUE(*output_vertex_pointer++ == 0.75f * 123.25f + 0.25f * 234.25f);                                                         // 0.25, 0.00
    ASSERT_TRUE(*output_vertex_pointer++ == 0.5f * 123.25f + 0.5f * 234.25f);                                                           // 0.50, 0.00
    ASSERT_TRUE(*output_vertex_pointer++ == 0.25f * 123.25f + 0.75f * 234.25f);                                                         // 0.75, 0.00
    ASSERT_TRUE(*output_vertex_pointer++ == 234.25f);                                                                                   // 1.00, 0.00
    ASSERT_TRUE(*output_vertex_pointer++ == 0.75f * 123.25f + 0.25f * 345.25f);                                                         // 0.00, 0.25
    ASSERT_TRUE(*output_vertex_pointer++ == 0.75f * (0.75f * 123.25f + 0.25f * 234.25f) + 0.25f * (0.75f * 345.25f + 0.25f * 456.25f)); // 0.25, 0.25
    ASSERT_TRUE(*output_vertex_pointer++ == 0.75f * (0.5f * 123.25f + 0.5f * 234.25f) + 0.25f * (0.5f * 345.25f + 0.5f * 456.25f));     // 0.50, 0.25
    ASSERT_TRUE(*output_vertex_pointer++ == 0.75f * (0.25f * 123.25f + 0.75f * 234.25f) + 0.25f * (0.25f * 345.25f + 0.75f * 456.25f)); // 0.75, 0.25
    ASSERT_TRUE(*output_vertex_pointer++ == 0.75f * 234.25f + 0.25f * 456.25f);                                                         // 1.00, 0.25
    ASSERT_TRUE(*output_vertex_pointer++ == 0.5f * 123.25f + 0.5f * 345.25f);                                                           // 0.00, 0.50
    ASSERT_TRUE(*output_vertex_pointer++ == 0.5f * (0.75f * 123.25f + 0.25f * 234.25f) + 0.5f * (0.75f * 345.25f + 0.25f * 456.25f));   // 0.25, 0.50
    ASSERT_TRUE(*output_vertex_pointer++ == 0.5f * (0.5f * 123.25f + 0.5f * 234.25f) + 0.5f * (0.5f * 345.25f + 0.5f * 456.25f));       // 0.50, 0.50
    ASSERT_TRUE(*output_vertex_pointer++ == 0.5f * (0.25f * 123.25f + 0.75f * 234.25f) + 0.5f * (0.25f * 345.25f + 0.75f * 456.25f));   // 0.75, 0.50
    ASSERT_TRUE(*output_vertex_pointer++ == 0.5f * 234.25f + 0.5f * 456.25f);                                                           // 1.00, 0.50
    ASSERT_TRUE(*output_vertex_pointer++ == 0.25f * 123.25f + 0.75f * 345.25f);                                                         // 0.00, 0.75
    ASSERT_TRUE(*output_vertex_pointer++ == 0.25f * (0.75f * 123.25f + 0.25f * 234.25f) + 0.75f * (0.75f * 345.25f + 0.25f * 456.25f)); // 0.25, 0.75
    ASSERT_TRUE(*output_vertex_pointer++ == 0.25f * (0.5f * 123.25f + 0.5f * 234.25f) + 0.75f * (0.5f * 345.25f + 0.5f * 456.25f));     // 0.50, 0.75
    ASSERT_TRUE(*output_vertex_pointer++ == 0.25f * (0.25f * 123.25f + 0.75f * 234.25f) + 0.75f * (0.25f * 345.25f + 0.75f * 456.25f)); // 0.75, 0.75
    ASSERT_TRUE(*output_vertex_pointer++ == 0.25f * 234.25f + 0.75f * 456.25f);                                                         // 1.00, 0.75
    ASSERT_TRUE(*output_vertex_pointer++ == 345.25f);                                                                                   // 0.00, 1.00
    ASSERT_TRUE(*output_vertex_pointer++ == 0.75f * 345.25f + 0.25f * 456.25f);                                                         // 0.25, 1.00
    ASSERT_TRUE(*output_vertex_pointer++ == 0.5f * 345.25f + 0.5f * 456.25f);                                                           // 0.50, 1.00
    ASSERT_TRUE(*output_vertex_pointer++ == 0.25f * 345.25f + 0.75f * 456.25f);                                                         // 0.75, 1.00
    ASSERT_TRUE(*output_vertex_pointer++ == 456.25f);                                                                                   // 1.00, 1.00
}
