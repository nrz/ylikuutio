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
#include "code/ylikuutio/input/codepoint.hpp"
#include "code/ylikuutio/input/text_input.hpp"
#include "code/ylikuutio/input/text_input_history.hpp"

// Include standard headers
#include <optional> // std::nullopt
#include <utility>  // std::move
#include <vector>   // std::vector

TEST(text_input_history_must_be_initialized_appropriately, text_input_history)
{
    yli::input::TextInputHistory text_input_history;
    ASSERT_FALSE(text_input_history.get_is_in_history());
    ASSERT_EQ(text_input_history.size(), 0);
    ASSERT_EQ(text_input_history.get_from_history(), std::nullopt);
}

TEST(moving_to_previous_input_must_fail_appropriately, empty_input_history)
{
    yli::input::TextInputHistory text_input_history;
    ASSERT_FALSE(text_input_history.move_to_previous());
    ASSERT_FALSE(text_input_history.get_is_in_history());
    ASSERT_EQ(text_input_history.size(), 0);
    ASSERT_EQ(text_input_history.get_from_history(), std::nullopt);
}

TEST(moving_to_next_input_must_fail_appropriately, empty_input_history)
{
    yli::input::TextInputHistory text_input_history;
    ASSERT_FALSE(text_input_history.move_to_next());
    ASSERT_FALSE(text_input_history.get_is_in_history());
    ASSERT_EQ(text_input_history.size(), 0);
    ASSERT_EQ(text_input_history.get_from_history(), std::nullopt);
}

TEST(adding_an_input_must_work_appropriately, abc)
{
    yli::input::TextInputHistory text_input_history;

    yli::input::TextInput text_input;
    const std::vector<yli::input::Codepoint> char_container { 'a', 'b', 'c' };
    text_input.add_characters(char_container);

    text_input_history.add_to_history(std::move(text_input));
    ASSERT_FALSE(text_input_history.move_to_next());
    ASSERT_FALSE(text_input_history.get_is_in_history());
    ASSERT_EQ(text_input_history.size(), 1);

    ASSERT_TRUE(text_input_history.enter_history());
    const std::optional<yli::input::TextInput> input_from_history = text_input_history.get_from_history();
    ASSERT_TRUE(input_from_history);

    ASSERT_EQ(*text_input_history.get_from_history(), text_input);
}
