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
#include <cstddef>     // std::size_t
#include <string>      // std::string
#include <string_view> // std::string_view

TEST(extract_string_with_several_endings_from_memory_std_string, nothing_must_be_extracted_when_source_string_is_empty_string_and_end_string_is_empty_string)
{
    std::string_view text { "" };
    std::size_t data_index = 0;

    std::string_view end_string { "" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_TRUE(dest_string.empty());
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, nothing_must_be_extracted_when_source_string_is_empty_string_and_end_string_is_1_char)
{
    std::string_view text { "" };
    std::size_t data_index = 0;

    std::string_view end_string { "a" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_TRUE(dest_string.empty());
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, nothing_must_be_extracted_when_source_string_is_empty_string_and_end_string_is_2_same_chars)
{
    std::string_view text { "" };
    std::size_t data_index = 0;

    std::string_view end_string { "aa" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_TRUE(dest_string.empty());
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, nothing_must_be_extracted_when_source_string_is_empty_string_and_end_string_is_2_different_chars)
{
    std::string_view text { "" };
    std::size_t data_index = 0;

    std::string_view end_string { "ab" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_TRUE(dest_string.empty());
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, nothing_must_be_extracted_when_source_string_is_1_char_and_end_string_is_matching_1_char)
{
    std::string_view text { "a" };
    std::size_t data_index = 0;

    std::string_view end_string { "a" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_TRUE(dest_string.empty());
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, nothing_must_be_extracted_when_source_string_is_1_char_and_first_char_of_end_string_matches_1st_char)
{
    std::string_view text { "a" };
    std::size_t data_index = 0;

    std::string_view end_string { "ab" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_TRUE(dest_string.empty());
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, nothing_must_be_extracted_when_source_string_is_1_char_and_second_char_of_end_string_matches_1st_char)
{
    std::string_view text { "a" };
    std::size_t data_index = 0;

    std::string_view end_string { "ba" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_TRUE(dest_string.empty());
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, nothing_must_be_extracted_when_source_string_is_1_char_and_both_chars_of_end_string_match_1st_char)
{
    std::string_view text { "a" };
    std::size_t data_index = 0;

    std::string_view end_string { "aa" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_TRUE(dest_string.empty());
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, 1_char_must_be_extracted_when_source_string_is_1_char_and_end_string_is_different_1_char)
{
    std::string_view text { "a" };
    std::size_t data_index = 0;

    std::string_view end_string { "b" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 1);
    ASSERT_EQ(dest_string, "a");
    ASSERT_EQ(data_index, 1);
}

TEST(extract_string_with_several_endings_from_memory_std_string, nothing_must_be_extracted_when_source_string_is_2_chars_and_end_string_is_same_as_1st_char)
{
    std::string_view text { "ab" };
    std::size_t data_index = 0;

    std::string_view end_string { "a" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_TRUE(dest_string.empty());
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_with_several_endings_from_memory, nothing_must_be_extracted_when_source_string_is_2_chars_and_end_string_is_same_as_1st_and_2nd_char)
{
    std::string_view text { "aa" };
    std::size_t data_index = 0;

    std::string_view end_string { "a" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_TRUE(dest_string.empty());
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, nothing_must_be_extracted_when_source_string_is_2_chars_and_end_string_is_same_as_1st_and_2nd_char)
{
    std::string_view text { "aa" };
    std::size_t data_index = 0;

    std::string_view end_string { "a" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_TRUE(dest_string.empty());
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, nothing_must_be_extracted_when_source_string_is_2_chars_and_end_string_is_same_as_1st_and_2nd_char)
{
    std::string_view text { "aa" };
    std::size_t data_index = 0;

    std::string_view end_string { "a" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_TRUE(dest_string.empty());
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_with_several_endings_from_memory, 1_char_must_be_extracted_when_source_string_is_2_chars_and_end_string_is_same_as_2nd_char)
{
    std::string_view text { "ab" };
    std::size_t data_index = 0;

    std::string_view end_string { "b" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 1);
    ASSERT_EQ(dest_string, "a");
    ASSERT_EQ(data_index, 1);
}

TEST(extract_string_with_several_endings_from_memory_std_string, 1_char_must_be_extracted_when_source_string_is_2_chars_and_end_string_is_same_as_2nd_char)
{
    std::string_view text { "ab" };
    std::size_t data_index = 0;

    std::string_view end_string { "b" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 1);
    ASSERT_EQ(dest_string, "a");
    ASSERT_EQ(data_index, 1);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, 1_char_must_be_extracted_when_source_string_is_2_chars_and_end_string_is_same_as_2nd_char)
{
    std::string_view text { "ab" };
    std::size_t data_index = 0;

    std::string_view end_string { "b" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 1);
    ASSERT_EQ(dest_string, "a");
    ASSERT_EQ(data_index, 1);
}

TEST(extract_string_with_several_endings_from_memory, 1_char_must_be_extracted_when_source_string_is_2_chars_and_first_char_of_end_string_is_same_as_2nd_char)
{
    std::string_view text { "ab" };
    std::size_t data_index = 0;

    std::string_view end_string { "bc" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 1);
    ASSERT_EQ(dest_string, "a");
    ASSERT_EQ(data_index, 1);
}

TEST(extract_string_with_several_endings_from_memory_std_string, 1_char_must_be_extracted_when_source_string_is_2_chars_and_first_char_of_end_string_is_same_as_2nd_char)
{
    std::string_view text { "ab" };
    std::size_t data_index = 0;

    std::string_view end_string { "bc" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 1);
    ASSERT_EQ(dest_string, "a");
    ASSERT_EQ(data_index, 1);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, 1_char_must_be_extracted_when_source_string_is_2_chars_and_first_char_of_end_string_is_same_as_2nd_char)
{
    std::string_view text { "ab" };
    std::size_t data_index = 0;

    std::string_view end_string { "bc" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 1);
    ASSERT_EQ(dest_string, "a");
    ASSERT_EQ(data_index, 1);
}

TEST(extract_string_with_several_endings_from_memory, 1_char_must_be_extracted_when_source_string_is_2_chars_and_second_char_of_end_string_is_same_as_2nd_char)
{
    std::string_view text { "ab" };
    std::size_t data_index = 0;

    std::string_view end_string { "cb" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 1);
    ASSERT_EQ(dest_string, "a");
    ASSERT_EQ(data_index, 1);
}

TEST(extract_string_with_several_endings_from_memory_std_string, 1_char_must_be_extracted_when_source_string_is_2_chars_and_second_char_of_end_string_is_same_as_2nd_char)
{
    std::string_view text { "ab" };
    std::size_t data_index = 0;

    std::string_view end_string { "cb" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 1);
    ASSERT_EQ(dest_string, "a");
    ASSERT_EQ(data_index, 1);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, 1_char_must_be_extracted_when_source_string_is_2_chars_and_second_char_of_end_string_is_same_as_2nd_char)
{
    std::string_view text { "ab" };
    std::size_t data_index = 0;

    std::string_view end_string { "cb" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 1);
    ASSERT_EQ(dest_string, "a");
    ASSERT_EQ(data_index, 1);
}

TEST(extract_string_with_several_endings_from_memory, 1_char_must_be_extracted_when_source_string_is_2_chars_and_both_chars_of_end_string_are_same_as_2nd_char)
{
    std::string_view text { "ab" };
    std::size_t data_index = 0;

    std::string_view end_string { "bb" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 1);
    ASSERT_EQ(dest_string, "a");
    ASSERT_EQ(data_index, 1);
}

TEST(extract_string_with_several_endings_from_memory_std_string, 1_char_must_be_extracted_when_source_string_is_2_chars_and_both_chars_of_end_string_are_same_as_2nd_char)
{
    std::string_view text { "ab" };
    std::size_t data_index = 0;

    std::string_view end_string { "bb" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 1);
    ASSERT_EQ(dest_string, "a");
    ASSERT_EQ(data_index, 1);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, 1_char_must_be_extracted_when_source_string_is_2_chars_and_both_chars_of_end_string_are_same_as_2nd_char)
{
    std::string_view text { "ab" };
    std::size_t data_index = 0;

    std::string_view end_string { "bb" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 1);
    ASSERT_EQ(dest_string, "a");
    ASSERT_EQ(data_index, 1);
}

TEST(extract_string_with_several_endings_from_memory, 2_chars_must_be_extracted_when_source_string_is_2_chars_and_end_string_is_different_1_char)
{
    std::string_view text { "ab" };
    std::size_t data_index = 0;

    std::string_view end_string { "c" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 2);
    ASSERT_EQ(dest_string, "ab");
    ASSERT_EQ(data_index, 2);
}

TEST(extract_string_with_several_endings_from_memory_std_string, 2_chars_must_be_extracted_when_source_string_is_2_chars_and_end_string_is_different_1_char)
{
    std::string_view text { "ab" };
    std::size_t data_index = 0;

    std::string_view end_string { "c" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 2);
    ASSERT_EQ(dest_string, "ab");
    ASSERT_EQ(data_index, 2);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, 2_chars_must_be_extracted_when_source_string_is_2_chars_and_end_string_is_different_1_char)
{
    std::string_view text { "ab" };
    std::size_t data_index = 0;

    std::string_view end_string { "c" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 2);
    ASSERT_EQ(dest_string, "ab");
    ASSERT_EQ(data_index, 2);
}

TEST(extract_string_with_several_endings_from_memory, nothing_must_be_extracted_when_source_string_is_3_chars_and_end_string_is_same_as_1st_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "a" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_TRUE(dest_string.empty());
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, nothing_must_be_extracted_when_source_string_is_3_chars_and_end_string_is_same_as_1st_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "a" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_TRUE(dest_string.empty());
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, nothing_must_be_extracted_when_source_string_is_3_chars_and_end_string_is_same_as_1st_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "a" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_TRUE(dest_string.empty());
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_with_several_endings_from_memory, 1_char_must_be_extracted_when_source_string_is_3_chars_and_end_string_is_same_as_2nd_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "b" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 1);
    ASSERT_EQ(dest_string, "a");
    ASSERT_EQ(data_index, 1);
}

TEST(extract_string_with_several_endings_from_memory_std_string, 1_char_must_be_extracted_when_source_string_is_3_chars_and_end_string_is_same_as_2nd_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "b" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 1);
    ASSERT_EQ(dest_string, "a");
    ASSERT_EQ(data_index, 1);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, 1_char_must_be_extracted_when_source_string_is_3_chars_and_end_string_is_same_as_2nd_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "b" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 1);
    ASSERT_EQ(dest_string, "a");
    ASSERT_EQ(data_index, 1);
}

TEST(extract_string_with_several_endings_from_memory, 2_chars_must_be_extracted_when_source_string_is_3_chars_and_end_string_is_same_as_3rd_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "c" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 2);
    ASSERT_EQ(dest_string, "ab");
    ASSERT_EQ(data_index, 2);
}

TEST(extract_string_with_several_endings_from_memory_std_string, 2_chars_must_be_extracted_when_source_string_is_3_chars_and_end_string_is_same_as_3rd_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "c" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 2);
    ASSERT_EQ(dest_string, "ab");
    ASSERT_EQ(data_index, 2);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, 2_chars_must_be_extracted_when_source_string_is_3_chars_and_end_string_is_same_as_3rd_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "c" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 2);
    ASSERT_EQ(dest_string, "ab");
    ASSERT_EQ(data_index, 2);
}

TEST(extract_string_with_several_endings_from_memory, 3_chars_must_be_extracted_when_source_string_is_3_chars_and_end_string_is_a_different_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "d" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 3);
    ASSERT_EQ(dest_string, "abc");
    ASSERT_EQ(data_index, 3);
}

TEST(extract_string_with_several_endings_from_memory_std_string, 3_chars_must_be_extracted_when_source_string_is_3_chars_and_end_string_is_a_different_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "d" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 3);
    ASSERT_EQ(dest_string, "abc");
    ASSERT_EQ(data_index, 3);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, 3_chars_must_be_extracted_when_source_string_is_3_chars_and_end_string_is_a_different_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "d" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 3);
    ASSERT_EQ(dest_string, "abc");
    ASSERT_EQ(data_index, 3);
}

TEST(extract_string_with_several_endings_from_memory, nothing_must_be_extracted_when_source_string_is_3_chars_and_1st_char_of_end_string_is_same_as_1st_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "ad" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_TRUE(dest_string.empty());
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, nothing_must_be_extracted_when_source_string_is_3_chars_and_1st_char_of_end_string_is_same_as_1st_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "ad" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_TRUE(dest_string.empty());
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, nothing_must_be_extracted_when_source_string_is_3_chars_and_1st_char_of_end_string_is_same_as_1st_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "ad" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_TRUE(dest_string.empty());
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_with_several_endings_from_memory, nothing_must_be_extracted_when_source_string_is_3_chars_and_2nd_char_of_end_string_is_same_as_1st_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "da" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_TRUE(dest_string.empty());
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, nothing_must_be_extracted_when_source_string_is_3_chars_and_2nd_char_of_end_string_is_same_as_1st_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "da" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_TRUE(dest_string.empty());
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, nothing_must_be_extracted_when_source_string_is_3_chars_and_2nd_char_of_end_string_is_same_as_1st_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "da" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_TRUE(dest_string.empty());
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_with_several_endings_from_memory, nothing_must_be_extracted_when_source_string_is_3_chars_and_3rd_char_of_end_string_is_same_as_1st_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "dea" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_TRUE(dest_string.empty());
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, nothing_must_be_extracted_when_source_string_is_3_chars_and_3rd_char_of_end_string_is_same_as_1st_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "dea" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_TRUE(dest_string.empty());
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, nothing_must_be_extracted_when_source_string_is_3_chars_and_3rd_char_of_end_string_is_same_as_1st_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "dea" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_TRUE(dest_string.empty());
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_with_several_endings_from_memory, nothing_must_be_extracted_when_source_string_is_3_chars_and_4th_char_of_end_string_is_same_as_1st_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "defa" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_TRUE(dest_string.empty());
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, nothing_must_be_extracted_when_source_string_is_3_chars_and_4th_char_of_end_string_is_same_as_1st_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "defa" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_TRUE(dest_string.empty());
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, nothing_must_be_extracted_when_source_string_is_3_chars_and_4th_char_of_end_string_is_same_as_1st_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "defa" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_TRUE(dest_string.empty());
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_with_several_endings_from_memory, nothing_must_be_extracted_when_source_string_is_3_chars_and_5th_char_of_end_string_is_same_as_1st_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "defga" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_TRUE(dest_string.empty());
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string, nothing_must_be_extracted_when_source_string_is_3_chars_and_5th_char_of_end_string_is_same_as_1st_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "defga" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_TRUE(dest_string.empty());
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, nothing_must_be_extracted_when_source_string_is_3_chars_and_5th_char_of_end_string_is_same_as_1st_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "defga" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_TRUE(dest_string.empty());
    ASSERT_EQ(data_index, 0);
}

TEST(extract_string_with_several_endings_from_memory, 1_char_must_be_extracted_when_source_string_is_3_chars_and_1st_char_of_end_string_is_same_as_2nd_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "bd" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 1);
    ASSERT_EQ(dest_string, "a");
    ASSERT_EQ(data_index, 1);
}

TEST(extract_string_with_several_endings_from_memory_std_string, 1_char_must_be_extracted_when_source_string_is_3_chars_and_1st_char_of_end_string_is_same_as_2nd_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "bd" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 1);
    ASSERT_EQ(dest_string, "a");
    ASSERT_EQ(data_index, 1);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, 1_char_must_be_extracted_when_source_string_is_3_chars_and_1st_char_of_end_string_is_same_as_2nd_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "bd" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 1);
    ASSERT_EQ(dest_string, "a");
    ASSERT_EQ(data_index, 1);
}

