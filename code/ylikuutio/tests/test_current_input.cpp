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
#include "code/ylikuutio/console/current_input.hpp"

// Include standard headers
#include <optional> // std::nullopt
#include <vector>   // std::vector

using yli::data::Codepoint;

TEST(current_input_must_be_initialized_appropriately, current_input)
{
    yli::console::ConsoleStateModule console_state_module;
    ASSERT_EQ(console_state_module.get_current_input(), nullptr);

    yli::console::CurrentInput current_input(console_state_module);
    ASSERT_EQ(current_input.size(), 0);
    ASSERT_TRUE(current_input.empty());
    ASSERT_EQ(current_input.get_character_at_current_index(), std::nullopt);
    ASSERT_EQ(current_input.get_character_to_the_left(), std::nullopt);
    ASSERT_EQ(current_input.get_cursor_index(), 0);
    ASSERT_EQ(current_input.data(), std::vector<Codepoint>{});
    ASSERT_EQ(current_input.to_string(), "");
    ASSERT_EQ(current_input.cbegin().unwrap(), current_input.data().cbegin());
    ASSERT_EQ(console_state_module.get_current_input(), &current_input);
}
