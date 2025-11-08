// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2025 Antti Nuortimo.
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

#include "console.hpp"
#include "apprentice_module.hpp"
#include "universe.hpp"
#include "font_2d.hpp"
#include "registry.hpp"
#include "horizontal_alignment.hpp"
#include "vertical_alignment.hpp"
#include "console_struct.hpp"
#include "texture_file_format.hpp"
#include "print_console_struct.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/console/console_state.hpp"
#include "code/ylikuutio/console/text_input_type.hpp"
#include "code/ylikuutio/console/text_line.hpp"
#include "code/ylikuutio/console/text_input.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/sdl/ylikuutio_sdl.hpp"

// Include standard headers
#include <cstddef>   // std::size_t
#include <iostream>  // std::cerr
#include <optional>  // std::optional
#include <stdint.h>  // uint32_t etc.
#include <string>    // std::string
#include <vector>    // std::vector

namespace yli::core
{
    class Application;
}

namespace yli::ontology
{
    class GenericParentModule;
    class GenericMasterModule;
    class Entity;
    class Scene;

    using yli::console::TextLine;
    using yli::console::TextInput;
    using yli::console::TextInputType;

    std::optional<yli::data::AnyValue> Console::bind_to_new_font_2d(
            Console& console,
            Font2d& new_font_2d) noexcept
    {
        // Set pointer to `console` to `nullptr`, set font according to the input,
        // and request a new apprenticeID from `new_font_2d`.

        // Master and apprentice must belong to the same `Scene`,
        // if both belong to some `Scene`, and not `Ecosystem`.
        if (console.get_scene() == new_font_2d.get_scene() ||
                console.get_scene() == nullptr ||
                new_font_2d.get_scene() == nullptr)
        {
            console.apprentice_of_font_2d.unbind_and_bind_to_new_generic_master_module(
                    &new_font_2d.master_of_consoles);
        }
        else
        {
            std::cerr << "ERROR: `Console::bind_to_new_font_2d`: master and apprentice can not belong to different `Scene`s!\n";
        }

        return std::nullopt;
    }

    Console::Console(
            yli::core::Application& application,
            Universe& universe,
            const ConsoleStruct& console_struct,
            GenericParentModule* const universe_parent_module,
            GenericMasterModule* const font_2d_master_module)
        : Entity(application, universe, console_struct),
        child_of_universe(universe_parent_module, *this),
        parent_of_console_callback_engines(
                *this,
                this->registry,
                "console_callback_engines"),
        parent_of_lisp_functions(
                *this,
                this->registry,
                "lisp_functions"),
        apprentice_of_font_2d(font_2d_master_module, this),
        master_of_input_modes(this, &this->registry, "input_modes"),
        console_left_x   { console_struct.left_x },
        console_right_x  { console_struct.right_x },
        console_top_y    { console_struct.top_y },
        console_bottom_y { console_struct.bottom_y },
        n_columns        { this->console_right_x - this->console_left_x + 1 },
        n_rows           { this->console_top_y - this->console_bottom_y + 1 },
        new_input            { TextInputType::NEW_INPUT },
        temp_input           { TextInputType::TEMP_INPUT },
        command_history      {},
        scrollback_buffer    { this->n_columns, this->n_rows },
        console_logic_module { this->new_input, this->temp_input, this->command_history, this->scrollback_buffer, this->n_columns, this->n_rows },
        completion_module    { *this }
    {
        // `Entity` member variables begin here.
        this->type_string = "yli::ontology::Console*";
        this->can_be_erased = true;
    }

    Console::~Console()
    {
        this->exit_console();

        if (this->universe.get_active_console() == this)
        {
            this->universe.set_active_console(nullptr);
        }
    }

    void Console::set_input_mode(InputMode* const input_mode)
    {
        this->master_of_input_modes.set_current_input_mode(input_mode);
    }

    void Console::print_text(const std::string& text)
    {
        // This function is to be called from console command callbacks to print text on console.
        // Please note that it is not necessary to be in console to be able to print in console.
        this->scrollback_buffer.add_to_buffer(TextLine(text));
    }

    void Console::print_help()
    {
        this->print_text("TODO: help text here");
    }

    void Console::activate()
    {
        if (this->universe.get_active_console() != nullptr)
        {
            this->universe.get_active_console()->exit_console();
        }

        this->universe.set_active_console(this);
        this->enter_console();
    }

