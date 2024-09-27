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

#ifndef YLIKUUTIO_DATA_QUEUE_HPP_INCLUDED
#define YLIKUUTIO_DATA_QUEUE_HPP_INCLUDED

#include "queue_iterator.hpp"
#include "code/ylikuutio/memory/memory_templates.hpp"

// Include standard headers
#include <array>     // std::array
#include <cstddef>   // std::size_t
#include <stdexcept> // std::runtime_error

namespace yli::data
{
    template<std::size_t QueueMaxSize = 1>
        class Queue
        {
            public:
                // Iterator typedefs.
                typedef QueueIterator<QueueMaxSize>       iterator;
                typedef QueueIterator<QueueMaxSize> const_iterator;

                void push(const std::size_t value)
                {
                    if (this->queue_size >= QueueMaxSize) [[unlikely]]
                    {
                        throw std::runtime_error("ERROR: `yli::data::Queue::push`: queue is full, no space to push!");
                    }

                    this->queue.at(this->next_tail++) = value;
                    this->queue_size++;

                    if (this->next_tail == QueueMaxSize)
                    {
                        this->next_tail = 0;
                    }
                }

                std::size_t pop()
                {
                    if (this->size() == 0) [[unlikely]]
                    {
                        throw std::runtime_error("ERROR: `yli::data::Queue::pop`: queue is empty, nothing to pop!");
                    }

                    std::size_t value = this->queue.at(this->head++);

                    if (this->head >= QueueMaxSize)
                    {
                        this->head = 0;
                    }

                    this->queue_size--;
                    return value;
                }

                std::size_t size() const
                {
                    return this->queue_size;
                }

                std::size_t max_size() const
                {
                    return QueueMaxSize;
                }

                std::size_t get_head() const
                {
                    return this->head;
                }

                std::size_t get_next_tail() const
                {
                    return this->next_tail;
                }

                const std::array<std::size_t, QueueMaxSize>& data() const
                {
                    return this->queue;
                }

                void move_to_beginning()
                {
                    yli::memory::copy_circular_buffer_into_begin(this->queue, this->head, this->queue_size);
                    this->head = 0;
                }

                // Iterator functions.
                iterator begin()
                {
                    return iterator(this->queue.begin());
                }

                iterator end()
                {
                    return iterator(this->queue.end());
                }

                iterator last()
                {
                    // Use only after calling `move_to_beginning`.
                    typename std::array<std::size_t, QueueMaxSize>::iterator it = this->queue.begin();
                    it += queue_size;
                    return iterator(it);
                }

                const_iterator cbegin()
                {
                    return const_iterator(this->queue.begin());
                }

                const_iterator cend()
                {
                    return const_iterator(this->queue.end());
                }

                const_iterator clast()
                {
                    // Use only after calling `move_to_beginning`.
                    typename std::array<std::size_t, QueueMaxSize>::const_iterator it = this->queue.cbegin();
                    it += queue_size;
                    return const_iterator(it);
                }

            private:
                std::array<std::size_t, QueueMaxSize> queue {};
                std::size_t head       { 0 };
                std::size_t next_tail  { 0 };
                std::size_t queue_size { 0 };
        };
}

#endif
