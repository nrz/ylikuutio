// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2026 Antti Nuortimo.
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
#include "code/ylikuutio/interpolation/bilinear_interpolation_struct.hpp"

// Include standard headers
#include <memory> // std::shared_ptr
#include <vector> // std::vector

TEST(a_1x1_terrain_must_be_interpolated_bilinearly_to_1x1_appropriately, no_change)
{
    yli::interpolation::BilinearInterpolationStruct bilinear_interpolation_struct;
    bilinear_interpolation_struct.input_image_width = 1;
    bilinear_interpolation_struct.input_image_height = 1;
    bilinear_interpolation_struct.output_image_width = 1;
    bilinear_interpolation_struct.output_image_height = 1;

    float* input_vertex_data = new float[bilinear_interpolation_struct.input_image_width * bilinear_interpolation_struct.input_image_height];
    input_vertex_data[0] = 123.25f;

    using OutputVector = std::shared_ptr<std::vector<float>>;
    OutputVector output_vector = yli::interpolation::interpolate_bilinearly(input_vertex_data, bilinear_interpolation_struct);
    ASSERT_NE(output_vector, nullptr);
    ASSERT_EQ(output_vector->size(), 1);
    ASSERT_EQ((*output_vector)[0], 123.25f);
}

TEST(a_2x2_terrain_must_be_interpolated_bilinearly_to_2x2_appropriately, no_change)
{
    yli::interpolation::BilinearInterpolationStruct bilinear_interpolation_struct;
    bilinear_interpolation_struct.input_image_width = 2;
    bilinear_interpolation_struct.input_image_height = 2;
    bilinear_interpolation_struct.output_image_width = 2;
    bilinear_interpolation_struct.output_image_height = 2;
    float* input_vertex_data = new float[bilinear_interpolation_struct.input_image_width * bilinear_interpolation_struct.input_image_height];
    float* input_vertex_pointer = input_vertex_data;

    *input_vertex_pointer++ = 123.25f;
    *input_vertex_pointer++ = 234.25f;
    *input_vertex_pointer++ = 345.25f;
    *input_vertex_pointer++ = 456.25f;

    using OutputVector = std::shared_ptr<std::vector<float>>;
    OutputVector output_vector = yli::interpolation::interpolate_bilinearly(input_vertex_data, bilinear_interpolation_struct);
    ASSERT_NE(output_vector, nullptr);
    ASSERT_EQ(output_vector->size(), 4);
    ASSERT_EQ((*output_vector)[0], 123.25f);
    ASSERT_EQ((*output_vector)[1], 234.25f);
    ASSERT_EQ((*output_vector)[2], 345.25f);
    ASSERT_EQ((*output_vector)[3], 456.25f);
}

TEST(a_2x1_terrain_must_be_interpolated_bilinearly_to_1x1_appropriately, interpolation)
{
    yli::interpolation::BilinearInterpolationStruct bilinear_interpolation_struct;
    bilinear_interpolation_struct.input_image_width = 2;
    bilinear_interpolation_struct.input_image_height = 1;
    bilinear_interpolation_struct.output_image_width = 1;
    bilinear_interpolation_struct.output_image_height = 1;
    float* input_vertex_data = new float[bilinear_interpolation_struct.input_image_width * bilinear_interpolation_struct.input_image_height];
    float* input_vertex_pointer = input_vertex_data;

    *input_vertex_pointer++ = 123.25f;
    *input_vertex_pointer++ = 234.25f;

    using OutputVector = std::shared_ptr<std::vector<float>>;
    OutputVector output_vector = yli::interpolation::interpolate_bilinearly(input_vertex_data, bilinear_interpolation_struct);
    ASSERT_NE(output_vector, nullptr);
    ASSERT_EQ(output_vector->size(), 1);

    //                                          sampling coordinates (x, z):
    ASSERT_EQ((*output_vector)[0], 178.75f); // (1.0, 0.5)
}

