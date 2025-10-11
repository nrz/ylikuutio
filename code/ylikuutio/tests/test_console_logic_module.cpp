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
#include "code/ylikuutio/console/scrollback_buffer.hpp"

// Include standard headers
#include <optional> // std::optional

TEST(console_logic_module_must_be_initialized_appropriately, console_logic_module)
{
    yli::console::TextInput new_input(yli::console::TextInputType::NEW_INPUT);
    yli::console::TextInput temp_input(yli::console::TextInputType::TEMP_INPUT);
    yli::console::TextInputHistory text_input_history;
    yli::console::ScrollbackBuffer scrollback_buffer;
    yli::console::ConsoleLogicModule console_logic_module(new_input, temp_input, text_input_history, scrollback_buffer);
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::INACTIVE_IN_NEW_INPUT);
    ASSERT_FALSE(console_logic_module.get_active_in_console());
    ASSERT_FALSE(console_logic_module.get_active_in_new_input());
    ASSERT_FALSE(console_logic_module.get_active_in_historical_input());
    ASSERT_FALSE(console_logic_module.get_active_in_temp_input());
    ASSERT_FALSE(console_logic_module.get_active_in_scrollback_buffer());
    ASSERT_EQ(&console_logic_module.get_new_input(), &new_input);
    ASSERT_EQ(&console_logic_module.get_temp_input(), &temp_input);
    ASSERT_EQ(console_logic_module.get_visible_input(), nullptr); // No visible input on deactivated console.
    ASSERT_EQ(&console_logic_module.get_text_input_history(), &text_input_history);
    ASSERT_EQ(&console_logic_module.get_scrollback_buffer(), &scrollback_buffer);
    ASSERT_EQ(console_logic_module.get_n_columns(), 80);
    ASSERT_EQ(console_logic_module.get_n_rows(), 24);
}

TEST(activation_must_work_appropriately, inactive_in_new_input)
{
    yli::console::TextInput new_input(yli::console::TextInputType::NEW_INPUT);
    yli::console::TextInput temp_input(yli::console::TextInputType::TEMP_INPUT);
    yli::console::TextInputHistory text_input_history;
    yli::console::ScrollbackBuffer scrollback_buffer;
    yli::console::ConsoleLogicModule console_logic_module(new_input, temp_input, text_input_history, scrollback_buffer);
    console_logic_module.activate();

    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::ACTIVE_IN_NEW_INPUT);
    ASSERT_TRUE(console_logic_module.get_active_in_console());
    ASSERT_TRUE(console_logic_module.get_active_in_new_input());
    ASSERT_FALSE(console_logic_module.get_active_in_historical_input());
    ASSERT_FALSE(console_logic_module.get_active_in_temp_input());
    ASSERT_FALSE(console_logic_module.get_active_in_scrollback_buffer());
    ASSERT_EQ(console_logic_module.get_visible_input(), &new_input);
}

TEST(deactivation_must_work_appropriately, active_in_new_input)
{
    // Do the necessary setup.
    yli::console::TextInput new_input(yli::console::TextInputType::NEW_INPUT);
    yli::console::TextInput temp_input(yli::console::TextInputType::TEMP_INPUT);
    yli::console::TextInputHistory text_input_history;
    yli::console::ScrollbackBuffer scrollback_buffer;
    yli::console::ConsoleLogicModule console_logic_module(new_input, temp_input, text_input_history, scrollback_buffer);
    console_logic_module.activate();

    console_logic_module.enter_new_input();
    std::optional<yli::console::ConsoleState> console_state = console_logic_module.deactivate();
    ASSERT_TRUE(console_state);
    ASSERT_EQ(*console_state, yli::console::ConsoleState::INACTIVE_IN_NEW_INPUT);
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::INACTIVE_IN_NEW_INPUT);
    ASSERT_FALSE(console_logic_module.get_active_in_console());
    ASSERT_FALSE(console_logic_module.get_active_in_new_input());
    ASSERT_FALSE(console_logic_module.get_active_in_historical_input());
    ASSERT_FALSE(console_logic_module.get_active_in_temp_input());
    ASSERT_FALSE(console_logic_module.get_active_in_scrollback_buffer());
    ASSERT_EQ(console_logic_module.get_visible_input(), nullptr); // No visible input on deactivated console.
}

TEST(changing_to_scrollback_buffer_must_fail_appropriately, inactive_in_new_input)
{
    yli::console::TextInput new_input(yli::console::TextInputType::NEW_INPUT);
    yli::console::TextInput temp_input(yli::console::TextInputType::TEMP_INPUT);
    yli::console::TextInputHistory text_input_history;
    yli::console::ScrollbackBuffer scrollback_buffer;
    yli::console::ConsoleLogicModule console_logic_module(new_input, temp_input, text_input_history, scrollback_buffer);
    ASSERT_FALSE(console_logic_module.enter_scrollback_buffer());
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::INACTIVE_IN_NEW_INPUT);
    ASSERT_FALSE(console_logic_module.get_active_in_console());
    ASSERT_FALSE(console_logic_module.get_active_in_new_input());
    ASSERT_FALSE(console_logic_module.get_active_in_historical_input());
    ASSERT_FALSE(console_logic_module.get_active_in_temp_input());
    ASSERT_FALSE(console_logic_module.get_active_in_scrollback_buffer());
    ASSERT_EQ(console_logic_module.get_visible_input(), nullptr); // No visible input on deactivated console.
}

