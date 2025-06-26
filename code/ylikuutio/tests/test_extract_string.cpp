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
#include "code/ylikuutio/string/ylikuutio_string.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <string>   // std::string

TEST(extract_string_from_memory, nothing_must_be_extracted_when_data_string_is_empty_string)
{
    const std::string data_string = "";
    std::size_t data_index = 0;
    const char separator = 'a';
    std::string dest_string = yli::string::extract_string<char>(data_string, data_index, separator);
    ASSERT_TRUE(dest_string.empty());
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_from_memory, nothing_must_be_extracted_when_separator_matches_1st_char_of_data_string)
{
    const std::string data_string = "a";
    std::size_t data_index = 0;
    const char separator = 'a';
    std::string dest_string = yli::string::extract_string<char>(data_string, data_index, separator);
    ASSERT_TRUE(dest_string.empty());
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_from_memory, 1_char_must_be_extracted_when_separator_does_not_match_and_data_string_size_is_1)
{
    const std::string data_string = "a";
    std::size_t data_index = 0;
    const char separator = 'b';
    std::string dest_string = yli::string::extract_string<char>(data_string, data_index, separator);
    ASSERT_EQ(dest_string, "a");
    ASSERT_EQ(data_index, 1);
}

TEST(extract_string_from_memory, 2_chars_must_be_extracted_when_separator_does_not_match_and_data_string_size_is_2)
{
    const std::string data_string = "ab";
    std::size_t data_index = 0;
    const char separator = 'c';
    std::string dest_string = yli::string::extract_string<char>(data_string, data_index, separator);
    ASSERT_EQ(dest_string, "ab");
    ASSERT_EQ(data_index, 2);
}

TEST(extract_string_from_memory, 1_char_must_be_extracted_when_separator_matches_2nd_char_of_data_string)
{
    const std::string data_string = "ab";
    std::size_t data_index = 0;
    const char separator = 'b';
    std::string dest_string = yli::string::extract_string<char>(data_string, data_index, separator);
    ASSERT_EQ(dest_string, "a");
    ASSERT_EQ(data_index, 1);
}

TEST(extract_string_from_memory, 2_char_must_be_extracted_when_separator_matches_3rd_char_of_data_string)
{
    const std::string data_string = "abc";
    std::size_t data_index = 0;
    const char separator = 'c';
    std::string dest_string = yli::string::extract_string<char>(data_string, data_index, separator);
    ASSERT_EQ(dest_string, "ab");
    ASSERT_EQ(data_index, 2);
}

TEST(extract_string_from_memory, nothing_must_be_extracted_when_data_string_is_empty_and_data_index_is_out_of_bounds)
{
    const std::string data_string = "";
    std::size_t data_index = 1;
    const char separator = 'a';
    std::string dest_string = yli::string::extract_string<char>(data_string, data_index, separator);
    ASSERT_TRUE(dest_string.empty());
    ASSERT_EQ(data_index, 1);
}

TEST(extract_string_from_memory, nothing_must_be_extracted_when_data_string_is_1_char_and_data_index_is_out_of_bounds)
{
    const std::string data_string = "a";
    std::size_t data_index = 2;
    const char separator = 'b';
    std::string dest_string = yli::string::extract_string<char>(data_string, data_index, separator);
    ASSERT_TRUE(dest_string.empty());
    ASSERT_EQ(data_index, 2);
}

TEST(extract_string_from_memory, nothing_must_be_extracted_when_data_string_is_2_chars_and_data_index_is_out_of_bounds)
{
    const std::string data_string = "ab";
    std::size_t data_index = 2;
    const char separator = 'c';
    std::string dest_string = yli::string::extract_string<char>(data_string, data_index, separator);
    ASSERT_TRUE(dest_string.empty());
    ASSERT_EQ(data_index, 2);
}
