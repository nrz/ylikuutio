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

#include "text_line.hpp"
#include "text_input.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <string>      // std::u32string
#include <string_view> // std::u32string_view

namespace yli::console
{
    bool TextLine::operator==(const TextLine& other) const
    {
        return this->line == other.line;
    }

    bool TextLine::operator!=(const TextLine& other) const
    {
        return this->line != other.line;
    }

    TextLine::TextLine(std::u32string_view text_line)
        : line { text_line }
    {
    }

    TextLine::TextLine(const TextInput& text_input)
        : line { text_input.data() }
    {
    }

    TextLine::TextLine(const TextLine::const_iterator begin, const TextLine::const_iterator end)
        : line(begin.unwrap(), end.unwrap())
    {
    }

    TextLine::TextLine(const TextInput::const_iterator begin, const TextInput::const_iterator end)
        : line(begin.unwrap(), end.unwrap())
    {
    }

    const std::u32string& TextLine::data() const
    {
        return this->line;
    }

    std::size_t TextLine::size() const
    {
        return this->line.size();
    }
}
