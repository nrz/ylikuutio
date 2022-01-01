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
#include "code/ylikuutio/load/image_file_loader.hpp"
#include "code/ylikuutio/load/image_loader_struct.hpp"

// Include standard headers
#include <memory>   // std::make_shared, std::shared_ptr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

TEST(grayscale_8_bit_png_files_must_be_loaded_approriately_as_grayscale, test3x3_png)
{
    const std::string image_path = "test3x3.png";
    uint32_t image_width;
    uint32_t image_height;
    uint32_t image_size;
    uint32_t n_color_channels;

    yli::load::ImageLoaderStruct image_loader_struct;
    std::shared_ptr<std::vector<uint8_t>> image_data = yli::load::load_image_file(image_path, image_loader_struct, image_width, image_height, image_size, n_color_channels);
    ASSERT_NE(image_data, nullptr);
    ASSERT_EQ(image_data->size(), 9);
    ASSERT_EQ(image_width, 3);
    ASSERT_EQ(image_height, 3);
    ASSERT_EQ(image_size, 9);
    ASSERT_EQ(n_color_channels, 1);
    ASSERT_EQ((*image_data)[0], 32);
    ASSERT_EQ((*image_data)[1], 64);
    ASSERT_EQ((*image_data)[2], 128);
    ASSERT_EQ((*image_data)[3], 4);
    ASSERT_EQ((*image_data)[4], 8);
    ASSERT_EQ((*image_data)[5], 16);
    ASSERT_EQ((*image_data)[6], 0);
    ASSERT_EQ((*image_data)[7], 1);
    ASSERT_EQ((*image_data)[8], 2);
}

TEST(grayscale_8_bit_png_files_must_be_loaded_approriately_as_rgb, test3x3_png)
{
    const std::string image_path = "test3x3.png";
    uint32_t image_width;
    uint32_t image_height;
    uint32_t image_size;
    uint32_t n_color_channels;

    yli::load::ImageLoaderStruct image_loader_struct;
    image_loader_struct.should_convert_grayscale_to_rgb = true;
    std::shared_ptr<std::vector<uint8_t>> image_data = yli::load::load_image_file(image_path, image_loader_struct, image_width, image_height, image_size, n_color_channels);
    ASSERT_NE(image_data, nullptr);
    ASSERT_EQ(image_data->size(), 27);
    ASSERT_EQ(image_width, 3);
    ASSERT_EQ(image_height, 3);
    ASSERT_EQ(image_size, 9);
    ASSERT_EQ(n_color_channels, 3);
    ASSERT_EQ((*image_data)[0], 32);
    ASSERT_EQ((*image_data)[1], 32);
    ASSERT_EQ((*image_data)[2], 32);
    ASSERT_EQ((*image_data)[3], 64);
    ASSERT_EQ((*image_data)[4], 64);
    ASSERT_EQ((*image_data)[5], 64);
    ASSERT_EQ((*image_data)[6], 128);
    ASSERT_EQ((*image_data)[7], 128);
    ASSERT_EQ((*image_data)[8], 128);
    ASSERT_EQ((*image_data)[9], 4);
    ASSERT_EQ((*image_data)[10], 4);
    ASSERT_EQ((*image_data)[11], 4);
    ASSERT_EQ((*image_data)[12], 8);
    ASSERT_EQ((*image_data)[13], 8);
    ASSERT_EQ((*image_data)[14], 8);
    ASSERT_EQ((*image_data)[15], 16);
    ASSERT_EQ((*image_data)[16], 16);
    ASSERT_EQ((*image_data)[17], 16);
    ASSERT_EQ((*image_data)[18], 0);
    ASSERT_EQ((*image_data)[19], 0);
    ASSERT_EQ((*image_data)[20], 0);
    ASSERT_EQ((*image_data)[21], 1);
    ASSERT_EQ((*image_data)[22], 1);
    ASSERT_EQ((*image_data)[23], 1);
    ASSERT_EQ((*image_data)[24], 2);
    ASSERT_EQ((*image_data)[25], 2);
    ASSERT_EQ((*image_data)[26], 2);
}