TEST(a_1x2_terrain_must_be_interpolated_bilinearly_to_1x1_appropriately, interpolation)
{
    yli::interpolation::BilinearInterpolationStruct bilinear_interpolation_struct;
    bilinear_interpolation_struct.input_image_width = 1;
    bilinear_interpolation_struct.input_image_height = 2;
    bilinear_interpolation_struct.output_image_width = 1;
    bilinear_interpolation_struct.output_image_height = 1;
    float* input_vertex_data = new float[bilinear_interpolation_struct.input_image_width * bilinear_interpolation_struct.input_image_height];
    float* input_vertex_pointer = input_vertex_data;

    *input_vertex_pointer++ = 123.25f;
    *input_vertex_pointer++ = 234.25f;

    using OutputVector = std::shared_ptr<std::vector<float>>;
    OutputVector output_vector = yli::interpolation::interpolate_bilinearly(input_vertex_data, bilinear_interpolation_struct);
    ASSERT_NE(output_vector, nullptr);
    ASSERT_EQ(output_vector->size(), 1);

    //                                          sampling coordinates (x, z):
    ASSERT_EQ((*output_vector)[0], 178.75f); // (0.5, 1.0)
}

TEST(a_2x2_terrain_must_be_interpolated_bilinearly_to_1x1_appropriately, interpolation)
{
    yli::interpolation::BilinearInterpolationStruct bilinear_interpolation_struct;
    bilinear_interpolation_struct.input_image_width = 2;
    bilinear_interpolation_struct.input_image_height = 2;
    bilinear_interpolation_struct.output_image_width = 1;
    bilinear_interpolation_struct.output_image_height = 1;
    float* input_vertex_data = new float[bilinear_interpolation_struct.input_image_width * bilinear_interpolation_struct.input_image_height];
    float* input_vertex_pointer = input_vertex_data;

    *input_vertex_pointer++ = 123.25f;
    *input_vertex_pointer++ = 234.25f;
    *input_vertex_pointer++ = 345.25f;
    *input_vertex_pointer++ = 456.25f;

    using OutputVector = std::shared_ptr<std::vector<float>>;
    OutputVector output_vector = yli::interpolation::interpolate_bilinearly(input_vertex_data, bilinear_interpolation_struct);
    ASSERT_NE(output_vector, nullptr);
    ASSERT_EQ(output_vector->size(), 1);

    //                                          sampling coordinates (x, z):
    ASSERT_EQ((*output_vector)[0], 289.75f); // (1.0, 1.0)
}

TEST(a_3x3_terrain_must_be_interpolated_bilinearly_to_2x2_appropriately, interpolation)
{
    yli::interpolation::BilinearInterpolationStruct bilinear_interpolation_struct;
    bilinear_interpolation_struct.input_image_width = 3;
    bilinear_interpolation_struct.input_image_height = 3;
    bilinear_interpolation_struct.output_image_width = 2;
    bilinear_interpolation_struct.output_image_height = 2;
    float* input_vertex_data = new float[bilinear_interpolation_struct.input_image_width * bilinear_interpolation_struct.input_image_height];
    float* input_vertex_pointer = input_vertex_data;

    *input_vertex_pointer++ = 12.25f;
    *input_vertex_pointer++ = 23.25f;
    *input_vertex_pointer++ = 34.25f;

    *input_vertex_pointer++ = 45.25f;
    *input_vertex_pointer++ = 56.25f;
    *input_vertex_pointer++ = 67.25f;

    *input_vertex_pointer++ = 78.25f;
    *input_vertex_pointer++ = 89.25f;
    *input_vertex_pointer++ = 100.25f;

    using OutputVector = std::shared_ptr<std::vector<float>>;
    OutputVector output_vector = yli::interpolation::interpolate_bilinearly(input_vertex_data, bilinear_interpolation_struct);
    ASSERT_NE(output_vector, nullptr);
    ASSERT_EQ(output_vector->size(), 4);

    //                                         sampling coordinates (x, z):
    ASSERT_EQ((*output_vector)[0], 23.25f); // (0.75, 0.75)
    ASSERT_EQ((*output_vector)[1], 39.75f); // (2.25, 0.75)

    ASSERT_EQ((*output_vector)[2], 72.75f); // (0.75, 2.25)
    ASSERT_EQ((*output_vector)[3], 89.25f); // (2.25, 2.25)
}

