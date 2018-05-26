#include "console.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/callback_system/callback_magic_numbers.hpp"

// Include standard headers
#include <iterator> // std::back_inserter
#include <list>     // std::list
#include <memory>   // std::make_shared, std::shared_ptr
#include <sstream>  // std::istringstream, std::ostringstream, std::stringstream
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace callback_system
{
    class CallbackEngine;
    class CallbackObject;
    class CallbackParameter;
}

namespace console
{
    class Console;

    // Public callbacks.

    // Action mode keyrelease callbacks begin here.

    std::shared_ptr<datatypes::AnyValue> Console::enable_enter_console(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>&,
            console::Console* console)
    {
        if (!console->in_console)
        {
            console->can_enter_console = true;
        }
        return nullptr;
    }

    // Action mode keypress callbacks begin here.

    std::shared_ptr<datatypes::AnyValue> Console::enter_console(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>&,
            console::Console* console)
    {
        if (!console->in_console &&
                console->can_enter_console &&
                console->my_keypress_callback_engine_vector_pointer != nullptr &&
                console->my_keyrelease_callback_engine_vector_pointer != nullptr &&
                console->current_keypress_callback_engine_vector_pointer_pointer != nullptr &&
                console->current_keyrelease_callback_engine_vector_pointer_pointer != nullptr)
        {
            // Store previous keypress callback engine vector pointer.
            console->previous_keypress_callback_engine_vector_pointer =
                *console->current_keypress_callback_engine_vector_pointer_pointer;

            // Set new keypress callback engine vector pointer.
            *console->current_keypress_callback_engine_vector_pointer_pointer =
                console->my_keypress_callback_engine_vector_pointer;

            // Store previous keyrelease callback engine vector pointer.
            console->previous_keyrelease_callback_engine_vector_pointer =
                *console->current_keyrelease_callback_engine_vector_pointer_pointer;

            // Set new keyrelease callback engine vector pointer.
            *console->current_keyrelease_callback_engine_vector_pointer_pointer =
                console->my_keyrelease_callback_engine_vector_pointer;

            glfwSetCharModsCallback(console->universe->get_window(), Console::charmods_callback);

            // Mark that we're in console.
            console->in_console = true;
            console->in_historical_input = false;

            // Usually key release is required to enable enter console.
            console->can_exit_console = false;
            console->can_enter_console = false;

            // Signal to caller that we have entered the console.
            uint32_t enter_console_magic_number = ENTER_CONSOLE_MAGIC_NUMBER;
            std::shared_ptr<datatypes::AnyValue> any_value_magic_number = std::make_shared<datatypes::AnyValue>(enter_console_magic_number);
            return any_value_magic_number;
        }

        // We did not enter the console.
        return nullptr;
    }

    // Console mode keyrelease callbacks begin here.

