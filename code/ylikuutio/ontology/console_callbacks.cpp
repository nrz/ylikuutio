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

#include "console.hpp"
#include "universe.hpp"
#include "lisp_function.hpp"
#include "callback_magic_numbers.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/lisp/parser.hpp"
#include "code/ylikuutio/lisp/executor.hpp"

// Include standard headers
#include <algorithm> // std::copy etc.
#include <cstddef>   // std::size_t
#include <iterator>  // std::back_inserter
#include <list>      // std::list
#include <optional>  // std::optional
#include <stdint.h>  // uint32_t etc.
#include <string>    // std::string
#include <vector>    // std::vector

namespace yli::ontology
{
    class GenericParentModule;
    class CallbackEngine;
    class CallbackObject;
    class CallbackParameter;
    class Console;
    class ConsoleCallbackEngine;
    class ConsoleCallbackObject;

    // Public callbacks.

    // Action mode keyrelease callbacks begin here.

    // Action mode keypress callbacks begin here.

    std::optional<yli::data::AnyValue> Console::enter_console(
            Universe& universe,
            CallbackEngine*,
            CallbackObject*,
            GenericParentModule&,
            const yli::data::AnyValue&)
    {
        Console* const console = universe.get_active_console();

        if (console == nullptr)
        {
            // We did not enter the console.
            return std::nullopt;
        }

        if (console->enter_console())
        {
            // Signal to caller that we have entered the console.
            uint32_t enter_console_magic_number = CallbackMagicNumber::ENTER_CONSOLE;
            return yli::data::AnyValue(enter_console_magic_number);
        }

        // We did not enter the console.
        return std::nullopt;
    }

    // Console mode keyrelease callbacks begin here.