TEST(a_4x4_terrain_must_be_interpolated_bilinearly_to_2x2_appropriately, interpolation)
{
    yli::interpolation::BilinearInterpolationStruct bilinear_interpolation_struct;
    bilinear_interpolation_struct.input_image_width = 4;
    bilinear_interpolation_struct.input_image_height = 4;
    bilinear_interpolation_struct.output_image_width = 2;
    bilinear_interpolation_struct.output_image_height = 2;
    float* input_vertex_data = new float[bilinear_interpolation_struct.input_image_width * bilinear_interpolation_struct.input_image_height];
    float* input_vertex_pointer = input_vertex_data;

    *input_vertex_pointer++ = 16.25f;
    *input_vertex_pointer++ = 2.25f;
    *input_vertex_pointer++ = 3.25f;
    *input_vertex_pointer++ = 13.25f;

    *input_vertex_pointer++ = 5.25f;
    *input_vertex_pointer++ = 11.25f;
    *input_vertex_pointer++ = 10.25f;
    *input_vertex_pointer++ = 8.25f;

    *input_vertex_pointer++ = 9.25f;
    *input_vertex_pointer++ = 7.25f;
    *input_vertex_pointer++ = 6.25f;
    *input_vertex_pointer++ = 12.25f;

    *input_vertex_pointer++ = 4.25f;
    *input_vertex_pointer++ = 14.25f;
    *input_vertex_pointer++ = 15.25f;
    *input_vertex_pointer++ = 1.25f;

    using OutputVector = std::shared_ptr<std::vector<float>>;
    OutputVector output_vector = yli::interpolation::interpolate_bilinearly(input_vertex_data, bilinear_interpolation_struct);
    ASSERT_NE(output_vector, nullptr);
    ASSERT_EQ(output_vector->size(), 4);

    //                                        sampling coordinates (x, z):
    ASSERT_EQ((*output_vector)[0], 8.75f); // (1.0, 1.0)
    ASSERT_EQ((*output_vector)[1], 8.75f); // (3.0, 1.0)

    ASSERT_EQ((*output_vector)[2], 8.75f); // (1.0, 3.0)
    ASSERT_EQ((*output_vector)[3], 8.75f); // (3.0, 3.0)
}

TEST(a_5x5_terrain_must_be_interpolated_bilinearly_to_2x2_appropriately, interpolation)
{
    yli::interpolation::BilinearInterpolationStruct bilinear_interpolation_struct;
    bilinear_interpolation_struct.input_image_width = 5;
    bilinear_interpolation_struct.input_image_height = 5;
    bilinear_interpolation_struct.output_image_width = 2;
    bilinear_interpolation_struct.output_image_height = 2;
    float* input_vertex_data = new float[bilinear_interpolation_struct.input_image_width * bilinear_interpolation_struct.input_image_height];
    float* input_vertex_pointer = input_vertex_data;

    *input_vertex_pointer++ = 17.25f;
    *input_vertex_pointer++ = 24.25f;
    *input_vertex_pointer++ = 1.25f;
    *input_vertex_pointer++ = 8.25f;
    *input_vertex_pointer++ = 15.25f;

    *input_vertex_pointer++ = 23.25f;
    *input_vertex_pointer++ = 5.25f;
    *input_vertex_pointer++ = 7.25f;
    *input_vertex_pointer++ = 14.25f;
    *input_vertex_pointer++ = 16.25f;

    *input_vertex_pointer++ = 4.25f;
    *input_vertex_pointer++ = 6.25f;
    *input_vertex_pointer++ = 13.25f;
    *input_vertex_pointer++ = 20.25f;
    *input_vertex_pointer++ = 22.25f;

    *input_vertex_pointer++ = 10.25f;
    *input_vertex_pointer++ = 12.25f;
    *input_vertex_pointer++ = 19.25f;
    *input_vertex_pointer++ = 21.25f;
    *input_vertex_pointer++ = 3.25f;

    *input_vertex_pointer++ = 11.25f;
    *input_vertex_pointer++ = 18.25f;
    *input_vertex_pointer++ = 25.25f;
    *input_vertex_pointer++ = 2.25f;
    *input_vertex_pointer++ = 9.25f;

    using OutputVector = std::shared_ptr<std::vector<float>>;
    OutputVector output_vector = yli::interpolation::interpolate_bilinearly(input_vertex_data, bilinear_interpolation_struct);
    ASSERT_NE(output_vector, nullptr);
    ASSERT_EQ(output_vector->size(), 4);

    //                                           sampling coordinates (x, z):
    ASSERT_EQ((*output_vector)[0], 12.9375f); // (1.25, 1.25)
    ASSERT_EQ((*output_vector)[1], 13.5625f); // (3.75, 1.25)

    ASSERT_EQ((*output_vector)[2], 12.9375f); // (1.25, 3.75)
    ASSERT_EQ((*output_vector)[3], 13.5625f); // (3.75, 3.75)
}

