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
#include "code/ylikuutio/console/text_line.hpp"
#include "code/ylikuutio/console/text_input.hpp"
#include "code/ylikuutio/console/text_input_type.hpp"

// Include standard headers
#include <string_view> // std::string_view
#include <vector>      // std::vector

TEST(text_line_must_be_initialized_appropriately, empty_text_line)
{
    yli::console::TextLine text_line("");
    ASSERT_EQ(text_line.data(), "");
    ASSERT_EQ(text_line.size(), 0);
    ASSERT_EQ(text_line.cbegin().unwrap(), text_line.data().cbegin());
}

TEST(text_line_must_be_initialized_appropriately, text_line)
{
    yli::console::TextLine text_line("abc");
    ASSERT_EQ(text_line.data(), "abc");
    ASSERT_EQ(text_line.size(), 3);
}

TEST(text_line_must_be_initialized_appropriately, from_text_input)
{
    yli::console::TextInput text_input(yli::console::TextInputType::NEW_INPUT);
    text_input.add_characters("abc");

    yli::console::TextLine text_line(text_input);
    ASSERT_EQ(text_line.data(), "abc");
    ASSERT_EQ(text_line.size(), 3);
}

TEST(text_line_must_be_initialized_appropriately, empty_string)
{
    std::string_view empty_string;
    yli::console::TextLine text_line(empty_string);
    ASSERT_EQ(text_line.data(), "");
    ASSERT_EQ(text_line.size(), 0);
}

TEST(text_line_must_be_initialized_appropriately, a_string)
{
    std::string_view my_string { "a" };
    yli::console::TextLine text_line(my_string);
    ASSERT_EQ(text_line.data(), "a");
    ASSERT_EQ(text_line.size(), 1);
}

TEST(text_line_must_be_initialized_appropriately, abc_string)
{
    std::string_view my_string { "abc" };
    yli::console::TextLine text_line(my_string);
    ASSERT_EQ(text_line.data(), "abc");
    ASSERT_EQ(text_line.size(), 3);
}

TEST(text_line_begin_iterator_must_work_appropriately, text_line_begin_iterator)
{
    std::string_view my_string { "abc" };
    yli::console::TextLine text_line(my_string);

    auto it = text_line.begin();
    ASSERT_EQ(*it, 'a');
    ++it;
    ASSERT_EQ(*it, 'b');
    ++it;
    ASSERT_EQ(*it, 'c');
    ++it;
    ASSERT_EQ(it, text_line.end());
    ASSERT_EQ(text_line.size(), 3);
}

TEST(text_line_end_iterator_must_work_appropriately, text_line_end_iterator)
{
    std::string_view my_string { "abc" };
    yli::console::TextLine text_line(my_string);

    auto it = text_line.end();
    --it;
    ASSERT_EQ(*it, 'c');
    --it;
    ASSERT_EQ(*it, 'b');
    --it;
    ASSERT_EQ(*it, 'a');
    ASSERT_EQ(it, text_line.begin());
    ASSERT_EQ(text_line.size(), 3);
}

TEST(text_line_cbegin_const_iterator_must_work_appropriately, text_line_cbegin_const_iterator)
{
    std::string_view my_string { "abc" };
    yli::console::TextLine text_line(my_string);

    auto it = text_line.cbegin();
    ASSERT_EQ(*it, 'a');
    ++it;
    ASSERT_EQ(*it, 'b');
    ++it;
    ASSERT_EQ(*it, 'c');
    ++it;
    ASSERT_EQ(it, text_line.cend());
    ASSERT_EQ(text_line.size(), 3);
}

TEST(text_line_cend_const_iterator_must_work_appropriately, text_line_cend_const_iterator)
{
    std::string_view my_string { "abc" };
    yli::console::TextLine text_line(my_string);

    auto it = text_line.cend();
    --it;
    ASSERT_EQ(*it, 'c');
    --it;
    ASSERT_EQ(*it, 'b');
    --it;
    ASSERT_EQ(*it, 'a');
    ASSERT_EQ(it, text_line.cbegin());
    ASSERT_EQ(text_line.size(), 3);
}

TEST(text_line_must_be_split_appropriately, empty_text_line_n_columns_1)
{
    std::string_view my_string { "" };
    yli::console::TextLine text_line(my_string);
    std::vector<std::string_view> views = text_line.split_into_lines(1);
    ASSERT_TRUE(views.empty());
}

TEST(text_line_must_be_split_appropriately, empty_text_line_n_columns_2)
{
    std::string_view my_string { "" };
    yli::console::TextLine text_line(my_string);
    std::vector<std::string_view> views = text_line.split_into_lines(2);
    ASSERT_TRUE(views.empty());
}

TEST(text_line_must_be_split_appropriately, text_line_a_n_columns_1)
{
    std::string_view my_string { "a" };
    yli::console::TextLine text_line(my_string);
    std::vector<std::string_view> views = text_line.split_into_lines(1);
    ASSERT_EQ(views.size(), 1);
    ASSERT_EQ(views.at(0), "a");
}

TEST(text_line_must_be_split_appropriately, text_line_a_n_columns_2)
{
    std::string_view my_string { "a" };
    yli::console::TextLine text_line(my_string);
    std::vector<std::string_view> views = text_line.split_into_lines(2);
    ASSERT_EQ(views.size(), 1);
    ASSERT_EQ(views.at(0), "a");
}

TEST(text_line_must_be_split_appropriately, text_line_ab_n_columns_1)
{
    std::string_view my_string { "ab" };
    yli::console::TextLine text_line(my_string);
    std::vector<std::string_view> views = text_line.split_into_lines(1);
    ASSERT_EQ(views.size(), 2);
    ASSERT_EQ(views.at(0), "a");
    ASSERT_EQ(views.at(1), "b");
}

