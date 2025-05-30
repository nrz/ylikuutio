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
#include "code/ylikuutio/data/codepoint.hpp"
#include "code/ylikuutio/console/console_state_module.hpp"
#include "code/ylikuutio/console/scrollback_buffer.hpp"
#include "code/ylikuutio/console/text_line.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <limits>   // std::numeric_limits
#include <optional> // std::nullopt

using yli::data::Codepoint;
using yli::console::TextLine;

TEST(scrollback_buffer_must_be_initialized_appropriately, line_width_0)
{
    yli::console::ConsoleStateModule console_state;
    yli::console::ScrollbackBuffer scrollback_buffer(console_state, 0);
    ASSERT_FALSE(scrollback_buffer.get_is_in_buffer());
    ASSERT_EQ(scrollback_buffer.size(), 0);
    ASSERT_TRUE(scrollback_buffer.empty());
    ASSERT_EQ(scrollback_buffer.get_line_width(), 1);
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(scrollback_buffer.get(), std::nullopt);
}

TEST(scrollback_buffer_must_be_initialized_appropriately, line_width_1)
{
    yli::console::ConsoleStateModule console_state;
    yli::console::ScrollbackBuffer scrollback_buffer(console_state, 1);
    ASSERT_FALSE(scrollback_buffer.get_is_in_buffer());
    ASSERT_EQ(scrollback_buffer.size(), 0);
    ASSERT_TRUE(scrollback_buffer.empty());
    ASSERT_EQ(scrollback_buffer.get_line_width(), 1);
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(scrollback_buffer.get(), std::nullopt);
}

TEST(scrollback_buffer_must_be_initialized_appropriately, line_width_2)
{
    yli::console::ConsoleStateModule console_state;
    yli::console::ScrollbackBuffer scrollback_buffer(console_state, 2);
    ASSERT_FALSE(scrollback_buffer.get_is_in_buffer());
    ASSERT_EQ(scrollback_buffer.size(), 0);
    ASSERT_TRUE(scrollback_buffer.empty());
    ASSERT_EQ(scrollback_buffer.get_line_width(), 2);
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(scrollback_buffer.get(), std::nullopt);
}

TEST(moving_to_previous_input_must_fail_appropriately, empty_scrollback_buffer_line_width_1)
{
    yli::console::ConsoleStateModule console_state;
    yli::console::ScrollbackBuffer scrollback_buffer(console_state, 1);
    ASSERT_FALSE(scrollback_buffer.move_to_previous());
    ASSERT_FALSE(scrollback_buffer.get_is_in_buffer());
    ASSERT_EQ(scrollback_buffer.size(), 0);
    ASSERT_TRUE(scrollback_buffer.empty());
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(scrollback_buffer.get(), std::nullopt);
}

TEST(moving_to_next_input_must_fail_appropriately, empty_scrollback_buffer_line_width_1)
{
    yli::console::ConsoleStateModule console_state;
    yli::console::ScrollbackBuffer scrollback_buffer(console_state, 1);
    ASSERT_FALSE(scrollback_buffer.move_to_next());
    ASSERT_FALSE(scrollback_buffer.get_is_in_buffer());
    ASSERT_EQ(scrollback_buffer.size(), 0);
    ASSERT_TRUE(scrollback_buffer.empty());
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(scrollback_buffer.get(), std::nullopt);
}

TEST(adding_empty_line_must_not_do_anything, scrollback_buffer_with_line_width_1_text_line_width_0)
{
    yli::console::ConsoleStateModule console_state;
    yli::console::ScrollbackBuffer scrollback_buffer(console_state, 1);
    scrollback_buffer.add_to_buffer(TextLine(std::vector<Codepoint>({})));
    ASSERT_FALSE(scrollback_buffer.get_is_in_buffer());
    ASSERT_EQ(scrollback_buffer.size(), 0);
    ASSERT_TRUE(scrollback_buffer.empty());
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), std::numeric_limits<std::size_t>::max());

    ASSERT_FALSE(scrollback_buffer.enter_buffer());
    ASSERT_EQ(scrollback_buffer.get_line_width(), 1);
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(scrollback_buffer.get(), std::nullopt);
}

