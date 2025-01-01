// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2025 Antti Nuortimo.
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
#include "code/ylikuutio/data/datatype.hpp"

// Include standard headers
#include <cstddef>       // std::size_t
#include <map>           // std::map
#include <stdexcept>     // std::runtime_error
#include <string>        // std::string
#include <utility>       // std::forward

namespace yli::memory
{
    struct ConstructibleModule;

    // `GetTypeEnumFunction` is a function template that return `TypeEnumType` values for different types.
    template<typename TypeEnumType = yli::data::Datatype>
        class MemorySystem final : public yli::memory::GenericMemorySystem
        {
            // Each class instance takes care of memory
            // management for a given application.

            public:
                explicit MemorySystem(TypeEnumType universe_datatype)
                    : universe_datatype { universe_datatype }
                {
                }

                ~MemorySystem()
                {
                    // Delete other except `Universe` allocators.

                    for (auto it = this->memory_allocators.begin(); it != this->memory_allocators.end(); )
                    {
                        if (it->first != this->universe_datatype)
                        {
                            auto old_it = it;
                            ++it;
                            delete old_it->second;
                            this->memory_allocators.erase(old_it);
                        }
                        else
                        {
                            ++it;
                        }
                    }

                    // Delete `Universe` allocator.
                    for (auto it = this->memory_allocators.begin(); it != this->memory_allocators.end(); )
                    {
                        if (it->first == this->universe_datatype)
                        {
                            auto old_it = it;
                            ++it;
                            delete old_it->second;
                            this->memory_allocators.erase(old_it);
                        }
                        else
                        {
                            ++it;
                        }
                    }
                }

                MemorySystem(const MemorySystem&) = delete;            // Delete copy constructor.
                MemorySystem& operator=(const MemorySystem&) = delete; // Delete copy assignment.

                TypeEnumType get_universe_datatype() const
                {
                    return this->universe_datatype;
                }

                yli::memory::MemorySystem<TypeEnumType>& get() const
                {
                    return const_cast<yli::memory::MemorySystem<TypeEnumType>&>(*this);
                }

                std::size_t get_number_of_allocators() const override
                {
                    return this->memory_allocators.size();
                }

                template<typename T1, typename... Args>
                    void create_allocator(int type, Args&&... args)
                    {
                        // TODO: Return the return value of `try_emplace`.
                        // TODO: Throw an exception if creating an allocator fails.
                        this->memory_allocators.try_emplace(type, new T1(type, std::forward<Args>(args)...));
                    }

                // TODO: use `TypeEnumType` instead of `int`!
                bool has_allocator(const int type) const override
                {
                    return this->memory_allocators.contains(type);
                }

                // TODO: use `TypeEnumType` instead of `int`!
                yli::memory::GenericMemoryAllocator& get_generic_allocator(const int type) const override
                {
                    if (this->has_allocator(type)) [[likely]]
                    {
                        return *(this->memory_allocators.at(type));
                    }

                    throw std::runtime_error("ERROR: `MemorySystem::get_generic_allocator`: allocator for type " + std::to_string(type) + " does not exist!");
                }

                template<typename T1, typename... Args>
                    // TODO: use `TypeEnumType` instead of `int`!
                    yli::memory::MemoryAllocator<T1>& get_allocator(const int type) const
                    {
                        if (this->has_allocator(type)) [[likely]]
                        {
                            return static_cast<yli::memory::MemoryAllocator<T1>&>(*(this->memory_allocators.at(type)));
                        }

                        throw std::runtime_error("ERROR: `MemorySystem::get_allocator`: allocator for type " + std::to_string(type) + " does not exist!");
                    }

                virtual void destroy(const yli::memory::ConstructibleModule& constructible_module) override
                {
                    if (constructible_module.alive && constructible_module.generic_allocator != nullptr)
                    {
                        yli::memory::GenericMemoryAllocator& allocator = *constructible_module.generic_allocator;
                        allocator.destroy(constructible_module);
                    }
                }

                template<typename T1, typename... Args>
                    // TODO: use `TypeEnumType` instead of `int`!
                    yli::memory::GenericMemoryAllocator& get_or_create_allocator(int type, Args&&... args)
                    {
                        if (this->has_allocator(type))
                        {
                            return this->get_generic_allocator(type);
                        }

                        this->create_allocator<T1, Args...>(type, std::forward<Args>(args)...);
                        return this->get_generic_allocator(type);
                    }

            private:
                // Allocators need to be created elsewhere and only stored here.
                // TODO: use `TypeEnumType` as the key type instead of `int`!
                std::map<int, yli::memory::GenericMemoryAllocator*> memory_allocators;
                const TypeEnumType universe_datatype;
        };
}

#endif
