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
#include "code/ylikuutio/load/obj_loader.cpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <string>  // std::string
#include <vector>  // std::vector

TEST(obj_files_must_be_loaded_approriately, suzanne_obj)
{
    const std::string obj_filename = "suzanne.obj";
    std::vector<glm::vec3> out_vertices;
    std::vector<glm::vec2> out_uvs;
    std::vector<glm::vec3> out_normals;

    const bool result = yli::load::load_obj(obj_filename.c_str(), out_vertices, out_uvs, out_normals);
    ASSERT_TRUE(result);

    // note: `load_obj` only loads the OBJ file. `load_obj` does not remove duplicate vertices.
    const int32_t number_of_faces = 968;
    const int32_t number_of_vertices_in_triangle = 3;
    ASSERT_EQ(out_vertices.size(), number_of_faces * number_of_vertices_in_triangle);
    ASSERT_EQ(out_uvs.size(), number_of_faces * number_of_vertices_in_triangle);
    ASSERT_EQ(out_normals.size(), number_of_faces * number_of_vertices_in_triangle);

    // face 0:
    // f 61/1/1 65/2/2 49/3/3
    // vertex 61 (vertex numbering begins from 1):
    // v 0.351563 0.242188 0.828125
    ASSERT_GT(out_vertices[0].x, 0.3515625);
    ASSERT_LT(out_vertices[0].x, 0.35546875);
    ASSERT_GT(out_vertices[0].y, 0.2421875);
    ASSERT_LT(out_vertices[0].y, 0.24609375);
    ASSERT_EQ(out_vertices[0].z, 0.828125);
    // UV 1 (UV numbering begins from 1):
    // vt 0.315596 0.792535
    ASSERT_GT(out_uvs[0].x, 0.314453125);
    ASSERT_LT(out_uvs[0].x, 0.31640625);
    ASSERT_GT(out_uvs[0].y, 0.791015625);
    ASSERT_LT(out_uvs[0].y, 0.79296875);
    // vertex normal 1 (vertex normal numbering begins from 1):
    // vn 0.189764 -0.003571 0.981811
    ASSERT_GT(out_normals[0].x, 0.189453125);
    ASSERT_LT(out_normals[0].x, 0.19140625);
    ASSERT_GT(out_normals[0].y, -0.003662109);
    ASSERT_LT(out_normals[0].y, -0.003540039);
    ASSERT_GT(out_normals[0].z, 0.981445313);
    ASSERT_LT(out_normals[0].z, 0.982421875);

    // vertex 65 (vertex numbering begins from 1):
    // v 0.445313 0.156250 0.781250
    ASSERT_GT(out_vertices[1].x, 0.4453125);
    ASSERT_LT(out_vertices[1].x, 0.44921875);
    ASSERT_EQ(out_vertices[1].y, 0.15625);
    ASSERT_EQ(out_vertices[1].z, 0.78125);
    // UV 2 (UV numbering begins from 1):
    // vt 0.331462 0.787091
    ASSERT_GT(out_uvs[1].x, 0.330078125);
    ASSERT_LT(out_uvs[1].x, 0.33203125);
    ASSERT_GT(out_uvs[1].y, 0.786132813);
    ASSERT_LT(out_uvs[1].y, 0.787109375);
    // vertex normal 2 (vertex normal numbering begins from 1):
    // vn 0.646809 -0.758202 0.082095
    ASSERT_GT(out_normals[1].x, 0.64453125);
    ASSERT_LT(out_normals[1].x, 0.6484375);
    ASSERT_GT(out_normals[1].y, -0.758300781);
    ASSERT_LT(out_normals[1].y, -0.758056641);
    ASSERT_GT(out_normals[1].z, 0.08203125);
    ASSERT_LT(out_normals[1].z, 0.083984375);

    // vertex 49 (vertex numbering begins from 1):
    // v 0.476563 0.242188 0.773438
    ASSERT_GT(out_vertices[2].x, 0.4765625);
    ASSERT_LT(out_vertices[2].x, 0.48046875);
    ASSERT_GT(out_vertices[2].y, 0.2421875);
    ASSERT_LT(out_vertices[2].y, 0.24609375);
    ASSERT_GT(out_vertices[2].z, 0.7734375);
    ASSERT_LT(out_vertices[2].z, 0.77734375);
    // UV 3 (UV numbering begins from 1):
    // vt 0.331944 0.799704
    ASSERT_GT(out_uvs[2].x, 0.330078125);
    ASSERT_LT(out_uvs[2].x, 0.33203125);
    ASSERT_GT(out_uvs[2].y, 0.798828125);
    ASSERT_LT(out_uvs[2].y, 0.8046875);

    // face 1:
    // f 50/4/4 66/5/5 62/6/6
    // vertex 50 (vertex numbering begins from 1):
    // v -0.476563 0.242188 0.773438
    ASSERT_GT(out_vertices[3].x, -0.48046875);
    ASSERT_LT(out_vertices[3].x, -0.4765625);
    ASSERT_GT(out_vertices[3].y, 0.2421875);
    ASSERT_LT(out_vertices[3].y, 0.24609375);
    ASSERT_GT(out_vertices[3].z, 0.7734375);
    ASSERT_LT(out_vertices[3].z, 0.77734375);
    // UV 4 (UV numbering begins from 1):
    // vt 0.049262 0.798007
    ASSERT_GT(out_uvs[3].x, 0.048828125);
    ASSERT_LT(out_uvs[3].x, 0.05078125);
    ASSERT_GT(out_uvs[3].y, 0.797851563);
    ASSERT_LT(out_uvs[3].y, 0.798828125);

    // vertex 66 (vertex numbering begins from 1):
    // v -0.445313 0.156250 0.781250
    ASSERT_GT(out_vertices[4].x, -0.44921875);
    ASSERT_LT(out_vertices[4].x, -0.4453125);
    ASSERT_EQ(out_vertices[4].y, 0.15625);
    ASSERT_EQ(out_vertices[4].z, 0.78125);
    // UV 5 (UV numbering begins from 1):
    // vt 0.050304 0.785428
    ASSERT_GT(out_uvs[4].x, 0.050292969);
    ASSERT_LT(out_uvs[4].x, 0.050537109);
    ASSERT_GT(out_uvs[4].y, 0.78515625);
    ASSERT_LT(out_uvs[4].y, 0.785644531);

    // vertex 62 (vertex numbering begins from 1):
    // v -0.351563 0.242188 0.828125
    ASSERT_GT(out_vertices[5].x, -0.35546875);
    ASSERT_LT(out_vertices[5].x, -0.3515625);
    ASSERT_GT(out_vertices[5].y, 0.2421875);
    ASSERT_LT(out_vertices[5].y, 0.24609375);
    ASSERT_EQ(out_vertices[5].z, 0.828125);
    // UV 5 (UV numbering begins from 1):
    // vt 0.065913 0.791570
    ASSERT_GT(out_uvs[5].x, 0.065673828);
    ASSERT_LT(out_uvs[5].x, 0.065917969);
    ASSERT_GT(out_uvs[5].y, 0.791503906);
    ASSERT_LT(out_uvs[5].y, 0.791992188);

    // face 2:
    // f 63/7/7 65/2/2 61/1/1
    // vertex 63 (vertex numbering begins from 1):
    // v 0.351563 0.117188 0.804688
    ASSERT_GT(out_vertices[6].x, 0.3515625);
    ASSERT_LT(out_vertices[6].x, 0.35546875);
    ASSERT_GT(out_vertices[6].y, 0.1171875);
    ASSERT_LT(out_vertices[6].y, 0.12109375);
    ASSERT_GT(out_vertices[6].z, 0.8046875);
    ASSERT_LT(out_vertices[6].z, 0.80859375);

    // vertex 65 (vertex numbering begins from 1):
    // v 0.445313 0.156250 0.781250
    ASSERT_GT(out_vertices[7].x, 0.4453125);
    ASSERT_LT(out_vertices[7].x, 0.44921875);
    ASSERT_EQ(out_vertices[7].y, 0.15625);
    ASSERT_EQ(out_vertices[7].z, 0.78125);

    // vertex 61 (vertex numbering begins from 1):
    // v 0.351563 0.242188 0.828125
    ASSERT_GT(out_vertices[8].x, 0.3515625);
    ASSERT_LT(out_vertices[8].x, 0.35546875);
    ASSERT_GT(out_vertices[8].y, 0.2421875);
    ASSERT_LT(out_vertices[8].y, 0.24609375);
    ASSERT_EQ(out_vertices[8].z, 0.828125);

    // face 3:
    // f 62/6/6 66/5/5 64/8/8
    // vertex 62 (vertex numbering begins from 1):
    // v -0.351563 0.242188 0.828125
    ASSERT_GT(out_vertices[9].x, -0.35546875);
    ASSERT_LT(out_vertices[9].x, -0.3515625);
    ASSERT_GT(out_vertices[9].y, 0.2421875);
    ASSERT_LT(out_vertices[9].y, 0.24609375);
    ASSERT_EQ(out_vertices[9].z, 0.828125);

    // vertex 66 (vertex numbering begins from 1):
    // v -0.445313 0.156250 0.781250
    ASSERT_GT(out_vertices[10].x, -0.44921875);
    ASSERT_LT(out_vertices[10].x, -0.4453125);
    ASSERT_EQ(out_vertices[10].y, 0.15625);
    ASSERT_EQ(out_vertices[10].z, 0.78125);

    // vertex 64 (vertex numbering begins from 1):
    // v -0.351563 0.117188 0.804688
    ASSERT_GT(out_vertices[11].x, -0.35546875);
    ASSERT_LT(out_vertices[11].x, -0.3515625);
    ASSERT_GT(out_vertices[11].y, 0.1171875);
    ASSERT_LT(out_vertices[11].y, 0.12109375);
    ASSERT_GT(out_vertices[11].z, 0.8046875);
    ASSERT_LT(out_vertices[11].z, 0.80859375);

    // face 4:
    // f 61/1/1 59/9/9 63/7/7
    // vertex 61 (vertex numbering begins from 1):
    // v 0.351563 0.242188 0.828125
    ASSERT_GT(out_vertices[12].x, 0.3515625);
    ASSERT_LT(out_vertices[12].x, 0.35546875);
    ASSERT_GT(out_vertices[12].y, 0.2421875);
    ASSERT_LT(out_vertices[12].y, 0.24609375);
    ASSERT_EQ(out_vertices[12].z, 0.828125);

    // vertex 59 (vertex numbering begins from 1):
    // v 0.265625 0.156250 0.820313
    ASSERT_EQ(out_vertices[13].x, 0.265625);
    ASSERT_EQ(out_vertices[13].y, 0.15625);
    ASSERT_GT(out_vertices[13].z, 0.8203125);
    ASSERT_LT(out_vertices[13].z, 0.82421875);

    // vertex 63 (vertex numbering begins from 1):
    // v 0.351563 0.117188 0.804688
    ASSERT_GT(out_vertices[14].x, 0.3515625);
    ASSERT_LT(out_vertices[14].x, 0.35546875);
    ASSERT_GT(out_vertices[14].y, 0.1171875);
    ASSERT_LT(out_vertices[14].y, 0.12109375);
    ASSERT_GT(out_vertices[14].z, 0.8046875);
    ASSERT_LT(out_vertices[14].z, 0.80859375);

    // face 967:
    // f 47/546/463 3/588/505 45/562/479
    // vertex 47 (vertex numbering begins from 1):
    // v 0.468750 0.242188 0.757813
    ASSERT_EQ(out_vertices[3 * 966].x, 0.46875);
    ASSERT_GT(out_vertices[3 * 966].y, 0.2421875);
    ASSERT_LT(out_vertices[3 * 966].y, 0.24609375);
    ASSERT_GT(out_vertices[3 * 966].z, 0.7578125);
    ASSERT_LT(out_vertices[3 * 966].z, 0.76171875);
}