TEST(extract_string_with_several_endings_from_memory, 1_char_must_be_extracted_when_source_string_is_3_chars_and_2nd_char_of_end_string_is_same_as_2nd_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "db" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 1);
    ASSERT_EQ(dest_string, "a");
    ASSERT_EQ(data_index, 1);
}

TEST(extract_string_with_several_endings_from_memory_std_string, 1_char_must_be_extracted_when_source_string_is_3_chars_and_2nd_char_of_end_string_is_same_as_2nd_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "db" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 1);
    ASSERT_EQ(dest_string, "a");
    ASSERT_EQ(data_index, 1);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, 1_char_must_be_extracted_when_source_string_is_3_chars_and_2nd_char_of_end_string_is_same_as_2nd_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "db" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 1);
    ASSERT_EQ(dest_string, "a");
    ASSERT_EQ(data_index, 1);
}

TEST(extract_string_with_several_endings_from_memory, 1_char_must_be_extracted_when_source_string_is_3_chars_and_3rd_char_of_end_string_is_same_as_2nd_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "deb" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 1);
    ASSERT_EQ(dest_string, "a");
    ASSERT_EQ(data_index, 1);
}

TEST(extract_string_with_several_endings_from_memory_std_string, 1_char_must_be_extracted_when_source_string_is_3_chars_and_3rd_char_of_end_string_is_same_as_2nd_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "deb" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 1);
    ASSERT_EQ(dest_string, "a");
    ASSERT_EQ(data_index, 1);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, 1_char_must_be_extracted_when_source_string_is_3_chars_and_3rd_char_of_end_string_is_same_as_2nd_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "deb" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 1);
    ASSERT_EQ(dest_string, "a");
    ASSERT_EQ(data_index, 1);
}

