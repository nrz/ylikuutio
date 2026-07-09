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

#ifndef YLIKUUTIO_ONTOLOGY_UNBIND_CHILD_FROM_PARENT_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_UNBIND_CHILD_FROM_PARENT_HPP_INCLUDED

#include "registry.hpp"
#include "code/ylikuutio/hierarchy/set_child_pointer.hpp"

// Include standard headers
#include <cstddef>       // std::size_t
#include <iostream>      // std::cout, std::cerr
#include <limits>        // std::numeric_limits
#include <queue>         // std::queue
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

namespace yli::ontology
{
    class Entity;

    template<typename T1>
    void unbind_child_from_parent(
        const std::size_t childID,
        const std::string& name,
        std::vector<T1>& child_pointer_vector,
        std::queue<std::size_t>& free_childID_queue,
        std::size_t& number_of_children,
        Registry& registry) noexcept
    {
        // requirements:
        // `child_pointer->childID` must not be `std::numeric_limits<std::size_t>::max()`.
        //     (`std::numeric_limits<std::size_t>::max()` as `childID` value means that `childID` is uninitialized).

        if (childID == std::numeric_limits<std::size_t>::max())
        {
            std::cerr << "ERROR: `unbind_child_from_parent`: `childID` is uninitialized!\n";
            return;
        }

        if (!name.empty() && registry.is_entity(name))
        {
            // Erase the name from the `entity_map`.
            registry.erase_entity(name);
        }

        // Set pointer to this child to `nullptr` in the old parent.
        hierarchy::set_child_pointer(
            childID,
            static_cast<T1>(nullptr),
            child_pointer_vector,
            free_childID_queue,
            number_of_children);
    }

    template<typename T1>
    void unbind_child_from_parent(
        const std::size_t childID,
        const std::string& name,
        std::vector<T1>& child_pointer_vector,
        std::queue<std::size_t>& free_childID_queue,
        std::size_t& number_of_children,
        std::unordered_map<std::string, Entity*>& entity_map) noexcept
    {
        // requirements:
        // `child_pointer->childID` must not be `std::numeric_limits<std::size_t>::max()`.
        //     (`std::numeric_limits<std::size_t>::max()` as `childID` value means that `childID` is uninitialized).

        if (childID == std::numeric_limits<std::size_t>::max())
        {
            std::cerr << "ERROR: `unbind_child_from_parent`: `childID` is uninitialized!\n";
            return;
        }

        if (!name.empty() && entity_map.count(name) == 1)
        {
            // Erase the name from the `entity_map`.
            entity_map.erase(name);
        }

        // Set pointer to this child to `nullptr` in the old parent.
        hierarchy::set_child_pointer(childID, static_cast<T1>(nullptr), child_pointer_vector, free_childID_queue,
                                     number_of_children);
    }
}

#endif
