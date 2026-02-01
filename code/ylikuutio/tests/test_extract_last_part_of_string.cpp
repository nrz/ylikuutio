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
#include "code/ylikuutio/string/ylikuutio_string.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <string>   // std::string

TEST(extract_last_part_of_string_std_string, nothing_must_be_extracted_when_source_string_is_empty_string)
{
    const std::string my_string = "";
    const char separator = 'a';

    std::string dest_string = yli::string::extract_last_part_of_string<char>(my_string, separator);
    ASSERT_TRUE(dest_string.empty());
}

TEST(extract_last_part_of_string_std_string, nothing_must_be_extracted_when_source_string_is_1_char_and_has_no_separator)
{
    const std::string my_string = "a";
    const char separator = 'b';

    std::string dest_string = yli::string::extract_last_part_of_string<char>(my_string, separator);
    ASSERT_TRUE(dest_string.empty());
}

TEST(extract_last_part_of_string_std_string, nothing_must_be_extracted_when_source_string_is_2_same_chars_and_has_no_separator)
{
    const std::string my_string = "aa";
    const char separator = 'b';

    std::string dest_string = yli::string::extract_last_part_of_string<char>(my_string, separator);
    ASSERT_TRUE(dest_string.empty());
}

TEST(extract_last_part_of_string_std_string, nothing_must_be_extracted_when_source_string_is_2_different_chars_and_has_no_separator)
{
    const std::string my_string = "ab";
    const char separator = 'c';

    std::string dest_string = yli::string::extract_last_part_of_string<char>(my_string, separator);
    ASSERT_TRUE(dest_string.empty());
}

TEST(extract_last_part_of_string_std_string, nothing_must_be_extracted_when_source_string_is_3_different_chars_and_has_no_separator)
{
    const std::string my_string = "abc";
    const char separator = 'd';

    std::string dest_string = yli::string::extract_last_part_of_string<char>(my_string, separator);
    ASSERT_TRUE(dest_string.empty());
}

TEST(extract_last_part_of_string_std_string, nothing_must_be_extracted_when_source_string_is_2_same_chars_and_separator_is_the_last_char)
{
    const std::string my_string = "ab";
    const char separator = 'b';

    std::string dest_string = yli::string::extract_last_part_of_string<char>(my_string, separator);
    ASSERT_TRUE(dest_string.empty());
}

TEST(extract_last_part_of_string_std_string, nothing_must_be_extracted_when_source_string_is_2_same_chars_and_separator_is_the_same_char)
{
    const std::string my_string = "aa";
    const char separator = 'a';

    std::string dest_string = yli::string::extract_last_part_of_string<char>(my_string, separator);
    ASSERT_TRUE(dest_string.empty());
}

TEST(extract_last_part_of_string_std_string, nothing_must_be_extracted_when_source_string_is_3_same_chars_and_separator_is_the_same_char)
{
    const std::string my_string = "aaa";
    const char separator = 'a';

    std::string dest_string = yli::string::extract_last_part_of_string<char>(my_string, separator);
    ASSERT_TRUE(dest_string.empty());
}

TEST(extract_last_part_of_string_std_string, 1_char_must_be_extracted_when_source_string_is_2_different_chars_and_separator_is_the_first_char)
{
    const std::string my_string = "ab";
    const char separator = 'a';

    std::string dest_string = yli::string::extract_last_part_of_string<char>(my_string, separator);
    ASSERT_EQ(dest_string, "b");
}

TEST(extract_last_part_of_string_std_string, nothing_must_be_extracted_when_source_string_is_3_different_chars_and_separator_is_the_last_char)
{
    const std::string my_string = "abc";
    const char separator = 'c';

    std::string dest_string = yli::string::extract_last_part_of_string<char>(my_string, separator);
    ASSERT_TRUE(dest_string.empty());
}

TEST(extract_last_part_of_string_std_string, 1_char_must_be_extracted_when_source_string_is_3_different_chars_and_separator_is_the_second_char)
{
    const std::string my_string = "abc";
    const char separator = 'b';

    std::string dest_string = yli::string::extract_last_part_of_string<char>(my_string, separator);
    ASSERT_EQ(dest_string, "c");
}

TEST(extract_last_part_of_string_std_string, 2_chars_must_be_extracted_when_source_string_is_3_different_chars_and_separator_is_the_first_char)
{
    const std::string my_string = "abc";
    const char separator = 'a';

    std::string dest_string = yli::string::extract_last_part_of_string<char>(my_string, separator);
    ASSERT_EQ(dest_string, "bc");
}
