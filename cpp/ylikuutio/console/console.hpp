#ifndef __CONSOLE_HPP_INCLUDED
#define __CONSOLE_HPP_INCLUDED

#include "cpp/ylikuutio/callback_system/key_and_callback_struct.hpp"
#include "cpp/ylikuutio/callback_system/callback_parameter.hpp"
#include "cpp/ylikuutio/callback_system/callback_object.hpp"
#include "cpp/ylikuutio/callback_system/callback_engine.hpp"
#include "cpp/ylikuutio/common/any_value.hpp"

// Include GLFW
#ifndef __GLFW3_H_INCLUDED
#define __GLFW3_H_INCLUDED
#include <glfw3.h>
#endif

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
            Console(std::vector<KeyAndCallbackStruct>** current_keypress_callback_engine_vector_pointer_pointer,
                    std::vector<KeyAndCallbackStruct>** current_keyrelease_callback_engine_vector_pointer_pointer);

            // destructor.
            ~Console();

            void set_my_keypress_callback_engine_vector_pointer(std::vector<KeyAndCallbackStruct>* my_keypress_callback_engine_vector_pointer);
            void set_my_keyrelease_callback_engine_vector_pointer(std::vector<KeyAndCallbackStruct>* my_keyrelease_callback_engine_vector_pointer);
            void draw_console();

            friend void charmods_callback(GLFWwindow* window, unsigned int codepoint, int mods);
            friend datatypes::AnyValue* enable_enter_console(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>);
            friend datatypes::AnyValue* enable_exit_console(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>);
            friend datatypes::AnyValue* enter_console(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>);
            friend datatypes::AnyValue* exit_console(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>);
            friend datatypes::AnyValue* add_character(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>);
            friend datatypes::AnyValue* backspace(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>);
            friend datatypes::AnyValue* enter_key(
                    callback_system::CallbackEngine*,
                    callback_system::CallbackObject*,
                    std::vector<callback_system::CallbackParameter*>);

        private:
            void enable_enter_console();
            void enable_exit_console();
            bool enter_console();
            bool exit_console();
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

            std::list<char> current_input; // This is used for actual inputs.
            std::list<char>::iterator cursor_it;
            uint32_t cursor_index;
            bool in_console;
            bool can_enter_console;
            bool can_exit_console;

            std::vector<std::list<char>> command_history;
            bool in_historical_input;
            uint32_t historical_input_i;
            std::list<char> temp_input;    // This is used for temporary storage of new input while modifying historical inputs.

            // These are related to keypress callbacks.
            std::vector<KeyAndCallbackStruct>** current_keypress_callback_engine_vector_pointer_pointer;
            std::vector<KeyAndCallbackStruct>* previous_keypress_callback_engine_vector_pointer;
            std::vector<KeyAndCallbackStruct>* my_keypress_callback_engine_vector_pointer;

            // These are related to keyrelease callbacks.
            std::vector<KeyAndCallbackStruct>** current_keyrelease_callback_engine_vector_pointer_pointer;
            std::vector<KeyAndCallbackStruct>* previous_keyrelease_callback_engine_vector_pointer;
            std::vector<KeyAndCallbackStruct>* my_keyrelease_callback_engine_vector_pointer;
    };
}

#endif
