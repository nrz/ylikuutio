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

#ifndef YLIKUUTIO_MEMORY_GENERIC_MEMORY_SYSTEM_HPP_INCLUDED
#define YLIKUUTIO_MEMORY_GENERIC_MEMORY_SYSTEM_HPP_INCLUDED

// Include standard headers
#include <cstddef> // std::size_t

namespace yli::memory
{
    class GenericMemoryAllocator;
    struct ConstructibleModule;

    class GenericMemorySystem
    {
        // `GenericMemorySystem` provides an interface
        // for the `MemorySystem` class template instantiations.

        public:
            virtual ~GenericMemorySystem() = default;

            virtual std::size_t get_number_of_allocators() const = 0;

            // TODO: use `TypeEnumType` instead of `int`!
            virtual bool has_allocator(const int type) const = 0;

            // TODO: use `TypeEnumType` instead of `int`!
            virtual yli::memory::GenericMemoryAllocator& get_generic_allocator(const int type) const = 0;

            virtual void destroy(const yli::memory::ConstructibleModule& constructible_module) = 0;
    };
}

#endif