TEST(extract_string_with_several_endings_from_memory, 1_char_must_be_extracted_when_source_string_is_3_chars_and_4th_char_of_end_string_is_same_as_2nd_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "defb" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 1);
    ASSERT_EQ(dest_string, "a");
    ASSERT_EQ(data_index, 1);
}

TEST(extract_string_with_several_endings_from_memory_std_string, 1_char_must_be_extracted_when_source_string_is_3_chars_and_4th_char_of_end_string_is_same_as_2nd_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "defb" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 1);
    ASSERT_EQ(dest_string, "a");
    ASSERT_EQ(data_index, 1);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, 1_char_must_be_extracted_when_source_string_is_3_chars_and_4th_char_of_end_string_is_same_as_2nd_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "defb" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 1);
    ASSERT_EQ(dest_string, "a");
    ASSERT_EQ(data_index, 1);
}

TEST(extract_string_with_several_endings_from_memory, 1_char_must_be_extracted_when_source_string_is_3_chars_and_5th_char_of_end_string_is_same_as_2nd_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "defgb" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 1);
    ASSERT_EQ(dest_string, "a");
    ASSERT_EQ(data_index, 1);
}

TEST(extract_string_with_several_endings_from_memory_std_string, 1_char_must_be_extracted_when_source_string_is_3_chars_and_5th_char_of_end_string_is_same_as_2nd_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "defgb" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 1);
    ASSERT_EQ(dest_string, "a");
    ASSERT_EQ(data_index, 1);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, 1_char_must_be_extracted_when_source_string_is_3_chars_and_5th_char_of_end_string_is_same_as_2nd_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "defgb" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 1);
    ASSERT_EQ(dest_string, "a");
    ASSERT_EQ(data_index, 1);
}

