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

#include "text_input.hpp"
#include "text_input_type.hpp"
#include "console_state.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <optional> // std::optional
#include <string>   // std::string
#include <string_view> // std::string_view
#include <utility>     // std::move

namespace yli::console
{
    TextInput::TextInput(const TextInputType type)
        : type { type }
    {
    }

    TextInput::TextInput(std::string&& string, const TextInputType type)
        : type { type }
    {
        this->input = std::move(string);
        this->move_cursor_to_end_of_line();
    }

    void TextInput::add_character(const char character)
    {
        // Assume there is memory available.
        // Insert a character at current index and make index grow by 1.
        this->input.insert(this->cursor_it, character);
        this->cursor_it = this->input.begin() + (++this->cursor_index);
    }

    void TextInput::add_characters(std::string_view char_container)
    {
        this->input.insert(this->input.end(), char_container.begin(), char_container.end());
        this->cursor_index += char_container.size();
        this->cursor_it = this->input.begin() + this->cursor_index;
    }

    void TextInput::emplace_back(char character)
    {
        this->input.push_back(character);
        this->cursor_it = this->input.end(); // Keep the iterator valid.
        this->cursor_index = this->size();   // Keep the index matched to the iterator.
    }

    void TextInput::push_back(char character)
    {
        this->input.push_back(character);
        this->cursor_it = this->input.end(); // Keep the iterator valid.
        this->cursor_index = this->size();   // Keep the index matched to the iterator.
    }

    std::optional<char> TextInput::get_character_at_current_index() const
    {
        if (this->cursor_it != this->input.end()) [[likely]]
        {
            return *this->cursor_it;
        }

        return std::nullopt;
    }

    std::optional<char> TextInput::get_character_to_the_left() const
    {
        if (this->cursor_it != this->input.begin()) [[likely]]
        {
            auto temp_it = cursor_it;
            return *(--temp_it);
        }

        return std::nullopt;
    }

    bool TextInput::delete_character()
    {
        // If the size of the input is > 0, delete the character at the current index, and return `true` to signal success.
        // Otherwise, return `false` to signal fail.
        if (this->input.size() > 0) [[likely]]
        {
            if (this->cursor_it == this->input.end()) [[likely]]
            {
                // Last character, deleting the character also decrements cursor index.
                this->cursor_index--;
            }

            this->input.erase(--this->cursor_it);
            this->cursor_it = this->input.begin() + this->cursor_index;
            return true;
        }

        return false;
    }

    void TextInput::ctrl_w()
    {
        // First, remove all spaces until a non-space is encountered.
        while (this->cursor_index != 0 && this->get_character_to_the_left() == ' ')
        {
            this->delete_character();
        }

        // Then, remove all non-spaces until a space is encountered.
        while (this->cursor_index != 0 && this->get_character_to_the_left() != ' ')
        {
            this->delete_character();
        }
    }

    void TextInput::clear()
    {
        // Clear the text field.
        this->input.clear();
        this->move_cursor_to_start_of_line();
    }

    bool TextInput::move_cursor_left()
    {
        // If index is > 0, decrease index by 1, and return `true` to signal success.
        // Otherwise, return `false` to signal fail.
        if (this->cursor_it != this->input.begin()) [[likely]]
        {
            this->cursor_it--;
            this->cursor_index--;
            return true;
        }

        return false;
    }

    bool TextInput::move_cursor_right()
    {
        // If index is < size - 2, increase index by 1, and return `true` to signal success.
        // Otherwise, return `false` to signal fail.
        if (this->cursor_it != this->input.end())
        {
            this->cursor_it++;
            this->cursor_index++;
            return true;
        }

        return false;
    }

    void TextInput::move_cursor_to_start_of_line()
    {
        // Set index to 0.
        this->cursor_it = this->input.begin();
        this->cursor_index = 0;
    }

    void TextInput::move_cursor_to_end_of_line()
    {
        // Set index to size - 1.
        this->cursor_it = this->input.end();
        this->cursor_index = this->input.size();
    }

    std::size_t TextInput::size() const
    {
        // Return the number of characters in the input.
        return this->input.size();
    }

    bool TextInput::empty() const
    {
        return this->size() == 0;
    }

    const std::string& TextInput::data() const
    {
        return this->input;
    }

    std::size_t TextInput::get_cursor_index() const
    {
        return this->cursor_index;
    }

    TextInputType TextInput::get_type() const
    {
        return this->type;
    }

    void TextInput::on_change(const yli::console::ConsoleState old_state, const yli::console::ConsoleState new_state)
    {
        if (new_state == old_state)
        {
            // No change.
            return;
        }

        // Console state change.
    }
}
