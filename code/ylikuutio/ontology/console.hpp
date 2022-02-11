// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2022 Antti Nuortimo.
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

#ifndef __YLIKUUTIO_ONTOLOGY_CONSOLE_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_CONSOLE_HPP_INCLUDED

#include "entity.hpp"
#include "child_module.hpp"
#include "generic_parent_module.hpp"
#include "generic_master_module.hpp"
#include "apprentice_module.hpp"
#include "console_struct.hpp"
#include "code/ylikuutio/console/console_command_callback.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/sdl/ylikuutio_sdl.hpp"

// Include standard headers
#include <cstddef>       // std::size_t
#include <iostream>      // std::cout, std::cin, std::cerr
#include <limits>        // std::numeric_limits
#include <list>          // std::list
#include <optional>      // std::optional
#include <queue>         // std::queue
#include <stdint.h>      // uint32_t etc.
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

// `Console` works through keypress callbacks and keyrelease callbacks.
// If the action of a key should not happen many times in a very fast
// succession, some means to control the frequency is needed.
// The easiest option is to use a `bool` variable like `bool enable_action`.
//
// In the keypress callback, the value of `enable_action` is tested, and
// nothing is done if it's `false`.
//
// If `enable_action` is `true`, the corresponding action takes place,
// after which `enable_action` is set to `false`.
//
// In the keyrelease callback `enable_action` is set to `true`.
//
// All console-related functions are implemented through keypress
// callbacks and keyrelease callbacks.
//
// `Console` is an `Entity` and multiple `Console`s can be created,
// each with its own commands. It is possible to change between the
// `Console`s by activating another `Console`.

namespace yli::callback
{
    class CallbackEngine;
    class CallbackObject;
    class CallbackParameter;
}

namespace yli::data
{
    class AnyValue;
}

namespace yli::input
{
    class InputMode;
}

namespace yli::map
{
    template <typename T1>
        void print_keys_to_console(const std::unordered_map<std::string, T1>* const unordered_map_pointer, yli::ontology::Console* const console);
}

namespace yli::ontology
{
    class Universe;
    class Scene;
    class Font2D;
    class Registry;

    class Console: public yli::ontology::Entity
    {
        public:
            void bind_to_new_font_2d(yli::ontology::Font2D* const new_font_2d);

            Console(yli::ontology::Universe& universe,
                    const yli::ontology::ConsoleStruct& console_struct,
                    yli::ontology::GenericParentModule* const parent_module,
                    yli::ontology::GenericMasterModule* const generic_master_module)
                : Entity(universe, console_struct),
                child_of_universe(parent_module, this),
                parent_of_lisp_functions(this, &this->registry, "lisp_functions"),
                apprentice_of_font_2d(generic_master_module, this)
            {
                // constructor.

                this->adjust_n_columns();
                this->adjust_n_rows();

                // `yli::ontology::Entity` member variables begin here.
                this->type_string = "yli::ontology::Console*";
                this->can_be_erased = true;
            }

            Console(const Console&) = delete;            // Delete copy constructor.
            Console& operator=(const Console&) = delete; // Delete copy assignment.

            // destructor.
            ~Console();

            void activate() override;

            void adjust_n_columns();
            void adjust_n_rows();

            void set_input_mode(yli::input::InputMode* const input_mode);
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

            // Public callbacks.

            // Action mode keypress callbacks begin here.

            static std::optional<yli::data::AnyValue> enter_console(
                    yli::ontology::Universe& universe,
                    yli::callback::CallbackEngine*,
                    yli::callback::CallbackObject*,
                    std::vector<yli::callback::CallbackParameter*>&,
                    const yli::data::AnyValue&);

            // Console mode keyrelease callbacks begin here.

