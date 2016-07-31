#include "console.hpp"
#include "console_keypress_callbacks.hpp"
#include "cpp/ylikuutio/ontology/text2D.hpp"
#include "cpp/ylikuutio/common/global_variables.hpp"
#include "cpp/ylikuutio/common/globals.hpp"
#include "cpp/ylikuutio/string/ylikuutio_string.hpp"

// Include GLFW
#ifndef __GLFW3_H_INCLUDED
#define __GLFW3_H_INCLUDED
#include <glfw3.h>
#endif

namespace console
{
    Console::Console(
            std::vector<KeyAndCallbackStruct>** current_keypress_callback_engine_vector_pointer_pointer,
            std::vector<KeyAndCallbackStruct>** current_keyrelease_callback_engine_vector_pointer_pointer,
            ontology::Text2D* text2D_pointer)
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

        // This is a pointer to `text2D::Text2D` instance that is used for printing.
        this->text2D_pointer = text2D_pointer;
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

    void Console::draw_console()
    {
        if (this->in_console)
        {
            // Convert current input into std::string.
            uint32_t characters_for_line = window_width / text_size;

            // Draw the console to screen using `text2D::printText2D`.
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
            printing_struct.text =
                "Welcome! Please write \"help\"\\n"
                "for more information.\\n";

            for (uint32_t historical_input_i = 0; historical_input_i < this->command_history.size(); historical_input_i++)
            {
                std::list<char> historical_input = this->command_history.at(historical_input_i);
                printing_struct.text += "$ " + string::convert_std_list_char_to_std_string(historical_input, characters_for_line - 2, characters_for_line) + "\\n";
            }
            printing_struct.text += "$ " + string::convert_std_list_char_to_std_string(this->current_input, characters_for_line - 2, characters_for_line);

            this->text2D_pointer->printText2D(printing_struct);
        }
    }

    void Console::copy_historical_input_into_current_input()
    {
        // Copy selected historical input into current input.
        this->current_input.clear();
        std::copy(this->command_history.at(this->historical_input_i).begin(),
                this->command_history.at(this->historical_input_i).end(),
                std::back_inserter(this->current_input));
    }

    void Console::enable_enter_console()
    {
        this->can_enter_console = true;
    }

    void Console::enable_exit_console()
    {
        this->can_exit_console = true;
    }

    void Console::release_left_control_in_console()
    {
        this->is_left_control_pressed = false;
    }

    void Console::release_right_control_in_console()
    {
        this->is_right_control_pressed = false;
    }

    void Console::release_left_alt_in_console()
    {
        this->is_left_alt_pressed = false;
    }

    void Console::release_right_alt_in_console()
    {
        this->is_right_alt_pressed = false;
    }

    void Console::release_left_shift_in_console()
    {
        this->is_left_shift_pressed = false;
    }

    void Console::release_right_shift_in_console()
    {
        this->is_right_shift_pressed = false;
    }

    void Console::enable_move_to_previous_input()
    {
        this->can_move_to_previous_input = true;
    }

    void Console::enable_move_to_next_input()
    {
        this->can_move_to_next_input = true;
    }

    void Console::enable_backspace()
    {
        this->can_backspace = true;
    }

    void Console::enable_enter_key()
    {
        this->can_enter_key = true;
    }

