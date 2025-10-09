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
#include "code/ylikuutio/console/text_line.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/lisp/parser.hpp"
#include "code/ylikuutio/lisp/executor.hpp"

// Include standard headers
#include <cstddef>   // std::size_t
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
        if (console.console_logic_module.get_active_in_console())
        {
            console.console_logic_module.set_is_left_control_pressed(false);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::release_right_control_in_console(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.console_logic_module.get_active_in_console())
        {
            console.console_logic_module.set_is_right_control_pressed(false);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::release_left_alt_in_console(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.console_logic_module.get_active_in_console())
        {
            console.console_logic_module.set_is_left_alt_pressed(false);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::release_right_alt_in_console(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.console_logic_module.get_active_in_console())
        {
            console.console_logic_module.set_is_right_alt_pressed(false);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::release_left_shift_in_console(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.console_logic_module.get_active_in_console())
        {
            console.console_logic_module.set_is_left_shift_pressed(false);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::release_right_shift_in_console(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.console_logic_module.get_active_in_console())
        {
            console.console_logic_module.set_is_right_shift_pressed(false);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::enable_move_to_previous_input(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.console_logic_module.get_active_in_console())
        {
            console.console_logic_module.set_can_move_to_previous_input(true);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::enable_move_to_next_input(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.console_logic_module.get_active_in_console())
        {
            console.console_logic_module.set_can_move_to_next_input(true);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::enable_backspace(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.console_logic_module.get_active_in_console())
        {
            console.console_logic_module.set_can_backspace(true);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::enable_tab(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.console_logic_module.get_active_in_console())
        {
            console.console_logic_module.set_can_tab(true);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::enable_enter_key(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.console_logic_module.get_active_in_console())
        {
            console.console_logic_module.set_can_enter_key(true);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::enable_ctrl_c(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.console_logic_module.get_active_in_console())
        {
            console.console_logic_module.set_can_ctrl_c(true);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::enable_ctrl_w(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.console_logic_module.get_active_in_console())
        {
            console.console_logic_module.set_can_ctrl_w(true);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::enable_page_up(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.console_logic_module.get_active_in_console())
        {
            console.console_logic_module.set_can_page_up(true);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::enable_page_down(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.console_logic_module.get_active_in_console())
        {
            console.console_logic_module.set_can_page_down(true);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::enable_home(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.console_logic_module.get_active_in_console())
        {
            console.console_logic_module.set_can_home(true);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::enable_end(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.console_logic_module.get_active_in_console())
        {
            console.console_logic_module.set_can_end(true);
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
        if (console.console_logic_module.get_active_in_console() && console.exit_console())
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
        if (console.console_logic_module.get_active_in_console())
        {
            console.console_logic_module.set_is_left_control_pressed(true);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::press_right_control_in_console(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.console_logic_module.get_active_in_console())
        {
            console.console_logic_module.set_is_right_control_pressed(true);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::press_left_alt_in_console(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.console_logic_module.get_active_in_console())
        {
            console.console_logic_module.set_is_left_alt_pressed(true);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::press_right_alt_in_console(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.console_logic_module.get_active_in_console())
        {
            console.console_logic_module.set_is_right_alt_pressed(true);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::press_left_shift_in_console(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.console_logic_module.get_active_in_console())
        {
            console.console_logic_module.set_is_left_shift_pressed(true);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::press_right_shift_in_console(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.console_logic_module.get_active_in_console())
        {
            console.console_logic_module.set_is_right_shift_pressed(true);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::move_to_previous_input(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.console_logic_module.get_active_in_console() && console.console_logic_module.get_can_move_to_previous_input())
        {
            const std::size_t history_index = console.command_history.get_history_index();

            if (!console.console_logic_module.get_active_in_historical_input() && !console.command_history.empty())
            {
                // OK, we moved from the new input to the last historical input.
                console.console_logic_module.enter_historical_input();
                console.console_logic_module.set_can_move_to_previous_input(false);
            }
            else if (console.console_logic_module.get_active_in_historical_input() && history_index > 0)
            {
                // OK, we moved to the previous historical input.
                console.command_history.move_to_previous();
                console.console_logic_module.set_can_move_to_previous_input(false);
            }
            else if (console.console_logic_module.get_active_in_temp_input() && history_index > 0)
            {
                // OK, we moved to the previous historical input from temp input.
                console.console_logic_module.enter_historical_input();
                console.command_history.move_to_nth(history_index - 1);

                console.move_cursor_to_end_of_line();
                console.console_logic_module.set_can_move_to_previous_input(false);
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
        if (console.console_logic_module.get_active_in_console() && console.console_logic_module.get_can_move_to_next_input() && !console.command_history.empty())
        {
            const std::size_t history_index = console.command_history.get_history_index();

            if (console.console_logic_module.get_active_in_historical_input() && history_index == console.command_history.size() - 1)
            {
                // OK, we moved from the last historical input to the new input.
                console.console_logic_module.enter_new_input();

                console.move_cursor_to_end_of_line();
                console.console_logic_module.set_can_move_to_next_input(false);
            }
            else if (console.console_logic_module.get_active_in_temp_input() && history_index == console.command_history.size() - 1)
            {
                // OK, we moved from the edited last historical input (temp input) to the new input.
                console.console_logic_module.enter_new_input();

                console.move_cursor_to_end_of_line();
                console.console_logic_module.set_can_move_to_next_input(false);
            }
            else if (console.console_logic_module.get_active_in_historical_input() && history_index < console.command_history.size() - 1)
            {
                // OK, we moved to the next historical input.
                console.command_history.move_to_next();

                console.move_cursor_to_end_of_line();
                console.console_logic_module.set_can_move_to_next_input(false);
            }
            else if (console.console_logic_module.get_active_in_temp_input() && history_index < console.command_history.size() - 1)
            {
                // OK, we moved to the next historical input from temp input.
                console.console_logic_module.enter_historical_input(); // Entering historical input causes history index reset to last.
                console.command_history.move_to_nth(history_index + 1);

                console.move_cursor_to_end_of_line();
                console.console_logic_module.set_can_move_to_next_input(false);
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

    std::optional<yli::data::AnyValue> Console::tab(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        Universe& universe = console.get_universe();

        if (console.console_logic_module.get_active_in_console() && console.console_logic_module.get_can_tab())
        {
            yli::console::TextInput* const active_input = console.console_logic_module.edit_input();

            if (active_input == nullptr)
            {
                return std::nullopt;
            }

            // Copy active input into a `std::string`.
            std::string input_string(active_input->data());

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
                active_input->clear();
                active_input->add_characters(completion);
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
                    active_input->add_characters(completion);
                }
            }
            else if (input_string.back() != ' ')
            {
                // If `input_string` does not end with a space,
                // then complete the current parameter.

                console.print_completions(universe.registry, parameter_vector.back());

                const std::string completion = universe.complete(parameter_vector.back());
                active_input->clear();
                active_input->add_characters(command);
                active_input->add_character(' ');

                // Copy the old parameters except the last.

                for (std::size_t i = 0; i + 1 < parameter_vector.size(); i++)
                {
                    active_input->add_characters(parameter_vector.at(i));
                    console.move_cursor_to_end_of_line();
                    active_input->add_character(' ');
                }

                // Copy the completed parameter.
                active_input->add_characters(completion);
            }
            else
            {
                // Complete the next parameter.

                const std::string completion = universe.complete("");

                if (!completion.empty())
                {
                    // Copy the completed parameter.
                    active_input->add_characters(completion);
                }
            }

            console.move_cursor_to_end_of_line();

            console.console_logic_module.set_can_tab(false);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::enter_key(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (!console.console_logic_module.get_active_in_console() || !console.console_logic_module.get_can_enter_key())
        {
            return std::nullopt;
        }

        yli::console::TextInput* const active_input = console.console_logic_module.edit_input();

        if (active_input == nullptr)
        {
            std::cerr << "ERROR: `Console::enter_key`: `active_input` is `nullptr`!\n";
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
            console.console_logic_module.set_can_enter_key(false);
            return any_value;
        }

        console.console_logic_module.enter_new_input();
        console.console_logic_module.set_can_enter_key(false);
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::ctrl_c(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.console_logic_module.get_active_in_console() &&
                console.console_logic_module.get_can_ctrl_c() &&
                (console.console_logic_module.get_is_left_control_pressed() || console.console_logic_module.get_is_right_control_pressed()) &&
                !console.console_logic_module.get_is_left_alt_pressed() && !console.console_logic_module.get_is_right_alt_pressed() &&
                !console.console_logic_module.get_is_left_shift_pressed() && !console.console_logic_module.get_is_right_shift_pressed())
        {
            console.new_input.clear();
            console.console_logic_module.enter_new_input();
            console.console_logic_module.set_can_ctrl_c(false);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::ctrl_w(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
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
                std::cerr << "ERROR: `Console::ctrl_w`: `active_input` is `nullptr`!\n";
                return std::nullopt;
            }

            active_input->ctrl_w();
            console.console_logic_module.set_can_ctrl_w(false);
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Console::page_up(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
    {
        if (console.console_logic_module.get_active_in_console() && console.console_logic_module.get_can_page_up())
        {
            if (!console.console_logic_module.get_active_in_scrollback_buffer())
            {
                // We are not yet in scrollback buffer.

                if (!console.console_logic_module.enter_scrollback_buffer())
                {
                    std::cerr << "ERROR: `Console::page_up`: state transition to scrollback buffer failed!\n";
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

    std::optional<yli::data::AnyValue> Console::page_down(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
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

    std::optional<yli::data::AnyValue> Console::home(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
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

    std::optional<yli::data::AnyValue> Console::end(
            ConsoleCallbackEngine*,
            ConsoleCallbackObject*,
            GenericParentModule&,
            Console& console)
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

    // Public callbacks end here.

    // Callbacks end here.
}
