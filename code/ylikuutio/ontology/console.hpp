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

#include "entity.hpp"
#include "code/ylikuutio/console/console_command_callback.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

#include "SDL.h"

// Include standard headers
#include <cstddef>       // std::size_t
#include <iostream>      // std::cout, std::cin, std::cerr
#include <limits>        // std::numeric_limits
#include <list>          // std::list
#include <memory>        // std::make_shared, std::shared_ptr
#include <queue>         // std::queue
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
//
// `Console` is created by `yli::ontology::Universe` constructor and
// deleted by `Universe` destructor, but `Console` is not an `Entity`.
// Thus there is no way to refer to the `Console` from the console input.

namespace yli
{
    namespace callback
    {
        class CallbackEngine;
        class CallbackObject;
        class CallbackParameter;
    }

    namespace common
    {
        class AnyValue;
    }

    namespace input
    {
        class InputMode;
    }

    namespace map
    {
        template <class T1>
            void print_keys_to_console(const std::unordered_map<std::string, T1>* const unordered_map_pointer, yli::ontology::Console* const console);
    }

    namespace ontology
    {
        class Universe;

        class Console: public yli::ontology::Entity
        {
            public:
                // constructor.
                Console(yli::ontology::Universe* const universe)
                    : Entity(universe)
                {
                    this->parent = universe;

                    // constructor.
                    this->should_be_rendered = true;
                    this->cursor_it = this->current_input.begin();
                    this->cursor_index = 0;
                    this->in_history = false;
                    this->in_historical_input = false;
                    this->history_line_i = std::numeric_limits<std::size_t>::max();     // some dummy value.
                    this->historical_input_i = std::numeric_limits<std::size_t>::max(); // some dummy value.
                    this->in_console = false;
                    this->can_move_to_previous_input = false;
                    this->can_move_to_next_input = false;
                    this->can_backspace = false;
                    this->can_enter_key = false;
                    this->can_ctrl_c = false;
                    this->can_ctrl_w = false;
                    this->can_page_up = false;
                    this->can_page_down = false;
                    this->can_home = false;
                    this->can_end = false;
                    this->is_left_control_pressed = false;
                    this->is_right_control_pressed = false;
                    this->is_left_alt_pressed = false;
                    this->is_right_alt_pressed = false;
                    this->is_left_shift_pressed = false;
                    this->is_right_shift_pressed = false;

                    // Get `childID` from `Universe` and set pointer to this `Console`.
                    this->bind_to_parent();

                    this->input_mode = nullptr;

                    // Initialize `console_top_y` to 9.
                    // `console_top_y` should be set by `activate_console_top_y` anyway.
                    std::cout << "Initializing console_top_y\n";
                    this->console_top_y = 9;

                    // Initialize `console_bottom_y` to 0.
                    // `console_bottom_y` should be set by `activate_console_bottom_y` anyway.
                    std::cout << "Initializing console_bottom_y\n";
                    this->console_bottom_y = 0;

                    // Initialize `console_left_x` to 0.
                    // `console_left_x` should be set by `activate_console_left_x` anyway.
                    std::cout << "Initializing console_left_x\n";
                    this->console_left_x = 0;

                    // Initialize `console_right_x` to 9.
                    // `console_right_x` should be set by `activate_console_right_x` anyway.
                    std::cout << "Initializing console_right_x\n";
                    this->console_right_x = 9;

                    // Initialize `n_rows`.
                    // `n_rows` should be set by `activate_console_top_y` and `activate_console_bottom_y` anyway.
                    std::cout << "Initializing n_rows\n";
                    this->n_rows = this->console_top_y - this->console_bottom_y + 1;

                    // Initialize `n_columns`.
                    // `n_columns` should be set by `activate_console_left_x` and `activate_console_right_x` anyway.
                    std::cout << "Initializing n_columns\n";
                    this->n_columns = this->console_right_x - this->console_left_x + 1;

                    this->adjust_n_columns();
                    this->adjust_n_rows();

                    // `yli::ontology::Entity` member variables begin here.
                    this->type_string = "yli::ontology::Console*";
                    this->can_be_erased = true;
                }

                Console(const Console&) = delete;            // Delete copy constructor.
                Console &operator=(const Console&) = delete; // Delete copy assignment.

                // destructor.
                ~Console();

                std::size_t get_number_of_children() const override;
                std::size_t get_number_of_descendants() const override;

                void adjust_n_columns();
                void adjust_n_rows();

                void set_input_mode(yli::input::InputMode* const input_mode);
                void add_command_callback(const std::string& command, ConsoleCommandCallback callback);
                void set_console_top_y(const uint32_t console_top_y);
                void set_console_bottom_y(const uint32_t console_bottom_y);
                void set_console_left_x(const uint32_t console_left_x);
                void set_console_right_x(const uint32_t console_right_x);
                void print_text(const std::string& text);
                void print_help();
                void render() const;

                bool enter_console();
                bool exit_console();
                bool get_in_console() const;
                void process_key_event(const SDL_KeyboardEvent& keyboard_event);

                yli::ontology::Universe* get_universe() const;

