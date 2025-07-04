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

#ifndef YLIKUUTIO_CONSOLE_TEXT_INPUT_CONST_ITERATOR_HPP_INCLUDED
#define YLIKUUTIO_CONSOLE_TEXT_INPUT_CONST_ITERATOR_HPP_INCLUDED

// Include standard headers
#include <cstddef>  // std::ptrdiff_t
#include <iterator> // std::bidirectional_iterator_tag
#include <string>   // std::u32string

namespace yli::console
{
    class TextInputConstIterator
    {
        public:
            using iterator_category = std::bidirectional_iterator_tag;
            using value_type        = char32_t;
            using difference_type   = std::ptrdiff_t;
            using pointer           = const char32_t*;
            using reference         = const char32_t&;

            explicit TextInputConstIterator(std::u32string::const_iterator it)
                : it { it }
            {
            }

            // copy constructor.
            TextInputConstIterator(const TextInputConstIterator&) = default;

            // copy assignment.
            TextInputConstIterator& operator=(const TextInputConstIterator&) = default;

            // assignment of `std::u32string` const_iterator.
            TextInputConstIterator& operator=(std::u32string::const_iterator it)
            {
                this->it = it;
                return *this;
            }

            ~TextInputConstIterator() = default;

            bool operator==(const TextInputConstIterator& other_it) const noexcept
            {
                return this->it == other_it.it;
            }

            bool operator!=(const TextInputConstIterator& other_it) const = default;

            TextInputConstIterator& operator++()
            {
                ++this->it;
                return *this;
            }

            TextInputConstIterator& operator--()
            {
                --this->it;
                return *this;
            }

            TextInputConstIterator& operator++(int)
            {
                TextInputConstIterator& temp { *this };
                ++this->it;
                return temp;
            }

            TextInputConstIterator& operator--(int)
            {
                TextInputConstIterator& temp { *this };
                --this->it;
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