TEST(a_5x5_terrain_must_be_interpolated_bilinearly_to_4x4_appropriately, interpolation)
{
    yli::interpolation::BilinearInterpolationStruct bilinear_interpolation_struct;
    bilinear_interpolation_struct.input_image_width = 5;
    bilinear_interpolation_struct.input_image_height = 5;
    bilinear_interpolation_struct.output_image_width = 4;
    bilinear_interpolation_struct.output_image_height = 4;
    float* input_vertex_data = new float[bilinear_interpolation_struct.input_image_width * bilinear_interpolation_struct.input_image_height];
    float* input_vertex_pointer = input_vertex_data;

    *input_vertex_pointer++ = 17.25f;
    *input_vertex_pointer++ = 24.25f;
    *input_vertex_pointer++ = 1.25f;
    *input_vertex_pointer++ = 8.25f;
    *input_vertex_pointer++ = 15.25f;

    *input_vertex_pointer++ = 23.25f;
    *input_vertex_pointer++ = 5.25f;
    *input_vertex_pointer++ = 7.25f;
    *input_vertex_pointer++ = 14.25f;
    *input_vertex_pointer++ = 16.25f;

    *input_vertex_pointer++ = 4.25f;
    *input_vertex_pointer++ = 6.25f;
    *input_vertex_pointer++ = 13.25f;
    *input_vertex_pointer++ = 20.25f;
    *input_vertex_pointer++ = 22.25f;

    *input_vertex_pointer++ = 10.25f;
    *input_vertex_pointer++ = 12.25f;
    *input_vertex_pointer++ = 19.25f;
    *input_vertex_pointer++ = 21.25f;
    *input_vertex_pointer++ = 3.25f;

    *input_vertex_pointer++ = 11.25f;
    *input_vertex_pointer++ = 18.25f;
    *input_vertex_pointer++ = 25.25f;
    *input_vertex_pointer++ = 2.25f;
    *input_vertex_pointer++ = 9.25f;

    using OutputVector = std::shared_ptr<std::vector<float>>;
    OutputVector output_vector = yli::interpolation::interpolate_bilinearly(input_vertex_data, bilinear_interpolation_struct);
    ASSERT_NE(output_vector, nullptr);
    ASSERT_EQ(output_vector->size(), 16);

    //                                              sampling coordinates (x, z):
    ASSERT_EQ((*output_vector)[0], 18.484375f);  // (0.625, 0.625)
    ASSERT_EQ((*output_vector)[1], 14.421875f);  // (1.875, 0.625)
    ASSERT_EQ((*output_vector)[2], 6.375f);      // (3.125, 0.625)
    ASSERT_EQ((*output_vector)[3], 14.578125);   // (4.375, 0.625)

    ASSERT_EQ((*output_vector)[4], 14.8125f);    // (0.625, 1.875)
    ASSERT_EQ((*output_vector)[5], 7.078125f);   // (1.875, 1.875)
    ASSERT_EQ((*output_vector)[6], 13.875f);     // (3.125, 1.875)
    ASSERT_EQ((*output_vector)[7], 18.25f);      // (4.375, 1.875)

    ASSERT_EQ((*output_vector)[8], 8.25f);       // (0.625, 3.125)
    ASSERT_EQ((*output_vector)[9], 12.625f);     // (1.875, 3.125)
    ASSERT_EQ((*output_vector)[10], 19.421875f); // (3.125, 3.125)
    ASSERT_EQ((*output_vector)[11], 11.6875f);   // (4.375, 3.125)

    ASSERT_EQ((*output_vector)[12], 11.921875f); // (0.625, 4.375)
    ASSERT_EQ((*output_vector)[13], 20.125f);    // (1.875, 4.375)
    ASSERT_EQ((*output_vector)[14], 12.078125f); // (3.125, 4.375)
    ASSERT_EQ((*output_vector)[15], 8.015625f) ; // (4.375, 4.375)
}