            static std::optional<yli::data::AnyValue> release_left_control_in_console(
                    yli::callback::CallbackEngine*,
                    yli::callback::CallbackObject*,
                    std::vector<yli::callback::CallbackParameter*>&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> release_right_control_in_console(
                    yli::callback::CallbackEngine*,
                    yli::callback::CallbackObject*,
                    std::vector<yli::callback::CallbackParameter*>&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> release_left_alt_in_console(
                    yli::callback::CallbackEngine*,
                    yli::callback::CallbackObject*,
                    std::vector<yli::callback::CallbackParameter*>&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> release_right_alt_in_console(
                    yli::callback::CallbackEngine*,
                    yli::callback::CallbackObject*,
                    std::vector<yli::callback::CallbackParameter*>&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> release_left_shift_in_console(
                    yli::callback::CallbackEngine*,
                    yli::callback::CallbackObject*,
                    std::vector<yli::callback::CallbackParameter*>&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> release_right_shift_in_console(
                    yli::callback::CallbackEngine*,
                    yli::callback::CallbackObject*,
                    std::vector<yli::callback::CallbackParameter*>&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> enable_move_to_previous_input(
                    yli::callback::CallbackEngine*,
                    yli::callback::CallbackObject*,
                    std::vector<yli::callback::CallbackParameter*>&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> enable_move_to_next_input(
                    yli::callback::CallbackEngine*,
                    yli::callback::CallbackObject*,
                    std::vector<yli::callback::CallbackParameter*>&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> enable_backspace(
                    yli::callback::CallbackEngine*,
                    yli::callback::CallbackObject*,
                    std::vector<yli::callback::CallbackParameter*>&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> enable_tab(
                    yli::callback::CallbackEngine*,
                    yli::callback::CallbackObject*,
                    std::vector<yli::callback::CallbackParameter*>&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> enable_enter_key(
                    yli::callback::CallbackEngine*,
                    yli::callback::CallbackObject*,
                    std::vector<yli::callback::CallbackParameter*>&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> enable_ctrl_c(
                    yli::callback::CallbackEngine*,
                    yli::callback::CallbackObject*,
                    std::vector<yli::callback::CallbackParameter*>&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> enable_ctrl_w(
                    yli::callback::CallbackEngine*,
                    yli::callback::CallbackObject*,
                    std::vector<yli::callback::CallbackParameter*>&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> enable_page_up(
                    yli::callback::CallbackEngine*,
                    yli::callback::CallbackObject*,
                    std::vector<yli::callback::CallbackParameter*>&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> enable_page_down(
                    yli::callback::CallbackEngine*,
                    yli::callback::CallbackObject*,
                    std::vector<yli::callback::CallbackParameter*>&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> enable_home(
                    yli::callback::CallbackEngine*,
                    yli::callback::CallbackObject*,
                    std::vector<yli::callback::CallbackParameter*>&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> enable_end(
                    yli::callback::CallbackEngine*,
                    yli::callback::CallbackObject*,
                    std::vector<yli::callback::CallbackParameter*>&,
                    yli::ontology::Console& console);

            // Console mode keypress callbacks begin here.

            static std::optional<yli::data::AnyValue> exit_console(
                    yli::callback::CallbackEngine*,
                    yli::callback::CallbackObject*,
                    std::vector<yli::callback::CallbackParameter*>&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> press_left_control_in_console(
                    yli::callback::CallbackEngine*,
                    yli::callback::CallbackObject*,
                    std::vector<yli::callback::CallbackParameter*>&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> press_right_control_in_console(
                    yli::callback::CallbackEngine*,
                    yli::callback::CallbackObject*,
                    std::vector<yli::callback::CallbackParameter*>&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> press_left_alt_in_console(
                    yli::callback::CallbackEngine*,
                    yli::callback::CallbackObject*,
                    std::vector<yli::callback::CallbackParameter*>&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> press_right_alt_in_console(
                    yli::callback::CallbackEngine*,
                    yli::callback::CallbackObject*,
                    std::vector<yli::callback::CallbackParameter*>&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> press_left_shift_in_console(
                    yli::callback::CallbackEngine*,
                    yli::callback::CallbackObject*,
                    std::vector<yli::callback::CallbackParameter*>&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> press_right_shift_in_console(
                    yli::callback::CallbackEngine*,
                    yli::callback::CallbackObject*,
                    std::vector<yli::callback::CallbackParameter*>&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> move_to_previous_input(
                    yli::callback::CallbackEngine*,
                    yli::callback::CallbackObject*,
                    std::vector<yli::callback::CallbackParameter*>&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> move_to_next_input(
                    yli::callback::CallbackEngine*,
                    yli::callback::CallbackObject*,
                    std::vector<yli::callback::CallbackParameter*>&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> backspace(
                    yli::callback::CallbackEngine*,
                    yli::callback::CallbackObject*,
                    std::vector<yli::callback::CallbackParameter*>&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> tab(
                    yli::callback::CallbackEngine*,
                    yli::callback::CallbackObject*,
                    std::vector<yli::callback::CallbackParameter*>&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> enter_key(
                    yli::callback::CallbackEngine*,
                    yli::callback::CallbackObject*,
                    std::vector<yli::callback::CallbackParameter*>&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> ctrl_c(
                    yli::callback::CallbackEngine*,
                    yli::callback::CallbackObject*,
                    std::vector<yli::callback::CallbackParameter*>&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> ctrl_w(
                    yli::callback::CallbackEngine*,
                    yli::callback::CallbackObject*,
                    std::vector<yli::callback::CallbackParameter*>&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> page_up(
                    yli::callback::CallbackEngine*,
                    yli::callback::CallbackObject*,
                    std::vector<yli::callback::CallbackParameter*>&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> page_down(
                    yli::callback::CallbackEngine*,
                    yli::callback::CallbackObject*,
                    std::vector<yli::callback::CallbackParameter*>&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> home(
                    yli::callback::CallbackEngine*,
                    yli::callback::CallbackObject*,
                    std::vector<yli::callback::CallbackParameter*>&,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> end(
                    yli::callback::CallbackEngine*,
                    yli::callback::CallbackObject*,
                    std::vector<yli::callback::CallbackParameter*>&,
                    yli::ontology::Console& console);

            // Console command callbacks begin here.

            static std::optional<yli::data::AnyValue> clear(
                    yli::ontology::Console& console);

            // Public callbacks end here.

            yli::ontology::ChildModule child_of_universe;
            yli::ontology::GenericParentModule parent_of_lisp_functions;
            yli::ontology::ApprenticeModule apprentice_of_font_2d;

            friend class yli::ontology::GenericMasterModule;

            template<typename T1>
                friend void yli::hierarchy::bind_apprentice_to_master(T1 apprentice_pointer, std::vector<T1>& apprentice_pointer_vector, std::queue<std::size_t>& free_apprenticeID_queue, std::size_t& number_of_apprenticeren);

        private:
            yli::ontology::Entity* get_parent() const override;

            yli::ontology::Scene* get_scene() const override;
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            // Callbacks end here.

            void copy_historical_input_into_current_input();
            std::string convert_current_input_into_string() const;
            void delete_character();
            void move_cursor_left();
            void move_cursor_right();
            void move_cursor_to_start_of_line();
            void move_cursor_to_end_of_line();
            void print_completions(const yli::ontology::Registry& registry, const std::string& input);

            std::vector<std::list<char>> command_history;
            std::vector<std::list<char>> console_history;

            std::list<char> current_input; // This is used for actual inputs.
            std::list<char> temp_input;    // This is used for temporary storage of new input while modifying historical inputs.
            std::list<char>::iterator cursor_it { this->current_input.begin() };

            const std::string prompt            { "$ " };

            yli::input::InputMode* input_mode   { nullptr };

            std::size_t cursor_index            { 0 }; // Name `cursor_index` is chosen to distinguish from `cursor_it`.
            std::size_t history_line_i          { std::numeric_limits<std::size_t>::max() }; // Some dummy value.
            std::size_t historical_input_i      { std::numeric_limits<std::size_t>::max() }; // Some dummy value.

            // Initialize `console_top_y` to 9.
            // `console_top_y` should be set by `activate_console_top_y` anyway.
            std::size_t console_top_y    { 9 };

            // Initialize `console_bottom_y` to 0.
            // `console_bottom_y` should be set by `activate_console_bottom_y` anyway.
            std::size_t console_bottom_y { 0 };

            // Initialize `console_left_x` to 0.
            // `console_left_x` should be set by `activate_console_left_x` anyway.
            std::size_t console_left_x   { 0 };

            // Initialize `console_right_x` to 9.
            // `console_right_x` should be set by `activate_console_right_x` anyway.
            std::size_t console_right_x  { 9 };

            // Initialize `n_rows`.
            // `n_rows` should be set by `activate_console_top_y` and `activate_console_bottom_y` anyway.
            std::size_t n_rows           { this->console_top_y - this->console_bottom_y + 1 };

            // Initialize `n_columns`.
            // `n_columns` should be set by `activate_console_left_x` and `activate_console_right_x` anyway.
            std::size_t n_columns        { this->console_right_x - this->console_left_x + 1 };

            bool in_console                 { false };
            bool can_move_to_previous_input { false };
            bool can_move_to_next_input     { false };
            bool can_backspace              { false };
            bool can_tab                    { false };
            bool can_enter_key              { false };
            bool can_ctrl_c                 { false };
            bool can_ctrl_w                 { false };
            bool can_page_up                { false };
            bool can_page_down              { false };
            bool can_home                   { false };
            bool can_end                    { false };
            bool is_left_control_pressed    { false };
            bool is_right_control_pressed   { false };
            bool is_left_alt_pressed        { false };
            bool is_right_alt_pressed       { false };
            bool is_left_shift_pressed      { false };
            bool is_right_shift_pressed     { false };
            bool in_history                 { false };
            bool in_historical_input        { false };
    };
}

#endif