TEST(extract_string_with_several_endings_from_memory, 2_chars_must_be_extracted_when_source_string_is_3_chars_and_1st_char_of_end_string_is_same_as_3rd_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "cd" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 2);
    ASSERT_EQ(dest_string, "ab");
    ASSERT_EQ(data_index, 2);
}

TEST(extract_string_with_several_endings_from_memory_std_string, 2_chars_must_be_extracted_when_source_string_is_3_chars_and_1st_char_of_end_string_is_same_as_3rd_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "cd" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 2);
    ASSERT_EQ(dest_string, "ab");
    ASSERT_EQ(data_index, 2);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, 2_chars_must_be_extracted_when_source_string_is_3_chars_and_1st_char_of_end_string_is_same_as_3rd_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "cd" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 2);
    ASSERT_EQ(dest_string, "ab");
    ASSERT_EQ(data_index, 2);
}

TEST(extract_string_with_several_endings_from_memory, 2_chars_must_be_extracted_when_source_string_is_3_chars_and_2nd_char_of_end_string_is_same_as_3rd_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "dc" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 2);
    ASSERT_EQ(dest_string, "ab");
    ASSERT_EQ(data_index, 2);
}

TEST(extract_string_with_several_endings_from_memory_std_string, 2_chars_must_be_extracted_when_source_string_is_3_chars_and_2nd_char_of_end_string_is_same_as_3rd_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "dc" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 2);
    ASSERT_EQ(dest_string, "ab");
    ASSERT_EQ(data_index, 2);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, 2_chars_must_be_extracted_when_source_string_is_3_chars_and_2nd_char_of_end_string_is_same_as_3rd_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "dc" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 2);
    ASSERT_EQ(dest_string, "ab");
    ASSERT_EQ(data_index, 2);
}