    void Console::render(const Scene* const) const
    {
        if (!this->console_logic_module.get_active_in_console() ||
                !this->should_render ||
                this->universe.get_active_console() != this)
        {
            return;
        }

        Font2d* const font_2d = static_cast<Font2d*>(
                this->apprentice_of_font_2d.get_master());

        if (font_2d == nullptr)
        {
            return;
        }

        const yli::console::TextInput* const visible_input = this->console_logic_module.get_visible_input();

        if (visible_input == nullptr)
        {
            return;
        }

        // Number of lines there are in total in the input that is currently visible (not all lines might be visible).
        const std::optional<std::size_t> maybe_n_lines_of_total_visible_input = this->console_logic_module.get_n_lines_of_visible_input();

        if (!maybe_n_lines_of_total_visible_input.has_value())
        {
            return;
        }

        const std::size_t n_lines_of_total_visible_input = *maybe_n_lines_of_total_visible_input;

        // Actual number of visible lines to be rendered can not exceed number of rows available.
        const std::size_t n_lines_of_visible_input = (n_lines_of_total_visible_input < this->n_rows ? n_lines_of_total_visible_input : this->n_rows);
        const std::size_t n_lines_of_scrollback_buffer_view = this->n_rows - n_lines_of_visible_input;

        // Draw the console to screen using `font_2d::print_console`.
        const bool is_in_scrollback_buffer = this->console_logic_module.get() & yli::console::in_scrollback_buffer;
        PrintConsoleStruct print_console_struct(
                (is_in_scrollback_buffer ?
                 (this->scrollback_buffer.get_view(this->scrollback_buffer.get_buffer_index(), this->n_rows)) :
                 (this->scrollback_buffer.get_view_to_last(n_lines_of_scrollback_buffer_view))),
                (is_in_scrollback_buffer ?
                 nullptr :
                 this->console_logic_module.get_visible_input()));
        print_console_struct.position.x = 0;
        print_console_struct.position.y = this->universe.get_window_height() - (2 * this->universe.get_text_size());
        print_console_struct.position.horizontal_alignment = HorizontalAlignment::LEFT;
        print_console_struct.position.vertical_alignment = VerticalAlignment::TOP;
        print_console_struct.font_size = this->universe.get_font_size();
        print_console_struct.prompt = this->get_prompt();

        font_2d->print_console(print_console_struct);
    }

    Entity* Console::get_parent() const
    {
        return this->child_of_universe.get_parent();
    }

    Scene* Console::get_scene() const
    {
        // `Console` does not belong in any `Scene`.
        return nullptr;
    }

    std::size_t Console::get_number_of_apprentices() const
    {
        return this->master_of_input_modes.get_number_of_apprentices();
    }

    std::size_t Console::get_number_of_children() const
    {
        return this->parent_of_console_callback_engines.get_number_of_children() +
            this->parent_of_lisp_functions.get_number_of_children();
    }

    std::size_t Console::get_number_of_descendants() const
    {
        return yli::ontology::get_number_of_descendants(this->parent_of_console_callback_engines.child_pointer_vector) +
            yli::ontology::get_number_of_descendants(this->parent_of_lisp_functions.child_pointer_vector);
    }

    bool Console::enter_console()
    {
        if (this->universe.get_active_console() == this &&
                !this->console_logic_module.get_active_in_console() &&
                this->master_of_input_modes.has_current_input_mode())
        {
            this->master_of_input_modes.activate_current_input_mode();

            // Do not display help screen when in console.
            this->universe.can_display_help_screen = false;

            // Mark that we're in console.
            this->console_logic_module.activate();
            this->universe.in_console = true;
            return true;
        }

        // We did not enter the console.
        return false;
    }

    bool Console::exit_console()
    {
        if (this->console_logic_module.get_active_in_console()) [[likely]]
        {
            // Restore previous input mode.
            if (this->master_of_input_modes.has_current_input_mode()) [[likely]]
            {
                this->master_of_input_modes.deactivate_current_input_mode();
            }

            // Enable display help screen when not in console.
            this->universe.can_display_help_screen = true;

            // Mark that we have exited the console.
            this->universe.in_console = false;
            this->console_logic_module.deactivate();

            return true;
        }
        return false;
    }

