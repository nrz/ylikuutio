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
#include <cstddef>  // std::size_t
#include <limits>   // std::numeric_limits
#include <optional> // std::optional
#include <string>   // std::string

namespace yli::data
{
    class AnyValue;
}

namespace yli::ontology
{
    class GenericParentModule;
    class Universe;
    class CallbackEngine;
    class CallbackObject;
    class Console;
    class ConsoleCallbackEngine;
    class ConsoleCallbackObject;
}

namespace yli::console
{
    class TextInput;
    class TextInputHistory;
    class ScrollbackBuffer;

    class ConsoleLogicModule
    {
        public:
            ConsoleLogicModule(
                    yli::console::TextInput& new_input,
                    yli::console::TextInput& temp_input,
                    yli::console::TextInputHistory& text_input_history,
                    yli::console::ScrollbackBuffer& scrollback_buffer,
                    const std::size_t n_columns = 80,
                    const std::size_t n_rows = 24);

            // State transition functions.
            // `ConsoleLogicModule` keeps track of the console state.
            // Behavior:
            // 1. potentially ask relevant 'modules' if they are ready to change
            //    ('modules' may also do internal changes as a result).
            // 2. do the state change in `ConsoleLogicModule`
            //    (if needed based on the response from relevant 'modules').
            // 3. signal the change to relevant 'modules'.
            //
            // If errors are encountered if any phase, return `std::nullopt`
            // as a sign of failed state transition, but do not roll back changes.
            std::optional<ConsoleState> activate();
            std::optional<ConsoleState> deactivate();
            std::optional<ConsoleState> enter_new_input();
            std::optional<ConsoleState> enter_historical_input();
            std::optional<ConsoleState> enter_temp_input();
            std::optional<ConsoleState> enter_scrollback_buffer();
            std::optional<ConsoleState> exit_scrollback_buffer();
            TextInput* edit_input();

            std::optional<ConsoleState> home();
            std::optional<ConsoleState> end();
            std::optional<ConsoleState> page_up();
            std::optional<ConsoleState> page_down();

            // State inquiry functions.
            bool get_active_in_console() const;
            bool get_active_in_new_input() const;
            bool get_active_in_historical_input() const;
            bool get_active_in_temp_input() const;
            bool get_active_in_scrollback_buffer() const;

            ConsoleState get() const;

            // Module inquiry functions.
            TextInput& get_new_input() const;
            TextInput& get_temp_input() const;
            TextInputHistory& get_text_input_history() const;
            ScrollbackBuffer& get_scrollback_buffer() const;
            const TextInput* get_visible_input() const; // The currently selected input, can be: new input, historical input, or temp input.
            std::optional<std::size_t> get_n_lines_of_visible_input() const;
            std::size_t get_temp_input_index() const;   // Index of the current temp input, or `std::numeric_limits<std::size_t>::max()` if none.

            std::size_t get_n_columns() const;
            std::size_t get_n_rows() const;

            void invalidate_temp_input();

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

            // Public callbacks.

            // Action mode keypress callbacks begin here.

            static std::optional<yli::data::AnyValue> enter_console(
                    yli::ontology::Universe& universe,
                    yli::ontology::CallbackEngine*,
                    yli::ontology::CallbackObject*,
                    yli::ontology::GenericParentModule&,
                    const yli::data::AnyValue&);

            // Console mode keyrelease callbacks begin here.