TEST(adding_a_line_width_of_1_must_work_properly, scrollback_buffer_with_line_width_1_text_line_width_1)
{
    yli::console::ConsoleStateModule console_state;
    yli::console::ScrollbackBuffer scrollback_buffer(console_state, 1);
    const std::vector<Codepoint> char_container { Codepoint('a') };
    const yli::console::TextLine text_line(char_container);
    scrollback_buffer.add_to_buffer(text_line);
    ASSERT_FALSE(scrollback_buffer.get_is_in_buffer());
    ASSERT_EQ(scrollback_buffer.size(), 1);
    ASSERT_FALSE(scrollback_buffer.empty());
    ASSERT_EQ(scrollback_buffer.get_line_width(), 1);
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(scrollback_buffer.get(), std::nullopt);
    ASSERT_EQ(scrollback_buffer.at(0), text_line);

    ASSERT_TRUE(scrollback_buffer.enter_buffer());
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), 0);
}

TEST(adding_a_line_width_of_1_must_work_properly, scrollback_buffer_with_line_width_2_text_line_width_1)
{
    yli::console::ConsoleStateModule console_state;
    yli::console::ScrollbackBuffer scrollback_buffer(console_state, 2);
    const std::vector<Codepoint> char_container { Codepoint('a') };
    const yli::console::TextLine text_line(char_container);
    scrollback_buffer.add_to_buffer(text_line);
    ASSERT_FALSE(scrollback_buffer.get_is_in_buffer());
    ASSERT_EQ(scrollback_buffer.size(), 1);
    ASSERT_FALSE(scrollback_buffer.empty());
    ASSERT_EQ(scrollback_buffer.get_line_width(), 2);
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(scrollback_buffer.get(), std::nullopt);
    ASSERT_EQ(scrollback_buffer.at(0), text_line);

    ASSERT_TRUE(scrollback_buffer.enter_buffer());
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), 0);
}

TEST(adding_a_line_width_of_1_must_work_properly, scrollback_buffer_with_line_width_3_text_line_width_1)
{
    yli::console::ConsoleStateModule console_state;
    yli::console::ScrollbackBuffer scrollback_buffer(console_state, 3);
    const std::vector<Codepoint> char_container { Codepoint('a') };
    const yli::console::TextLine text_line(char_container);
    scrollback_buffer.add_to_buffer(text_line);
    ASSERT_FALSE(scrollback_buffer.get_is_in_buffer());
    ASSERT_EQ(scrollback_buffer.size(), 1);
    ASSERT_FALSE(scrollback_buffer.empty());
    ASSERT_EQ(scrollback_buffer.get_line_width(), 3);
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(scrollback_buffer.get(), std::nullopt);
    ASSERT_EQ(scrollback_buffer.at(0), text_line);

    ASSERT_TRUE(scrollback_buffer.enter_buffer());
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), 0);
}

TEST(adding_a_line_width_of_2_must_work_properly, scrollback_buffer_with_line_width_1_text_line_width_2)
{
    yli::console::ConsoleStateModule console_state;
    yli::console::ScrollbackBuffer scrollback_buffer(console_state, 1);
    const std::vector<Codepoint> char_container { Codepoint('a'), Codepoint('b') };
    const yli::console::TextLine text_line(char_container);
    scrollback_buffer.add_to_buffer(text_line);
    ASSERT_FALSE(scrollback_buffer.get_is_in_buffer());
    ASSERT_EQ(scrollback_buffer.size(), 2);
    ASSERT_FALSE(scrollback_buffer.empty());
    ASSERT_EQ(scrollback_buffer.get_line_width(), 1);
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(scrollback_buffer.get(), std::nullopt);

    const yli::console::TextLine expected_text_line_a({ Codepoint('a') });
    ASSERT_EQ(scrollback_buffer.at(0), expected_text_line_a);
    const yli::console::TextLine expected_text_line_b({ Codepoint('b') });
    ASSERT_EQ(scrollback_buffer.at(1), expected_text_line_b);

    ASSERT_TRUE(scrollback_buffer.enter_buffer());
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), 1);
}

