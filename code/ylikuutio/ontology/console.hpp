// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2024 Antti Nuortimo.
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

#ifndef YLIKUUTIO_ONTOLOGY_CONSOLE_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_CONSOLE_HPP_INCLUDED

#include "entity.hpp"
#include "child_module.hpp"
#include "generic_parent_module.hpp"
#include "apprentice_module.hpp"
#include "master_of_input_modes_module.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/sdl/ylikuutio_sdl.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <limits>   // std::numeric_limits
#include <list>     // std::list
#include <optional> // std::optional
#include <queue>    // std::queue
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

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

namespace yli::core
{
    class Application;
}

namespace yli::memory
{
    template<typename T1, std::size_t DataSize>
        class MemoryStorage;
}

namespace yli::ontology
{
    class Registry;
    class GenericMasterModule;
    class Universe;
    class CallbackEngine;
    class CallbackObject;
    class CallbackParameter;
    class Scene;
    class Font2d;
    class InputMode;
    class ConsoleCallbackEngine;
    class ConsoleCallbackObject;
    struct ConsoleStruct;

    class Console final : public Entity
    {
        public:
            // Set pointer to `console` to `nullptr`, set font according to the input,
            // and request a new apprenticeID from `new_font_2d`.
            static std::optional<yli::data::AnyValue> bind_to_new_font_2d(
                    Console& console,
                    Font2d& new_font_2d) noexcept;

        private:
            Console(
                    yli::core::Application& application,
                    Universe& universe,
                    const ConsoleStruct& console_struct,
                    GenericParentModule* const universe_parent_module,
                    GenericMasterModule* const font_2d_master_module);

            ~Console();

        public:
            Console(const Console&) = delete;            // Delete copy constructor.
            Console& operator=(const Console&) = delete; // Delete copy assignment.

            void activate() override;

            void adjust_n_columns();
            void adjust_n_rows();

            void set_input_mode(InputMode* const input_mode);
            void set_console_top_y(const uint32_t console_top_y);
            void set_console_bottom_y(const uint32_t console_bottom_y);
            void set_console_left_x(const uint32_t console_left_x);
            void set_console_right_x(const uint32_t console_right_x);
            void print_text(const std::string& text);
            void print_help();
            void render(const Scene* const) const;

            bool enter_console();
            bool exit_console();
            void process_key_event(const SDL_KeyboardEvent& keyboard_event);

            GenericParentModule* get_generic_parent_module(const int type);

            template<typename ApprenticeType>
                GenericMasterModule* get_generic_master_module() = delete;

            // Public callbacks.

            // Action mode keypress callbacks begin here.

            static std::optional<yli::data::AnyValue> enter_console(
                    Universe& universe,
                    CallbackEngine*,
                    CallbackObject*,
                    GenericParentModule&,
                    const yli::data::AnyValue&);

            // Console mode keyrelease callbacks begin here.

            static std::optional<yli::data::AnyValue> release_left_control_in_console(
                    ConsoleCallbackEngine*,
                    ConsoleCallbackObject*,
                    GenericParentModule&,
                    Console& console);

            static std::optional<yli::data::AnyValue> release_right_control_in_console(
                    ConsoleCallbackEngine*,
                    ConsoleCallbackObject*,
                    GenericParentModule&,
                    Console& console);

            static std::optional<yli::data::AnyValue> release_left_alt_in_console(
                    ConsoleCallbackEngine*,
                    ConsoleCallbackObject*,
                    GenericParentModule&,
                    Console& console);

            static std::optional<yli::data::AnyValue> release_right_alt_in_console(
                    ConsoleCallbackEngine*,
                    ConsoleCallbackObject*,
                    GenericParentModule&,
                    Console& console);

            static std::optional<yli::data::AnyValue> release_left_shift_in_console(
                    ConsoleCallbackEngine*,
                    ConsoleCallbackObject*,
                    GenericParentModule&,
                    Console& console);

            static std::optional<yli::data::AnyValue> release_right_shift_in_console(
                    ConsoleCallbackEngine*,
                    ConsoleCallbackObject*,
                    GenericParentModule&,
                    Console& console);

            static std::optional<yli::data::AnyValue> enable_move_to_previous_input(
                    ConsoleCallbackEngine*,
                    ConsoleCallbackObject*,
                    GenericParentModule&,
                    Console& console);

