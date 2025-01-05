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
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace yli::console
{
    class TextInput;

    ScrollbackBuffer::ScrollbackBuffer(const uint32_t line_width)
        : line_width { (line_width > 0 ? line_width : 1)  }
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

    const TextLine& ScrollbackBuffer::at(const std::size_t line_i) const
    {
        return *(this->buffer.begin() + line_i);
    }

    std::size_t ScrollbackBuffer::size() const
    {
        return this->buffer.size();
    }

    uint32_t ScrollbackBuffer::get_line_width() const
    {
        return this->line_width;
    }
}
