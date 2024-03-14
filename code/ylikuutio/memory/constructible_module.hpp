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

#ifndef YLIKUUTIO_MEMORY_CONSTRUCTIBLE_MODULE_HPP_INCLUDED
#define YLIKUUTIO_MEMORY_CONSTRUCTIBLE_MODULE_HPP_INCLUDED

// Include standard headers
#include <cstddef>  // std::size_t
#include <limits>   // std::numeric_limits

namespace yli::memory
{
    struct ConstructibleModule
    {
        ConstructibleModule()
        {
        }

        ConstructibleModule(int datatype, const std::size_t storage_i, const std::size_t slot_i)
            : datatype { datatype },
            storage_i { storage_i },
            slot_i { slot_i }
        {
        }

        int datatype          { 0 }; // Unknown type.
        std::size_t storage_i { std::numeric_limits<std::size_t>::max() };
        std::size_t slot_i    { std::numeric_limits<std::size_t>::max() };
        bool alive            { true };
    };
}

#endif
