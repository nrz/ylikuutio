// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2021 Antti Nuortimo.
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

#ifndef __YLIKUUTIO_ONTOLOGY_MASTER_MODULE_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_MASTER_MODULE_HPP_INCLUDED

#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef>    // std::size_t
#include <queue>      // std::queue
#include <vector>     // std::vector

// `yli::ontology::MasterModule` is a module that implements
// the master part of a master-apprentice relationship.
//
// In Ylikuutio terminology, master-apprentice relationship
// exists so that the master provides some functionality to
// the apprentice without being a direct ancestor in the
// ontological graph.
//
// Each master may have several apprentices,
// unless specifically restricted by the master.
//
// Each apprentice may have several masters of
// different types.
//
// If the master of a master-apprentice relation dies,
// the apprentice will survice.
//
// If the apprentice of a master-apprentice relation dies,
// the master will survice.

namespace yli::ontology
{
    template<class M, class A>
        class MasterModule
        {
            public:
                void bind_apprentice(A const apprentice)
                {
                    yli::hierarchy::bind_apprentice_to_master<A>(
                            apprentice,
                            this->apprentice_pointer_vector,
                            this->free_apprenticeID_queue,
                            this->number_of_apprentices);
                }

                void unbind_apprentice(std::size_t apprenticeID)
                {
                    yli::hierarchy::unbind_child_from_parent<A>(
                            apprenticeID,
                            this->apprentice_pointer_vector,
                            this->free_apprenticeID_queue,
                            this->number_of_apprentices);
                }

                MasterModule(M const master)
                    : number_of_apprentices { 0 },
                    master { master }
                {
                    // constructor.
                }

                ~MasterModule()
                {
                    // destructor.

                    for (std::size_t apprentice_i = 0; apprentice_i < this->apprentice_pointer_vector.size(); apprentice_i++)
                    {
                        A const apprentice = this->apprentice_pointer_vector[apprentice_i];

                        if (apprentice != nullptr)
                        {
                            // Call the unbind callback.
                            this->unbind_apprentice(apprentice->apprenticeID);
                        }
                    }
                }

                std::size_t get_number_of_apprentices() const
                {
                    return this->number_of_apprentices;
                }

                std::vector<A> apprentice_pointer_vector;

            private:
                std::queue<std::size_t> free_apprenticeID_queue;
                std::size_t number_of_apprentices;

                M master; // The `Entity` that owns this `MasterModule`.
        };
}

#endif
