// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2026 Antti Nuortimo.
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

#ifndef YLIKUUTIO_CONSOLE_TEXT_INPUT_HISTORY_CONST_ITERATOR_HPP_INCLUDED
#define YLIKUUTIO_CONSOLE_TEXT_INPUT_HISTORY_CONST_ITERATOR_HPP_INCLUDED

#include "text_input.hpp"

// Include standard headers
#include <cstddef>  // std::ptrdiff_t
#include <iterator> // std::bidirectional_iterator_tag
#include <vector>   // std::vector

namespace yli::console
{
    class TextInputHistoryConstIterator
    {
        public:
            using iterator_category = std::bidirectional_iterator_tag;
            using value_type        = TextInput;
            using difference_type   = std::ptrdiff_t;
            using pointer           = const TextInput*;
            using reference         = const TextInput&;

            explicit TextInputHistoryConstIterator(std::vector<TextInput>::const_iterator it)
                : it { it }
            {
            }

            // copy constructor.
            TextInputHistoryConstIterator(const TextInputHistoryConstIterator&) = default;

            // copy assignment.
            TextInputHistoryConstIterator& operator=(const TextInputHistoryConstIterator&) = default;

            // assignment of `std::vector` iterator.
            TextInputHistoryConstIterator& operator=(std::vector<TextInput>::const_iterator it)
            {
                this->it = it;
                return *this;
            }

            ~TextInputHistoryConstIterator() = default;

            bool operator==(const TextInputHistoryConstIterator& other_it) const noexcept
            {
                return this->it == other_it.it;
            }

            bool operator!=(const TextInputHistoryConstIterator& other_it) const = default;

            TextInputHistoryConstIterator& operator++()
            {
                ++this->it;
                return *this;
            }

            TextInputHistoryConstIterator& operator--()
            {
                --this->it;
                return *this;
            }

            TextInputHistoryConstIterator& operator++(int)
            {
                TextInputHistoryConstIterator& temp { *this };
                ++this->it;
                return temp;
            }

            TextInputHistoryConstIterator& operator--(int)
            {
                TextInputHistoryConstIterator& temp { *this };
                --this->it;
                return temp;
            }

            TextInput operator*()
            {
                return *(this->it);
            }

        private:
            std::vector<TextInput>::const_iterator it;
    };
}

#endif
