// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2023 Antti Nuortimo.
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
#include "code/ylikuutio/load/png_heightmap_loader.hpp"
#include "code/ylikuutio/load/heightmap_loader_struct.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

TEST(a_png_terrain_must_be_loaded_appropriately, load_3x3_png_terrain)
{
    yli::load::HeightmapLoaderStruct heightmap_loader_struct;
    heightmap_loader_struct.filename = "test3x3.png";
    heightmap_loader_struct.x_step = 1;
    heightmap_loader_struct.y_step = 1;
    heightmap_loader_struct.triangulation_type = "bilinear_interpolation";
    heightmap_loader_struct.use_real_texture_coordinates = true;

    std::vector<glm::vec3> out_vertices;
    std::vector<glm::vec2> out_uvs;
    std::vector<glm::vec3> out_normals;
    uint32_t image_width = 0;
    uint32_t image_height = 0;
    const std::string color_channel = "mean";

    bool model_loading_result = yli::load::load_png_terrain(
            heightmap_loader_struct,
            out_vertices,
            out_uvs,
            out_normals,
            image_width,
            image_height,
            color_channel);

    ASSERT_TRUE(model_loading_result);

    const uint32_t n_vertices_for_face = 3;
    const uint32_t n_faces_for_bilinear_triangulation = 4;
    const uint32_t n_width_of_image_file = 3;
    const uint32_t n_height_of_image_file = 3;

    //                         48 =                  3 *                                  4 * (                    3 - 1) * (                     3 - 1)
    ASSERT_EQ(out_vertices.size(), n_vertices_for_face * n_faces_for_bilinear_triangulation * (n_width_of_image_file - 1) * (n_height_of_image_file - 1));

    //                    48 =                  3  *                                 4 * (                    3 - 1) * (                     3 - 1)
    ASSERT_EQ(out_uvs.size(), n_vertices_for_face * n_faces_for_bilinear_triangulation * (n_width_of_image_file - 1) * (n_height_of_image_file - 1));

    //                        48 =                  3  *                                 4 * (                    3 - 1) * (                     3 - 1)
    ASSERT_EQ(out_normals.size(), n_vertices_for_face * n_faces_for_bilinear_triangulation * (n_width_of_image_file - 1) * (n_height_of_image_file - 1));

    // test3x3.png colors:
    // | 32,32,32  64,64,64  128,128,128 |
    // |  4, 4, 4   8, 8, 8   16, 16, 16 |
    // |  0, 0, 0   1, 1, 1    2,  2,  2 |
    //
    // Or simply as graycolor (PNG):
    // |  32 64 128 |
    // |   4  8  16 |
    // |   0  1   2 |

    ASSERT_EQ(out_vertices[0].x, 0.5f); // first vertex (center) of first (south) triangle.
    ASSERT_EQ(out_vertices[0].z, 0.5f);
    ASSERT_EQ(out_vertices[0].y, 3.25f);
    ASSERT_EQ(out_uvs[0].x, 0.5f);
    ASSERT_EQ(out_uvs[0].y, 0.5f);

    ASSERT_EQ(out_vertices[1].x, 1.0f); // second vertex (southeast) of first (south) triangle.
    ASSERT_EQ(out_vertices[1].z, 0.0f);
    ASSERT_EQ(out_vertices[1].y, 1.0f);
    ASSERT_EQ(out_uvs[1].x, 1.0f);
    ASSERT_EQ(out_uvs[1].y, 0.0f);

    ASSERT_EQ(out_vertices[2].x, 0.0f); // third vertex (southwest) of first (south) triangle.
    ASSERT_EQ(out_vertices[2].z, 0.0f);
    ASSERT_EQ(out_vertices[2].y, 0.0f);
    ASSERT_EQ(out_uvs[2].x, 0.0f);
    ASSERT_EQ(out_uvs[2].y, 0.0f);

    ASSERT_EQ(out_vertices[3].x, 0.5f); // first vertex (center) of second (west) triangle.
    ASSERT_EQ(out_vertices[3].z, 0.5f);
    ASSERT_EQ(out_vertices[3].y, 3.25f);
    ASSERT_EQ(out_uvs[3].x, 0.5f);
    ASSERT_EQ(out_uvs[3].y, 0.5f);

    ASSERT_EQ(out_vertices[4].x, 0.0f); // second vertex (southwest) of second (west) triangle.
    ASSERT_EQ(out_vertices[4].z, 0.0f);
    ASSERT_EQ(out_vertices[4].y, 0.0f);
    ASSERT_EQ(out_uvs[4].x, 0.0f);
    ASSERT_EQ(out_uvs[4].y, 0.0f);

    ASSERT_EQ(out_vertices[5].x, 0.0f); // third vertex (northwest) of second (west) triangle.
    ASSERT_EQ(out_vertices[5].z, 1.0f);
    ASSERT_EQ(out_vertices[5].y, 4.0f);
    ASSERT_EQ(out_uvs[5].x, 0.0f);
    ASSERT_EQ(out_uvs[5].y, 1.0f);

    ASSERT_EQ(out_vertices[6].x, 0.5f); // first vertex (center) of third (north) triangle.
    ASSERT_EQ(out_vertices[6].z, 0.5f);
    ASSERT_EQ(out_vertices[6].y, 3.25f);
    ASSERT_EQ(out_uvs[6].x, 0.5f);
    ASSERT_EQ(out_uvs[6].y, 0.5f);

    ASSERT_EQ(out_vertices[7].x, 0.0f); // second vertex (northwest) of third (north) triangle.
    ASSERT_EQ(out_vertices[7].z, 1.0f);
    ASSERT_EQ(out_vertices[7].y, 4.0f);
    ASSERT_EQ(out_uvs[7].x, 0.0f);
    ASSERT_EQ(out_uvs[7].y, 1.0f);

    ASSERT_EQ(out_vertices[8].x, 1.0f); // third vertex (northeast) of third (north) triangle.
    ASSERT_EQ(out_vertices[8].z, 1.0f);
    ASSERT_EQ(out_vertices[8].y, 8.0f);
    ASSERT_EQ(out_uvs[8].x, 1.0f);
    ASSERT_EQ(out_uvs[8].y, 1.0f);

    ASSERT_EQ(out_vertices[9].x, 0.5f); // first vertex (center) of fourth (east) triangle.
    ASSERT_EQ(out_vertices[9].z, 0.5f);
    ASSERT_EQ(out_vertices[9].y, 3.25f);
    ASSERT_EQ(out_uvs[9].x, 0.5f);
    ASSERT_EQ(out_uvs[9].y, 0.5f);

    ASSERT_EQ(out_vertices[10].x, 1.0f); // second vertex (northeast) of fourth (east) triangle.
    ASSERT_EQ(out_vertices[10].z, 1.0f);
    ASSERT_EQ(out_vertices[10].y, 8.0f);
    ASSERT_EQ(out_uvs[10].x, 1.0f);
    ASSERT_EQ(out_uvs[10].y, 1.0f);

    ASSERT_EQ(out_vertices[11].x, 1.0f); // third vertex (southeast) of fourth (east) triangle.
    ASSERT_EQ(out_vertices[11].z, 0.0f);
    ASSERT_EQ(out_vertices[11].y, 1.0f);
    ASSERT_EQ(out_uvs[11].x, 1.0f);
    ASSERT_EQ(out_uvs[11].y, 0.0f);

    ASSERT_EQ(out_vertices[12].x, 1.5f); // first vertex (center) of fifth (south) triangle.
    ASSERT_EQ(out_vertices[12].z, 0.5f);
    ASSERT_EQ(out_vertices[12].y, 6.75f);
    ASSERT_EQ(out_uvs[12].x, 0.5f);
    ASSERT_EQ(out_uvs[12].y, 0.5f);

    ASSERT_EQ(out_vertices[13].x, 2.0f); // second vertex (southeast) of fifth (south) triangle.
    ASSERT_EQ(out_vertices[13].z, 0.0f);
    ASSERT_EQ(out_vertices[13].y, 2.0f);
    ASSERT_EQ(out_uvs[13].x, 0.0f);
    ASSERT_EQ(out_uvs[13].y, 0.0f);

    ASSERT_EQ(out_vertices[14].x, 1.0f); // third vertex (southwest) of fifth (south) triangle.
    ASSERT_EQ(out_vertices[14].z, 0.0f);
    ASSERT_EQ(out_vertices[14].y, 1.0f);
    ASSERT_EQ(out_uvs[14].x, 1.0f);
    ASSERT_EQ(out_uvs[14].y, 0.0f);

    ASSERT_EQ(out_vertices[15].x, 1.5f); // first vertex (center) of sixth (west) triangle.
    ASSERT_EQ(out_vertices[15].z, 0.5f);
    ASSERT_EQ(out_vertices[15].y, 6.75);
    ASSERT_EQ(out_uvs[15].x, 0.5f);
    ASSERT_EQ(out_uvs[15].y, 0.5f);

    ASSERT_EQ(out_vertices[16].x, 1.0f); // second vertex (southwest) of sixth (west) triangle.
    ASSERT_EQ(out_vertices[16].z, 0.0f);
    ASSERT_EQ(out_vertices[16].y, 1.0f);
    ASSERT_EQ(out_uvs[16].x, 1.0f);
    ASSERT_EQ(out_uvs[16].y, 0.0f);

    ASSERT_EQ(out_vertices[17].x, 1.0f); // third vertex (northwest) of sixth (west) triangle.
    ASSERT_EQ(out_vertices[17].z, 1.0f);
    ASSERT_EQ(out_vertices[17].y, 8.0f);
    ASSERT_EQ(out_uvs[17].x, 1.0f);
    ASSERT_EQ(out_uvs[17].y, 1.0f);

    ASSERT_EQ(out_vertices[18].x, 1.5f); // first vertex (center) of seventh (north) triangle.
    ASSERT_EQ(out_vertices[18].z, 0.5f);
    ASSERT_EQ(out_vertices[18].y, 6.75f);
    ASSERT_EQ(out_uvs[18].x, 0.5f);
    ASSERT_EQ(out_uvs[18].y, 0.5f);

    ASSERT_EQ(out_vertices[19].x, 1.0f); // second vertex (northwest) of seventh (north) triangle.
    ASSERT_EQ(out_vertices[19].z, 1.0f);
    ASSERT_EQ(out_vertices[19].y, 8.0f);
    ASSERT_EQ(out_uvs[19].x, 1.0f);
    ASSERT_EQ(out_uvs[19].y, 1.0f);

    ASSERT_EQ(out_vertices[20].x, 2.0f); // third vertex (northeast) of seventh (north) triangle.
    ASSERT_EQ(out_vertices[20].z, 1.0f);
    ASSERT_EQ(out_vertices[20].y, 16.0f);

    ASSERT_EQ(out_vertices[21].x, 1.5f); // first vertex (center) of eigth (east) triangle.
    ASSERT_EQ(out_vertices[21].z, 0.5f);
    ASSERT_EQ(out_vertices[21].y, 6.75f);
    ASSERT_EQ(out_uvs[21].x, 0.5f);
    ASSERT_EQ(out_uvs[21].y, 0.5f);

    ASSERT_EQ(out_vertices[22].x, 2.0f); // second vertex (northeast) of eigth (east) triangle.
    ASSERT_EQ(out_vertices[22].z, 1.0f);
    ASSERT_EQ(out_vertices[22].y, 16.0f);

    ASSERT_EQ(out_vertices[23].x, 2.0f); // third vertex (southeast) of eigth (east) triangle.
    ASSERT_EQ(out_vertices[23].z, 0.0f);
    ASSERT_EQ(out_vertices[23].y, 2.0f);

    ASSERT_EQ(out_vertices[24].x, 0.5f); // first vertex (center) of ninth (south) triangle.
    ASSERT_EQ(out_vertices[24].z, 1.5f);
    ASSERT_EQ(out_vertices[24].y, 27.0f);
    ASSERT_EQ(out_uvs[24].x, 0.5f);
    ASSERT_EQ(out_uvs[24].y, 0.5f);

    ASSERT_EQ(out_vertices[25].x, 1.0f); // second vertex (southeast) of ninth (south) triangle.
    ASSERT_EQ(out_vertices[25].z, 1.0f);
    ASSERT_EQ(out_vertices[25].y, 8.0f);
    ASSERT_EQ(out_uvs[25].x, 1.0f);
    ASSERT_EQ(out_uvs[25].y, 1.0f);

    ASSERT_EQ(out_vertices[26].x, 0.0f); // third vertex (southwest) of ninth (south) triangle.
    ASSERT_EQ(out_vertices[26].z, 1.0f);
    ASSERT_EQ(out_vertices[26].y, 4.0f);
    ASSERT_EQ(out_uvs[26].x, 0.0f);
    ASSERT_EQ(out_uvs[26].y, 1.0f);

    ASSERT_EQ(out_vertices[27].x, 0.5f); // first vertex (center) of tenth (west) triangle.
    ASSERT_EQ(out_vertices[27].z, 1.5f);
    ASSERT_EQ(out_vertices[27].y, 27.0);
    ASSERT_EQ(out_uvs[27].x, 0.5f);
    ASSERT_EQ(out_uvs[27].y, 0.5f);

    ASSERT_EQ(out_vertices[28].x, 0.0f); // second vertex (southwest) of tenth (west) triangle.
    ASSERT_EQ(out_vertices[28].z, 1.0f);
    ASSERT_EQ(out_vertices[28].y, 4.0);
    ASSERT_EQ(out_uvs[28].x, 0.0f);
    ASSERT_EQ(out_uvs[28].y, 1.0f);

    ASSERT_EQ(out_vertices[29].x, 0.0f); // third vertex (northwest) of tenth (west) triangle.
    ASSERT_EQ(out_vertices[29].z, 2.0f);
    ASSERT_EQ(out_vertices[29].y, 32.0);
    ASSERT_EQ(out_uvs[29].x, 0.0f);
    ASSERT_EQ(out_uvs[29].y, 0.0f);

    ASSERT_EQ(out_vertices[30].x, 0.5f); // first vertex (center) of 11th (north) triangle.
    ASSERT_EQ(out_vertices[30].z, 1.5f);
    ASSERT_EQ(out_vertices[30].y, 27.0);
    ASSERT_EQ(out_uvs[30].x, 0.5f);
    ASSERT_EQ(out_uvs[30].y, 0.5f);

    ASSERT_EQ(out_vertices[31].x, 0.0f); // second vertex (northwest) of 11th (north) triangle.
    ASSERT_EQ(out_vertices[31].z, 2.0f);
    ASSERT_EQ(out_vertices[31].y, 32.0);
    ASSERT_EQ(out_uvs[31].x, 0.0f);
    ASSERT_EQ(out_uvs[31].y, 0.0f);

    ASSERT_EQ(out_vertices[32].x, 1.0f); // third vertex (northeast) of 11th (north) triangle.
    ASSERT_EQ(out_vertices[32].z, 2.0f);
    ASSERT_EQ(out_vertices[32].y, 64.0);
    ASSERT_EQ(out_uvs[32].x, 1.0f);
    ASSERT_EQ(out_uvs[32].y, 0.0f);

    ASSERT_EQ(out_vertices[33].x, 0.5f); // first vertex (center) of 12th (east) triangle.
    ASSERT_EQ(out_vertices[33].z, 1.5f);
    ASSERT_EQ(out_vertices[33].y, 27.0f);
    ASSERT_EQ(out_uvs[33].x, 0.5f);
    ASSERT_EQ(out_uvs[33].y, 0.5f);

    ASSERT_EQ(out_vertices[34].x, 1.0f); // second vertex (northeast) of 12th (east) triangle.
    ASSERT_EQ(out_vertices[34].z, 2.0f);
    ASSERT_EQ(out_vertices[34].y, 64.0f);
    ASSERT_EQ(out_uvs[34].x, 1.0f);
    ASSERT_EQ(out_uvs[34].y, 0.0f);

    ASSERT_EQ(out_vertices[35].x, 1.0f); // third vertex (southeast) of 12th (east) triangle.
    ASSERT_EQ(out_vertices[35].z, 1.0f);
    ASSERT_EQ(out_vertices[35].y, 8.0f);
    ASSERT_EQ(out_uvs[35].x, 1.0f);
    ASSERT_EQ(out_uvs[35].y, 1.0f);

    ASSERT_EQ(out_vertices[36].x, 1.5f); // first vertex (center) of 13th (south) triangle.
    ASSERT_EQ(out_vertices[36].z, 1.5f);
    ASSERT_EQ(out_vertices[36].y, 54.0f);
    ASSERT_EQ(out_uvs[36].x, 0.5f);
    ASSERT_EQ(out_uvs[36].y, 0.5f);

    ASSERT_EQ(out_vertices[37].x, 2.0f); // second vertex (southeast) of 13th (south) triangle.
    ASSERT_EQ(out_vertices[37].z, 1.0f);
    ASSERT_EQ(out_vertices[37].y, 16.0f);
    ASSERT_EQ(out_uvs[37].x, 0.0f);
    ASSERT_EQ(out_uvs[37].y, 1.0f);

    ASSERT_EQ(out_vertices[38].x, 1.0f); // third vertex (southwest) of 13th (south) triangle.
    ASSERT_EQ(out_vertices[38].z, 1.0f);
    ASSERT_EQ(out_vertices[38].y, 8.0f);
    ASSERT_EQ(out_uvs[38].x, 1.0f);
    ASSERT_EQ(out_uvs[38].y, 1.0f);

    ASSERT_EQ(out_vertices[39].x, 1.5f); // first vertex (center) of 14th (west) triangle.
    ASSERT_EQ(out_vertices[39].z, 1.5f);
    ASSERT_EQ(out_vertices[39].y, 54.0f);
    ASSERT_EQ(out_uvs[39].x, 0.5f);
    ASSERT_EQ(out_uvs[39].y, 0.5f);

    ASSERT_EQ(out_vertices[40].x, 1.0f); // second vertex (southwest) of 14th (west) triangle.
    ASSERT_EQ(out_vertices[40].z, 1.0f);
    ASSERT_EQ(out_vertices[40].y, 8.0f);
    ASSERT_EQ(out_uvs[40].x, 1.0f);
    ASSERT_EQ(out_uvs[40].y, 1.0f);

    ASSERT_EQ(out_vertices[41].x, 1.0f); // third vertex (northwest) of 14th (west) triangle.
    ASSERT_EQ(out_vertices[41].z, 2.0f);
    ASSERT_EQ(out_vertices[41].y, 64.0f);
    ASSERT_EQ(out_uvs[41].x, 1.0f);
    ASSERT_EQ(out_uvs[41].y, 0.0f);

    ASSERT_EQ(out_vertices[42].x, 1.5f); // first vertex (center) of 15th (north) triangle.
    ASSERT_EQ(out_vertices[42].z, 1.5f);
    ASSERT_EQ(out_vertices[42].y, 54.0f);
    ASSERT_EQ(out_uvs[42].x, 0.5f);
    ASSERT_EQ(out_uvs[42].y, 0.5f);

    ASSERT_EQ(out_vertices[43].x, 1.0f); // second vertex (northwest) of 15th (north) triangle.
    ASSERT_EQ(out_vertices[43].z, 2.0f);
    ASSERT_EQ(out_vertices[43].y, 64.0f);
    ASSERT_EQ(out_uvs[43].x, 1.0f);
    ASSERT_EQ(out_uvs[43].y, 0.0f);

    ASSERT_EQ(out_vertices[44].x, 2.0f); // third vertex (northeast) of 15th (north) triangle.
    ASSERT_EQ(out_vertices[44].z, 2.0f);
    ASSERT_EQ(out_vertices[44].y, 128.0f);
    ASSERT_EQ(out_uvs[44].x, 0.0f);
    ASSERT_EQ(out_uvs[44].y, 0.0f);

    ASSERT_EQ(out_vertices[45].x, 1.5f); // first vertex (center) of 16th (east) triangle.
    ASSERT_EQ(out_vertices[45].z, 1.5f);
    ASSERT_EQ(out_vertices[45].y, 54.0f);
    ASSERT_EQ(out_uvs[45].x, 0.5f);
    ASSERT_EQ(out_uvs[45].y, 0.5f);

    ASSERT_EQ(out_vertices[46].x, 2.0f); // second vertex (northeast) of 16th (east) triangle.
    ASSERT_EQ(out_vertices[46].z, 2.0f);
    ASSERT_EQ(out_vertices[46].y, 128.0f);
    ASSERT_EQ(out_uvs[46].x, 0.0f);
    ASSERT_EQ(out_uvs[46].y, 0.0f);

    ASSERT_EQ(out_vertices[47].x, 2.0f); // third vertex (southeast) of 16th (east) triangle.
    ASSERT_EQ(out_vertices[47].z, 1.0f);
    ASSERT_EQ(out_vertices[47].y, 16.0f);
    ASSERT_EQ(out_uvs[47].x, 0.0f);
    ASSERT_EQ(out_uvs[47].y, 1.0f);

    // TODO: add assertions for normals!
}