TEST(extract_string_with_several_endings_from_memory, 2_chars_must_be_extracted_when_source_string_is_3_chars_and_3rd_char_of_end_string_is_same_as_3rd_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "dec" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 2);
    ASSERT_EQ(dest_string, "ab");
    ASSERT_EQ(data_index, 2);
}

TEST(extract_string_with_several_endings_from_memory_std_string, 2_chars_must_be_extracted_when_source_string_is_3_chars_and_3rd_char_of_end_string_is_same_as_3rd_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "dec" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 2);
    ASSERT_EQ(dest_string, "ab");
    ASSERT_EQ(data_index, 2);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, 2_chars_must_be_extracted_when_source_string_is_3_chars_and_3rd_char_of_end_string_is_same_as_3rd_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "dec" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 2);
    ASSERT_EQ(dest_string, "ab");
    ASSERT_EQ(data_index, 2);
}

TEST(extract_string_with_several_endings_from_memory, 2_chars_must_be_extracted_when_source_string_is_3_chars_and_4th_char_of_end_string_is_same_as_3rd_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "defc" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 2);
    ASSERT_EQ(dest_string, "ab");
    ASSERT_EQ(data_index, 2);
}

TEST(extract_string_with_several_endings_from_memory_std_string, 2_chars_must_be_extracted_when_source_string_is_3_chars_and_4th_char_of_end_string_is_same_as_3rd_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "defc" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 2);
    ASSERT_EQ(dest_string, "ab");
    ASSERT_EQ(data_index, 2);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, 2_chars_must_be_extracted_when_source_string_is_3_chars_and_4th_char_of_end_string_is_same_as_3rd_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "defc" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 2);
    ASSERT_EQ(dest_string, "ab");
    ASSERT_EQ(data_index, 2);
}

