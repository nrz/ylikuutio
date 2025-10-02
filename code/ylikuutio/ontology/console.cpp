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
#include "text_struct.hpp"
#include "family_templates.hpp"
#include "callback_magic_numbers.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/data/datatype.hpp"
#include "code/ylikuutio/sdl/ylikuutio_sdl.hpp"
#include "code/ylikuutio/string/ylikuutio_string.hpp"

// Include standard headers
#include <algorithm> // std::copy etc.
#include <cstddef>   // std::size_t
#include <iostream>  // std::cerr
#include <iterator>  // std::back_inserter
#include <list>      // std::list
#include <optional>  // std::optional
#include <stdint.h>  // uint32_t etc.
#include <string>    // std::string
#include <variant>   // std::get
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
        n_rows           { this->console_top_y - this->console_bottom_y + 1 }
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
        std::list<char> text_char_list;
        std::size_t current_line_length = 0;

        for (const char& my_char : text)
        {
            if (my_char == '\n')
            {
                // A newline.
                this->console_history.emplace_back(text_char_list);
                text_char_list.clear();
                current_line_length = 0;
            }
            else if (++current_line_length <= this->n_columns)
            {
                // Normal case.
                text_char_list.emplace_back(my_char);
            }
            else
            {
                // Newline is needed due to too long line.
                this->console_history.emplace_back(text_char_list);
                text_char_list.clear();
                text_char_list.emplace_back(my_char);
                current_line_length = 1;
            }
        }

        if (text_char_list.size() > 0)
        {
            this->console_history.emplace_back(text_char_list);
        }
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
        if (!this->in_console ||
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

        // Convert new input into std::string.
        const std::size_t characters_for_line = this->universe.get_window_width() / this->universe.get_text_size();

        // Draw the console to screen using `font_2d::print_text_2d`.
        TextStruct text_struct { TextureFileFormat::PNG };
        text_struct.text_size = this->universe.get_text_size();
        text_struct.font_size = this->universe.get_font_size();

        text_struct.position.x = 0;
        text_struct.position.y = this->universe.get_window_height() - (2 * this->universe.get_text_size());
        text_struct.position.horizontal_alignment = HorizontalAlignment::LEFT;
        text_struct.position.vertical_alignment = VerticalAlignment::TOP;

        if (this->in_history)
        {
            const std::size_t history_end_i = history_line_i + this->n_rows;

            for (std::size_t history_i = history_line_i;
                    history_i < history_end_i && history_i < this->console_history.size();
                    history_i++)
            {
                std::list<char> historical_text = this->console_history.at(history_i);
                std::get<std::string>(text_struct.text) += yli::string::convert_char_container_to_std_string(
                        historical_text,
                        characters_for_line,
                        characters_for_line) +
                    "\n";
            }
        }
        else
        {
            const std::size_t n_chars_on_noncomplete_line = (this->prompt.size() + this->new_input.size()) % this->n_columns;
            const std::size_t n_lines_of_new_input = (n_chars_on_noncomplete_line > 0 ?
                    (this->prompt.size() + this->new_input.size()) / this->n_columns + 1 :
                    (this->prompt.size() + this->new_input.size()) / this->n_columns);

            if (n_lines_of_new_input > this->n_rows)
            {
                // Current input does not fit completely in the console 'window'.

                // Split new input into lines and print only n last lines,
                // where n == `this->n_rows`.
                std::list<char> new_input_with_prompt = this->new_input;
                std::list<char>::iterator it = new_input_with_prompt.begin();

                // Copy prompt into the front of the new input.
                for (const char& my_char : this->prompt)
                {
                    new_input_with_prompt.insert(it, my_char);
                }

                // Convert into a vector of lines.
                const std::vector<std::string> new_input_vector = yli::string::convert_char_container_to_std_vector_std_string(
                        new_input_with_prompt,
                        this->n_columns);

                // Print only n last lines.
                for (std::size_t i = new_input_vector.size() - this->n_rows; i < new_input_vector.size(); i++)
                {
                    std::get<std::string>(text_struct.text) += new_input_vector.at(i) + "\\n";
                }
            }
            else
            {
                const std::string new_input_string = this->convert_new_input_into_string();

                // Current input fits completely in the console 'window'.
                std::size_t history_start_i { 0 }; // Assume everything does fit in the console 'window'.

                if (this->console_history.size() + n_lines_of_new_input > this->n_rows)
                {
                    // Everything does not fit in the console 'window'.
                    history_start_i = this->console_history.size() - this->n_rows + n_lines_of_new_input;
                }

                // We are not in history so print everything to the end of the history.
                for (std::size_t history_i = history_start_i; history_i < this->console_history.size(); history_i++)
                {
                    const std::list<char> historical_text = this->console_history.at(history_i);
                    std::get<std::string>(text_struct.text) += yli::string::convert_char_container_to_std_string(
                            historical_text,
                            characters_for_line,
                            characters_for_line) +
                        "\n";
                }

                std::get<std::string>(text_struct.text) += this->convert_new_input_into_string();
            }
        }

        font_2d->print_text_2d(text_struct);
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
                !this->in_console &&
                this->master_of_input_modes.has_current_input_mode())
        {
            this->master_of_input_modes.activate_current_input_mode();

            // Do not display help screen when in console.
            this->universe.can_display_help_screen = false;

            // Mark that we're in console.
            this->universe.in_console = true;
            this->in_console = true;
            this->in_historical_input = false;
            return true;
        }

        // We did not enter the console.
        return false;
    }

    bool Console::exit_console()
    {
        if (this->in_console)
        {
            // Restore previous input mode.
            if (this->master_of_input_modes.has_current_input_mode())
            {
                this->master_of_input_modes.deactivate_current_input_mode();
            }

            // Enable display help screen when not in console.
            this->universe.can_display_help_screen = true;

            // Mark that we have exited the console.
            this->universe.in_console = false;
            this->in_console = false;

            return true;
        }
        return false;
    }

    void Console::process_key_event(const SDL_KeyboardEvent& keyboard_event)
    {
        const uint16_t modifiers = keyboard_event.keysym.mod;
        const uint16_t shift_bitmask = KMOD_LSHIFT | KMOD_RSHIFT;
        const uint16_t ctrl_alt_altgr_bitmask = KMOD_LCTRL | KMOD_RCTRL | KMOD_LALT | KMOD_RALT | KMOD_MODE;

        if (keyboard_event.state == SDL_PRESSED &&
                keyboard_event.keysym.scancode != SDL_SCANCODE_GRAVE &&
                keyboard_event.keysym.sym != SDLK_UNKNOWN &&
                keyboard_event.keysym.sym != SDLK_RETURN &&
                keyboard_event.keysym.sym != SDLK_KP_ENTER &&
                keyboard_event.keysym.sym >= 0x20 &&
                keyboard_event.keysym.sym <= 0x7f &&
                ((modifiers & ctrl_alt_altgr_bitmask) == 0) &&
                this->in_console)
        {
            this->in_history = false;

            const char keyboard_char = static_cast<char>(keyboard_event.keysym.sym);

            if ((modifiers & shift_bitmask) != 0)
            {
                // Before a support for different keyboard layouts in implemented,
                // use US QWERTY layout as reference.
                switch (keyboard_char)
                {
                    case '`':
                        this->cursor_it = this->new_input.insert(this->cursor_it, '~');
                        break;
                    case '1':
                        this->cursor_it = this->new_input.insert(this->cursor_it, '!');
                        break;
                    case '2':
                        this->cursor_it = this->new_input.insert(this->cursor_it, '@');
                        break;
                    case '3':
                        this->cursor_it = this->new_input.insert(this->cursor_it, '#');
                        break;
                    case '4':
                        this->cursor_it = this->new_input.insert(this->cursor_it, '$');
                        break;
                    case '5':
                        this->cursor_it = this->new_input.insert(this->cursor_it, '%');
                        break;
                    case '6':
                        this->cursor_it = this->new_input.insert(this->cursor_it, '^');
                        break;
                    case '7':
                        this->cursor_it = this->new_input.insert(this->cursor_it, '&');
                        break;
                    case '8':
                        this->cursor_it = this->new_input.insert(this->cursor_it, '*');
                        break;
                    case '9':
                        this->cursor_it = this->new_input.insert(this->cursor_it, '(');
                        break;
                    case '0':
                        this->cursor_it = this->new_input.insert(this->cursor_it, ')');
                        break;
                    case '-':
                        this->cursor_it = this->new_input.insert(this->cursor_it, '_');
                        break;
                    case '=':
                        this->cursor_it = this->new_input.insert(this->cursor_it, '+');
                        break;
                    case '[':
                        this->cursor_it = this->new_input.insert(this->cursor_it, '{');
                        break;
                    case ']':
                        this->cursor_it = this->new_input.insert(this->cursor_it, '}');
                        break;
                    case '\\':
                        this->cursor_it = this->new_input.insert(this->cursor_it, '|');
                        break;
                    case ';':
                        this->cursor_it = this->new_input.insert(this->cursor_it, ':');
                        break;
                    case '\'':
                        this->cursor_it = this->new_input.insert(this->cursor_it, '"');
                        break;
                    case ',':
                        this->cursor_it = this->new_input.insert(this->cursor_it, '<');
                        break;
                    case '.':
                        this->cursor_it = this->new_input.insert(this->cursor_it, '>');
                        break;
                    case '/':
                        this->cursor_it = this->new_input.insert(this->cursor_it, '?');
                        break;
                    default:
                        if (keyboard_char >= 'a' && keyboard_char <= 'z')
                        {
                            this->cursor_it = this->new_input.insert(this->cursor_it, keyboard_char - ('a' - 'A'));
                        }
                        break;
                }
            }
            else
            {
                this->cursor_it = this->new_input.insert(this->cursor_it, keyboard_char);
            }

            ++this->cursor_it;
            this->cursor_index++;
        }
    }

    GenericParentModule* Console::get_generic_parent_module(const int type)
    {
        if (type == yli::data::Datatype::CONSOLE_CALLBACK_ENGINE)
        {
            return &this->parent_of_console_callback_engines;
        }
        else if (type == yli::data::Datatype::LISP_FUNCTION)
        {
            return &this->parent_of_lisp_functions;
        }

        return nullptr;
    }

    void Console::copy_historical_input_into_new_input()
    {
        if (this->in_console)
        {
            // Copy selected historical input into new input.
            this->new_input.clear();
            std::copy(this->command_history.at(this->historical_input_i).begin(),
                    this->command_history.at(this->historical_input_i).end(),
                    std::back_inserter(this->new_input));
        }
    }

    std::string Console::convert_new_input_into_string() const
    {
        const std::size_t characters_for_line = this->universe.get_window_width() / this->universe.get_text_size();

        return this->prompt + yli::string::convert_char_container_to_std_string(
                this->new_input,
                characters_for_line - this->prompt.size(), // First line is shorter due to space taken by the prompt.
                characters_for_line);                      // The rest lines have full length.
    }

    void Console::delete_character()
    {
        if (this->in_console)
        {
            this->new_input.erase(this->cursor_it);
        }
    }

    void Console::move_cursor_left()
    {
        if (this->in_console)
        {
            this->in_history = false;

            if (this->cursor_it != this->new_input.begin())
            {
                --this->cursor_it;
                this->cursor_index--;
            }
        }
    }

    void Console::move_cursor_right()
    {
        if (this->in_console)
        {
            this->in_history = false;

            if (this->cursor_it != this->new_input.end())
            {
                ++this->cursor_it;
                this->cursor_index++;
            }
        }
    }

    void Console::move_cursor_to_start_of_line()
    {
        if (this->in_console)
        {
            this->in_history = false;
            this->cursor_it = this->new_input.begin();
            this->cursor_index = 0;
        }
    }

    void Console::move_cursor_to_end_of_line()
    {
        if (this->in_console)
        {
            this->in_history = false;
            this->cursor_it = this->new_input.end();
            this->cursor_index = this->new_input.size();
        }
    }

    void Console::print_completions(const Registry& registry, const std::string& input)
    {
        if (registry.get_number_of_completions(input) > 1)
        {
            this->print_text(this->convert_new_input_into_string());

            const std::vector<std::string> completions = registry.get_completions(input);

            for (const std::string& completion : completions)
            {
                this->print_text(completion);
            }
        }
    }

    // Getters for unit tests and for building upon `Console`.

    const std::list<char>& Console::get_new_input() const
    {
        return this->new_input;
    }

    const std::list<char>& Console::get_temp_input() const
    {
        return this->temp_input;
    }

    const std::string& Console::get_prompt() const
    {
        return this->prompt;
    }

    InputMode* Console::get_input_mode() const
    {
        return this->master_of_input_modes.get_current_input_mode();
    }

    std::size_t Console::get_cursor_index() const
    {
        return this->cursor_index;
    }

    std::size_t Console::get_history_line_i() const
    {
        return this->history_line_i;
    }

    std::size_t Console::get_historical_input_i() const
    {
        return this->historical_input_i;
    }

    std::size_t Console::get_console_left_x() const
    {
        return this->console_left_x;
    }

    std::size_t Console::get_console_right_x() const
    {
        return this->console_right_x;
    }

    std::size_t Console::get_console_top_y() const
    {
        return this->console_top_y;
    }

    std::size_t Console::get_console_bottom_y() const
    {
        return this->console_bottom_y;
    }

    std::size_t Console::get_n_columns() const
    {
        return this->n_columns;
    }

    std::size_t Console::get_n_rows() const
    {
        return this->n_rows;
    }

    bool Console::get_in_console() const
    {
        return this->in_console;
    }

    bool Console::get_can_move_to_previous_input() const
    {
        return this->can_move_to_previous_input;
    }

    bool Console::get_can_move_to_next_input() const
    {
        return this->can_move_to_next_input;
    }

    bool Console::get_can_backspace() const
    {
        return this->can_backspace;
    }

    bool Console::get_can_tab() const
    {
        return this->can_tab;
    }

    bool Console::get_can_enter_key() const
    {
        return this->can_enter_key;
    }

    bool Console::get_can_ctrl_c() const
    {
        return this->can_ctrl_c;
    }

    bool Console::get_can_ctrl_w() const
    {
        return this->can_ctrl_w;
    }

    bool Console::get_can_page_up() const
    {
        return this->can_page_up;
    }

    bool Console::get_can_page_down() const
    {
        return this->can_page_down;
    }

    bool Console::get_can_home() const
    {
        return this->can_home;
    }

    bool Console::get_can_end() const
    {
        return this->can_end;
    }

    bool Console::get_is_left_control_pressed() const
    {
        return this->is_left_control_pressed;
    }

    bool Console::get_is_right_control_pressed() const
    {
        return this->is_right_control_pressed;
    }

    bool Console::get_is_left_alt_pressed() const
    {
        return this->is_left_alt_pressed;
    }

    bool Console::get_is_right_alt_pressed() const
    {
        return this->is_right_alt_pressed;
    }

    bool Console::get_is_left_shift_pressed() const
    {
        return this->is_left_shift_pressed;
    }

    bool Console::get_is_right_shift_pressed() const
    {
        return this->is_right_shift_pressed;
    }

    bool Console::get_in_history() const
    {
        return this->in_history;
    }

    bool Console::get_in_historical_input() const
    {
        return this->in_historical_input;
    }

    // Console command callbacks begin here.

    std::optional<yli::data::AnyValue> Console::clear(
            Console& console)
    {
        console.in_history = false;
        console.in_historical_input = false;
        console.history_line_i = 0;
        console.historical_input_i = 0;
        console.command_history.clear();
        console.console_history.clear();
        console.new_input.clear();

        const uint32_t clear_console_magic_number = CallbackMagicNumber::CLEAR_CONSOLE;
        return yli::data::AnyValue(clear_console_magic_number);
    }

    // Public callbacks end here.
}
