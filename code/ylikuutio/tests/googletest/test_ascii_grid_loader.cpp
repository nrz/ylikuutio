#include "gtest/gtest.h"
#include "code/ylikuutio/loaders/ascii_grid_loader.hpp"
#include "code/ylikuutio/loaders/ascii_grid_loader.cpp"

TEST(an_ASCII_grid_must_be_defined_and_interpolated_appropriately, test_3x3_0_1_2_4_8_16_32_64_128_256_x_step_1_z_step_1)
{
    const std::string ASCII_grid_model_filename = "test_3x3_0_1_2_4_8_16_32_64_128.asc"; // Helsinki eastern downtown.
    const int32_t x_step = 1;
    const int32_t z_step = 1;
    const std::string triangulation_type = "bilinear_interpolation";

    std::vector<glm::vec3> vertices;         // vertices of the object.
    std::vector<glm::vec2> UVs;              // UVs of the object.
    std::vector<glm::vec3> normals;          // normals of the object.

    bool model_loading_result = loaders::load_ASCII_grid(
            ASCII_grid_model_filename,
            vertices,
            UVs,
            normals,
            x_step,
            z_step,
            triangulation_type);

    ASSERT_TRUE(model_loading_result);

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

    ASSERT_EQ(vertices[0].y, 3.25f); // central vertex of 1st triangle.
    ASSERT_EQ(vertices[1].y, 1.00f); // southeast vertex.
    ASSERT_EQ(vertices[2].y, 0.00f); // southwest vertex.

    ASSERT_EQ(vertices[3].y, 3.25f); // central vertex of 2nd triangle.
    ASSERT_EQ(vertices[4].y, 0.00f); // southwest vertex.
    ASSERT_EQ(vertices[5].y, 4.00f); // northwest vertex.

    ASSERT_EQ(vertices[6].y, 3.25f); // central vertex of 3rd triangle.
    ASSERT_EQ(vertices[7].y, 4.00f); // northwest vertex.
    ASSERT_EQ(vertices[8].y, 8.00f); // northeast vertex.

    ASSERT_EQ(vertices[9].y, 3.25f);  // central vertex of 4th triangle.
    ASSERT_EQ(vertices[10].y, 8.00f); // northeast vertex.
    ASSERT_EQ(vertices[11].y, 1.00f); // southeast vertex.

    ASSERT_EQ(vertices[12].y, 6.75f); // central vertex of 5th triangle.
    ASSERT_EQ(vertices[13].y, 2.00f); // southeast vertex.
    ASSERT_EQ(vertices[14].y, 1.00f); // southwest vertex.

    ASSERT_EQ(vertices[15].y, 6.75f); // central vertex of 6th triangle.
    ASSERT_EQ(vertices[16].y, 1.00f); // southwest vertex.
    ASSERT_EQ(vertices[17].y, 8.00f); // northwest vertex.

    ASSERT_EQ(vertices[18].y, 6.75f);  // central vertex of 7th triangle.
    ASSERT_EQ(vertices[19].y, 8.00f);  // northwest vertex.
    ASSERT_EQ(vertices[20].y, 16.00f); // northeast vertex.

    ASSERT_EQ(vertices[21].y, 6.75f);  // central vertex of 8th triangle.
    ASSERT_EQ(vertices[22].y, 16.00f); // northeast vertex.
    ASSERT_EQ(vertices[23].y, 2.00f);  // southeast vertex.

    ASSERT_EQ(vertices[24].y, 27.00f); // central vertex of 9th triangle.
    ASSERT_EQ(vertices[25].y, 8.00f);  // southeast vertex.
    ASSERT_EQ(vertices[26].y, 4.00f);  // southwest vertex.

    ASSERT_EQ(vertices[27].y, 27.00f); // central vertex of 10th triangle.
    ASSERT_EQ(vertices[28].y, 4.00f);  // southwest vertex.
    ASSERT_EQ(vertices[29].y, 32.00f); // northwest vertex.

    ASSERT_EQ(vertices[30].y, 27.00f); // central vertex of 11th triangle.
    ASSERT_EQ(vertices[31].y, 32.00f); // northwest vertex.
    ASSERT_EQ(vertices[32].y, 64.00f); // northeast vertex.

    ASSERT_EQ(vertices[33].y, 27.00f); // central vertex of 12th triangle.
    ASSERT_EQ(vertices[34].y, 64.00f); // northeast vertex.
    ASSERT_EQ(vertices[35].y, 8.00f);  // southeast vertex.

    ASSERT_EQ(vertices[36].y, 54.00f); // central vertex of 13th triangle.
    ASSERT_EQ(vertices[37].y, 16.00f); // southeast vertex.
    ASSERT_EQ(vertices[38].y, 8.00f);  // southwest vertex.

    ASSERT_EQ(vertices[39].y, 54.00f); // central vertex of 14th triangle.
    ASSERT_EQ(vertices[40].y, 8.00f);  // southwest vertex.
    ASSERT_EQ(vertices[41].y, 64.00f); // northwest vertex.

    ASSERT_EQ(vertices[42].y, 54.00f);  // central vertex of 15th triangle.
    ASSERT_EQ(vertices[43].y, 64.00f);  // northwest vertex.
    ASSERT_EQ(vertices[44].y, 128.00f); // northeast vertex.

    ASSERT_EQ(vertices[45].y, 54.00f);  // central vertex of 15th triangle.
    ASSERT_EQ(vertices[46].y, 128.00f); // northeast vertex.
    ASSERT_EQ(vertices[47].y, 16.00f);  // southeast vertex.
}
