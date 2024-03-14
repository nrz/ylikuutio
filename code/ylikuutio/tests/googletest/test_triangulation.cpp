// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2024 Antti Nuortimo.
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
#include "code/ylikuutio/triangulation/face_normals.hpp"
#include "code/ylikuutio/triangulation/triangulation_templates.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <vector>   // std::vector

TEST(vertices_must_be_defined_and_interpolated_appropriately, a_3x3_terrain)
{
    const std::size_t image_width = 3;
    const std::size_t image_height = 3;
    const bool use_real_texture_coordinates = true;

    float* const input_vertex_data = new float[image_width * image_height];
    ASSERT_NE(input_vertex_data, nullptr);
    float* input_vertex_pointer = input_vertex_data;

    // Fill input vertex data with values.
    // |  32 64 128 |
    // |   4  8  16 |
    // |   0  1   2 |
    *input_vertex_pointer++ = 0.0f;
    *input_vertex_pointer++ = 1.0f;
    *input_vertex_pointer++ = 2.0f;
    *input_vertex_pointer++ = 4.0f;
    *input_vertex_pointer++ = 8.0f;
    *input_vertex_pointer++ = 16.0f;
    *input_vertex_pointer++ = 32.0f;
    *input_vertex_pointer++ = 64.0f;
    *input_vertex_pointer++ = 128.0f;

    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;

    const std::size_t x_step = 1;
    const std::size_t z_step = 1;

    yli::triangulation::define_vertices(
            input_vertex_data,
            image_width,
            image_height,
            x_step,
            z_step,
            use_real_texture_coordinates,
            temp_vertices,
            temp_uvs);

    ASSERT_TRUE(yli::triangulation::interpolate_and_define_vertices_using_bilinear_interpolation(
                input_vertex_data,
                image_width,
                image_height,
                x_step,
                z_step,
                use_real_texture_coordinates,
                temp_vertices,
                temp_uvs));

    // Predefined vertices.

    // x = 0, z = 0, y = 0.
    ASSERT_EQ(temp_vertices[0].x, 0.0f);
    ASSERT_EQ(temp_vertices[0].z, 0.0f);
    ASSERT_EQ(temp_vertices[0].y, 0.0f);
    ASSERT_EQ(temp_uvs[0].x, 0.0f);
    ASSERT_EQ(temp_uvs[0].y, 0.0f);

    // x = 1, z = 0, y = 1.
    ASSERT_EQ(temp_vertices[1].x, 1.0f);
    ASSERT_EQ(temp_vertices[1].z, 0.0f);
    ASSERT_EQ(temp_vertices[1].y, 1.0f);
    ASSERT_EQ(temp_uvs[1].x, 1.0f);
    ASSERT_EQ(temp_uvs[1].y, 0.0f);

    // x = 2, z = 0, y = 2.
    ASSERT_EQ(temp_vertices[2].x, 2.0f);
    ASSERT_EQ(temp_vertices[2].z, 0.0f);
    ASSERT_EQ(temp_vertices[2].y, 2.0f);
    ASSERT_EQ(temp_uvs[2].x, 0.0f);
    ASSERT_EQ(temp_uvs[2].y, 0.0f);

    // x = 0, z = 1, y = 4.
    ASSERT_EQ(temp_vertices[3].x, 0.0f);
    ASSERT_EQ(temp_vertices[3].z, 1.0f);
    ASSERT_EQ(temp_vertices[3].y, 4.0f);
    ASSERT_EQ(temp_uvs[3].x, 0.0f);
    ASSERT_EQ(temp_uvs[3].y, 1.0f);

    // x = 1, z = 1, y = 8.
    ASSERT_EQ(temp_vertices[4].x, 1.0f);
    ASSERT_EQ(temp_vertices[4].z, 1.0f);
    ASSERT_EQ(temp_vertices[4].y, 8.0f);
    ASSERT_EQ(temp_uvs[4].x, 1.0f);
    ASSERT_EQ(temp_uvs[4].y, 1.0f);

    // x = 2, z = 1, y = 16.
    ASSERT_EQ(temp_vertices[5].x, 2.0f);
    ASSERT_EQ(temp_vertices[5].z, 1.0f);
    ASSERT_EQ(temp_vertices[5].y, 16.0f);
    ASSERT_EQ(temp_uvs[5].x, 0.0f);
    ASSERT_EQ(temp_uvs[5].y, 1.0f);

    // x = 0, z = 2, y = 32.
    ASSERT_EQ(temp_vertices[6].x, 0.0f);
    ASSERT_EQ(temp_vertices[6].z, 2.0f);
    ASSERT_EQ(temp_vertices[6].y, 32.0f);
    ASSERT_EQ(temp_uvs[6].x, 0.0f);
    ASSERT_EQ(temp_uvs[6].y, 0.0f);

    // x = 1, z = 2, y = 64.
    ASSERT_EQ(temp_vertices[7].x, 1.0f);
    ASSERT_EQ(temp_vertices[7].z, 2.0f);
    ASSERT_EQ(temp_vertices[7].y, 64.0f);
    ASSERT_EQ(temp_uvs[7].x, 1.0f);
    ASSERT_EQ(temp_uvs[7].y, 0.0f);

    // x = 2, z = 2, y = 128.
    ASSERT_EQ(temp_vertices[8].x, 2.0f);
    ASSERT_EQ(temp_vertices[8].z, 2.0f);
    ASSERT_EQ(temp_vertices[8].y, 128.0f);
    ASSERT_EQ(temp_uvs[8].x, 0.0f);
    ASSERT_EQ(temp_uvs[8].y, 0.0f);

    // Interpolated vertices.

    // x = 0.5, z = 0.5, y = 3.25.
    ASSERT_EQ(temp_vertices[9].x, 0.5f);
    ASSERT_EQ(temp_vertices[9].z, 0.5f);
    ASSERT_EQ(temp_vertices[9].y, 3.25f);
    ASSERT_EQ(temp_uvs[9].x, 0.5f);
    ASSERT_EQ(temp_uvs[9].y, 0.5f);

    // x = 1.5, z = 0.5, y = 6.75.
    ASSERT_EQ(temp_vertices[10].x, 1.5f);
    ASSERT_EQ(temp_vertices[10].z, 0.5f);
    ASSERT_EQ(temp_vertices[10].y, 6.75f);
    ASSERT_EQ(temp_uvs[10].x, 0.5f);
    ASSERT_EQ(temp_uvs[10].y, 0.5f);

    // x = 0.5, z = 1.5, y = 27.
    ASSERT_EQ(temp_vertices[11].x, 0.5f);
    ASSERT_EQ(temp_vertices[11].z, 1.5f);
    ASSERT_EQ(temp_vertices[11].y, 27.0f);
    ASSERT_EQ(temp_uvs[11].x, 0.5f);
    ASSERT_EQ(temp_uvs[11].y, 0.5f);

    // x = 1.5, z = 1.5, y = 54.
    ASSERT_EQ(temp_vertices[12].x, 1.5f);
    ASSERT_EQ(temp_vertices[12].z, 1.5f);
    ASSERT_EQ(temp_vertices[12].y, 54.0f);
    ASSERT_EQ(temp_uvs[12].x, 0.5f);
    ASSERT_EQ(temp_uvs[12].y, 0.5f);

    std::vector<glm::vec3> face_normal_vector_vec3;

    ASSERT_TRUE(yli::triangulation::compute_face_normals(
                temp_vertices,
                face_normal_vector_vec3,
                image_width,
                image_height));

    // Predefined vertices.
    const glm::vec3 i0_x0_z0 = glm::vec3(0.0f, 0.0f, 0.0f);
    const glm::vec3 i1_x1_z0 = glm::vec3(1.0f, 1.0f, 0.0f);
    const glm::vec3 i2_x2_z0 = glm::vec3(2.0f, 2.0f, 0.0f);
    const glm::vec3 i3_x0_z1 = glm::vec3(0.0f, 4.0f, 1.0f);
    const glm::vec3 i4_x1_z1 = glm::vec3(1.0f, 8.0f, 1.0f);
    const glm::vec3 i5_x2_z1 = glm::vec3(2.0f, 16.0f, 1.0f);
    const glm::vec3 i6_x0_z2 = glm::vec3(0.0f, 32.0f, 2.0f);
    const glm::vec3 i7_x1_z2 = glm::vec3(1.0f, 64.0f, 2.0f);
    const glm::vec3 i8_x2_z2 = glm::vec3(2.0f, 128.0f, 2.0f);

    // Interpolated vertices.
    const glm::vec3 i9_x0_5_z0_5 = glm::vec3(0.5f, 3.25f, 0.5f);
    const glm::vec3 i10_x1_5_z0_5 = glm::vec3(1.5f, 6.75f, 0.5f);
    const glm::vec3 i11_x0_5_z1_5 = glm::vec3(0.5f, 27.0f, 1.5f);
    const glm::vec3 i12_x1_5_z1_5 = glm::vec3(1.5f, 54.0f, 1.5f);

    // Predefined vertices.
    ASSERT_TRUE(glm::all(glm::equal(temp_vertices[0], i0_x0_z0)));
    ASSERT_TRUE(glm::all(glm::equal(temp_vertices[1], i1_x1_z0)));
    ASSERT_TRUE(glm::all(glm::equal(temp_vertices[2], i2_x2_z0)));
    ASSERT_TRUE(glm::all(glm::equal(temp_vertices[3], i3_x0_z1)));
    ASSERT_TRUE(glm::all(glm::equal(temp_vertices[4], i4_x1_z1)));
    ASSERT_TRUE(glm::all(glm::equal(temp_vertices[5], i5_x2_z1)));
    ASSERT_TRUE(glm::all(glm::equal(temp_vertices[6], i6_x0_z2)));
    ASSERT_TRUE(glm::all(glm::equal(temp_vertices[7], i7_x1_z2)));
    ASSERT_TRUE(glm::all(glm::equal(temp_vertices[8], i8_x2_z2)));

    // Interpolated vertices.
    ASSERT_TRUE(glm::all(glm::equal(temp_vertices[9], i9_x0_5_z0_5)));
    ASSERT_TRUE(glm::all(glm::equal(temp_vertices[10], i10_x1_5_z0_5)));
    ASSERT_TRUE(glm::all(glm::equal(temp_vertices[11], i11_x0_5_z1_5)));
    ASSERT_TRUE(glm::all(glm::equal(temp_vertices[12], i12_x1_5_z1_5)));

    // Face normals.
    ASSERT_TRUE(glm::all(glm::equal(face_normal_vector_vec3[0], glm::normalize(glm::cross(i1_x1_z0 - i9_x0_5_z0_5, i0_x0_z0 - i9_x0_5_z0_5)))));
    ASSERT_TRUE(glm::all(glm::equal(face_normal_vector_vec3[1], glm::normalize(glm::cross(i0_x0_z0 - i9_x0_5_z0_5, i3_x0_z1 - i9_x0_5_z0_5)))));
    ASSERT_TRUE(glm::all(glm::equal(face_normal_vector_vec3[2], glm::normalize(glm::cross(i3_x0_z1 - i9_x0_5_z0_5, i4_x1_z1 - i9_x0_5_z0_5)))));
    ASSERT_TRUE(glm::all(glm::equal(face_normal_vector_vec3[3], glm::normalize(glm::cross(i4_x1_z1 - i9_x0_5_z0_5, i1_x1_z0 - i9_x0_5_z0_5)))));
    ASSERT_TRUE(glm::all(glm::equal(face_normal_vector_vec3[4], glm::normalize(glm::cross(i2_x2_z0 - i10_x1_5_z0_5, i1_x1_z0 - i10_x1_5_z0_5)))));
    ASSERT_TRUE(glm::all(glm::equal(face_normal_vector_vec3[5], glm::normalize(glm::cross(i1_x1_z0 - i10_x1_5_z0_5, i4_x1_z1 - i10_x1_5_z0_5)))));
    ASSERT_TRUE(glm::all(glm::equal(face_normal_vector_vec3[6], glm::normalize(glm::cross(i4_x1_z1 - i10_x1_5_z0_5, i5_x2_z1 - i10_x1_5_z0_5)))));
    ASSERT_TRUE(glm::all(glm::equal(face_normal_vector_vec3[7], glm::normalize(glm::cross(i5_x2_z1 - i10_x1_5_z0_5, i2_x2_z0 - i10_x1_5_z0_5)))));
    ASSERT_TRUE(glm::all(glm::equal(face_normal_vector_vec3[8], glm::normalize(glm::cross(i4_x1_z1 - i11_x0_5_z1_5, i3_x0_z1 - i11_x0_5_z1_5)))));
    ASSERT_TRUE(glm::all(glm::equal(face_normal_vector_vec3[9], glm::normalize(glm::cross(i3_x0_z1 - i11_x0_5_z1_5, i6_x0_z2 - i11_x0_5_z1_5)))));
    ASSERT_TRUE(glm::all(glm::equal(face_normal_vector_vec3[10], glm::normalize(glm::cross(i6_x0_z2 - i11_x0_5_z1_5, i7_x1_z2 - i11_x0_5_z1_5)))));
    ASSERT_TRUE(glm::all(glm::equal(face_normal_vector_vec3[11], glm::normalize(glm::cross(i7_x1_z2 - i11_x0_5_z1_5, i4_x1_z1 - i11_x0_5_z1_5)))));
}
