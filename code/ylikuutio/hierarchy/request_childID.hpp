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

#ifndef YLIKUUTIO_HIERARCHY_REQUEST_CHILD_ID_HPP_INCLUDED
#define YLIKUUTIO_HIERARCHY_REQUEST_CHILD_ID_HPP_INCLUDED

// Include standard headers
#include <cstddef> // std::size_t
#include <queue>   // std::queue
#include <vector>  // std::vector

namespace yli::hierarchy
{
    template<typename T1>
    std::size_t request_childID(std::vector<T1>& child_pointer_vector,
                                std::queue<std::size_t>& free_childID_queue) noexcept
    {
        // This function is called eg. from `bind_child_to_parent`,
        // so that child instance gets an appropriate `childID`.
        std::size_t childID;

        while (!free_childID_queue.empty())
        {
            // return the first (oldest) free childID.
            childID = free_childID_queue.front();
            free_childID_queue.pop();

            // check that the child index does not exceed current child pointer vector.
            if (childID >= child_pointer_vector.size())
            {
                // Child index exceeds current child pointer vector.
                continue;
            }

            if (child_pointer_vector.at(childID) == nullptr)
            {
                // OK, child index does not exceed current child pointer vector and the index is free.
                return childID;
            }
        }

        // OK, the queue is empty.
        // A new child index must be created.
        childID = child_pointer_vector.size();

        // child pointer vector must also be extended with an appropriate nullptr pointer.
        child_pointer_vector.emplace_back(nullptr);

        return childID;
    }
}

#endif