TEST(a_6x6_terrain_must_be_interpolated_bilinearly_to_3x3_appropriately, interpolation)
{
    yli::interpolation::BilinearInterpolationStruct bilinear_interpolation_struct;
    bilinear_interpolation_struct.input_image_width = 6;
    bilinear_interpolation_struct.input_image_height = 6;
    bilinear_interpolation_struct.output_image_width = 3;
    bilinear_interpolation_struct.output_image_height = 3;
    float* input_vertex_data = new float[bilinear_interpolation_struct.input_image_width * bilinear_interpolation_struct.input_image_height];
    float* input_vertex_pointer = input_vertex_data;

    *input_vertex_pointer++ = 35.25f;
    *input_vertex_pointer++ = 1.25f;
    *input_vertex_pointer++ = 6.25f;
    *input_vertex_pointer++ = 26.25f;
    *input_vertex_pointer++ = 19.25f;
    *input_vertex_pointer++ = 24.25f;

    *input_vertex_pointer++ = 3.25f;
    *input_vertex_pointer++ = 32.25f;
    *input_vertex_pointer++ = 7.25f;
    *input_vertex_pointer++ = 21.25f;
    *input_vertex_pointer++ = 23.25f;
    *input_vertex_pointer++ = 25.25f;

    *input_vertex_pointer++ = 31.25f;
    *input_vertex_pointer++ = 9.25f;
    *input_vertex_pointer++ = 2.25f;
    *input_vertex_pointer++ = 22.25f;
    *input_vertex_pointer++ = 27.25f;
    *input_vertex_pointer++ = 20.25f;

    *input_vertex_pointer++ = 8.25f;
    *input_vertex_pointer++ = 28.25f;
    *input_vertex_pointer++ = 33.25f;
    *input_vertex_pointer++ = 17.25f;
    *input_vertex_pointer++ = 10.25f;
    *input_vertex_pointer++ = 15.25f;

    *input_vertex_pointer++ = 30.25f;
    *input_vertex_pointer++ = 5.25f;
    *input_vertex_pointer++ = 34.25f;
    *input_vertex_pointer++ = 12.25f;
    *input_vertex_pointer++ = 14.25f;
    *input_vertex_pointer++ = 16.25f;

    *input_vertex_pointer++ = 4.25f;
    *input_vertex_pointer++ = 36.25f;
    *input_vertex_pointer++ = 29.25f;
    *input_vertex_pointer++ = 13.25f;
    *input_vertex_pointer++ = 18.25f;
    *input_vertex_pointer++ = 11.25f;

    using OutputVector = std::shared_ptr<std::vector<float>>;
    OutputVector output_vector = yli::interpolation::interpolate_bilinearly(input_vertex_data, bilinear_interpolation_struct);
    ASSERT_NE(output_vector, nullptr);
    ASSERT_EQ(output_vector->size(), 9);

    //                                         sampling coordinates (x, z):
    ASSERT_EQ((*output_vector)[0], 18.0f);  // (1.0, 1.0)
    ASSERT_EQ((*output_vector)[1], 15.25f); // (3.0, 1.0)
    ASSERT_EQ((*output_vector)[2], 23.0f);  // (5.0, 1.0)

    ASSERT_EQ((*output_vector)[3], 19.25f); // (1.0, 3.0)
    ASSERT_EQ((*output_vector)[4], 18.75f); // (3.0, 3.0)
    ASSERT_EQ((*output_vector)[5], 18.25f); // (5.0, 3.0)

    ASSERT_EQ((*output_vector)[6], 19.0f);  // (1.0, 5.0)
    ASSERT_EQ((*output_vector)[7], 22.25f); // (3.0, 5.0)
    ASSERT_EQ((*output_vector)[8], 15.0f);  // (5.0, 5.0)
}
