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
#include "code/ylikuutio/console/scrollback_buffer.hpp"
#include "code/ylikuutio/console/text_line.hpp"

using yli::data::Codepoint;
using yli::console::TextLine;

TEST(scrollback_buffer_must_be_initialized_appropriately, line_width_0)
{
    yli::console::ScrollbackBuffer scrollback_buffer(0);
    ASSERT_EQ(scrollback_buffer.size(), 0);
    ASSERT_EQ(scrollback_buffer.get_line_width(), 1);
}

TEST(scrollback_buffer_must_be_initialized_appropriately, line_width_1)
{
    yli::console::ScrollbackBuffer scrollback_buffer(1);
    ASSERT_EQ(scrollback_buffer.size(), 0);
    ASSERT_EQ(scrollback_buffer.get_line_width(), 1);
}

TEST(scrollback_buffer_must_be_initialized_appropriately, line_width_2)
{
    yli::console::ScrollbackBuffer scrollback_buffer(2);
    ASSERT_EQ(scrollback_buffer.size(), 0);
    ASSERT_EQ(scrollback_buffer.get_line_width(), 2);
}

TEST(adding_empty_line_must_not_do_anything, scrollback_buffer_with_line_width_1_text_line_width_0)
{
    yli::console::ScrollbackBuffer scrollback_buffer(1);
    scrollback_buffer.add_to_buffer(TextLine(std::vector<Codepoint>({})));
    ASSERT_EQ(scrollback_buffer.size(), 0);
    ASSERT_EQ(scrollback_buffer.get_line_width(), 1);
}

TEST(adding_a_line_width_of_1_must_work_properly, scrollback_buffer_with_line_width_1_text_line_width_1)
{
    yli::console::ScrollbackBuffer scrollback_buffer(1);
    const std::vector<Codepoint> char_container { Codepoint('a') };
    const yli::console::TextLine text_line(char_container);
    scrollback_buffer.add_to_buffer(text_line);
    ASSERT_EQ(scrollback_buffer.size(), 1);
    ASSERT_EQ(scrollback_buffer.get_line_width(), 1);
    ASSERT_EQ(scrollback_buffer.get_nth(0), text_line);
}

TEST(adding_a_line_width_of_1_must_work_properly, scrollback_buffer_with_line_width_2_text_line_width_1)
{
    yli::console::ScrollbackBuffer scrollback_buffer(2);
    const std::vector<Codepoint> char_container { Codepoint('a') };
    const yli::console::TextLine text_line(char_container);
    scrollback_buffer.add_to_buffer(text_line);
    ASSERT_EQ(scrollback_buffer.size(), 1);
    ASSERT_EQ(scrollback_buffer.get_line_width(), 2);
    ASSERT_EQ(scrollback_buffer.get_nth(0), text_line);
}

TEST(adding_a_line_width_of_1_must_work_properly, scrollback_buffer_with_line_width_3_text_line_width_1)
{
    yli::console::ScrollbackBuffer scrollback_buffer(3);
    const std::vector<Codepoint> char_container { Codepoint('a') };
    const yli::console::TextLine text_line(char_container);
    scrollback_buffer.add_to_buffer(text_line);
    ASSERT_EQ(scrollback_buffer.size(), 1);
    ASSERT_EQ(scrollback_buffer.get_line_width(), 3);
    ASSERT_EQ(scrollback_buffer.get_nth(0), text_line);
}

TEST(adding_a_line_width_of_2_must_work_properly, scrollback_buffer_with_line_width_1_text_line_width_2)
{
    yli::console::ScrollbackBuffer scrollback_buffer(1);
    const std::vector<Codepoint> char_container { Codepoint('a'), Codepoint('b') };
    const yli::console::TextLine text_line(char_container);
    scrollback_buffer.add_to_buffer(text_line);
    ASSERT_EQ(scrollback_buffer.size(), 2);
    ASSERT_EQ(scrollback_buffer.get_line_width(), 1);

    const yli::console::TextLine expected_text_line_a({ Codepoint('a') });
    ASSERT_EQ(scrollback_buffer.get_nth(0), expected_text_line_a);
    const yli::console::TextLine expected_text_line_b({ Codepoint('b') });
    ASSERT_EQ(scrollback_buffer.get_nth(1), expected_text_line_b);
}

