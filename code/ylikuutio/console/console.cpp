#include "console.hpp"
#include "command_and_callback_struct.hpp"
#include "code/ylikuutio/ontology/font2D.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/callback_system/callback_magic_numbers.hpp"
#include "code/ylikuutio/common/global_variables.hpp"
#include "code/ylikuutio/common/globals.hpp"
#include "code/ylikuutio/string/ylikuutio_string.hpp"

// Include GLFW
#ifndef __GLFW3_H_INCLUDED
#define __GLFW3_H_INCLUDED
#include <glfw3.h>
#endif

// Include standard headers
#include <algorithm>     // std::sort
#include <iterator>      // std::back_inserter
#include <list>          // std::list
#include <sstream>       // std::otringstream, std::istringstream, std::ostringstream
#include <stdint.h>      // uint32_t etc.
#include <string.h>      // strlen
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

namespace console
{
    Console::Console(
            std::vector<KeyAndCallbackStruct>** current_keypress_callback_engine_vector_pointer_pointer,
            std::vector<KeyAndCallbackStruct>** current_keyrelease_callback_engine_vector_pointer_pointer,
            std::unordered_map<std::string, ConsoleCommandCallback>* command_callback_map_pointer,
            ontology::Universe* universe_pointer,
            ontology::Font2D* text2D_pointer)
    {
        // constructor.
        this->cursor_it = this->current_input.begin();
        this->cursor_index = 0;
        this->in_historical_input = false;
        this->in_console = false;
        this->can_enter_console = true;
        this->can_exit_console = false;
        this->can_move_to_previous_input = false;
        this->can_move_to_next_input = false;
        this->can_backspace = false;
        this->can_enter_key = false;
        this->can_ctrl_c = false;
        this->is_left_control_pressed = false;
        this->is_right_control_pressed = false;
        this->is_left_alt_pressed = false;
        this->is_right_alt_pressed = false;
        this->is_left_shift_pressed = false;
        this->is_right_shift_pressed = false;
        this->previous_keypress_callback_engine_vector_pointer = nullptr;
        this->my_keypress_callback_engine_vector_pointer = nullptr;
        this->previous_keyrelease_callback_engine_vector_pointer = nullptr;
        this->my_keyrelease_callback_engine_vector_pointer = nullptr;

        // This is a pointer to `std::vector<KeyAndCallbackStruct>*` that controls keypress callbacks.
        this->current_keypress_callback_engine_vector_pointer_pointer = current_keypress_callback_engine_vector_pointer_pointer;

        // This is a pointer to `std::vector<KeyAndCallbackStruct>*` that controls keyrelease callbacks.
        this->current_keyrelease_callback_engine_vector_pointer_pointer = current_keyrelease_callback_engine_vector_pointer_pointer;

        // This is a pointer to `std::unordered_map<std::string, bool>` that contains console command callbacks.
        this->command_callback_map_pointer = command_callback_map_pointer;

        // This is a pointer to `ontology::Universe`.
        this->universe_pointer = universe_pointer;

        // This is a pointer to `font2D::Font2D` instance that is used for printing.
        this->text2D_pointer = text2D_pointer;

        this->print_text("Welcome! Please write \"help\" for more");
        this->print_text("information.");
    }

    Console::~Console()
    {
        // destructor.
        this->exit_console();
    }

    void Console::set_my_keypress_callback_engine_vector_pointer(std::vector<KeyAndCallbackStruct>* my_keypress_callback_engine_vector_pointer)
    {
        this->my_keypress_callback_engine_vector_pointer = my_keypress_callback_engine_vector_pointer;
    }

    void Console::set_my_keyrelease_callback_engine_vector_pointer(std::vector<KeyAndCallbackStruct>* my_keyrelease_callback_engine_vector_pointer)
    {
        this->my_keyrelease_callback_engine_vector_pointer = my_keyrelease_callback_engine_vector_pointer;
    }

    void Console::print_text(std::string text)
    {
        // This function is to be called from console command callbacks to print text on console.
        // Please not that it is not necessary to be in console to be able to print in console.
        const char* text_char = text.c_str();

        uint32_t characters_for_line = window_width / text_size;

        std::list<char> text_char_list;
        uint32_t current_line_length = 0;

        for (char& my_char : text)
        {
            if (my_char == '\n')
            {
                // A newline.
                this->console_history.push_back(text_char_list);
                text_char_list.clear();
                current_line_length = 0;
            }
            else if (current_line_length < characters_for_line)
            {
                // Normal case.
                text_char_list.push_back(my_char);
                current_line_length++;
            }
            else
            {
                // Newline is needed due to too long line.
                this->console_history.push_back(text_char_list);
                text_char_list.clear();
                text_char_list.push_back(my_char);
                current_line_length = 1;
            }
        }

        if (text_char_list.size() > 0)
        {
            this->console_history.push_back(text_char_list);
        }
    }