    std::shared_ptr<datatypes::AnyValue> Console::enable_exit_console(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>&,
            console::Console* console)
    {
        if (console->in_console)
        {
            console->can_exit_console = true;
        }
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> Console::release_left_control_in_console(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>&,
            console::Console* console)
    {
        if (console->in_console)
        {
            console->is_left_control_pressed = false;
        }
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> Console::release_right_control_in_console(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>&,
            console::Console* console)
    {
        if (console->in_console)
        {
            console->is_right_control_pressed = false;
        }
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> Console::release_left_alt_in_console(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>&,
            console::Console* console)
    {
        if (console->in_console)
        {
            console->is_left_alt_pressed = false;
        }
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> Console::release_right_alt_in_console(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>&,
            console::Console* console)
    {
        if (console->in_console)
        {
            console->is_right_alt_pressed = false;
        }
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> Console::release_left_shift_in_console(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>&,
            console::Console* console)
    {
        if (console->in_console)
        {
            console->is_left_shift_pressed = false;
        }
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> Console::release_right_shift_in_console(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>&,
            console::Console* console)
    {
        if (console->in_console)
        {
            console->is_right_shift_pressed = false;
        }
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> Console::enable_move_to_previous_input(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>&,
            console::Console* console)
    {
        if (console->in_console)
        {
            console->can_move_to_previous_input = true;
        }
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> Console::enable_move_to_next_input(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>&,
            console::Console* console)
    {
        if (console->in_console)
        {
            console->can_move_to_next_input = true;
        }
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> Console::enable_backspace(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>&,
            console::Console* console)
    {
        if (console->in_console)
        {
            console->can_backspace = true;
        }
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> Console::enable_enter_key(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>&,
            console::Console* console)
    {
        if (console->in_console)
        {
            console->can_enter_key = true;
        }
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> Console::enable_ctrl_c(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>&,
            console::Console* console)
    {
        if (console->in_console)
        {
            console->can_ctrl_c = true;
        }
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> Console::enable_ctrl_w(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>&,
            console::Console* console)
    {
        if (console->in_console)
        {
            console->can_ctrl_w = true;
        }
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> Console::enable_page_up(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>&,
            console::Console* console)
    {
        if (console->in_console)
        {
            console->can_page_up = true;
        }
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> Console::enable_page_down(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>&,
            console::Console* console)
    {
        if (console->in_console)
        {
            console->can_page_down = true;
        }
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> Console::enable_home(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>&,
            console::Console* console)
    {
        if (console->in_console)
        {
            console->can_home = true;
        }
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> Console::enable_end(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>&,
            console::Console* console)
    {
        if (console->in_console)
        {
            console->can_end = true;
        }
        return nullptr;
    }

    // Console mode keypress callbacks begin here.

    std::shared_ptr<datatypes::AnyValue> Console::exit_console(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>&,
            console::Console* console)
    {
        if (console->in_console && console->exit_console())
        {
            // Signal to caller that we have exited the console.
            uint32_t exit_console_magic_number = EXIT_CONSOLE_MAGIC_NUMBER;
            std::shared_ptr<datatypes::AnyValue> any_value_magic_number = std::make_shared<datatypes::AnyValue>(exit_console_magic_number);
            return any_value_magic_number;
        }

        // We did not exit the console.
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> Console::press_left_control_in_console(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>&,
            console::Console* console)
    {
        if (console->in_console)
        {
            console->is_left_control_pressed = true;
        }
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> Console::press_right_control_in_console(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>&,
            console::Console* console)
    {
        if (console->in_console)
        {
            console->is_right_control_pressed = true;
        }
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> Console::press_left_alt_in_console(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>&,
            console::Console* console)
    {
        if (console->in_console)
        {
            console->is_left_alt_pressed = true;
        }
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> Console::press_right_alt_in_console(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>&,
            console::Console* console)
    {
        if (console->in_console)
        {
            console->is_right_alt_pressed = true;
        }
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> Console::press_left_shift_in_console(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>&,
            console::Console* console)
    {
        if (console->in_console)
        {
            console->is_left_shift_pressed = true;
        }
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> Console::press_right_shift_in_console(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>&,
            console::Console* console)
    {
        if (console->in_console)
        {
            console->is_right_shift_pressed = true;
        }
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> Console::move_to_previous_input(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>&,
            console::Console* console)
    {
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

    std::shared_ptr<datatypes::AnyValue> Console::move_to_next_input(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>&,
            console::Console* console)
    {
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

    std::shared_ptr<datatypes::AnyValue> Console::backspace(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>&,
            console::Console* console)
    {
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

    std::shared_ptr<datatypes::AnyValue> Console::enter_key(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>&,
            console::Console* console)
    {
        std::shared_ptr<datatypes::AnyValue> any_value = nullptr;

        if (console->in_console &&
                console->can_enter_key)
        {
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

            if (is_command)
            {
                // Call the corresponding console command callback, if there is one.
                if (console->command_callback_map_pointer != nullptr &&
                        console->command_callback_map_pointer->count(command) == 1)
                {
                    ConsoleCommandCallback callback = console->command_callback_map_pointer->at(command);
                    any_value = callback(console, console->universe, parameter_vector);
                }
            }

            console->current_input.clear();
            console->in_historical_input = false;
            console->cursor_it = console->current_input.begin();
            console->cursor_index = 0;
            console->can_enter_key = false;
        }
        return any_value;
    }

    std::shared_ptr<datatypes::AnyValue> Console::ctrl_c(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>&,
            console::Console* console)
    {
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

    std::shared_ptr<datatypes::AnyValue> Console::ctrl_w(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>&,
            console::Console* console)
    {
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

    std::shared_ptr<datatypes::AnyValue> Console::page_up(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>&,
            console::Console* console)
    {
        if (console->in_console && console->can_page_up)
        {
            if (console->in_history)
            {
                console->history_line_i -= console->n_rows;
            }
            else
            {
                console->in_history = true;
                console->history_line_i = console->console_history.size() - 2 * console->n_rows;
            }

            if (console->history_line_i < 0)
            {
                console->history_line_i = 0;
            }

            if (console->history_line_i + console->n_rows >= console->console_history.size())
            {
                console->in_history = false;
            }

            console->can_page_up = false;
        }

        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> Console::page_down(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>&,
            console::Console* console)
    {
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

    std::shared_ptr<datatypes::AnyValue> Console::home(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>&,
            console::Console* console)
    {
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

    std::shared_ptr<datatypes::AnyValue> Console::end(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>&,
            console::Console* console)
    {
        if (console->in_console && console->can_end)
        {
            console->in_history = false;
            console->can_home = false;
        }
        return nullptr;
    }

    // Public callbacks end here.

    // Keep these variable types as this is according to GLFW documentation!
    // So: `unsigned int codepoint`, `int mods`.
    void Console::charmods_callback(GLFWwindow* window, unsigned int codepoint, int mods)
    {
        // `int mods` values:
        // No modificators:       0x00
        // Shift (left or right): 0x01
        // Alt (not AltGr):       0x04
        // Shift + Alt:           0x05
        ontology::Universe* universe = static_cast<ontology::Universe*>(glfwGetWindowUserPointer(window));

        if (universe == nullptr)
        {
            return;
        }

        console::Console* console = universe->get_console();

        if (console == nullptr)
        {
            return;
        }

        if ((mods == 0 || mods == 1) &&
                console->in_console &&
                !console->is_left_control_pressed &&
                !console->is_right_control_pressed &&
                !console->is_left_alt_pressed)
        {
            console->in_history = false;
            console->cursor_it = console->current_input.insert(console->cursor_it, static_cast<char>(codepoint));
            console->cursor_it++;
            console->cursor_index++;
        }
    }

    // Callbacks end here.
}
