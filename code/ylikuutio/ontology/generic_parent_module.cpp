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

#include "registry.hpp"
#include "generic_parent_module.hpp"
#include "entity.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <string>   // std::string

namespace yli::memory
{
    class GenericMemoryAllocator;
}

namespace yli::ontology
{
    class Scene;

    bool GenericParentModule::bind_child(yli::ontology::Entity* const child) noexcept
    {
        if (this->entity == nullptr || child == nullptr)
        {
            return false; // Binding failed.
        }

        yli::ontology::bind_child_to_parent<yli::ontology::Entity*>(
                child,
                this->child_pointer_vector,
                this->free_childID_queue,
                this->number_of_children,
                this->entity->registry);

        return true; // Binding successful.
    }

    bool GenericParentModule::unbind_child(std::size_t childID) noexcept
    {
        if (this->entity == nullptr)
        {
            std::cerr << "ERROR: `GenericParentModule::unbind_child`: `this->entity` is `nullptr`!\n";
            return false; // Unbinding failed.
        }

        if (childID >= this->child_pointer_vector.size())
        {
            std::cerr << "ERROR: `GenericParentModule::unbind_child`: the value of `childID` is too big!\n";
            return false; // Unbinding failed.
        }

        yli::ontology::Entity* const child = this->child_pointer_vector.at(childID);

        if (child == nullptr)
        {
            std::cerr << "ERROR: `GenericParentModule::unbind_child`: `child` is `nullptr`!\n";
            return false; // Unbinding failed.
        }

        const std::string name = child->get_local_name();

        yli::ontology::unbind_child_from_parent<yli::ontology::Entity*>(
                childID,
                name,
                this->child_pointer_vector,
                this->free_childID_queue,
                this->number_of_children,
                this->entity->registry);

        return true; // Unbinding successful.
    }

    GenericParentModule::GenericParentModule(
            yli::ontology::Entity* const entity,
            yli::ontology::Registry* const registry,
            yli::memory::GenericMemoryAllocator& memory_allocator,
            const std::string& name) noexcept
        : entity { entity },
        memory_allocator { memory_allocator }
    {
        // constructor.

        registry->add_indexable(this, name);
    }

    GenericParentModule::~GenericParentModule() noexcept
    {
        // destructor.

        yli::hierarchy::delete_children<yli::ontology::Entity*>(this->child_pointer_vector, this->number_of_children);
    }

    yli::ontology::GenericParentModule* GenericParentModule::get() const noexcept
    {
        // This function exists simply to be able to pass `GenericParentModule` as non-const parameter.
        yli::ontology::GenericParentModule* generic_parent_module = const_cast<yli::ontology::GenericParentModule*>(this);
        return generic_parent_module;
    }

    yli::ontology::Entity* GenericParentModule::get_entity() const noexcept
    {
        return this->entity;
    }

    std::size_t GenericParentModule::get_number_of_children() const noexcept
    {
        return this->number_of_children;
    }

    std::size_t GenericParentModule::get_number_of_descendants() const noexcept
    {
        return yli::ontology::get_number_of_descendants(this->child_pointer_vector);
    }

    yli::ontology::Scene* GenericParentModule::get_scene() const noexcept
    {
        return this->entity->get_scene();
    }

    yli::ontology::Entity* GenericParentModule::get(const std::size_t index) const noexcept
    {
        if (index < this->child_pointer_vector.size())
        {
            return this->child_pointer_vector.at(index);
        }

        return nullptr;
    }
}
