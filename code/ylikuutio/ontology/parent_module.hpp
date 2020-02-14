// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
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

#ifndef __PARENT_MODULE_HPP_INCLUDED
#define __PARENT_MODULE_HPP_INCLUDED

// Include standard headers
#include <cstddef> // std::size_t
#include <queue>   // std::queue
#include <vector>  // std::vector

namespace yli
{
    namespace ontology
    {
        class Entity;

        class ParentModule
        {
            public:
                void bind_child(yli::ontology::Entity* const child);
                void unbind_child(std::size_t childID);

                ParentModule(yli::ontology::Entity* const entity)
                    : number_of_children(0),
                    entity(entity)
                {
                    // constructor.
                }

                ParentModule(const ParentModule&) = delete;            // Delete copy constructor.
                ParentModule &operator=(const ParentModule&) = delete; // Delete copy assignment.

                yli::ontology::Entity* get_entity() const;
                std::size_t get_number_of_children() const;
                std::size_t get_number_of_descendants() const;

                // destructor.
                ~ParentModule();

                std::vector<yli::ontology::Entity*> child_pointer_vector;
            private:
                std::queue<std::size_t> free_childID_queue;
                std::size_t number_of_children;

                yli::ontology::Entity* entity; // The `Entity` that owns this `ParentModule`.
        };
    }
}

#endif
