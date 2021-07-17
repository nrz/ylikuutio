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

#include "entity.hpp"
#include "variable.hpp"
#include "universe.hpp"
#include "family_templates.hpp"
#include "entity_factory.hpp"
#include "entity_variable_activation.hpp"
#include "entity_variable_read.hpp"
#include "entity_struct.hpp"
#include "variable_struct.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef>       // std::size_t
#include <limits>        // std::numeric_limits
#include <memory>        // std::make_shared, std::shared_ptr
#include <regex>         // std::regex, std::regex_match
#include <string>        // std::string
#include <unordered_map> // std::unordered_map

namespace yli::ontology
{
    class Scene;

    void Entity::bind_variable(yli::ontology::Variable* const variable)
    {
        if (variable != nullptr)
        {
            // get `childID` from `Entity` and set pointer to `variable`.
            yli::hierarchy::bind_child_to_parent<yli::ontology::Variable*>(
                    variable,
                    this->variable_pointer_vector,
                    this->free_variableID_queue,
                    this->number_of_variables);

            // `variable` with a local name needs to be added to `entity_map` as well.
            this->add_entity(variable->get_local_name(), variable);
        }
    }

    void Entity::unbind_variable(const std::size_t childID, const std::string& local_name)
    {
        yli::ontology::unbind_child_from_parent(
                childID,
                local_name,
                this->variable_pointer_vector,
                this->free_variableID_queue,
                this->number_of_variables,
                this->registry);
    }

    void Entity::bind_to_universe()
    {
        // Requirements:
        // `this->universe` must not be `nullptr`.
        yli::ontology::Universe* const universe = this->universe;

        if (universe == nullptr)
        {
            // When `Application` is created, `universe` is still `nullptr`.
            return;
        }

        // Get `entityID` from the `Universe` and set pointer to this `Entity`.
        universe->bind_entity(this);
    }

    void Entity::bind_to_new_parent(yli::ontology::Entity* new_entity_parent)
    {
        // Do nothing.
        // `yli::ontology` classes which support binding must `override`
        // this `yli::ontology::Entity` base class implementation.
    }

    Entity::Entity(yli::ontology::Universe* const universe, const yli::ontology::EntityStruct& entity_struct)
        : registry(),
        parent_of_any_struct_entities(this, &this->registry, "any_struct_entities"),
        universe { universe },
        is_application { entity_struct.is_application },
        is_variable { entity_struct.is_variable }
    {
        // constructor.

        // Get `entityID` from `Universe` and set pointer to this `Entity`.
        if (!this->is_application)
        {
            this->bind_to_universe();
        }

        if (!this->is_application && !this->is_variable && this->universe != nullptr && this->universe != this)
        {
            this->should_be_rendered = !this->universe->get_is_headless();

            yli::ontology::VariableStruct should_be_rendered_variable_struct(std::make_shared<yli::data::AnyValue>(this->should_be_rendered));
            should_be_rendered_variable_struct.local_name = "should_be_rendered";
            should_be_rendered_variable_struct.activate_callback = &yli::ontology::activate_should_be_rendered;
            should_be_rendered_variable_struct.read_callback = &yli::ontology::read_should_be_rendered;
            should_be_rendered_variable_struct.should_call_activate_callback_now = true;
            this->create_variable(should_be_rendered_variable_struct);
        }
    }

    Entity::~Entity()
    {
        // destructor.

        if (this->universe == nullptr)
        {
            // When leaving the `main` before binding `Application` to `Universe`,
            // `this->universe` is still `nullptr`.
            return;
        }

        this->universe->unbind_entity(this->entityID);

        if (!this->global_name.empty() && this->universe != nullptr)
        {
            // OK, this `Entity` had a global name, so it's global name shall be erased.
            this->universe->erase_entity(this->global_name);
        }

        // Local names must be erased in the destructors
        // of classes that inherit `yli::ontology::Entity`!
        // They can not be erased here in `Entity` destructor,
        // because `Entity` class does not keep track of the
        // parent. `Entity` only provides virtual function
        // `Entity::get_parent`, but that can not be called
        // from here.
    }

    void Entity::activate()
    {
    }

    std::size_t Entity::get_childID() const
    {
        return this->childID;
    }

    std::string Entity::get_type() const
    {
        return this->type_string;
    }

    bool Entity::get_can_be_erased() const
    {
        return this->can_be_erased;
    }

    yli::ontology::Universe* Entity::get_universe() const
    {
        return this->universe;
    }

    yli::ontology::Scene* Entity::get_scene() const
    {
        // Different classes are bound to `Scene` in different ways,
        // so they need to `override` this to provide the functionality.
        // Note: not all classes have any relation to a specific `Scene`.
        // E.g. `Universe` may have many `Scene`s, but is descendant of none.
        return nullptr;
    }

    yli::ontology::EntityFactory* Entity::get_entity_factory() const
    {
        if (this->universe == nullptr)
        {
            return nullptr;
        }

        return this->universe->get_entity_factory();
    }

