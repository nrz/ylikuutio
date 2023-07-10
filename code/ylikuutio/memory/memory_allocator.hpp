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

#ifndef YLIKUUTIO_MEMORY_MEMORY_ALLOCATOR_HPP_INCLUDED
#define YLIKUUTIO_MEMORY_MEMORY_ALLOCATOR_HPP_INCLUDED

#include "generic_memory_allocator.hpp"
#include "memory_storage.hpp"
#include "constructible_module.hpp"
#include "code/ylikuutio/ontology/lisp_function_overload.hpp"

// Include standard headers
#include <cstddef>   // std::byte, std::size_t
#include <limits>    // std::numeric_limits
#include <memory>    // std::make_unique, std::unique_ptr
#include <stdexcept> // std::runtime_error
#include <sstream>   // std::stringstream
#include <utility>   // std::forward, std::move
#include <vector>    // std::vector

namespace yli::ontology
{
    class GenericLispFunctionOverload;
}

namespace yli::memory
{
    template<typename T1 = std::byte, std::size_t DataSize = 1>
        class MemoryAllocator : public yli::memory::GenericMemoryAllocator
        {
            // Each class instance takes care of the memory storage
            // management for some given storable datatype.

            public:
                MemoryAllocator() = default;

                template<typename... Args>
                    T1* build_in(int datatype, Args&&... args)
                    {
                        for (auto& storage : this->storages)
                        {
                            T1* instance = storage->build_in(datatype, std::forward<Args>(args)...);

                            if (instance != nullptr)
                            {
                                return instance;
                            }
                        }

                        // Pass number of storages to `MemoryStorage` constructor as the `storage_i`.
                        // This assumes that storages can not be deleted (except in `MemoryAllocator`'s destructor).
                        const std::size_t storage_i { this->storages.size() };
                        auto storage = std::make_unique<yli::memory::MemoryStorage<T1, DataSize>>(storage_i);
                        this->storages.emplace_back(std::move(storage));
                        return this->storages.back()->build_in(datatype, std::forward<Args>(args)...);
                    }

                std::size_t get_number_of_storages() const override
                {
                    return this->storages.size();
                }

                std::size_t get_number_of_instances() const override
                {
                    std::size_t count { 0 };

                    for (const auto& storage : this->storages)
                    {
                        count += storage->get_number_of_instances();
                    }

                    return count;
                }

                std::size_t get_data_size() const
                {
                    return DataSize;
                }

                yli::memory::MemoryStorage<T1, DataSize>& get_storage(const std::size_t storage_i) const
                {
                    if (storage_i == std::numeric_limits<std::size_t>::max())
                    {
                        throw std::runtime_error("ERROR: `MemoryAllocator::get_storage`: trying to get storage with an invalid `storage_i`!");
                    }

                    if (storage_i >= this->get_number_of_storages())
                    {
                        std::stringstream runtime_error_stringstream;
                        runtime_error_stringstream << "ERROR: `MemoryAllocator::get_storage`: `storage_i` " << storage_i <<
                            " is out of bounds, size is " << this->get_number_of_storages();
                        throw std::runtime_error(runtime_error_stringstream.str());
                    }

                    auto raw_storage_pointer = this->storages.at(storage_i).get();

                    if (raw_storage_pointer == nullptr)
                    {
                        std::stringstream runtime_error_stringstream;
                        runtime_error_stringstream << "ERROR: `MemoryAllocator::get_storage`: `storage_i` " << storage_i <<
                            " is `nullptr`!";
                        throw std::runtime_error(runtime_error_stringstream.str());
                    }

                    return *raw_storage_pointer;
                }

                void destroy(const yli::memory::ConstructibleModule& constructible_module) override
                {
                    if (constructible_module.storage_i == std::numeric_limits<std::size_t>::max())
                    {
                        throw std::runtime_error("ERROR: `MemoryAllocator::destroy`: `constructible_module.storage_i` has invalid value!");
                    }

                    if (constructible_module.slot_i == std::numeric_limits<std::size_t>::max())
                    {
                        throw std::runtime_error("ERROR: `MemoryAllocator::destroy`: `constructible_module.slot_i` has invalid value!");
                    }

                    if (constructible_module.storage_i >= this->get_number_of_storages())
                    {
                        std::stringstream runtime_error_stringstream;
                        runtime_error_stringstream << "ERROR: `MemoryAllocator::destroy`: `storage_i` " <<
                            constructible_module.storage_i << " is out of bounds, size is " << this->get_number_of_storages();
                        throw std::runtime_error(runtime_error_stringstream.str());
                    }

                    auto& storage = this->get_storage(constructible_module.storage_i);
                    storage.destroy(constructible_module.slot_i);
                }

            private:
                std::vector<std::unique_ptr<yli::memory::MemoryStorage<T1, DataSize>>> storages;
        };

    template<std::size_t DataSize>
        class MemoryAllocator<yli::ontology::GenericLispFunctionOverload, DataSize> : public yli::memory::GenericMemoryAllocator
        {
            public:
                MemoryAllocator() = default;

                ~MemoryAllocator()
                {
                    for (auto* instance : this->instances)
                    {
                        delete instance;
                    }
                }

                template<typename... Args>
                    yli::ontology::GenericLispFunctionOverload* build_in(Args&&... args)
                    {
                        yli::ontology::GenericLispFunctionOverload* function_overload =
                            new yli::ontology::LispFunctionOverload(std::forward<Args>(args)...);
                        this->instances.emplace_back(function_overload);
                        return function_overload;
                    }

                std::size_t get_number_of_storages() const override
                {
                    return 1;
                }

                std::size_t get_number_of_instances() const override
                {
                    return this->instances.size();
                }

                void destroy(const yli::memory::ConstructibleModule& constructible_module) override
                {
                    // TODO
                }

            private:
                std::vector<yli::ontology::GenericLispFunctionOverload*> instances;
        };
}

#endif
