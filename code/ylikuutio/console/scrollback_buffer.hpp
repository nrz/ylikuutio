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
#include <limits>   // std::numeric_limits
#include <optional> // std::optional
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace yli::console
{
    class ConsoleStateModule;

    class ScrollbackBuffer
    {
        public:
            // Iterator typedefs.
            typedef ScrollbackBufferIterator      iterator;
            typedef ScrollbackBufferConstIterator const_iterator;

            ScrollbackBuffer(ConsoleStateModule& console_state_module, const uint32_t line_width);

            ScrollbackBuffer(const ScrollbackBuffer&) = delete;
            ScrollbackBuffer& operator=(const ScrollbackBuffer&) = delete;

            void add_to_buffer(const TextInput& input);
            void add_to_buffer(const TextLine& text);
            void emplace_back(const TextLine& text);
            void push_back(const TextLine& text);

            bool enter_buffer();
            bool exit_buffer();

            bool move_to_previous();
            bool move_to_next();
            void move_to_first();
            void move_to_last();

            std::optional<TextLine> get() const;
            const TextLine& at(const std::size_t line_i) const;

            bool get_is_in_buffer() const;
            std::size_t size() const;
            bool empty() const;
            uint32_t get_line_width() const;

            std::size_t get_buffer_index() const;

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
            ConsoleStateModule& console_state_module;
            std::vector<TextLine> buffer;
            const uint32_t line_width; // Line width must be at least 1.
            std::vector<TextLine>::iterator buffer_it { this->buffer.end() };
            std::size_t buffer_index { std::numeric_limits<std::size_t>::max() };
    };
}

#endif
