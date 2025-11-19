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

#ifndef YLIKUUTIO_CONSOLE_TEXT_LINE_ITERATOR_HPP_INCLUDED
#define YLIKUUTIO_CONSOLE_TEXT_LINE_ITERATOR_HPP_INCLUDED

// Include standard headers
#include <cstddef>  // std::ptrdiff_t, std::size_t
#include <iterator> // std::bidirectional_iterator_tag
#include <string>   // std::string

namespace yli::console
{
    class TextLineIterator
    {
        public:
            using iterator_category = std::bidirectional_iterator_tag;
            using value_type        = char;
            using difference_type   = std::ptrdiff_t;
            using pointer           = char*;
            using reference         = char&;

            explicit TextLineIterator(std::string::iterator it)
                : it { it }
            {
            }

            // copy constructor.
            TextLineIterator(const TextLineIterator&) = default;

            // copy assignment.
            TextLineIterator& operator=(const TextLineIterator&) = default;

            // assignment of `std::string::iterator` iterator.
            TextLineIterator& operator=(std::string::iterator it)
            {
                this->it = it;
                return *this;
            }

            ~TextLineIterator() = default;

            bool operator==(const TextLineIterator& other_it) const noexcept
            {
                return this->it == other_it.it;
            }

            bool operator!=(const TextLineIterator& other_it) const = default;

            TextLineIterator& operator++()
            {
                ++this->it;
                return *this;
            }

            TextLineIterator& operator--()
            {
                --this->it;
                return *this;
            }

            TextLineIterator& operator++(int)
            {
                TextLineIterator& temp { *this };
                ++this->it;
                return temp;
            }

            TextLineIterator& operator--(int)
            {
                TextLineIterator& temp { *this };
                --this->it;
                return temp;
            }

            TextLineIterator& operator+(const std::size_t count)
            {
                TextLineIterator& temp { *this };
                this->it += count;
                return temp;
            }

            TextLineIterator& operator-(const std::size_t count)
            {
                TextLineIterator& temp { *this };
                this->it -= count;
                return temp;
            }

            char operator*()
            {
                return *(this->it);
            }

            std::string::iterator unwrap() const
            {
                return this->it;
            }

        private:
            std::string::iterator it;
    };
}

#endif