    void Console::print_help()
    {
        std::vector<std::string> command_vector;
        command_vector.reserve(this->command_callback_map_pointer->size());

        for (auto key_and_value : *this->command_callback_map_pointer)
        {
            command_vector.push_back(key_and_value.first); // key (command).
        }

        // sort command vector alphabetically.
        std::sort(command_vector.begin(), command_vector.end());

        uint32_t characters_for_line = window_width / text_size;

        std::string commands_text;

        for (std::string command : command_vector)
        {
            if (commands_text.size() > 0 &&
                    commands_text.size() + command.size() >= characters_for_line)
            {
                // Not enough space for this command on this line.
                // Print this line.
                this->print_text(commands_text);
                commands_text = command;
            }
            else if (commands_text.size() > 0)
            {
                // There is space, and this is not the first command on this line.
                commands_text += " " + command;
            }
            else
            {
                // This is the first command on this line.
                commands_text += command;
            }
        }
        if (commands_text.size() > 0)
        {
            // Print the last line.
            this->print_text(commands_text);
        }
    }

    void Console::draw_console()
    {
        if (this->in_console)
        {
            // Convert current input into std::string.
            uint32_t characters_for_line = window_width / text_size;

            // Draw the console to screen using `font2D::printText2D`.
            PrintingStruct printing_struct;
            printing_struct.screen_width = (GLuint) window_width;
            printing_struct.screen_height = (GLuint) window_height;
            printing_struct.text_size = text_size;
            printing_struct.font_size = font_size;
            printing_struct.char_font_texture_file_format = "bmp";

            printing_struct.x = 0;
            printing_struct.y = window_height - (2 * text_size);
            printing_struct.horizontal_alignment = "left";
            printing_struct.vertical_alignment = "top";

            for (uint32_t history_i = 0; history_i < this->console_history.size(); history_i++)
            {
                std::list<char> historical_text = this->console_history.at(history_i);
                printing_struct.text += string::convert_std_list_char_to_std_string(historical_text, characters_for_line, characters_for_line) + "\\n";
            }
            printing_struct.text += "$ " + string::convert_std_list_char_to_std_string(this->current_input, characters_for_line - 2, characters_for_line);

            this->text2D_pointer->printText2D(printing_struct);
        }
    }

    // Public callbacks.

    // Action mode keyrelease callbacks begin here.

    datatypes::AnyValue* Console::enable_enter_console(
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

    datatypes::AnyValue* Console::enter_console(
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

            glfwSetCharModsCallback(window, Console::charmods_callback);

            // Mark that we're in console.
            console->in_console = true;
            console->in_historical_input = false;

            // Usually key release is required to enable enter console.
            console->can_exit_console = false;
            console->can_enter_console = false;

            // Signal to caller that we have entered the console.
            uint32_t enter_console_magic_number = ENTER_CONSOLE_MAGIC_NUMBER;
            datatypes::AnyValue* any_value_magic_number = new datatypes::AnyValue(enter_console_magic_number);
            return any_value_magic_number;
        }

        // We did not enter the console.
        return nullptr;
    }

    // Console mode keyrelease callbacks begin here.

