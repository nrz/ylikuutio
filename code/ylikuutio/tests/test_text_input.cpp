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
#include "code/ylikuutio/console/text_input.hpp"

// Include standard headers
#include <optional> // std::nullopt
#include <string>   // std::string

TEST(text_input_must_be_initialized_appropriately, text_input)
{
    yli::console::TextInput text_input;
    ASSERT_EQ(text_input.size(), 0);
    ASSERT_TRUE(text_input.empty());
    ASSERT_EQ(text_input.get_character_at_current_index(), std::nullopt);
    ASSERT_EQ(text_input.get_character_to_the_left(), std::nullopt);
    ASSERT_EQ(text_input.get_cursor_index(), 0);
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().begin());
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().end());
    ASSERT_EQ(text_input.data(), "");
    ASSERT_EQ(text_input.cbegin().unwrap(), text_input.data().cbegin());
}

TEST(text_input_must_be_initialized_appropriately, string_foo)
{
    yli::console::TextInput text_input("foo");
    ASSERT_EQ(text_input.size(), 3);
    ASSERT_FALSE(text_input.empty());
    ASSERT_EQ(text_input.get_character_at_current_index(), 'f');
    ASSERT_EQ(text_input.get_character_to_the_left(), std::nullopt);
    ASSERT_EQ(text_input.get_cursor_index(), 0);
    std::string::iterator it = text_input.get_cursor_it();
    ASSERT_EQ(it, text_input.data().begin());
    it += text_input.size();
    ASSERT_EQ(it, text_input.data().end());
    ASSERT_EQ(text_input.data(), "foo");
    ASSERT_EQ(text_input.cbegin().unwrap(), text_input.data().cbegin());
}

TEST(one_character_must_be_added_to_the_text_input_appropriately, single_character_a)
{
    yli::console::TextInput text_input;
    text_input.add_character('a');
    ASSERT_EQ(text_input.get_character_at_current_index(), std::nullopt);
    ASSERT_EQ(text_input.get_character_to_the_left(), 'a');
    ASSERT_EQ(text_input.size(), 1);
    ASSERT_FALSE(text_input.empty());
    ASSERT_EQ(text_input.get_cursor_index(), 1);
    ASSERT_NE(text_input.get_cursor_it(), text_input.data().begin());
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().end());
    ASSERT_EQ(text_input.data(), "a");
}

TEST(two_characters_must_be_added_to_the_text_input_appropriately, single_characters_a_b)
{
    yli::console::TextInput text_input;
    text_input.add_character('a');
    text_input.add_character('b');
    ASSERT_EQ(text_input.get_character_at_current_index(), std::nullopt);
    ASSERT_EQ(text_input.get_character_to_the_left(), 'b');
    ASSERT_EQ(text_input.size(), 2);
    ASSERT_FALSE(text_input.empty());
    ASSERT_EQ(text_input.get_cursor_index(), 2);
    ASSERT_NE(text_input.get_cursor_it(), text_input.data().begin());
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().end());
    ASSERT_EQ(text_input.data(), "ab");
}

TEST(three_characters_must_be_added_to_the_text_input_appropriately, single_characters_a_b_c)
{
    yli::console::TextInput text_input;
    text_input.add_character('a');
    text_input.add_character('b');
    text_input.add_character('c');
    ASSERT_EQ(text_input.get_character_at_current_index(), std::nullopt);
    ASSERT_EQ(text_input.get_character_to_the_left(), 'c');
    ASSERT_EQ(text_input.size(), 3);
    ASSERT_FALSE(text_input.empty());
    ASSERT_EQ(text_input.get_cursor_index(), 3);
    ASSERT_NE(text_input.get_cursor_it(), text_input.data().begin());
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().end());
    ASSERT_EQ(text_input.data(), "abc");
}

TEST(one_character_must_be_added_to_the_text_input_appropriately, single_ascii_character_a)
{
    yli::console::TextInput text_input;
    text_input.add_character('a');
    ASSERT_EQ(text_input.get_character_at_current_index(), std::nullopt);
    ASSERT_EQ(text_input.get_character_to_the_left(), 'a');
    ASSERT_EQ(text_input.size(), 1);
    ASSERT_FALSE(text_input.empty());
    ASSERT_EQ(text_input.get_cursor_index(), 1);
    ASSERT_NE(text_input.get_cursor_it(), text_input.data().begin());
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().end());
    ASSERT_EQ(text_input.data(), "a");
}

