#include "console.hpp"
#include "cpp/ylikuutio/ontology/text2D.hpp"
#include "cpp/ylikuutio/common/globals.hpp"
#include "cpp/ylikuutio/string/ylikuutio_string.hpp"

namespace console
{
    Console::Console(std::vector<KeyAndCallbackStruct>** current_callback_engine_vector_pointer_pointer)
    {
        // constructor.
        this->cursor_it = this->current_input.begin();
        this->cursor_index = 0;
        this->in_console = false;
        this->previous_callback_engine_vector_pointer = nullptr;
        this->my_callback_engine_vector_pointer = nullptr;

        // This is a pointer to `std::vector<KeyAndCallbackStruct>*` that controls keypress callbacks.
        this->current_callback_engine_vector_pointer_pointer = current_callback_engine_vector_pointer_pointer;
    }

    Console::~Console()
    {
        // destructor.
        this->exit_console();
    }

    void Console::set_my_callback_engine_vector_pointer(std::vector<KeyAndCallbackStruct>* my_callback_engine_vector_pointer)
    {
        this->my_callback_engine_vector_pointer = my_callback_engine_vector_pointer;
    }

    void Console::draw_console()
    {
        if (this->in_console)
        {
            // Convert current input into std::string.
            std::string current_input_string = string::convert_std_list_char_to_std_string(this->current_input);

            // Draw the console to screen using `text2D::printText2D`.
            PrintingStruct printing_struct;
            printing_struct.screen_width = (GLuint) window_width;
            printing_struct.screen_height = (GLuint) window_height;
            printing_struct.text_size = text_size;
            printing_struct.font_size = font_size;
            printing_struct.char_font_texture_file_format = "bmp";

            printing_struct.x = 0;
            printing_struct.y = window_height - (2 * text_size);
            printing_struct.text =
                "Welcome! Please write \"help\"\\n"
                "for more information.\\n"
                "$ " + current_input_string;
            printing_struct.horizontal_alignment = "left";
            printing_struct.vertical_alignment = "top";
            text2D::printText2D(printing_struct);
        }
    }

    void Console::enter_console()
    {
        if (this->my_callback_engine_vector_pointer != nullptr)
        {
            // Store previous callback engine vector pointer.
            this->previous_callback_engine_vector_pointer = *this->current_callback_engine_vector_pointer_pointer;

            // Set new callback engine vector pointer.
            *this->current_callback_engine_vector_pointer_pointer = this->my_callback_engine_vector_pointer;

            // Mark that we're in console.
            this->in_console = true;
        }
    }

    void Console::exit_console()
    {
        if (this->in_console)
        {
            // Restore previous callback engine vector pointer.
            *this->current_callback_engine_vector_pointer_pointer = this->previous_callback_engine_vector_pointer;
            this->in_console = false;
        }
    }

    void Console::add_character(char character)
    {
        this->cursor_it = this->current_input.insert(this->cursor_it, character);
        this->cursor_it++;
        this->cursor_index++;
    }

    void Console::backspace()
    {
        if (this->cursor_it != this->current_input.begin())
        {
            this->cursor_index--;
            this->cursor_it = this->current_input.erase(--this->cursor_it);
        }
    }

    void Console::delete_character()
    {
        this->current_input.erase(this->cursor_it);
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
