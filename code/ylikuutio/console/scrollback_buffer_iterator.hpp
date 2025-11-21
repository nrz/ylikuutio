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

#ifndef YLIKUUTIO_CONSOLE_SCROLLBACK_BUFFER_ITERATOR_HPP_INCLUDED
#define YLIKUUTIO_CONSOLE_SCROLLBACK_BUFFER_ITERATOR_HPP_INCLUDED

// Include standard headers
#include <cstddef>  // std::ptrdiff_t
#include <iterator> // std::bidirectional_iterator_tag
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::console
{
    class ScrollbackBufferIterator
    {
        public:
            using iterator_category = std::bidirectional_iterator_tag;
            using value_type        = std::string;
            using difference_type   = std::ptrdiff_t;
            using pointer           = std::string*;
            using reference         = std::string&;

            explicit ScrollbackBufferIterator(std::vector<std::string>::iterator it)
                : it { it }
            {
            }

            // copy constructor.
            ScrollbackBufferIterator(const ScrollbackBufferIterator&) = default;

            // copy assignment.
            ScrollbackBufferIterator& operator=(const ScrollbackBufferIterator&) = default;

            // assignment of `std::vector` iterator.
            ScrollbackBufferIterator& operator=(std::vector<std::string>::iterator it)
            {
                this->it = it;
                return *this;
            }

            ~ScrollbackBufferIterator() = default;

            bool operator==(const ScrollbackBufferIterator& other_it) const noexcept
            {
                return this->it == other_it.it;
            }

            bool operator!=(const ScrollbackBufferIterator& other_it) const = default;

            ScrollbackBufferIterator& operator++()
            {
                ++this->it;
                return *this;
            }

            ScrollbackBufferIterator& operator--()
            {
                --this->it;
                return *this;
            }

            ScrollbackBufferIterator& operator++(int)
            {
                ScrollbackBufferIterator& temp { *this };
                ++this->it;
                return temp;
            }

            ScrollbackBufferIterator& operator--(int)
            {
                ScrollbackBufferIterator& temp { *this };
                --this->it;
                return temp;
            }

            std::string operator*()
            {
                return *(this->it);
            }

        private:
            std::vector<std::string>::iterator it;
    };
}

#endif