TEST(two_characters_must_be_added_to_the_text_input_appropriately, single_ascii_characters_a_b)
{
    yli::console::TextInput text_input;
    text_input.add_character('a');
    text_input.add_character('b');
    ASSERT_EQ(text_input.get_character_at_current_index(), std::nullopt);
    ASSERT_EQ(text_input.get_character_to_the_left(), 'b');
    ASSERT_EQ(text_input.size(), 2);
    ASSERT_FALSE(text_input.empty());
    ASSERT_EQ(text_input.get_cursor_index(), 2);
    ASSERT_NE(text_input.get_cursor_it(), text_input.data().begin());
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().end());
    ASSERT_EQ(text_input.data(), "ab");
}

TEST(three_characters_must_be_added_to_the_text_input_appropriately, single_ascii_characters_a_b_c)
{
    yli::console::TextInput text_input;
    text_input.add_character('a');
    text_input.add_character('b');
    text_input.add_character('c');
    ASSERT_EQ(text_input.get_character_at_current_index(), std::nullopt);
    ASSERT_EQ(text_input.get_character_to_the_left(), 'c');
    ASSERT_EQ(text_input.size(), 3);
    ASSERT_FALSE(text_input.empty());
    ASSERT_EQ(text_input.get_cursor_index(), 3);
    ASSERT_NE(text_input.get_cursor_it(), text_input.data().begin());
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().end());
    ASSERT_EQ(text_input.data(), "abc");
}

TEST(one_character_must_be_added_to_the_text_input_appropriately, char_container_a)
{
    yli::console::TextInput text_input;
    text_input.add_characters("a");
    ASSERT_EQ(text_input.get_character_at_current_index(), std::nullopt);
    ASSERT_EQ(text_input.get_character_to_the_left(), 'a');
    ASSERT_EQ(text_input.size(), 1);
    ASSERT_FALSE(text_input.empty());
    ASSERT_EQ(text_input.get_cursor_index(), 1);
    ASSERT_NE(text_input.get_cursor_it(), text_input.data().begin());
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().end());
    ASSERT_EQ(text_input.data(), "a");
}

TEST(two_characters_must_be_added_to_the_text_input_appropriately, char_container_a_b)
{
    yli::console::TextInput text_input;
    text_input.add_characters("ab");
    ASSERT_EQ(text_input.get_character_at_current_index(), std::nullopt);
    ASSERT_EQ(text_input.get_character_to_the_left(), 'b');
    ASSERT_EQ(text_input.size(), 2);
    ASSERT_FALSE(text_input.empty());
    ASSERT_EQ(text_input.get_cursor_index(), 2);
    ASSERT_NE(text_input.get_cursor_it(), text_input.data().begin());
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().end());
    ASSERT_EQ(text_input.data(), "ab");
}

TEST(three_characters_must_be_added_to_the_text_input_appropriately, char_container_a_b_c)
{
    yli::console::TextInput text_input;
    text_input.add_characters("abc");
    ASSERT_EQ(text_input.get_character_at_current_index(), std::nullopt);
    ASSERT_EQ(text_input.get_character_to_the_left(), 'c');
    ASSERT_EQ(text_input.size(), 3);
    ASSERT_FALSE(text_input.empty());
    ASSERT_EQ(text_input.get_cursor_index(), 3);
    ASSERT_NE(text_input.get_cursor_it(), text_input.data().begin());
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().end());
    ASSERT_EQ(text_input.data(), "abc");
}

TEST(two_characters_must_be_added_to_the_text_input_appropriately, single_character_a_and_char_container_b)
{
    yli::console::TextInput text_input;
    text_input.add_character('a');
    text_input.add_characters("b");
    ASSERT_EQ(text_input.get_character_at_current_index(), std::nullopt);
    ASSERT_EQ(text_input.get_character_to_the_left(), 'b');
    ASSERT_EQ(text_input.size(), 2);
    ASSERT_FALSE(text_input.empty());
    ASSERT_EQ(text_input.get_cursor_index(), 2);
    ASSERT_NE(text_input.get_cursor_it(), text_input.data().begin());
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().end());
    ASSERT_EQ(text_input.data(), "ab");
}

