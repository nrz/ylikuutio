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

#include "text_input.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <vector>  // std::vector

namespace yli::input
{
    void TextInput::add_character(const char character)
    {
        // Assume there is memory available.
        // Insert a character at current index and make index grow by 1.
        this->input.insert(this->cursor_it, character);
        this->cursor_it = this->input.begin() + (++this->cursor_index);
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

    void TextInput::clear()
    {
        // Clear the text field.
        this->input.clear();
        this->cursor_it = this->input.begin();
        this->cursor_index = 0;
    }

    bool TextInput::move_cursor_left()
    {
        // If index is > 0, decrease index by 1, and return `true` to signal success.
        // Otherwise, return `false` to signal fail.
        if (this->cursor_it != this->input.begin())
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

    const std::vector<char>& TextInput::data() const
    {
        return this->input;
    }

    std::size_t TextInput::get_cursor_index() const
    {
        return this->cursor_index;
    }
}