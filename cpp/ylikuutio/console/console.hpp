#ifndef __CONSOLE_HPP_INCLUDED
#define __CONSOLE_HPP_INCLUDED

// Include standard headers
#include <list>     // std::list
#include <stdint.h> // uint32_t etc.

namespace console
{
    class Console
    {
        public:
            // constructor.
            Console();

            // destructor.
            ~Console();

            void add_character(char character);
            void backspace(char character);
            void delete_character(char character);
            void Console::move_cursor_left();
            void Console::move_cursor_right();
            void Console::move_cursor_to_start_of_line();
            void Console::move_cursor_to_end_of_line();
            void Console::page_up();
            void Console::page_down();
            void Console::home();
            void Console::end();

        private:
            std::list<char> current_input;
            uint32_t cursor_index;
    };
}
#endif
