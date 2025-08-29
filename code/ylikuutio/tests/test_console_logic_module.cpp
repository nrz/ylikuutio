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
#include "code/ylikuutio/console/console_state.hpp"
#include "code/ylikuutio/console/console_logic_module.hpp"
#include "code/ylikuutio/console/text_input.hpp"
#include "code/ylikuutio/console/text_input_history.hpp"

// Include standard headers
#include <optional> // std::optional

TEST(console_logic_module_must_be_initialized_appropriately, console_logic_module)
{
    yli::console::ConsoleLogicModule console_logic_module;
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::INACTIVE_IN_CURRENT_INPUT);
    ASSERT_FALSE(console_logic_module.get_active_in_console());
    ASSERT_FALSE(console_logic_module.get_active_in_current_input());
    ASSERT_FALSE(console_logic_module.get_active_in_historical_input());
    ASSERT_FALSE(console_logic_module.get_active_in_temp_input());
    ASSERT_FALSE(console_logic_module.get_active_in_scrollback_buffer());
    ASSERT_EQ(console_logic_module.get_current_input(), nullptr);
    ASSERT_EQ(console_logic_module.get_temp_input(), nullptr);
}

TEST(registering_current_input_must_work_appropriately, current_input)
{
    yli::console::ConsoleLogicModule console_logic_module;
    yli::console::TextInput current_input;
    console_logic_module.register_current_input(&current_input);
    ASSERT_EQ(console_logic_module.get_current_input(), &current_input);
    ASSERT_EQ(console_logic_module.get_temp_input(), nullptr);
    ASSERT_EQ(console_logic_module.get_text_input_history(), nullptr);
}

TEST(registering_temp_input_must_work_appropriately, temp_input)
{
    yli::console::ConsoleLogicModule console_logic_module;
    yli::console::TextInput temp_input;
    console_logic_module.register_temp_input(&temp_input);
    ASSERT_EQ(console_logic_module.get_current_input(), nullptr);
    ASSERT_EQ(console_logic_module.get_temp_input(), &temp_input);
    ASSERT_EQ(console_logic_module.get_text_input_history(), nullptr);
}

TEST(registering_current_input_and_temp_input_must_work_appropriately, current_input_first_then_temp_input)
{
    yli::console::ConsoleLogicModule console_logic_module;
    yli::console::TextInput current_input;
    yli::console::TextInput temp_input;
    console_logic_module.register_current_input(&current_input);
    ASSERT_EQ(console_logic_module.get_current_input(), &current_input);
    ASSERT_EQ(console_logic_module.get_temp_input(), nullptr);
    ASSERT_EQ(console_logic_module.get_text_input_history(), nullptr);
    console_logic_module.register_temp_input(&temp_input);
    ASSERT_EQ(console_logic_module.get_current_input(), &current_input);
    ASSERT_EQ(console_logic_module.get_temp_input(), &temp_input);
    ASSERT_EQ(console_logic_module.get_text_input_history(), nullptr);
}

TEST(registering_current_input_and_temp_input_must_work_appropriately, temp_input_first_then_current_input)
{
    yli::console::ConsoleLogicModule console_logic_module;
    yli::console::TextInput current_input;
    yli::console::TextInput temp_input;
    console_logic_module.register_temp_input(&temp_input);
    ASSERT_EQ(console_logic_module.get_current_input(), nullptr);
    ASSERT_EQ(console_logic_module.get_temp_input(), &temp_input);
    ASSERT_EQ(console_logic_module.get_text_input_history(), nullptr);
    console_logic_module.register_current_input(&current_input);
    ASSERT_EQ(console_logic_module.get_current_input(), &current_input);
    ASSERT_EQ(console_logic_module.get_temp_input(), &temp_input);
    ASSERT_EQ(console_logic_module.get_text_input_history(), nullptr);
}

TEST(registering_text_input_history_must_work_appropriately, text_input_history)
{
    yli::console::ConsoleLogicModule console_logic_module;
    yli::console::TextInputHistory text_input_history(console_logic_module);
    console_logic_module.register_text_input_history(&text_input_history);
    ASSERT_EQ(console_logic_module.get_current_input(), nullptr);
    ASSERT_EQ(console_logic_module.get_temp_input(), nullptr);
    ASSERT_EQ(console_logic_module.get_text_input_history(), &text_input_history);
}