TEST(adding_a_line_width_of_2_must_work_properly, scrollback_buffer_with_line_width_2_text_line_width_2)
{
    yli::console::ConsoleStateModule console_state;
    yli::console::ScrollbackBuffer scrollback_buffer(console_state, 2);
    const std::vector<Codepoint> char_container { Codepoint('a'), Codepoint('b') };
    const yli::console::TextLine text_line(char_container);
    scrollback_buffer.add_to_buffer(text_line);
    ASSERT_FALSE(scrollback_buffer.get_is_in_buffer());
    ASSERT_EQ(scrollback_buffer.size(), 1);
    ASSERT_FALSE(scrollback_buffer.empty());
    ASSERT_EQ(scrollback_buffer.get_line_width(), 2);
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(scrollback_buffer.get(), std::nullopt);

    const yli::console::TextLine expected_text_line_ab({ Codepoint('a'), Codepoint('b') });
    ASSERT_EQ(scrollback_buffer.at(0), expected_text_line_ab);

    ASSERT_TRUE(scrollback_buffer.enter_buffer());
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), 0);
}

TEST(adding_a_line_width_of_2_must_work_properly, scrollback_buffer_with_line_width_3_text_line_width_2)
{
    yli::console::ConsoleStateModule console_state;
    yli::console::ScrollbackBuffer scrollback_buffer(console_state, 3);
    const std::vector<Codepoint> char_container { Codepoint('a'), Codepoint('b') };
    const yli::console::TextLine text_line(char_container);
    scrollback_buffer.add_to_buffer(text_line);
    ASSERT_FALSE(scrollback_buffer.get_is_in_buffer());
    ASSERT_EQ(scrollback_buffer.size(), 1);
    ASSERT_FALSE(scrollback_buffer.empty());
    ASSERT_EQ(scrollback_buffer.get_line_width(), 3);
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(scrollback_buffer.get(), std::nullopt);

    const yli::console::TextLine expected_text_line_ab({ Codepoint('a'), Codepoint('b') });
    ASSERT_EQ(scrollback_buffer.at(0), expected_text_line_ab);

    ASSERT_TRUE(scrollback_buffer.enter_buffer());
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), 0);
}

TEST(adding_a_line_width_of_3_must_work_properly, scrollback_buffer_with_line_width_1_text_line_width_3)
{
    yli::console::ConsoleStateModule console_state;
    yli::console::ScrollbackBuffer scrollback_buffer(console_state, 1);
    const std::vector<Codepoint> char_container { Codepoint('a'), Codepoint('b'), Codepoint('c') };
    const yli::console::TextLine text_line(char_container);
    scrollback_buffer.add_to_buffer(text_line);
    ASSERT_FALSE(scrollback_buffer.get_is_in_buffer());
    ASSERT_EQ(scrollback_buffer.size(), 3);
    ASSERT_FALSE(scrollback_buffer.empty());
    ASSERT_EQ(scrollback_buffer.get_line_width(), 1);
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(scrollback_buffer.get(), std::nullopt);

    const yli::console::TextLine expected_text_line_a({ Codepoint('a') });
    ASSERT_EQ(scrollback_buffer.at(0), expected_text_line_a);
    const yli::console::TextLine expected_text_line_b({ Codepoint('b') });
    ASSERT_EQ(scrollback_buffer.at(1), expected_text_line_b);
    const yli::console::TextLine expected_text_line_c({ Codepoint('c') });
    ASSERT_EQ(scrollback_buffer.at(2), expected_text_line_c);

    ASSERT_TRUE(scrollback_buffer.enter_buffer());
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), 2);
}

TEST(adding_a_line_width_of_3_must_work_properly, scrollback_buffer_with_line_width_2_text_line_width_3)
{
    yli::console::ConsoleStateModule console_state;
    yli::console::ScrollbackBuffer scrollback_buffer(console_state, 2);
    const std::vector<Codepoint> char_container { Codepoint('a'), Codepoint('b'), Codepoint('c') };
    const yli::console::TextLine text_line(char_container);
    scrollback_buffer.add_to_buffer(text_line);
    ASSERT_FALSE(scrollback_buffer.get_is_in_buffer());
    ASSERT_EQ(scrollback_buffer.size(), 2);
    ASSERT_FALSE(scrollback_buffer.empty());
    ASSERT_EQ(scrollback_buffer.get_line_width(), 2);
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(scrollback_buffer.get(), std::nullopt);

    const yli::console::TextLine expected_text_line_ab({ Codepoint('a'), Codepoint('b') });
    ASSERT_EQ(scrollback_buffer.at(0), expected_text_line_ab);
    const yli::console::TextLine expected_text_line_c({ Codepoint('c') });
    ASSERT_EQ(scrollback_buffer.at(1), expected_text_line_c);

    ASSERT_TRUE(scrollback_buffer.enter_buffer());
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), 1);
}

