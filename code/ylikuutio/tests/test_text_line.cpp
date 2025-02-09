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
#include "code/ylikuutio/data/codepoint.hpp"

// Include standard headers
#include <string> // std::string
#include <vector> // std::vector

using yli::data::Codepoint;

TEST(text_line_must_be_initialized_appropriately, empty_text_line)
{
    const std::vector<Codepoint> char_container {};
    yli::console::TextLine text_line(char_container);
    ASSERT_EQ(text_line.data(), char_container);
    ASSERT_EQ(text_line.to_string(), "");
    ASSERT_EQ(text_line.size(), 0);
    ASSERT_EQ(text_line.cbegin().unwrap(), text_line.data().cbegin());
}

TEST(text_line_must_be_initialized_appropriately, text_line)
{
    const std::vector<Codepoint> char_container { Codepoint('a'), Codepoint('b'), Codepoint('c') };
    yli::console::TextLine text_line(char_container);
    ASSERT_EQ(text_line.data(), char_container);
    ASSERT_EQ(text_line.to_string(), "abc");
    ASSERT_EQ(text_line.size(), 3);
}

TEST(text_line_must_be_initialized_appropriately, from_text_input)
{
    yli::console::TextInput text_input;
    const std::vector<Codepoint> char_container { Codepoint('a'), Codepoint('b'), Codepoint('c') };
    text_input.add_characters(char_container);

    yli::console::TextLine text_line(text_input);
    ASSERT_EQ(text_line.data(), char_container);
    ASSERT_EQ(text_line.to_string(), "abc");
    ASSERT_EQ(text_line.size(), 3);
}

TEST(text_line_must_be_initialized_appropriatel_using_begin_and_end_iterators, empty_string_begin_0_end_0)
{
    const std::vector<Codepoint> char_container {};
    yli::console::TextLine text_line(char_container.cbegin(), char_container.cbegin());
    ASSERT_EQ(text_line.data(), char_container);
    ASSERT_EQ(text_line.to_string(), "");
    ASSERT_EQ(text_line.size(), 0);
}

TEST(text_line_must_be_initialized_appropriatel_using_begin_and_end_iterators, a_string_begin_0_end_0)
{
    const std::vector<Codepoint> char_container { Codepoint('a') };
    yli::console::TextLine text_line(char_container.cbegin(), char_container.cbegin());
    ASSERT_EQ(text_line.data(), std::vector<Codepoint>{});
    ASSERT_EQ(text_line.to_string(), "");
    ASSERT_EQ(text_line.size(), 0);
}

TEST(text_line_must_be_initialized_appropriatel_using_begin_and_end_iterators, a_string_begin_0_end_1)
{
    const std::vector<Codepoint> char_container { Codepoint('a') };
    yli::console::TextLine text_line(char_container.cbegin(), char_container.cbegin() + 1);
    ASSERT_EQ(text_line.data(), char_container);
    ASSERT_EQ(text_line.to_string(), "a");
    ASSERT_EQ(text_line.size(), 1);
}

TEST(text_line_must_be_initialized_appropriatel_using_begin_and_end_iterators, a_string_begin_1_end_1)
{
    const std::vector<Codepoint> char_container { Codepoint('a') };
    yli::console::TextLine text_line(char_container.cbegin() + 1, char_container.cbegin() + 1);
    ASSERT_EQ(text_line.data(), std::vector<Codepoint>{});
    ASSERT_EQ(text_line.to_string(), "");
    ASSERT_EQ(text_line.size(), 0);
}

TEST(text_line_must_be_initialized_appropriatel_using_begin_and_end_iterators, abc_begin_0_end_0)
{
    const std::vector<Codepoint> char_container { Codepoint('a'), Codepoint('b'), Codepoint('c') };
    yli::console::TextLine text_line(char_container.cbegin(), char_container.cbegin());
    ASSERT_EQ(text_line.data(), std::vector<Codepoint>{});
    ASSERT_EQ(text_line.to_string(), "");
    ASSERT_EQ(text_line.size(), 0);
}

