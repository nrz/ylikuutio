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

#ifndef YLIKUUTIO_CONSOLE_CONSOLE_LOGIC_MODULE_HPP_INCLUDED
#define YLIKUUTIO_CONSOLE_CONSOLE_LOGIC_MODULE_HPP_INCLUDED

#include "code/ylikuutio/console/console_state.hpp"

// Include standard headers
#include <optional> // std::optional

namespace yli::console
{
    class TextInput;
    class TextInputHistory;

    class ConsoleLogicModule
    {
        public:
            // State transition functions.
            void activate();
            void deactivate();
            std::optional<ConsoleState> switch_to_state(const ConsoleState new_state);
            std::optional<ConsoleState> enter_current_input();
            std::optional<ConsoleState> enter_historical_input();
            std::optional<ConsoleState> enter_temp_input();
            std::optional<ConsoleState> enter_scrollback_buffer();
            std::optional<ConsoleState> exit_scrollback_buffer();
            TextInput* edit_input();

            // State inquiry functions.
            bool get_active_in_console() const;
            bool get_active_in_current_input() const;
            bool get_active_in_historical_input() const;
            bool get_active_in_temp_input() const;
            bool get_active_in_scrollback_buffer() const;

            // Module registration functions.
            void register_current_input(TextInput* const current_input);
            void register_temp_input(TextInput* const temp_input);
            void register_text_input_history(TextInputHistory* const text_input_history);

            ConsoleState get() const;

            // Module inquiry functions.
            TextInput* get_current_input() const;
            TextInput* get_temp_input() const;
            TextInputHistory* get_text_input_history() const;

            // Boolean state inquiry functions.
            bool get_can_move_to_previous_input() const;
            bool get_can_move_to_next_input() const;
            bool get_can_backspace() const;
            bool get_can_tab() const;
            bool get_can_enter_key() const;
            bool get_can_ctrl_c() const;
            bool get_can_ctrl_w() const;
            bool get_can_page_up() const;
            bool get_can_page_down() const;
            bool get_can_home() const;
            bool get_can_end() const;
            bool get_is_left_control_pressed() const;
            bool get_is_right_control_pressed() const;
            bool get_is_left_alt_pressed() const;
            bool get_is_right_alt_pressed() const;
            bool get_is_left_shift_pressed() const;
            bool get_is_right_shift_pressed() const;

            // Boolean state transitions functions.
            void set_can_move_to_previous_input(const bool can_move_to_previous_input);
            void set_can_move_to_next_input(const bool can_move_to_next_input);
            void set_can_backspace(const bool can_backspace);
            void set_can_tab(const bool can_tab);
            void set_can_enter_key(const bool can_enter_key);
            void set_can_ctrl_c(const bool can_ctrl_c);
            void set_can_ctrl_w(const bool can_ctrl_w);
            void set_can_page_up(const bool can_page_up);
            void set_can_page_down(const bool can_page_down);
            void set_can_home(const bool can_home);
            void set_can_end(const bool can_end);
            void set_is_left_control_pressed(const bool is_left_control_pressed);
            void set_is_right_control_pressed(const bool is_right_control_pressed);
            void set_is_left_alt_pressed(const bool is_left_alt_pressed);
            void set_is_right_alt_pressed(const bool is_right_alt_pressed);
            void set_is_left_shift_pressed(const bool is_left_shift_pressed);
            void set_is_right_shift_pressed(const bool is_right_shift_pressed);

        private:
            ConsoleState state                   { ConsoleState::INACTIVE_IN_CURRENT_INPUT };
            TextInput* current_input             { nullptr };
            TextInput* temp_input                { nullptr };
            TextInputHistory* text_input_history { nullptr };

            bool can_move_to_previous_input { false };
            bool can_move_to_next_input     { false };
            bool can_backspace              { false };
            bool can_tab                    { false };
            bool can_enter_key              { false };
            bool can_ctrl_c                 { false };
            bool can_ctrl_w                 { false };
            bool can_page_up                { false };
            bool can_page_down              { false };
            bool can_home                   { false };
            bool can_end                    { false };
            bool is_left_control_pressed    { false };
            bool is_right_control_pressed   { false };
            bool is_left_alt_pressed        { false };
            bool is_right_alt_pressed       { false };
            bool is_left_shift_pressed      { false };
            bool is_right_shift_pressed     { false };
    };
}

#endif