    bool Entity::has_child(const std::string& name) const
    {
        return this->registry.is_entity(name);
    }

    yli::ontology::Entity* Entity::get_entity(const std::string& name) const
    {
        // Requirements:
        // `name` must not begin with a dot.
        // `name` must not end with a dot.
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

        if (first.empty())
        {
            // Name must not be empty.
            return nullptr;
        }

        if (!this->registry.is_entity(first))
        {
            return nullptr;
        }

        yli::ontology::Entity* entity = this->registry.get_entity(first);

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

    void Entity::add_entity(const std::string& name, yli::ontology::Entity* const entity)
    {
        this->registry.add_entity(entity, name);
    }

    void Entity::erase_entity(const std::string& name)
    {
        this->registry.erase_entity(name);
    }

    void Entity::create_variable(const yli::ontology::VariableStruct& variable_struct)
    {
        if (this->universe == nullptr)
        {
            return;
        }

        yli::ontology::EntityFactory* const entity_factory = this->universe->get_entity_factory();

        if (entity_factory == nullptr)
        {
            return;
        }

        yli::ontology::VariableStruct new_variable_struct(variable_struct);
        new_variable_struct.parent = this;
        entity_factory->create_variable(new_variable_struct);
    }

    bool Entity::has_variable(const std::string& variable_name) const
    {
        return this->get(variable_name) != nullptr;
    }

    yli::ontology::Variable* Entity::get(const std::string& variable_name) const
    {
        return dynamic_cast<yli::ontology::Variable*>(this->registry.get_entity(variable_name));
    }

    bool Entity::set(const std::string& variable_name, std::shared_ptr<yli::data::AnyValue> variable_new_any_value)
    {
        yli::ontology::Variable* const variable = this->get(variable_name);

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

    std::string Entity::help(const std::string& variable_name) const
    {
        yli::ontology::Variable* const variable = this->get(variable_name);

        if (variable == nullptr)
        {
            return this->help();
        }

        return variable->help();
    }

    void Entity::prerender() const
    {
        // Requirements:
        // `this->prerender_callback` must not be `nullptr`.
        // `this->universe` must not be `nullptr`.

        if (this->prerender_callback != nullptr &&
                this->universe != nullptr)
        {
            this->prerender_callback(this->universe);
        }
    }

    void Entity::postrender() const
    {
        // Requirements:
        // `this->postrender_callback` must not be `nullptr`.
        // `this->universe` must not be `nullptr`.

        if (this->postrender_callback != nullptr &&
                this->universe != nullptr)
        {
            this->postrender_callback(this->universe);
        }
    }

    std::string Entity::get_global_name() const
    {
        return this->global_name;
    }

    std::size_t Entity::get_number_of_all_children() const
    {
        return this->number_of_variables +
            this->get_number_of_non_variable_children();
    }

    std::size_t Entity::get_number_of_all_descendants() const
    {
        return yli::ontology::get_number_of_descendants(this->variable_pointer_vector) +
            yli::ontology::get_number_of_descendants(this->parent_of_any_struct_entities.child_pointer_vector) +
            this->get_number_of_descendants();
    }

    std::size_t Entity::get_number_of_variables() const
    {
        return this->number_of_variables;
    }

    std::size_t Entity::get_number_of_non_variable_children() const
    {
        return this->parent_of_any_struct_entities.get_number_of_children() +
            this->get_number_of_children();
    }

    std::string Entity::get_local_name() const
    {
        return this->local_name;
    }

    void Entity::set_global_name(const std::string& global_name)
    {
        // Requirements:
        // `this->universe` must not be `nullptr`.
        // `global_name` must not be already in use.

        if (global_name.empty())
        {
            return;
        }

        if (!std::regex_match(global_name, std::regex("[a-zA-Z][a-zA-Z0-9_-]*")))
        {
            return;
        }

        if (this->universe == nullptr)
        {
            return;
        }

        if (this->universe->has_child(global_name))
        {
            // The global name is already in use.
            return;
        }

        // Erase old global name.
        this->universe->erase_entity(this->global_name);

        // Set new global name.
        this->global_name = global_name;
        this->universe->add_entity(global_name, this);

        if (this->universe == this->get_parent())
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

        yli::ontology::Entity* const parent = this->get_parent();

        if (parent == nullptr)
        {
            return;
        }

        if (parent->has_child(local_name))
        {
            // The name is in use.
            return;
        }

        // Erase old local name.
        parent->erase_entity(this->local_name);

        // Set new local name.
        parent->add_entity(local_name, this);
        this->local_name = local_name;

        if (parent == this->universe)
        {
            // Special case: this `Entity` is a child of the `Universe`!
            // Therefore, the local name is also the global name,
            // and vice versa. This means that the requested
            // global name must not be in use.
            this->global_name = local_name;
        }
    }
}
