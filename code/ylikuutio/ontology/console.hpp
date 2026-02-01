// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2026 Antti Nuortimo.
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
#include "code/ylikuutio/console/console_logic_module.hpp"
#include "code/ylikuutio/console/completion_module.hpp"
#include "code/ylikuutio/console/text_input.hpp"
#include "code/ylikuutio/console/text_input_history.hpp"
#include "code/ylikuutio/console/scrollback_buffer.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/sdl/ylikuutio_sdl.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
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
    class LispFunction;
    struct ConsoleStruct;

    using yli::console::TextInput;
    using yli::console::TextInputHistory;
    using yli::console::ScrollbackBuffer;
    using yli::console::ConsoleLogicModule;
    using yli::console::CompletionModule;

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

            void set_input_mode(InputMode* const input_mode);
            void print_text(const std::string& text);
            void print_help();
            void render(const Scene* const) const;

            bool enter_console();
            bool exit_console();
            void process_text_input(const SDL_TextInputEvent& text_input_event);

            template<typename ChildType>
                GenericParentModule* get_generic_parent_module() = delete;

            template<typename ApprenticeType>
                GenericMasterModule* get_generic_master_module() = delete;

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

        public:
            void copy_historical_input_into_temp_input();
            void delete_character();
            void move_cursor_left();
            void move_cursor_right();
            void move_cursor_to_start_of_line();
            void move_cursor_to_end_of_line();
            void print_completions(const Registry& registry, const std::string& input);

            // Getters for unit tests and for building upon `Console`.

        public:
            const std::string& get_prompt() const;

            InputMode* get_input_mode() const;

            // Getters end here.

            const uint32_t console_left_x;
            const uint32_t console_right_x;
            const uint32_t console_top_y;
            const uint32_t console_bottom_y;

            const uint32_t n_columns;
            const uint32_t n_rows;

            TextInput new_input;  // This is used for new inputs.
            TextInput temp_input; // This is used as copy of a unchanged historical input, for editing.
            TextInputHistory command_history;
            ScrollbackBuffer scrollback_buffer;
            ConsoleLogicModule console_logic_module;
            CompletionModule completion_module;
    };

    template<>
        inline GenericParentModule* Console::get_generic_parent_module<ConsoleCallbackEngine>()
        {
            return &this->parent_of_console_callback_engines;
        }

    template<>
        inline GenericParentModule* Console::get_generic_parent_module<LispFunction>()
        {
            return &this->parent_of_lisp_functions;
        }

    template<>
        inline GenericMasterModule* Console::get_generic_master_module<InputMode>()
        {
            return &this->master_of_input_modes;
        }
}

#endif