                // Public callbacks.

                // Action mode keypress callbacks begin here.

                static std::shared_ptr<yli::common::AnyValue> enter_console(
                        yli::ontology::Universe* universe,
                        yli::callback::CallbackEngine*,
                        yli::callback::CallbackObject*,
                        std::vector<yli::callback::CallbackParameter*>&,
                        std::shared_ptr<yli::common::AnyValue>);

                // Console mode keyrelease callbacks begin here.

                static std::shared_ptr<yli::common::AnyValue> release_left_control_in_console(
                        yli::callback::CallbackEngine*,
                        yli::callback::CallbackObject*,
                        std::vector<yli::callback::CallbackParameter*>&,
                        yli::ontology::Console* console);

                static std::shared_ptr<yli::common::AnyValue> release_right_control_in_console(
                        yli::callback::CallbackEngine*,
                        yli::callback::CallbackObject*,
                        std::vector<yli::callback::CallbackParameter*>&,
                        yli::ontology::Console* console);

                static std::shared_ptr<yli::common::AnyValue> release_left_alt_in_console(
                        yli::callback::CallbackEngine*,
                        yli::callback::CallbackObject*,
                        std::vector<yli::callback::CallbackParameter*>&,
                        yli::ontology::Console* console);

                static std::shared_ptr<yli::common::AnyValue> release_right_alt_in_console(
                        yli::callback::CallbackEngine*,
                        yli::callback::CallbackObject*,
                        std::vector<yli::callback::CallbackParameter*>&,
                        yli::ontology::Console* console);

                static std::shared_ptr<yli::common::AnyValue> release_left_shift_in_console(
                        yli::callback::CallbackEngine*,
                        yli::callback::CallbackObject*,
                        std::vector<yli::callback::CallbackParameter*>&,
                        yli::ontology::Console* console);

                static std::shared_ptr<yli::common::AnyValue> release_right_shift_in_console(
                        yli::callback::CallbackEngine*,
                        yli::callback::CallbackObject*,
                        std::vector<yli::callback::CallbackParameter*>&,
                        yli::ontology::Console* console);

                static std::shared_ptr<yli::common::AnyValue> enable_move_to_previous_input(
                        yli::callback::CallbackEngine*,
                        yli::callback::CallbackObject*,
                        std::vector<yli::callback::CallbackParameter*>&,
                        yli::ontology::Console* console);

                static std::shared_ptr<yli::common::AnyValue> enable_move_to_next_input(
                        yli::callback::CallbackEngine*,
                        yli::callback::CallbackObject*,
                        std::vector<yli::callback::CallbackParameter*>&,
                        yli::ontology::Console* console);

                static std::shared_ptr<yli::common::AnyValue> enable_backspace(
                        yli::callback::CallbackEngine*,
                        yli::callback::CallbackObject*,
                        std::vector<yli::callback::CallbackParameter*>&,
                        yli::ontology::Console* console);

                static std::shared_ptr<yli::common::AnyValue> enable_enter_key(
                        yli::callback::CallbackEngine*,
                        yli::callback::CallbackObject*,
                        std::vector<yli::callback::CallbackParameter*>&,
                        yli::ontology::Console* console);

                static std::shared_ptr<yli::common::AnyValue> enable_ctrl_c(
                        yli::callback::CallbackEngine*,
                        yli::callback::CallbackObject*,
                        std::vector<yli::callback::CallbackParameter*>&,
                        yli::ontology::Console* console);

                static std::shared_ptr<yli::common::AnyValue> enable_ctrl_w(
                        yli::callback::CallbackEngine*,
                        yli::callback::CallbackObject*,
                        std::vector<yli::callback::CallbackParameter*>&,
                        yli::ontology::Console* console);

                static std::shared_ptr<yli::common::AnyValue> enable_page_up(
                        yli::callback::CallbackEngine*,
                        yli::callback::CallbackObject*,
                        std::vector<yli::callback::CallbackParameter*>&,
                        yli::ontology::Console* console);

                static std::shared_ptr<yli::common::AnyValue> enable_page_down(
                        yli::callback::CallbackEngine*,
                        yli::callback::CallbackObject*,
                        std::vector<yli::callback::CallbackParameter*>&,
                        yli::ontology::Console* console);

                static std::shared_ptr<yli::common::AnyValue> enable_home(
                        yli::callback::CallbackEngine*,
                        yli::callback::CallbackObject*,
                        std::vector<yli::callback::CallbackParameter*>&,
                        yli::ontology::Console* console);

                static std::shared_ptr<yli::common::AnyValue> enable_end(
                        yli::callback::CallbackEngine*,
                        yli::callback::CallbackObject*,
                        std::vector<yli::callback::CallbackParameter*>&,
                        yli::ontology::Console* console);

                // Console mode keypress callbacks begin here.

                static std::shared_ptr<yli::common::AnyValue> exit_console(
                        yli::callback::CallbackEngine*,
                        yli::callback::CallbackObject*,
                        std::vector<yli::callback::CallbackParameter*>&,
                        yli::ontology::Console* console);

