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
#include "code/ylikuutio/load/ascii_grid_heightmap_loader.hpp"
#include "code/ylikuutio/load/heightmap_loader_struct.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

TEST(an_ascii_grid_must_be_defined_and_interpolated_appropriately, test_3x3_0_1_2_4_8_16_32_64_128_256_x_step_1_y_step_1)
{
    yli::load::HeightmapLoaderStruct heightmap_loader_struct;
    heightmap_loader_struct.filename = "test_3x3_0_1_2_4_8_16_32_64_128.asc";
    heightmap_loader_struct.x_step = 1;
    heightmap_loader_struct.y_step = 1;
    heightmap_loader_struct.use_real_texture_coordinates = true;

    std::vector<glm::vec3> vertices;         // vertices of the object.
    std::vector<glm::vec2> uvs;              // UVs of the object.
    std::vector<glm::vec3> normals;          // normals of the object.
    uint32_t image_width;
    uint32_t image_height;

    bool model_loading_result = yli::load::load_ascii_grid_terrain(
            heightmap_loader_struct,
            vertices,
            uvs,
            normals,
            image_width,
            image_height);

    ASSERT_TRUE(model_loading_result);
    ASSERT_EQ(vertices.size(), 16 * 3);
    ASSERT_EQ(uvs.size(), 16 * 3);
    ASSERT_EQ(normals.size(), 16 * 3);

    //  +-------+-------+
    //  |\ 10  /|\ 14  /|
    //  | \   / | \   / |
    //  |  \ /  |  \ /  |
    //  | 9 x 11|13 x 15|
    //  |  / \  |  / \  |
    //  | /   \ | /   \ |
    //  |/  8  \|/ 12  \|
    //  +-------+-------+
    //  |\  2  /|\  6  /|
    //  | \   / | \   / |
    //  |  \ /  |  \ /  |
    //  |1  x  3|5  x  7|
    //  |  / \  |  / \  |
    //  | /   \ | /   \ |
    //  |/  0  \|/  4  \|
    //  +-------+-------+

    ASSERT_EQ(vertices[0].z, 3.25f); // central vertex of 1st triangle.
    ASSERT_EQ(vertices[1].z, 1.00f); // southeast vertex.
    ASSERT_EQ(vertices[2].z, 0.00f); // southwest vertex.

    ASSERT_EQ(vertices[3].z, 3.25f); // central vertex of 2nd triangle.
    ASSERT_EQ(vertices[4].z, 0.00f); // southwest vertex.
    ASSERT_EQ(vertices[5].z, 4.00f); // northwest vertex.

    ASSERT_EQ(vertices[6].z, 3.25f); // central vertex of 3rd triangle.
    ASSERT_EQ(vertices[7].z, 4.00f); // northwest vertex.
    ASSERT_EQ(vertices[8].z, 8.00f); // northeast vertex.

    ASSERT_EQ(vertices[9].z, 3.25f);  // central vertex of 4th triangle.
    ASSERT_EQ(vertices[10].z, 8.00f); // northeast vertex.
    ASSERT_EQ(vertices[11].z, 1.00f); // southeast vertex.

    ASSERT_EQ(vertices[12].z, 6.75f); // central vertex of 5th triangle.
    ASSERT_EQ(vertices[13].z, 2.00f); // southeast vertex.
    ASSERT_EQ(vertices[14].z, 1.00f); // southwest vertex.

    ASSERT_EQ(vertices[15].z, 6.75f); // central vertex of 6th triangle.
    ASSERT_EQ(vertices[16].z, 1.00f); // southwest vertex.
    ASSERT_EQ(vertices[17].z, 8.00f); // northwest vertex.

    ASSERT_EQ(vertices[18].z, 6.75f);  // central vertex of 7th triangle.
    ASSERT_EQ(vertices[19].z, 8.00f);  // northwest vertex.
    ASSERT_EQ(vertices[20].z, 16.00f); // northeast vertex.

    ASSERT_EQ(vertices[21].z, 6.75f);  // central vertex of 8th triangle.
    ASSERT_EQ(vertices[22].z, 16.00f); // northeast vertex.
    ASSERT_EQ(vertices[23].z, 2.00f);  // southeast vertex.

    ASSERT_EQ(vertices[24].z, 27.00f); // central vertex of 9th triangle.
    ASSERT_EQ(vertices[25].z, 8.00f);  // southeast vertex.
    ASSERT_EQ(vertices[26].z, 4.00f);  // southwest vertex.

    ASSERT_EQ(vertices[27].z, 27.00f); // central vertex of 10th triangle.
    ASSERT_EQ(vertices[28].z, 4.00f);  // southwest vertex.
    ASSERT_EQ(vertices[29].z, 32.00f); // northwest vertex.

    ASSERT_EQ(vertices[30].z, 27.00f); // central vertex of 11th triangle.
    ASSERT_EQ(vertices[31].z, 32.00f); // northwest vertex.
    ASSERT_EQ(vertices[32].z, 64.00f); // northeast vertex.

    ASSERT_EQ(vertices[33].z, 27.00f); // central vertex of 12th triangle.
    ASSERT_EQ(vertices[34].z, 64.00f); // northeast vertex.
    ASSERT_EQ(vertices[35].z, 8.00f);  // southeast vertex.

    ASSERT_EQ(vertices[36].z, 54.00f); // central vertex of 13th triangle.
    ASSERT_EQ(vertices[37].z, 16.00f); // southeast vertex.
    ASSERT_EQ(vertices[38].z, 8.00f);  // southwest vertex.

    ASSERT_EQ(vertices[39].z, 54.00f); // central vertex of 14th triangle.
    ASSERT_EQ(vertices[40].z, 8.00f);  // southwest vertex.
    ASSERT_EQ(vertices[41].z, 64.00f); // northwest vertex.

    ASSERT_EQ(vertices[42].z, 54.00f);  // central vertex of 15th triangle.
    ASSERT_EQ(vertices[43].z, 64.00f);  // northwest vertex.
    ASSERT_EQ(vertices[44].z, 128.00f); // northeast vertex.

    ASSERT_EQ(vertices[45].z, 54.00f);  // central vertex of 15th triangle.
    ASSERT_EQ(vertices[46].z, 128.00f); // northeast vertex.
    ASSERT_EQ(vertices[47].z, 16.00f);  // southeast vertex.

    //  +-------+-------+
    //  |\ 10  /|\ 14  /|
    //  | \   / | \   / |
    //  |  \ /  |  \ /  |
    //  | 9 x 11|13 x 15|
    //  |  / \  |  / \  |
    //  | /   \ | /   \ |
    //  |/  8  \|/ 12  \|
    //  +-------+-------+
    //  |\  2  /|\  6  /|
    //  | \   / | \   / |
    //  |  \ /  |  \ /  |
    //  |1  x  3|5  x  7|
    //  |  / \  |  / \  |
    //  | /   \ | /   \ |
    //  |/  0  \|/  4  \|
    //  +-------+-------+

    ASSERT_EQ(uvs[0].x, 0.5f); // central vertex of 1st triangle.
    ASSERT_EQ(uvs[0].y, 0.5f); // central vertex of 1st triangle.
    ASSERT_EQ(uvs[1].x, 1.0f); // southeast vertex.
    ASSERT_EQ(uvs[1].y, 0.0f); // southeast vertex.
    ASSERT_EQ(uvs[2].x, 0.0f); // southwest vertex.
    ASSERT_EQ(uvs[2].y, 0.0f); // southwest vertex.

    ASSERT_EQ(uvs[3].x, 0.5f); // central vertex of 2nd triangle.
    ASSERT_EQ(uvs[3].y, 0.5f); // central vertex of 2nd triangle.
    ASSERT_EQ(uvs[4].x, 0.0f); // southwest vertex.
    ASSERT_EQ(uvs[4].y, 0.0f); // southwest vertex.
    ASSERT_EQ(uvs[5].x, 0.0f); // northwest vertex.
    ASSERT_EQ(uvs[5].y, 1.0f); // northwest vertex.

    ASSERT_EQ(uvs[6].x, 0.5f); // central vertex of 3rd triangle.
    ASSERT_EQ(uvs[6].y, 0.5f); // central vertex of 3rd triangle.
    ASSERT_EQ(uvs[7].x, 0.0f); // northwest vertex.
    ASSERT_EQ(uvs[7].y, 1.0f); // northwest vertex.
    ASSERT_EQ(uvs[8].x, 1.0f); // northeast vertex.
    ASSERT_EQ(uvs[8].y, 1.0f); // northeast vertex.

    ASSERT_EQ(uvs[9].x, 0.5f);  // central vertex of 4th triangle.
    ASSERT_EQ(uvs[9].y, 0.5f);  // central vertex of 4th triangle.
    ASSERT_EQ(uvs[10].x, 1.0f); // northeast vertex.
    ASSERT_EQ(uvs[10].y, 1.0f); // northeast vertex.
    ASSERT_EQ(uvs[11].x, 1.0f); // southeast vertex.
    ASSERT_EQ(uvs[11].y, 0.0f); // southeast vertex.

    ASSERT_EQ(uvs[12].x, 0.5f); // central vertex of 5th triangle.
    ASSERT_EQ(uvs[12].y, 0.5f); // central vertex of 5th triangle.
    ASSERT_EQ(uvs[13].x, 0.0f); // southeast vertex.
    ASSERT_EQ(uvs[13].y, 0.0f); // southeast vertex.
    ASSERT_EQ(uvs[14].x, 1.0f); // southwest vertex.
    ASSERT_EQ(uvs[14].y, 0.0f); // southwest vertex.

    ASSERT_EQ(uvs[15].x, 0.5f); // central vertex of 6th triangle.
    ASSERT_EQ(uvs[15].y, 0.5f); // central vertex of 6th triangle.
    ASSERT_EQ(uvs[16].x, 1.0f); // southwest vertex.
    ASSERT_EQ(uvs[16].y, 0.0f); // southwest vertex.
    ASSERT_EQ(uvs[17].x, 1.0f); // northwest vertex.
    ASSERT_EQ(uvs[17].y, 1.0f); // northwest vertex.

    ASSERT_EQ(uvs[18].x, 0.5f); // central vertex of 7th triangle.
    ASSERT_EQ(uvs[18].y, 0.5f); // central vertex of 7th triangle.
    ASSERT_EQ(uvs[19].x, 1.0f); // northwest vertex.
    ASSERT_EQ(uvs[19].y, 1.0f); // northwest vertex.
    ASSERT_EQ(uvs[20].x, 0.0f); // northeast vertex.
    ASSERT_EQ(uvs[20].y, 1.0f); // northeast vertex.

    ASSERT_EQ(uvs[21].x, 0.5f); // central vertex of 8th triangle.
    ASSERT_EQ(uvs[21].y, 0.5f); // central vertex of 8th triangle.
    ASSERT_EQ(uvs[22].x, 0.0f); // northeast vertex.
    ASSERT_EQ(uvs[22].y, 1.0f); // northeast vertex.
    ASSERT_EQ(uvs[23].x, 0.0f); // southeast vertex.
    ASSERT_EQ(uvs[23].y, 0.0f); // southeast vertex.

    ASSERT_EQ(uvs[24].x, 0.5f); // central vertex of 9th triangle.
    ASSERT_EQ(uvs[24].y, 0.5f); // central vertex of 9th triangle.
    ASSERT_EQ(uvs[25].x, 1.0f); // southeast vertex.
    ASSERT_EQ(uvs[25].y, 1.0f); // southeast vertex.
    ASSERT_EQ(uvs[26].x, 0.0f); // southwest vertex.
    ASSERT_EQ(uvs[26].y, 1.0f); // southwest vertex.

    ASSERT_EQ(uvs[27].x, 0.5f); // central vertex of 10th triangle.
    ASSERT_EQ(uvs[27].y, 0.5f); // central vertex of 10th triangle.
    ASSERT_EQ(uvs[28].x, 0.0f); // southwest vertex.
    ASSERT_EQ(uvs[28].y, 1.0f); // southwest vertex.
    ASSERT_EQ(uvs[29].x, 0.0f); // northwest vertex.
    ASSERT_EQ(uvs[29].y, 0.0f); // northwest vertex.

    ASSERT_EQ(uvs[30].x, 0.5f); // central vertex of 11th triangle.
    ASSERT_EQ(uvs[30].y, 0.5f); // central vertex of 11th triangle.
    ASSERT_EQ(uvs[31].x, 0.0f); // northwest vertex.
    ASSERT_EQ(uvs[31].y, 0.0f); // northwest vertex.
    ASSERT_EQ(uvs[32].x, 1.0f); // northeast vertex.
    ASSERT_EQ(uvs[32].y, 0.0f); // northeast vertex.

    ASSERT_EQ(uvs[33].x, 0.5f); // central vertex of 12th triangle.
    ASSERT_EQ(uvs[33].y, 0.5f); // central vertex of 12th triangle.
    ASSERT_EQ(uvs[34].x, 1.0f); // northeast vertex.
    ASSERT_EQ(uvs[34].y, 0.0f); // northeast vertex.
    ASSERT_EQ(uvs[35].x, 1.0f); // southeast vertex.
    ASSERT_EQ(uvs[35].y, 1.0f); // southeast vertex.

    ASSERT_EQ(uvs[36].x, 0.5f); // central vertex of 13th triangle.
    ASSERT_EQ(uvs[36].y, 0.5f); // central vertex of 13th triangle.
    ASSERT_EQ(uvs[37].x, 0.0f); // southeast vertex.
    ASSERT_EQ(uvs[37].y, 1.0f); // southeast vertex.
    ASSERT_EQ(uvs[38].x, 1.0f); // southwest vertex.
    ASSERT_EQ(uvs[38].y, 1.0f); // southwest vertex.

    ASSERT_EQ(uvs[39].x, 0.5f); // central vertex of 14th triangle.
    ASSERT_EQ(uvs[39].y, 0.5f); // central vertex of 14th triangle.
    ASSERT_EQ(uvs[40].x, 1.0f); // southwest vertex.
    ASSERT_EQ(uvs[40].y, 1.0f); // southwest vertex.
    ASSERT_EQ(uvs[41].x, 1.0f); // northwest vertex.
    ASSERT_EQ(uvs[41].y, 0.0f); // northwest vertex.

    ASSERT_EQ(uvs[42].x, 0.5f); // central vertex of 15th triangle.
    ASSERT_EQ(uvs[42].y, 0.5f); // central vertex of 15th triangle.
    ASSERT_EQ(uvs[43].x, 1.0f); // northwest vertex.
    ASSERT_EQ(uvs[43].y, 0.0f); // northwest vertex.
    ASSERT_EQ(uvs[44].x, 0.0f); // northeast vertex.
    ASSERT_EQ(uvs[44].y, 0.0f); // northeast vertex.

    ASSERT_EQ(uvs[45].x, 0.5f); // central vertex of 16th triangle.
    ASSERT_EQ(uvs[45].y, 0.5f); // central vertex of 16th triangle.
    ASSERT_EQ(uvs[46].x, 0.0f); // northeast vertex.
    ASSERT_EQ(uvs[46].y, 0.0f); // northeast vertex.
    ASSERT_EQ(uvs[47].x, 0.0f); // southeast vertex.
    ASSERT_EQ(uvs[47].y, 1.0f); // southeast vertex.
}

