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

#include "console_logic_module.hpp"
#include "console_state.hpp"
#include "text_input_history.hpp"
#include "scrollback_buffer.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/lisp/parser.hpp"
#include "code/ylikuutio/lisp/executor.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/console.hpp"
#include "code/ylikuutio/ontology/callback_magic_numbers.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cerr
#include <limits>   // std::numeric_limits
#include <optional> // std::optional
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::ontology
{
    class GenericParentModule;
    class CallbackEngine;
    class CallbackObject;
    class ConsoleCallbackEngine;
    class ConsoleCallbackObject;
}

namespace yli::console
{
    class TextInput;
    class TextInputHistory;
    class ScrollbackBuffer;

    // console states (note: these numbers do not match `ConsoleState` enum values):
    //  0. inactive, in new input (initial state)
    //  1. inactive, in historical input
    //  2. inactive, in temp input
    //  3. inactive, in scrollback buffer while in new input
    //  4. inactive, in scrollback buffer while in historical input
    //  5. inactive, in scrollback buffer while in temp input
    //
    //  6. active, in new input
    //  7. active, in historical input
    //  8. active, in temp input
    //  9. active, in scrollback buffer while in new input
    // 10. active, in scrollback buffer while in historical input
    // 11. active, in scrollback buffer while in temp input
    //
    // 0. initial state: inactive, in new input
    // state transitions:
    // -> 6. active, in new input (activate console)
    //
    // 1. inactive, in historical input (input index needs to keep tracked of)
    // state transitions:
    // -> 7. active, in historical input (input index needs to keep tracked of)
    //
    //  2. inactive, in temp input (input index needs to keep tracked of)
    // state transitions:
    // -> 8. active, in temp input (input index needs to keep tracked of)
    //
    //  3. inactive, in scrollback buffer while in new input (scrollback buffer line and input index need to keep tracked of)
    // state transitions:
    // -> 9. active, in scrollback buffer while in new input (scrollback buffer line and input index need to keep tracked of)
    //
    // 4. inactive, in scrollback buffer while in historical input (scrollback buffer line and input index need to keep tracked of)
    // state transitions:
    // -> 10. active, in scrollback buffer while in historical input (scrollback buffer line and input index need to keep tracked of)
    //
    // 5. inactive, in scrollback buffer while in temp input (scrollback buffer line and input index need to keep tracked of)
    // state transitions:
    // -> 11. active, in scrollback buffer while in temp input (scrollback buffer line and input index need to keep tracked of)
    //
    // 6. active, in new input
    // state transitions:
    // -> 0. inactive, in new input (deactivate)
    // -> 7. active, in historical input (key up to historical input)
    // -> 9. active, in scrollback buffer while in new input (pgup to scrollback buffer)
    //
    // 7. active, in historical input
    // state transitions:
    // ->  1. inactive, in historical input (deactivate)
    // ->  6. active, in new input (key down to new input while in last historical input)
    // ->  7. active, in temp input (edit historical input, that is, copy it to temp input for editing)
    // -> 10. active, in scrollback buffer while in historical input (pgup to scrollback buffer)
    //
    // 8. active, in temp input
    // state transitions:
    // -> 2. inactive, in temp input (deactivate)
    // -> 6. active, in new input (key down to new input while editing last historical input)
    // -> 7. active, in historical input (key up or down to another historical input)
    //
    // 9. active, in scrollback buffer while in new input
    // state transitions:
    // -> 3. inactive, in scrollback buffer while in new input (deactivate)
    // -> 7. active, in historical input (key up to exit scrollback buffer and to move to last historical input)
    //
    // 10. active, in scrollback buffer while in historical input
    // state transitions:
    // -> 4. inactive, in scrollback buffer while in historical input (deactivate)
    // -> 6. active, in new input (key down to new input while in last historical input)
    // -> 7. active, in historical input (key up or down to another historical input)
    // -> 8. active, in temp input (edit historical input, that is, copy it to temp input for editing)
    //
    // 11. active, in scrollback buffer while in temp input
    // state transitions:
    // -> 5. inactive, in scrollback buffer while in temp input (deactivate)
    // -> 6. active, in new input (key down to new input while editing last historical input)
    // -> 7. active, in historical input (key up or down to another historical input)
    // -> 8. active, in temp input (edit historical input, that is, copy it to temp input for editing)

    ConsoleLogicModule::ConsoleLogicModule(
            yli::console::TextInput& new_input,
            yli::console::TextInput& temp_input,
            yli::console::TextInputHistory& text_input_history,
            yli::console::ScrollbackBuffer& scrollback_buffer,
            const std::size_t n_columns,
            const std::size_t n_rows)
        : new_input { new_input },
        temp_input { temp_input },
        text_input_history { text_input_history },
        scrollback_buffer { scrollback_buffer },
        n_columns { n_columns },
        n_rows { n_rows }
    {
    }

    // State transition functions.

    std::optional<ConsoleState> ConsoleLogicModule::activate()
    {
        // Activation is not reported to 'modules' because they don't need to know.
        // Activation always returns to the same state in which deactivate was run.
        return this->switch_to_state(ConsoleState(this->state | yli::console::active));
    }

