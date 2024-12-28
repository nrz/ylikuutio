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

#ifndef YLIKUUTIO_CONSOLE_TEXT_LINE_ITERATOR_HPP_INCLUDED
#define YLIKUUTIO_CONSOLE_TEXT_LINE_ITERATOR_HPP_INCLUDED

#include "code/ylikuutio/data/codepoint.hpp"

// Include standard headers
#include <cstddef>  // std::ptrdiff_t
#include <iterator> // std::bidirectional_iterator_tag
#include <vector>   // std::vector

namespace yli::console
{
    class TextLineIterator
    {
        public:
            using iterator_category = std::bidirectional_iterator_tag;
            using value_type        = yli::data::Codepoint;
            using difference_type   = std::ptrdiff_t;
            using pointer           = yli::data::Codepoint*;
            using reference         = yli::data::Codepoint&;

            explicit TextLineIterator(std::vector<yli::data::Codepoint>::iterator it)
                : it { it }
            {
            }

            // copy constructor.
            TextLineIterator(const TextLineIterator&) = default;

            // copy assignment.
            TextLineIterator& operator=(const TextLineIterator&) = default;

            // assignment of `std::vector` iterator.
            TextLineIterator& operator=(std::vector<yli::data::Codepoint>::iterator it)
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

            yli::data::Codepoint operator*()
            {
                return *(this->it);
            }

        private:
            std::vector<yli::data::Codepoint>::iterator it;
    };
}

#endif
