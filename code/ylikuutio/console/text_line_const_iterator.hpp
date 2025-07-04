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

#ifndef YLIKUUTIO_CONSOLE_TEXT_LINE_CONST_ITERATOR_HPP_INCLUDED
#define YLIKUUTIO_CONSOLE_TEXT_LINE_CONST_ITERATOR_HPP_INCLUDED

// Include standard headers
#include <cstddef>  // std::ptrdiff_t, std::size_t
#include <iterator> // std::bidirectional_iterator_tag
#include <string>   // std::u32string

namespace yli::console
{
    class TextLineConstIterator
    {
        public:
            using iterator_category = std::bidirectional_iterator_tag;
            using value_type        = char32_t;
            using difference_type   = std::ptrdiff_t;
            using pointer           = const char32_t*;
            using reference         = const char32_t&;

            explicit TextLineConstIterator(std::u32string::const_iterator it)
                : it { it }
            {
            }

            // copy constructor.
            TextLineConstIterator(const TextLineConstIterator&) = default;

            // copy assignment.
            TextLineConstIterator& operator=(const TextLineConstIterator&) = default;

            // assignment of `std::u32string::const_iterator` const_iterator.
            TextLineConstIterator& operator=(std::u32string::const_iterator it)
            {
                this->it = it;
                return *this;
            }

            ~TextLineConstIterator() = default;

            bool operator==(const TextLineConstIterator& other_it) const noexcept
            {
                return this->it == other_it.it;
            }

            bool operator!=(const TextLineConstIterator& other_it) const = default;

            TextLineConstIterator& operator++()
            {
                ++this->it;
                return *this;
            }

            TextLineConstIterator& operator--()
            {
                --this->it;
                return *this;
            }

            TextLineConstIterator& operator++(int)
            {
                TextLineConstIterator& temp { *this };
                ++this->it;
                return temp;
            }

            TextLineConstIterator& operator--(int)
            {
                TextLineConstIterator& temp { *this };
                --this->it;
                return temp;
            }

            TextLineConstIterator& operator+(const std::size_t count)
            {
                TextLineConstIterator& temp { *this };
                this->it += count;
                return temp;
            }

            TextLineConstIterator& operator-(const std::size_t count)
            {
                TextLineConstIterator& temp { *this };
                this->it -= count;
                return temp;
            }

            char32_t operator*()
            {
                return *(this->it);
            }

            std::u32string::const_iterator unwrap() const
            {
                return this->it;
            }

        private:
            std::u32string::const_iterator it;
    };
}

#endif