    std::optional<ConsoleState> ConsoleLogicModule::deactivate()
    {
        // Deactivation is not reported to 'modules' because they don't need to know.
        // Deactivation always returns to the last active state.
        return this->switch_to_state(ConsoleState(this->state & (~yli::console::active)));
    }

    std::optional<ConsoleState> ConsoleLogicModule::enter_new_input()
    {
        return this->switch_to_state(ConsoleState::ACTIVE_IN_NEW_INPUT);
    }

    std::optional<ConsoleState> ConsoleLogicModule::enter_historical_input()
    {
        // If there is no historical input, then do not enter historical input.
        if (this->text_input_history.empty()) [[unlikely]]
        {
            return std::nullopt; // Transition failed.
        }

        return this->switch_to_state(ConsoleState::ACTIVE_IN_HISTORICAL_INPUT);
    }

    std::optional<ConsoleState> ConsoleLogicModule::enter_temp_input()
    {
        // If there is no temp input, then do not enter temp input.
        if (this->text_input_history.empty() || this->temp_input_index == std::numeric_limits<std::size_t>::max()) [[unlikely]]
        {
            return std::nullopt; // Transition failed.
        }

        return this->switch_to_state(ConsoleState::ACTIVE_IN_TEMP_INPUT);
    }

    std::optional<ConsoleState> ConsoleLogicModule::enter_scrollback_buffer()
    {
        return this->switch_to_state(ConsoleState(this->state | yli::console::in_scrollback_buffer));
    }

    std::optional<ConsoleState> ConsoleLogicModule::exit_scrollback_buffer()
    {
        return this->switch_to_state(ConsoleState(this->state & (~yli::console::in_scrollback_buffer)));
    }

    TextInput* ConsoleLogicModule::edit_input()
    {
        if (this->state == yli::console::ConsoleState::ACTIVE_IN_NEW_INPUT)
        {
            // If we are in new input, the new input is the active input.
            // If we are in scrollback buffer while in new input, the new input is the active input.
            return &this->new_input;
        }
        else if (this->state == yli::console::ConsoleState::ACTIVE_IN_HISTORICAL_INPUT)
        {
            // If we are in a historical input, the temp input is the active input.
            // If we are in scrollback buffer while in historical input, the historical input is the active input.
            const TextInput* const historical_input = this->text_input_history.get();

            if (historical_input != nullptr)
            {
                // If we are in historical input or in scrollback buffer
                // while in historical input, the current historical input becomes
                // the new temp input, and temp input becomes the active input.
                this->switch_to_state(yli::console::ConsoleState::ACTIVE_IN_TEMP_INPUT);
                this->temp_input_index = this->text_input_history.get_history_index();
                this->temp_input = *historical_input;
                this->temp_input.move_cursor_to_end_of_line();
                return &this->temp_input;
            }
        }
        else if (this->state == yli::console::ConsoleState::ACTIVE_IN_TEMP_INPUT)
        {
            // If we are in a temp input, the temp input is the active input.
            // If we are in scrollback buffer while in temp input, the temp input is the active input.
            return &this->temp_input;
        }

        // Otherwise we have no active input.
        return nullptr;
    }

    std::optional<ConsoleState> ConsoleLogicModule::page_up()
    {
        // This function does page up action and returns the resulting console state.

        if (this->get_active_in_scrollback_buffer())
        {
            // We are already in scrollback buffer.
            if (this->scrollback_buffer.page_up()) [[likely]]
            {
                return this->state;
            }
            else
            {
                return std::nullopt; // Transition failed.
            }
        }

        // Enter scrollback buffer and signal console state change to 'modules'.
        return this->enter_scrollback_buffer();
    }

    std::optional<ConsoleState> ConsoleLogicModule::page_down()
    {
        // This function does page down action and returns the resulting console state.

        if (this->get_active_in_scrollback_buffer()) [[likely]]
        {
            // We are in scrollback buffer.

            if (!this->scrollback_buffer.page_down())
            {
                // No space to page down without exiting scrollback buffer.

                // Exit scrollback buffer and signal console state change to 'modules'.
                return this->exit_scrollback_buffer();
            }
        }

        // No change in state.
        return this->state;
    }

    // State inquiry functions.

    bool ConsoleLogicModule::get_active_in_console() const
    {
        return this->state & yli::console::active;
    }

    bool ConsoleLogicModule::get_active_in_new_input() const
    {
        return this->state == ConsoleState::ACTIVE_IN_NEW_INPUT;
    }

    bool ConsoleLogicModule::get_active_in_historical_input() const
    {
        return this->state == ConsoleState::ACTIVE_IN_HISTORICAL_INPUT;
    }

    bool ConsoleLogicModule::get_active_in_temp_input() const
    {
        return this->state == ConsoleState::ACTIVE_IN_TEMP_INPUT;
    }

    bool ConsoleLogicModule::get_active_in_scrollback_buffer() const
    {
        return (this->state & yli::console::active) && (this->state & yli::console::in_scrollback_buffer);
    }

    yli::console::ConsoleState ConsoleLogicModule::get() const
    {
        return this->state;
    }

    // Module inquiry functions.

