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

#ifndef YLIKUUTIO_MEMORY_CONSTRUCTIBLE_MODULE_HPP_INCLUDED
#define YLIKUUTIO_MEMORY_CONSTRUCTIBLE_MODULE_HPP_INCLUDED

#include "constructible_module.hpp"
#include "abstract_memory_allocator.hpp"
#include "handle.hpp"

namespace yli::memory
{
    struct ConstructibleModule
    {
        ConstructibleModule(AbstractMemoryAllocator& generic_allocator, const Handle& handle)
            : generic_allocator { &generic_allocator },
              handle { handle }
        { }

        ConstructibleModule(const ConstructibleModule& other)
            : generic_allocator { other.generic_allocator },
              handle { other.handle }
        { }

        ~ConstructibleModule()
        {
            this->generic_allocator->mark_destroyed(handle);
        }

        ConstructibleModule& operator=(const ConstructibleModule& other)
        {
            this->generic_allocator = other.generic_allocator;
            this->handle = other.handle;
            this->alive = other.alive;
            return *this;
        }

        AbstractMemoryAllocator* generic_allocator { nullptr };
        Handle handle; // Default value 0 means invalid handle.
        bool alive { true };
    };
}

#endif