    void Console::process_key_event(const SDL_KeyboardEvent& keyboard_event)
    {
        const uint16_t modifiers = keyboard_event.mod;
        const uint16_t shift_bitmask = SDL_KMOD_LSHIFT | SDL_KMOD_RSHIFT;
        const uint16_t ctrl_alt_altgr_bitmask = SDL_KMOD_LCTRL | SDL_KMOD_RCTRL | SDL_KMOD_LALT | SDL_KMOD_RALT | SDL_KMOD_MODE;

        if (keyboard_event.down &&
                keyboard_event.scancode != SDL_SCANCODE_GRAVE &&
                keyboard_event.key != SDLK_UNKNOWN &&
                keyboard_event.key != SDLK_RETURN &&
                keyboard_event.key != SDLK_KP_ENTER &&
                keyboard_event.key >= 0x20 &&
                keyboard_event.key <= 0x7f &&
                ((modifiers & ctrl_alt_altgr_bitmask) == 0) &&
                this->console_logic_module.get_active_in_console())
        {
            TextInput* const active_input = this->console_logic_module.edit_input();

            if (active_input == nullptr) [[unlikely]]
            {
                return;
            }

            const char keyboard_char = static_cast<char>(keyboard_event.key);

            if ((modifiers & shift_bitmask) != 0)
            {
                // Before a support for different keyboard layouts in implemented,
                // use US QWERTY layout as reference.
                switch (keyboard_char)
                {
                    case '`':
                        active_input->add_character('~');
                        break;
                    case '1':
                        active_input->add_character('!');
                        break;
                    case '2':
                        active_input->add_character('@');
                        break;
                    case '3':
                        active_input->add_character('#');
                        break;
                    case '4':
                        active_input->add_character('$');
                        break;
                    case '5':
                        active_input->add_character('%');
                        break;
                    case '6':
                        active_input->add_character('^');
                        break;
                    case '7':
                        active_input->add_character('&');
                        break;
                    case '8':
                        active_input->add_character('*');
                        break;
                    case '9':
                        active_input->add_character('(');
                        break;
                    case '0':
                        active_input->add_character(')');
                        break;
                    case '-':
                        active_input->add_character('_');
                        break;
                    case '=':
                        active_input->add_character('+');
                        break;
                    case '[':
                        active_input->add_character('{');
                        break;
                    case ']':
                        active_input->add_character('}');
                        break;
                    case '\\':
                        active_input->add_character('|');
                        break;
                    case ';':
                        active_input->add_character(':');
                        break;
                    case '\'':
                        active_input->add_character('"');
                        break;
                    case ',':
                        active_input->add_character('<');
                        break;
                    case '.':
                        active_input->add_character('>');
                        break;
                    case '/':
                        active_input->add_character('?');
                        break;
                    default:
                        if (keyboard_char >= 'a' && keyboard_char <= 'z')
                        {
                            active_input->add_character(keyboard_char - ('a' - 'A'));
                        }
                        break;
                }
            }
            else
            {
                active_input->add_character(keyboard_char);
            }
        }
    }

    void Console::copy_historical_input_into_temp_input()
    {
        const TextInput* const historical_input = this->command_history.get();

        if (historical_input == nullptr) [[unlikely]]
        {
            return;
        }

        // Copy selected historical input into temp input.
        this->temp_input.clear();
        this->temp_input = *historical_input;
    }

    void Console::delete_character()
    {
        if (this->console_logic_module.get_active_in_console()) [[likely]]
        {
            TextInput* const active_input = this->console_logic_module.edit_input();

            if (active_input != nullptr) [[likely]]
            {
                active_input->delete_character();
            }
        }
    }

    void Console::move_cursor_left()
    {
        if (this->console_logic_module.get_active_in_console()) [[likely]]
        {
            TextInput* const active_input = this->console_logic_module.edit_input();

            if (active_input != nullptr) [[likely]]
            {
                active_input->move_cursor_left();
            }
        }
    }

    void Console::move_cursor_right()
    {
        if (this->console_logic_module.get_active_in_console()) [[likely]]
        {
            TextInput* const active_input = this->console_logic_module.edit_input();

            if (active_input != nullptr) [[likely]]
            {
                active_input->move_cursor_right();
            }
        }
    }

    void Console::move_cursor_to_start_of_line()
    {
        if (this->console_logic_module.get_active_in_console()) [[likely]]
        {
            TextInput* const active_input = this->console_logic_module.edit_input();

            if (active_input != nullptr) [[likely]]
            {
                active_input->move_cursor_to_start_of_line();
            }
        }
    }

    void Console::move_cursor_to_end_of_line()
    {
        if (this->console_logic_module.get_active_in_console()) [[likely]]
        {
            TextInput* const active_input = this->console_logic_module.edit_input();

            if (active_input != nullptr) [[likely]]
            {
                active_input->move_cursor_to_end_of_line();
            }
        }
    }

    void Console::print_completions(const Registry& registry, const std::string& input)
    {
        if (registry.get_number_of_completions(input) > 1)
        {
            TextInput* const active_input = this->console_logic_module.edit_input();

            if (active_input == nullptr) [[unlikely]]
            {
                return;
            }

            this->print_text(active_input->data());

            const std::vector<std::string> completions = registry.get_completions(input);

            for (const std::string& completion : completions)
            {
                this->print_text(completion);
            }
        }
    }

    // Getters for unit tests and for building upon `Console`.

    const std::string& Console::get_prompt() const
    {
        return this->console_logic_module.prompt;
    }

    InputMode* Console::get_input_mode() const
    {
        return this->master_of_input_modes.get_current_input_mode();
    }
}