    datatypes::AnyValue* Console::enable_exit_console(
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

    datatypes::AnyValue* Console::release_left_control_in_console(
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

    datatypes::AnyValue* Console::release_right_control_in_console(
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

    datatypes::AnyValue* Console::release_left_alt_in_console(
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

    datatypes::AnyValue* Console::release_right_alt_in_console(
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

    datatypes::AnyValue* Console::release_left_shift_in_console(
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

    datatypes::AnyValue* Console::release_right_shift_in_console(
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

    datatypes::AnyValue* Console::enable_move_to_previous_input(
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

    datatypes::AnyValue* Console::enable_move_to_next_input(
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

    datatypes::AnyValue* Console::enable_backspace(
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

    datatypes::AnyValue* Console::enable_enter_key(
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

    datatypes::AnyValue* Console::enable_ctrl_c(
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

    // Console mode keypress callbacks begin here.

    datatypes::AnyValue* Console::exit_console(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>&,
            console::Console* console)
    {
        if (console->in_console && console->exit_console())
        {
            // Signal to caller that we have exited the console.
            uint32_t exit_console_magic_number = EXIT_CONSOLE_MAGIC_NUMBER;
            datatypes::AnyValue* any_value_magic_number = new datatypes::AnyValue(exit_console_magic_number);
            return any_value_magic_number;
        }

        // We did not exit the console.
        return nullptr;
    }

    datatypes::AnyValue* Console::press_left_control_in_console(
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

    datatypes::AnyValue* Console::press_right_control_in_console(
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

    datatypes::AnyValue* Console::press_left_alt_in_console(
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

    datatypes::AnyValue* Console::press_right_alt_in_console(
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

    datatypes::AnyValue* Console::press_left_shift_in_console(
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

    datatypes::AnyValue* Console::press_right_shift_in_console(
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

    datatypes::AnyValue* Console::move_to_previous_input(
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

    datatypes::AnyValue* Console::move_to_next_input(
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

    datatypes::AnyValue* Console::backspace(
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

    datatypes::AnyValue* Console::enter_key(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>&,
            console::Console* console)
    {
        datatypes::AnyValue* any_value = nullptr;

        if (console->in_console &&
                console->can_enter_key)
        {
            // Parse input into vector.
            std::string input_string(console->current_input.begin(), console->current_input.end());
            std::istringstream input_stringstream(input_string);
            std::string command;

            console->command_history.push_back(console->current_input);
            std::list<char>::iterator it = console->current_input.begin();
            console->current_input.insert(it, '$');
            console->current_input.insert(it, ' ');
            console->console_history.push_back(console->current_input);

            if (std::getline(input_stringstream, command, ' '))
            {
                // OK, there was a command.
                std::vector<std::string> parameter_vector;

                // Now read the command parameters.
                while (true)
                {
                    std::string parameter;

                    if (std::getline(input_stringstream, parameter, ' '))
                    {
                        parameter_vector.push_back(parameter);
                    }
                    else
                    {
                        break;
                    }
                }

                // Call the corresponding console command callback, if there is one.
                if (console->command_callback_map_pointer != nullptr &&
                        console->command_callback_map_pointer->count(command) == 1)
                {
                    ConsoleCommandCallback callback = console->command_callback_map_pointer->at(command);
                    any_value = callback(console, console->universe_pointer, parameter_vector);
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

    datatypes::AnyValue* Console::ctrl_c(
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
        if ((mods == 0 || mods == 1) &&
                global_console_pointer->in_console &&
                !global_console_pointer->is_left_control_pressed &&
                !global_console_pointer->is_right_control_pressed &&
                !global_console_pointer->is_left_alt_pressed)
        {
            global_console_pointer->cursor_it = global_console_pointer->current_input.insert(global_console_pointer->cursor_it, static_cast<char>(codepoint));
            global_console_pointer->cursor_it++;
            global_console_pointer->cursor_index++;
        }
    }

    // Callbacks end here.

    void Console::copy_historical_input_into_current_input()
    {
        if (this->in_console)
        {
            // Copy selected historical input into current input.
            this->current_input.clear();
            std::copy(this->command_history.at(this->historical_input_i).begin(),
                    this->command_history.at(this->historical_input_i).end(),
                    std::back_inserter(this->current_input));
        }
    }

    bool Console::exit_console()
    {
        if (this->in_console &&
                this->can_exit_console &&
                this->previous_keypress_callback_engine_vector_pointer != nullptr &&
                this->previous_keyrelease_callback_engine_vector_pointer != nullptr)
        {
            // Restore previous keypress callback engine vector pointer.
            *this->current_keypress_callback_engine_vector_pointer_pointer = this->previous_keypress_callback_engine_vector_pointer;

            // Restore previous keyrelease callback engine vector pointer.
            *this->current_keyrelease_callback_engine_vector_pointer_pointer = this->previous_keyrelease_callback_engine_vector_pointer;

            glfwSetCharModsCallback(window, nullptr);

            // Mark that we have exited the console.
            this->in_console = false;

            // Usually key release is required to enable exit console.
            this->can_enter_console = false;
            this->can_exit_console = false;
            return true;
        }
        return false;
    }

    void Console::delete_character()
    {
        if (this->in_console)
        {
            this->current_input.erase(this->cursor_it);
        }
    }

    void Console::move_cursor_left()
    {
        if (this->cursor_it != this->current_input.begin())
        {
            this->cursor_it--;
            this->cursor_index--;
        }
    }

    void Console::move_cursor_right()
    {
        if (this->in_console && this->cursor_it != this->current_input.end())
        {
            this->cursor_it++;
            this->cursor_index++;
        }
    }

    void Console::move_cursor_to_start_of_line()
    {
        if (this->in_console)
        {
            this->cursor_it = this->current_input.begin();
            this->cursor_index = 0;
        }
    }

    void Console::move_cursor_to_end_of_line()
    {
        if (this->in_console)
        {
            this->cursor_it = this->current_input.end();
            this->cursor_index = this->current_input.size();
        }
    }

    void Console::page_up()
    {
        if (this->in_console)
        {
            // TODO: implement this function!
        }
    }

    void Console::page_down()
    {
        if (this->in_console)
        {
            // TODO: implement this function!
        }
    }

    void Console::home()
    {
        if (this->in_console)
        {
            // TODO: implement this function!
        }
    }

    void Console::end()
    {
        if (this->in_console)
        {
            // TODO: implement this function!
        }
    }
}