TEST(changing_to_historical_input_must_fail_appropriately, inactive_in_new_input_and_no_historical_input_yet)
{
    yli::console::TextInput new_input(yli::console::TextInputType::NEW_INPUT);
    yli::console::TextInput temp_input(yli::console::TextInputType::TEMP_INPUT);
    yli::console::TextInputHistory text_input_history;
    yli::console::ScrollbackBuffer scrollback_buffer;
    yli::console::ConsoleLogicModule console_logic_module(new_input, temp_input, text_input_history, scrollback_buffer);
    ASSERT_FALSE(console_logic_module.enter_historical_input());
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::INACTIVE_IN_NEW_INPUT);
    ASSERT_FALSE(console_logic_module.get_active_in_console());
    ASSERT_FALSE(console_logic_module.get_active_in_new_input());
    ASSERT_FALSE(console_logic_module.get_active_in_historical_input());
    ASSERT_FALSE(console_logic_module.get_active_in_temp_input());
    ASSERT_FALSE(console_logic_module.get_active_in_scrollback_buffer());
    ASSERT_EQ(console_logic_module.get_visible_input(), nullptr); // No visible input on deactivated console.
}

TEST(changing_to_historical_input_must_fail_appropriately, inactive_in_new_input_but_with_historical_input)
{
    yli::console::TextInput new_input(yli::console::TextInputType::NEW_INPUT);
    yli::console::TextInput temp_input(yli::console::TextInputType::TEMP_INPUT);
    yli::console::TextInputHistory text_input_history;
    yli::console::ScrollbackBuffer scrollback_buffer;
    yli::console::ConsoleLogicModule console_logic_module(new_input, temp_input, text_input_history, scrollback_buffer);
    new_input.add_characters("abc");
    text_input_history.add_to_history(new_input);
    ASSERT_FALSE(console_logic_module.enter_historical_input());
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::INACTIVE_IN_NEW_INPUT);
    ASSERT_FALSE(console_logic_module.get_active_in_console());
    ASSERT_FALSE(console_logic_module.get_active_in_new_input());
    ASSERT_FALSE(console_logic_module.get_active_in_historical_input());
    ASSERT_FALSE(console_logic_module.get_active_in_temp_input());
    ASSERT_FALSE(console_logic_module.get_active_in_scrollback_buffer());
}

TEST(changing_to_historical_input_must_fail_appropriately, active_in_new_input_but_no_historical_input_yet)
{
    yli::console::TextInput new_input(yli::console::TextInputType::NEW_INPUT);
    yli::console::TextInput temp_input(yli::console::TextInputType::TEMP_INPUT);
    yli::console::TextInputHistory text_input_history;
    yli::console::ScrollbackBuffer scrollback_buffer;
    yli::console::ConsoleLogicModule console_logic_module(new_input, temp_input, text_input_history, scrollback_buffer);
    console_logic_module.enter_new_input();
    ASSERT_FALSE(console_logic_module.enter_historical_input());
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::ACTIVE_IN_NEW_INPUT);
    ASSERT_TRUE(console_logic_module.get_active_in_console());
    ASSERT_TRUE(console_logic_module.get_active_in_new_input());
    ASSERT_FALSE(console_logic_module.get_active_in_historical_input());
    ASSERT_FALSE(console_logic_module.get_active_in_temp_input());
    ASSERT_FALSE(console_logic_module.get_active_in_scrollback_buffer());
}

TEST(entering_new_input_from_new_input_must_work_appropriately, no_change)
{
    // Do the necessary setup.
    yli::console::TextInput new_input(yli::console::TextInputType::NEW_INPUT);
    yli::console::TextInput temp_input(yli::console::TextInputType::TEMP_INPUT);
    yli::console::TextInputHistory text_input_history;
    yli::console::ScrollbackBuffer scrollback_buffer;
    yli::console::ConsoleLogicModule console_logic_module(new_input, temp_input, text_input_history, scrollback_buffer);
    console_logic_module.activate();

    std::optional<yli::console::ConsoleState> console_state = console_logic_module.enter_new_input();
    ASSERT_TRUE(console_state);
    ASSERT_EQ(*console_state, yli::console::ConsoleState::ACTIVE_IN_NEW_INPUT);
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::ACTIVE_IN_NEW_INPUT);
    ASSERT_TRUE(console_logic_module.get_active_in_console());
    ASSERT_TRUE(console_logic_module.get_active_in_new_input());
    ASSERT_FALSE(console_logic_module.get_active_in_historical_input());
    ASSERT_FALSE(console_logic_module.get_active_in_temp_input());
    ASSERT_FALSE(console_logic_module.get_active_in_scrollback_buffer());
    ASSERT_EQ(console_logic_module.get_visible_input(), &new_input);
}