TEST(an_ascii_grid_must_be_defined_appropriately, test_3x3_0_1_2_4_8_16_32_64_128_256_x_step_1_y_step_1)
{
    yli::load::HeightmapLoaderStruct heightmap_loader_struct;
    heightmap_loader_struct.filename = "test_3x3_0_1_2_4_8_16_32_64_128.asc";
    heightmap_loader_struct.x_step = 1;
    heightmap_loader_struct.y_step = 1;
    heightmap_loader_struct.use_real_texture_coordinates = true;
    heightmap_loader_struct.triangulate = false;

    std::vector<glm::vec3> vertices;         // vertices of the object.
    std::vector<glm::vec2> uvs;              // UVs of the object.
    std::vector<glm::vec3> normals;          // normals of the object.
    uint32_t image_width;
    uint32_t image_height;

    bool model_loading_result = yli::load::load_ascii_grid_terrain(
            heightmap_loader_struct,
            vertices,
            uvs,
            normals,
            image_width,
            image_height);

    ASSERT_TRUE(model_loading_result);
    ASSERT_EQ(vertices.size(), 9);
    ASSERT_EQ(uvs.size(), 0);
    ASSERT_EQ(normals.size(), 0);

    ASSERT_EQ(vertices[0].z, 0.0f);
    ASSERT_EQ(vertices[1].z, 1.0f);
    ASSERT_EQ(vertices[2].z, 2.0f);

    ASSERT_EQ(vertices[3].z, 4.0f);
    ASSERT_EQ(vertices[4].z, 8.0f);
    ASSERT_EQ(vertices[5].z, 16.0f);

    ASSERT_EQ(vertices[6].z, 32.0f);
    ASSERT_EQ(vertices[7].z, 64.0f);
    ASSERT_EQ(vertices[8].z, 128.0f);
}
