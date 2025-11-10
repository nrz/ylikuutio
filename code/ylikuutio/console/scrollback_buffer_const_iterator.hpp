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

#ifndef YLIKUUTIO_CONSOLE_SCROLLBACK_BUFFER_CONST_ITERATOR_HPP_INCLUDED
#define YLIKUUTIO_CONSOLE_SCROLLBACK_BUFFER_CONST_ITERATOR_HPP_INCLUDED

#include "text_line.hpp"

// Include standard headers
#include <cstddef>  // std::ptrdiff_t
#include <iterator> // std::bidirectional_iterator_tag
#include <vector>   // std::vector

namespace yli::console
{
    class ScrollbackBufferConstIterator
    {
        public:
            using iterator_category = std::bidirectional_iterator_tag;
            using value_type        = TextLine;
            using difference_type   = std::ptrdiff_t;
            using pointer           = const TextLine*;
            using reference         = const TextLine&;

            explicit ScrollbackBufferConstIterator(std::vector<TextLine>::const_iterator it)
                : it { it }
            {
            }

            // copy constructor.
            ScrollbackBufferConstIterator(const ScrollbackBufferConstIterator&) = default;

            // copy assignment.
            ScrollbackBufferConstIterator& operator=(const ScrollbackBufferConstIterator&) = default;

            // assignment of `std::vector` const_iterator.
            ScrollbackBufferConstIterator& operator=(std::vector<TextLine>::const_iterator it)
            {
                this->it = it;
                return *this;
            }

            ~ScrollbackBufferConstIterator() = default;

            bool operator==(const ScrollbackBufferConstIterator& other_it) const noexcept
            {
                return this->it == other_it.it;
            }

            bool operator!=(const ScrollbackBufferConstIterator& other_it) const = default;

            ScrollbackBufferConstIterator& operator++()
            {
                ++this->it;
                return *this;
            }

            ScrollbackBufferConstIterator& operator--()
            {
                --this->it;
                return *this;
            }

            ScrollbackBufferConstIterator& operator++(int)
            {
                ScrollbackBufferConstIterator& temp { *this };
                ++this->it;
                return temp;
            }

            ScrollbackBufferConstIterator& operator--(int)
            {
                ScrollbackBufferConstIterator& temp { *this };
                --this->it;
                return temp;
            }

            TextLine operator*()
            {
                return *(this->it);
            }

        private:
            std::vector<TextLine>::const_iterator it;
    };
}

#endif