    TextInput& ConsoleLogicModule::get_new_input() const
    {
        return this->new_input;
    }

    TextInput& ConsoleLogicModule::get_temp_input() const
    {
        return this->temp_input;
    }

    TextInputHistory& ConsoleLogicModule::get_text_input_history() const
    {
        return this->text_input_history;
    }

    ScrollbackBuffer& ConsoleLogicModule::get_scrollback_buffer() const
    {
        return this->scrollback_buffer;
    }

    const TextInput* ConsoleLogicModule::get_visible_input() const
    {
        // This function returns the selected (visible) input irrespective whether it's edited or not.
        // This function returns the selected input even if we are in scrollback buffer and the
        // input might not be visible completely or at all. The console rendering code needs to take care
        // of rendering the right lines.

        if (this->state == ConsoleState::ACTIVE_IN_NEW_INPUT || this->state == ConsoleState::ACTIVE_IN_SCROLLBACK_BUFFER_WHILE_IN_NEW_INPUT)
        {
            // If we are in new input, the new input is the visible input.
            // If we are in scrollback buffer while in new input, the new input is the visible input.
            return &this->new_input;
        }
        else if (this->state == ConsoleState::ACTIVE_IN_HISTORICAL_INPUT || this->state == ACTIVE_IN_SCROLLBACK_BUFFER_WHILE_IN_HISTORICAL_INPUT)
        {
            // If we are in a historical input, the temp input is the visible input.
            // If we are in scrollback buffer while in historical input, the historical input is the visible input.
            return this->text_input_history.get();
        }
        else if (this->state == console::ConsoleState::ACTIVE_IN_TEMP_INPUT || this->state == ACTIVE_IN_SCROLLBACK_BUFFER_WHILE_IN_TEMP_INPUT)
        {
            // If we are in a temp input, the temp input is the visible input.
            // If we are in scrollback buffer while in temp input, the temp input is the visible input.
            return &this->temp_input;
        }

        // Otherwise we have no selected visible input.
        return nullptr;
    }

    std::size_t ConsoleLogicModule::get_temp_input_index() const
    {
        return this->temp_input_index;
    }

    std::size_t ConsoleLogicModule::get_n_columns() const
    {
        return this->n_columns;
    }

    std::size_t ConsoleLogicModule::get_n_rows() const
    {
        return this->n_rows;
    }

    void ConsoleLogicModule::invalidate_temp_input()
    {
        this->temp_input.clear();
        this->temp_input_index = std::numeric_limits<std::size_t>::max();
    }

    // Boolean state inquiry functions.

    bool ConsoleLogicModule::get_can_move_to_previous_input() const
    {
        return this->can_move_to_previous_input;
    }

    bool ConsoleLogicModule::get_can_move_to_next_input() const
    {
        return this->can_move_to_next_input;
    }

    bool ConsoleLogicModule::get_can_backspace() const
    {
        return this->can_backspace;
    }

    bool ConsoleLogicModule::get_can_tab() const
    {
        return this->can_tab;
    }

    bool ConsoleLogicModule::get_can_enter_key() const
    {
        return this->can_enter_key;
    }

    bool ConsoleLogicModule::get_can_ctrl_c() const
    {
        return this->can_ctrl_c;
    }

    bool ConsoleLogicModule::get_can_ctrl_w() const
    {
        return this->can_ctrl_w;
    }

    bool ConsoleLogicModule::get_can_page_up() const
    {
        return this->can_page_up;
    }

    bool ConsoleLogicModule::get_can_page_down() const
    {
        return this->can_page_down;
    }

    bool ConsoleLogicModule::get_can_home() const
    {
        return this->can_home;
    }

    bool ConsoleLogicModule::get_can_end() const
    {
        return this->can_end;
    }

    bool ConsoleLogicModule::get_is_left_control_pressed() const
    {
        return this->is_left_control_pressed;
    }

    bool ConsoleLogicModule::get_is_right_control_pressed() const
    {
        return this->is_right_control_pressed;
    }

    bool ConsoleLogicModule::get_is_left_alt_pressed() const
    {
        return this->is_left_alt_pressed;
    }

    bool ConsoleLogicModule::get_is_right_alt_pressed() const
    {
        return this->is_right_alt_pressed;
    }

    bool ConsoleLogicModule::get_is_left_shift_pressed() const
    {
        return this->is_left_shift_pressed;
    }

    bool ConsoleLogicModule::get_is_right_shift_pressed() const
    {
        return this->is_right_shift_pressed;
    }

    // Boolean state transitions functions.

    void ConsoleLogicModule::set_can_move_to_previous_input(const bool can_move_to_previous_input)
    {
        this->can_move_to_previous_input = can_move_to_previous_input;
    }

    void ConsoleLogicModule::set_can_move_to_next_input(const bool can_move_to_next_input)
    {
        this->can_move_to_next_input = can_move_to_next_input;
    }

    void ConsoleLogicModule::set_can_backspace(const bool can_backspace)
    {
        this->can_backspace = can_backspace;
    }

    void ConsoleLogicModule::set_can_tab(const bool can_tab)
    {
        this->can_tab = can_tab;
    }

    void ConsoleLogicModule::set_can_enter_key(const bool can_enter_key)
    {
        this->can_enter_key = can_enter_key;
    }

