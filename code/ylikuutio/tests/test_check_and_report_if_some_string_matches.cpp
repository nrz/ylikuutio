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
#include <vector>   // std::vector

TEST(string_matching_std_string, some_string_must_match_when_the_only_identifier_string_is_an_empty_string)
{
    const std::string text_string = "a";
    const std::size_t data_index = 0;
    const std::vector<std::string> identifier_strings_vector = { "" };
    ASSERT_TRUE(yli::string::check_and_report_if_some_string_matches(text_string, data_index, identifier_strings_vector));
}

TEST(string_matching_std_string, some_string_must_match_when_there_is_only_one_1_character_string_in_the_identifier_string_vector_and_it_matches)
{
    const std::string text_string = "a";
    const std::size_t data_index = 0;
    const std::vector<std::string> identifier_strings_vector = { "a" };
    ASSERT_TRUE(yli::string::check_and_report_if_some_string_matches(text_string, data_index, identifier_strings_vector));

    const std::string other_text_string = "ab";
    const std::size_t other_text_data_index = 0;
    ASSERT_TRUE(yli::string::check_and_report_if_some_string_matches(other_text_string, other_text_data_index, identifier_strings_vector));
}

TEST(string_matching_std_string, some_string_must_match_when_there_is_only_one_2_character_string_in_the_identifier_string_vector_and_it_matches)
{
    const std::string text_string = "ab";
    const std::size_t data_index = 0;
    const std::vector<std::string> identifier_strings_vector = { "ab" };
    ASSERT_TRUE(yli::string::check_and_report_if_some_string_matches(text_string, data_index, identifier_strings_vector));
}

TEST(string_matching_std_string, some_string_must_match_when_there_is_only_one_3_character_string_in_the_identifier_string_vector_and_it_matches)
{
    const std::string text_string = "abc";
    const std::size_t data_index = 0;
    const std::vector<std::string> identifier_strings_vector = { "abc" };
    ASSERT_TRUE(yli::string::check_and_report_if_some_string_matches(text_string, data_index, identifier_strings_vector));
}

TEST(string_matching_std_string, some_string_must_match_when_there_are_two_1_character_strings_in_the_identifier_string_vector_and_the_1st_matches)
{
    const std::string text_string = "a";
    const std::size_t data_index = 0;
    const std::vector<std::string> identifier_strings_vector = { "a", "b" };
    ASSERT_TRUE(yli::string::check_and_report_if_some_string_matches(text_string, data_index, identifier_strings_vector));
}

TEST(string_matching_std_string, some_string_must_match_when_there_are_two_1_character_strings_in_the_identifier_string_vector_and_the_2nd_matches)
{
    const std::string text_string = "b";
    const std::size_t data_index = 0;
    const std::vector<std::string> identifier_strings_vector = { "a", "b" };
    ASSERT_TRUE(yli::string::check_and_report_if_some_string_matches(text_string, data_index, identifier_strings_vector));
}

TEST(string_matching_std_string, some_string_must_match_when_there_are_three_1_character_strings_in_the_identifier_string_vector_and_the_1st_matches)
{
    const std::string text_string = "a";
    const std::size_t data_index = 0;
    const std::vector<std::string> identifier_strings_vector = { "a", "b", "c" };
    ASSERT_TRUE(yli::string::check_and_report_if_some_string_matches(text_string, data_index, identifier_strings_vector));
}

TEST(string_matching_std_string, some_string_must_match_when_there_are_three_1_character_strings_in_the_identifier_string_vector_and_the_2nd_matches)
{
    const std::string text_string = "b";
    const std::size_t data_index = 0;
    const std::vector<std::string> identifier_strings_vector = { "a", "b", "c" };
    ASSERT_TRUE(yli::string::check_and_report_if_some_string_matches(text_string, data_index, identifier_strings_vector));
}

TEST(string_matching_std_string, some_string_must_match_when_there_are_three_1_character_strings_in_the_identifier_string_vector_and_the_3rd_matches)
{
    const std::string text_string = "c";
    const std::size_t data_index = 0;
    const std::vector<std::string> identifier_strings_vector = { "a", "b", "c" };
    ASSERT_TRUE(yli::string::check_and_report_if_some_string_matches(text_string, data_index, identifier_strings_vector));
}

TEST(string_matching_std_string, no_string_must_match_when_the_identifier_string_vector_is_empty)
{
    const std::string text_string = "a";
    const std::size_t data_index = 0;
    const std::vector<std::string> identifier_strings_vector = {};
    ASSERT_FALSE(yli::string::check_and_report_if_some_string_matches(text_string, data_index, identifier_strings_vector));
}

