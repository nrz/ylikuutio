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

#ifndef YLIKUUTIO_HIERARCHY_SET_CHILD_POINTER_HPP_INCLUDED
#define YLIKUUTIO_HIERARCHY_SET_CHILD_POINTER_HPP_INCLUDED

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cerr
#include <limits>   // std::numeric_limits
#include <queue>    // std::queue
#include <vector>   // std::vector

namespace yli::hierarchy
{
    template<typename T1>
    void set_child_pointer(
        const std::size_t childID,
        const T1 child_pointer,
        std::vector<T1>& child_pointer_vector,
        std::queue<std::size_t>& free_childID_queue,
        std::size_t& number_of_children) noexcept
    {
        // requirements:
        // `childID` must not be `std::numeric_limits<std::size_t>::max()`.
        //     (`std::numeric_limits<std::size_t>::max()` as `childID` value means that `childID` is uninitialized).

        if (childID == std::numeric_limits<std::size_t>::max())
        {
            std::cerr << "ERROR: `yli::hierarchy::set_child_pointer`: `childID` is uninitialized!\n";
            return;
        }

        if (childID >= child_pointer_vector.size())
        {
            std::cerr << "ERROR: `yli::hierarchy::set_child_pointer`: `childID` " << childID <<
                    " is out of bounds, size is " << child_pointer_vector.size() << "\n";
            return;
        }

        child_pointer_vector.at(childID) = child_pointer;

        if (child_pointer == nullptr)
        {
            if (childID == child_pointer_vector.size() - 1)
            {
                // OK, this is the biggest childID of all childID's of this 'object'.
                // We can reduce the size of the child pointer vector at least by 1.
                while ((!child_pointer_vector.empty()) && (child_pointer_vector.back() == nullptr))
                {
                    // Reduce the size of child pointer vector by 1.
                    child_pointer_vector.pop_back();
                }
            }
            else
            {
                // `childID` is not the highest allocated `childID`.
                // Therefore, store `childID` for the future use.
                free_childID_queue.push(childID);
            }

            // 1 child less.
            if (number_of_children > 0)
            {
                number_of_children--;
            }
        }
        else
        {
            // 1 child more.
            number_of_children++;
        }
    }
}

#endif