            static std::optional<yli::data::AnyValue> enable_move_to_next_input(
                    ConsoleCallbackEngine*,
                    ConsoleCallbackObject*,
                    GenericParentModule&,
                    Console& console);

            static std::optional<yli::data::AnyValue> enable_backspace(
                    ConsoleCallbackEngine*,
                    ConsoleCallbackObject*,
                    GenericParentModule&,
                    Console& console);

            static std::optional<yli::data::AnyValue> enable_tab(
                    ConsoleCallbackEngine*,
                    ConsoleCallbackObject*,
                    GenericParentModule&,
                    Console& console);

            static std::optional<yli::data::AnyValue> enable_enter_key(
                    ConsoleCallbackEngine*,
                    ConsoleCallbackObject*,
                    GenericParentModule&,
                    Console& console);

            static std::optional<yli::data::AnyValue> enable_ctrl_c(
                    ConsoleCallbackEngine*,
                    ConsoleCallbackObject*,
                    GenericParentModule&,
                    Console& console);

            static std::optional<yli::data::AnyValue> enable_ctrl_w(
                    ConsoleCallbackEngine*,
                    ConsoleCallbackObject*,
                    GenericParentModule&,
                    Console& console);

            static std::optional<yli::data::AnyValue> enable_page_up(
                    ConsoleCallbackEngine*,
                    ConsoleCallbackObject*,
                    GenericParentModule&,
                    Console& console);

            static std::optional<yli::data::AnyValue> enable_page_down(
                    ConsoleCallbackEngine*,
                    ConsoleCallbackObject*,
                    GenericParentModule&,
                    Console& console);

            static std::optional<yli::data::AnyValue> enable_home(
                    ConsoleCallbackEngine*,
                    ConsoleCallbackObject*,
                    GenericParentModule&,
                    Console& console);

            static std::optional<yli::data::AnyValue> enable_end(
                    ConsoleCallbackEngine*,
                    ConsoleCallbackObject*,
                    GenericParentModule&,
                    Console& console);

            // Console mode keypress callbacks begin here.

            static std::optional<yli::data::AnyValue> exit_console(
                    ConsoleCallbackEngine*,
                    ConsoleCallbackObject*,
                    GenericParentModule&,
                    Console& console);

            static std::optional<yli::data::AnyValue> press_left_control_in_console(
                    ConsoleCallbackEngine*,
                    ConsoleCallbackObject*,
                    GenericParentModule&,
                    Console& console);

            static std::optional<yli::data::AnyValue> press_right_control_in_console(
                    ConsoleCallbackEngine*,
                    ConsoleCallbackObject*,
                    GenericParentModule&,
                    Console& console);

            static std::optional<yli::data::AnyValue> press_left_alt_in_console(
                    ConsoleCallbackEngine*,
                    ConsoleCallbackObject*,
                    GenericParentModule&,
                    Console& console);

            static std::optional<yli::data::AnyValue> press_right_alt_in_console(
                    ConsoleCallbackEngine*,
                    ConsoleCallbackObject*,
                    GenericParentModule&,
                    Console& console);

            static std::optional<yli::data::AnyValue> press_left_shift_in_console(
                    ConsoleCallbackEngine*,
                    ConsoleCallbackObject*,
                    GenericParentModule&,
                    Console& console);

            static std::optional<yli::data::AnyValue> press_right_shift_in_console(
                    ConsoleCallbackEngine*,
                    ConsoleCallbackObject*,
                    GenericParentModule&,
                    Console& console);

            static std::optional<yli::data::AnyValue> move_to_previous_input(
                    ConsoleCallbackEngine*,
                    ConsoleCallbackObject*,
                    GenericParentModule&,
                    Console& console);

            static std::optional<yli::data::AnyValue> move_to_next_input(
                    ConsoleCallbackEngine*,
                    ConsoleCallbackObject*,
                    GenericParentModule&,
                    Console& console);

            static std::optional<yli::data::AnyValue> backspace(
                    ConsoleCallbackEngine*,
                    ConsoleCallbackObject*,
                    GenericParentModule&,
                    Console& console);

            static std::optional<yli::data::AnyValue> tab(
                    ConsoleCallbackEngine*,
                    ConsoleCallbackObject*,
                    GenericParentModule&,
                    Console& console);