TEST(registering_current_input_and_temp_input_and_text_input_history_must_work_appropriately, current_input_and_temp_input_and_text_input_history)
{
    yli::console::ConsoleLogicModule console_logic_module;
    yli::console::TextInput current_input;
    yli::console::TextInput temp_input;
    yli::console::TextInputHistory text_input_history(console_logic_module);
    console_logic_module.register_current_input(&current_input);
    console_logic_module.register_temp_input(&temp_input);
    console_logic_module.register_text_input_history(&text_input_history);
    ASSERT_EQ(console_logic_module.get_current_input(), &current_input);
    ASSERT_EQ(console_logic_module.get_temp_input(), &temp_input);
    ASSERT_EQ(console_logic_module.get_text_input_history(), &text_input_history);
}

TEST(activation_must_fail_appropriately, no_current_input_registered)
{
    yli::console::ConsoleLogicModule console_logic_module;
    ASSERT_FALSE(console_logic_module.activate());
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::INACTIVE_IN_CURRENT_INPUT);
    ASSERT_FALSE(console_logic_module.get_active_in_console());
    ASSERT_FALSE(console_logic_module.get_active_in_current_input());
    ASSERT_FALSE(console_logic_module.get_active_in_historical_input());
    ASSERT_FALSE(console_logic_module.get_active_in_temp_input());
    ASSERT_FALSE(console_logic_module.get_active_in_scrollback_buffer());
}

TEST(activation_must_work_appropriately, inactive_in_current_input)
{
    yli::console::ConsoleLogicModule console_logic_module;
    yli::console::TextInput current_input;
    console_logic_module.register_current_input(&current_input);
    console_logic_module.activate();
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::ACTIVE_IN_CURRENT_INPUT);
    ASSERT_TRUE(console_logic_module.get_active_in_console());
    ASSERT_TRUE(console_logic_module.get_active_in_current_input());
    ASSERT_FALSE(console_logic_module.get_active_in_historical_input());
    ASSERT_FALSE(console_logic_module.get_active_in_temp_input());
    ASSERT_FALSE(console_logic_module.get_active_in_scrollback_buffer());
}

TEST(changing_to_scrollback_buffer_must_fail_appropriately, inactive_in_current_input)
{
    yli::console::ConsoleLogicModule console_logic_module;
    ASSERT_FALSE(console_logic_module.enter_scrollback_buffer());
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::INACTIVE_IN_CURRENT_INPUT);
    ASSERT_FALSE(console_logic_module.get_active_in_console());
    ASSERT_FALSE(console_logic_module.get_active_in_current_input());
    ASSERT_FALSE(console_logic_module.get_active_in_historical_input());
    ASSERT_FALSE(console_logic_module.get_active_in_temp_input());
    ASSERT_FALSE(console_logic_module.get_active_in_scrollback_buffer());
}

TEST(changing_to_historical_input_must_fail_appropriately, inactive_in_current_input)
{
    yli::console::ConsoleLogicModule console_logic_module;
    ASSERT_FALSE(console_logic_module.enter_historical_input());
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::INACTIVE_IN_CURRENT_INPUT);
    ASSERT_FALSE(console_logic_module.get_active_in_console());
    ASSERT_FALSE(console_logic_module.get_active_in_current_input());
    ASSERT_FALSE(console_logic_module.get_active_in_historical_input());
    ASSERT_FALSE(console_logic_module.get_active_in_temp_input());
    ASSERT_FALSE(console_logic_module.get_active_in_scrollback_buffer());
}

TEST(entering_current_input_from_current_input_must_work_appropriately, no_change)
{
    yli::console::ConsoleLogicModule console_logic_module;
    yli::console::TextInput current_input;
    console_logic_module.register_current_input(&current_input);
    console_logic_module.activate();
    console_logic_module.enter_current_input();
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::ACTIVE_IN_CURRENT_INPUT);
    ASSERT_TRUE(console_logic_module.get_active_in_console());
    ASSERT_TRUE(console_logic_module.get_active_in_current_input());
    ASSERT_FALSE(console_logic_module.get_active_in_historical_input());
    ASSERT_FALSE(console_logic_module.get_active_in_temp_input());
    ASSERT_FALSE(console_logic_module.get_active_in_scrollback_buffer());
}

