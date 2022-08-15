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

#include "gtest/gtest.h"
#include "code/ylikuutio/geometry/spherical_terrain_struct.hpp"
#include "code/ylikuutio/triangulation/triangulate_quads_struct.hpp"
#include "code/ylikuutio/triangulation/quad_triangulation.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <cstddef>  // std::size_t
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

TEST(a_2x2_terrain_must_be_triangulated_appropriately, bilinear_interpolation)
{
    // *---*
    // |\ /|
    // | * |
    // |/ \|
    // *---*
    // bilinear interpolation.
    const std::size_t image_width = 2;
    const std::size_t image_height = 2;
    const std::size_t terrain_size = image_width * image_height;

    uint32_t* const vertex_data = new uint32_t[terrain_size];
    ASSERT_NE(vertex_data, nullptr);
    uint32_t* vertex_pointer = vertex_data;
    // x, z: height (y).
    const std::size_t southwest_height = 1;
    const std::size_t southeast_height = 2;
    const std::size_t northwest_height = 4;
    const std::size_t northeast_height = 8;
    const float center_x = 0.5f;
    const float center_z = 0.5f;

    // 0, 0: 1.
    *vertex_pointer++ = southwest_height;
    // 1, 0: 2.
    *vertex_pointer++ = southeast_height;
    // 0, 1: 4.
    *vertex_pointer++ = northwest_height;
    // 1, 1: 8.
    *vertex_pointer++ = northeast_height;

    std::vector<glm::vec3> vertices; // vertices of the object.
    std::vector<glm::vec2> UVs;      // UVs of the object.
    std::vector<glm::vec3> normals;  // normals of the object.

    yli::triangulation::TriangulateQuadsStruct triangulate_quads_struct;
    triangulate_quads_struct.image_width = image_width;
    triangulate_quads_struct.image_height = image_height;
    triangulate_quads_struct.sphere_radius = NAN;

    triangulate_quads_struct.triangulation_type = "bilinear_interpolation";

    const bool is_success = yli::triangulation::triangulate_quads(vertex_data, triangulate_quads_struct, vertices, UVs, normals);
    ASSERT_TRUE(is_success);
    ASSERT_EQ(vertices.size(), 12);
    ASSERT_EQ(UVs.size(), 12);
    ASSERT_EQ(normals.size(), 12);

    // 1st vertex is the center vertex of the 1st triangle.
    ASSERT_EQ(vertices[0].x, center_x);
    ASSERT_EQ(vertices[0].z, center_z);
    ASSERT_EQ(vertices[0].y, static_cast<float>(southwest_height + southeast_height + northwest_height + northeast_height) / 4.0f);

    // 2nd vertex is the southeast vertex of the 1st triangle.
    ASSERT_EQ(vertices[1].x, 1.0f);
    ASSERT_EQ(vertices[1].z, 0.0f);
    ASSERT_EQ(vertices[1].y, southeast_height);

    // 3rd vertex is the southwest vertex of the 1st triangle.
    ASSERT_EQ(vertices[2].x, 0.0f);
    ASSERT_EQ(vertices[2].z, 0.0f);
    ASSERT_EQ(vertices[2].y, southwest_height);

    // 4th vertex is the center vertex of the 2nd triangle.
    ASSERT_EQ(vertices[3].x, center_x);
    ASSERT_EQ(vertices[3].z, center_z);
    ASSERT_EQ(vertices[3].y, static_cast<float>(southwest_height + southeast_height + northwest_height + northeast_height) / 4.0f);

    // 5th vertex is the southwest vertex of the 2nd triangle.
    ASSERT_EQ(vertices[4].x, 0.0f);
    ASSERT_EQ(vertices[4].z, 0.0f);
    ASSERT_EQ(vertices[4].y, southwest_height);

    // 6th vertex is the northwest vertex of the 2nd triangle.
    ASSERT_EQ(vertices[5].x, 0.0f);
    ASSERT_EQ(vertices[5].z, 1.0f);
    ASSERT_EQ(vertices[5].y, northwest_height);

    // 7th vertex is the center vertex of the 3rd triangle.
    ASSERT_EQ(vertices[6].x, center_x);
    ASSERT_EQ(vertices[6].z, center_z);
    ASSERT_EQ(vertices[6].y, static_cast<float>(southwest_height + southeast_height + northwest_height + northeast_height) / 4.0f);

    // 8th vertex is the northwest vertex of the 3rd triangle.
    ASSERT_EQ(vertices[7].x, 0.0f);
    ASSERT_EQ(vertices[7].z, 1.0f);
    ASSERT_EQ(vertices[7].y, northwest_height);

    // 9th vertex is the northeast vertex of the 3rd triangle.
    ASSERT_EQ(vertices[8].x, 1.0f);
    ASSERT_EQ(vertices[8].z, 1.0f);
    ASSERT_EQ(vertices[8].y, northeast_height);

    // 10th vertex is the center vertex of the 4th triangle.
    ASSERT_EQ(vertices[9].x, center_x);
    ASSERT_EQ(vertices[9].z, center_z);
    ASSERT_EQ(vertices[9].y, static_cast<float>(southwest_height + southeast_height + northwest_height + northeast_height) / 4);

    // 11th vertex is the northeast vertex of the 4th triangle.
    ASSERT_EQ(vertices[10].x, 1.0f);
    ASSERT_EQ(vertices[10].z, 1.0f);
    ASSERT_EQ(vertices[10].y, northeast_height);

    // 12th vertex is the southeast vertex of the 4th triangle.
    ASSERT_EQ(vertices[11].x, 1.0f);
    ASSERT_EQ(vertices[11].z, 0.0f);
    ASSERT_EQ(vertices[11].y, southeast_height);

    delete vertex_data;
}

