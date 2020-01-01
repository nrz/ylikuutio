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
#include "code/ylikuutio/file/file_loader.hpp"
#include "code/ylikuutio/memory/memory_templates.hpp"

// Include standard headers
#include <memory>   // std::make_shared, std::shared_ptr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

TEST(file_must_be_slurped_appropriately, this_file_does_not_exist_at_all)
{
    std::shared_ptr<std::string> file_content = yli::file::slurp("this_file_does_not_exist_at_all");
    ASSERT_EQ(file_content, nullptr);
}

TEST(binary_file_must_be_slurped_appropriately, this_file_does_not_exist_at_all)
{
    std::shared_ptr<std::vector<uint8_t>> file_content = yli::file::binary_slurp("this_file_does_not_exist_at_all");
    ASSERT_EQ(file_content, nullptr);
}

TEST(file_must_be_slurped_appropriately, kongtext_svg)
{
    std::shared_ptr<std::string> file_content = yli::file::slurp("kongtext.svg");
    const std::string first_line_of_kongtext_svg = "<?xml version=\"1.0\" standalone=\"no\"?>";
    const uint32_t length_of_first_line_of_kongtext_svg = first_line_of_kongtext_svg.size();
    ASSERT_EQ(file_content->compare(0, length_of_first_line_of_kongtext_svg, first_line_of_kongtext_svg), 0);

    const uint32_t offset_of_first_character_of_tenth_line = 0x126;
    const std::string tenth_line_of_kongtext_svg = "<font id=\"KongtextRegular\" horiz-adv-x=\"1024\" >";
    const uint32_t length_of_tenth_line_of_kongtext_svg = tenth_line_of_kongtext_svg.size();
    ASSERT_EQ(file_content->compare(offset_of_first_character_of_tenth_line, length_of_tenth_line_of_kongtext_svg, tenth_line_of_kongtext_svg), 0);
}

TEST(file_must_be_slurped_appropriately, test3x3_bmp)
{
    const std::string bmp_filename = "test3x3.bmp";
    std::shared_ptr<std::vector<uint8_t>> file_content = yli::file::binary_slurp(bmp_filename);
    ASSERT_NE(file_content, nullptr);
    const uint16_t* file_content_uint16_t = (uint16_t*) file_content->data();

    // a BMP file always begins with "BM".
    ASSERT_EQ((*file_content)[0], 'B');
    ASSERT_EQ((*file_content)[1], 'M');

    // size of file (0x9e == 158 bytes)
    ASSERT_EQ(file_content_uint16_t[2 / sizeof(uint16_t)], 0x9e);
    ASSERT_EQ(file_content_uint16_t[4 / sizeof(uint16_t)], 0);
    ASSERT_EQ(file_content_uint16_t[0x1a / sizeof(uint16_t)], 1); // number of color planes (must be 1)

    const uint32_t magic_number_and_file_size = yli::memory::read_nonaligned_32_bit<uint8_t, uint32_t>(file_content->data(), 0);
    ASSERT_EQ(magic_number_and_file_size, 0x9e4d42);

    const int32_t image_width = yli::memory::read_nonaligned_32_bit<uint8_t, int32_t>(file_content->data(), 0x12); // bitmap width in pixels (`int32_t`).
    ASSERT_EQ(image_width, 3);

    const int32_t image_height = yli::memory::read_nonaligned_32_bit<uint8_t, int32_t>(file_content->data(), 0x16); // bitmap height in pixels (`int32_t`).
    ASSERT_EQ(image_height, 3);

    const uint32_t image_size = yli::memory::read_nonaligned_32_bit<uint8_t, uint32_t>(file_content->data(), 0x22); // image size.
    ASSERT_EQ(image_size, 36);
}
