// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2023 Antti Nuortimo.
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

#ifndef YLIKUUTIO_MEMORY_QUEUE_HPP_INCLUDED
#define YLIKUUTIO_MEMORY_QUEUE_HPP_INCLUDED

// Include standard headers
#include <array>     // std::array
#include <stdexcept> // std::runtime_error
#include <stdint.h>  // uint32_t

namespace yli::data
{
    template<uint32_t QueueMaxSize = 1>
        class Queue
        {
            public:
                uint32_t pop()
                {
                    if (this->size() == 0)
                    {
                        throw std::runtime_error("ERROR: `yli::data::Queue::pop`: queue is empty, nothing to pop!");
                    }

                    uint32_t value = this->queue.at(this->head++);

                    if (this->head >= QueueMaxSize)
                    {
                        this->head = 0;
                    }

                    this->queue_size--;
                    return value;
                }

                void push(uint32_t value)
                {
                    if (this->queue_size >= QueueMaxSize)
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

                uint32_t size() const
                {
                    return this->queue_size;
                }

                uint32_t max_size() const
                {
                    return QueueMaxSize;
                }

                uint32_t get_head() const
                {
                    return this->head;
                }

                uint32_t get_next_tail() const
                {
                    return this->next_tail;
                }

            private:
                std::array<uint32_t, QueueMaxSize> queue {};
                uint32_t head       { 0 };
                uint32_t next_tail  { 0 };
                uint32_t queue_size { 0 };
        };
}

#endif
