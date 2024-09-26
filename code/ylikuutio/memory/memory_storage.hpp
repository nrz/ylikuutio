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

#ifndef YLIKUUTIO_MEMORY_MEMORY_STORAGE_HPP_INCLUDED
#define YLIKUUTIO_MEMORY_MEMORY_STORAGE_HPP_INCLUDED

#include "constructible_module.hpp"
#include "memory_templates.hpp"
#include "code/ylikuutio/data/queue.hpp"

// Include standard headers
#include <array>     // std::array
#include <cstddef>   // std::byte, std::size_t
#include <limits>    // std::numeric_limits
#include <new>       // std::launder
#include <stdexcept> // std::runtime_error
#include <utility>   // std::forward

namespace yli::memory
{
    class GenericMemoryAllocator;

    template<typename T1 = std::byte, std::size_t DataSize = 1>
        class MemoryStorage
        {
            // `MemoryStorage` instance takes care of single memory storage.

            public:
                MemoryStorage(yli::memory::GenericMemoryAllocator& allocator, const std::size_t storage_i)
                    : allocator { allocator },
                    storage_i { storage_i }
                {
                    if (storage_i == std::numeric_limits<std::size_t>::max()) [[unlikely]]
                    {
                        throw std::runtime_error("ERROR: `MemoryStorage::MemoryStorage`: `storage_i` has invalid value!");
                    }
                }

                ~MemoryStorage() noexcept
                {
                    if (this->number_of_instances == 0) [[unlikely]]
                    {
                        // No instances to destroy.
                        return;
                    }

                    // The queue needs to be sorted as it will be used
                    // for finding out which slots are in use.
                    //
                    // First, copy the data so that the head of the queue is at index 0.
                    this->free_slot_id_queue.move_to_beginning();

                    // Sort.
                    for (
                            typename yli::data::Queue<DataSize>::iterator left_it = this->free_slot_id_queue.begin();
                            left_it != this->free_slot_id_queue.last();
                            ++left_it)
                    {
                        typename yli::data::Queue<DataSize>::iterator right_it = this->free_slot_id_queue.begin();
                        ++right_it;

                        for ( ; right_it != this->free_slot_id_queue.last(); ++right_it)
                        {
                            if (*left_it > *right_it)
                            {
                                std::size_t temp = *left_it;
                                *left_it = *right_it;
                                *right_it = temp;
                            }
                        }
                    }

                    typename yli::data::Queue<DataSize>::iterator queue_it = this->free_slot_id_queue.begin();

                    for (
                            std::size_t slot_i = 0, count = 0;
                            count < this->number_of_instances;
                            slot_i++)
                    {
                        if (queue_it != free_slot_id_queue.last() && slot_i == *queue_it)
                        {
                            // This slot ID was not in use.

                            ++queue_it;
                            continue;
                        }

                        T1* data = std::launder(reinterpret_cast<T1*>(this->memory.data()));
                        T1* instance { &data[slot_i] };
                        instance->~T1();
                        count++;
                    }
                }

                MemoryStorage(const MemoryStorage&) = delete;            // Delete copy constructor.
                MemoryStorage& operator=(const MemoryStorage&) = delete; // Delete copy assignment.

                template<typename... Args>
                    T1* build_in(Args&&... args)
                    {
                        if (this->number_of_instances >= DataSize) [[unlikely]]
                        {
                            // This `MemoryStorage` is already full, can't build anything.
                            return nullptr;
                        }

                        std::size_t slot_i;

                        if (this->free_slot_id_queue.size() == 0) [[unlikely]]
                        {
                            // Queue is empty.
                            // Use the current number of instances as the index,
                            slot_i = this->number_of_instances;
                        }
                        else [[likely]]
                        {
                            // Queue is not empty.
                            // Pop a free index from queue.
                            slot_i = this->free_slot_id_queue.pop();
                        }

                        T1* data = std::launder(reinterpret_cast<T1*>(this->memory.data()));
                        auto* instance { new (&data[slot_i]) T1(std::forward<Args>(args)...) };
                        instance->constructible_module = yli::memory::ConstructibleModule(this->allocator, this->storage_i, slot_i);
                        this->number_of_instances++;
                        return instance;
                    }

                void destroy(const std::size_t slot_i)
                {
                    if (slot_i == std::numeric_limits<std::size_t>::max()) [[unlikely]]
                    {
                        throw std::runtime_error("ERROR: `MemoryStorage::destroy`: `slot_i` has invalid value!");
                    }

                    if (slot_i >= DataSize) [[unlikely]]
                    {
                        throw std::runtime_error(
                                "ERROR: `MemoryStorage::destroy`: `slot_i` " + std::to_string(storage_i) +
                                " is out of bounds, `DataSize` is " + std::to_string(DataSize));
                    }

                    // `slot_i` is not checked here (because it would make `destroy` O(n) operation instead of O(1)).
                    // The caller must make sure that `slot_i` points to an existing instance.
                    T1* data = std::launder(reinterpret_cast<T1*>(this->memory.data()));
                    T1* instance { &data[slot_i] };
                    instance->~T1();

                    // Push the freed index to the queue.
                    this->free_slot_id_queue.push(slot_i);
                    this->number_of_instances--;
                }

                std::size_t get_storage_id() const
                {
                    return this->storage_i;
                }

                std::size_t get_number_of_instances() const
                {
                    return this->number_of_instances;
                }

            private:
                yli::memory::GenericMemoryAllocator& allocator;
                alignas(T1) std::array<std::byte, DataSize * sizeof(T1)> memory {};
                yli::data::Queue<DataSize> free_slot_id_queue;
                const std::size_t storage_i;
                std::size_t number_of_instances { 0 };
        };
}

#endif