TEST(entering_historical_input_from_new_input_must_work_appropriately, historical_input_from_new_input)
{
    // Do the necessary setup.
    yli::console::TextInput new_input(yli::console::TextInputType::NEW_INPUT);
    yli::console::TextInput temp_input(yli::console::TextInputType::TEMP_INPUT);
    yli::console::TextInputHistory text_input_history;
    yli::console::ScrollbackBuffer scrollback_buffer;
    yli::console::ConsoleLogicModule console_logic_module(new_input, temp_input, text_input_history, scrollback_buffer);
    console_logic_module.activate();
    new_input.add_characters("abc");
    text_input_history.add_to_history(new_input);

    std::optional<yli::console::ConsoleState> console_state = console_logic_module.enter_historical_input();
    ASSERT_TRUE(console_state);
    ASSERT_EQ(*console_state, yli::console::ConsoleState::ACTIVE_IN_HISTORICAL_INPUT);
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::ACTIVE_IN_HISTORICAL_INPUT);
    ASSERT_TRUE(console_logic_module.get_active_in_console());
    ASSERT_FALSE(console_logic_module.get_active_in_new_input());
    ASSERT_TRUE(console_logic_module.get_active_in_historical_input());
    ASSERT_FALSE(console_logic_module.get_active_in_temp_input());
    ASSERT_FALSE(console_logic_module.get_active_in_scrollback_buffer());
    ASSERT_EQ(console_logic_module.get_visible_input(), &text_input_history.at(0));
}

TEST(entering_scrollback_buffer_from_new_input_must_work_appropriately, scrollback_buffer_from_new_input_n_columns_1_n_rows_1_input_a)
{
    // Do the necessary setup.
    yli::console::TextInput new_input(yli::console::TextInputType::NEW_INPUT);
    yli::console::TextInput temp_input(yli::console::TextInputType::TEMP_INPUT);
    yli::console::TextInputHistory text_input_history;
    yli::console::ScrollbackBuffer scrollback_buffer;
    yli::console::ConsoleLogicModule console_logic_module(new_input, temp_input, text_input_history, scrollback_buffer, 1, 1);
    console_logic_module.activate();

    new_input.add_characters("a");
    text_input_history.add_to_history(new_input);
    scrollback_buffer.add_to_buffer(new_input);
    ASSERT_EQ(text_input_history.at(0).data(), "a");
    ASSERT_EQ(scrollback_buffer.at(0).data(), "a");
    std::optional<yli::console::ConsoleState> console_state = console_logic_module.enter_scrollback_buffer();
    ASSERT_TRUE(console_state);
    ASSERT_EQ(*console_state, yli::console::ConsoleState::ACTIVE_IN_SCROLLBACK_BUFFER_WHILE_IN_NEW_INPUT);
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::ACTIVE_IN_SCROLLBACK_BUFFER_WHILE_IN_NEW_INPUT);
    ASSERT_TRUE(console_logic_module.get_active_in_console());
    ASSERT_FALSE(console_logic_module.get_active_in_new_input());
    ASSERT_FALSE(console_logic_module.get_active_in_historical_input());
    ASSERT_FALSE(console_logic_module.get_active_in_temp_input());
    ASSERT_TRUE(console_logic_module.get_active_in_scrollback_buffer());
    ASSERT_EQ(console_logic_module.get_visible_input(), &new_input);
}

TEST(entering_new_input_from_historical_input_must_work_appropriately, new_input_from_historical_input)
{
    // Do the necessary setup.
    yli::console::TextInput new_input(yli::console::TextInputType::NEW_INPUT);
    yli::console::TextInput temp_input(yli::console::TextInputType::TEMP_INPUT);
    yli::console::TextInputHistory text_input_history;
    yli::console::ScrollbackBuffer scrollback_buffer;
    yli::console::ConsoleLogicModule console_logic_module(new_input, temp_input, text_input_history, scrollback_buffer);
    console_logic_module.activate();

    new_input.add_characters("abc");
    text_input_history.add_to_history(new_input);
    console_logic_module.enter_historical_input();
    std::optional<yli::console::ConsoleState> console_state = console_logic_module.enter_new_input();
    ASSERT_TRUE(console_state);
    ASSERT_EQ(*console_state, yli::console::ConsoleState::ACTIVE_IN_NEW_INPUT);
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::ACTIVE_IN_NEW_INPUT);
    ASSERT_TRUE(console_logic_module.get_active_in_console());
    ASSERT_TRUE(console_logic_module.get_active_in_new_input());
    ASSERT_FALSE(console_logic_module.get_active_in_historical_input());
    ASSERT_FALSE(console_logic_module.get_active_in_temp_input());
    ASSERT_FALSE(console_logic_module.get_active_in_scrollback_buffer());
    ASSERT_EQ(console_logic_module.get_visible_input(), &new_input);
}

TEST(entering_historical_input_from_historical_input_must_work_appropriately, historical_input_from_historical_input_no_effect)
{
    // Do the necessary setup.
    yli::console::TextInput new_input(yli::console::TextInputType::NEW_INPUT);
    yli::console::TextInput temp_input(yli::console::TextInputType::TEMP_INPUT);
    yli::console::TextInputHistory text_input_history;
    yli::console::ScrollbackBuffer scrollback_buffer;
    yli::console::ConsoleLogicModule console_logic_module(new_input, temp_input, text_input_history, scrollback_buffer);
    console_logic_module.activate();

    new_input.add_characters("abc");
    text_input_history.add_to_history(new_input);
    console_logic_module.enter_historical_input();
    std::optional<yli::console::ConsoleState> console_state = console_logic_module.enter_historical_input();
    ASSERT_TRUE(console_state);
    ASSERT_EQ(*console_state, yli::console::ConsoleState::ACTIVE_IN_HISTORICAL_INPUT);
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::ACTIVE_IN_HISTORICAL_INPUT);
    ASSERT_TRUE(console_logic_module.get_active_in_console());
    ASSERT_FALSE(console_logic_module.get_active_in_new_input());
    ASSERT_TRUE(console_logic_module.get_active_in_historical_input());
    ASSERT_FALSE(console_logic_module.get_active_in_temp_input());
    ASSERT_FALSE(console_logic_module.get_active_in_scrollback_buffer());
    ASSERT_EQ(console_logic_module.get_visible_input(), &text_input_history.at(0));
}

