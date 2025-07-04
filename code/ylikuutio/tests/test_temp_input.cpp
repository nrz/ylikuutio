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
#include "code/ylikuutio/console/console_state_module.hpp"
#include "code/ylikuutio/console/temp_input.hpp"

// Include standard headers
#include <optional> // std::nullopt

TEST(temp_input_must_be_initialized_appropriately, temp_input)
{
    yli::console::ConsoleStateModule console_state_module;
    ASSERT_EQ(console_state_module.get_temp_input(), nullptr);

    yli::console::TempInput temp_input(console_state_module);
    ASSERT_EQ(temp_input.size(), 0);
    ASSERT_TRUE(temp_input.empty());
    ASSERT_EQ(temp_input.get_character_at_current_index(), std::nullopt);
    ASSERT_EQ(temp_input.get_character_to_the_left(), std::nullopt);
    ASSERT_EQ(temp_input.get_cursor_index(), 0);
    ASSERT_EQ(temp_input.data(), U"");
    ASSERT_EQ(temp_input.cbegin().unwrap(), temp_input.data().cbegin());
    ASSERT_EQ(console_state_module.get_temp_input(), &temp_input);
}
