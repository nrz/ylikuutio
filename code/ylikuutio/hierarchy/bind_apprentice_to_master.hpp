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

#ifndef YLIKUUTIO_HIERARCHY_BIND_APPRENTICE_TO_MASTER_HPP_INCLUDED
#define YLIKUUTIO_HIERARCHY_BIND_APPRENTICE_TO_MASTER_HPP_INCLUDED

#include "request_childID.hpp"
#include "set_child_pointer.hpp"

// Include standard headers
#include <cstddef>       // std::size_t
#include <queue>         // std::queue
#include <vector>        // std::vector

namespace yli::hierarchy
{
    template<typename T1>
    void bind_apprentice_to_master(
        T1& apprentice,
        std::vector<T1*>& apprentice_pointer_vector,
        std::queue<std::size_t>& free_apprenticeID_queue,
        std::size_t& number_of_apprentices) noexcept
    {
        // Note: this function must be used only for
        // master-apprentice relationships.
        //
        // Child-parent relationships must be implemented
        // using `yli::hierarchy::bind_child_to_parent`.

        apprentice.apprenticeID = request_childID(apprentice_pointer_vector, free_apprenticeID_queue);
        // set pointer to the apprentice in master's apprentice pointer vector so that master knows about apprentices' whereabouts!
        set_child_pointer(apprentice.apprenticeID, &apprentice, apprentice_pointer_vector, free_apprenticeID_queue,
                          number_of_apprentices);
    }
}

#endif
