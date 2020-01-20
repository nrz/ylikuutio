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

#include "parent_module.hpp"
#include "entity.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef> // std::size_t

namespace yli
{
    namespace ontology
    {
        void ParentModule::bind_child(yli::ontology::Entity* const child)
        {
            yli::hierarchy::bind_child_to_parent<yli::ontology::Entity*>(
                    child,
                    this->child_pointer_vector,
                    this->free_childID_queue,
                    this->number_of_children);
        }

        void ParentModule::unbind_child(std::size_t childID)
        {
            yli::hierarchy::unbind_child_from_parent<yli::ontology::Entity*>(
                    childID,
                    this->child_pointer_vector,
                    this->free_childID_queue,
                    this->number_of_children);
        }

        ParentModule::~ParentModule()
        {
            // destructor.

            yli::hierarchy::delete_children<yli::ontology::Entity*>(this->child_pointer_vector, this->number_of_children);
        }

        std::size_t ParentModule::get_number_of_children() const
        {
            return this->number_of_children;
        }

        std::size_t ParentModule::get_number_of_descendants() const
        {
            return yli::ontology::get_number_of_descendants(this->child_pointer_vector);
        }
    }
}