TEST(two_characters_must_be_added_to_the_text_input_appropriately, char_container_a_and_single_character_b)
{
    yli::console::TextInput text_input;
    text_input.add_characters("a");
    text_input.add_character('b');
    ASSERT_EQ(text_input.get_character_at_current_index(), std::nullopt);
    ASSERT_EQ(text_input.get_character_to_the_left(), 'b');
    ASSERT_EQ(text_input.size(), 2);
    ASSERT_FALSE(text_input.empty());
    ASSERT_EQ(text_input.get_cursor_index(), 2);
    ASSERT_NE(text_input.get_cursor_it(), text_input.data().begin());
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().end());
    ASSERT_EQ(text_input.data(), "ab");
}

TEST(deleting_a_character_must_fail_appropriately_for_empty_text_input, empty_text_input)
{
    yli::console::TextInput text_input;
    ASSERT_FALSE(text_input.delete_character());
    ASSERT_EQ(text_input.get_character_at_current_index(), std::nullopt);
    ASSERT_EQ(text_input.get_character_to_the_left(), std::nullopt);
    ASSERT_EQ(text_input.size(), 0);
    ASSERT_TRUE(text_input.empty());
    ASSERT_EQ(text_input.get_cursor_index(), 0);
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().begin());
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().end());
    ASSERT_EQ(text_input.data(), "");
}

TEST(character_must_deleted_from_the_text_input_appropriately, single_character_a)
{
    yli::console::TextInput text_input;
    text_input.add_character('a');
    ASSERT_TRUE(text_input.delete_character());
    ASSERT_EQ(text_input.get_character_at_current_index(), std::nullopt);
    ASSERT_EQ(text_input.get_character_to_the_left(), std::nullopt);
    ASSERT_EQ(text_input.size(), 0);
    ASSERT_TRUE(text_input.empty());
    ASSERT_EQ(text_input.get_cursor_index(), 0);
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().begin());
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().end());
    ASSERT_EQ(text_input.data(), "");
}

TEST(character_must_deleted_from_the_text_input_appropriately, char_container_a)
{
    yli::console::TextInput text_input;
    text_input.add_characters("a");
    ASSERT_TRUE(text_input.delete_character());
    ASSERT_EQ(text_input.get_character_at_current_index(), std::nullopt);
    ASSERT_EQ(text_input.get_character_to_the_left(), std::nullopt);
    ASSERT_EQ(text_input.size(), 0);
    ASSERT_TRUE(text_input.empty());
    ASSERT_EQ(text_input.get_cursor_index(), 0);
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().begin());
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().end());
    ASSERT_EQ(text_input.data(), "");
}

TEST(character_must_deleted_from_the_text_input_appropriately, single_character_a_b)
{
    yli::console::TextInput text_input;
    text_input.add_character('a');
    text_input.add_character('b');
    ASSERT_TRUE(text_input.delete_character());
    ASSERT_EQ(text_input.get_character_at_current_index(), std::nullopt);
    ASSERT_EQ(text_input.get_character_to_the_left(), 'a');
    ASSERT_EQ(text_input.size(), 1);
    ASSERT_FALSE(text_input.empty());
    ASSERT_EQ(text_input.get_cursor_index(), 1);
    ASSERT_NE(text_input.get_cursor_it(), text_input.data().begin());
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().end());
    ASSERT_EQ(text_input.data(), "a");

    ASSERT_TRUE(text_input.delete_character());
    ASSERT_EQ(text_input.get_character_at_current_index(), std::nullopt);
    ASSERT_EQ(text_input.get_character_to_the_left(), std::nullopt);
    ASSERT_EQ(text_input.size(), 0);
    ASSERT_TRUE(text_input.empty());
    ASSERT_EQ(text_input.get_cursor_index(), 0);
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().begin());
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().end());
    ASSERT_EQ(text_input.data(), "");
}

