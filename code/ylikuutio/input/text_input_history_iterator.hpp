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

#ifndef YLIKUUTIO_INPUT_TEXT_INPUT_HISTORY_ITERATOR_HPP_INCLUDED
#define YLIKUUTIO_INPUT_TEXT_INPUT_HISTORY_ITERATOR_HPP_INCLUDED

#include "text_input.hpp"

// Include standard headers
#include <cstddef>  // std::ptrdiff_t
#include <iterator> // std::bidirectional_iterator_tag
#include <vector>   // std::vector

namespace yli::input
{
    class TextInputHistoryIterator
    {
        public:
            using iterator_category = std::bidirectional_iterator_tag;
            using value_type        = TextInput;
            using difference_type   = std::ptrdiff_t;
            using pointer           = TextInput*;
            using reference         = TextInput&;

            explicit TextInputHistoryIterator(std::vector<TextInput>::iterator it)
                : it { it }
            {
            }

            // copy constructor.
            TextInputHistoryIterator(const TextInputHistoryIterator&) = default;

            // copy assignment.
            TextInputHistoryIterator& operator=(const TextInputHistoryIterator&) = default;

            // assignment of `std::vector` iterator.
            TextInputHistoryIterator& operator=(std::vector<TextInput>::iterator it)
            {
                this->it = it;
                return *this;
            }

            ~TextInputHistoryIterator() = default;

            bool operator==(const TextInputHistoryIterator& other_it) const noexcept
            {
                return this->it == other_it.it;
            }

            bool operator!=(const TextInputHistoryIterator& other_it) const = default;

            TextInputHistoryIterator& operator++()
            {
                ++this->it;
                return *this;
            }

            TextInputHistoryIterator& operator--()
            {
                --this->it;
                return *this;
            }

            TextInputHistoryIterator& operator++(int)
            {
                TextInputHistoryIterator& temp { *this };
                ++this->it;
                return temp;
            }

            TextInputHistoryIterator& operator--(int)
            {
                TextInputHistoryIterator& temp { *this };
                --this->it;
                return temp;
            }

            TextInput operator*()
            {
                return *(this->it);
            }

        private:
            std::vector<TextInput>::iterator it;
    };
}

#endif