TEST(adding_a_line_width_of_3_must_work_properly, scrollback_buffer_with_line_width_3_text_line_width_3)
{
    yli::console::ConsoleStateModule console_state;
    yli::console::ScrollbackBuffer scrollback_buffer(console_state, 3);
    const std::vector<Codepoint> char_container { Codepoint('a'), Codepoint('b'), Codepoint('c') };
    const yli::console::TextLine text_line(char_container);
    scrollback_buffer.add_to_buffer(text_line);
    ASSERT_FALSE(scrollback_buffer.get_is_in_buffer());
    ASSERT_EQ(scrollback_buffer.size(), 1);
    ASSERT_FALSE(scrollback_buffer.empty());
    ASSERT_EQ(scrollback_buffer.get_line_width(), 3);
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(scrollback_buffer.get(), std::nullopt);

    const yli::console::TextLine expected_text_line_abc({ Codepoint('a'), Codepoint('b'), Codepoint('c') });
    ASSERT_EQ(scrollback_buffer.at(0), expected_text_line_abc);

    ASSERT_TRUE(scrollback_buffer.enter_buffer());
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), 0);
}

TEST(adding_a_line_width_of_3_must_work_properly, scrollback_buffer_with_line_width_1_text_input_width_3)
{
    yli::console::TextInput text_input;
    const std::vector<Codepoint> char_container { Codepoint('a'), Codepoint('b'), Codepoint('c') };
    text_input.add_characters(char_container);

    yli::console::ConsoleStateModule console_state;
    yli::console::ScrollbackBuffer scrollback_buffer(console_state, 1);
    scrollback_buffer.add_to_buffer(text_input);
    ASSERT_FALSE(scrollback_buffer.get_is_in_buffer());
    ASSERT_EQ(scrollback_buffer.size(), 3);
    ASSERT_FALSE(scrollback_buffer.empty());
    ASSERT_EQ(scrollback_buffer.get_line_width(), 1);
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(scrollback_buffer.get(), std::nullopt);

    const yli::console::TextLine expected_text_line_a({ Codepoint('a') });
    ASSERT_EQ(scrollback_buffer.at(0), expected_text_line_a);
    const yli::console::TextLine expected_text_line_b({ Codepoint('b') });
    ASSERT_EQ(scrollback_buffer.at(1), expected_text_line_b);
    const yli::console::TextLine expected_text_line_c({ Codepoint('c') });
    ASSERT_EQ(scrollback_buffer.at(2), expected_text_line_c);

    ASSERT_TRUE(scrollback_buffer.enter_buffer());
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), 2);
}

TEST(adding_a_line_width_of_3_must_work_properly, scrollback_buffer_with_line_width_2_text_input_width_3)
{
    yli::console::TextInput text_input;
    const std::vector<Codepoint> char_container { Codepoint('a'), Codepoint('b'), Codepoint('c') };
    text_input.add_characters(char_container);

    yli::console::ConsoleStateModule console_state;
    yli::console::ScrollbackBuffer scrollback_buffer(console_state, 2);
    scrollback_buffer.add_to_buffer(text_input);
    ASSERT_FALSE(scrollback_buffer.get_is_in_buffer());
    ASSERT_EQ(scrollback_buffer.size(), 2);
    ASSERT_FALSE(scrollback_buffer.empty());
    ASSERT_EQ(scrollback_buffer.get_line_width(), 2);
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(scrollback_buffer.get(), std::nullopt);

    const yli::console::TextLine expected_text_line_ab({ Codepoint('a'), Codepoint('b') });
    ASSERT_EQ(scrollback_buffer.at(0), expected_text_line_ab);
    const yli::console::TextLine expected_text_line_c({ Codepoint('c') });
    ASSERT_EQ(scrollback_buffer.at(1), expected_text_line_c);

    ASSERT_TRUE(scrollback_buffer.enter_buffer());
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), 1);
}

