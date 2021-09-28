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

#include "child_module.hpp"
#include "parent_module.hpp"
#include "entity.hpp"

namespace yli::ontology
{
    void ChildModule::bind_to_parent_module()
    {
        // requirements:
        // `this->parent` must not be `nullptr`.
        // `this->entity` must not be `nullptr`.

        if (this->parent_module == nullptr)
        {
            return;
        }

        if (this->entity == nullptr)
        {
            return;
        }

        // get `childID` from the `ParentModule` and set pointer to this child.
        this->parent_module->bind_child(this->entity);
    }

    ChildModule::~ChildModule()
    {
        // destructor.

        // requirements:
        // `this->parent` must not be `nullptr`.

        if (this->parent_module == nullptr)
        {
            return;
        }

        if (this->entity == nullptr)
        {
            return;
        }

        // Set pointer to this `Entity` to `nullptr`.
        this->parent_module->unbind_child(this->entity->childID);
    }

    yli::ontology::Entity* ChildModule::get_parent() const
    {
        if (this->parent_module == nullptr)
        {
            return nullptr;
        }

        return this->parent_module->get_entity();
    }

    yli::ontology::Entity* ChildModule::get_child() const
    {
        return this->entity;
    }

    void ChildModule::unbind_child() const
    {
        if (this->parent_module == nullptr)
        {
            return;
        }

        if (this->entity == nullptr)
        {
            return;
        }

        this->parent_module->unbind_child(entity->get_childID());
    }

    void ChildModule::set_parent_module_and_bind_to_new_parent(yli::ontology::ParentModule* const new_parent_module)
    {
        if (new_parent_module == nullptr)
        {
            return;
        }

        if (this->entity == nullptr)
        {
            return;
        }

        this->parent_module = new_parent_module;
        this->parent_module->bind_child(this->entity);
    }
}
