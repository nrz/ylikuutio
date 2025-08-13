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

// Include standard headers
#include <string_view> // std::string_view

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
    yli::console::TextInput text_input;
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

TEST(text_line_cbegin_const_iterator_must_work_appropriately, text_line_cbegin_const_iterator)
{
    std::string_view my_string { "abc" };
    yli::console::TextLine text_line(my_string);

    auto it = text_line.cbegin();
    ASSERT_EQ(*it, U'a');
    ++it;
    ASSERT_EQ(*it, U'b');
    ++it;
    ASSERT_EQ(*it, U'c');
    ++it;
    ASSERT_EQ(it, text_line.cend());
    ASSERT_EQ(text_line.size(), 3);
}

TEST(text_line_cend_iterator_must_work_appropriately, text_line_cend_iterator)
{
    std::string_view my_string { "abc" };
    yli::console::TextLine text_line(my_string);

    auto it = text_line.cend();
    --it;
    ASSERT_EQ(*it, U'c');
    --it;
    ASSERT_EQ(*it, U'b');
    --it;
    ASSERT_EQ(*it, U'a');
    ASSERT_EQ(it, text_line.cbegin());
    ASSERT_EQ(text_line.size(), 3);
}