TEST(a_2x2_terrain_must_be_triangulated_appropriately, southeast_northwest_edges)
{
    // *---*
    // |\  |
    // | \ |
    // |  \|
    // *---*
    // southeast northwest edges.
    const std::size_t image_width = 2;
    const std::size_t image_height = 2;
    const std::size_t terrain_size = image_width * image_height;

    uint32_t* const vertex_data = new uint32_t[terrain_size];
    ASSERT_NE(vertex_data, nullptr);
    uint32_t* vertex_pointer = vertex_data;
    // x, z: height (y).
    const std::size_t southwest_height = 1;
    const std::size_t southeast_height = 2;
    const std::size_t northwest_height = 4;
    const std::size_t northeast_height = 8;

    // 0, 0: 1.
    *vertex_pointer++ = southwest_height;
    // 1, 0: 2.
    *vertex_pointer++ = southeast_height;
    // 0, 1: 4.
    *vertex_pointer++ = northwest_height;
    // 1, 1: 8.
    *vertex_pointer++ = northeast_height;

    std::vector<glm::vec3> vertices; // vertices of the object.
    std::vector<glm::vec2> UVs;      // UVs of the object.
    std::vector<glm::vec3> normals;  // normals of the object.

    yli::triangulation::TriangulateQuadsStruct triangulate_quads_struct;
    triangulate_quads_struct.image_width = image_width;
    triangulate_quads_struct.image_height = image_height;
    triangulate_quads_struct.sphere_radius = NAN;
    triangulate_quads_struct.spherical_terrain_struct = yli::geometry::SphericalTerrainStruct(); // not used, but is needed in the function call.

    triangulate_quads_struct.triangulation_type = "southeast_northwest_edges";

    const bool is_success = yli::triangulation::triangulate_quads(vertex_data, triangulate_quads_struct, vertices, UVs, normals);
    ASSERT_TRUE(is_success);
    ASSERT_EQ(vertices.size(), 6);
    ASSERT_EQ(UVs.size(), 6);
    ASSERT_EQ(normals.size(), 6);

    // 1st vertex is the southwest vertex of the 1st triangle.
    ASSERT_EQ(vertices[0].x, 0.0f);
    ASSERT_EQ(vertices[0].z, 0.0f);
    ASSERT_EQ(vertices[0].y, southwest_height);

    // 2nd vertex is the northwest vertex of the 1st triangle.
    ASSERT_EQ(vertices[1].x, 0.0f);
    ASSERT_EQ(vertices[1].z, 1.0f);
    ASSERT_EQ(vertices[1].y, northwest_height);

    // 3rd vertex is the southeast vertex of the 1st triangle.
    ASSERT_EQ(vertices[2].x, 1.0f);
    ASSERT_EQ(vertices[2].z, 0.0f);
    ASSERT_EQ(vertices[2].y, southeast_height);

    // 4th vertex is the northeast vertex of the 2nd triangle.
    ASSERT_EQ(vertices[3].x, 1.0f);
    ASSERT_EQ(vertices[3].z, 1.0f);
    ASSERT_EQ(vertices[3].y, northeast_height);

    // 5th vertex is the southeast vertex of the 2nd triangle.
    ASSERT_EQ(vertices[4].x, 1.0f);
    ASSERT_EQ(vertices[4].z, 0.0f);
    ASSERT_EQ(vertices[4].y, southeast_height);

    // 6th vertex is the northwest vertex of the 2nd triangle.
    ASSERT_EQ(vertices[5].x, 0.0f);
    ASSERT_EQ(vertices[5].z, 1.0f);
    ASSERT_EQ(vertices[5].y, northwest_height);

    delete vertex_data;
}