TEST(entering_historical_input_from_current_input_must_work_appropriately, historical_input_from_current_input)
{
    yli::console::ConsoleLogicModule console_logic_module;
    yli::console::TextInput current_input;
    console_logic_module.register_current_input(&current_input);
    console_logic_module.activate();
    std::optional<yli::console::ConsoleState> console_state = console_logic_module.enter_historical_input();
    ASSERT_TRUE(console_state);
    ASSERT_EQ(*console_state, yli::console::ConsoleState::ACTIVE_IN_HISTORICAL_INPUT);
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::ACTIVE_IN_HISTORICAL_INPUT);
    ASSERT_TRUE(console_logic_module.get_active_in_console());
    ASSERT_FALSE(console_logic_module.get_active_in_current_input());
    ASSERT_TRUE(console_logic_module.get_active_in_historical_input());
    ASSERT_FALSE(console_logic_module.get_active_in_temp_input());
    ASSERT_FALSE(console_logic_module.get_active_in_scrollback_buffer());
}

TEST(entering_scrollback_buffer_from_current_input_must_work_appropriately, scrollback_buffer_from_current_input)
{
    yli::console::ConsoleLogicModule console_logic_module;
    yli::console::TextInput current_input;
    console_logic_module.register_current_input(&current_input);
    console_logic_module.activate();
    std::optional<yli::console::ConsoleState> console_state = console_logic_module.enter_scrollback_buffer();
    ASSERT_TRUE(console_state);
    ASSERT_EQ(*console_state, yli::console::ConsoleState::ACTIVE_IN_SCROLLBACK_BUFFER_WHILE_IN_CURRENT_INPUT);
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::ACTIVE_IN_SCROLLBACK_BUFFER_WHILE_IN_CURRENT_INPUT);
    ASSERT_TRUE(console_logic_module.get_active_in_console());
    ASSERT_FALSE(console_logic_module.get_active_in_current_input());
    ASSERT_FALSE(console_logic_module.get_active_in_historical_input());
    ASSERT_FALSE(console_logic_module.get_active_in_temp_input());
    ASSERT_TRUE(console_logic_module.get_active_in_scrollback_buffer());
}

TEST(entering_current_input_from_historical_input_must_work_appropriately, current_input_from_historical_input)
{
    yli::console::ConsoleLogicModule console_logic_module;
    yli::console::TextInput current_input;
    console_logic_module.register_current_input(&current_input);
    console_logic_module.activate();
    console_logic_module.enter_historical_input();
    std::optional<yli::console::ConsoleState> console_state = console_logic_module.enter_current_input();
    ASSERT_TRUE(console_state);
    ASSERT_EQ(*console_state, yli::console::ConsoleState::ACTIVE_IN_CURRENT_INPUT);
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::ACTIVE_IN_CURRENT_INPUT);
    ASSERT_TRUE(console_logic_module.get_active_in_console());
    ASSERT_TRUE(console_logic_module.get_active_in_current_input());
    ASSERT_FALSE(console_logic_module.get_active_in_historical_input());
    ASSERT_FALSE(console_logic_module.get_active_in_temp_input());
    ASSERT_FALSE(console_logic_module.get_active_in_scrollback_buffer());
}

TEST(entering_historical_input_from_historical_input_must_work_appropriately, historical_input_from_historical_input_no_effect)
{
    yli::console::ConsoleLogicModule console_logic_module;
    yli::console::TextInput current_input;
    console_logic_module.register_current_input(&current_input);
    console_logic_module.activate();
    console_logic_module.enter_historical_input();
    std::optional<yli::console::ConsoleState> console_state = console_logic_module.enter_historical_input();
    ASSERT_TRUE(console_state);
    ASSERT_EQ(*console_state, yli::console::ConsoleState::ACTIVE_IN_HISTORICAL_INPUT);
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::ACTIVE_IN_HISTORICAL_INPUT);
    ASSERT_TRUE(console_logic_module.get_active_in_console());
    ASSERT_FALSE(console_logic_module.get_active_in_current_input());
    ASSERT_TRUE(console_logic_module.get_active_in_historical_input());
    ASSERT_FALSE(console_logic_module.get_active_in_temp_input());
    ASSERT_FALSE(console_logic_module.get_active_in_scrollback_buffer());
}