TEST(string_matching_std_string, no_string_must_match_when_the_only_identifier_string_is_longer_than_the_string_to_be_compared_with)
{
    const std::string text_string = "a";
    const std::size_t data_index = 0;
    const std::vector<std::string> identifier_strings_vector = { "aa" };
    ASSERT_FALSE(yli::string::check_and_report_if_some_string_matches(text_string, data_index, identifier_strings_vector));
}

TEST(string_matching_std_string, no_string_must_match_when_there_is_only_one_1_character_string_in_the_identifier_string_vector_and_it_does_not_match)
{
    const std::string text_string = "a";
    const std::size_t data_index = 0;
    std::vector<std::string> identifier_strings_vector = { "b" };
    ASSERT_FALSE(yli::string::check_and_report_if_some_string_matches(text_string, data_index, identifier_strings_vector));

    identifier_strings_vector = { "A" };
    ASSERT_FALSE(yli::string::check_and_report_if_some_string_matches(text_string, data_index, identifier_strings_vector));
}

TEST(string_matching_std_string, no_string_must_match_when_there_is_only_one_2_character_string_in_the_identifier_string_vector_and_its_1st_character_does_not_match)
{
    const std::string text_string = "ab";
    const std::size_t data_index = 0;
    std::vector<std::string> identifier_strings_vector = { "bb" };
    ASSERT_FALSE(yli::string::check_and_report_if_some_string_matches(text_string, data_index, identifier_strings_vector));

    identifier_strings_vector = { "Ab" };
    ASSERT_FALSE(yli::string::check_and_report_if_some_string_matches(text_string, data_index, identifier_strings_vector));
}

TEST(string_matching_std_string, no_string_must_match_when_there_is_only_one_2_character_string_in_the_identifier_string_vector_and_its_2nd_character_does_not_match)
{
    const std::string text_string = "ab";
    const std::size_t data_index = 0;
    std::vector<std::string> identifier_strings_vector = { "aa" };
    ASSERT_FALSE(yli::string::check_and_report_if_some_string_matches(text_string, data_index, identifier_strings_vector));

    identifier_strings_vector = { "aB" };
    ASSERT_FALSE(yli::string::check_and_report_if_some_string_matches(text_string, data_index, identifier_strings_vector));
}

TEST(string_matching_std_string, no_string_must_match_when_there_is_only_one_3_character_string_in_the_identifier_string_vector_and_its_1st_character_does_not_match)
{
    const std::string text_string = "abc";
    const std::size_t data_index = 0;
    std::vector<std::string> identifier_strings_vector = { "bbc" };
    ASSERT_FALSE(yli::string::check_and_report_if_some_string_matches(text_string, data_index, identifier_strings_vector));

    identifier_strings_vector = { "Abc" };
    ASSERT_FALSE(yli::string::check_and_report_if_some_string_matches(text_string, data_index, identifier_strings_vector));
}

TEST(string_matching_std_string, no_string_must_match_when_there_is_only_one_3_character_string_in_the_identifier_string_vector_and_its_2nd_character_does_not_match)
{
    const std::string text_string = "abc";
    const std::size_t data_index = 0;
    std::vector<std::string> identifier_strings_vector = { "aac" };
    ASSERT_FALSE(yli::string::check_and_report_if_some_string_matches(text_string, data_index, identifier_strings_vector));

    identifier_strings_vector = { "aBc" };
    ASSERT_FALSE(yli::string::check_and_report_if_some_string_matches(text_string, data_index, identifier_strings_vector));
}

TEST(string_matching_std_string, no_string_must_match_when_there_is_only_one_3_character_string_in_the_identifier_string_vector_and_its_3rd_character_does_not_match)
{
    const std::string text_string = "abc";
    const std::size_t data_index = 0;
    std::vector<std::string> identifier_strings_vector = { "abb" };
    ASSERT_FALSE(yli::string::check_and_report_if_some_string_matches(text_string, data_index, identifier_strings_vector));

    identifier_strings_vector = { "abC" };
    ASSERT_FALSE(yli::string::check_and_report_if_some_string_matches(text_string, data_index, identifier_strings_vector));
}

TEST(string_matching_std_string, no_string_must_match_when_there_are_two_1_character_strings_in_the_identifier_string_vector_and_neither_matches)
{
    const std::string text_string = "a";
    const std::size_t data_index = 0;
    const std::vector<std::string> identifier_strings_vector = { "A", "b" };
    ASSERT_FALSE(yli::string::check_and_report_if_some_string_matches(text_string, data_index, identifier_strings_vector));
}

TEST(string_matching_std_string, no_string_must_match_when_there_are_three_1_character_strings_in_the_identifier_string_vector_and_none_matches)
{
    const std::string text_string = "a";
    const std::size_t data_index = 0;
    const std::vector<std::string> identifier_strings_vector = { "A", "b", "c" };
    ASSERT_FALSE(yli::string::check_and_report_if_some_string_matches(text_string, data_index, identifier_strings_vector));
}
