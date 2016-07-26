#ifndef __CONSOLE_HPP_INCLUDED
#define __CONSOLE_HPP_INCLUDED

#include "cpp/ylikuutio/callback_system/key_and_callback_struct.hpp"

// Include standard headers
#include <list>     // std::list
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace console
{
    class Console
    {
        public:
            // constructor.
            Console(std::vector<KeyAndCallbackStruct>** current_callback_engine_vector_pointer_pointer);

            // destructor.
            ~Console();

            void set_my_callback_engine_vector_pointer(std::vector<KeyAndCallbackStruct>* my_callback_engine_vector_pointer);
            void draw_console();
            void enter_console();
            void exit_console();
            void add_character(char character);
            void backspace();
            void delete_character();
            void enter_key();
            void move_cursor_left();
            void move_cursor_right();
            void move_cursor_to_start_of_line();
            void move_cursor_to_end_of_line();
            void page_up();
            void page_down();
            void home();
            void end();

        private:
            std::list<char> current_input;
            std::list<char>::iterator cursor_it;
            uint32_t cursor_index;
            bool in_console;
            std::vector<std::list<char>> command_history;
            std::vector<KeyAndCallbackStruct>** current_callback_engine_vector_pointer_pointer;
            std::vector<KeyAndCallbackStruct>* previous_callback_engine_vector_pointer;
            std::vector<KeyAndCallbackStruct>* my_callback_engine_vector_pointer;
    };
}

#endif
