// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2025 Antti Nuortimo.
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

#ifndef YLIKUUTIO_ONTOLOGY_FAMILY_TEMPLATES_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_FAMILY_TEMPLATES_HPP_INCLUDED

#include "registry.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

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

            child.set_childID(yli::hierarchy::request_childID(child_pointer_vector, free_childID_queue));
            // set pointer to the child in parent's child pointer vector so that parent knows about children's whereabouts!
            yli::hierarchy::set_child_pointer(child.get_childID(), &child, child_pointer_vector, free_childID_queue, number_of_children);

            const std::string& name = child.get_local_name();

            if (!name.empty() && !registry.is_name(name))
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

            child.set_childID(yli::hierarchy::request_childID(child_pointer_vector, free_childID_queue));
            // set pointer to the child in parent's child pointer vector so that parent knows about children's whereabouts!
            yli::hierarchy::set_child_pointer(child.get_childID(), &child, child_pointer_vector, free_childID_queue, number_of_children);

            const std::string& name = child->get_local_name();

            if (!name.empty() && entity_map.count(name) == 0)
            {
                entity_map[name] = &child;
            }
        }

    template <typename T1>
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
            yli::hierarchy::set_child_pointer(
                    childID,
                    static_cast<T1>(nullptr),
                    child_pointer_vector,
                    free_childID_queue,
                    number_of_children);
        }

    template <typename T1>
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
            yli::hierarchy::set_child_pointer(childID, static_cast<T1>(nullptr), child_pointer_vector, free_childID_queue, number_of_children);
        }

    template<typename T1>
        std::size_t get_number_of_descendants(const std::vector<T1>& child_pointer_vector) noexcept
        {
            std::size_t number_of_descendants = 0;

            for (std::size_t child_i = 0; child_i < child_pointer_vector.size(); child_i++)
            {
                T1 child_pointer = static_cast<T1>(child_pointer_vector.at(child_i));

                if (child_pointer != nullptr)
                {
                    number_of_descendants += child_pointer->get_number_of_all_descendants() + 1; // +1 for the child itself.
                }
            }

            return number_of_descendants;
        }
}

#endif
