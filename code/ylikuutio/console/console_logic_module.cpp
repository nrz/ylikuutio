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

// Include standard headers
#include <iostream> // std::cerr
#include <optional> // std::optional

namespace yli::console
{
    class TextInput;
    class TextInputHistory;

    // console states:
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

    // State transition functions.

    std::optional<ConsoleState> ConsoleLogicModule::activate()
    {
        if (this->new_input != nullptr)
        {
            return this->switch_to_state(ConsoleState(this->state | yli::console::active));
        }

        return std::nullopt; // Transition failed.
    }

    std::optional<ConsoleState> ConsoleLogicModule::deactivate()
    {
        return this->switch_to_state(ConsoleState(this->state & (~yli::console::active)));
    }

    std::optional<ConsoleState> ConsoleLogicModule::enter_new_input()
    {
        if (this->new_input != nullptr)
        {
            return this->switch_to_state(ConsoleState::ACTIVE_IN_NEW_INPUT);
        }

        return std::nullopt; // Transition failed.
    }

    std::optional<ConsoleState> ConsoleLogicModule::enter_historical_input()
    {
        return this->switch_to_state(ConsoleState::ACTIVE_IN_HISTORICAL_INPUT);
    }

    std::optional<ConsoleState> ConsoleLogicModule::enter_temp_input()
    {
        return this->switch_to_state(ConsoleState::ACTIVE_IN_TEMP_INPUT);
    }

    std::optional<ConsoleState> ConsoleLogicModule::enter_scrollback_buffer()
    {
        return this->switch_to_state(ConsoleState(this->state | yli::console::in_scrollback_buffer));
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

    // Module registration functions.

    void ConsoleLogicModule::register_new_input(TextInput* const new_input)
    {
        this->new_input = new_input;
    }

    void ConsoleLogicModule::register_temp_input(TextInput* const temp_input)
    {
        this->temp_input = temp_input;
    }

    void ConsoleLogicModule::register_text_input_history(TextInputHistory* const text_input_history)
    {
        this->text_input_history = text_input_history;
    }

    yli::console::ConsoleState ConsoleLogicModule::get() const
    {
        return this->state;
    }

    // Module inquiry functions.

    TextInput* ConsoleLogicModule::get_new_input() const

    {
        return this->new_input;
    }

    TextInput* ConsoleLogicModule::get_temp_input() const
    {
        return this->temp_input;
    }

    TextInputHistory* ConsoleLogicModule::get_text_input_history() const
    {
        return this->text_input_history;
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

    std::optional<ConsoleState> ConsoleLogicModule::switch_to_state(const ConsoleState new_state)
    {
        if (!((this->state ^ new_state) & (~yli::console::active)))
        {
            // If the old state and new state differ possibly only with regards to activation state,
            // then the transition is valid.
            this->state = new_state;
            return new_state;
        }
        else if (!((this->state ^ new_state) & (~yli::console::in_scrollback_buffer)) && (this->state & yli::console::active))
        {
            // If the old state and new state differ possibly only with regards to in-scrollback-buffer state,
            // and the current state in active, then the transition is valid.
            this->state = new_state;
            return new_state;
        }
        else if (const uint32_t any_input = in_new_input | in_historical_input | in_temp_input;
                !((this->state ^ new_state) & (~any_input)) && (this->state & yli::console::active))
        {
            // If the old state and new state differ possibly only with regards to which-buffer state,
            // and the current state in active, then the transition is valid.
            this->state = new_state;
            return new_state;
        }

        std::cerr << "ERROR: `ConsoleLogicModule::switch_to_state`: state transition failed!\n";
        return std::nullopt; // Transition failed.
    }
}