TEST(entering_temp_input_from_historical_input_must_work_appropriately, temp_input_from_historical_input)
{
    // Do the necessary setup.
    yli::console::TextInput new_input(yli::console::TextInputType::NEW_INPUT);
    yli::console::TextInput temp_input(yli::console::TextInputType::TEMP_INPUT);
    yli::console::TextInputHistory text_input_history;
    yli::console::ScrollbackBuffer scrollback_buffer;
    yli::console::ConsoleLogicModule console_logic_module(new_input, temp_input, text_input_history, scrollback_buffer);
    console_logic_module.activate();

    console_logic_module.enter_historical_input();
    std::optional<yli::console::ConsoleState> console_state = console_logic_module.enter_temp_input();
    ASSERT_TRUE(console_state);
    ASSERT_EQ(*console_state, yli::console::ConsoleState::ACTIVE_IN_TEMP_INPUT);
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::ACTIVE_IN_TEMP_INPUT);
    ASSERT_TRUE(console_logic_module.get_active_in_console());
    ASSERT_FALSE(console_logic_module.get_active_in_new_input());
    ASSERT_FALSE(console_logic_module.get_active_in_historical_input());
    ASSERT_TRUE(console_logic_module.get_active_in_temp_input());
    ASSERT_FALSE(console_logic_module.get_active_in_scrollback_buffer());
    ASSERT_EQ(console_logic_module.get_visible_input(), &temp_input);
}

TEST(entering_scrollback_buffer_from_historical_input_must_work_appropriately, scrollback_buffer_from_historical_input)
{
    // Do the necessary setup.
    yli::console::TextInput new_input(yli::console::TextInputType::NEW_INPUT);
    yli::console::TextInput temp_input(yli::console::TextInputType::TEMP_INPUT);
    yli::console::TextInputHistory text_input_history;
    yli::console::ScrollbackBuffer scrollback_buffer;
    yli::console::ConsoleLogicModule console_logic_module(new_input, temp_input, text_input_history, scrollback_buffer);
    console_logic_module.activate();
    new_input.add_characters("abc");
    text_input_history.add_to_history(new_input);

    console_logic_module.enter_historical_input();
    std::optional<yli::console::ConsoleState> console_state = console_logic_module.enter_scrollback_buffer();
    ASSERT_TRUE(console_state);
    ASSERT_EQ(*console_state, yli::console::ConsoleState::ACTIVE_IN_SCROLLBACK_BUFFER_WHILE_IN_HISTORICAL_INPUT);
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::ACTIVE_IN_SCROLLBACK_BUFFER_WHILE_IN_HISTORICAL_INPUT);
    ASSERT_TRUE(console_logic_module.get_active_in_console());
    ASSERT_FALSE(console_logic_module.get_active_in_new_input());
    ASSERT_FALSE(console_logic_module.get_active_in_historical_input());
    ASSERT_FALSE(console_logic_module.get_active_in_temp_input());
    ASSERT_TRUE(console_logic_module.get_active_in_scrollback_buffer());
    ASSERT_EQ(console_logic_module.get_visible_input(), &text_input_history.at(0));
}

TEST(entering_new_input_from_temp_input_must_work_appropriately, new_input_from_temp_input)
{
    // Do the necessary setup.
    yli::console::TextInput new_input(yli::console::TextInputType::NEW_INPUT);
    yli::console::TextInput temp_input(yli::console::TextInputType::TEMP_INPUT);
    yli::console::TextInputHistory text_input_history;
    yli::console::ScrollbackBuffer scrollback_buffer;
    yli::console::ConsoleLogicModule console_logic_module(new_input, temp_input, text_input_history, scrollback_buffer);
    console_logic_module.activate();

    console_logic_module.enter_historical_input();
    console_logic_module.enter_temp_input();
    std::optional<yli::console::ConsoleState> console_state = console_logic_module.enter_new_input();
    ASSERT_TRUE(console_state);
    ASSERT_EQ(*console_state, yli::console::ConsoleState::ACTIVE_IN_NEW_INPUT);
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::ACTIVE_IN_NEW_INPUT);
    ASSERT_TRUE(console_logic_module.get_active_in_console());
    ASSERT_TRUE(console_logic_module.get_active_in_new_input());
    ASSERT_FALSE(console_logic_module.get_active_in_historical_input());
    ASSERT_FALSE(console_logic_module.get_active_in_temp_input());
    ASSERT_FALSE(console_logic_module.get_active_in_scrollback_buffer());
}