            static std::optional<yli::data::AnyValue> enter_key(
                    ConsoleCallbackEngine*,
                    ConsoleCallbackObject*,
                    GenericParentModule&,
                    Console& console);

            static std::optional<yli::data::AnyValue> ctrl_c(
                    ConsoleCallbackEngine*,
                    ConsoleCallbackObject*,
                    GenericParentModule&,
                    Console& console);

            static std::optional<yli::data::AnyValue> ctrl_w(
                    ConsoleCallbackEngine*,
                    ConsoleCallbackObject*,
                    GenericParentModule&,
                    Console& console);

            static std::optional<yli::data::AnyValue> page_up(
                    ConsoleCallbackEngine*,
                    ConsoleCallbackObject*,
                    GenericParentModule&,
                    Console& console);

            static std::optional<yli::data::AnyValue> page_down(
                    ConsoleCallbackEngine*,
                    ConsoleCallbackObject*,
                    GenericParentModule&,
                    Console& console);

            static std::optional<yli::data::AnyValue> home(
                    ConsoleCallbackEngine*,
                    ConsoleCallbackObject*,
                    GenericParentModule&,
                    Console& console);

            static std::optional<yli::data::AnyValue> end(
                    ConsoleCallbackEngine*,
                    ConsoleCallbackObject*,
                    GenericParentModule&,
                    Console& console);

            // Console command callbacks begin here.

            static std::optional<yli::data::AnyValue> clear(
                    Console& console);

            // Public callbacks end here.

            template<typename T1, std::size_t DataSize>
                friend class yli::memory::MemoryStorage;

            ChildModule child_of_universe;
            GenericParentModule parent_of_console_callback_engines;
            GenericParentModule parent_of_lisp_functions;
            ApprenticeModule apprentice_of_font_2d;
            MasterOfInputModesModule master_of_input_modes;

            friend class GenericMasterModule;

            template<typename T1>
                friend void yli::hierarchy::bind_apprentice_to_master(
                        T1& apprentice,
                        std::vector<T1*>& apprentice_pointer_vector,
                        std::queue<std::size_t>& free_apprenticeID_queue,
                        std::size_t& number_of_apprentices) noexcept;

        private:
            Entity* get_parent() const override;

        public:
            Scene* get_scene() const override;

            std::size_t get_number_of_apprentices() const;

        private:
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
            void print_completions(const Registry& registry, const std::string& input);

            // Getters for unit tests and for building upon `Console`.

        public:
            const std::list<char>& get_current_input() const;
            const std::list<char>& get_temp_input() const;

            const std::string& get_prompt() const;

            InputMode* get_input_mode() const;
            std::size_t get_cursor_index() const;
            std::size_t get_history_line_i() const;
            std::size_t get_historical_input_i() const;
            std::size_t get_console_top_y() const;
            std::size_t get_console_bottom_y() const;
            std::size_t get_console_left_x() const;
            std::size_t get_console_right_x() const;
            std::size_t get_n_rows() const;
            std::size_t get_n_columns() const;

            bool get_in_console() const;
            bool get_can_move_to_previous_input() const;
            bool get_can_move_to_next_input() const;
            bool get_can_backspace() const;
            bool get_can_tab() const;
            bool get_can_enter_key() const;
            bool get_can_ctrl_c() const;
            bool get_can_ctrl_w() const;
            bool get_can_page_up() const;
            bool get_can_page_down() const;
            bool get_can_home() const;
            bool get_can_end() const;
            bool get_is_left_control_pressed() const;
            bool get_is_right_control_pressed() const;
            bool get_is_left_alt_pressed() const;
            bool get_is_right_alt_pressed() const;
            bool get_is_left_shift_pressed() const;
            bool get_is_right_shift_pressed() const;
            bool get_in_history() const;
            bool get_in_historical_input() const;

            // Getters end here.

        private:
            std::vector<std::list<char>> command_history;
            std::vector<std::list<char>> console_history;

            std::list<char> current_input; // This is used for actual inputs.
            std::list<char> temp_input;    // This is used for temporary storage of new input while modifying historical inputs.
            std::list<char>::iterator cursor_it { this->current_input.begin() };

            const std::string prompt            { "$ " };

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

    template<>
        inline GenericMasterModule* Console::get_generic_master_module<InputMode>()
        {
            return &this->master_of_input_modes;
        }
}

#endif
