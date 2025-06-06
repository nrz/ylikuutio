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

#include "entity.hpp"
#include "variable.hpp"
#include "universe.hpp"
#include "family_templates.hpp"
#include "generic_entity_factory.hpp"
#include "entity_variable_activation.hpp"
#include "entity_variable_read.hpp"
#include "entity_struct.hpp"
#include "variable_struct.hpp"
#include "code/ylikuutio/core/application.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/memory/constructible_module.hpp"

// Include standard headers
#include <cstddef>       // std::size_t
#include <limits>        // std::numeric_limits
#include <regex>         // std::regex, std::regex_match
#include <string>        // std::string
#include <utility>       // std::move

namespace yli::ontology
{
    class Scene;

    bool Entity::operator==(const Entity& rhs) const noexcept
    {
        return this == &rhs;
    }

    yli::core::Application& Entity::get_application() const
    {
        return this->application;
    }

    void Entity::bind_to_universe() noexcept
    {
        // Get `entityID` from the `Universe` and set pointer to this `Entity`.
        this->universe.bind_entity(this);
    }

    Entity::Entity(
            yli::core::Application& application,
            Universe& universe,
            const EntityStruct& entity_struct)
        : application { application },
        registry(),
        parent_of_variables(
                *this,
                this->registry,
                ""), // Do not index `parent_of_variables`, index only the variables.
        parent_of_callback_engines(
                *this,
                this->registry,
                "callback_engines"),
        universe { universe },
        is_universe { entity_struct.is_universe }
    {
        // Get `entityID` from `Universe` and set pointer to this `Entity`.
        this->bind_to_universe();

        if (!this->is_universe && !entity_struct.is_variable)
        {
            this->should_render = !this->universe.get_is_headless();

            VariableStruct should_render_variable_struct(this->universe, this);
            should_render_variable_struct.local_name = "should_render";
            should_render_variable_struct.activate_callback = &activate_should_render;
            should_render_variable_struct.read_callback = &read_should_render;
            should_render_variable_struct.should_call_activate_callback_now = true;
            this->create_variable(should_render_variable_struct, yli::data::AnyValue(this->should_render));
        }
    }

    Entity::~Entity()
    {
        this->terminate(); // Mark this `Entity` as dead.

        if (!this->is_universe)
        {
            this->universe.unbind_entity(this->entityID);
        }

        if (!this->global_name.empty())
        {
            // OK, this `Entity` had a global name, so it's global name shall be erased.
            this->universe.erase_entity(this->global_name);
        }

        // Local names must be erased in the destructors
        // of classes that inherit `Entity`!
        // They can not be erased here in `Entity` destructor,
        // because `Entity` class does not keep track of the
        // parent. `Entity` only provides virtual function
        // `Entity::get_parent`, but that can not be called
        // from here.
    }

    void Entity::activate()
    {
        // There is no default activation behavior.
        //
        // Each derivative class may override `Entity::activate`
        // to implement its own specific activation behavior.
    }

    void Entity::terminate()
    {
        this->constructible_module.alive = false;
    }

    yli::memory::ConstructibleModule Entity::get_constructible_module() const
    {
        return this->constructible_module;
    }

    void Entity::set_childID(const std::size_t childID)
    {
        this->childID = childID;
    }

    std::size_t Entity::get_childID() const
    {
        return this->childID;
    }

    void Entity::release()
    {
        this->childID = std::numeric_limits<std::size_t>::max();
    }

    std::string Entity::get_type() const
    {
        return this->type_string;
    }

    bool Entity::get_can_be_erased() const
    {
        return this->can_be_erased;
    }

    Universe& Entity::get_universe() const
    {
        return this->universe;
    }

    bool Entity::has_child(const std::string& name) const
    {
        return this->registry.is_entity(name);
    }

    Entity* Entity::get_entity(const std::string& name) const
    {
        // Requirements:
        // `name` must not be empty.
        // `name` must not begin with a dot.
        // `name` must not end with a dot.

        if (name.empty() || name.front() == '.' || name.back() == '.')
        {
            return nullptr;
        }

        std::size_t first_dot_pos = name.find_first_of('.');

        if (first_dot_pos == std::string::npos)
        {
            // There are no dots in the name.

            if (!this->registry.is_entity(name))
            {
                return nullptr;
            }

            return this->registry.get_entity(name);
        }

        // OK, assumedly we have a multi-part name.

        const std::string first = std::string(name, 0, first_dot_pos);
        const std::string rest = std::string(name, ++first_dot_pos);

        if (!this->registry.is_entity(first))
        {
            return nullptr;
        }

        const Entity* const entity = this->registry.get_entity(first);

        if (entity == nullptr)
        {
            return nullptr;
        }

        return entity->get_entity(rest);
    }