TEST(adding_a_line_width_of_2_must_work_properly, scrollback_buffer_with_line_width_2_text_line_width_2)
{
    yli::console::ScrollbackBuffer scrollback_buffer(2);
    const std::vector<Codepoint> char_container { Codepoint('a'), Codepoint('b') };
    const yli::console::TextLine text_line(char_container);
    scrollback_buffer.add_to_buffer(text_line);
    ASSERT_EQ(scrollback_buffer.size(), 1);
    ASSERT_EQ(scrollback_buffer.get_line_width(), 2);

    const yli::console::TextLine expected_text_line_ab({ Codepoint('a'), Codepoint('b') });
    ASSERT_EQ(scrollback_buffer.get_nth(0), expected_text_line_ab);
}

TEST(adding_a_line_width_of_2_must_work_properly, scrollback_buffer_with_line_width_3_text_line_width_2)
{
    yli::console::ScrollbackBuffer scrollback_buffer(3);
    const std::vector<Codepoint> char_container { Codepoint('a'), Codepoint('b') };
    const yli::console::TextLine text_line(char_container);
    scrollback_buffer.add_to_buffer(text_line);
    ASSERT_EQ(scrollback_buffer.size(), 1);
    ASSERT_EQ(scrollback_buffer.get_line_width(), 3);

    const yli::console::TextLine expected_text_line_ab({ Codepoint('a'), Codepoint('b') });
    ASSERT_EQ(scrollback_buffer.get_nth(0), expected_text_line_ab);
}

TEST(adding_a_line_width_of_3_must_work_properly, scrollback_buffer_with_line_width_1_text_line_width_3)
{
    yli::console::ScrollbackBuffer scrollback_buffer(1);
    const std::vector<Codepoint> char_container { Codepoint('a'), Codepoint('b'), Codepoint('c') };
    const yli::console::TextLine text_line(char_container);
    scrollback_buffer.add_to_buffer(text_line);
    ASSERT_EQ(scrollback_buffer.size(), 3);
    ASSERT_EQ(scrollback_buffer.get_line_width(), 1);

    const yli::console::TextLine expected_text_line_a({ Codepoint('a') });
    ASSERT_EQ(scrollback_buffer.get_nth(0), expected_text_line_a);
    const yli::console::TextLine expected_text_line_b({ Codepoint('b') });
    ASSERT_EQ(scrollback_buffer.get_nth(1), expected_text_line_b);
    const yli::console::TextLine expected_text_line_c({ Codepoint('c') });
    ASSERT_EQ(scrollback_buffer.get_nth(2), expected_text_line_c);
}

TEST(adding_a_line_width_of_3_must_work_properly, scrollback_buffer_with_line_width_2_text_line_width_3)
{
    yli::console::ScrollbackBuffer scrollback_buffer(2);
    const std::vector<Codepoint> char_container { Codepoint('a'), Codepoint('b'), Codepoint('c') };
    const yli::console::TextLine text_line(char_container);
    scrollback_buffer.add_to_buffer(text_line);
    ASSERT_EQ(scrollback_buffer.size(), 2);
    ASSERT_EQ(scrollback_buffer.get_line_width(), 2);

    const yli::console::TextLine expected_text_line_ab({ Codepoint('a'), Codepoint('b') });
    ASSERT_EQ(scrollback_buffer.get_nth(0), expected_text_line_ab);
    const yli::console::TextLine expected_text_line_c({ Codepoint('c') });
    ASSERT_EQ(scrollback_buffer.get_nth(1), expected_text_line_c);
}

TEST(adding_a_line_width_of_3_must_work_properly, scrollback_buffer_with_line_width_3_text_line_width_3)
{
    yli::console::ScrollbackBuffer scrollback_buffer(3);
    const std::vector<Codepoint> char_container { Codepoint('a'), Codepoint('b'), Codepoint('c') };
    const yli::console::TextLine text_line(char_container);
    scrollback_buffer.add_to_buffer(text_line);
    ASSERT_EQ(scrollback_buffer.size(), 1);
    ASSERT_EQ(scrollback_buffer.get_line_width(), 3);

    const yli::console::TextLine expected_text_line_abc({ Codepoint('a'), Codepoint('b'), Codepoint('c') });
    ASSERT_EQ(scrollback_buffer.get_nth(0), expected_text_line_abc);
}