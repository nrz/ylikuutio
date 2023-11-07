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

#include "child_module.hpp"
#include "generic_parent_module.hpp"
#include "entity.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <iostream> // std::cerr
#include <limits>  // std::numeric_limits

namespace yli::ontology
{
    class Scene;

    void ChildModule::bind_to_parent_module() noexcept
    {
        // requirements:
        // `this->parent` must not be `nullptr`.

        if (this->parent_module == nullptr)
        {
            return;
        }

        // get `childID` from the `ParentModule` and set pointer to this child.
        this->parent_module->bind_child(this->entity);
    }

    ChildModule::~ChildModule() noexcept
    {
        // requirements:
        // `this->parent_module` must not be `nullptr`.

        if (this->get_childID() == std::numeric_limits<std::size_t>::max()) [[unlikely]]
        {
            // OK, this `ChildModule` has been released already.
            this->parent_module = nullptr; // Clean up by setting parent to `nullptr`.
            return;
        }
        else if (this->parent_module == nullptr) [[unlikely]]
        {
            std::cerr << "ERROR: `ChildModule::~ChildModule`: `ChildModule` has no parent but `childID` is not properly released!\n";
            this->release();
            return;
        }
        else [[likely]]
        {
            // OK, this `ChildModule` has not been released yet.

            // Set pointer to this `Entity` to `nullptr`.
            this->parent_module->unbind_child(this->entity.get_childID());
            this->release();
        }
    }

    yli::ontology::Entity* ChildModule::get_parent() const noexcept
    {
        if (this->parent_module == nullptr)
        {
            return nullptr;
        }

        return this->parent_module->get_entity();
    }

    yli::ontology::Entity* ChildModule::get_child() const noexcept
    {
        return &this->entity;
    }

    void ChildModule::release() noexcept
    {
        this->parent_module = nullptr;
        this->entity.set_childID(std::numeric_limits<std::size_t>::max());
    }

    yli::ontology::Scene* ChildModule::get_scene() const noexcept
    {
        if (this->parent_module != nullptr)
        {
            return this->parent_module->get_scene();
        }

        return nullptr;
    }

    std::size_t ChildModule::get_childID() const noexcept
    {
        return this->entity.get_childID();
    }

    void ChildModule::unbind_child() const noexcept
    {
        if (this->parent_module == nullptr)
        {
            return;
        }

        this->parent_module->unbind_child(this->get_childID());
    }

    void ChildModule::set_parent_module_and_bind_to_new_parent(
            yli::ontology::GenericParentModule* const new_parent_module) noexcept
    {
        if (new_parent_module == nullptr)
        {
            return;
        }

        this->parent_module = new_parent_module;
        this->parent_module->bind_child(this->entity);
    }

    void ChildModule::unbind_and_bind_to_new_parent(
            yli::ontology::GenericParentModule* const new_parent_module) noexcept
    {
        if (new_parent_module != this->parent_module)
        {
            this->unbind_child();
            this->release();
            this->set_parent_module_and_bind_to_new_parent(new_parent_module);
        }
    }
}