TEST(text_line_must_be_split_appropriately, text_line_ab_n_columns_2)
{
    std::string_view my_string { "ab" };
    yli::console::TextLine text_line(my_string);
    std::vector<std::string_view> views = text_line.split_into_lines(2);
    ASSERT_EQ(views.size(), 1);
    ASSERT_EQ(views.at(0), "ab");
}

TEST(text_line_must_be_split_appropriately, text_line_ab_n_columns_3)
{
    std::string_view my_string { "ab" };
    yli::console::TextLine text_line(my_string);
    std::vector<std::string_view> views = text_line.split_into_lines(3);
    ASSERT_EQ(views.size(), 1);
    ASSERT_EQ(views.at(0), "ab");
}

TEST(text_line_must_be_split_appropriately, text_line_abc_n_columns_1)
{
    std::string_view my_string { "abc" };
    yli::console::TextLine text_line(my_string);
    std::vector<std::string_view> views = text_line.split_into_lines(1);
    ASSERT_EQ(views.size(), 3);
    ASSERT_EQ(views.at(0), "a");
    ASSERT_EQ(views.at(1), "b");
    ASSERT_EQ(views.at(2), "c");
}

TEST(text_line_must_be_split_appropriately, text_line_abc_n_columns_2)
{
    std::string_view my_string { "abc" };
    yli::console::TextLine text_line(my_string);
    std::vector<std::string_view> views = text_line.split_into_lines(2);
    ASSERT_EQ(views.size(), 2);
    ASSERT_EQ(views.at(0), "ab");
    ASSERT_EQ(views.at(1), "c");
}

TEST(text_line_must_be_split_appropriately, text_line_abc_n_columns_3)
{
    std::string_view my_string { "abc" };
    yli::console::TextLine text_line(my_string);
    std::vector<std::string_view> views = text_line.split_into_lines(3);
    ASSERT_EQ(views.size(), 1);
    ASSERT_EQ(views.at(0), "abc");
}

TEST(last_lines_must_be_chosen_appropriately, text_line_abc_n_lines_1_n_columns_1)
{
    std::string_view my_string { "abc" };
    yli::console::TextLine text_line(my_string);
    std::vector<std::string_view> views = text_line.get_n_last_lines(1, 1);
    ASSERT_EQ(views.size(), 1);
    ASSERT_EQ(views.at(0), "c");
}

TEST(last_lines_must_be_chosen_appropriately, text_line_abc_n_lines_1_n_columns_2)
{
    std::string_view my_string { "abc" };
    yli::console::TextLine text_line(my_string);
    std::vector<std::string_view> views = text_line.get_n_last_lines(1, 2);
    ASSERT_EQ(views.size(), 1);
    ASSERT_EQ(views.at(0), "c");
}

TEST(last_lines_must_be_chosen_appropriately, text_line_abc_n_lines_2_n_columns_1)
{
    std::string_view my_string { "abc" };
    yli::console::TextLine text_line(my_string);
    std::vector<std::string_view> views = text_line.get_n_last_lines(2, 1);
    ASSERT_EQ(views.size(), 2);
    ASSERT_EQ(views.at(0), "b");
    ASSERT_EQ(views.at(1), "c");
}

TEST(last_lines_must_be_chosen_appropriately, text_line_abc_n_lines_2_n_columns_2)
{
    std::string_view my_string { "abc" };
    yli::console::TextLine text_line(my_string);
    std::vector<std::string_view> views = text_line.get_n_last_lines(2, 2);
    ASSERT_EQ(views.size(), 2);
    ASSERT_EQ(views.at(0), "ab");
    ASSERT_EQ(views.at(1), "c");
}

TEST(last_lines_must_be_chosen_appropriately, text_line_abcd_n_lines_1_n_columns_1)
{
    std::string_view my_string { "abcd" };
    yli::console::TextLine text_line(my_string);
    std::vector<std::string_view> views = text_line.get_n_last_lines(1, 1);
    ASSERT_EQ(views.size(), 1);
    ASSERT_EQ(views.at(0), "d");
}

TEST(last_lines_must_be_chosen_appropriately, text_line_abcd_n_lines_1_n_columns_2)
{
    std::string_view my_string { "abcd" };
    yli::console::TextLine text_line(my_string);
    std::vector<std::string_view> views = text_line.get_n_last_lines(1, 2);
    ASSERT_EQ(views.size(), 1);
    ASSERT_EQ(views.at(0), "cd");
}

TEST(last_lines_must_be_chosen_appropriately, text_line_abcd_n_lines_1_n_columns_3)
{
    std::string_view my_string { "abcd" };
    yli::console::TextLine text_line(my_string);
    std::vector<std::string_view> views = text_line.get_n_last_lines(1, 3);
    ASSERT_EQ(views.size(), 1);
    ASSERT_EQ(views.at(0), "d");
}

TEST(last_lines_must_be_chosen_appropriately, text_line_abcd_n_lines_2_n_columns_1)
{
    std::string_view my_string { "abcd" };
    yli::console::TextLine text_line(my_string);
    std::vector<std::string_view> views = text_line.get_n_last_lines(2, 1);
    ASSERT_EQ(views.size(), 2);
    ASSERT_EQ(views.at(0), "c");
    ASSERT_EQ(views.at(1), "d");
}

TEST(last_lines_must_be_chosen_appropriately, text_line_abcd_n_lines_2_n_columns_2)
{
    std::string_view my_string { "abcd" };
    yli::console::TextLine text_line(my_string);
    std::vector<std::string_view> views = text_line.get_n_last_lines(2, 2);
    ASSERT_EQ(views.size(), 2);
    ASSERT_EQ(views.at(0), "ab");
    ASSERT_EQ(views.at(1), "cd");
}
