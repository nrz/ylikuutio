// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2019 Antti Nuortimo.
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

#ifndef __CONSOLE_HPP_INCLUDED
#define __CONSOLE_HPP_INCLUDED

#include "console_command_callback.hpp"
#include "code/ylikuutio/callback_system/key_and_callback_struct.hpp"

#include "SDL.h"

// Include standard headers
#include <cstddef>       // std::size_t
#include <list>          // std::list
#include <memory>        // std::make_shared, std::shared_ptr
#include <stdint.h>      // uint32_t etc.
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

// `Console` works through keypress callbacks and keyrelease callbacks, and
// `glfwSetCharModsCallback`. If the action of a key should not happen many
// times in a very fast succession, some means to control the frequency is
// needed. The easiest option is to use a `bool` variable like
// `bool enable_action`.
//
// In the keypress callback, the value of `enable_action` is tested, and
// nothing is done if it's `false`.
//
// If `enable_action` is `true`, the corresponding action takes place,
// after which `enable_action` is set to `false`.
//
// In the keyrelease callback `enable_action` is set to `true`.
//
// `glfwSetCharModsCallback` sets a separate callback for some special keys.
// This is used for entering text into console (writing commands).
// All other console-related functions are implemented through keypress
// callbacks and keyrelease callbacks.

namespace yli
{
    namespace callback_system
    {
        class CallbackEngine;
        class CallbackObject;
        class CallbackParameter;
    }

    namespace common
    {
        class AnyValue;
    }

    namespace map
    {
        template <class T1>
            void print_keys_to_console(const std::unordered_map<std::string, T1>* const unordered_map_pointer, yli::console::Console* const console);
    }

    namespace ontology
    {
        class Universe;
    }

    namespace console
    {
        class Console
        {
            public:
                // constructor.
                Console(
                        yli::ontology::Universe* const universe,
                        std::vector<yli::callback_system::KeyAndCallbackStruct>** current_keypress_callback_engine_vector_pointer_pointer,
                        std::vector<yli::callback_system::KeyAndCallbackStruct>** current_keyrelease_callback_engine_vector_pointer_pointer);

                Console(const Console&) = delete;            // Delete copy constructor.
                Console &operator=(const Console&) = delete; // Delete copy assignment.

                // destructor.
                ~Console();

                void set_my_keypress_callback_engine_vector_pointer(std::vector<yli::callback_system::KeyAndCallbackStruct>* my_keypress_callback_engine_vector_pointer);
                void set_my_keyrelease_callback_engine_vector_pointer(std::vector<yli::callback_system::KeyAndCallbackStruct>* my_keyrelease_callback_engine_vector_pointer);
                void add_command_callback(const std::string& command, ConsoleCommandCallback callback);
                void set_console_top_y(const uint32_t console_top_y);
                void set_console_bottom_y(const uint32_t console_bottom_y);
                void set_console_left_x(const uint32_t console_left_x);
                void set_console_right_x(const uint32_t console_right_x);
                void print_text(const std::string& text);
                void print_help();
                void render() const;

                bool get_in_console() const;
                void process_key_event(const SDL_KeyboardEvent& keyboard_event);

                yli::ontology::Universe* get_universe() const;

                // Public callbacks.

                // Action mode keypress callbacks begin here.