            static std::optional<yli::data::AnyValue> release_left_control_in_console(
                    yli::ontology::ConsoleCallbackEngine*,
                    yli::ontology::ConsoleCallbackObject*,
                    yli::ontology::GenericParentModule&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> release_right_control_in_console(
                    yli::ontology::ConsoleCallbackEngine*,
                    yli::ontology::ConsoleCallbackObject*,
                    yli::ontology::GenericParentModule&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> release_left_alt_in_console(
                    yli::ontology::ConsoleCallbackEngine*,
                    yli::ontology::ConsoleCallbackObject*,
                    yli::ontology::GenericParentModule&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> release_right_alt_in_console(
                    yli::ontology::ConsoleCallbackEngine*,
                    yli::ontology::ConsoleCallbackObject*,
                    yli::ontology::GenericParentModule&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> release_left_shift_in_console(
                    yli::ontology::ConsoleCallbackEngine*,
                    yli::ontology::ConsoleCallbackObject*,
                    yli::ontology::GenericParentModule&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> release_right_shift_in_console(
                    yli::ontology::ConsoleCallbackEngine*,
                    yli::ontology::ConsoleCallbackObject*,
                    yli::ontology::GenericParentModule&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> enable_move_to_previous_input(
                    yli::ontology::ConsoleCallbackEngine*,
                    yli::ontology::ConsoleCallbackObject*,
                    yli::ontology::GenericParentModule&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> enable_move_to_next_input(
                    yli::ontology::ConsoleCallbackEngine*,
                    yli::ontology::ConsoleCallbackObject*,
                    yli::ontology::GenericParentModule&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> enable_backspace(
                    yli::ontology::ConsoleCallbackEngine*,
                    yli::ontology::ConsoleCallbackObject*,
                    yli::ontology::GenericParentModule&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> enable_tab(
                    yli::ontology::ConsoleCallbackEngine*,
                    yli::ontology::ConsoleCallbackObject*,
                    yli::ontology::GenericParentModule&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> enable_enter_key(
                    yli::ontology::ConsoleCallbackEngine*,
                    yli::ontology::ConsoleCallbackObject*,
                    yli::ontology::GenericParentModule&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> enable_ctrl_c(
                    yli::ontology::ConsoleCallbackEngine*,
                    yli::ontology::ConsoleCallbackObject*,
                    yli::ontology::GenericParentModule&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> enable_ctrl_w(
                    yli::ontology::ConsoleCallbackEngine*,
                    yli::ontology::ConsoleCallbackObject*,
                    yli::ontology::GenericParentModule&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> enable_page_up(
                    yli::ontology::ConsoleCallbackEngine*,
                    yli::ontology::ConsoleCallbackObject*,
                    yli::ontology::GenericParentModule&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> enable_page_down(
                    yli::ontology::ConsoleCallbackEngine*,
                    yli::ontology::ConsoleCallbackObject*,
                    yli::ontology::GenericParentModule&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> enable_home(
                    yli::ontology::ConsoleCallbackEngine*,
                    yli::ontology::ConsoleCallbackObject*,
                    yli::ontology::GenericParentModule&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> enable_end(
                    yli::ontology::ConsoleCallbackEngine*,
                    yli::ontology::ConsoleCallbackObject*,
                    yli::ontology::GenericParentModule&,
                    yli::ontology::Console& console);

            // yli::ontology::Console mode keypress callbacks begin here.

            static std::optional<yli::data::AnyValue> exit_console(
                    yli::ontology::ConsoleCallbackEngine*,
                    yli::ontology::ConsoleCallbackObject*,
                    yli::ontology::GenericParentModule&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> press_left_control_in_console(
                    yli::ontology::ConsoleCallbackEngine*,
                    yli::ontology::ConsoleCallbackObject*,
                    yli::ontology::GenericParentModule&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> press_right_control_in_console(
                    yli::ontology::ConsoleCallbackEngine*,
                    yli::ontology::ConsoleCallbackObject*,
                    yli::ontology::GenericParentModule&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> press_left_alt_in_console(
                    yli::ontology::ConsoleCallbackEngine*,
                    yli::ontology::ConsoleCallbackObject*,
                    yli::ontology::GenericParentModule&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> press_right_alt_in_console(
                    yli::ontology::ConsoleCallbackEngine*,
                    yli::ontology::ConsoleCallbackObject*,
                    yli::ontology::GenericParentModule&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> press_left_shift_in_console(
                    yli::ontology::ConsoleCallbackEngine*,
                    yli::ontology::ConsoleCallbackObject*,
                    yli::ontology::GenericParentModule&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> press_right_shift_in_console(
                    yli::ontology::ConsoleCallbackEngine*,
                    yli::ontology::ConsoleCallbackObject*,
                    yli::ontology::GenericParentModule&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> move_to_previous_input(
                    yli::ontology::ConsoleCallbackEngine*,
                    yli::ontology::ConsoleCallbackObject*,
                    yli::ontology::GenericParentModule&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> move_to_next_input(
                    yli::ontology::ConsoleCallbackEngine*,
                    yli::ontology::ConsoleCallbackObject*,
                    yli::ontology::GenericParentModule&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> backspace(
                    yli::ontology::ConsoleCallbackEngine*,
                    yli::ontology::ConsoleCallbackObject*,
                    yli::ontology::GenericParentModule&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> tab(
                    yli::ontology::ConsoleCallbackEngine*,
                    yli::ontology::ConsoleCallbackObject*,
                    yli::ontology::GenericParentModule&,
                    yli::ontology::Console&);

            static std::optional<yli::data::AnyValue> enter_key(
                    yli::ontology::ConsoleCallbackEngine*,
                    yli::ontology::ConsoleCallbackObject*,
                    yli::ontology::GenericParentModule&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> ctrl_c(
                    yli::ontology::ConsoleCallbackEngine*,
                    yli::ontology::ConsoleCallbackObject*,
                    yli::ontology::GenericParentModule&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> ctrl_w(
                    yli::ontology::ConsoleCallbackEngine*,
                    yli::ontology::ConsoleCallbackObject*,
                    yli::ontology::GenericParentModule&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> page_up(
                    yli::ontology::ConsoleCallbackEngine*,
                    yli::ontology::ConsoleCallbackObject*,
                    yli::ontology::GenericParentModule&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> page_down(
                    yli::ontology::ConsoleCallbackEngine*,
                    yli::ontology::ConsoleCallbackObject*,
                    yli::ontology::GenericParentModule&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> home(
                    yli::ontology::ConsoleCallbackEngine*,
                    yli::ontology::ConsoleCallbackObject*,
                    yli::ontology::GenericParentModule&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> end(
                    yli::ontology::ConsoleCallbackEngine*,
                    yli::ontology::ConsoleCallbackObject*,
                    yli::ontology::GenericParentModule&,
                    yli::ontology::Console& console);

            // Console command callbacks begin here.

            static std::optional<yli::data::AnyValue> clear(
                    yli::ontology::Console& console);

            // Public callbacks end here.

        private:
            std::optional<ConsoleState> signal_state_change(const ConsoleState old_state, const ConsoleState new_state);
            std::optional<ConsoleState> switch_to_state(const ConsoleState new_state);

            ConsoleState state                   { ConsoleState::INACTIVE_IN_NEW_INPUT };
            TextInput& new_input;
            TextInput& temp_input;
            TextInputHistory& text_input_history;
            ScrollbackBuffer& scrollback_buffer;

            const std::size_t n_columns;
            const std::size_t n_rows;

            std::size_t temp_input_index { std::numeric_limits<std::size_t>::max() };

            bool can_move_to_previous_input { true };
            bool can_move_to_next_input     { true };
            bool can_backspace              { true };
            bool can_tab                    { true };
            bool can_enter_key              { true };
            bool can_ctrl_c                 { true };
            bool can_ctrl_w                 { true };
            bool can_page_up                { true };
            bool can_page_down              { true };
            bool can_home                   { true };
            bool can_end                    { true };
            bool is_left_control_pressed    { false };
            bool is_right_control_pressed   { false };
            bool is_left_alt_pressed        { false };
            bool is_right_alt_pressed       { false };
            bool is_left_shift_pressed      { false };
            bool is_right_shift_pressed     { false };

        public:
            const std::string prompt        { "$ " };
    };
}

#endif
