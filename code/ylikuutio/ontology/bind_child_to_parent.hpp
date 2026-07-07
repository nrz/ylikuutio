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

#ifndef YLIKUUTIO_ONTOLOGY_BIND_CHILD_TO_PARENT_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_BIND_CHILD_TO_PARENT_HPP_INCLUDED

#include "registry.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef>       // std::size_t
#include <queue>         // std::queue
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

namespace yli::ontology
{
    class Entity;

    template<typename T1>
        void bind_child_to_parent(
                T1& child,
                std::vector<T1*>& child_pointer_vector,
                std::queue<std::size_t>& free_childID_queue,
                std::size_t& number_of_children,
                Registry& registry) noexcept
    {
        // If a class' instances have parents, this function must be
        // called in the constructor. The call must be done only once
        // in each constructor, usually after setting
        // `this->parent`. So, get `childID` from the parent,
        // because every child deserves a unique ID!
        // If `ChildModule` is used, then it will
        // take care of calling this function and in that case
        // this function must not be called elsewhere.
        // Note: this function modifies child's `childID` and thus
        // the child must define this function template as a `friend`.
        // Note: this function must be used only for child-parent
        // relationships. Other binding relationships, that is
        // master-apprentice relationships, must be implemented
        // using `bind_apprentice_to_master`, not this function.

        child.set_childID(hierarchy::request_childID(child_pointer_vector, free_childID_queue));
        // set pointer to the child in parent's child pointer vector so that parent knows about children's whereabouts!
        hierarchy::set_child_pointer(child.get_childID(), &child, child_pointer_vector, free_childID_queue, number_of_children);

        if (const std::string& name = child.get_local_name(); !name.empty() && !registry.is_name(name))
        {
            registry.add_entity(child, name);
        }
    }

    template<typename T1>
        void bind_child_to_parent(
                const T1& child,
                std::vector<T1*>& child_pointer_vector,
                std::queue<std::size_t>& free_childID_queue,
                std::size_t& number_of_children,
                std::unordered_map<std::string, Entity*>& entity_map) noexcept
    {
        // If a class' instances have parents, this function must be
        // called in the constructor. The call must be done only once
        // in each constructor, usually after setting
        // `this->parent`. So, get `childID` from the parent,
        // because every child deserves a unique ID!
        // If `ChildModule` is used, then it will
        // take care of calling this function and in that case
        // this function must not be called elsewhere.
        // Note: this function modifies child's `childID` and thus
        // the child must define this function template as a `friend`.
        // Note: this function must be used only for child-parent
        // relationships. Other binding relationships, that is
        // master-apprentice relationships, must be implemented
        // using `bind_apprentice_to_master`, not this function.

        child.set_childID(hierarchy::request_childID(child_pointer_vector, free_childID_queue));
        // set pointer to the child in parent's child pointer vector so that parent knows about children's whereabouts!
        hierarchy::set_child_pointer(child.get_childID(), &child, child_pointer_vector, free_childID_queue, number_of_children);

        if (const std::string& name = child->get_local_name(); !name.empty() && !entity_map.contains(name))
        {
            entity_map[name] = &child;
        }
    }
}

#endif