TEST(extract_string_with_several_endings_from_memory, 2_chars_must_be_extracted_when_source_string_is_3_chars_and_5th_char_of_end_string_is_same_as_3rd_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "defgc" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 2);
    ASSERT_EQ(dest_string, "ab");
    ASSERT_EQ(data_index, 2);
}

TEST(extract_string_with_several_endings_from_memory_std_string, 2_chars_must_be_extracted_when_source_string_is_3_chars_and_5th_char_of_end_string_is_same_as_3rd_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "defgc" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 2);
    ASSERT_EQ(dest_string, "ab");
    ASSERT_EQ(data_index, 2);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, 2_chars_must_be_extracted_when_source_string_is_3_chars_and_5th_char_of_end_string_is_same_as_3rd_char)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "defgc" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 2);
    ASSERT_EQ(dest_string, "ab");
    ASSERT_EQ(data_index, 2);
}

TEST(extract_string_with_several_endings_from_memory, 3_chars_must_be_extracted_when_source_string_is_3_chars_and_end_string_is_an_empty_string)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 3);
    ASSERT_EQ(dest_string, "abc");
    ASSERT_EQ(data_index, 3);
}

TEST(extract_string_with_several_endings_from_memory_std_string, 3_chars_must_be_extracted_when_source_string_is_3_chars_and_end_string_is_an_empty_string)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 3);
    ASSERT_EQ(dest_string, "abc");
    ASSERT_EQ(data_index, 3);
}

TEST(extract_string_with_several_endings_from_memory_std_string_in_out, 3_chars_must_be_extracted_when_source_string_is_3_chars_and_end_string_is_an_empty_string)
{
    std::string_view text { "abc" };
    std::size_t data_index = 0;

    std::string_view end_string { "" };
    std::string dest_string;

    yli::string::extract_string_with_several_endings(text, data_index, dest_string, end_string);
    ASSERT_EQ(dest_string.size(), 3);
    ASSERT_EQ(dest_string, "abc");
    ASSERT_EQ(data_index, 3);
}
