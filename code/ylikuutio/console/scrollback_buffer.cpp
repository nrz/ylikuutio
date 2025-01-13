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

#include "scrollback_buffer.hpp"
#include "text_line.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <limits>   // std::numeric_limits
#include <optional> // std::optional
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace yli::console
{
    class TextInput;

    ScrollbackBuffer::ScrollbackBuffer(ConsoleStateModule& console_state_module, const uint32_t line_width)
        : console_state_module { console_state_module },
        line_width { (line_width > 0 ? line_width : 1) }
    {
    }

    void ScrollbackBuffer::add_to_buffer(const TextInput& text)
    {
        this->add_to_buffer(TextLine(text));
    }

    void ScrollbackBuffer::add_to_buffer(const TextLine& text)
    {
        for (std::size_t text_i = 0; text_i < text.size(); text_i += this->line_width)
        {
            if (text_i + this->line_width <= text.size())
            {
                TextLine text_line(text.cbegin() + text_i, text.cbegin() + text_i + this->line_width);
                this->buffer.emplace_back(text_line);
            }
            else
            {
                TextLine text_line(text.cbegin() + text_i, text.cend());
                this->buffer.emplace_back(text_line);
            }
        }
    }

    void ScrollbackBuffer::emplace_back(const TextLine& text)
    {
        this->buffer.emplace_back(text);
    }

    void ScrollbackBuffer::push_back(const TextLine& text)
    {
        this->buffer.push_back(text);
    }

    bool ScrollbackBuffer::enter_buffer()
    {
        if (std::size_t buffer_size = this->buffer.size(); !this->get_is_in_buffer() && buffer_size > 0) [[likely]]
        {
            // If we are not in buffer and the buffer is not empty, enter the buffer.
            this->buffer_index = buffer_size - 1;
            this->buffer_it = this->buffer.begin() + buffer_index;
            return true;
        }

        // Otherwise, entering buffer failed.
        return false;
    }

    bool ScrollbackBuffer::exit_buffer()
    {
        if (this->get_is_in_buffer())
        {
            // If we are in buffer, exit the buffer.
            this->buffer_index = std::numeric_limits<std::size_t>::max();
            this->buffer_it = this->buffer.end();
            return true;
        }

        return false;
    }

    bool ScrollbackBuffer::move_to_previous()
    {
        if (this->get_is_in_buffer() && this->buffer_index > 0) [[likely]]
        {
            // If we are in the buffer and not in the oldest input, move to the previous input.
            this->buffer_index--;
            this->buffer_it--;
            return true;
        }

        // Otherwise either buffer is empty, or we are not in buffer, or we are in the first input of the buffer.
        return false;
    }

    bool ScrollbackBuffer::move_to_next()
    {
        if (this->get_is_in_buffer() && this->buffer_index < this->size()) [[likely]]
        {
            // If we are in the buffer and not in the newest input, move to the next input.
            this->buffer_index++;
            this->buffer_it++;
            return true;
        }

        // Otherwise either buffer is empty, or we are not in buffer, or we are in the last input of the buffer.
        return false;
    }

    void ScrollbackBuffer::move_to_first()
    {
        if (this->size() > 0 && this->get_is_in_buffer()) [[likely]]
        {
            this->buffer_index = 0;
            this->buffer_it = this->buffer.begin();
        }
    }

    void ScrollbackBuffer::move_to_last()
    {
        if (this->size() > 0 && this->get_is_in_buffer()) [[likely]]
        {
            this->buffer_index = this->size() - 1;
            this->buffer_it = this->buffer.begin() + this->size() - 1;
        }
    }

    std::optional<TextLine> ScrollbackBuffer::get() const
    {
        if (this->buffer_index < this->buffer.size()) [[likely]]
        {
            return this->buffer.at(this->buffer_index);
        }

        return std::nullopt;
    }

    const TextLine& ScrollbackBuffer::at(const std::size_t line_i) const
    {
        return *(this->buffer.begin() + line_i);
    }

    bool ScrollbackBuffer::get_is_in_buffer() const
    {
        return this->buffer_index < std::numeric_limits<std::size_t>::max();
    }

    std::size_t ScrollbackBuffer::size() const
    {
        return this->buffer.size();
    }

    bool ScrollbackBuffer::empty() const
    {
        return this->size() == 0;
    }

    uint32_t ScrollbackBuffer::get_line_width() const
    {
        return this->line_width;
    }

    std::size_t ScrollbackBuffer::get_buffer_index() const
    {
        return this->buffer_index;
    }
}
