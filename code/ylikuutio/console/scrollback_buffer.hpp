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
#include "console_state.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <limits>   // std::numeric_limits
#include <span>     // std::span
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

            explicit ScrollbackBuffer(const uint32_t n_columns = 80, const uint32_t n_rows = 24);

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
            bool page_up();
            bool page_down();

            void clear();

            std::span<const TextLine> get_view(const std::size_t top_index, const std::size_t max_rows) const;
            std::span<const TextLine> get_view_to_last(const std::size_t max_rows) const;
            std::span<const TextLine> get_end_view(const std::size_t max_rows) const;
            const TextLine& at(const std::size_t line_i) const;

            bool get_is_active_in_buffer() const;
            std::size_t size() const;
            bool empty() const;
            const std::vector<TextLine>& data() const;
            uint32_t get_n_columns() const;
            uint32_t get_n_rows() const;

            std::size_t get_buffer_index() const;

            void on_change(const ConsoleState old_state, const ConsoleState new_state);

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
            const uint32_t n_columns;  // Number of columns must be at least 1.
            const uint32_t n_rows;     // Number of rows must be at least 1.
            std::vector<TextLine>::iterator buffer_it { this->buffer.end() };
            std::size_t buffer_index { std::numeric_limits<std::size_t>::max() };
    };
}

#endif