TEST(character_must_deleted_from_the_text_input_appropriately, char_container_a_b)
{
    yli::console::TextInput text_input;
    text_input.add_characters("ab");
    ASSERT_TRUE(text_input.delete_character());
    ASSERT_EQ(text_input.get_character_at_current_index(), std::nullopt);
    ASSERT_EQ(text_input.get_character_to_the_left(), 'a');
    ASSERT_EQ(text_input.size(), 1);
    ASSERT_FALSE(text_input.empty());
    ASSERT_EQ(text_input.get_cursor_index(), 1);
    ASSERT_NE(text_input.get_cursor_it(), text_input.data().begin());
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().end());
    ASSERT_EQ(text_input.data(), "a");

    ASSERT_TRUE(text_input.delete_character());
    ASSERT_EQ(text_input.get_character_at_current_index(), std::nullopt);
    ASSERT_EQ(text_input.get_character_to_the_left(), std::nullopt);
    ASSERT_EQ(text_input.size(), 0);
    ASSERT_TRUE(text_input.empty());
    ASSERT_EQ(text_input.get_cursor_index(), 0);
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().begin());
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().end());
    ASSERT_EQ(text_input.data(), "");
}

TEST(text_input_must_be_cleared_appropriately, after_single_character_a)
{
    yli::console::TextInput text_input;
    text_input.add_character('a');
    text_input.clear();
    ASSERT_EQ(text_input.get_character_at_current_index(), std::nullopt);
    ASSERT_EQ(text_input.get_character_to_the_left(), std::nullopt);
    ASSERT_EQ(text_input.size(), 0);
    ASSERT_TRUE(text_input.empty());
    ASSERT_EQ(text_input.get_cursor_index(), 0);
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().begin());
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().end());
}

TEST(text_input_must_be_cleared_appropriately, after_single_characters_a_b)
{
    yli::console::TextInput text_input;
    text_input.add_character('a');
    text_input.add_character('b');
    text_input.clear();
    ASSERT_EQ(text_input.get_character_at_current_index(), std::nullopt);
    ASSERT_EQ(text_input.get_character_to_the_left(), std::nullopt);
    ASSERT_EQ(text_input.size(), 0);
    ASSERT_TRUE(text_input.empty());
    ASSERT_EQ(text_input.get_cursor_index(), 0);
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().begin());
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().end());
}

TEST(moving_cursor_to_left_must_fail_appropriately, no_input)
{
    yli::console::TextInput text_input;
    ASSERT_FALSE(text_input.move_cursor_left());
    ASSERT_EQ(text_input.size(), 0);
    ASSERT_TRUE(text_input.empty());
    ASSERT_EQ(text_input.get_character_at_current_index(), std::nullopt);
    ASSERT_EQ(text_input.get_character_to_the_left(), std::nullopt);
    ASSERT_EQ(text_input.get_cursor_index(), 0);
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().begin());
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().end());
    ASSERT_EQ(text_input.data(), "");
}

TEST(moving_cursor_to_left_must_succeed_appropriately, after_single_character_a)
{
    yli::console::TextInput text_input;
    text_input.add_character('a');
    ASSERT_TRUE(text_input.move_cursor_left());
    ASSERT_EQ(text_input.get_character_at_current_index(), 'a');
    ASSERT_EQ(text_input.get_character_to_the_left(), std::nullopt);
    ASSERT_EQ(text_input.size(), 1);
    ASSERT_FALSE(text_input.empty());
    ASSERT_EQ(text_input.get_cursor_index(), 0);
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().begin());
    ASSERT_NE(text_input.get_cursor_it(), text_input.data().end());
    ASSERT_EQ(text_input.data(), "a");
}

TEST(moving_cursor_to_left_must_fail_appropriately, after_single_characters_a_b)
{
    yli::console::TextInput text_input;
    text_input.add_character('a');
    text_input.add_character('b');
    ASSERT_TRUE(text_input.move_cursor_left());
    ASSERT_EQ(text_input.get_character_at_current_index(), 'b');
    ASSERT_EQ(text_input.get_character_to_the_left(), 'a');
    ASSERT_EQ(text_input.size(), 2);
    ASSERT_FALSE(text_input.empty());
    ASSERT_EQ(text_input.get_cursor_index(), 1);
    std::string::iterator it = text_input.get_cursor_it();
    ASSERT_NE(it, text_input.data().begin());
    ++it;
    ASSERT_EQ(it, text_input.data().end());
    ASSERT_EQ(text_input.data(), "ab");
}

TEST(moving_cursor_to_right_must_fail_appropriately, no_input)
{
    yli::console::TextInput text_input;
    ASSERT_FALSE(text_input.move_cursor_right());
    ASSERT_EQ(text_input.get_character_at_current_index(), std::nullopt);
    ASSERT_EQ(text_input.get_character_to_the_left(), std::nullopt);
    ASSERT_EQ(text_input.size(), 0);
    ASSERT_TRUE(text_input.empty());
    ASSERT_EQ(text_input.get_cursor_index(), 0);
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().begin());
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().end());
    ASSERT_EQ(text_input.data(), "");
}