TEST(a_2x2_terrain_must_be_triangulated_appropriately, southwest_northeast_edges)
{
    // *---*
    // |  /|
    // | / |
    // |/  |
    // *---*
    // southwest northeast edges.
    const std::size_t image_width = 2;
    const std::size_t image_height = 2;
    const std::size_t terrain_size = image_width * image_height;

    uint32_t* const vertex_data = new uint32_t[terrain_size];
    ASSERT_NE(vertex_data, nullptr);
    uint32_t* vertex_pointer = vertex_data;
    // x, z: height (y).
    const std::size_t southwest_height = 1;
    const std::size_t southeast_height = 2;
    const std::size_t northwest_height = 4;
    const std::size_t northeast_height = 8;

    // 0, 0: 1.
    *vertex_pointer++ = southwest_height;
    // 1, 0: 2.
    *vertex_pointer++ = southeast_height;
    // 0, 1: 4.
    *vertex_pointer++ = northwest_height;
    // 1, 1: 8.
    *vertex_pointer++ = northeast_height;

    std::vector<glm::vec3> vertices; // vertices of the object.
    std::vector<glm::vec2> UVs;      // UVs of the object.
    std::vector<glm::vec3> normals;  // normals of the object.

    yli::triangulation::TriangulateQuadsStruct triangulate_quads_struct;
    triangulate_quads_struct.image_width = image_width;
    triangulate_quads_struct.image_height = image_height;
    triangulate_quads_struct.sphere_radius = NAN;
    triangulate_quads_struct.spherical_terrain_struct = yli::geometry::SphericalTerrainStruct(); // not used, but is needed in the function call.

    triangulate_quads_struct.triangulation_type = "southwest_northeast_edges";

    const bool is_success = yli::triangulation::triangulate_quads(vertex_data, triangulate_quads_struct, vertices, UVs, normals);
    ASSERT_TRUE(is_success);
    ASSERT_EQ(vertices.size(), 6);
    ASSERT_EQ(UVs.size(), 6);
    ASSERT_EQ(normals.size(), 6);

    // 1st vertex is the southeast vertex of the 1st triangle.
    ASSERT_EQ(vertices[0].x, 1.0f);
    ASSERT_EQ(vertices[0].z, 0.0f);
    ASSERT_EQ(vertices[0].y, southeast_height);

    // 2nd vertex is the southwest vertex of the 1st triangle.
    ASSERT_EQ(vertices[1].x, 0.0f);
    ASSERT_EQ(vertices[1].z, 0.0f);
    ASSERT_EQ(vertices[1].y, southwest_height);

    // 3rd vertex is the northeast vertex of the 1st triangle.
    ASSERT_EQ(vertices[2].x, 1.0f);
    ASSERT_EQ(vertices[2].z, 1.0f);
    ASSERT_EQ(vertices[2].y, northeast_height);

    // 4th vertex is the northwest vertex of the 2nd triangle.
    ASSERT_EQ(vertices[3].x, 0.0f);
    ASSERT_EQ(vertices[3].z, 1.0f);
    ASSERT_EQ(vertices[3].y, northwest_height);

    // 5th vertex is the northeast vertex of the 2nd triangle.
    ASSERT_EQ(vertices[4].x, 1.0f);
    ASSERT_EQ(vertices[4].z, 1.0f);
    ASSERT_EQ(vertices[4].y, northeast_height);

    // 6th vertex is the southwest vertex of the 2nd triangle.
    ASSERT_EQ(vertices[5].x, 0.0f);
    ASSERT_EQ(vertices[5].z, 0.0f);
    ASSERT_EQ(vertices[5].y, southwest_height);

    delete vertex_data;
}