TEST(entering_historical_input_from_temp_input_must_work_appropriately, historical_input_from_temp_input)
{
    // Do the necessary setup.
    yli::console::TextInput new_input(yli::console::TextInputType::NEW_INPUT);
    yli::console::TextInput temp_input(yli::console::TextInputType::TEMP_INPUT);
    yli::console::TextInputHistory text_input_history;
    yli::console::ScrollbackBuffer scrollback_buffer;
    yli::console::ConsoleLogicModule console_logic_module(new_input, temp_input, text_input_history, scrollback_buffer);
    console_logic_module.activate();
    new_input.add_characters("abc");
    text_input_history.add_to_history(new_input);

    console_logic_module.enter_historical_input();
    console_logic_module.enter_temp_input();
    std::optional<yli::console::ConsoleState> console_state = console_logic_module.enter_historical_input();
    ASSERT_TRUE(console_state);
    ASSERT_EQ(*console_state, yli::console::ConsoleState::ACTIVE_IN_HISTORICAL_INPUT);
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::ACTIVE_IN_HISTORICAL_INPUT);
    ASSERT_TRUE(console_logic_module.get_active_in_console());
    ASSERT_FALSE(console_logic_module.get_active_in_new_input());
    ASSERT_TRUE(console_logic_module.get_active_in_historical_input());
    ASSERT_FALSE(console_logic_module.get_active_in_temp_input());
    ASSERT_FALSE(console_logic_module.get_active_in_scrollback_buffer());
}

TEST(entering_temp_input_from_temp_input_must_work_appropriately, temp_input_from_temp_input_no_effect)
{
    // Do the necessary setup.
    yli::console::TextInput new_input(yli::console::TextInputType::NEW_INPUT);
    yli::console::TextInput temp_input(yli::console::TextInputType::TEMP_INPUT);
    yli::console::TextInputHistory text_input_history;
    yli::console::ScrollbackBuffer scrollback_buffer;
    yli::console::ConsoleLogicModule console_logic_module(new_input, temp_input, text_input_history, scrollback_buffer);
    console_logic_module.activate();

    console_logic_module.enter_historical_input();
    console_logic_module.enter_temp_input();
    std::optional<yli::console::ConsoleState> console_state = console_logic_module.enter_temp_input();
    ASSERT_TRUE(console_state);
    ASSERT_EQ(*console_state, yli::console::ConsoleState::ACTIVE_IN_TEMP_INPUT);
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::ACTIVE_IN_TEMP_INPUT);
    ASSERT_TRUE(console_logic_module.get_active_in_console());
    ASSERT_FALSE(console_logic_module.get_active_in_new_input());
    ASSERT_FALSE(console_logic_module.get_active_in_historical_input());
    ASSERT_TRUE(console_logic_module.get_active_in_temp_input());
    ASSERT_FALSE(console_logic_module.get_active_in_scrollback_buffer());
}

TEST(entering_scrollback_buffer_from_temp_input_must_work_appropriately, scrollback_buffer_from_temp_input)
{
    // Do the necessary setup.
    yli::console::TextInput new_input(yli::console::TextInputType::NEW_INPUT);
    yli::console::TextInput temp_input(yli::console::TextInputType::TEMP_INPUT);
    yli::console::TextInputHistory text_input_history;
    yli::console::ScrollbackBuffer scrollback_buffer;
    yli::console::ConsoleLogicModule console_logic_module(new_input, temp_input, text_input_history, scrollback_buffer);
    console_logic_module.activate();

    console_logic_module.enter_historical_input();
    console_logic_module.enter_temp_input();
    std::optional<yli::console::ConsoleState> console_state = console_logic_module.enter_scrollback_buffer();
    ASSERT_TRUE(console_state);
    ASSERT_EQ(*console_state, yli::console::ConsoleState::ACTIVE_IN_SCROLLBACK_BUFFER_WHILE_IN_TEMP_INPUT);
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::ACTIVE_IN_SCROLLBACK_BUFFER_WHILE_IN_TEMP_INPUT);
    ASSERT_TRUE(console_logic_module.get_active_in_console());
    ASSERT_FALSE(console_logic_module.get_active_in_new_input());
    ASSERT_FALSE(console_logic_module.get_active_in_historical_input());
    ASSERT_FALSE(console_logic_module.get_active_in_temp_input());
    ASSERT_TRUE(console_logic_module.get_active_in_scrollback_buffer());
}

TEST(entering_new_input_from_scrollback_buffer_must_work_appropriately, new_input_from_scrollback_buffer)
{
    // Do the necessary setup.
    yli::console::TextInput new_input(yli::console::TextInputType::NEW_INPUT);
    yli::console::TextInput temp_input(yli::console::TextInputType::TEMP_INPUT);
    yli::console::TextInputHistory text_input_history;
    yli::console::ScrollbackBuffer scrollback_buffer;
    yli::console::ConsoleLogicModule console_logic_module(new_input, temp_input, text_input_history, scrollback_buffer);
    console_logic_module.activate();

    console_logic_module.enter_scrollback_buffer();
    std::optional<yli::console::ConsoleState> console_state = console_logic_module.enter_new_input();
    ASSERT_TRUE(console_state);
    ASSERT_EQ(*console_state, yli::console::ConsoleState::ACTIVE_IN_NEW_INPUT);
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::ACTIVE_IN_NEW_INPUT);
    ASSERT_TRUE(console_logic_module.get_active_in_console());
    ASSERT_TRUE(console_logic_module.get_active_in_new_input());
    ASSERT_FALSE(console_logic_module.get_active_in_historical_input());
    ASSERT_FALSE(console_logic_module.get_active_in_temp_input());
    ASSERT_FALSE(console_logic_module.get_active_in_scrollback_buffer());
}