TEST(entering_temp_input_from_historical_input_must_work_appropriately, temp_input_from_historical_input)
{
    yli::console::ConsoleLogicModule console_logic_module;
    yli::console::TextInput current_input;
    console_logic_module.register_current_input(&current_input);
    console_logic_module.activate();
    console_logic_module.enter_historical_input();
    std::optional<yli::console::ConsoleState> console_state = console_logic_module.enter_temp_input();
    ASSERT_TRUE(console_state);
    ASSERT_EQ(*console_state, yli::console::ConsoleState::ACTIVE_IN_TEMP_INPUT);
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::ACTIVE_IN_TEMP_INPUT);
    ASSERT_TRUE(console_logic_module.get_active_in_console());
    ASSERT_FALSE(console_logic_module.get_active_in_current_input());
    ASSERT_FALSE(console_logic_module.get_active_in_historical_input());
    ASSERT_TRUE(console_logic_module.get_active_in_temp_input());
    ASSERT_FALSE(console_logic_module.get_active_in_scrollback_buffer());
}

TEST(entering_scrollback_buffer_from_historical_input_must_work_appropriately, scrollback_buffer_from_historical_input)
{
    yli::console::ConsoleLogicModule console_logic_module;
    yli::console::TextInput current_input;
    console_logic_module.register_current_input(&current_input);
    console_logic_module.activate();
    console_logic_module.enter_historical_input();
    std::optional<yli::console::ConsoleState> console_state = console_logic_module.enter_scrollback_buffer();
    ASSERT_TRUE(console_state);
    ASSERT_EQ(*console_state, yli::console::ConsoleState::ACTIVE_IN_SCROLLBACK_BUFFER_WHILE_IN_HISTORICAL_INPUT);
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::ACTIVE_IN_SCROLLBACK_BUFFER_WHILE_IN_HISTORICAL_INPUT);
    ASSERT_TRUE(console_logic_module.get_active_in_console());
    ASSERT_FALSE(console_logic_module.get_active_in_current_input());
    ASSERT_FALSE(console_logic_module.get_active_in_historical_input());
    ASSERT_FALSE(console_logic_module.get_active_in_temp_input());
    ASSERT_TRUE(console_logic_module.get_active_in_scrollback_buffer());
}

TEST(entering_current_input_from_temp_input_must_work_appropriately, current_input_from_temp_input)
{
    yli::console::ConsoleLogicModule console_logic_module;
    yli::console::TextInput current_input;
    console_logic_module.register_current_input(&current_input);
    console_logic_module.activate();
    console_logic_module.enter_historical_input();
    console_logic_module.enter_temp_input();
    std::optional<yli::console::ConsoleState> console_state = console_logic_module.enter_current_input();
    ASSERT_TRUE(console_state);
    ASSERT_EQ(*console_state, yli::console::ConsoleState::ACTIVE_IN_CURRENT_INPUT);
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::ACTIVE_IN_CURRENT_INPUT);
    ASSERT_TRUE(console_logic_module.get_active_in_console());
    ASSERT_TRUE(console_logic_module.get_active_in_current_input());
    ASSERT_FALSE(console_logic_module.get_active_in_historical_input());
    ASSERT_FALSE(console_logic_module.get_active_in_temp_input());
    ASSERT_FALSE(console_logic_module.get_active_in_scrollback_buffer());
}

TEST(entering_historical_input_from_temp_input_must_work_appropriately, historical_input_from_temp_input)
{
    yli::console::ConsoleLogicModule console_logic_module;
    yli::console::TextInput current_input;
    console_logic_module.register_current_input(&current_input);
    console_logic_module.activate();
    console_logic_module.enter_historical_input();
    console_logic_module.enter_temp_input();
    std::optional<yli::console::ConsoleState> console_state = console_logic_module.enter_historical_input();
    ASSERT_TRUE(console_state);
    ASSERT_EQ(*console_state, yli::console::ConsoleState::ACTIVE_IN_HISTORICAL_INPUT);
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::ACTIVE_IN_HISTORICAL_INPUT);
    ASSERT_TRUE(console_logic_module.get_active_in_console());
    ASSERT_FALSE(console_logic_module.get_active_in_current_input());
    ASSERT_TRUE(console_logic_module.get_active_in_historical_input());
    ASSERT_FALSE(console_logic_module.get_active_in_temp_input());
    ASSERT_FALSE(console_logic_module.get_active_in_scrollback_buffer());
}