TEST(a_png_terrain_must_be_loaded_appropriately, load_256x256_png_terrain)
{
    yli::load::HeightmapLoaderStruct heightmap_loader_struct;
    heightmap_loader_struct.filename = "noise256x256.png";
    heightmap_loader_struct.x_step = 1;
    heightmap_loader_struct.y_step = 1;
    heightmap_loader_struct.triangulation_type = "bilinear_interpolation";
    heightmap_loader_struct.use_real_texture_coordinates = true;

    std::vector<glm::vec3> out_vertices;
    std::vector<glm::vec2> out_uvs;
    std::vector<glm::vec3> out_normals;
    uint32_t image_width = 0;
    uint32_t image_height = 0;
    const std::string color_channel = "mean";

    const bool model_loading_result = yli::load::load_png_terrain(
            heightmap_loader_struct,
            out_vertices,
            out_uvs,
            out_normals,
            image_width,
            image_height,
            color_channel);

    ASSERT_TRUE(model_loading_result);

    const uint32_t n_vertices_for_face = 3;
    const uint32_t n_faces_for_bilinear_triangulation = 4;
    const uint32_t n_width_of_image_file = 256;
    const uint32_t n_height_of_image_file = 256;

    ASSERT_EQ(out_vertices.size(), n_vertices_for_face * n_faces_for_bilinear_triangulation * (n_width_of_image_file - 1) * (n_height_of_image_file - 1));
    ASSERT_EQ(out_uvs.size(), n_vertices_for_face * n_faces_for_bilinear_triangulation * (n_width_of_image_file - 1) * (n_height_of_image_file - 1));
    ASSERT_EQ(out_normals.size(), n_vertices_for_face * n_faces_for_bilinear_triangulation * (n_width_of_image_file - 1) * (n_height_of_image_file - 1));
}