TEST(moving_cursor_to_right_must_fail_appropriately, after_single_character_a)
{
    yli::console::TextInput text_input;
    text_input.add_character('a');
    ASSERT_FALSE(text_input.move_cursor_right());
    ASSERT_EQ(text_input.get_character_at_current_index(), std::nullopt);
    ASSERT_EQ(text_input.get_character_to_the_left(), 'a');
    ASSERT_EQ(text_input.size(), 1);
    ASSERT_FALSE(text_input.empty());
    ASSERT_EQ(text_input.get_cursor_index(), 1);
    ASSERT_NE(text_input.get_cursor_it(), text_input.data().begin());
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().end());
    ASSERT_EQ(text_input.data(), "a");
}

TEST(moving_cursor_to_right_must_fail_appropriately, after_single_characters_a_b)
{
    yli::console::TextInput text_input;
    text_input.add_character('a');
    text_input.add_character('b');
    ASSERT_FALSE(text_input.move_cursor_right());
    ASSERT_EQ(text_input.get_character_at_current_index(), std::nullopt);
    ASSERT_EQ(text_input.get_character_to_the_left(), 'b');
    ASSERT_EQ(text_input.size(), 2);
    ASSERT_FALSE(text_input.empty());
    ASSERT_EQ(text_input.get_cursor_index(), 2);
    ASSERT_NE(text_input.get_cursor_it(), text_input.data().begin());
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().end());
    ASSERT_EQ(text_input.data(), "ab");
}

TEST(moving_cursor_to_right_must_succeed_appropriately, no_input_and_move_to_left)
{
    yli::console::TextInput text_input;
    text_input.move_cursor_left();
    ASSERT_FALSE(text_input.move_cursor_right());
    ASSERT_EQ(text_input.get_character_at_current_index(), std::nullopt);
    ASSERT_EQ(text_input.get_character_to_the_left(), std::nullopt);
    ASSERT_EQ(text_input.size(), 0);
    ASSERT_TRUE(text_input.empty());
    ASSERT_EQ(text_input.get_cursor_index(), 0);
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().begin());
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().end());
    ASSERT_EQ(text_input.data(), "");
}
TEST(moving_cursor_to_right_must_succeed_appropriately, after_single_character_a_and_move_to_left)
{
    yli::console::TextInput text_input;
    text_input.add_character('a');
    text_input.move_cursor_left();
    ASSERT_TRUE(text_input.move_cursor_right());
    ASSERT_EQ(text_input.get_character_at_current_index(), std::nullopt);
    ASSERT_EQ(text_input.get_character_to_the_left(), 'a');
    ASSERT_EQ(text_input.size(), 1);
    ASSERT_FALSE(text_input.empty());
    ASSERT_EQ(text_input.get_cursor_index(), 1);
    ASSERT_NE(text_input.get_cursor_it(), text_input.data().begin());
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().end());
    ASSERT_EQ(text_input.data(), "a");
}

TEST(moving_cursor_to_start_of_line_must_succeed_appropriately, no_input)
{
    yli::console::TextInput text_input;
    text_input.move_cursor_to_start_of_line();
    ASSERT_EQ(text_input.get_character_at_current_index(), std::nullopt);
    ASSERT_EQ(text_input.get_character_to_the_left(), std::nullopt);
    ASSERT_EQ(text_input.size(), 0);
    ASSERT_TRUE(text_input.empty());
    ASSERT_EQ(text_input.get_cursor_index(), 0);
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().begin());
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().end());
    ASSERT_EQ(text_input.data(), "");
}

TEST(moving_cursor_to_end_of_line_must_succeed_appropriately, no_input)
{
    yli::console::TextInput text_input;
    text_input.move_cursor_to_end_of_line();
    ASSERT_EQ(text_input.get_character_at_current_index(), std::nullopt);
    ASSERT_EQ(text_input.get_character_to_the_left(), std::nullopt);
    ASSERT_EQ(text_input.size(), 0);
    ASSERT_TRUE(text_input.empty());
    ASSERT_EQ(text_input.get_cursor_index(), 0);
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().begin());
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().end());
    ASSERT_EQ(text_input.data(), "");
}