TEST(entering_temp_input_from_temp_input_must_work_appropriately, temp_input_from_temp_input_no_effect)
{
    yli::console::ConsoleLogicModule console_logic_module;
    yli::console::TextInput current_input;
    console_logic_module.register_current_input(&current_input);
    console_logic_module.activate();
    console_logic_module.enter_historical_input();
    console_logic_module.enter_temp_input();
    std::optional<yli::console::ConsoleState> console_state = console_logic_module.enter_temp_input();
    ASSERT_TRUE(console_state);
    ASSERT_EQ(*console_state, yli::console::ConsoleState::ACTIVE_IN_TEMP_INPUT);
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::ACTIVE_IN_TEMP_INPUT);
    ASSERT_TRUE(console_logic_module.get_active_in_console());
    ASSERT_FALSE(console_logic_module.get_active_in_current_input());
    ASSERT_FALSE(console_logic_module.get_active_in_historical_input());
    ASSERT_TRUE(console_logic_module.get_active_in_temp_input());
    ASSERT_FALSE(console_logic_module.get_active_in_scrollback_buffer());
}

TEST(entering_scrollback_buffer_from_temp_input_must_work_appropriately, scrollback_buffer_from_temp_input)
{
    yli::console::ConsoleLogicModule console_logic_module;
    yli::console::TextInput current_input;
    console_logic_module.register_current_input(&current_input);
    console_logic_module.activate();
    console_logic_module.enter_historical_input();
    console_logic_module.enter_temp_input();
    std::optional<yli::console::ConsoleState> console_state = console_logic_module.enter_scrollback_buffer();
    ASSERT_TRUE(console_state);
    ASSERT_EQ(*console_state, yli::console::ConsoleState::ACTIVE_IN_SCROLLBACK_BUFFER_WHILE_IN_TEMP_INPUT);
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::ACTIVE_IN_SCROLLBACK_BUFFER_WHILE_IN_TEMP_INPUT);
    ASSERT_TRUE(console_logic_module.get_active_in_console());
    ASSERT_FALSE(console_logic_module.get_active_in_current_input());
    ASSERT_FALSE(console_logic_module.get_active_in_historical_input());
    ASSERT_FALSE(console_logic_module.get_active_in_temp_input());
    ASSERT_TRUE(console_logic_module.get_active_in_scrollback_buffer());
}

TEST(entering_current_input_from_scrollback_buffer_must_work_appropriately, current_input_from_scrollback_buffer)
{
    yli::console::ConsoleLogicModule console_logic_module;
    yli::console::TextInput current_input;
    console_logic_module.register_current_input(&current_input);
    console_logic_module.activate();
    console_logic_module.enter_scrollback_buffer();
    std::optional<yli::console::ConsoleState> console_state = console_logic_module.enter_current_input();
    ASSERT_TRUE(console_state);
    ASSERT_EQ(*console_state, yli::console::ConsoleState::ACTIVE_IN_CURRENT_INPUT);
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::ACTIVE_IN_CURRENT_INPUT);
    ASSERT_TRUE(console_logic_module.get_active_in_console());
    ASSERT_TRUE(console_logic_module.get_active_in_current_input());
    ASSERT_FALSE(console_logic_module.get_active_in_historical_input());
    ASSERT_FALSE(console_logic_module.get_active_in_temp_input());
    ASSERT_FALSE(console_logic_module.get_active_in_scrollback_buffer());
}

TEST(entering_historical_input_from_scrollback_buffer_must_work_appropriately, historical_input_from_scrollback_buffer)
{
    yli::console::ConsoleLogicModule console_logic_module;
    yli::console::TextInput current_input;
    console_logic_module.register_current_input(&current_input);
    console_logic_module.activate();
    console_logic_module.enter_scrollback_buffer();
    ASSERT_FALSE(console_logic_module.enter_historical_input());
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::ACTIVE_IN_SCROLLBACK_BUFFER_WHILE_IN_CURRENT_INPUT);
    ASSERT_TRUE(console_logic_module.get_active_in_console());
    ASSERT_FALSE(console_logic_module.get_active_in_current_input());
    ASSERT_FALSE(console_logic_module.get_active_in_historical_input());
    ASSERT_FALSE(console_logic_module.get_active_in_temp_input());
    ASSERT_TRUE(console_logic_module.get_active_in_scrollback_buffer());
}

