// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
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

#include "console.hpp"
#include "universe.hpp"
#include "console_command.hpp"
#include "code/ylikuutio/callback/callback_magic_numbers.hpp"
#include "code/ylikuutio/common/any_value.hpp"

// Include standard headers
#include <algorithm> // std::copy etc.
#include <iterator> // std::back_inserter
#include <list>     // std::list
#include <memory>   // std::make_shared, std::shared_ptr
#include <sstream>  // std::istringstream, std::ostringstream, std::stringstream
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string, std::getline
#include <vector>   // std::vector

namespace yli::callback
{
    class CallbackEngine;
    class CallbackObject;
    class CallbackParameter;
}

namespace yli::ontology
{
    class Console;

    // Public callbacks.

    // Action mode keyrelease callbacks begin here.

    // Action mode keypress callbacks begin here.

    std::shared_ptr<yli::common::AnyValue> Console::enter_console(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::common::AnyValue>)
    {
        if (universe == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Console* const console = universe->get_active_console();

        if (console == nullptr)
        {
            // We did not enter the console.
            return nullptr;
        }

        if (console->enter_console())
        {
            // Signal to caller that we have entered the console.
            uint32_t enter_console_magic_number = ENTER_CONSOLE_MAGIC_NUMBER;
            return std::make_shared<yli::common::AnyValue>(enter_console_magic_number);
        }

        // We did not enter the console.
        return nullptr;
    }

    // Console mode keyrelease callbacks begin here.

    std::shared_ptr<yli::common::AnyValue> Console::release_left_control_in_console(
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            yli::ontology::Console* console)
    {
        if (console->in_console)
        {
            console->is_left_control_pressed = false;
        }
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> Console::release_right_control_in_console(
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            yli::ontology::Console* console)
    {
        if (console->in_console)
        {
            console->is_right_control_pressed = false;
        }
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> Console::release_left_alt_in_console(
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            yli::ontology::Console* console)
    {
        if (console->in_console)
        {
            console->is_left_alt_pressed = false;
        }
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> Console::release_right_alt_in_console(
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            yli::ontology::Console* console)
    {
        if (console->in_console)
        {
            console->is_right_alt_pressed = false;
        }
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> Console::release_left_shift_in_console(
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            yli::ontology::Console* console)
    {
        if (console->in_console)
        {
            console->is_left_shift_pressed = false;
        }
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> Console::release_right_shift_in_console(
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            yli::ontology::Console* console)
    {
        if (console->in_console)
        {
            console->is_right_shift_pressed = false;
        }
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> Console::enable_move_to_previous_input(
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            yli::ontology::Console* console)
    {
        if (console->in_console)
        {
            console->can_move_to_previous_input = true;
        }
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> Console::enable_move_to_next_input(
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            yli::ontology::Console* console)
    {
        if (console->in_console)
        {
            console->can_move_to_next_input = true;
        }
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> Console::enable_backspace(
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            yli::ontology::Console* console)
    {
        if (console->in_console)
        {
            console->can_backspace = true;
        }
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> Console::enable_enter_key(
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            yli::ontology::Console* console)
    {
        if (console->in_console)
        {
            console->can_enter_key = true;
        }
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> Console::enable_ctrl_c(
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            yli::ontology::Console* console)
    {
        if (console->in_console)
        {
            console->can_ctrl_c = true;
        }
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> Console::enable_ctrl_w(
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            yli::ontology::Console* console)
    {
        if (console->in_console)
        {
            console->can_ctrl_w = true;
        }
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> Console::enable_page_up(
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            yli::ontology::Console* console)
    {
        if (console->in_console)
        {
            console->can_page_up = true;
        }
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> Console::enable_page_down(
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            yli::ontology::Console* console)
    {
        if (console->in_console)
        {
            console->can_page_down = true;
        }
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> Console::enable_home(
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            yli::ontology::Console* console)
    {
        if (console->in_console)
        {
            console->can_home = true;
        }
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> Console::enable_end(
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            yli::ontology::Console* console)
    {
        if (console->in_console)
        {
            console->can_end = true;
        }
        return nullptr;
    }

    // Console mode keypress callbacks begin here.

    std::shared_ptr<yli::common::AnyValue> Console::exit_console(
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            yli::ontology::Console* console)
    {
        if (console == nullptr)
        {
            // We did not exit the console.
            return nullptr;
        }

        if (console->in_console && console->exit_console())
        {
            // Signal to caller that we have exited the console.
            uint32_t exit_console_magic_number = EXIT_CONSOLE_MAGIC_NUMBER;
            return std::make_shared<yli::common::AnyValue>(exit_console_magic_number);
        }

        // We did not exit the console.
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> Console::press_left_control_in_console(
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            yli::ontology::Console* console)
    {
        if (console == nullptr)
        {
            return nullptr;
        }

        if (console->in_console)
        {
            console->is_left_control_pressed = true;
        }
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> Console::press_right_control_in_console(
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            yli::ontology::Console* console)
    {
        if (console == nullptr)
        {
            return nullptr;
        }

        if (console->in_console)
        {
            console->is_right_control_pressed = true;
        }
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> Console::press_left_alt_in_console(
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            yli::ontology::Console* console)
    {
        if (console == nullptr)
        {
            return nullptr;
        }

        if (console->in_console)
        {
            console->is_left_alt_pressed = true;
        }
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> Console::press_right_alt_in_console(
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            yli::ontology::Console* console)
    {
        if (console == nullptr)
        {
            return nullptr;
        }

        if (console->in_console)
        {
            console->is_right_alt_pressed = true;
        }
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> Console::press_left_shift_in_console(
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            yli::ontology::Console* console)
    {
        if (console == nullptr)
        {
            return nullptr;
        }

        if (console->in_console)
        {
            console->is_left_shift_pressed = true;
        }
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> Console::press_right_shift_in_console(
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            yli::ontology::Console* console)
    {
        if (console == nullptr)
        {
            return nullptr;
        }

        if (console->in_console)
        {
            console->is_right_shift_pressed = true;
        }
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> Console::move_to_previous_input(
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            yli::ontology::Console* console)
    {
        if (console == nullptr)
        {
            return nullptr;
        }

        if (console->in_console && console->can_move_to_previous_input)
        {
            if (!console->in_historical_input && console->command_history.size() > 0)
            {
                // OK, we moved from the new input to the last historical input.
                console->in_historical_input = true;
                console->historical_input_i = console->command_history.size() - 1;

                // Copy the new input into temp input.
                console->temp_input.clear();
                std::copy(console->current_input.begin(), console->current_input.end(), std::back_inserter(console->temp_input));

                // Copy the historical input into current input.
                console->current_input.clear();
                console->copy_historical_input_into_current_input();

                console->move_cursor_to_end_of_line();
                console->can_move_to_previous_input = false;
            }
            else if (console->in_historical_input && console->historical_input_i > 0)
            {
                // OK, we moved to the previous historical input.
                console->historical_input_i--;

                // Copy the historical input into current input.
                console->copy_historical_input_into_current_input();

                console->move_cursor_to_end_of_line();
                console->can_move_to_previous_input = false;
            }
        }
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> Console::move_to_next_input(
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            yli::ontology::Console* console)
    {
        if (console == nullptr)
        {
            return nullptr;
        }

        if (console->in_console && console->can_move_to_next_input)
        {
            if (console->in_historical_input && console->historical_input_i == console->command_history.size() - 1)
            {
                // OK, we moved from the last historical input to the new input.
                console->in_historical_input = false;

                // Copy temp input into current input.
                console->current_input.clear();
                std::copy(console->temp_input.begin(), console->temp_input.end(), std::back_inserter(console->current_input));

                console->move_cursor_to_end_of_line();
                console->can_move_to_next_input = false;
            }
            else if (console->in_historical_input && console->historical_input_i < console->command_history.size() - 1)
            {
                // OK, we moved to the next historical input.
                console->historical_input_i++;

                // Copy the historical input into current input.
                console->copy_historical_input_into_current_input();

                console->move_cursor_to_end_of_line();
                console->can_move_to_next_input = false;
            }
        }
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> Console::backspace(
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            yli::ontology::Console* console)
    {
        if (console == nullptr)
        {
            return nullptr;
        }

        if (console->in_console &&
                console->can_backspace &&
                console->cursor_it != console->current_input.begin())
        {
            console->cursor_it = console->current_input.erase(--console->cursor_it);
            console->cursor_index--;
            console->can_backspace = false;
        }
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> Console::enter_key(
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            yli::ontology::Console* console)
    {
        if (console == nullptr || !console->in_console || !console->can_enter_key)
        {
            return nullptr;
        }

        std::shared_ptr<yli::common::AnyValue> any_value = nullptr;

        // Copy current input into a `std::string`.
        std::string input_string(console->current_input.begin(), console->current_input.end());

        // Copy current input into the command history.
        console->command_history.push_back(console->current_input);

        // Prefix current input with the prompt, for saving into `console_history`.
        std::list<char>::iterator it = console->current_input.begin();

        for (const char& my_char : console->prompt)
        {
            console->current_input.insert(it, my_char);
        }

        std::list<char> current_input_char_list;

        // Split into lines, push_back each line into `console_history` separately.
        for (const char& my_char : console->current_input)
        {
            current_input_char_list.push_back(my_char);

            if (current_input_char_list.size () >= console->n_columns)
            {
                console->console_history.push_back(current_input_char_list);
                current_input_char_list.clear();
            }
        }

        if (current_input_char_list.size() > 0)
        {
            console->console_history.push_back(current_input_char_list);
        }

        bool is_command = false;
        std::istringstream input_stringstream(input_string);
        std::vector<std::string> parameter_vector;
        std::string command;
        std::string token;

        // The reader begins here.

        while (std::getline(input_stringstream, token, ' '))
        {
            if (token.empty())
            {
                continue;
            }

            if (!is_command)
            {
                // First non-empty token is the command.
                command = token;
                is_command = true;
            }
            else
            {
                // The rest non-empty tokens are the parameters.
                parameter_vector.push_back(token);
            }
        }

        // The reader ends here.

        console->current_input.clear();

        if (is_command)
        {
            // Call the corresponding console command callback, if there is one.
            yli::ontology::Universe* universe = console->get_universe();

            if (universe != nullptr)
            {
                yli::ontology::Entity* const console_command_entity = universe->get_entity(command);

                if (console_command_entity != nullptr && console_command_entity->get_parent() == console)
                {
                    yli::ontology::ConsoleCommand* const console_command =
                        dynamic_cast<yli::ontology::ConsoleCommand*>(console_command_entity);

                    if (console_command != nullptr)
                    {
                        any_value = console_command->execute(parameter_vector);
                    }
                }
            }
        }

        console->in_historical_input = false;
        console->cursor_it = console->current_input.begin();
        console->cursor_index = 0;
        console->can_enter_key = false;

        return any_value;
    }

    std::shared_ptr<yli::common::AnyValue> Console::ctrl_c(
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            yli::ontology::Console* console)
    {
        if (console == nullptr)
        {
            return nullptr;
        }

        if (console->in_console &&
                console->can_ctrl_c &&
                (console->is_left_control_pressed || console->is_right_control_pressed) &&
                !console->is_left_alt_pressed && !console->is_right_alt_pressed &&
                !console->is_left_shift_pressed && !console->is_right_shift_pressed)
        {
            console->current_input.clear();
            console->in_historical_input = false;
            console->cursor_it = console->current_input.begin();
            console->cursor_index = 0;
            console->can_ctrl_c = false;
        }
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> Console::ctrl_w(
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            yli::ontology::Console* console)
    {
        if (console == nullptr)
        {
            return nullptr;
        }

        if (console->in_console &&
                console->can_ctrl_w &&
                (console->is_left_control_pressed || console->is_right_control_pressed) &&
                !console->is_left_alt_pressed && !console->is_right_alt_pressed &&
                !console->is_left_shift_pressed && !console->is_right_shift_pressed)
        {
            console->in_historical_input = false;

            // First, remove all spaces until a non-space is encountered.
            while (console->cursor_it != console->current_input.begin())
            {
                if (*--console->cursor_it == ' ')
                {
                    console->cursor_it++;
                    break;
                }

                console->cursor_it = console->current_input.erase(console->cursor_it);
                console->cursor_index--;
            }

            // Then, remove all non-spaces until a space is encountered.
            while (console->cursor_it != console->current_input.begin())
            {
                if (*--console->cursor_it != ' ')
                {
                    console->cursor_it++;
                    break;
                }

                console->cursor_it = console->current_input.erase(console->cursor_it);
                console->cursor_index--;
            }

            console->can_ctrl_w = false;
        }
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> Console::page_up(
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            yli::ontology::Console* console)
    {
        if (console == nullptr)
        {
            return nullptr;
        }

        if (console->in_console && console->can_page_up)
        {
            if (console->in_history)
            {
                console->history_line_i = console->history_line_i > console->n_rows ? console->history_line_i - console->n_rows : 0;
            }
            else
            {
                console->in_history = true;
                console->history_line_i = console->console_history.size() > 2 * console->n_rows ? console->console_history.size() > 2 * console->n_rows : 0;
            }

            if (console->history_line_i + console->n_rows >= console->console_history.size())
            {
                console->in_history = false;
            }

            console->can_page_up = false;
        }

        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> Console::page_down(
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            yli::ontology::Console* console)
    {
        if (console == nullptr)
        {
            return nullptr;
        }

        if (console->in_console && console->can_page_down)
        {
            if (console->in_history)
            {
                console->history_line_i += console->n_rows;

                if (console->history_line_i + console->n_rows >= console->console_history.size())
                {
                    console->in_history = false;
                }
            }

            console->can_page_down = false;
        }
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> Console::home(
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            yli::ontology::Console* console)
    {
        if (console == nullptr)
        {
            return nullptr;
        }

        if (console->in_console && console->can_home)
        {
            console->history_line_i = 0;

            if (console->history_line_i + console->n_rows >= console->console_history.size())
            {
                console->in_history = false;
            }
            else
            {
                console->in_history = true;
            }

            console->can_home = false;
        }
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> Console::end(
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            yli::ontology::Console* console)
    {
        if (console == nullptr)
        {
            return nullptr;
        }

        if (console->in_console && console->can_end)
        {
            console->in_history = false;
            console->can_home = false;
        }
        return nullptr;
    }

    // Public callbacks end here.

    // Callbacks end here.
}
