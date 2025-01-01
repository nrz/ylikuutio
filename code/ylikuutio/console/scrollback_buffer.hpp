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

#ifndef YLIKUUTIO_CONSOLE_SCROLLBACK_BUFFER_HPP_INCLUDED
#define YLIKUUTIO_CONSOLE_SCROLLBACK_BUFFER_HPP_INCLUDED

#include "scrollback_buffer_iterator.hpp"
#include "scrollback_buffer_const_iterator.hpp"
#include "text_line.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace yli::console
{
    class ScrollbackBuffer
    {
        public:
            // Iterator typedefs.
            typedef ScrollbackBufferIterator      iterator;
            typedef ScrollbackBufferConstIterator const_iterator;

            explicit ScrollbackBuffer(const uint32_t input_field_width);

            ScrollbackBuffer(const ScrollbackBuffer&) = delete;
            ScrollbackBuffer& operator=(const ScrollbackBuffer&) = delete;

            void add_to_buffer(const TextInput& input);
            void add_to_buffer(const TextLine& text);
            const TextLine& get_nth(const std::size_t line_i) const;

            std::size_t size() const;
            uint32_t get_line_width() const;

            // Iterator functions.
            iterator begin()
            {
                return iterator(this->buffer.begin());
            }

            iterator end()
            {
                return iterator(this->buffer.end());
            }

            const_iterator cbegin() const
            {
                return const_iterator(this->buffer.cbegin());
            }

            const_iterator cend() const
            {
                return const_iterator(this->buffer.cend());
            }

        private:
            std::vector<TextLine> buffer;
            const uint32_t line_width; // Line width must be at least 1.
    };
}

#endif