    std::optional<yli::data::AnyValue> Console::release_left_control_in_console(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.in_console)
        {
            console.is_left_control_pressed = false;
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::release_right_control_in_console(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.in_console)
        {
            console.is_right_control_pressed = false;
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::release_left_alt_in_console(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.in_console)
        {
            console.is_left_alt_pressed = false;
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::release_right_alt_in_console(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.in_console)
        {
            console.is_right_alt_pressed = false;
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::release_left_shift_in_console(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.in_console)
        {
            console.is_left_shift_pressed = false;
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::release_right_shift_in_console(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.in_console)
        {
            console.is_right_shift_pressed = false;
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::enable_move_to_previous_input(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.in_console)
        {
            console.can_move_to_previous_input = true;
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::enable_move_to_next_input(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.in_console)
        {
            console.can_move_to_next_input = true;
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::enable_backspace(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.in_console)
        {
            console.can_backspace = true;
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::enable_tab(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.in_console)
        {
            console.can_tab = true;
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::enable_enter_key(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.in_console)
        {
            console.can_enter_key = true;
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::enable_ctrl_c(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.in_console)
        {
            console.can_ctrl_c = true;
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::enable_ctrl_w(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.in_console)
        {
            console.can_ctrl_w = true;
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::enable_page_up(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.in_console)
        {
            console.can_page_up = true;
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::enable_page_down(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.in_console)
        {
            console.can_page_down = true;
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::enable_home(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.in_console)
        {
            console.can_home = true;
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::enable_end(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.in_console)
        {
            console.can_end = true;
        }
        return std::nullopt;
    }

    // Console mode keypress callbacks begin here.

    std::optional<yli::data::AnyValue> Console::exit_console(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.in_console && console.exit_console())
        {
            // Signal to caller that we have exited the console.
            uint32_t exit_console_magic_number = CallbackMagicNumber::EXIT_CONSOLE;
            return yli::data::AnyValue(exit_console_magic_number);
        }

        // We did not exit the console.
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::press_left_control_in_console(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.in_console)
        {
            console.is_left_control_pressed = true;
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::press_right_control_in_console(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.in_console)
        {
            console.is_right_control_pressed = true;
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::press_left_alt_in_console(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.in_console)
        {
            console.is_left_alt_pressed = true;
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::press_right_alt_in_console(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.in_console)
        {
            console.is_right_alt_pressed = true;
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::press_left_shift_in_console(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.in_console)
        {
            console.is_left_shift_pressed = true;
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::press_right_shift_in_console(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.in_console)
        {
            console.is_right_shift_pressed = true;
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::move_to_previous_input(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.in_console && console.can_move_to_previous_input)
        {
            if (!console.in_historical_input && !console.command_history.empty())
            {
                // OK, we moved from the new input to the last historical input.
                console.in_historical_input = true;
                console.historical_input_i = console.command_history.size() - 1;

                // Copy the new input into temp input.
                console.temp_input.clear();
                std::copy(console.current_input.begin(), console.current_input.end(), std::back_inserter(console.temp_input));

                // Copy the historical input into current input.
                console.current_input.clear();
                console.copy_historical_input_into_current_input();

                console.move_cursor_to_end_of_line();
                console.can_move_to_previous_input = false;
            }
            else if (console.in_historical_input && console.historical_input_i > 0)
            {
                // OK, we moved to the previous historical input.
                console.historical_input_i--;

                // Copy the historical input into current input.
                console.copy_historical_input_into_current_input();

                console.move_cursor_to_end_of_line();
                console.can_move_to_previous_input = false;
            }
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::move_to_next_input(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.in_console && console.can_move_to_next_input && !console.command_history.empty())
        {
            if (console.in_historical_input && console.historical_input_i == console.command_history.size() - 1)
            {
                // OK, we moved from the last historical input to the new input.
                console.in_historical_input = false;

                // Copy temp input into current input.
                console.current_input.clear();
                std::copy(console.temp_input.begin(), console.temp_input.end(), std::back_inserter(console.current_input));

                console.move_cursor_to_end_of_line();
                console.can_move_to_next_input = false;
            }
            else if (console.in_historical_input && console.historical_input_i < console.command_history.size() - 1)
            {
                // OK, we moved to the next historical input.
                console.historical_input_i++;

                // Copy the historical input into current input.
                console.copy_historical_input_into_current_input();

                console.move_cursor_to_end_of_line();
                console.can_move_to_next_input = false;
            }
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::backspace(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.in_console &&
                console.can_backspace &&
                console.cursor_it != console.current_input.begin())
        {
            console.cursor_it = console.current_input.erase(--console.cursor_it);
            console.cursor_index--;
            console.can_backspace = false;
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::tab(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        Universe& universe = console.get_universe();

        if (console.in_console && console.can_tab)
        {
            // Copy current input into a `std::string`.
            std::string input_string(console.current_input.begin(), console.current_input.end());

            std::vector<std::string> parameter_vector;
            std::string command;

            yli::lisp::parse(input_string, command, parameter_vector);

            if (command.empty() ||
                    (parameter_vector.empty() && input_string.back() != ' '))
            {
                // If `input_string` is empty, then complete the command.
                // Also if there are no parameters and `input_string` does not end with a space, then complete the command.

                console.print_completions(universe.registry, command);

                const std::string completion = universe.complete(command);
                console.current_input.clear();
                std::copy(completion.begin(), completion.end(), std::back_inserter(console.current_input));
            }
            else if (parameter_vector.empty())
            {
                // If `input_string` has no parameters,
                // then complete the parameter using the empty string.

                // If `input_string` is empty, then complete the parameter.

                console.print_completions(universe.registry, "");

                const std::string completion = universe.complete("");

                if (!completion.empty())
                {
                    std::copy(completion.begin(), completion.end(), std::back_inserter(console.current_input));
                }
            }
            else if (input_string.back() != ' ')
            {
                // If `input_string` does not end with a space,
                // then complete the current parameter.

                console.print_completions(universe.registry, parameter_vector.back());

                const std::string completion = universe.complete(parameter_vector.back());
                console.current_input.clear();
                std::copy(command.begin(), command.end(), std::back_inserter(console.current_input));
                console.current_input.emplace_back(' ');

                // Copy the old parameters except the last.

                for (std::size_t i = 0; i + 1 < parameter_vector.size(); i++)
                {
                    std::copy(parameter_vector.at(i).begin(), parameter_vector.at(i).end(), std::back_inserter(console.current_input));
                    console.move_cursor_to_end_of_line();
                    console.current_input.emplace_back(' ');
                }

                // Copy the completed parameter.
                std::copy(completion.begin(), completion.end(), std::back_inserter(console.current_input));
            }
            else
            {
                // Complete the next parameter.

                const std::string completion = universe.complete("");

                if (!completion.empty())
                {
                    std::copy(completion.begin(), completion.end(), std::back_inserter(console.current_input));
                }
            }

            console.move_cursor_to_end_of_line();

            console.can_tab = false;
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::enter_key(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (!console.in_console || !console.can_enter_key)
        {
            return std::nullopt;
        }

        // Copy current input into a `std::string`.
        const std::string input_string(console.current_input.begin(), console.current_input.end());

        // Copy current input into the command history.
        console.command_history.emplace_back(console.current_input);

        // Prefix current input with the prompt, for saving into `console_history`.
        std::list<char>::iterator it = console.current_input.begin();

        for (const char& my_char : console.prompt)
        {
            console.current_input.insert(it, my_char);
        }

        std::list<char> current_input_char_list;

        // Split into lines, emplace_back each line into `console_history` separately.
        for (const char& my_char : console.current_input)
        {
            current_input_char_list.emplace_back(my_char);

            if (current_input_char_list.size () >= console.n_columns)
            {
                console.console_history.emplace_back(current_input_char_list);
                current_input_char_list.clear();
            }
        }

        if (current_input_char_list.size() > 0)
        {
            console.console_history.emplace_back(current_input_char_list);
        }

        std::vector<std::string> parameter_vector;
        std::string command;

        console.current_input.clear();

        if (yli::lisp::parse(input_string, command, parameter_vector))
        {
            std::optional<yli::data::AnyValue> any_value = yli::lisp::execute(console, command, parameter_vector);
            console.in_historical_input = false;
            console.cursor_it = console.current_input.begin();
            console.cursor_index = 0;
            console.can_enter_key = false;
            return any_value;
        }

        console.in_historical_input = false;
        console.cursor_it = console.current_input.begin();
        console.cursor_index = 0;
        console.can_enter_key = false;

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::ctrl_c(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.in_console &&
                console.can_ctrl_c &&
                (console.is_left_control_pressed || console.is_right_control_pressed) &&
                !console.is_left_alt_pressed && !console.is_right_alt_pressed &&
                !console.is_left_shift_pressed && !console.is_right_shift_pressed)
        {
            console.current_input.clear();
            console.in_historical_input = false;
            console.cursor_it = console.current_input.begin();
            console.cursor_index = 0;
            console.can_ctrl_c = false;
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::ctrl_w(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.in_console &&
                console.can_ctrl_w &&
                (console.is_left_control_pressed || console.is_right_control_pressed) &&
                !console.is_left_alt_pressed && !console.is_right_alt_pressed &&
                !console.is_left_shift_pressed && !console.is_right_shift_pressed)
        {
            console.in_historical_input = false;

            // First, remove all spaces until a non-space is encountered.
            while (console.cursor_it != console.current_input.begin())
            {
                if (*--console.cursor_it == ' ')
                {
                    ++console.cursor_it;
                    break;
                }

                console.cursor_it = console.current_input.erase(console.cursor_it);
                console.cursor_index--;
            }

            // Then, remove all non-spaces until a space is encountered.
            while (console.cursor_it != console.current_input.begin())
            {
                if (*--console.cursor_it != ' ')
                {
                    ++console.cursor_it;
                    break;
                }

                console.cursor_it = console.current_input.erase(console.cursor_it);
                console.cursor_index--;
            }

            console.can_ctrl_w = false;
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::page_up(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.in_console && console.can_page_up)
        {
            if (console.in_history)
            {
                console.history_line_i = console.history_line_i > console.n_rows ? console.history_line_i - console.n_rows : 0;
            }
            else
            {
                console.in_history = true;
                console.history_line_i = console.console_history.size() > 2 * console.n_rows ? console.console_history.size() > 2 * console.n_rows : 0;
            }

            if (console.history_line_i + console.n_rows >= console.console_history.size())
            {
                console.in_history = false;
            }

            console.can_page_up = false;
        }

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::page_down(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.in_console && console.can_page_down)
        {
            if (console.in_history)
            {
                console.history_line_i += console.n_rows;

                if (console.history_line_i + console.n_rows >= console.console_history.size())
                {
                    console.in_history = false;
                }
            }

            console.can_page_down = false;
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::home(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.in_console && console.can_home)
        {
            console.history_line_i = 0;

            if (console.history_line_i + console.n_rows >= console.console_history.size())
            {
                console.in_history = false;
            }
            else
            {
                console.in_history = true;
            }

            console.can_home = false;
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::end(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.in_console && console.can_end)
        {
            console.in_history = false;
            console.can_home = false;
        }
        return std::nullopt;
    }

    // Public callbacks end here.

    // Callbacks end here.
}