TEST(adding_a_line_width_of_3_must_work_properly, scrollback_buffer_with_line_width_3_text_input_width_3)
{
    yli::console::TextInput text_input;
    const std::vector<Codepoint> char_container { Codepoint('a'), Codepoint('b'), Codepoint('c') };
    text_input.add_characters(char_container);

    yli::console::ConsoleStateModule console_state;
    yli::console::ScrollbackBuffer scrollback_buffer(console_state, 3);
    scrollback_buffer.add_to_buffer(text_input);
    ASSERT_FALSE(scrollback_buffer.get_is_in_buffer());
    ASSERT_EQ(scrollback_buffer.size(), 1);
    ASSERT_FALSE(scrollback_buffer.empty());
    ASSERT_EQ(scrollback_buffer.get_line_width(), 3);
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(scrollback_buffer.get(), std::nullopt);

    const yli::console::TextLine expected_text_line_abc({ Codepoint('a'), Codepoint('b'), Codepoint('c') });
    ASSERT_EQ(scrollback_buffer.at(0), expected_text_line_abc);

    ASSERT_TRUE(scrollback_buffer.enter_buffer());
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), 0);
}

TEST(scrollback_buffer_begin_iterator_must_work_appropriately, scrollback_buffer_line_width_3_begin_iterator)
{
    const std::vector<Codepoint> abc_char_container { Codepoint('a'), Codepoint('b'), Codepoint('c') };
    const std::vector<Codepoint> def_char_container { Codepoint('d'), Codepoint('e'), Codepoint('f') };
    const std::vector<Codepoint> ghi_char_container { Codepoint('g'), Codepoint('h'), Codepoint('i') };

    yli::console::ConsoleStateModule console_state;
    yli::console::ScrollbackBuffer scrollback_buffer(console_state, 3);
    {
        yli::console::TextInput text_input;
        text_input.add_characters(abc_char_container);
        scrollback_buffer.add_to_buffer(text_input);
    }
    {
        yli::console::TextInput text_input;
        text_input.add_characters(def_char_container);
        scrollback_buffer.add_to_buffer(text_input);
    }
    {
        yli::console::TextInput text_input;
        text_input.add_characters(ghi_char_container);
        scrollback_buffer.add_to_buffer(text_input);
    }

    auto it = scrollback_buffer.begin();
    ASSERT_EQ((*it).data(), abc_char_container);
    ++it;
    ASSERT_EQ((*it).data(), def_char_container);
    ++it;
    ASSERT_EQ((*it).data(), ghi_char_container);
    ++it;
    ASSERT_EQ(it, scrollback_buffer.end());
}

TEST(scrollback_buffer_cbegin_iterator_must_work_appropriately, scrollback_buffer_line_width_3_cbegin_iterator)
{
    const std::vector<Codepoint> abc_char_container { Codepoint('a'), Codepoint('b'), Codepoint('c') };
    const std::vector<Codepoint> def_char_container { Codepoint('d'), Codepoint('e'), Codepoint('f') };
    const std::vector<Codepoint> ghi_char_container { Codepoint('g'), Codepoint('h'), Codepoint('i') };

    yli::console::ConsoleStateModule console_state;
    yli::console::ScrollbackBuffer scrollback_buffer(console_state, 3);
    {
        yli::console::TextInput text_input;
        text_input.add_characters(abc_char_container);
        scrollback_buffer.add_to_buffer(text_input);
    }
    {
        yli::console::TextInput text_input;
        text_input.add_characters(def_char_container);
        scrollback_buffer.add_to_buffer(text_input);
    }
    {
        yli::console::TextInput text_input;
        text_input.add_characters(ghi_char_container);
        scrollback_buffer.add_to_buffer(text_input);
    }

    auto it = scrollback_buffer.cbegin();
    ASSERT_EQ((*it).data(), abc_char_container);
    ++it;
    ASSERT_EQ((*it).data(), def_char_container);
    ++it;
    ASSERT_EQ((*it).data(), ghi_char_container);
    ++it;
    ASSERT_EQ(it, scrollback_buffer.cend());
}