    void ConsoleLogicModule::set_can_ctrl_c(const bool can_ctrl_c)
    {
        this->can_ctrl_c = can_ctrl_c;
    }

    void ConsoleLogicModule::set_can_ctrl_w(const bool can_ctrl_w)
    {
        this->can_ctrl_w = can_ctrl_w;
    }

    void ConsoleLogicModule::set_can_page_up(const bool can_page_up)
    {
        this->can_page_up = can_page_up;
    }

    void ConsoleLogicModule::set_can_page_down(const bool can_page_down)
    {
        this->can_page_down = can_page_down;
    }

    void ConsoleLogicModule::set_can_home(const bool can_home)
    {
        this->can_home = can_home;
    }

    void ConsoleLogicModule::set_can_end(const bool can_end)
    {
        this->can_end = can_end;
    }

    void ConsoleLogicModule::set_is_left_control_pressed(const bool is_left_control_pressed)
    {
        this->is_left_control_pressed = is_left_control_pressed;
    }

    void ConsoleLogicModule::set_is_right_control_pressed(const bool is_right_control_pressed)
    {
        this->is_right_control_pressed = is_right_control_pressed;
    }

    void ConsoleLogicModule::set_is_left_alt_pressed(const bool is_left_alt_pressed)
    {
        this->is_left_alt_pressed = is_left_alt_pressed;
    }

    void ConsoleLogicModule::set_is_right_alt_pressed(const bool is_right_alt_pressed)
    {
        this->is_right_alt_pressed = is_right_alt_pressed;
    }

    void ConsoleLogicModule::set_is_left_shift_pressed(const bool is_left_shift_pressed)
    {
        this->is_left_shift_pressed = is_left_shift_pressed;
    }

    void ConsoleLogicModule::set_is_right_shift_pressed(const bool is_right_shift_pressed)
    {
        this->is_right_shift_pressed = is_right_shift_pressed;
    }

    std::optional<ConsoleState> ConsoleLogicModule::signal_state_change(const ConsoleState old_state, const ConsoleState new_state)
    {
        // Signal the 'modules' that the state has changed.

        this->new_input.on_change(old_state, new_state);
        this->temp_input.on_change(old_state, new_state);
        this->text_input_history.on_change(old_state, new_state);
        this->scrollback_buffer.on_change(old_state, new_state);
        return new_state;
    }

    std::optional<ConsoleState> ConsoleLogicModule::switch_to_state(const ConsoleState new_state)
    {
        const ConsoleState old_state = this->state;

        if (!((this->state ^ new_state) & (~yli::console::active)))
        {
            // If the old state and new state differ possibly only with regards to activation state,
            // then the transition is valid.
            this->state = new_state;
            return this->signal_state_change(old_state, new_state);
        }
        else if (!((this->state ^ new_state) & (~yli::console::in_scrollback_buffer)) && (this->state & yli::console::active))
        {
            // If the old state and new state differ possibly only with regards to in-scrollback-buffer state,
            // and the current state in active, then the transition is valid.
            this->state = new_state;
            return this->signal_state_change(old_state, new_state);
        }
        else if (const uint32_t any_input = in_new_input | in_historical_input | in_temp_input;
                !((this->state ^ new_state) & (~any_input)) && (this->state & yli::console::active))
        {
            // If the old state and new state differ possibly only with regards to which-buffer state,
            // and the current state in active, then the transition is valid.
            this->state = new_state;
            return this->signal_state_change(old_state, new_state);
        }

        std::cerr << "ERROR: `ConsoleLogicModule::switch_to_state`: state transition failed!\n";
        return std::nullopt; // Transition failed.
    }

    // Public callbacks.

    // Action mode keyrelease callbacks begin here.

    // Action mode keypress callbacks begin here.

    std::optional<yli::data::AnyValue> ConsoleLogicModule::enter_console(
            yli::ontology::Universe& universe,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject*,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&)
    {
        yli::ontology::Console* const console = universe.get_active_console();

        if (console == nullptr)
        {
            // We did not enter the console.
            return std::nullopt;
        }

        if (console->enter_console())
        {
            // Signal to caller that we have entered the console.
            uint32_t enter_console_magic_number = yli::ontology::CallbackMagicNumber::ENTER_CONSOLE;
            return yli::data::AnyValue(enter_console_magic_number);
        }

        // We did not enter the console.
        return std::nullopt;
    }

    // Console mode keyrelease callbacks begin here.

