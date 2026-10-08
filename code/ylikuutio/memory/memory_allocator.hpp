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

#ifndef YLIKUUTIO_MEMORY_MEMORY_ALLOCATOR_HPP_INCLUDED
#define YLIKUUTIO_MEMORY_MEMORY_ALLOCATOR_HPP_INCLUDED

#include "generic_memory_allocator.hpp"
#include "constructible_module.hpp"
#include "code/ylikuutio/data/queue.hpp"
#include "code/ylikuutio/ontology/console_lisp_function_overload.hpp"

// Include standard headers
#include <array>      // std::array
#include <cstddef>    // std::byte, std::size_t
#include <iostream>   // std::cerr
#include <limits>     // std::numeric_limits
#include <memory>     // std::make_unique, std::unique_ptr
#include <new>        // std::launder
#include <stdexcept>  // std::runtime_error
#include <string>     // std::to_string
#include <utility>    // std::forward

namespace yli::ontology
{
    class GenericConsoleLispFunctionOverload;
}

namespace yli::memory
{
    template<typename T1 = std::byte, std::size_t DataSize = 1>
    class MemoryAllocator : public GenericMemoryAllocator
    {
        // Each class instance takes care of the memory
        // management for some given storable datatype.

    public:
        explicit MemoryAllocator(const int datatype)
            : datatype { datatype }
        { }

        ~MemoryAllocator() override
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
                typename data::Queue<DataSize>::iterator left_it = this->free_slot_id_queue.begin();
                left_it != this->free_slot_id_queue.last();
                ++left_it)
            {
                typename data::Queue<DataSize>::iterator right_it = this->free_slot_id_queue.begin();
                ++right_it;

                for (; right_it != this->free_slot_id_queue.last(); ++right_it)
                {
                    if (*left_it > *right_it)
                    {
                        const std::size_t temp = *left_it;
                        *left_it = *right_it;
                        *right_it = temp;
                    }
                }
            }

            typename data::Queue<DataSize>::iterator queue_it = this->free_slot_id_queue.begin();

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

        MemoryAllocator(const MemoryAllocator&) = delete; // Delete copy constructor.
        MemoryAllocator& operator=(const MemoryAllocator&) = delete; // Delete copy assignment.

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

            T1* instance = new(this->memory.data() + (slot_i * sizeof(T1))) T1(std::forward<Args>(args)...);
            instance->constructible_module = ConstructibleModule(*this, slot_i);
            ++this->number_of_instances;
            return instance;
        }

        [[nodiscard]] std::size_t get_datatype() const override
        {
            return this->datatype;
        }

        [[nodiscard]] std::size_t get_number_of_instances() const override
        {
            return this->number_of_instances;
        }

        [[nodiscard]] static std::size_t get_data_size()
        {
            return DataSize;
        }

        void destroy(const ConstructibleModule& constructible_module) override
        {
            if (constructible_module.slot_i == std::numeric_limits<std::size_t>::max())
            {
                std::cerr << "ERROR: `MemoryAllocator::destroy`: `constructible_module.slot_i` has invalid value!\n";
                return;
            }

            if (constructible_module.slot_i >= DataSize) [[unlikely]]
            {
                throw std::runtime_error(
                    "ERROR: `MemoryAllocator::destroy`: `slot_i` " + std::to_string(constructible_module.slot_i) +
                    " is out of bounds, `DataSize` is " + std::to_string(DataSize));
            }

            // `slot_i` is not checked here (because it would make `destroy` O(n) operation instead of O(1)).
            // The caller must make sure that `slot_i` points to an existing instance.
            T1* data = std::launder(reinterpret_cast<T1*>(this->memory.data()));
            T1* instance { &data[constructible_module.slot_i] };
            instance->~T1();

            // Push the freed index to the queue.
            this->free_slot_id_queue.push(constructible_module.slot_i);
            --this->number_of_instances;
        }

    private:
        const int datatype;
        alignas(T1) std::array<std::byte, DataSize * sizeof(T1)> memory {};
        data::Queue<DataSize> free_slot_id_queue;
        std::size_t number_of_instances { 0 };
    };

    template<std::size_t DataSize>
    class MemoryAllocator<ontology::GenericConsoleLispFunctionOverload, DataSize> : public GenericMemoryAllocator
    {
    public:
        explicit MemoryAllocator(const int datatype)
            : datatype { datatype }
        { }

        ~MemoryAllocator() override
        {
            for (auto* const instance : this->instances)
            {
                delete instance;
            }
        }

        MemoryAllocator(const MemoryAllocator&) = delete; // Delete copy constructor.
        MemoryAllocator& operator=(const MemoryAllocator&) = delete; // Delete copy assignment.

        template<typename... Args>
        ontology::GenericConsoleLispFunctionOverload* build_in(Args&&... args)
        {
            ontology::GenericConsoleLispFunctionOverload* function_overload =
                    new ontology::ConsoleLispFunctionOverload(std::forward<Args>(args)...);

            if (this->free_slotID_queue.empty())
            {
                function_overload->constructible_module = ConstructibleModule(
                    *this, this->free_slotID_queue.size());
                this->instances.emplace_back(function_overload);
            }
            else
            {
                const std::size_t slot_i = this->free_slotID_queue.front();
                this->free_slotID_queue.pop();
                function_overload->constructible_module = ConstructibleModule(*this, slot_i);
                this->instances.at(slot_i) = function_overload;
            }

            return function_overload;
        }

        [[nodiscard]] std::size_t get_datatype() const override
        {
            return this->datatype;
        }

        [[nodiscard]] std::size_t get_number_of_instances() const override
        {
            return this->instances.size();
        }

        void destroy(const ConstructibleModule& constructible_module) noexcept override
        {
            delete this->instances.at(constructible_module.slot_i);
            this->instances.at(constructible_module.slot_i) = nullptr;
            this->free_slotID_queue.push(constructible_module.slot_i);
        }

    private:
        const int datatype;
        std::vector<ontology::GenericConsoleLispFunctionOverload*> instances;
        std::queue<std::size_t> free_slotID_queue;
    };
}

#endif