TEST(moving_cursor_to_start_of_line_must_succeed_appropriately, after_single_character_a)
{
    yli::console::TextInput text_input;
    text_input.add_character('a');
    text_input.move_cursor_to_start_of_line();
    ASSERT_EQ(text_input.get_character_at_current_index(), 'a');
    ASSERT_EQ(text_input.get_character_to_the_left(), std::nullopt);
    ASSERT_EQ(text_input.size(), 1);
    ASSERT_FALSE(text_input.empty());
    ASSERT_EQ(text_input.get_cursor_index(), 0);
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().begin());
    ASSERT_NE(text_input.get_cursor_it(), text_input.data().end());
    ASSERT_EQ(text_input.data(), "a");
}

TEST(ctrl_w_must_succeed_appropriately, no_input)
{
    yli::console::TextInput text_input;
    text_input.ctrl_w();
    ASSERT_EQ(text_input.size(), 0);
    ASSERT_TRUE(text_input.empty());
    ASSERT_EQ(text_input.get_character_at_current_index(), std::nullopt);
    ASSERT_EQ(text_input.get_character_to_the_left(), std::nullopt);
    ASSERT_EQ(text_input.get_cursor_index(), 0);
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().begin());
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().end());
    ASSERT_EQ(text_input.data(), "");
}

TEST(ctrl_w_must_succeed_appropriately, single_character_a)
{
    yli::console::TextInput text_input;
    text_input.add_character('a');
    text_input.ctrl_w();
    ASSERT_EQ(text_input.size(), 0);
    ASSERT_TRUE(text_input.empty());
    ASSERT_EQ(text_input.get_character_at_current_index(), std::nullopt);
    ASSERT_EQ(text_input.get_character_to_the_left(), std::nullopt);
    ASSERT_EQ(text_input.get_cursor_index(), 0);
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().begin());
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().end());
    ASSERT_EQ(text_input.data(), "");
}

TEST(ctrl_w_must_succeed_appropriately, single_characters_a_b)
{
    yli::console::TextInput text_input;
    text_input.add_character('a');
    text_input.add_character('b');
    text_input.ctrl_w();
    ASSERT_EQ(text_input.size(), 0);
    ASSERT_TRUE(text_input.empty());
    ASSERT_EQ(text_input.get_character_at_current_index(), std::nullopt);
    ASSERT_EQ(text_input.get_character_to_the_left(), std::nullopt);
    ASSERT_EQ(text_input.get_cursor_index(), 0);
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().begin());
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().end());
    ASSERT_EQ(text_input.data(), "");
}

TEST(ctrl_w_must_succeed_appropriately, single_characters_a_space)
{
    yli::console::TextInput text_input;
    text_input.add_character('a');
    text_input.add_character(' ');
    text_input.ctrl_w();
    ASSERT_EQ(text_input.size(), 0);
    ASSERT_TRUE(text_input.empty());
    ASSERT_EQ(text_input.get_character_at_current_index(), std::nullopt);
    ASSERT_EQ(text_input.get_character_to_the_left(), std::nullopt);
    ASSERT_EQ(text_input.get_cursor_index(), 0);
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().begin());
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().end());
    ASSERT_EQ(text_input.data(), "");
}

TEST(ctrl_w_must_succeed_appropriately, single_characters_a_space_space)
{
    yli::console::TextInput text_input;
    text_input.add_character('a');
    text_input.add_character(' ');
    text_input.add_character(' ');
    text_input.ctrl_w();
    ASSERT_EQ(text_input.size(), 0);
    ASSERT_TRUE(text_input.empty());
    ASSERT_EQ(text_input.get_character_at_current_index(), std::nullopt);
    ASSERT_EQ(text_input.get_character_to_the_left(), std::nullopt);
    ASSERT_EQ(text_input.get_cursor_index(), 0);
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().begin());
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().end());
    ASSERT_EQ(text_input.data(), "");
}

TEST(ctrl_w_must_succeed_appropriately, single_characters_space_a)
{
    yli::console::TextInput text_input;
    text_input.add_character(' ');
    text_input.add_character('a');
    text_input.ctrl_w();
    ASSERT_EQ(text_input.size(), 1);
    ASSERT_FALSE(text_input.empty());
    ASSERT_EQ(text_input.get_character_at_current_index(), std::nullopt);
    ASSERT_EQ(text_input.get_character_to_the_left(), ' ');
    ASSERT_EQ(text_input.get_cursor_index(), 1);
    ASSERT_NE(text_input.get_cursor_it(), text_input.data().begin());
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().end());
    ASSERT_EQ(text_input.data(), " ");
}