TEST(entering_scrollback_buffer_from_scrollback_buffer_must_work_appropriately, scrollback_buffer_from_scrollback_buffer_while_in_current_input_no_effect)
{
    yli::console::ConsoleLogicModule console_logic_module;
    yli::console::TextInput current_input;
    console_logic_module.register_current_input(&current_input);
    console_logic_module.activate();
    console_logic_module.enter_scrollback_buffer();
    std::optional<yli::console::ConsoleState> console_state = console_logic_module.enter_scrollback_buffer();
    ASSERT_TRUE(console_state);
    ASSERT_EQ(*console_state, yli::console::ConsoleState::ACTIVE_IN_SCROLLBACK_BUFFER_WHILE_IN_CURRENT_INPUT);
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::ACTIVE_IN_SCROLLBACK_BUFFER_WHILE_IN_CURRENT_INPUT);
    ASSERT_TRUE(console_logic_module.get_active_in_console());
    ASSERT_FALSE(console_logic_module.get_active_in_current_input());
    ASSERT_FALSE(console_logic_module.get_active_in_historical_input());
    ASSERT_FALSE(console_logic_module.get_active_in_temp_input());
    ASSERT_TRUE(console_logic_module.get_active_in_scrollback_buffer());
}

TEST(entering_scrollback_buffer_from_scrollback_buffer_must_work_appropriately, scrollback_buffer_from_scrollback_buffer_while_in_historical_input_no_effect)
{
    yli::console::ConsoleLogicModule console_logic_module;
    yli::console::TextInput current_input;
    console_logic_module.register_current_input(&current_input);
    console_logic_module.activate();
    console_logic_module.enter_historical_input();
    console_logic_module.enter_scrollback_buffer();
    std::optional<yli::console::ConsoleState> console_state = console_logic_module.enter_scrollback_buffer();
    ASSERT_TRUE(console_state);
    ASSERT_EQ(*console_state, yli::console::ConsoleState::ACTIVE_IN_SCROLLBACK_BUFFER_WHILE_IN_HISTORICAL_INPUT);
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::ACTIVE_IN_SCROLLBACK_BUFFER_WHILE_IN_HISTORICAL_INPUT);
    ASSERT_TRUE(console_logic_module.get_active_in_console());
    ASSERT_FALSE(console_logic_module.get_active_in_current_input());
    ASSERT_FALSE(console_logic_module.get_active_in_historical_input());
    ASSERT_FALSE(console_logic_module.get_active_in_temp_input());
    ASSERT_TRUE(console_logic_module.get_active_in_scrollback_buffer());
}

TEST(entering_scrollback_buffer_from_scrollback_buffer_must_work_appropriately, scrollback_buffer_from_scrollback_buffer_while_in_temp_input_no_effect)
{
    yli::console::ConsoleLogicModule console_logic_module;
    yli::console::TextInput current_input;
    console_logic_module.register_current_input(&current_input);
    console_logic_module.activate();
    console_logic_module.enter_historical_input();
    console_logic_module.enter_temp_input();
    console_logic_module.enter_scrollback_buffer();
    std::optional<yli::console::ConsoleState> console_state = console_logic_module.enter_scrollback_buffer();
    ASSERT_TRUE(console_state);
    ASSERT_EQ(*console_state, yli::console::ConsoleState::ACTIVE_IN_SCROLLBACK_BUFFER_WHILE_IN_TEMP_INPUT);
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::ACTIVE_IN_SCROLLBACK_BUFFER_WHILE_IN_TEMP_INPUT);
    ASSERT_TRUE(console_logic_module.get_active_in_console());
    ASSERT_FALSE(console_logic_module.get_active_in_current_input());
    ASSERT_FALSE(console_logic_module.get_active_in_historical_input());
    ASSERT_FALSE(console_logic_module.get_active_in_temp_input());
    ASSERT_TRUE(console_logic_module.get_active_in_scrollback_buffer());
}
