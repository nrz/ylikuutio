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

#ifndef YLIKUUTIO_MEMORY_MEMORY_STORAGE_HPP_INCLUDED
#define YLIKUUTIO_MEMORY_MEMORY_STORAGE_HPP_INCLUDED

#include "constructible_module.hpp"

// Include standard headers
#include <algorithm> // std::sort
#include <array>     // std::array
#include <cstddef>   // std::byte
#include <stdint.h>  // uint32_t
#include <utility>   // std::forward
#include <vector>    // std::vector

namespace yli::memory
{
    template<typename T1 = std::byte, uint32_t DataSize = 1>
        class MemoryStorage
        {
            // `MemoryStorage` instance takes care of single memory storage.

            public:
                explicit MemoryStorage(const uint32_t storage_i)
                    : storage_i { storage_i }
                {
                }

                ~MemoryStorage()
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
                    std::vector<uint32_t> copy_of_free_slot_id_queue;

                    for (
                            uint32_t src_i = (this->free_slot_id_queue_start_i + this->size_of_free_slot_id_queue) % DataSize, count = 0;
                            count < this->size_of_free_slot_id_queue;
                            count++)
                    {
                        copy_of_free_slot_id_queue.emplace_back(this->free_slot_id_queue.at(src_i));
                        src_i = (src_i + 1) % DataSize;
                    }

                    std::sort(copy_of_free_slot_id_queue.begin(), copy_of_free_slot_id_queue.end());

                    for (
                            uint32_t slot_i = 0, queue_copy_i = 0, count = 0;
                            count < this->number_of_instances;
                            slot_i++)
                    {
                        if (queue_copy_i < copy_of_free_slot_id_queue.size() &&
                                slot_i == copy_of_free_slot_id_queue.at(queue_copy_i))
                        {
                            // This slot ID was not in use.

                            queue_copy_i++;
                            continue;
                        }

                        T1& instance = reinterpret_cast<T1*>(this->memory.data())[slot_i];
                        instance.~T1();
                        count++;
                    }
                }

                template<typename... Args>
                    T1* build_in(Args&&... args)
                    {
                        if (this->number_of_instances >= DataSize) [[unlikely]]
                        {
                            // This `MemoryStorage` is already full, can't build anything.
                            return nullptr;
                        }

                        uint32_t slot_i;

                        if (this->size_of_free_slot_id_queue == 0) [[unlikely]]
                        {
                            // Queue is empty.
                            // Use the current number of instances as the index,
                            slot_i = this->number_of_instances;
                        }
                        else [[likely]]
                        {
                            // Queue is not empty.
                            // Use the highest free index as the index.
                            slot_i = this->free_slot_id_queue.at(this->free_slot_id_queue_start_i);

                            // Advance to the next index in a barrel buffer.
                            this->free_slot_id_queue_start_i = (this->free_slot_id_queue_start_i + 1) % DataSize;

                            // The front element of the queue was used.
                            this->size_of_free_slot_id_queue--;
                        }

                        T1* data = reinterpret_cast<T1*>(this->memory.data());
                        auto* instance { new (&data[slot_i]) T1(std::forward<Args>(args)...) };
                        instance->constructible_module = yli::memory::ConstructibleModule(this->storage_i, slot_i);
                        this->number_of_instances++;
                        return instance;
                    }

                void destroy(const uint32_t slot_i)
                {
                    // `slot_i` is not checked here (because it would make `destroy` O(n) operation instead of O(1)).
                    // The caller must make sure that `slot_i` points to an existing instance.
                    T1* instance { &reinterpret_cast<T1*>(this->memory.data())[slot_i] };
                    instance->~T1();

                    this->free_slot_id_queue.at((this->free_slot_id_queue_start_i + this->size_of_free_slot_id_queue) % DataSize) = slot_i;
                    this->size_of_free_slot_id_queue++;
                }

                uint32_t get_storage_id() const
                {
                    return this->storage_i;
                }

                std::uint32_t get_number_of_instances() const
                {
                    return this->number_of_instances;
                }

            private:
                std::array<std::byte, DataSize * sizeof(T1)> memory {};
                std::array<uint32_t, DataSize> free_slot_id_queue {};
                const uint32_t storage_i;
                uint32_t number_of_instances        { 0 };
                uint32_t free_slot_id_queue_start_i { 0 };
                uint32_t size_of_free_slot_id_queue { 0 };
        };
}

#endif