// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2024 Antti Nuortimo.
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

#ifndef YLIKUUTIO_INPUT_TEXT_INPUT_ITERATOR_HPP_INCLUDED
#define YLIKUUTIO_INPUT_TEXT_INPUT_ITERATOR_HPP_INCLUDED

#include "codepoint.hpp"

// Include standard headers
#include <cstddef>  // std::ptrdiff_t
#include <iterator> // std::bidirectional_iterator_tag
#include <vector>   // std::vector

namespace yli::input
{
    class TextInputIterator
    {
        public:
            using iterator_category = std::bidirectional_iterator_tag;
            using value_type        = Codepoint;
            using difference_type   = std::ptrdiff_t;
            using pointer           = Codepoint*;
            using reference         = Codepoint&;

            explicit TextInputIterator(std::vector<Codepoint>::iterator it)
                : it { it }
            {
            }

            // copy constructor.
            TextInputIterator(const TextInputIterator&) = default;

            // copy assignment.
            TextInputIterator& operator=(const TextInputIterator&) = default;

            // assignment of `std::vector` iterator.
            TextInputIterator& operator=(std::vector<Codepoint>::iterator it)
            {
                this->it = it;
                return *this;
            }

            ~TextInputIterator() = default;

            bool operator==(const TextInputIterator& other_it) const noexcept
            {
                return this->it == other_it.it;
            }

            bool operator!=(const TextInputIterator& other_it) const = default;

            TextInputIterator& operator++()
            {
                ++this->it;
                return *this;
            }

            TextInputIterator& operator--()
            {
                --this->it;
                return *this;
            }

            TextInputIterator& operator++(int)
            {
                TextInputIterator& temp { *this };
                ++this->it;
                return temp;
            }

            TextInputIterator& operator--(int)
            {
                TextInputIterator& temp { *this };
                --this->it;
                return temp;
            }

            Codepoint operator*()
            {
                return *(this->it);
            }

        private:
            std::vector<Codepoint>::iterator it;
    };
}

#endif