                static std::shared_ptr<yli::common::AnyValue> press_left_control_in_console(
                        yli::callback::CallbackEngine*,
                        yli::callback::CallbackObject*,
                        std::vector<yli::callback::CallbackParameter*>&,
                        yli::ontology::Console* console);

                static std::shared_ptr<yli::common::AnyValue> press_right_control_in_console(
                        yli::callback::CallbackEngine*,
                        yli::callback::CallbackObject*,
                        std::vector<yli::callback::CallbackParameter*>&,
                        yli::ontology::Console* console);

                static std::shared_ptr<yli::common::AnyValue> press_left_alt_in_console(
                        yli::callback::CallbackEngine*,
                        yli::callback::CallbackObject*,
                        std::vector<yli::callback::CallbackParameter*>&,
                        yli::ontology::Console* console);

                static std::shared_ptr<yli::common::AnyValue> press_right_alt_in_console(
                        yli::callback::CallbackEngine*,
                        yli::callback::CallbackObject*,
                        std::vector<yli::callback::CallbackParameter*>&,
                        yli::ontology::Console* console);

                static std::shared_ptr<yli::common::AnyValue> press_left_shift_in_console(
                        yli::callback::CallbackEngine*,
                        yli::callback::CallbackObject*,
                        std::vector<yli::callback::CallbackParameter*>&,
                        yli::ontology::Console* console);

                static std::shared_ptr<yli::common::AnyValue> press_right_shift_in_console(
                        yli::callback::CallbackEngine*,
                        yli::callback::CallbackObject*,
                        std::vector<yli::callback::CallbackParameter*>&,
                        yli::ontology::Console* console);

                static std::shared_ptr<yli::common::AnyValue> move_to_previous_input(
                        yli::callback::CallbackEngine*,
                        yli::callback::CallbackObject*,
                        std::vector<yli::callback::CallbackParameter*>&,
                        yli::ontology::Console* console);

                static std::shared_ptr<yli::common::AnyValue> move_to_next_input(
                        yli::callback::CallbackEngine*,
                        yli::callback::CallbackObject*,
                        std::vector<yli::callback::CallbackParameter*>&,
                        yli::ontology::Console* console);

                static std::shared_ptr<yli::common::AnyValue> backspace(
                        yli::callback::CallbackEngine*,
                        yli::callback::CallbackObject*,
                        std::vector<yli::callback::CallbackParameter*>&,
                        yli::ontology::Console* console);

                static std::shared_ptr<yli::common::AnyValue> enter_key(
                        yli::callback::CallbackEngine*,
                        yli::callback::CallbackObject*,
                        std::vector<yli::callback::CallbackParameter*>&,
                        yli::ontology::Console* console);

                static std::shared_ptr<yli::common::AnyValue> ctrl_c(
                        yli::callback::CallbackEngine*,
                        yli::callback::CallbackObject*,
                        std::vector<yli::callback::CallbackParameter*>&,
                        yli::ontology::Console* console);

                static std::shared_ptr<yli::common::AnyValue> ctrl_w(
                        yli::callback::CallbackEngine*,
                        yli::callback::CallbackObject*,
                        std::vector<yli::callback::CallbackParameter*>&,
                        yli::ontology::Console* console);

                static std::shared_ptr<yli::common::AnyValue> page_up(
                        yli::callback::CallbackEngine*,
                        yli::callback::CallbackObject*,
                        std::vector<yli::callback::CallbackParameter*>&,
                        yli::ontology::Console* console);

                static std::shared_ptr<yli::common::AnyValue> page_down(
                        yli::callback::CallbackEngine*,
                        yli::callback::CallbackObject*,
                        std::vector<yli::callback::CallbackParameter*>&,
                        yli::ontology::Console* console);

                static std::shared_ptr<yli::common::AnyValue> home(
                        yli::callback::CallbackEngine*,
                        yli::callback::CallbackObject*,
                        std::vector<yli::callback::CallbackParameter*>&,
                        yli::ontology::Console* console);

                static std::shared_ptr<yli::common::AnyValue> end(
                        yli::callback::CallbackEngine*,
                        yli::callback::CallbackObject*,
                        std::vector<yli::callback::CallbackParameter*>&,
                        yli::ontology::Console* console);

                // Console command callbacks begin here.

                static std::shared_ptr<yli::common::AnyValue> clear(
                        yli::ontology::Console* const console,
                        yli::ontology::Entity* const universe_entity,
                        const std::vector<std::string>& command_parameters);

                // Public callbacks end here.

                bool should_be_rendered;

                template<class T1>
                    friend void yli::hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue, std::size_t& number_of_children);

            private:
                void bind_to_parent();

                yli::ontology::Entity* get_parent() const override;

                static void charmods_callback(SDL_Window* window, unsigned int codepoint, int mods);

                // Callbacks end here.

                void copy_historical_input_into_current_input();
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

                yli::input::InputMode* input_mode;

                // `std::unordered_map` contains console command callbacks.
                std::unordered_map<std::string, ConsoleCommandCallback> command_callback_map;

                // This is a pointer to `yli::ontology::Universe`.
                yli::ontology::Universe* parent;

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
