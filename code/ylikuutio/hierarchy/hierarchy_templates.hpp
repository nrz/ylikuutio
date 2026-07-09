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

#ifndef YLIKUUTIO_HIERARCHY_HIERARCHY_TEMPLATES_HPP_INCLUDED
#define YLIKUUTIO_HIERARCHY_HIERARCHY_TEMPLATES_HPP_INCLUDED

#include "set_child_pointer.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <limits>  // std::numeric_limits
#include <queue>   // std::queue
#include <vector>  // std::vector

namespace yli::hierarchy
{
    template<typename T1>
    void unbind_child_from_parent(
        const std::size_t childID,
        std::vector<T1>& child_pointer_vector,
        std::queue<std::size_t>& free_childID_queue,
        std::size_t& number_of_children) noexcept
    {
        if (childID == std::numeric_limits<std::size_t>::max())
        {
            // Nothing to do.
            return;
        }

        // Set pointer to this child to `nullptr` in the old parent.
        set_child_pointer(childID, static_cast<T1>(nullptr), child_pointer_vector, free_childID_queue,
                          number_of_children);
    }
}

#endif