TEST(scrollback_buffer_end_iterator_must_work_appropriately, scrollback_buffer_line_width_3_end_iterator)
{
    const std::vector<Codepoint> abc_char_container { Codepoint('a'), Codepoint('b'), Codepoint('c') };
    const std::vector<Codepoint> def_char_container { Codepoint('d'), Codepoint('e'), Codepoint('f') };
    const std::vector<Codepoint> ghi_char_container { Codepoint('g'), Codepoint('h'), Codepoint('i') };

    yli::console::ConsoleStateModule console_state;
    yli::console::ScrollbackBuffer scrollback_buffer(console_state, 3);
    {
        yli::console::TextInput text_input;
        text_input.add_characters(abc_char_container);
        scrollback_buffer.add_to_buffer(text_input);
    }
    {
        yli::console::TextInput text_input;
        text_input.add_characters(def_char_container);
        scrollback_buffer.add_to_buffer(text_input);
    }
    {
        yli::console::TextInput text_input;
        text_input.add_characters(ghi_char_container);
        scrollback_buffer.add_to_buffer(text_input);
    }

    auto it = scrollback_buffer.end();
    --it;
    ASSERT_EQ((*it).data(), ghi_char_container);
    --it;
    ASSERT_EQ((*it).data(), def_char_container);
    --it;
    ASSERT_EQ((*it).data(), abc_char_container);
    ASSERT_EQ(it, scrollback_buffer.begin());
}

TEST(scrollback_buffer_cend_iterator_must_work_appropriately, scrollback_buffer_line_width_3_cend_iterator)
{
    const std::vector<Codepoint> abc_char_container { Codepoint('a'), Codepoint('b'), Codepoint('c') };
    const std::vector<Codepoint> def_char_container { Codepoint('d'), Codepoint('e'), Codepoint('f') };
    const std::vector<Codepoint> ghi_char_container { Codepoint('g'), Codepoint('h'), Codepoint('i') };

    yli::console::ConsoleStateModule console_state;
    yli::console::ScrollbackBuffer scrollback_buffer(console_state, 3);
    {
        yli::console::TextInput text_input;
        text_input.add_characters(abc_char_container);
        scrollback_buffer.add_to_buffer(text_input);
    }
    {
        yli::console::TextInput text_input;
        text_input.add_characters(def_char_container);
        scrollback_buffer.add_to_buffer(text_input);
    }
    {
        yli::console::TextInput text_input;
        text_input.add_characters(ghi_char_container);
        scrollback_buffer.add_to_buffer(text_input);
    }

    auto it = scrollback_buffer.cend();
    --it;
    ASSERT_EQ((*it).data(), ghi_char_container);
    --it;
    ASSERT_EQ((*it).data(), def_char_container);
    --it;
    ASSERT_EQ((*it).data(), abc_char_container);
    ASSERT_EQ(it, scrollback_buffer.cbegin());
}

TEST(emplacing_back_a_line_width_of_1_must_work_properly, scrollback_buffer_with_line_width_1_text_line_width_1)
{
    yli::console::ConsoleStateModule console_state;
    yli::console::ScrollbackBuffer scrollback_buffer(console_state, 1);
    const std::vector<Codepoint> char_container { Codepoint('a') };
    const yli::console::TextLine text_line(char_container);
    scrollback_buffer.emplace_back(text_line);
    ASSERT_EQ(scrollback_buffer.size(), 1);
    ASSERT_FALSE(scrollback_buffer.empty());
    ASSERT_EQ(scrollback_buffer.get_line_width(), 1);
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(scrollback_buffer.get(), std::nullopt);
    ASSERT_EQ(scrollback_buffer.at(0), text_line);
}

TEST(pushing_back_a_line_width_of_1_must_work_properly, scrollback_buffer_with_line_width_1_text_line_width_1)
{
    yli::console::ConsoleStateModule console_state;
    yli::console::ScrollbackBuffer scrollback_buffer(console_state, 1);
    const std::vector<Codepoint> char_container { Codepoint('a') };
    const yli::console::TextLine text_line(char_container);
    scrollback_buffer.push_back(text_line);
    ASSERT_EQ(scrollback_buffer.size(), 1);
    ASSERT_FALSE(scrollback_buffer.empty());
    ASSERT_EQ(scrollback_buffer.get_line_width(), 1);
    ASSERT_EQ(scrollback_buffer.get_buffer_index(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(scrollback_buffer.get(), std::nullopt);
    ASSERT_EQ(scrollback_buffer.at(0), text_line);
}