    bool Console::enter_console()
    {
        if (!this->in_console &&
                this->can_enter_console &&
                this->my_keypress_callback_engine_vector_pointer != nullptr &&
                this->my_keyrelease_callback_engine_vector_pointer != nullptr &&
                this->current_keypress_callback_engine_vector_pointer_pointer != nullptr &&
                this->current_keyrelease_callback_engine_vector_pointer_pointer != nullptr)
        {
            // Store previous keypress callback engine vector pointer.
            this->previous_keypress_callback_engine_vector_pointer = *this->current_keypress_callback_engine_vector_pointer_pointer;

            // Set new keypress callback engine vector pointer.
            *this->current_keypress_callback_engine_vector_pointer_pointer = this->my_keypress_callback_engine_vector_pointer;

            // Store previous keyrelease callback engine vector pointer.
            this->previous_keyrelease_callback_engine_vector_pointer = *this->current_keyrelease_callback_engine_vector_pointer_pointer;

            // Set new keyrelease callback engine vector pointer.
            *this->current_keyrelease_callback_engine_vector_pointer_pointer = this->my_keyrelease_callback_engine_vector_pointer;

            glfwSetCharModsCallback(window, console::charmods_callback);

            // Mark that we're in console.
            this->in_console = true;
            this->in_historical_input = false;

            // Usually key release is required to enable enter console.
            this->can_exit_console = false;
            this->can_enter_console = false;
            return true;
        }
        return false;
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

    void Console::press_left_control_in_console()
    {
        this->is_left_control_pressed = true;
    }

    void Console::press_right_control_in_console()
    {
        this->is_right_control_pressed = true;
    }

    void Console::press_left_alt_in_console()
    {
        this->is_left_alt_pressed = true;
    }

    void Console::press_right_alt_in_console()
    {
        this->is_right_alt_pressed = true;
    }

    void Console::press_left_shift_in_console()
    {
        this->is_left_shift_pressed = true;
    }

    void Console::press_right_shift_in_console()
    {
        this->is_right_shift_pressed = true;
    }

    void Console::add_character(char character, uint32_t mods)
    {
        if ((mods == 0 || mods == 1) &&
                !this->is_left_control_pressed &&
                !this->is_right_control_pressed &&
                !this->is_left_alt_pressed)
        {
            this->cursor_it = this->current_input.insert(this->cursor_it, character);
            this->cursor_it++;
            this->cursor_index++;
        }
    }

    void Console::backspace()
    {
        if (this->in_console &&
                this->can_backspace &&
                this->cursor_it != this->current_input.begin())
        {
            this->cursor_it = this->current_input.erase(--this->cursor_it);
            this->cursor_index--;
            this->can_backspace = false;
        }
    }

    void Console::delete_character()
    {
        this->current_input.erase(this->cursor_it);
    }

    void Console::enter_key()
    {
        if (this->in_console &&
                this->can_enter_key)
        {
            this->command_history.push_back(this->current_input);
            this->current_input.clear();
            this->in_historical_input = false;
            this->cursor_it = this->current_input.begin();
            this->cursor_index = 0;
            this->can_enter_key = false;
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
        if (this->cursor_it != this->current_input.end())
        {
            this->cursor_it++;
            this->cursor_index++;
        }
    }

    void Console::move_cursor_to_start_of_line()
    {
        this->cursor_it = this->current_input.begin();
        this->cursor_index = 0;
    }

    void Console::move_cursor_to_end_of_line()
    {
        this->cursor_it = this->current_input.end();
        this->cursor_index = this->current_input.size();
    }

    void Console::move_to_previous_input()
    {
        if (this->in_console && this->can_move_to_previous_input)
        {
            if (!this->in_historical_input && this->command_history.size() > 0)
            {
                // OK, we moved from the new input to the last historical input.
                this->in_historical_input = true;
                this->historical_input_i = this->command_history.size() - 1;

                // Copy the new input into temp input.
                this->temp_input.clear();
                std::copy(this->current_input.begin(), this->current_input.end(), std::back_inserter(this->temp_input));

                // Copy the historical input into current input.
                this->current_input.clear();
                this->copy_historical_input_into_current_input();

                this->move_cursor_to_end_of_line();
                this->can_move_to_previous_input = false;
            }
            else if (this->in_historical_input && this->historical_input_i > 0)
            {
                // OK, we moved to the previous historical input.
                this->historical_input_i--;

                // Copy the historical input into current input.
                this->copy_historical_input_into_current_input();

                this->move_cursor_to_end_of_line();
                this->can_move_to_previous_input = false;
            }
        }
    }

    void Console::move_to_next_input()
    {
        if (this->in_console && this->can_move_to_next_input)
        {
            if (this->in_historical_input && this->historical_input_i == this->command_history.size() - 1)
            {
                // OK, we moved from the last historical input to the new input.
                this->in_historical_input = false;

                // Copy temp input into current input.
                this->current_input.clear();
                std::copy(this->temp_input.begin(), this->temp_input.end(), std::back_inserter(this->current_input));
                // this->current_input.assign(this->temp_input.begin(), this->temp_input.end());

                this->move_cursor_to_end_of_line();
                this->can_move_to_next_input = false;
            }
            else if (this->in_historical_input && this->historical_input_i < this->command_history.size() - 1)
            {
                // OK, we moved to the next historical input.
                this->historical_input_i++;

                // Copy the historical input into current input.
                this->copy_historical_input_into_current_input();

                this->move_cursor_to_end_of_line();
                this->can_move_to_next_input = false;
            }
        }
    }

    void Console::page_up()
    {
        // TODO: implement this function!
    }

    void Console::page_down()
    {
        // TODO: implement this function!
    }

    void Console::home()
    {
        // TODO: implement this function!
    }

    void Console::end()
    {
        // TODO: implement this function!
    }
}