TEST(a_3x3_terrain_must_be_triangulated_appropriately, southeast_northwest_edges)
{
    // *---*---*
    // |\  |\  |
    // | \ | \ |
    // |  \|  \|
    // *---*---*
    // |\  |\  |
    // | \ | \ |
    // |  \|  \|
    // *---*---*
    // southeast northwest edges.
    const std::size_t image_width = 3;
    const std::size_t image_height = 3;
    const std::size_t terrain_size = image_width * image_height;

    uint32_t* const vertex_data = new uint32_t[terrain_size];
    ASSERT_NE(vertex_data, nullptr);
    uint32_t* vertex_pointer = vertex_data;
    // x, z: height (y).
    const std::size_t x0_z0_height = 10;
    const std::size_t x1_z0_height = 20;
    const std::size_t x2_z0_height = 30;
    const std::size_t x0_z1_height = 40;
    const std::size_t x1_z1_height = 50;
    const std::size_t x2_z1_height = 60;
    const std::size_t x0_z2_height = 70;
    const std::size_t x1_z2_height = 80;
    const std::size_t x2_z2_height = 90;

    // 0, 0: 10.
    *vertex_pointer++ = x0_z0_height;
    // 1, 0: 20.
    *vertex_pointer++ = x1_z0_height;
    // 2, 0: 30.
    *vertex_pointer++ = x2_z0_height;
    // 0, 1: 40.
    *vertex_pointer++ = x0_z1_height;
    // 1, 1: 50.
    *vertex_pointer++ = x1_z1_height;
    // 2, 1: 60.
    *vertex_pointer++ = x2_z1_height;
    // 0, 2: 70.
    *vertex_pointer++ = x0_z2_height;
    // 1, 2: 80.
    *vertex_pointer++ = x1_z2_height;
    // 2, 2: 90.
    *vertex_pointer++ = x2_z2_height;

    std::vector<glm::vec3> vertices; // vertices of the object.
    std::vector<glm::vec2> UVs;      // UVs of the object.
    std::vector<glm::vec3> normals;  // normals of the object.

    yli::triangulation::TriangulateQuadsStruct triangulate_quads_struct;
    triangulate_quads_struct.image_width = image_width;
    triangulate_quads_struct.image_height = image_height;
    triangulate_quads_struct.sphere_radius = NAN;
    triangulate_quads_struct.spherical_terrain_struct = yli::geometry::SphericalTerrainStruct(); // not used, but is needed in the function call.

    triangulate_quads_struct.triangulation_type = "southeast_northwest_edges";

    const bool is_success = yli::triangulation::triangulate_quads(vertex_data, triangulate_quads_struct, vertices, UVs, normals);
    ASSERT_TRUE(is_success);
    ASSERT_EQ(vertices.size(), 24);
    ASSERT_EQ(UVs.size(), 24);
    ASSERT_EQ(normals.size(), 24);

    // 1st vertex is the southwest vertex of the 1st triangle.
    ASSERT_EQ(vertices[0].x, 0.0f);
    ASSERT_EQ(vertices[0].z, 0.0f);
    ASSERT_EQ(vertices[0].y, x0_z0_height);

    // 2nd vertex is the northwest vertex of the 1st triangle.
    ASSERT_EQ(vertices[1].x, 0.0f);
    ASSERT_EQ(vertices[1].z, 1.0f);
    ASSERT_EQ(vertices[1].y, x0_z1_height);

    // 3rd vertex is the southeast vertex of the 1st triangle.
    ASSERT_EQ(vertices[2].x, 1.0f);
    ASSERT_EQ(vertices[2].z, 0.0f);
    ASSERT_EQ(vertices[2].y, x1_z0_height);

    // 4th vertex is the northeast vertex of the 2nd triangle.
    ASSERT_EQ(vertices[3].x, 1.0f);
    ASSERT_EQ(vertices[3].z, 1.0f);
    ASSERT_EQ(vertices[3].y, x1_z1_height);

    // 5th vertex is the southeast vertex of the 2nd triangle.
    ASSERT_EQ(vertices[4].x, 1.0f);
    ASSERT_EQ(vertices[4].z, 0.0f);
    ASSERT_EQ(vertices[4].y, x1_z0_height);

    // 6th vertex is the northwest vertex of the 2nd triangle.
    ASSERT_EQ(vertices[5].x, 0.0f);
    ASSERT_EQ(vertices[5].z, 1.0f);
    ASSERT_EQ(vertices[5].y, x0_z1_height);

    // 7th vertex is the southwest vertex of the 3rd triangle.
    ASSERT_EQ(vertices[6].x, 1.0f);
    ASSERT_EQ(vertices[6].z, 0.0f);
    ASSERT_EQ(vertices[6].y, x1_z0_height);

    // 8th vertex is the northwest vertex of the 3rd triangle.
    ASSERT_EQ(vertices[7].x, 1.0f);
    ASSERT_EQ(vertices[7].z, 1.0f);
    ASSERT_EQ(vertices[7].y, x1_z1_height);

    // 9th vertex is the southeast vertex of the 3rd triangle.
    ASSERT_EQ(vertices[8].x, 2.0f);
    ASSERT_EQ(vertices[8].z, 0.0f);
    ASSERT_EQ(vertices[8].y, x2_z0_height);

    // 10th vertex is the northeast vertex of the 4th triangle.
    ASSERT_EQ(vertices[9].x, 2.0f);
    ASSERT_EQ(vertices[9].z, 1.0f);
    ASSERT_EQ(vertices[9].y, x2_z1_height);

    // 11th vertex is the southeast vertex of the 4th triangle.
    ASSERT_EQ(vertices[10].x, 2.0f);
    ASSERT_EQ(vertices[10].z, 0.0f);
    ASSERT_EQ(vertices[10].y, x2_z0_height);

    // 12th vertex is the northwest vertex of the 4th triangle.
    ASSERT_EQ(vertices[11].x, 1.0f);
    ASSERT_EQ(vertices[11].z, 1.0f);
    ASSERT_EQ(vertices[11].y, x1_z1_height);

    // 13th vertex is the southwest vertex of the 5th triangle.
    ASSERT_EQ(vertices[12].x, 0.0f);
    ASSERT_EQ(vertices[12].z, 1.0f);
    ASSERT_EQ(vertices[12].y, x0_z1_height);

    // 14th vertex is the northwest vertex of the 5th triangle.
    ASSERT_EQ(vertices[13].x, 0.0f);
    ASSERT_EQ(vertices[13].z, 2.0f);
    ASSERT_EQ(vertices[13].y, x0_z2_height);

    // 15th vertex is the southeast vertex of the 5th triangle.
    ASSERT_EQ(vertices[14].x, 1.0f);
    ASSERT_EQ(vertices[14].z, 1.0f);
    ASSERT_EQ(vertices[14].y, x1_z1_height);

    // 16th vertex is the northeast vertex of the 6th triangle.
    ASSERT_EQ(vertices[15].x, 1.0f);
    ASSERT_EQ(vertices[15].z, 2.0f);
    ASSERT_EQ(vertices[15].y, x1_z2_height);

    // 17th vertex is the southeast vertex of the 6th triangle.
    ASSERT_EQ(vertices[16].x, 1.0f);
    ASSERT_EQ(vertices[16].z, 1.0f);
    ASSERT_EQ(vertices[16].y, x1_z1_height);

    // 18th vertex is the northwest vertex of the 6th triangle.
    ASSERT_EQ(vertices[17].x, 0.0f);
    ASSERT_EQ(vertices[17].z, 2.0f);
    ASSERT_EQ(vertices[17].y, x0_z2_height);

    // 19th vertex is the southwest vertex of the 7th triangle.
    ASSERT_EQ(vertices[18].x, 1.0f);
    ASSERT_EQ(vertices[18].z, 1.0f);
    ASSERT_EQ(vertices[18].y, x1_z1_height);

    // 20th vertex is the northwest vertex of the 7th triangle.
    ASSERT_EQ(vertices[19].x, 1.0f);
    ASSERT_EQ(vertices[19].z, 2.0f);
    ASSERT_EQ(vertices[19].y, x1_z2_height);

    // 21st vertex is the southeast vertex of the 7th triangle.
    ASSERT_EQ(vertices[20].x, 2.0f);
    ASSERT_EQ(vertices[20].z, 1.0f);
    ASSERT_EQ(vertices[20].y, x2_z1_height);

    // 22nd vertex is the northeast vertex of the 8th triangle.
    ASSERT_EQ(vertices[21].x, 2.0f);
    ASSERT_EQ(vertices[21].z, 2.0f);
    ASSERT_EQ(vertices[21].y, x2_z2_height);

    // 23th vertex is the southeast vertex of the 8th triangle.
    ASSERT_EQ(vertices[22].x, 2.0f);
    ASSERT_EQ(vertices[22].z, 1.0f);
    ASSERT_EQ(vertices[22].y, x2_z1_height);

    // 24th vertex is the northwest vertex of the 8th triangle.
    ASSERT_EQ(vertices[23].x, 1.0f);
    ASSERT_EQ(vertices[23].z, 2.0f);
    ASSERT_EQ(vertices[23].y, x1_z2_height);

    delete vertex_data;
}
