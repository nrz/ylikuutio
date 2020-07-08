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
#include <iostream> // std::cout, std::cin, std::cerr
#include <string>  // std::string

namespace yli::ontology
{
    void ParentModule::bind_child(yli::ontology::Entity* const child)
    {
        if (this->entity == nullptr || child == nullptr)
        {
            return;
        }

        yli::ontology::bind_child_to_parent<yli::ontology::Entity*>(
                child,
                this->child_pointer_vector,
                this->free_childID_queue,
                this->number_of_children,
                this->entity->entity_map);
    }

    void ParentModule::unbind_child(std::size_t childID)
    {
        if (this->entity == nullptr)
        {
            std::cerr << "ERROR: `ParentModule::unbind_child`: `this->entity` is `nullptr`!\n";
            return;
        }

        if (childID >= this->child_pointer_vector.size())
        {
            std::cerr << "ERROR: `ParentModule::unbind_child`: the value of `childID` is too big!\n";
            return;
        }

        yli::ontology::Entity* const child = this->child_pointer_vector.at(childID);

        if (child == nullptr)
        {
            std::cerr << "ERROR: `ParentModule::unbind_child`: `child` is `nullptr`!\n";
            return;
        }

        const std::string name = child->get_local_name();

        yli::ontology::unbind_child_from_parent<yli::ontology::Entity*>(
                childID,
                name,
                this->child_pointer_vector,
                this->free_childID_queue,
                this->number_of_children,
                this->entity->entity_map);
    }

    ParentModule::~ParentModule()
    {
        // destructor.

        yli::hierarchy::delete_children<yli::ontology::Entity*>(this->child_pointer_vector, this->number_of_children);
    }

    yli::ontology::Entity* ParentModule::get_entity() const
    {
        return this->entity;
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
