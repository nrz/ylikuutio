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
#include "code/ylikuutio/data/codepoint.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <vector>  // std::vector

namespace yli::console
{
    class TextLine
    {
        public:
            // Iterator typedefs.
            typedef TextLineConstIterator const_iterator;

            bool operator==(const TextLine& other) const
            {
                return this->line == other.line;
            }

            bool operator!=(const TextLine& other) const
            {
                return this->line != other.line;
            }

            explicit TextLine(const std::vector<yli::data::Codepoint>& text_line)
                : line { text_line }
            {
            }

            explicit TextLine(const TextInput& text_input)
                : line { text_input.data() }
            {
            }

            TextLine(const std::vector<yli::data::Codepoint>::const_iterator begin, const std::vector<yli::data::Codepoint>::const_iterator end)
                : line(begin, end)
            {
            }

            TextLine(TextLine::const_iterator begin, TextLine::const_iterator end)
                : line(begin.unwrap(), end.unwrap())
            {
            }

            TextLine(TextInput::const_iterator begin, TextInput::const_iterator end)
                : line(begin.unwrap(), end.unwrap())
            {
            }

            const std::vector<yli::data::Codepoint>& data() const;

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
            const std::vector<yli::data::Codepoint> line;
    };
}

#endif
