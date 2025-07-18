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

#ifndef YLIKUUTIO_CONSOLE_TEXT_LINE_HPP_INCLUDED
#define YLIKUUTIO_CONSOLE_TEXT_LINE_HPP_INCLUDED

#include "text_line_const_iterator.hpp"
#include "text_input.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <string>      // std::u32string
#include <string_view> // std::u32string_view

namespace yli::console
{
    class TextLine
    {
        public:
            TextLine(const TextLine& other) = default;
            TextLine& operator=(const TextLine&) = delete;

            // Iterator typedefs.
            typedef TextLineConstIterator const_iterator;

            bool operator==(const TextLine& other) const;
            bool operator!=(const TextLine& other) const;

            explicit TextLine(std::u32string_view text_line);

            explicit TextLine(const TextInput& text_input);

            TextLine(const typename std::u32string::const_iterator begin, const typename std::u32string::const_iterator end);
            TextLine(const TextLine::const_iterator begin, const TextLine::const_iterator end);
            TextLine(const TextInput::const_iterator begin, const TextInput::const_iterator end);

            const std::u32string& data() const;

            std::size_t size() const;

            // Iterator functions.
            const_iterator cbegin() const
            {
                return const_iterator(this->line.cbegin());
            }

            const_iterator cend() const
            {
                return const_iterator(this->line.cend());
            }

        private:
            const std::u32string line;
    };
}

#endif
