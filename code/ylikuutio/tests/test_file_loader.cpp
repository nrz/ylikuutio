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
#include "code/ylikuutio/file/file_loader.hpp"
#include "code/ylikuutio/memory/memory_templates.hpp"

// Include standard headers
#include <optional> // std::optional
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

TEST(file_must_be_slurped_appropriately, this_file_does_not_exist_at_all)
{
    std::optional<std::string> file_content = yli::file::slurp("this_file_does_not_exist_at_all");
    ASSERT_FALSE(file_content);
}

TEST(binary_file_must_be_slurped_appropriately, this_file_does_not_exist_at_all)
{
    std::optional<std::vector<uint8_t>> file_content = yli::file::binary_slurp("this_file_does_not_exist_at_all");
    ASSERT_FALSE(file_content);
}

TEST(file_must_be_slurped_appropriately, kongtext_svg)
{
    std::optional<std::string> file_content = yli::file::slurp("kongtext.svg");
    ASSERT_TRUE(file_content);
    const std::string first_line_of_kongtext_svg = "<?xml version=\"1.0\" standalone=\"no\"?>";
    const uint32_t length_of_first_line_of_kongtext_svg = first_line_of_kongtext_svg.size();
    ASSERT_EQ(file_content->compare(0, length_of_first_line_of_kongtext_svg, first_line_of_kongtext_svg), 0);

    const uint32_t offset_of_first_character_of_tenth_line = 0x126;
    const std::string tenth_line_of_kongtext_svg = "<font id=\"KongtextRegular\" horiz-adv-x=\"1024\" >";
    const uint32_t length_of_tenth_line_of_kongtext_svg = tenth_line_of_kongtext_svg.size();
    ASSERT_EQ(file_content->compare(offset_of_first_character_of_tenth_line, length_of_tenth_line_of_kongtext_svg, tenth_line_of_kongtext_svg), 0);
}

TEST(file_must_be_slurped_appropriately, test3x3_png)
{
    const std::string png_filename = "test3x3.png";
    std::optional<std::vector<uint8_t>> file_content = yli::file::binary_slurp(png_filename);
    ASSERT_TRUE(file_content);
    ASSERT_EQ(file_content->size(), 229);
    const uint16_t* file_content_uint16_t = (uint16_t*) file_content->data();

    // a PNG file begins with 0x89, 0x50, 0x4e, 0x47.
    ASSERT_EQ((*file_content)[0], 0x89);
    ASSERT_EQ((*file_content)[1], 'P');
    ASSERT_EQ((*file_content)[2], 'N');
    ASSERT_EQ((*file_content)[3], 'G');
    ASSERT_EQ((*file_content)[4], 0x0d);
    ASSERT_EQ((*file_content)[5], 0x0a);
    ASSERT_EQ((*file_content)[6], 0x1a);
    ASSERT_EQ((*file_content)[7], 0x0a);
}