                static std::shared_ptr<yli::common::AnyValue> enter_console(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                // Console mode keyrelease callbacks begin here.

                static std::shared_ptr<yli::common::AnyValue> release_left_control_in_console(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::common::AnyValue> release_right_control_in_console(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::common::AnyValue> release_left_alt_in_console(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::common::AnyValue> release_right_alt_in_console(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::common::AnyValue> release_left_shift_in_console(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::common::AnyValue> release_right_shift_in_console(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::common::AnyValue> enable_move_to_previous_input(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::common::AnyValue> enable_move_to_next_input(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::common::AnyValue> enable_backspace(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::common::AnyValue> enable_enter_key(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::common::AnyValue> enable_ctrl_c(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::common::AnyValue> enable_ctrl_w(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::common::AnyValue> enable_page_up(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::common::AnyValue> enable_page_down(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::common::AnyValue> enable_home(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::common::AnyValue> enable_end(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                // Console mode keypress callbacks begin here.

                static std::shared_ptr<yli::common::AnyValue> exit_console(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::common::AnyValue> press_left_control_in_console(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::common::AnyValue> press_right_control_in_console(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::common::AnyValue> press_left_alt_in_console(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::common::AnyValue> press_right_alt_in_console(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::common::AnyValue> press_left_shift_in_console(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::common::AnyValue> press_right_shift_in_console(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::common::AnyValue> move_to_previous_input(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::common::AnyValue> move_to_next_input(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::common::AnyValue> backspace(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::common::AnyValue> enter_key(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::common::AnyValue> ctrl_c(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::common::AnyValue> ctrl_w(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::common::AnyValue> page_up(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::common::AnyValue> page_down(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::common::AnyValue> home(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                static std::shared_ptr<yli::common::AnyValue> end(
                        yli::callback_system::CallbackEngine*,
                        yli::callback_system::CallbackObject*,
                        std::vector<yli::callback_system::CallbackParameter*>&,
                        yli::console::Console* console);

                // Console command callbacks begin here.

                static std::shared_ptr<yli::common::AnyValue> clear(
                        yli::console::Console* const console,
                        yli::ontology::Entity* const universe_entity,
                        const std::vector<std::string>& command_parameters);

                // Public callbacks end here.

                bool should_be_rendered;

            private:
                static void charmods_callback(SDL_Window* window, unsigned int codepoint, int mods);

                // Callbacks end here.

                void copy_historical_input_into_current_input();
                bool exit_console();
                void delete_character();
                void move_cursor_left();
                void move_cursor_right();
                void move_cursor_to_start_of_line();
                void move_cursor_to_end_of_line();

                std::list<char> current_input; // This is used for actual inputs.
                std::list<char>::iterator cursor_it;
                std::size_t cursor_index;
                bool in_console;
                bool can_move_to_previous_input;
                bool can_move_to_next_input;
                bool can_backspace;
                bool can_enter_key;
                bool can_ctrl_c;
                bool can_ctrl_w;
                bool can_page_up;
                bool can_page_down;
                bool can_home;
                bool can_end;
                bool is_left_control_pressed;
                bool is_right_control_pressed;
                bool is_left_alt_pressed;
                bool is_right_alt_pressed;
                bool is_left_shift_pressed;
                bool is_right_shift_pressed;

                std::vector<std::list<char>> command_history;
                std::vector<std::list<char>> console_history;

                bool in_history;
                bool in_historical_input;
                std::size_t history_line_i;
                std::size_t historical_input_i;
                std::list<char> temp_input;    // This is used for temporary storage of new input while modifying historical inputs.

                // These are related to keypress callbacks.
                std::vector<yli::callback_system::KeyAndCallbackStruct>** current_keypress_callback_engine_vector_pointer_pointer;
                std::vector<yli::callback_system::KeyAndCallbackStruct>* previous_keypress_callback_engine_vector_pointer;
                std::vector<yli::callback_system::KeyAndCallbackStruct>* my_keypress_callback_engine_vector_pointer;

                // These are related to keyrelease callbacks.
                std::vector<yli::callback_system::KeyAndCallbackStruct>** current_keyrelease_callback_engine_vector_pointer_pointer;
                std::vector<yli::callback_system::KeyAndCallbackStruct>* previous_keyrelease_callback_engine_vector_pointer;
                std::vector<yli::callback_system::KeyAndCallbackStruct>* my_keyrelease_callback_engine_vector_pointer;

                // `std::unordered_map` contains console command callbacks.
                std::unordered_map<std::string, ConsoleCommandCallback> command_callback_map;

                // This is a pointer to `yli::ontology::Universe`.
                yli::ontology::Universe* universe;

                std::size_t console_top_y;
                std::size_t console_bottom_y;
                std::size_t console_left_x;
                std::size_t console_right_x;

                std::size_t n_rows;
                std::size_t n_columns;

                const std::string prompt = "$ ";
        };
    }
}

#endif