TEST(entering_historical_input_from_scrollback_buffer_must_fail_appropriately, historical_input_from_scrollback_buffer)
{
    // Do the necessary setup.
    yli::console::TextInput new_input(yli::console::TextInputType::NEW_INPUT);
    yli::console::TextInput temp_input(yli::console::TextInputType::TEMP_INPUT);
    yli::console::TextInputHistory text_input_history;
    yli::console::ScrollbackBuffer scrollback_buffer;
    yli::console::ConsoleLogicModule console_logic_module(new_input, temp_input, text_input_history, scrollback_buffer);
    console_logic_module.activate();

    console_logic_module.enter_scrollback_buffer();
    ASSERT_FALSE(console_logic_module.enter_historical_input());
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::ACTIVE_IN_SCROLLBACK_BUFFER_WHILE_IN_NEW_INPUT);
    ASSERT_TRUE(console_logic_module.get_active_in_console());
    ASSERT_FALSE(console_logic_module.get_active_in_new_input());
    ASSERT_FALSE(console_logic_module.get_active_in_historical_input());
    ASSERT_FALSE(console_logic_module.get_active_in_temp_input());
    ASSERT_TRUE(console_logic_module.get_active_in_scrollback_buffer());
}

TEST(entering_scrollback_buffer_from_scrollback_buffer_must_work_appropriately, scrollback_buffer_from_scrollback_buffer_while_in_new_input_no_effect)
{
    // Do the necessary setup.
    yli::console::TextInput new_input(yli::console::TextInputType::NEW_INPUT);
    yli::console::TextInput temp_input(yli::console::TextInputType::TEMP_INPUT);
    yli::console::TextInputHistory text_input_history;
    yli::console::ScrollbackBuffer scrollback_buffer;
    yli::console::ConsoleLogicModule console_logic_module(new_input, temp_input, text_input_history, scrollback_buffer);
    console_logic_module.activate();

    console_logic_module.enter_scrollback_buffer();
    std::optional<yli::console::ConsoleState> console_state = console_logic_module.enter_scrollback_buffer();
    ASSERT_TRUE(console_state);
    ASSERT_EQ(*console_state, yli::console::ConsoleState::ACTIVE_IN_SCROLLBACK_BUFFER_WHILE_IN_NEW_INPUT);
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::ACTIVE_IN_SCROLLBACK_BUFFER_WHILE_IN_NEW_INPUT);
    ASSERT_TRUE(console_logic_module.get_active_in_console());
    ASSERT_FALSE(console_logic_module.get_active_in_new_input());
    ASSERT_FALSE(console_logic_module.get_active_in_historical_input());
    ASSERT_FALSE(console_logic_module.get_active_in_temp_input());
    ASSERT_TRUE(console_logic_module.get_active_in_scrollback_buffer());
}

TEST(entering_scrollback_buffer_from_scrollback_buffer_must_work_appropriately, scrollback_buffer_from_scrollback_buffer_while_in_historical_input_no_effect)
{
    // Do the necessary setup.
    yli::console::TextInput new_input(yli::console::TextInputType::NEW_INPUT);
    yli::console::TextInput temp_input(yli::console::TextInputType::TEMP_INPUT);
    yli::console::TextInputHistory text_input_history;
    yli::console::ScrollbackBuffer scrollback_buffer;
    yli::console::ConsoleLogicModule console_logic_module(new_input, temp_input, text_input_history, scrollback_buffer);
    console_logic_module.activate();
    new_input.add_characters("abc");
    text_input_history.add_to_history(new_input);

    console_logic_module.enter_historical_input();
    console_logic_module.enter_scrollback_buffer();
    std::optional<yli::console::ConsoleState> console_state = console_logic_module.enter_scrollback_buffer();
    ASSERT_TRUE(console_state);
    ASSERT_EQ(*console_state, yli::console::ConsoleState::ACTIVE_IN_SCROLLBACK_BUFFER_WHILE_IN_HISTORICAL_INPUT);
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::ACTIVE_IN_SCROLLBACK_BUFFER_WHILE_IN_HISTORICAL_INPUT);
    ASSERT_TRUE(console_logic_module.get_active_in_console());
    ASSERT_FALSE(console_logic_module.get_active_in_new_input());
    ASSERT_FALSE(console_logic_module.get_active_in_historical_input());
    ASSERT_FALSE(console_logic_module.get_active_in_temp_input());
    ASSERT_TRUE(console_logic_module.get_active_in_scrollback_buffer());
}

