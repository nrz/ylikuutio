// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2024 Antti Nuortimo.
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
#include "code/ylikuutio/data/codepoint.hpp"

// Include standard headers
#include <vector> // std::vector

TEST(text_line_must_be_initialized_appropriately, text_line)
{
    const std::vector<yli::data::Codepoint> char_container { 'a', 'b', 'c' };
    yli::console::TextLine text_line(char_container);
    ASSERT_EQ(text_line.data(), char_container);
}

TEST(text_line_begin_iterator_must_work_appropriately, text_line_begin_iterator)
{
    const std::vector<yli::data::Codepoint> char_container { 'a', 'b', 'c' };
    yli::console::TextLine text_line(char_container);

    auto it = text_line.begin();
    ASSERT_EQ(*it, yli::data::Codepoint('a'));
    ++it;
    ASSERT_EQ(*it, yli::data::Codepoint('b'));
    ++it;
    ASSERT_EQ(*it, yli::data::Codepoint('c'));
    ++it;
    ASSERT_EQ(it, text_line.end());
}

TEST(text_line_cbegin_const_iterator_must_work_appropriately, text_line_cbegin_const_iterator)
{
    const std::vector<yli::data::Codepoint> char_container { 'a', 'b', 'c' };
    yli::console::TextLine text_line(char_container);

    auto it = text_line.cbegin();
    ASSERT_EQ(*it, yli::data::Codepoint('a'));
    ++it;
    ASSERT_EQ(*it, yli::data::Codepoint('b'));
    ++it;
    ASSERT_EQ(*it, yli::data::Codepoint('c'));
    ++it;
    ASSERT_EQ(it, text_line.cend());
}

TEST(text_line_end_iterator_must_work_appropriately, text_line_end_iterator)
{
    const std::vector<yli::data::Codepoint> char_container { 'a', 'b', 'c' };
    yli::console::TextLine text_line(char_container);

    auto it = text_line.end();
    --it;
    ASSERT_EQ(*it, yli::data::Codepoint('c'));
    --it;
    ASSERT_EQ(*it, yli::data::Codepoint('b'));
    --it;
    ASSERT_EQ(*it, yli::data::Codepoint('a'));
    ASSERT_EQ(it, text_line.begin());
}

TEST(text_line_cend_iterator_must_work_appropriately, text_line_cend_iterator)
{
    const std::vector<yli::data::Codepoint> char_container { 'a', 'b', 'c' };
    yli::console::TextLine text_line(char_container);

    auto it = text_line.cend();
    --it;
    ASSERT_EQ(*it, yli::data::Codepoint('c'));
    --it;
    ASSERT_EQ(*it, yli::data::Codepoint('b'));
    --it;
    ASSERT_EQ(*it, yli::data::Codepoint('a'));
    ASSERT_EQ(it, text_line.cbegin());
}
