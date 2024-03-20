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
#include "code/mock/mock_application.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/input_mode.hpp"
#include "code/ylikuutio/ontology/console.hpp"
#include "code/ylikuutio/ontology/input_mode_struct.hpp"
#include "code/ylikuutio/ontology/console_struct.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <limits>  // std::numeric_limits

TEST(console_must_be_initialized_appropriately, no_font)
{
    mock::MockApplication application;
    yli::ontology::ConsoleStruct console_struct;
    yli::ontology::Console* console = application.get_generic_entity_factory().create_console(
            console_struct);
    ASSERT_TRUE(console->get_current_input().empty());
    ASSERT_TRUE(console->get_temp_input().empty());
    ASSERT_EQ(console->get_prompt(), "$ ");        // This may change in the future.
    ASSERT_EQ(console->get_input_mode(), nullptr);
    ASSERT_EQ(console->get_cursor_index(), 0);
    ASSERT_EQ(console->get_history_line_i(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(console->get_historical_input_i(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(console->get_console_top_y(), 9);    // This may change in the future.
    ASSERT_EQ(console->get_console_bottom_y(), 0); // This may change in the future.
    ASSERT_EQ(console->get_console_left_x(), 0);   // This may change in the future.
    ASSERT_EQ(console->get_console_right_x(), 9);  // This may change in the future.
    ASSERT_EQ(console->get_n_rows(), 10);          // This may change in the future.
    ASSERT_EQ(console->get_n_columns(), 10);       // This may change in the future.
    ASSERT_FALSE(console->get_in_console());
    ASSERT_FALSE(console->get_can_move_to_previous_input());
    ASSERT_FALSE(console->get_can_move_to_next_input());
    ASSERT_FALSE(console->get_can_backspace());
    ASSERT_FALSE(console->get_can_tab());
    ASSERT_FALSE(console->get_can_enter_key());
    ASSERT_FALSE(console->get_can_ctrl_c());
    ASSERT_FALSE(console->get_can_ctrl_w());
    ASSERT_FALSE(console->get_can_page_up());
    ASSERT_FALSE(console->get_can_page_down());
    ASSERT_FALSE(console->get_can_home());
    ASSERT_FALSE(console->get_can_end());
    ASSERT_FALSE(console->get_is_left_control_pressed());
    ASSERT_FALSE(console->get_is_right_control_pressed());
    ASSERT_FALSE(console->get_is_left_alt_pressed());
    ASSERT_FALSE(console->get_is_right_alt_pressed());
    ASSERT_FALSE(console->get_is_left_shift_pressed());
    ASSERT_FALSE(console->get_is_right_shift_pressed());
    ASSERT_FALSE(console->get_in_history());
    ASSERT_FALSE(console->get_in_historical_input());

    ASSERT_EQ(console->apprentice_of_font_2d.get_master(), nullptr);
    ASSERT_EQ(console->apprentice_of_font_2d.get_apprenticeID(), std::numeric_limits<std::size_t>::max());
}

TEST(setting_input_mode_of_the_console_must_function_appropriately, no_font)
{
    mock::MockApplication application;
    yli::ontology::ConsoleStruct console_struct;
    yli::ontology::Console* console = application.get_generic_entity_factory().create_console(
            console_struct);

    yli::ontology::InputModeStruct console_mode_input_mode_struct;
    console_mode_input_mode_struct.console = console;
    yli::ontology::InputMode* const input_mode = application.get_generic_entity_factory().create_input_mode(console_mode_input_mode_struct);
    console->set_input_mode(input_mode);
    ASSERT_EQ(console->get_input_mode(), input_mode);

    ASSERT_EQ(console->apprentice_of_font_2d.get_master(), nullptr);
    ASSERT_EQ(console->apprentice_of_font_2d.get_apprenticeID(), std::numeric_limits<std::size_t>::max());
}

TEST(setting_console_top_y_must_function_appropriately, no_font)
{
    mock::MockApplication application;
    yli::ontology::ConsoleStruct console_struct;
    yli::ontology::Console* console = application.get_generic_entity_factory().create_console(
            console_struct);

    console->set_console_top_y(3);
    ASSERT_EQ(console->get_console_top_y(), 3);
    console->set_console_top_y(1);
    ASSERT_EQ(console->get_console_top_y(), 1);
    console->set_console_top_y(4);
    ASSERT_EQ(console->get_console_top_y(), 4);
    console->set_console_top_y(15);
    ASSERT_EQ(console->get_console_top_y(), 15);
}

TEST(setting_console_bottom_y_must_function_appropriately, no_font)
{
    mock::MockApplication application;
    yli::ontology::ConsoleStruct console_struct;
    yli::ontology::Console* console = application.get_generic_entity_factory().create_console(
            console_struct);

    console->set_console_bottom_y(3);
    ASSERT_EQ(console->get_console_bottom_y(), 3);
    console->set_console_bottom_y(1);
    ASSERT_EQ(console->get_console_bottom_y(), 1);
    console->set_console_bottom_y(4);
    ASSERT_EQ(console->get_console_bottom_y(), 4);
    console->set_console_bottom_y(15);
    ASSERT_EQ(console->get_console_bottom_y(), 15);
}

TEST(setting_console_left_x_must_function_appropriately, no_font)
{
    mock::MockApplication application;
    yli::ontology::ConsoleStruct console_struct;
    yli::ontology::Console* console = application.get_generic_entity_factory().create_console(
            console_struct);

    console->set_console_left_x(3);
    ASSERT_EQ(console->get_console_left_x(), 3);
    console->set_console_left_x(1);
    ASSERT_EQ(console->get_console_left_x(), 1);
    console->set_console_left_x(4);
    ASSERT_EQ(console->get_console_left_x(), 4);
    console->set_console_left_x(15);
    ASSERT_EQ(console->get_console_left_x(), 15);
}

TEST(setting_console_right_x_must_function_appropriately, no_font)
{
    mock::MockApplication application;
    yli::ontology::ConsoleStruct console_struct;
    yli::ontology::Console* console = application.get_generic_entity_factory().create_console(
            console_struct);

    console->set_console_right_x(3);
    ASSERT_EQ(console->get_console_right_x(), 3);
    console->set_console_right_x(1);
    ASSERT_EQ(console->get_console_right_x(), 1);
    console->set_console_right_x(4);
    ASSERT_EQ(console->get_console_right_x(), 4);
    console->set_console_right_x(15);
    ASSERT_EQ(console->get_console_right_x(), 15);
}

TEST(enter_console_must_function_appropriately, no_font)
{
    mock::MockApplication application;
    yli::ontology::ConsoleStruct console_struct;
    yli::ontology::Console* console = application.get_generic_entity_factory().create_console(
            console_struct);

    application.get_universe().set_active_console(console);

    yli::ontology::InputModeStruct console_mode_input_mode_struct;
    console_mode_input_mode_struct.console = console;
    yli::ontology::InputMode* const input_mode = application.get_generic_entity_factory().create_input_mode(console_mode_input_mode_struct);
    console->set_input_mode(input_mode);
    console->enter_console();
    ASSERT_TRUE(console->get_in_console());
}

TEST(exit_console_must_function_appropriately, no_font)
{
    mock::MockApplication application;
    yli::ontology::ConsoleStruct console_struct;
    yli::ontology::Console* console = application.get_generic_entity_factory().create_console(
            console_struct);

    application.get_universe().set_active_console(console);

    yli::ontology::InputModeStruct console_mode_input_mode_struct;
    console_mode_input_mode_struct.console = console;
    yli::ontology::InputMode* const input_mode = application.get_generic_entity_factory().create_input_mode(console_mode_input_mode_struct);
    console->set_input_mode(input_mode);
    console->enter_console();
    console->exit_console();
    ASSERT_FALSE(console->get_in_console());
}