TEST(entering_scrollback_buffer_from_scrollback_buffer_must_work_appropriately, scrollback_buffer_from_scrollback_buffer_while_in_temp_input_no_effect)
{
    // Do the necessary setup.
    yli::console::TextInput new_input(yli::console::TextInputType::NEW_INPUT);
    yli::console::TextInput temp_input(yli::console::TextInputType::TEMP_INPUT);
    yli::console::TextInputHistory text_input_history;
    yli::console::ScrollbackBuffer scrollback_buffer;
    yli::console::ConsoleLogicModule console_logic_module(new_input, temp_input, text_input_history, scrollback_buffer);
    console_logic_module.activate();

    console_logic_module.enter_historical_input();
    console_logic_module.enter_temp_input();
    console_logic_module.enter_scrollback_buffer();
    std::optional<yli::console::ConsoleState> console_state = console_logic_module.enter_scrollback_buffer();
    ASSERT_TRUE(console_state);
    ASSERT_EQ(*console_state, yli::console::ConsoleState::ACTIVE_IN_SCROLLBACK_BUFFER_WHILE_IN_TEMP_INPUT);
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::ACTIVE_IN_SCROLLBACK_BUFFER_WHILE_IN_TEMP_INPUT);
    ASSERT_TRUE(console_logic_module.get_active_in_console());
    ASSERT_FALSE(console_logic_module.get_active_in_new_input());
    ASSERT_FALSE(console_logic_module.get_active_in_historical_input());
    ASSERT_FALSE(console_logic_module.get_active_in_temp_input());
    ASSERT_TRUE(console_logic_module.get_active_in_scrollback_buffer());
}

TEST(exiting_scrollback_buffer_must_work_appropriately, scrollback_buffer_while_in_new_input)
{
    // Do the necessary setup.
    yli::console::TextInput new_input(yli::console::TextInputType::NEW_INPUT);
    yli::console::TextInput temp_input(yli::console::TextInputType::TEMP_INPUT);
    yli::console::TextInputHistory text_input_history;
    yli::console::ScrollbackBuffer scrollback_buffer;
    yli::console::ConsoleLogicModule console_logic_module(new_input, temp_input, text_input_history, scrollback_buffer, 1, 1);
    console_logic_module.activate();
    new_input.add_characters("a");
    text_input_history.add_to_history(new_input);
    scrollback_buffer.add_to_buffer(new_input);
    console_logic_module.enter_scrollback_buffer();

    std::optional<yli::console::ConsoleState> console_state = console_logic_module.exit_scrollback_buffer();
    ASSERT_TRUE(console_state);
    ASSERT_EQ(*console_state, yli::console::ConsoleState::ACTIVE_IN_NEW_INPUT);
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::ACTIVE_IN_NEW_INPUT);
}

TEST(exiting_scrollback_buffer_must_work_appropriately, scrollback_buffer_while_in_historical_input)
{
    // Do the necessary setup.
    yli::console::TextInput new_input(yli::console::TextInputType::NEW_INPUT);
    yli::console::TextInput temp_input(yli::console::TextInputType::TEMP_INPUT);
    yli::console::TextInputHistory text_input_history;
    yli::console::ScrollbackBuffer scrollback_buffer;
    yli::console::ConsoleLogicModule console_logic_module(new_input, temp_input, text_input_history, scrollback_buffer);
    console_logic_module.activate();
    new_input.add_characters("abc");
    text_input_history.add_to_history(new_input);
    console_logic_module.enter_historical_input();
    console_logic_module.enter_scrollback_buffer();

    std::optional<yli::console::ConsoleState> console_state = console_logic_module.exit_scrollback_buffer();
    ASSERT_TRUE(console_state);
    ASSERT_EQ(*console_state, yli::console::ConsoleState::ACTIVE_IN_HISTORICAL_INPUT);
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::ACTIVE_IN_HISTORICAL_INPUT);
}

TEST(exiting_scrollback_buffer_must_work_appropriately, scrollback_buffer_while_in_temp_input)
{
    // Do the necessary setup.
    yli::console::TextInput new_input(yli::console::TextInputType::NEW_INPUT);
    yli::console::TextInput temp_input(yli::console::TextInputType::TEMP_INPUT);
    yli::console::TextInputHistory text_input_history;
    yli::console::ScrollbackBuffer scrollback_buffer;
    yli::console::ConsoleLogicModule console_logic_module(new_input, temp_input, text_input_history, scrollback_buffer);
    console_logic_module.activate();
    console_logic_module.enter_historical_input();
    console_logic_module.enter_temp_input();
    console_logic_module.enter_scrollback_buffer();

    std::optional<yli::console::ConsoleState> console_state = console_logic_module.exit_scrollback_buffer();
    ASSERT_TRUE(console_state);
    ASSERT_EQ(*console_state, yli::console::ConsoleState::ACTIVE_IN_TEMP_INPUT);
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::ACTIVE_IN_TEMP_INPUT);
}

TEST(editing_current_input_must_work_appropriately, editing_current_input)
{
    // Do the necessary setup.
    yli::console::TextInput new_input(yli::console::TextInputType::NEW_INPUT);
    yli::console::TextInput temp_input(yli::console::TextInputType::TEMP_INPUT);
    yli::console::TextInputHistory text_input_history;
    yli::console::ScrollbackBuffer scrollback_buffer;
    yli::console::ConsoleLogicModule console_logic_module(new_input, temp_input, text_input_history, scrollback_buffer);
    console_logic_module.activate();

    const yli::console::TextInput* const active_input = console_logic_module.edit_input();
    ASSERT_NE(active_input, nullptr);
    ASSERT_EQ(active_input, &new_input);
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::ACTIVE_IN_NEW_INPUT);
}

