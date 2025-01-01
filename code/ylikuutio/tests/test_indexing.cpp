// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2025 Antti Nuortimo.
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
#include "code/ylikuutio/triangulation/indexing.hpp"
#include "code/ylikuutio/triangulation/triangulation_enums.hpp"

// Include standard headers
#include <cstddef>  // std::size_t

TEST(face_indices_must_be_computed_appropriately, a_4x4_terrain)
{
    // Face indices example for a 4x4 image file using bilinear interpolation.
    //
    //  +-------+-------+-------+
    //  |\ 26  /|\ 30  /|\ 34  /|
    //  | \   / | \   / | \   / |
    //  |  \ /  |  \ /  |  \ /  |
    //  |25 x 27|29 x 31|33 x 35|
    //  |  / \  |  / \  |  / \  |
    //  | /   \ | /   \ | /   \ |
    //  |/ 24  \|/ 28  \|/ 32  \|
    //  +-------+-------+-------+
    //  |\ 14  /|\ 18  /|\ 22  /|
    //  | \   / | \   / | \   / |
    //  |  \ /  |  \ /  |  \ /  |
    //  |13 x 15|17 x 19|21 x 23|
    //  |  / \  |  / \  |  / \  |
    //  | /   \ | /   \ | /   \ |
    //  |/ 12  \|/ 16  \|/ 20  \|
    //  +-------+-------+-------+
    //  |\  2  /|\  6  /|\ 10  /|
    //  | \   / | \   / | \   / |
    //  |  \ /  |  \ /  |  \ /  |
    //  |1  x  3|5  x  7|9  x 11|
    //  |  / \  |  / \  |  / \  |
    //  | /   \ | /   \ | /   \ |
    //  |/  0  \|/  4  \|/  8  \|
    //  +-------+-------+-------+

    const std::size_t example_width = 4;
    // x = 0, z = 0.
    ASSERT_EQ(yli::triangulation::get_face_normal_i(0, 0, yli::triangulation::BilinearDirections::ENE, example_width), 0);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(0, 0, yli::triangulation::BilinearDirections::NNE, example_width), 1);

    // x = 1, z = 0.
    ASSERT_EQ(yli::triangulation::get_face_normal_i(1, 0, yli::triangulation::BilinearDirections::WNW, example_width), 0);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(1, 0, yli::triangulation::BilinearDirections::NNW, example_width), 3);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(1, 0, yli::triangulation::BilinearDirections::NNE, example_width), 5);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(1, 0, yli::triangulation::BilinearDirections::ENE, example_width), 4);

    // x = 2, z = 0.
    ASSERT_EQ(yli::triangulation::get_face_normal_i(2, 0, yli::triangulation::BilinearDirections::WNW, example_width), 4);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(2, 0, yli::triangulation::BilinearDirections::NNW, example_width), 7);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(2, 0, yli::triangulation::BilinearDirections::NNE, example_width), 9);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(2, 0, yli::triangulation::BilinearDirections::ENE, example_width), 8);

    // x = 3, z = 0.
    ASSERT_EQ(yli::triangulation::get_face_normal_i(3, 0, yli::triangulation::BilinearDirections::WNW, example_width), 8);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(3, 0, yli::triangulation::BilinearDirections::NNW, example_width), 11);

    // x = 0, z = 1.
    ASSERT_EQ(yli::triangulation::get_face_normal_i(0, 1, yli::triangulation::BilinearDirections::NNE, example_width), 13);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(0, 1, yli::triangulation::BilinearDirections::ENE, example_width), 12);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(0, 1, yli::triangulation::BilinearDirections::ESE, example_width), 2);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(0, 1, yli::triangulation::BilinearDirections::SSE, example_width), 1);

    // x = 1, z = 1.
    ASSERT_EQ(yli::triangulation::get_face_normal_i(1, 1, yli::triangulation::BilinearDirections::NNE, example_width), 17);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(1, 1, yli::triangulation::BilinearDirections::ENE, example_width), 16);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(1, 1, yli::triangulation::BilinearDirections::ESE, example_width), 6);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(1, 1, yli::triangulation::BilinearDirections::SSE, example_width), 5);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(1, 1, yli::triangulation::BilinearDirections::SSW, example_width), 3);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(1, 1, yli::triangulation::BilinearDirections::WSW, example_width), 2);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(1, 1, yli::triangulation::BilinearDirections::WNW, example_width), 12);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(1, 1, yli::triangulation::BilinearDirections::NNW, example_width), 15);

    // x = 2, z = 1.
    ASSERT_EQ(yli::triangulation::get_face_normal_i(2, 1, yli::triangulation::BilinearDirections::NNE, example_width), 21);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(2, 1, yli::triangulation::BilinearDirections::ENE, example_width), 20);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(2, 1, yli::triangulation::BilinearDirections::ESE, example_width), 10);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(2, 1, yli::triangulation::BilinearDirections::SSE, example_width), 9);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(2, 1, yli::triangulation::BilinearDirections::SSW, example_width), 7);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(2, 1, yli::triangulation::BilinearDirections::WSW, example_width), 6);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(2, 1, yli::triangulation::BilinearDirections::WNW, example_width), 16);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(2, 1, yli::triangulation::BilinearDirections::NNW, example_width), 19);

    // x = 3, z = 1.
    ASSERT_EQ(yli::triangulation::get_face_normal_i(3, 1, yli::triangulation::BilinearDirections::SSW, example_width), 11);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(3, 1, yli::triangulation::BilinearDirections::WSW, example_width), 10);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(3, 1, yli::triangulation::BilinearDirections::WNW, example_width), 20);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(3, 1, yli::triangulation::BilinearDirections::NNW, example_width), 23);

    // x = 0, z = 2.
    ASSERT_EQ(yli::triangulation::get_face_normal_i(0, 2, yli::triangulation::BilinearDirections::NNE, example_width), 25);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(0, 2, yli::triangulation::BilinearDirections::ENE, example_width), 24);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(0, 2, yli::triangulation::BilinearDirections::ESE, example_width), 14);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(0, 2, yli::triangulation::BilinearDirections::SSE, example_width), 13);

    // x = 1, z = 2.
    ASSERT_EQ(yli::triangulation::get_face_normal_i(1, 2, yli::triangulation::BilinearDirections::NNE, example_width), 29);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(1, 2, yli::triangulation::BilinearDirections::ENE, example_width), 28);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(1, 2, yli::triangulation::BilinearDirections::ESE, example_width), 18);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(1, 2, yli::triangulation::BilinearDirections::SSE, example_width), 17);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(1, 2, yli::triangulation::BilinearDirections::SSW, example_width), 15);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(1, 2, yli::triangulation::BilinearDirections::WSW, example_width), 14);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(1, 2, yli::triangulation::BilinearDirections::WNW, example_width), 24);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(1, 2, yli::triangulation::BilinearDirections::NNW, example_width), 27);

    // x = 2, z = 2.
    ASSERT_EQ(yli::triangulation::get_face_normal_i(2, 2, yli::triangulation::BilinearDirections::NNE, example_width), 33);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(2, 2, yli::triangulation::BilinearDirections::ENE, example_width), 32);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(2, 2, yli::triangulation::BilinearDirections::ESE, example_width), 22);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(2, 2, yli::triangulation::BilinearDirections::SSE, example_width), 21);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(2, 2, yli::triangulation::BilinearDirections::SSW, example_width), 19);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(2, 2, yli::triangulation::BilinearDirections::WSW, example_width), 18);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(2, 2, yli::triangulation::BilinearDirections::WNW, example_width), 28);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(2, 2, yli::triangulation::BilinearDirections::NNW, example_width), 31);

    // x = 3, z = 2.
    ASSERT_EQ(yli::triangulation::get_face_normal_i(3, 2, yli::triangulation::BilinearDirections::SSW, example_width), 23);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(3, 2, yli::triangulation::BilinearDirections::WSW, example_width), 22);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(3, 2, yli::triangulation::BilinearDirections::WNW, example_width), 32);
    ASSERT_EQ(yli::triangulation::get_face_normal_i(3, 2, yli::triangulation::BilinearDirections::NNW, example_width), 35);
}
