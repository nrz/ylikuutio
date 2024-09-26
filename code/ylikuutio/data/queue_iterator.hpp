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

#ifndef YLIKUUTIO_DATA_QUEUE_ITERATOR_HPP_INCLUDED
#define YLIKUUTIO_DATA_QUEUE_ITERATOR_HPP_INCLUDED

// Include standard headers
#include <array>    // std::array
#include <cstddef>  // std::size_t, std::ptrdiff_t
#include <iterator> // std::bidirectional_iterator_tag

namespace yli::data
{
    template<std::size_t QueueMaxSize = 1>
        class QueueIterator
        {
            public:
                using iterator_category = std::bidirectional_iterator_tag;
                using value_type        = std::size_t;
                using difference_type   = std::ptrdiff_t;
                using pointer           = std::size_t*;
                using reference         = std::size_t&;

                explicit QueueIterator(typename std::array<std::size_t, QueueMaxSize>::iterator it)
                    : it { it }
                {
                }

                // copy constructor.
                QueueIterator(const QueueIterator&) = default;

                // copy assignment.
                QueueIterator& operator=(const QueueIterator&) = default;

                // assignment of `std::array` iterator.
                QueueIterator& operator=(typename std::array<std::size_t, QueueMaxSize>::iterator it)
                {
                    this->it = it;
                    return *this;
                }

                ~QueueIterator() = default;

                bool operator==(const QueueIterator& other_it) const noexcept
                {
                    return this->it == other_it.it;
                }

                bool operator!=(const QueueIterator& other_it) const = default;

                QueueIterator& operator++()
                {
                    ++this->it;
                    return *this;
                }

                QueueIterator& operator--()
                {
                    --this->it;
                    return *this;
                }

                QueueIterator& operator++(int)
                {
                    QueueIterator& temp { *this };
                    ++this->it;
                    return temp;
                }

                QueueIterator& operator--(int)
                {
                    QueueIterator& temp { *this };
                    --this->it;
                    return temp;
                }

                std::size_t& operator*()
                {
                    return *(this->it);
                }

            private:
                typename std::array<std::size_t, QueueMaxSize>::iterator it;
        };
}

#endif