    std::optional<yli::data::AnyValue> ConsoleLogicModule::release_left_control_in_console(
            yli::ontology::ConsoleCallbackEngine*,
            yli::ontology::ConsoleCallbackObject*,
            yli::ontology::GenericParentModule&,
            yli::ontology::Console& console)
    {
        if (console.console_logic_module.get_active_in_console())
        {
            console.console_logic_module.set_is_left_control_pressed(false);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> ConsoleLogicModule::release_right_control_in_console(
            yli::ontology::ConsoleCallbackEngine*,
            yli::ontology::ConsoleCallbackObject*,
            yli::ontology::GenericParentModule&,
            yli::ontology::Console& console)
    {
        if (console.console_logic_module.get_active_in_console())
        {
            console.console_logic_module.set_is_right_control_pressed(false);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> ConsoleLogicModule::release_left_alt_in_console(
            yli::ontology::ConsoleCallbackEngine*,
            yli::ontology::ConsoleCallbackObject*,
            yli::ontology::GenericParentModule&,
            yli::ontology::Console& console)
    {
        if (console.console_logic_module.get_active_in_console())
        {
            console.console_logic_module.set_is_left_alt_pressed(false);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> ConsoleLogicModule::release_right_alt_in_console(
            yli::ontology::ConsoleCallbackEngine*,
            yli::ontology::ConsoleCallbackObject*,
            yli::ontology::GenericParentModule&,
            yli::ontology::Console& console)
    {
        if (console.console_logic_module.get_active_in_console())
        {
            console.console_logic_module.set_is_right_alt_pressed(false);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> ConsoleLogicModule::release_left_shift_in_console(
            yli::ontology::ConsoleCallbackEngine*,
            yli::ontology::ConsoleCallbackObject*,
            yli::ontology::GenericParentModule&,
            yli::ontology::Console& console)
    {
        if (console.console_logic_module.get_active_in_console())
        {
            console.console_logic_module.set_is_left_shift_pressed(false);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> ConsoleLogicModule::release_right_shift_in_console(
            yli::ontology::ConsoleCallbackEngine*,
            yli::ontology::ConsoleCallbackObject*,
            yli::ontology::GenericParentModule&,
            yli::ontology::Console& console)
    {
        if (console.console_logic_module.get_active_in_console())
        {
            console.console_logic_module.set_is_right_shift_pressed(false);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> ConsoleLogicModule::enable_move_to_previous_input(
            yli::ontology::ConsoleCallbackEngine*,
            yli::ontology::ConsoleCallbackObject*,
            yli::ontology::GenericParentModule&,
            yli::ontology::Console& console)
    {
        if (console.console_logic_module.get_active_in_console())
        {
            console.console_logic_module.set_can_move_to_previous_input(true);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> ConsoleLogicModule::enable_move_to_next_input(
            yli::ontology::ConsoleCallbackEngine*,
            yli::ontology::ConsoleCallbackObject*,
            yli::ontology::GenericParentModule&,
            yli::ontology::Console& console)
    {
        if (console.console_logic_module.get_active_in_console())
        {
            console.console_logic_module.set_can_move_to_next_input(true);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> ConsoleLogicModule::enable_backspace(
            yli::ontology::ConsoleCallbackEngine*,
            yli::ontology::ConsoleCallbackObject*,
            yli::ontology::GenericParentModule&,
            yli::ontology::Console& console)
    {
        if (console.console_logic_module.get_active_in_console())
        {
            console.console_logic_module.set_can_backspace(true);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> ConsoleLogicModule::enable_tab(
            yli::ontology::ConsoleCallbackEngine*,
            yli::ontology::ConsoleCallbackObject*,
            yli::ontology::GenericParentModule&,
            yli::ontology::Console& console)
    {
        if (console.console_logic_module.get_active_in_console())
        {
            console.console_logic_module.set_can_tab(true);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> ConsoleLogicModule::enable_enter_key(
            yli::ontology::ConsoleCallbackEngine*,
            yli::ontology::ConsoleCallbackObject*,
            yli::ontology::GenericParentModule&,
            yli::ontology::Console& console)
    {
        if (console.console_logic_module.get_active_in_console())
        {
            console.console_logic_module.set_can_enter_key(true);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> ConsoleLogicModule::enable_ctrl_c(
            yli::ontology::ConsoleCallbackEngine*,
            yli::ontology::ConsoleCallbackObject*,
            yli::ontology::GenericParentModule&,
            yli::ontology::Console& console)
    {
        if (console.console_logic_module.get_active_in_console())
        {
            console.console_logic_module.set_can_ctrl_c(true);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> ConsoleLogicModule::enable_ctrl_w(
            yli::ontology::ConsoleCallbackEngine*,
            yli::ontology::ConsoleCallbackObject*,
            yli::ontology::GenericParentModule&,
            yli::ontology::Console& console)
    {
        if (console.console_logic_module.get_active_in_console())
        {
            console.console_logic_module.set_can_ctrl_w(true);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> ConsoleLogicModule::enable_page_up(
            yli::ontology::ConsoleCallbackEngine*,
            yli::ontology::ConsoleCallbackObject*,
            yli::ontology::GenericParentModule&,
            yli::ontology::Console& console)
    {
        if (console.console_logic_module.get_active_in_console())
        {
            console.console_logic_module.set_can_page_up(true);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> ConsoleLogicModule::enable_page_down(
            yli::ontology::ConsoleCallbackEngine*,
            yli::ontology::ConsoleCallbackObject*,
            yli::ontology::GenericParentModule&,
            yli::ontology::Console& console)
    {
        if (console.console_logic_module.get_active_in_console())
        {
            console.console_logic_module.set_can_page_down(true);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> ConsoleLogicModule::enable_home(
            yli::ontology::ConsoleCallbackEngine*,
            yli::ontology::ConsoleCallbackObject*,
            yli::ontology::GenericParentModule&,
            yli::ontology::Console& console)
    {
        if (console.console_logic_module.get_active_in_console())
        {
            console.console_logic_module.set_can_home(true);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> ConsoleLogicModule::enable_end(
            yli::ontology::ConsoleCallbackEngine*,
            yli::ontology::ConsoleCallbackObject*,
            yli::ontology::GenericParentModule&,
            yli::ontology::Console& console)
    {
        if (console.console_logic_module.get_active_in_console())
        {
            console.console_logic_module.set_can_end(true);
        }
        return std::nullopt;
    }

    // Console mode keypress callbacks begin here.

    std::optional<yli::data::AnyValue> ConsoleLogicModule::exit_console(
            yli::ontology::ConsoleCallbackEngine*,
            yli::ontology::ConsoleCallbackObject*,
            yli::ontology::GenericParentModule&,
            yli::ontology::Console& console)
    {
        if (console.console_logic_module.get_active_in_console() && console.exit_console())
        {
            // Signal to caller that we have exited the console.
            uint32_t exit_console_magic_number = yli::ontology::CallbackMagicNumber::EXIT_CONSOLE;
            return yli::data::AnyValue(exit_console_magic_number);
        }

        // We did not exit the console.
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> ConsoleLogicModule::press_left_control_in_console(
            yli::ontology::ConsoleCallbackEngine*,
            yli::ontology::ConsoleCallbackObject*,
            yli::ontology::GenericParentModule&,
            yli::ontology::Console& console)
    {
        if (console.console_logic_module.get_active_in_console())
        {
            console.console_logic_module.set_is_left_control_pressed(true);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> ConsoleLogicModule::press_right_control_in_console(
            yli::ontology::ConsoleCallbackEngine*,
            yli::ontology::ConsoleCallbackObject*,
            yli::ontology::GenericParentModule&,
            yli::ontology::Console& console)
    {
        if (console.console_logic_module.get_active_in_console())
        {
            console.console_logic_module.set_is_right_control_pressed(true);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> ConsoleLogicModule::press_left_alt_in_console(
            yli::ontology::ConsoleCallbackEngine*,
            yli::ontology::ConsoleCallbackObject*,
            yli::ontology::GenericParentModule&,
            yli::ontology::Console& console)
    {
        if (console.console_logic_module.get_active_in_console())
        {
            console.console_logic_module.set_is_left_alt_pressed(true);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> ConsoleLogicModule::press_right_alt_in_console(
            yli::ontology::ConsoleCallbackEngine*,
            yli::ontology::ConsoleCallbackObject*,
            yli::ontology::GenericParentModule&,
            yli::ontology::Console& console)
    {
        if (console.console_logic_module.get_active_in_console())
        {
            console.console_logic_module.set_is_right_alt_pressed(true);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> ConsoleLogicModule::press_left_shift_in_console(
            yli::ontology::ConsoleCallbackEngine*,
            yli::ontology::ConsoleCallbackObject*,
            yli::ontology::GenericParentModule&,
            yli::ontology::Console& console)
    {
        if (console.console_logic_module.get_active_in_console())
        {
            console.console_logic_module.set_is_left_shift_pressed(true);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> ConsoleLogicModule::press_right_shift_in_console(
            yli::ontology::ConsoleCallbackEngine*,
            yli::ontology::ConsoleCallbackObject*,
            yli::ontology::GenericParentModule&,
            yli::ontology::Console& console)
    {
        if (console.console_logic_module.get_active_in_console())
        {
            console.console_logic_module.set_is_right_shift_pressed(true);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> ConsoleLogicModule::move_to_previous_input(
            yli::ontology::ConsoleCallbackEngine*,
            yli::ontology::ConsoleCallbackObject*,
            yli::ontology::GenericParentModule&,
            yli::ontology::Console& console)
    {
        if (console.console_logic_module.get_active_in_console() && console.console_logic_module.get_can_move_to_previous_input())
        {
            const std::size_t history_index = console.command_history.get_history_index();
            const std::size_t temp_input_index = console.console_logic_module.get_temp_input_index();

            if (console.console_logic_module.get_active_in_new_input() &&
                    !console.command_history.empty() &&
                    temp_input_index == console.command_history.size() - 1)
            {
                // OK, we moved from the new input to the last historical input, which happens to be the temp input.
                console.console_logic_module.enter_historical_input();
                console.console_logic_module.enter_temp_input();
                console.temp_input.move_cursor_to_end_of_line();
            }
            else if (console.console_logic_module.get_active_in_new_input() &&
                    !console.command_history.empty())
            {
                // OK, we moved from the new input to the last historical input.
                console.console_logic_module.enter_historical_input();
            }
            else if (console.console_logic_module.get_active_in_historical_input() &&
                    history_index > 0 &&
                    history_index - 1 == temp_input_index)
            {
                // OK, we moved to the previous historical input, which happens to be the temp input.
                console.command_history.move_to_previous();
                console.console_logic_module.enter_temp_input();
                console.temp_input.move_cursor_to_end_of_line();
            }
            else if (console.console_logic_module.get_active_in_historical_input() && history_index > 0)
            {
                // OK, we moved to the previous historical input.
                console.command_history.move_to_previous();
            }
            else if (console.console_logic_module.get_active_in_temp_input() && history_index > 0)
            {
                // OK, we moved to the previous historical input from temp input.
                console.console_logic_module.enter_historical_input();
                console.command_history.move_to_nth(history_index - 1);
            }

            console.console_logic_module.set_can_move_to_previous_input(false);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> ConsoleLogicModule::move_to_next_input(
            yli::ontology::ConsoleCallbackEngine*,
            yli::ontology::ConsoleCallbackObject*,
            yli::ontology::GenericParentModule&,
            yli::ontology::Console& console)
    {
        if (console.console_logic_module.get_active_in_console() && console.console_logic_module.get_can_move_to_next_input() && !console.command_history.empty())
        {
            const std::size_t history_index = console.command_history.get_history_index();
            const std::size_t temp_input_index = console.console_logic_module.get_temp_input_index();

            if (console.console_logic_module.get_active_in_historical_input() && history_index == console.command_history.size() - 1)
            {
                // OK, we moved from the last historical input to the new input.
                console.console_logic_module.enter_new_input();
                console.new_input.move_cursor_to_end_of_line();
            }
            else if (console.console_logic_module.get_active_in_temp_input() && history_index == console.command_history.size() - 1)
            {
                // OK, we moved from the edited last historical input (temp input) to the new input.
                console.console_logic_module.enter_new_input();
                console.new_input.move_cursor_to_end_of_line();
            }
            else if (console.console_logic_module.get_active_in_historical_input() &&
                    history_index < console.command_history.size() - 1 &&
                    history_index + 1 == temp_input_index)
            {
                // OK, we moved to the next historical input which happens to be the temp input.
                console.command_history.move_to_next();
                console.console_logic_module.enter_temp_input();
                console.temp_input.move_cursor_to_end_of_line();
            }
            else if (console.console_logic_module.get_active_in_historical_input() && history_index < console.command_history.size() - 1)
            {
                // OK, we moved to the next historical input.
                console.command_history.move_to_next();
            }
            else if (console.console_logic_module.get_active_in_temp_input() && history_index < console.command_history.size() - 1)
            {
                // OK, we moved to the next historical input from temp input.
                console.console_logic_module.enter_historical_input(); // Entering historical input causes history index reset to last.
                console.command_history.move_to_nth(history_index + 1);
            }

            console.console_logic_module.set_can_move_to_next_input(false);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> ConsoleLogicModule::backspace(
            yli::ontology::ConsoleCallbackEngine*,
            yli::ontology::ConsoleCallbackObject*,
            yli::ontology::GenericParentModule&,
            yli::ontology::Console& console)
    {
        if (console.console_logic_module.get_active_in_console() &&
                console.console_logic_module.get_can_backspace())
        {
            yli::console::TextInput* const active_input = console.console_logic_module.edit_input();

            if (active_input != nullptr)
            {
                active_input->delete_character();
            }

            console.console_logic_module.set_can_backspace(false);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> ConsoleLogicModule::tab(
            yli::ontology::ConsoleCallbackEngine*,
            yli::ontology::ConsoleCallbackObject*,
            yli::ontology::GenericParentModule&,
            yli::ontology::Console& console)
    {
        console.completion_module.complete();
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> ConsoleLogicModule::enter_key(
            yli::ontology::ConsoleCallbackEngine*,
            yli::ontology::ConsoleCallbackObject*,
            yli::ontology::GenericParentModule&,
            yli::ontology::Console& console)
    {
        if (!console.console_logic_module.get_active_in_console() || !console.console_logic_module.get_can_enter_key())
        {
            return std::nullopt;
        }

        yli::console::TextInput* const active_input = console.console_logic_module.edit_input();

        if (active_input == nullptr)
        {
            std::cerr << "ERROR: `ConsoleLogicModule::enter_key`: `active_input` is `nullptr`!\n";
            return std::nullopt;
        }

        // Copy prompt input into a `std::string`.
        std::string input_string(console.prompt);

        // Append active input.
        input_string.append(active_input->data().begin(), active_input->data().end());

        // Copy active input into the command history.
        console.command_history.add_to_history(*active_input);

        // Store new input prefixed with prompt to scrollback buffer.
        console.scrollback_buffer.add_to_buffer(yli::console::TextLine(input_string));

        std::vector<std::string> parameter_vector;
        std::string command;

        console.new_input.clear();

        if (yli::lisp::parse(console.command_history.at(console.command_history.size() - 1).data(), command, parameter_vector))
        {
            std::optional<yli::data::AnyValue> any_value = yli::lisp::execute(console, command, parameter_vector);
            console.console_logic_module.enter_new_input();
            console.console_logic_module.invalidate_temp_input();
            console.console_logic_module.set_can_enter_key(false);
            return any_value;
        }

        console.console_logic_module.enter_new_input();
        console.console_logic_module.invalidate_temp_input();
        console.console_logic_module.set_can_enter_key(false);
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> ConsoleLogicModule::ctrl_c(
            yli::ontology::ConsoleCallbackEngine*,
            yli::ontology::ConsoleCallbackObject*,
            yli::ontology::GenericParentModule&,
            yli::ontology::Console& console)
    {
        if (console.console_logic_module.get_active_in_console() &&
                console.console_logic_module.get_can_ctrl_c() &&
                (console.console_logic_module.get_is_left_control_pressed() || console.console_logic_module.get_is_right_control_pressed()) &&
                !console.console_logic_module.get_is_left_alt_pressed() && !console.console_logic_module.get_is_right_alt_pressed() &&
                !console.console_logic_module.get_is_left_shift_pressed() && !console.console_logic_module.get_is_right_shift_pressed())
        {
            console.new_input.clear();
            console.console_logic_module.enter_new_input();
            console.console_logic_module.invalidate_temp_input();
            console.console_logic_module.set_can_ctrl_c(false);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> ConsoleLogicModule::ctrl_w(
            yli::ontology::ConsoleCallbackEngine*,
            yli::ontology::ConsoleCallbackObject*,
            yli::ontology::GenericParentModule&,
            yli::ontology::Console& console)
    {
        if (console.console_logic_module.get_active_in_console() &&
                console.console_logic_module.get_can_ctrl_w() &&
                (console.console_logic_module.get_is_left_control_pressed() || console.console_logic_module.get_is_right_control_pressed()) &&
                !console.console_logic_module.get_is_left_alt_pressed() && !console.console_logic_module.get_is_right_alt_pressed() &&
                !console.console_logic_module.get_is_left_shift_pressed() && !console.console_logic_module.get_is_right_shift_pressed())
        {
            yli::console::TextInput* const active_input = console.console_logic_module.edit_input();

            if (active_input == nullptr)
            {
                std::cerr << "ERROR: `ConsoleLogicModule::ctrl_w`: `active_input` is `nullptr`!\n";
                return std::nullopt;
            }

            active_input->ctrl_w();
            console.console_logic_module.set_can_ctrl_w(false);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> ConsoleLogicModule::page_up(
            yli::ontology::ConsoleCallbackEngine*,
            yli::ontology::ConsoleCallbackObject*,
            yli::ontology::GenericParentModule&,
            yli::ontology::Console& console)
    {
        if (console.console_logic_module.get_active_in_console() && console.console_logic_module.get_can_page_up())
        {
            if (!console.console_logic_module.get_active_in_scrollback_buffer())
            {
                // We are not yet in scrollback buffer.

                if (!console.console_logic_module.enter_scrollback_buffer())
                {
                    std::cerr << "ERROR: `ConsoleLogicModule::page_up`: state transition to scrollback buffer failed!\n";
                }
                return std::nullopt;
            }
            else
            {
                // We are already in scrollback buffer.
                console.scrollback_buffer.page_up();
            }

            console.console_logic_module.set_can_page_up(false);
        }

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> ConsoleLogicModule::page_down(
            yli::ontology::ConsoleCallbackEngine*,
            yli::ontology::ConsoleCallbackObject*,
            yli::ontology::GenericParentModule&,
            yli::ontology::Console& console)
    {
        if (console.console_logic_module.get_active_in_console() && console.console_logic_module.get_can_page_down())
        {
            if (console.console_logic_module.get_active_in_scrollback_buffer())
            {
                if (!console.scrollback_buffer.page_down())
                {
                    // Page down caused exit from scrollback buffer.
                    console.console_logic_module.exit_scrollback_buffer();
                }
            }

            console.console_logic_module.set_can_page_down(false);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> ConsoleLogicModule::home(
            yli::ontology::ConsoleCallbackEngine*,
            yli::ontology::ConsoleCallbackObject*,
            yli::ontology::GenericParentModule&,
            yli::ontology::Console& console)
    {
        if (console.console_logic_module.get_active_in_console() && console.console_logic_module.get_can_home())
        {
            if (console.console_logic_module.get_active_in_scrollback_buffer())
            {
                console.scrollback_buffer.move_to_first();
            }
            else
            {
                console.console_logic_module.enter_scrollback_buffer();
                console.scrollback_buffer.move_to_first();
            }

            console.console_logic_module.set_can_home(false);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> ConsoleLogicModule::end(
            yli::ontology::ConsoleCallbackEngine*,
            yli::ontology::ConsoleCallbackObject*,
            yli::ontology::GenericParentModule&,
            yli::ontology::Console& console)
    {
        if (console.console_logic_module.get_active_in_console() && console.console_logic_module.get_can_end())
        {
            if (console.console_logic_module.get_active_in_scrollback_buffer())
            {
                console.console_logic_module.exit_scrollback_buffer();
            }

            console.console_logic_module.set_can_end(false);
        }
        return std::nullopt;
    }

    // Console command callbacks begin here.

    std::optional<yli::data::AnyValue> ConsoleLogicModule::clear(
            yli::ontology::Console& console)
    {
        console.console_logic_module.enter_new_input();
        console.new_input.clear();
        console.command_history.clear();
        console.scrollback_buffer.clear();

        const uint32_t clear_console_magic_number = yli::ontology::CallbackMagicNumber::CLEAR_CONSOLE;
        return yli::data::AnyValue(clear_console_magic_number);
    }

    // Public callbacks end here.

    // Callbacks end here.
}