TEST(ctrl_w_must_succeed_appropriately, single_characters_space_a_b)
{
    yli::console::TextInput text_input;
    text_input.add_character(' ');
    text_input.add_character('a');
    text_input.add_character('b');
    text_input.ctrl_w();
    ASSERT_EQ(text_input.size(), 1);
    ASSERT_FALSE(text_input.empty());
    ASSERT_EQ(text_input.get_character_at_current_index(), std::nullopt);
    ASSERT_EQ(text_input.get_character_to_the_left(), ' ');
    ASSERT_EQ(text_input.get_cursor_index(), 1);
    ASSERT_NE(text_input.get_cursor_it(), text_input.data().begin());
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().end());
    ASSERT_EQ(text_input.data(), " ");
}

TEST(ctrl_w_must_succeed_appropriately, single_characters_space_a_space)
{
    yli::console::TextInput text_input;
    text_input.add_character(' ');
    text_input.add_character('a');
    text_input.add_character(' ');
    text_input.ctrl_w();
    ASSERT_EQ(text_input.size(), 1);
    ASSERT_FALSE(text_input.empty());
    ASSERT_EQ(text_input.get_character_at_current_index(), std::nullopt);
    ASSERT_EQ(text_input.get_character_to_the_left(), ' ');
    ASSERT_EQ(text_input.get_cursor_index(), 1);
    ASSERT_NE(text_input.get_cursor_it(), text_input.data().begin());
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().end());
    ASSERT_EQ(text_input.data(), " ");
}

TEST(ctrl_w_must_succeed_appropriately, single_characters_space_space_a_b)
{
    yli::console::TextInput text_input;
    text_input.add_character(' ');
    text_input.add_character(' ');
    text_input.add_character('a');
    text_input.add_character('b');
    text_input.ctrl_w();
    ASSERT_EQ(text_input.size(), 2);
    ASSERT_FALSE(text_input.empty());
    ASSERT_EQ(text_input.get_character_at_current_index(), std::nullopt);
    ASSERT_EQ(text_input.get_character_to_the_left(), ' ');
    ASSERT_EQ(text_input.get_cursor_index(), 2);
    ASSERT_NE(text_input.get_cursor_it(), text_input.data().begin());
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().end());
    ASSERT_EQ(text_input.data(), "  ");
}

TEST(ctrl_w_must_succeed_appropriately, single_characters_space_space_a_b_space_space_c_d)
{
    yli::console::TextInput text_input;
    text_input.add_character(' ');
    text_input.add_character(' ');
    text_input.add_character('a');
    text_input.add_character('b');
    text_input.add_character(' ');
    text_input.add_character(' ');
    text_input.add_character('c');
    text_input.add_character('d');
    text_input.ctrl_w();
    ASSERT_EQ(text_input.size(), 6);
    ASSERT_FALSE(text_input.empty());
    ASSERT_EQ(text_input.get_character_at_current_index(), std::nullopt);
    ASSERT_EQ(text_input.get_character_to_the_left(), ' ');
    ASSERT_EQ(text_input.get_cursor_index(), 6);
    ASSERT_NE(text_input.get_cursor_it(), text_input.data().begin());
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().end());
    ASSERT_EQ(text_input.data(), "  ab  ");
}

TEST(ctrl_w_must_succeed_appropriately, single_characters_space_space_a_b_space_space_c_d_space)
{
    yli::console::TextInput text_input;
    text_input.add_character(' ');
    text_input.add_character(' ');
    text_input.add_character('a');
    text_input.add_character('b');
    text_input.add_character(' ');
    text_input.add_character(' ');
    text_input.add_character('c');
    text_input.add_character('d');
    text_input.add_character(' ');
    text_input.ctrl_w();
    ASSERT_EQ(text_input.size(), 6);
    ASSERT_FALSE(text_input.empty());
    ASSERT_EQ(text_input.get_character_at_current_index(), std::nullopt);
    ASSERT_EQ(text_input.get_character_to_the_left(), ' ');
    ASSERT_EQ(text_input.get_cursor_index(), 6);
    ASSERT_NE(text_input.get_cursor_it(), text_input.data().begin());
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().end());
    ASSERT_EQ(text_input.data(), "  ab  ");
}

