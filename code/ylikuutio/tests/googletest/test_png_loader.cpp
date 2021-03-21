// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2021 Antti Nuortimo.
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
#include "code/ylikuutio/load/image_file_loader.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <memory>   // std::make_shared, std::shared_ptr
#include <string>   // std::string
#include <vector>   // std::vector

TEST(png_files_must_be_loaded_approriately, test3x3_png)
{
    const std::string image_path = "test3x3.png";
    std::size_t image_width;
    std::size_t image_height;
    std::size_t image_size;

    std::shared_ptr<std::vector<uint8_t>> image_data = yli::load::load_image_file(image_path, image_width, image_height, image_size);
    ASSERT_NE(image_data, nullptr);
    ASSERT_EQ((*image_data)[0], 0);
    ASSERT_EQ((*image_data)[1], 0);
    ASSERT_EQ((*image_data)[2], 0);

    ASSERT_EQ((*image_data)[3], 1);
    ASSERT_EQ((*image_data)[4], 1);
    ASSERT_EQ((*image_data)[5], 1);

    ASSERT_EQ((*image_data)[6], 2);
    ASSERT_EQ((*image_data)[7], 2);
    ASSERT_EQ((*image_data)[8], 2);

    ASSERT_EQ((*image_data)[9], 4);
    ASSERT_EQ((*image_data)[10], 4);
    ASSERT_EQ((*image_data)[11], 4);

    ASSERT_EQ((*image_data)[12], 8);
    ASSERT_EQ((*image_data)[13], 8);
    ASSERT_EQ((*image_data)[14], 8);

    ASSERT_EQ((*image_data)[15], 16);
    ASSERT_EQ((*image_data)[16], 16);
    ASSERT_EQ((*image_data)[17], 16);

    ASSERT_EQ((*image_data)[18], 32);
    ASSERT_EQ((*image_data)[19], 32);
    ASSERT_EQ((*image_data)[20], 32);

    ASSERT_EQ((*image_data)[21], 64);
    ASSERT_EQ((*image_data)[22], 64);
    ASSERT_EQ((*image_data)[23], 64);

    ASSERT_EQ((*image_data)[24], 128);
    ASSERT_EQ((*image_data)[25], 128);
    ASSERT_EQ((*image_data)[26], 128);
}
