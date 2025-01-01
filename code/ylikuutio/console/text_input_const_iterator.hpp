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

#include "code/ylikuutio/data/codepoint.hpp"

// Include standard headers
#include <cstddef>  // std::ptrdiff_t
#include <iterator> // std::bidirectional_iterator_tag
#include <vector>   // std::vector

namespace yli::console
{
    class TextInputConstIterator
    {
        public:
            using iterator_category = std::bidirectional_iterator_tag;
            using value_type        = yli::data::Codepoint;
            using difference_type   = std::ptrdiff_t;
            using pointer           = const yli::data::Codepoint*;
            using reference         = const yli::data::Codepoint&;

            explicit TextInputConstIterator(std::vector<yli::data::Codepoint>::const_iterator it)
                : it { it }
            {
            }

            // copy constructor.
            TextInputConstIterator(const TextInputConstIterator&) = default;

            // copy assignment.
            TextInputConstIterator& operator=(const TextInputConstIterator&) = default;

            // assignment of `std::vector` const_iterator.
            TextInputConstIterator& operator=(std::vector<yli::data::Codepoint>::const_iterator it)
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

            yli::data::Codepoint operator*()
            {
                return *(this->it);
            }

            std::vector<yli::data::Codepoint>::const_iterator unwrap() const
            {
                return this->it;
            }

        private:
            std::vector<yli::data::Codepoint>::const_iterator it;
    };
}

#endif
