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

#ifndef YLIKUUTIO_MEMORY_MEMORY_SYSTEM_HPP_INCLUDED
#define YLIKUUTIO_MEMORY_MEMORY_SYSTEM_HPP_INCLUDED

#include "generic_memory_system.hpp"
#include "generic_memory_allocator.hpp"
#include "memory_allocator.hpp"
#include "code/ylikuutio/core/application.hpp"
#include "code/ylikuutio/data/datatype.hpp"
#include "code/ylikuutio/ontology/universe.hpp"

// Include standard headers
#include <unordered_map> // std::unordered_map
#include <stdexcept>     // std::runtime_error
#include <stdint.h>      // uint32_t
#include <sstream>       // std::stringstream
#include <utility>       // std::forward
#include <iostream>      // std::cout, std::cin, std::cerr

namespace yli::memory
{
    // `GetTypeEnumFunction` is a function template that return `TypeEnumType` values for different types.
    template<typename TypeEnumType = yli::data::Datatype>
        class MemorySystem final : public yli::memory::GenericMemorySystem
        {
            // Each class instance takes care of memory
            // management for a given application.

            public:
                MemorySystem(yli::core::Application* const application, TypeEnumType universe_datatype)
                    : universe_datatype { universe_datatype }
                {
                    // `application` is given as a pointer to enable
                    // unit testing without a mock `Application` derivative.
                    if (application != nullptr) [[likely]]
                    {
                        std::cout << "Creating memory allocators.\n";
                        application->create_memory_allocators();
                    }
                }

                ~MemorySystem()
                {
                    // Delete other except `Universe` allocators.
                    std::cout << "Deleting memory allocators except the `Universe` allocator.\n";

                    for (auto [type, allocator] : this->memory_allocators)
                    {
                        if (type != this->universe_datatype)
                        {
                            delete allocator;
                        }
                    }

                    std::cout << "Deleting the `Universe` allocator.\n";

                    // Delete `Universe` allocator.
                    for (auto [type, allocator] : this->memory_allocators)
                    {
                        if (type == this->universe_datatype)
                        {
                            delete allocator;
                            std::cout << "`Universe` allocator deleted.\n";
                        }
                    }
                }

                TypeEnumType get_universe_datatype() const
                {
                    return this->universe_datatype;
                }

                yli::memory::MemorySystem<TypeEnumType>& get() const
                {
                    return const_cast<yli::memory::MemorySystem<TypeEnumType>&>(*this);
                }

                uint32_t get_number_of_allocators() const override
                {
                    return this->memory_allocators.size();
                }

                // There is no allocator building function here because
                // different allocators may need different `DataSize`
                // template argument values. Construct the allocator elsewhere
                // and acquire its ownership by passing it to `store_allocator`.

                template<typename T1, typename... Args>
                    void create_allocator(int type, Args&&... args)
                    {
                        // TODO: Return the return value of `try_emplace`.
                        // TODO: Throw an exception if creating an allocator fails.
                        std::cout << "Creating memory allocator of type " << type << "\n";
                        this->memory_allocators.try_emplace(type, new T1(std::forward<Args>(args)...));
                    }

                // TODO: use `TypeEnumType` instead of `int`!
                bool has_allocator(const int type) const override
                {
                    return this->memory_allocators.contains(type);
                }

                // TODO: use `TypeEnumType` instead of `int`!
                yli::memory::GenericMemoryAllocator& get_allocator(const int type) const override
                {
                    if (this->has_allocator(type))
                    {
                        return *(this->memory_allocators.at(type));
                    }

                    std::stringstream runtime_error_stringstream;
                    runtime_error_stringstream <<
                        "ERROR: `MemorySystem::get_allocator`: allocator for type " << type << " does not exist!";
                    throw std::runtime_error(runtime_error_stringstream.str());
                }

                template<typename T1, typename... Args>
                    // TODO: use `TypeEnumType` instead of `int`!
                    yli::memory::GenericMemoryAllocator& get_or_create_allocator(int type, Args&&... args)
                    {
                        if (this->has_allocator(type))
                        {
                            return this->get_allocator(type);
                        }

                        this->create_allocator<T1, Args...>(type, std::forward<Args>(args)...);
                        return this->get_allocator(type);
                    }

                // TODO: use `TypeEnumType` instead of `int`!
                bool store_allocator(int type, yli::memory::GenericMemoryAllocator* allocator)
                {
                    if (!this->has_allocator(type))
                    {
                        this->memory_allocators[type] = allocator;

                        // Storing the allocator succeeded.
                        return true;
                    }

                    // Storing the allocator failed.
                    return false;
                }

            private:
                // Allocators need to be created elsewhere and only stored here.
                // TODO: use `TypeEnumType` as the key type instead of `int`!
                std::unordered_map<int, yli::memory::GenericMemoryAllocator*> memory_allocators;
                const TypeEnumType universe_datatype;
        };
}

#endif