TEST(editing_historical_input_must_work_appropriately, editing_historical_input)
{
    // Do the necessary setup.
    yli::console::TextInput new_input(yli::console::TextInputType::NEW_INPUT);
    yli::console::TextInput temp_input(yli::console::TextInputType::TEMP_INPUT);
    yli::console::TextInputHistory text_input_history;
    yli::console::ScrollbackBuffer scrollback_buffer;
    yli::console::ConsoleLogicModule console_logic_module(new_input, temp_input, text_input_history, scrollback_buffer);
    console_logic_module.activate();

    new_input.add_characters("abc");
    text_input_history.add_to_history(new_input);
    console_logic_module.enter_historical_input();

    const yli::console::TextInput* const active_input = console_logic_module.edit_input();
    ASSERT_NE(active_input, nullptr);
    ASSERT_EQ(*active_input, text_input_history.at(0));
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::ACTIVE_IN_TEMP_INPUT);
}

TEST(editing_temp_input_must_work_appropriately, editing_temp_input)
{
    // Do the necessary setup.
    yli::console::TextInput new_input(yli::console::TextInputType::NEW_INPUT);
    yli::console::TextInput temp_input(yli::console::TextInputType::TEMP_INPUT);
    yli::console::TextInputHistory text_input_history;
    yli::console::ScrollbackBuffer scrollback_buffer;
    yli::console::ConsoleLogicModule console_logic_module(new_input, temp_input, text_input_history, scrollback_buffer);
    console_logic_module.activate();

    new_input.add_characters("abc");
    text_input_history.add_to_history(new_input);
    console_logic_module.enter_historical_input();

    console_logic_module.edit_input(); // Start editing, this changes state to `ACTIVE_IN_TEMP_INPUT`.
    const yli::console::TextInput* const active_input = console_logic_module.edit_input(); // Should be idempotent.
    ASSERT_NE(active_input, nullptr);
    ASSERT_EQ(active_input->data(), "abc");
    ASSERT_EQ(*active_input, text_input_history.at(0));
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::ACTIVE_IN_TEMP_INPUT);
}

TEST(editing_historical_input_and_returning_to_new_input_must_work_appropriately, editing_historical_input_and_returning_to_new_input)
{
    // Do the necessary setup.
    yli::console::TextInput new_input(yli::console::TextInputType::NEW_INPUT);
    yli::console::TextInput temp_input(yli::console::TextInputType::TEMP_INPUT);
    yli::console::TextInputHistory text_input_history;
    yli::console::ScrollbackBuffer scrollback_buffer;
    yli::console::ConsoleLogicModule console_logic_module(new_input, temp_input, text_input_history, scrollback_buffer);
    console_logic_module.activate();

    new_input.add_characters("abc");
    text_input_history.add_to_history(new_input);
    new_input.clear();

    new_input.add_characters("def");
    console_logic_module.enter_historical_input();

    const yli::console::TextInput* const active_input = console_logic_module.edit_input();
    ASSERT_NE(active_input, nullptr);
    ASSERT_EQ(active_input->data(), "abc");
    ASSERT_EQ(*active_input, text_input_history.at(0));
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::ACTIVE_IN_TEMP_INPUT);

    std::optional<yli::console::ConsoleState> console_state = console_logic_module.enter_new_input();
    ASSERT_TRUE(console_state);
    ASSERT_EQ(console_state, yli::console::ConsoleState::ACTIVE_IN_NEW_INPUT);
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::ACTIVE_IN_NEW_INPUT);
    ASSERT_EQ(console_logic_module.get_visible_input(), &new_input);
    ASSERT_EQ(new_input.data(), "def");
}

TEST(adding_x_to_historical_input_and_returning_to_new_input_must_work_appropriately, adding_x_to_historical_input_and_returning_to_new_input)
{
    // Do the necessary setup.
    yli::console::TextInput new_input(yli::console::TextInputType::NEW_INPUT);
    yli::console::TextInput temp_input(yli::console::TextInputType::TEMP_INPUT);
    yli::console::TextInputHistory text_input_history;
    yli::console::ScrollbackBuffer scrollback_buffer;
    yli::console::ConsoleLogicModule console_logic_module(new_input, temp_input, text_input_history, scrollback_buffer);
    console_logic_module.activate();

    new_input.add_characters("abc");
    text_input_history.add_to_history(new_input);
    new_input.clear();

    new_input.add_characters("def");
    console_logic_module.enter_historical_input();

    yli::console::TextInput* const active_input = console_logic_module.edit_input();
    ASSERT_NE(active_input, nullptr);
    ASSERT_EQ(active_input->data(), "abc");
    ASSERT_EQ(*active_input, text_input_history.at(0));
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::ACTIVE_IN_TEMP_INPUT);
    active_input->add_character('x');
    ASSERT_EQ(active_input->data(), "abcx");

    std::optional<yli::console::ConsoleState> console_state = console_logic_module.enter_new_input();
    ASSERT_TRUE(console_state);
    ASSERT_EQ(console_state, yli::console::ConsoleState::ACTIVE_IN_NEW_INPUT);
    ASSERT_EQ(console_logic_module.get(), yli::console::ConsoleState::ACTIVE_IN_NEW_INPUT);
    ASSERT_EQ(console_logic_module.get_visible_input(), &new_input);
    ASSERT_EQ(new_input.data(), "def");
}