TEST(text_line_must_be_initialized_appropriatel_using_begin_and_end_iterators, abc_begin_0_end_1)
{
    const std::vector<Codepoint> char_container { Codepoint('a'), Codepoint('b'), Codepoint('c') };
    yli::console::TextLine text_line(char_container.cbegin(), char_container.cbegin() + 1);
    const std::vector<Codepoint> expected { Codepoint('a') };
    ASSERT_EQ(text_line.data(), expected);
    ASSERT_EQ(text_line.to_string(), "a");
    ASSERT_EQ(text_line.size(), 1);
}

TEST(text_line_must_be_initialized_appropriatel_using_begin_and_end_iterators, abc_begin_0_end_2)
{
    const std::vector<Codepoint> char_container { Codepoint('a'), Codepoint('b'), Codepoint('c') };
    yli::console::TextLine text_line(char_container.cbegin(), char_container.cbegin() + 2);
    const std::vector<Codepoint> expected { Codepoint('a'), Codepoint('b') };
    ASSERT_EQ(text_line.data(), expected);
    ASSERT_EQ(text_line.to_string(), "ab");
    ASSERT_EQ(text_line.size(), 2);
}

TEST(text_line_must_be_initialized_appropriatel_using_begin_and_end_iterators, abc_begin_0_end_3)
{
    const std::vector<Codepoint> char_container { Codepoint('a'), Codepoint('b'), Codepoint('c') };
    yli::console::TextLine text_line(char_container.cbegin(), char_container.cbegin() + 3);
    ASSERT_EQ(text_line.data(), char_container);
    ASSERT_EQ(text_line.to_string(), "abc");
    ASSERT_EQ(text_line.size(), 3);
}

TEST(text_line_must_be_initialized_appropriatel_using_begin_and_end_iterators, abc_begin_1_end_1)
{
    const std::vector<Codepoint> char_container { Codepoint('a'), Codepoint('b'), Codepoint('c') };
    yli::console::TextLine text_line(char_container.cbegin() + 1, char_container.cbegin() + 1);
    ASSERT_EQ(text_line.data(), std::vector<Codepoint>{});
    ASSERT_EQ(text_line.to_string(), "");
    ASSERT_EQ(text_line.size(), 0);
}

TEST(text_line_must_be_initialized_appropriatel_using_begin_and_end_iterators, abc_begin_1_end_2)
{
    const std::vector<Codepoint> char_container { Codepoint('a'), Codepoint('b'), Codepoint('c') };
    yli::console::TextLine text_line(char_container.cbegin() + 1, char_container.cbegin() + 2);
    const std::vector<Codepoint> expected { Codepoint('b') };
    ASSERT_EQ(text_line.data(), expected);
    ASSERT_EQ(text_line.to_string(), "b");
    ASSERT_EQ(text_line.size(), 1);
}

TEST(text_line_must_be_initialized_appropriatel_using_begin_and_end_iterators, abc_begin_1_end_3)
{
    const std::vector<Codepoint> char_container { Codepoint('a'), Codepoint('b'), Codepoint('c') };
    yli::console::TextLine text_line(char_container.cbegin() + 1, char_container.cbegin() + 3);
    const std::vector<Codepoint> expected { Codepoint('b'), Codepoint('c') };
    ASSERT_EQ(text_line.data(), expected);
    ASSERT_EQ(text_line.to_string(), "bc");
    ASSERT_EQ(text_line.size(), 2);
}

TEST(text_line_must_be_initialized_appropriatel_using_begin_and_end_iterators, abc_begin_2_end_2)
{
    const std::vector<Codepoint> char_container { Codepoint('a'), Codepoint('b'), Codepoint('c') };
    yli::console::TextLine text_line(char_container.cbegin() + 2, char_container.cbegin() + 2);
    ASSERT_EQ(text_line.data(), std::vector<Codepoint>{});
    ASSERT_EQ(text_line.to_string(), "");
    ASSERT_EQ(text_line.size(), 0);
}

