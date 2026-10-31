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

#ifndef YLIKUUTIO_MEMORY_HANDLE_HPP_INCLUDED
#define YLIKUUTIO_MEMORY_HANDLE_HPP_INCLUDED

// Include standard headers
#include <cstdint> // std::uint32_t

namespace yli::memory
{
    struct Handle
    {
        static constexpr std::uint32_t n_type_bits { 10 };
        static constexpr std::uint32_t n_slot_bits { 22 };
        static_assert(n_type_bits + n_slot_bits == 32, "`n_type_bits` + `n_slot_bits` must be equal to 32.");

        static constexpr std::uint32_t max_type { (1 << (n_type_bits)) - 1 };
        static constexpr std::uint32_t max_slot { (1 << (n_slot_bits)) - 1 };

        Handle(const std::uint32_t type, const std::uint32_t slot_i)
            : handle { type <= max_type && slot_i <= max_slot ? ((type << n_slot_bits) | slot_i) : 0 }
        { }

        explicit Handle(const std::uint32_t handle)
            : handle { handle }
        { }

        explicit Handle(const Handle& other_handle)
            : handle { other_handle.handle }
        { }

        Handle& operator=(const Handle& other)
        {
            this->handle = other.handle;
            return *this;
        }

        std::uint32_t get_type() const
        {
            return this->handle >> n_slot_bits;
        }

        std::uint32_t get_slot_i() const
        {
            return this->handle & ((1 << n_slot_bits) - 1);
        }

        std::uint32_t handle { 0 }; // Default value 0 means invalid handle.
    };
}

#endif
