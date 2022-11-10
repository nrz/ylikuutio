// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2022 Antti Nuortimo.
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

// Include standard headers
#include <array>      // std::array
#include <cstddef>    // std::byte
#include <queue>      // std::priority_queue
#include <stdint.h>   // uint32_t
#include <utility>    // std::forward

namespace yli::memory
{
    template<typename T1 = std::byte, uint32_t DataSize = 1>
        class MemoryStorage
        {
            // `MemoryStorage` instance takes care of single memory storage.

            public:
                explicit MemoryStorage(const uint32_t storageID)
                    : storageID { storageID }
                {
                }

                ~MemoryStorage()
                {
                    if (this->number_of_instances == 0) [[unlikely]]
                    {
                        // No instances to destroy.
                        return;
                    }

                    for (uint32_t index_plus_1 = this->highest_potential_slotID + 1; index_plus_1 > 0; index_plus_1--)
                    {
                        const uint32_t index = index_plus_1 - 1;

                        if (!this->free_slotID_queue.empty() && index == this->free_slotID_queue.top())
                        {
                            // This slot ID is not in use, nothing to destroy there.
                            this->free_slotID_queue.pop();
                            continue;
                        }

                        this->free_slotID_queue.pop();
                        T1& instance = reinterpret_cast<T1*>(this->memory.data())[index];
                        instance.~T1();
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

                        uint32_t index;

                        if (this->free_slotID_queue.empty()) [[unlikely]]
                        {
                            // Queue is empty.
                            // Use the current number of instances as the index,
                            index = this->number_of_instances;
                        }
                        else [[likely]]
                        {
                            // Queue is not empty.
                            // Use the highest free index as the index.
                            index = free_slotID_queue.top();
                            free_slotID_queue.pop();
                        }

                        if (this->number_of_instances == 0) [[unlikely]]
                        {
                            // There was no instances.
                            this->highest_potential_slotID = index;
                        }
                        else if (index > this->highest_potential_slotID) [[likely]]
                        {
                            // New index is the highest potential index.
                            this->highest_potential_slotID = index;
                        }

                        this->number_of_instances++;
                        T1* data = reinterpret_cast<T1*>(this->memory.data());
                        auto* instance { new (&data[index]) T1(std::forward<Args>(args)...) };
                        instance->storage_and_slotID = (static_cast<uint64_t>(this->storageID) << 32) | index;
                        return instance;
                    }

                void destroy(uint32_t index)
                {
                    T1* instance { &reinterpret_cast<T1*>(this->memory.data())[index] };
                    instance->~T1();

                    this->free_slotID_queue.push(index);

                    if (--this->number_of_instances == 0) [[unlikely]]
                    {
                        // No instances currently.
                        this->highest_potential_slotID = 0;
                    }
                }

                uint32_t get_storageID() const
                {
                    return this->storageID;
                }

                std::uint32_t get_number_of_instances() const
                {
                    return this->number_of_instances;
                }

            private:
                std::array<std::byte, DataSize * sizeof(T1)> memory {};
                std::priority_queue<uint32_t, std::vector<uint32_t>> free_slotID_queue;
                const uint32_t storageID;
                uint32_t number_of_instances      { 0 };
                uint32_t highest_potential_slotID { 0 };
        };
}

#endif