TEST(text_line_must_be_initialized_appropriatel_using_begin_and_end_iterators, abc_begin_2_end_3)
{
    const std::vector<Codepoint> char_container { Codepoint('a'), Codepoint('b'), Codepoint('c') };
    yli::console::TextLine text_line(char_container.cbegin() + 2, char_container.cbegin() + 3);
    const std::vector<Codepoint> expected { Codepoint('c') };
    ASSERT_EQ(text_line.data(), expected);
    ASSERT_EQ(text_line.to_string(), "c");
    ASSERT_EQ(text_line.size(), 1);
}

TEST(text_line_must_be_initialized_appropriatel_using_begin_and_end_iterators, abc_begin_3_end_3)
{
    const std::vector<Codepoint> char_container { Codepoint('a'), Codepoint('b'), Codepoint('c') };
    yli::console::TextLine text_line(char_container.cbegin() + 3, char_container.cbegin() + 3);
    ASSERT_EQ(text_line.data(), std::vector<Codepoint>{});
    ASSERT_EQ(text_line.to_string(), "");
    ASSERT_EQ(text_line.size(), 0);
}

TEST(text_line_cbegin_const_iterator_must_work_appropriately, text_line_cbegin_const_iterator)
{
    const std::vector<Codepoint> char_container { Codepoint('a'), Codepoint('b'), Codepoint('c') };
    yli::console::TextLine text_line(char_container);

    auto it = text_line.cbegin();
    ASSERT_EQ(*it, Codepoint('a'));
    ++it;
    ASSERT_EQ(*it, Codepoint('b'));
    ++it;
    ASSERT_EQ(*it, Codepoint('c'));
    ++it;
    ASSERT_EQ(it, text_line.cend());
    ASSERT_EQ(text_line.size(), 3);
}

TEST(text_line_cend_iterator_must_work_appropriately, text_line_cend_iterator)
{
    const std::vector<Codepoint> char_container { Codepoint('a'), Codepoint('b'), Codepoint('c') };
    yli::console::TextLine text_line(char_container);

    auto it = text_line.cend();
    --it;
    ASSERT_EQ(*it, Codepoint('c'));
    --it;
    ASSERT_EQ(*it, Codepoint('b'));
    --it;
    ASSERT_EQ(*it, Codepoint('a'));
    ASSERT_EQ(it, text_line.cbegin());
    ASSERT_EQ(text_line.size(), 3);
}

TEST(text_line_must_be_initialized_appropriately, from_text_line_begin_end_iterators)
{
    const std::vector<Codepoint> abcdef_char_container { Codepoint('a'), Codepoint('b'), Codepoint('c'), Codepoint('d'), Codepoint('e'), Codepoint('f') };
    yli::console::TextLine abcdef_text_line(abcdef_char_container);
    yli::console::TextLine cd_text_line(abcdef_text_line.data().begin() + 2, abcdef_text_line.data().begin() + 4);

    const std::vector<Codepoint> cd_char_container { Codepoint('c'), Codepoint('d') };
    yli::console::TextLine expected_text_line(cd_char_container);
    ASSERT_EQ(cd_text_line.data(), expected_text_line.data());
}

TEST(text_line_must_be_initialized_appropriately, from_text_input_begin_end_iterators)
{
    yli::console::TextInput text_input;
    const std::vector<Codepoint> abcdef_char_container { Codepoint('a'), Codepoint('b'), Codepoint('c'), Codepoint('d'), Codepoint('e'), Codepoint('f') };
    text_input.add_characters(abcdef_char_container);
    yli::console::TextLine cd_text_line(text_input.data().begin() + 2, text_input.data().begin() + 4);

    const std::vector<Codepoint> cd_char_container { Codepoint('c'), Codepoint('d') };
    yli::console::TextLine expected_text_line(cd_char_container);
    ASSERT_EQ(cd_text_line.data(), expected_text_line.data());
}

TEST(text_line_must_be_initialized_appropriately, from_reference_to_const_std_string)
{
    const std::string abc_string("abc");
    yli::console::TextLine text_line(abc_string);

    const std::vector<Codepoint> abc_char_container { Codepoint('a'), Codepoint('b'), Codepoint('c') };
    ASSERT_EQ(text_line.data(), abc_char_container);
    ASSERT_EQ(text_line.size(), 3);
}
