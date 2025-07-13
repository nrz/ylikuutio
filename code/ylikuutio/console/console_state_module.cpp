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

#include "console_state_module.hpp"
#include "console_state.hpp"

namespace yli::console
{
    class CurrentInput;
    class TempInput;

    void ConsoleStateModule::enter_current_input()
    {
        this->state = ConsoleState::IN_CURRENT_INPUT;
    }

    void ConsoleStateModule::enter_historical_input()
    {
        this->state = ConsoleState::IN_HISTORICAL_INPUT;
    }

    void ConsoleStateModule::enter_temp_input()
    {
        this->state = ConsoleState::IN_TEMP_INPUT;
    }

    void ConsoleStateModule::enter_scrollback_buffer()
    {
        this->state = ConsoleState::IN_SCROLLBACK_BUFFER;
    }

    bool ConsoleStateModule::get_in_console() const
    {
        return this->state != ConsoleState::NOT_IN_CONSOLE;
    }

    bool ConsoleStateModule::get_in_current_input() const
    {
        return this->state == ConsoleState::IN_CURRENT_INPUT;
    }

    bool ConsoleStateModule::get_in_historical_input() const
    {
        return this->state == ConsoleState::IN_HISTORICAL_INPUT;
    }

    bool ConsoleStateModule::get_in_temp_input() const
    {
        return this->state == ConsoleState::IN_TEMP_INPUT;
    }

    bool ConsoleStateModule::get_in_scrollback_buffer() const
    {
        return this->state == ConsoleState::IN_SCROLLBACK_BUFFER;
    }

    void ConsoleStateModule::register_current_input(CurrentInput* const current_input)
    {
        this->current_input = current_input;
    }

    void ConsoleStateModule::register_temp_input(TempInput* const temp_input)
    {
        this->temp_input = temp_input;
    }

    yli::console::ConsoleState ConsoleStateModule::get() const
    {
        return this->state;
    }

    CurrentInput* ConsoleStateModule::get_current_input() const
    {
        return this->current_input;
    }

    TempInput* ConsoleStateModule::get_temp_input() const
    {
        return this->temp_input;
    }

    bool ConsoleStateModule::get_can_move_to_previous_input() const
    {
        return this->can_move_to_previous_input;
    }

    bool ConsoleStateModule::get_can_move_to_next_input() const
    {
        return this->can_move_to_next_input;
    }

    bool ConsoleStateModule::get_can_backspace() const
    {
        return this->can_backspace;
    }

    bool ConsoleStateModule::get_can_tab() const
    {
        return this->can_tab;
    }

    bool ConsoleStateModule::get_can_enter_key() const
    {
        return this->can_enter_key;
    }

    bool ConsoleStateModule::get_can_ctrl_c() const
    {
        return this->can_ctrl_c;
    }

    bool ConsoleStateModule::get_can_ctrl_w() const
    {
        return this->can_ctrl_w;
    }

    bool ConsoleStateModule::get_can_page_up() const
    {
        return this->can_page_up;
    }

    bool ConsoleStateModule::get_can_page_down() const
    {
        return this->can_page_down;
    }

    bool ConsoleStateModule::get_can_home() const
    {
        return this->can_home;
    }

    bool ConsoleStateModule::get_can_end() const
    {
        return this->can_end;
    }

    bool ConsoleStateModule::get_is_left_control_pressed() const
    {
        return this->is_left_control_pressed;
    }

    bool ConsoleStateModule::get_is_right_control_pressed() const
    {
        return this->is_right_control_pressed;
    }

    bool ConsoleStateModule::get_is_left_alt_pressed() const
    {
        return this->is_left_alt_pressed;
    }

    bool ConsoleStateModule::get_is_right_alt_pressed() const
    {
        return this->is_right_alt_pressed;
    }

    bool ConsoleStateModule::get_is_left_shift_pressed() const
    {
        return this->is_left_shift_pressed;
    }

    bool ConsoleStateModule::get_is_right_shift_pressed() const
    {
        return this->is_right_shift_pressed;
    }

    void ConsoleStateModule::set_can_move_to_previous_input(const bool can_move_to_previous_input)
    {
        this->can_move_to_previous_input = can_move_to_previous_input;
    }

    void ConsoleStateModule::set_can_move_to_next_input(const bool can_move_to_next_input)
    {
        this->can_move_to_next_input = can_move_to_next_input;
    }

    void ConsoleStateModule::set_can_backspace(const bool can_backspace)
    {
        this->can_backspace = can_backspace;
    }

    void ConsoleStateModule::set_can_tab(const bool can_tab)
    {
        this->can_tab = can_tab;
    }

    void ConsoleStateModule::set_can_enter_key(const bool can_enter_key)
    {
        this->can_enter_key = can_enter_key;
    }

    void ConsoleStateModule::set_can_ctrl_c(const bool can_ctrl_c)
    {
        this->can_ctrl_c = can_ctrl_c;
    }

    void ConsoleStateModule::set_can_ctrl_w(const bool can_ctrl_w)
    {
        this->can_ctrl_w = can_ctrl_w;
    }

    void ConsoleStateModule::set_can_page_up(const bool can_page_up)
    {
        this->can_page_up = can_page_up;
    }

    void ConsoleStateModule::set_can_page_down(const bool can_page_down)
    {
        this->can_page_down = can_page_down;
    }

    void ConsoleStateModule::set_can_home(const bool can_home)
    {
        this->can_home = can_home;
    }

    void ConsoleStateModule::set_can_end(const bool can_end)
    {
        this->can_end = can_end;
    }

    void ConsoleStateModule::set_is_left_control_pressed(const bool is_left_control_pressed)
    {
        this->is_left_control_pressed = is_left_control_pressed;
    }

    void ConsoleStateModule::set_is_right_control_pressed(const bool is_right_control_pressed)
    {
        this->is_right_control_pressed = is_right_control_pressed;
    }

    void ConsoleStateModule::set_is_left_alt_pressed(const bool is_left_alt_pressed)
    {
        this->is_left_alt_pressed = is_left_alt_pressed;
    }

    void ConsoleStateModule::set_is_right_alt_pressed(const bool is_right_alt_pressed)
    {
        this->is_right_alt_pressed = is_right_alt_pressed;
    }

    void ConsoleStateModule::set_is_left_shift_pressed(const bool is_left_shift_pressed)
    {
        this->is_left_shift_pressed = is_left_shift_pressed;
    }

    void ConsoleStateModule::set_is_right_shift_pressed(const bool is_right_shift_pressed)
    {
        this->is_right_shift_pressed = is_right_shift_pressed;
    }

    void ConsoleStateModule::exit_console()
    {
        this->state = ConsoleState::NOT_IN_CONSOLE;
    }
}