    std::string Entity::get_entity_names() const
    {
        return this->registry.get_entity_names();
    }

    std::string Entity::complete(const std::string& input) const
    {
        return this->registry.complete(input);
    }

    void Entity::add_entity(const std::string& name, Entity& entity)
    {
        this->registry.add_entity(entity, name);
    }

    void Entity::erase_entity(const std::string& name)
    {
        this->registry.erase_entity(name);
    }

    void Entity::create_variable(const VariableStruct& variable_struct, yli::data::AnyValue&& any_value)
    {
        GenericEntityFactory& entity_factory = this->application.get_generic_entity_factory();

        const VariableStruct new_variable_struct(this, variable_struct);
        entity_factory.create_variable(new_variable_struct, std::move(any_value));
    }

    bool Entity::has_variable(const std::string& variable_name) const
    {
        return this->get_variable(variable_name) != nullptr;
    }

    Variable* Entity::get_variable(const std::string& variable_name) const
    {
        return dynamic_cast<Variable*>(this->registry.get_entity(variable_name));
    }

    bool Entity::set_variable(const std::string& variable_name, const yli::data::AnyValue& variable_new_any_value)
    {
        Variable* const variable = this->get_variable(variable_name);

        if (variable == nullptr)
        {
            return false;
        }

        // OK, this is a valid variable name.
        // Set the variable value and activate it by
        // calling the corresponding activate callback.

        variable->set(variable_new_any_value);
        return true;
    }

    std::string Entity::help() const
    {
        std::string help_string = "TODO: create general helptext";
        return help_string;
    }

    std::string Entity::help_for_variable(const std::string& variable_name) const
    {
        const Variable* const variable = this->get_variable(variable_name);

        if (variable == nullptr)
        {
            return this->help();
        }

        return variable->help();
    }

    std::string Entity::get_global_name() const
    {
        return this->global_name;
    }

    std::size_t Entity::get_number_of_all_children() const
    {
        return this->parent_of_variables.get_number_of_children() +
            this->get_number_of_non_variable_children();
    }

    std::size_t Entity::get_number_of_all_descendants() const
    {
        return yli::ontology::get_number_of_descendants(this->parent_of_variables.child_pointer_vector) +
            this->get_number_of_descendants();
    }

    std::size_t Entity::get_number_of_variables() const
    {
        return this->parent_of_variables.get_number_of_children();
    }

    std::size_t Entity::get_number_of_non_variable_children() const
    {
        return this->get_number_of_children();
    }

    std::string Entity::get_local_name() const
    {
        return this->local_name;
    }

    void Entity::set_global_name(const std::string& global_name)
    {
        // Requirements:
        // `global_name` must not be already in use.

        if (global_name.empty())
        {
            return;
        }

        if (!std::regex_match(global_name, std::regex("[a-zA-Z][a-zA-Z0-9_-]*")))
        {
            return;
        }

        if (this->universe.has_child(global_name))
        {
            // The global name is already in use.
            return;
        }

        // Erase old global name.
        this->universe.erase_entity(this->global_name);

        // Set new global name.
        this->global_name = global_name;
        this->universe.add_entity(global_name, *this);

        if (&this->universe == this->get_parent())
        {
            // `Universe` is the parent of this `Entity`.
            // Therefore, local name and global name
            // are the same for this `Entity`.
            this->local_name = global_name;
        }
    }

    void Entity::set_local_name(const std::string& local_name)
    {
        if (local_name.empty())
        {
            return;
        }

        if (!std::regex_match(local_name, std::regex("[a-zA-Z][a-zA-Z0-9_-]*")))
        {
            return;
        }

        Entity* const entity_parent = this->get_parent();

        if (entity_parent == nullptr)
        {
            // `Universe` has no parent and can not be given a local name.
            return;
        }

        if (entity_parent->has_child(local_name))
        {
            // The name is in use.
            return;
        }

        // Erase old local name.
        entity_parent->erase_entity(this->local_name);

        // Set new local name.
        entity_parent->add_entity(local_name, *this);
        this->local_name = local_name;

        if (entity_parent == &this->universe)
        {
            // Special case: this `Entity` is a child of the `Universe`!
            // Therefore, the local name is also the global name,
            // and vice versa. This means that the requested
            // global name must not be in use.
            this->global_name = local_name;
        }
    }
}