TEST(ctrl_w_must_succeed_appropriately, single_characters_space_space_a_b_space_space_c_d_space_space)
{
    yli::console::TextInput text_input;
    text_input.add_character(' ');
    text_input.add_character(' ');
    text_input.add_character('a');
    text_input.add_character('b');
    text_input.add_character(' ');
    text_input.add_character(' ');
    text_input.add_character('c');
    text_input.add_character('d');
    text_input.add_character(' ');
    text_input.add_character(' ');
    text_input.ctrl_w();
    ASSERT_EQ(text_input.size(), 6);
    ASSERT_FALSE(text_input.empty());
    ASSERT_EQ(text_input.get_character_at_current_index(), std::nullopt);
    ASSERT_EQ(text_input.get_character_to_the_left(), ' ');
    ASSERT_EQ(text_input.get_cursor_index(), 6);
    ASSERT_NE(text_input.get_cursor_it(), text_input.data().begin());
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().end());
    ASSERT_EQ(text_input.data(), "  ab  ");
}

TEST(text_input_begin_iterator_must_work_appropriately, text_input_begin_iterator)
{
    yli::console::TextInput text_input;
    text_input.add_characters("abc");

    auto it = text_input.begin();
    ASSERT_EQ(*it, 'a');
    ++it;
    ASSERT_EQ(*it, 'b');
    ++it;
    ASSERT_EQ(*it, 'c');
    ++it;
    ASSERT_EQ(it, text_input.end());
}

TEST(text_input_cbegin_const_iterator_must_work_appropriately, text_input_cbegin_const_iterator)
{
    yli::console::TextInput text_input;
    text_input.add_characters("abc");

    auto it = text_input.cbegin();
    ASSERT_EQ(*it, 'a');
    ++it;
    ASSERT_EQ(*it, 'b');
    ++it;
    ASSERT_EQ(*it, 'c');
    ++it;
    ASSERT_EQ(it, text_input.cend());
}

TEST(text_input_end_iterator_must_work_appropriately, text_input_end_iterator)
{
    yli::console::TextInput text_input;
    text_input.add_characters("abc");

    auto it = text_input.end();
    --it;
    ASSERT_EQ(*it, 'c');
    --it;
    ASSERT_EQ(*it, 'b');
    --it;
    ASSERT_EQ(*it, 'a');
    ASSERT_EQ(it, text_input.begin());
}

TEST(text_input_cend_iterator_must_work_appropriately, text_input_cend_iterator)
{
    yli::console::TextInput text_input;
    text_input.add_characters("abc");

    auto it = text_input.cend();
    --it;
    ASSERT_EQ(*it, 'c');
    --it;
    ASSERT_EQ(*it, 'b');
    --it;
    ASSERT_EQ(*it, 'a');
    ASSERT_EQ(it, text_input.cbegin());
}

TEST(one_character_must_be_emplaced_back_to_the_text_input_appropriately, single_character_a)
{
    yli::console::TextInput text_input;
    text_input.emplace_back('a');
    ASSERT_EQ(text_input.get_character_at_current_index(), std::nullopt);
    ASSERT_EQ(text_input.get_character_to_the_left(), 'a');
    ASSERT_EQ(text_input.size(), 1);
    ASSERT_FALSE(text_input.empty());
    ASSERT_EQ(text_input.get_cursor_index(), 1);
    ASSERT_NE(text_input.get_cursor_it(), text_input.data().begin());
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().end());
    ASSERT_EQ(text_input.data(), "a");
}

TEST(one_character_must_be_pushed_back_to_the_text_input_appropriately, single_character_a)
{
    yli::console::TextInput text_input;
    text_input.push_back('a');
    ASSERT_EQ(text_input.get_character_at_current_index(), std::nullopt);
    ASSERT_EQ(text_input.get_character_to_the_left(), 'a');
    ASSERT_EQ(text_input.size(), 1);
    ASSERT_FALSE(text_input.empty());
    ASSERT_EQ(text_input.get_cursor_index(), 1);
    ASSERT_NE(text_input.get_cursor_it(), text_input.data().begin());
    ASSERT_EQ(text_input.get_cursor_it(), text_input.data().end());
    ASSERT_EQ(text_input.data(), "a");
}
