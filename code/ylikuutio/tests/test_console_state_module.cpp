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

TEST(console_state_module_must_be_initialized_appropriately, console_state_module)
{
    yli::console::ConsoleStateModule console_state_module;
    ASSERT_EQ(console_state_module.get(), yli::console::ConsoleState::IN_CURRENT_INPUT);
}

TEST(entering_current_input_from_current_input_must_work_appropriately, current_input_from_current_input_no_effect)
{
    yli::console::ConsoleStateModule console_state_module;
    console_state_module.enter_current_input();
    ASSERT_EQ(console_state_module.get(), yli::console::ConsoleState::IN_CURRENT_INPUT);
}

TEST(entering_historical_input_from_current_input_must_work_appropriately, historical_input_from_current_input)
{
    yli::console::ConsoleStateModule console_state_module;
    console_state_module.enter_historical_input();
    ASSERT_EQ(console_state_module.get(), yli::console::ConsoleState::IN_HISTORICAL_INPUT);
}

TEST(entering_scrollback_buffer_from_current_input_must_work_appropriately, scrollback_buffer_from_current_input)
{
    yli::console::ConsoleStateModule console_state_module;
    console_state_module.enter_scrollback_buffer();
    ASSERT_EQ(console_state_module.get(), yli::console::ConsoleState::IN_SCROLLBACK_BUFFER);
}

TEST(entering_current_input_from_historical_input_must_work_appropriately, current_input_from_historical_input)
{
    yli::console::ConsoleStateModule console_state_module;
    console_state_module.enter_historical_input();
    console_state_module.enter_current_input();
    ASSERT_EQ(console_state_module.get(), yli::console::ConsoleState::IN_CURRENT_INPUT);
}

TEST(entering_historical_input_from_historical_input_must_work_appropriately, historical_input_from_historical_input_no_effect)
{
    yli::console::ConsoleStateModule console_state_module;
    console_state_module.enter_historical_input();
    console_state_module.enter_historical_input();
    ASSERT_EQ(console_state_module.get(), yli::console::ConsoleState::IN_HISTORICAL_INPUT);
}

TEST(entering_temp_input_from_historical_input_must_work_appropriately, temp_input_from_historical_input)
{
    yli::console::ConsoleStateModule console_state_module;
    console_state_module.enter_historical_input();
    console_state_module.enter_temp_input();
    ASSERT_EQ(console_state_module.get(), yli::console::ConsoleState::IN_TEMP_INPUT);
}

TEST(entering_scrollback_buffer_from_historical_input_must_work_appropriately, scrollback_buffer_from_historical_input)
{
    yli::console::ConsoleStateModule console_state_module;
    console_state_module.enter_historical_input();
    console_state_module.enter_scrollback_buffer();
    ASSERT_EQ(console_state_module.get(), yli::console::ConsoleState::IN_SCROLLBACK_BUFFER);
}

TEST(entering_current_input_from_temp_input_must_work_appropriately, current_input_from_temp_input)
{
    yli::console::ConsoleStateModule console_state_module;
    console_state_module.enter_historical_input();
    console_state_module.enter_temp_input();
    console_state_module.enter_current_input();
    ASSERT_EQ(console_state_module.get(), yli::console::ConsoleState::IN_CURRENT_INPUT);
}

TEST(entering_historical_input_from_temp_input_must_work_appropriately, historical_input_from_temp_input)
{
    yli::console::ConsoleStateModule console_state_module;
    console_state_module.enter_historical_input();
    console_state_module.enter_temp_input();
    console_state_module.enter_historical_input();
    ASSERT_EQ(console_state_module.get(), yli::console::ConsoleState::IN_HISTORICAL_INPUT);
}

TEST(entering_temp_input_from_temp_input_must_work_appropriately, temp_input_from_temp_input_no_effect)
{
    yli::console::ConsoleStateModule console_state_module;
    console_state_module.enter_historical_input();
    console_state_module.enter_temp_input();
    console_state_module.enter_temp_input();
    ASSERT_EQ(console_state_module.get(), yli::console::ConsoleState::IN_TEMP_INPUT);
}

TEST(entering_scrollback_buffer_from_temp_input_must_work_appropriately, scrollback_buffer_from_temp_input)
{
    yli::console::ConsoleStateModule console_state_module;
    console_state_module.enter_historical_input();
    console_state_module.enter_temp_input();
    console_state_module.enter_scrollback_buffer();
    ASSERT_EQ(console_state_module.get(), yli::console::ConsoleState::IN_SCROLLBACK_BUFFER);
}

TEST(entering_current_input_from_scrollback_buffer_must_work_appropriately, current_input_from_scrollback_buffer)
{
    yli::console::ConsoleStateModule console_state_module;
    console_state_module.enter_scrollback_buffer();
    console_state_module.enter_current_input();
    ASSERT_EQ(console_state_module.get(), yli::console::ConsoleState::IN_CURRENT_INPUT);
}

TEST(entering_historical_input_from_scrollback_buffer_must_work_appropriately, historical_input_from_scrollback_buffer)
{
    yli::console::ConsoleStateModule console_state_module;
    console_state_module.enter_scrollback_buffer();
    console_state_module.enter_historical_input();
    ASSERT_EQ(console_state_module.get(), yli::console::ConsoleState::IN_HISTORICAL_INPUT);
}

TEST(entering_scrollback_buffer_from_scrollback_buffer_must_work_appropriately, scrollback_buffer_from_scrollback_buffer_no_effect)
{
    yli::console::ConsoleStateModule console_state_module;
    console_state_module.enter_scrollback_buffer();
    console_state_module.enter_scrollback_buffer();
    ASSERT_EQ(console_state_module.get(), yli::console::ConsoleState::IN_SCROLLBACK_BUFFER);
}
