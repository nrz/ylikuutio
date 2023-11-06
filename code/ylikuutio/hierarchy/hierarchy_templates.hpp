// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2023 Antti Nuortimo.
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

// Include standard headers
#include <cstddef>       // std::size_t
#include <iostream>      // std::cerr
#include <limits>        // std::numeric_limits
#include <queue>         // std::queue
#include <vector>        // std::vector

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
                std::cerr << "ERROR: `yli::hierarchy::set_child_pointer`: `childID` " << childID << " is out of bounds, size is " << child_pointer_vector.size() << "\n";
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

    template<typename T1>
        std::size_t request_childID(std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue) noexcept
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

    template<typename T1>
        void bind_child_to_parent(
                const T1& child,
                std::vector<T1>& child_pointer_vector,
                std::queue<std::size_t>& free_childID_queue,
                std::size_t& number_of_children) noexcept
        {
            // If a class' instances have parents, this function must be
            // called in the constructor. The call must be done only once
            // in each constructor, usually after setting
            // `this->parent`. So, get `childID` from the parent,
            // because every child deserves a unique ID!
            // If `yli::ontology::ChildModule` is used, then it will
            // take care of calling this function and in that case
            // this function must not be called elsewhere.
            // Note: this function modifies child's `childID` and thus
            // the child must define this function template as a `friend`.
            // Note: this function must be used only for child-parent
            // relationships. Other binding relationships, that is
            // master-apprentice relationships, must be implemented
            // using `bind_apprentice_to_master`, not this function.

            child.childID = yli::hierarchy::request_childID(child_pointer_vector, free_childID_queue);
            // set pointer to the child in parent's child pointer vector so that parent knows about children's whereabouts!
            yli::hierarchy::set_child_pointer(child.childID, &child, child_pointer_vector, free_childID_queue, number_of_children);
        }

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

            apprentice.apprenticeID = yli::hierarchy::request_childID(apprentice_pointer_vector, free_apprenticeID_queue);
            // set pointer to the apprentice in master's apprentice pointer vector so that master knows about apprentices' whereabouts!
            yli::hierarchy::set_child_pointer(apprentice.apprenticeID, &apprentice, apprentice_pointer_vector, free_apprenticeID_queue, number_of_apprentices);
        }

    template <typename T1>
        void unbind_child_from_parent(
                const std::size_t childID,
                std::vector<T1>& child_pointer_vector,
                std::queue<std::size_t>& free_childID_queue,
                std::size_t& number_of_children) noexcept
        {
            // requirements:
            // `childID` must not be `std::numeric_limits<std::size_t>::max()`.
            //     (`std::numeric_limits<std::size_t>::max()` as `childID` value means that `childID` is uninitialized).

            if (childID == std::numeric_limits<std::size_t>::max())
            {
                return;
            }

            // Set pointer to this child to `nullptr` in the old parent.
            yli::hierarchy::set_child_pointer(childID, static_cast<T1>(nullptr), child_pointer_vector, free_childID_queue, number_of_children);
        }

    template<typename T1>
        T1 get_first_child(const std::vector<T1>& child_pointer_vector, const std::size_t number_of_children) noexcept
        {
            if (number_of_children == 0)
            {
                return nullptr;
            }

            for (T1 child : child_pointer_vector)
            {
                if (child != nullptr)
                {
                    return child;
                }
            }

            return nullptr;
        }
}

#endif
