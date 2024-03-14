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

#include "variable.hpp"
#include "entity.hpp"
#include "console.hpp"
#include "variable_struct.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <cstddef>   // std::size_t
#include <optional>  // std::optional
#include <stdexcept> // std::runtime_error
#include <string>    // std::string

namespace yli::core
{
    class Application;
}

namespace yli::ontology
{
    class Entity;
    class Universe;
    class Scene;

    Variable::Variable(
            yli::core::Application& application,
            yli::ontology::Universe& universe,
            const yli::ontology::VariableStruct& variable_struct,
            const yli::data::AnyValue& any_value)
        : Entity(application, universe, variable_struct),
        child_of_entity(&variable_struct.parent.parent_of_variables, *this),
        variable_value    { any_value },
        activate_callback { variable_struct.activate_callback },
        read_callback     { variable_struct.read_callback }
    {
        // `yli::ontology::Entity` member variables begin here.
        this->type_string = "yli::ontology::Variable*";
        this->can_be_erased = true;
    }

    yli::ontology::Entity* Variable::get_parent() const
    {
        return this->child_of_entity.get_parent();
    }

    yli::ontology::Scene* Variable::get_scene() const
    {
        const yli::ontology::Entity* const entity_parent = this->get_parent();

        if (entity_parent == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Variable::get_scene`: `entity_parent` is `nullptr`!");
        }

        return entity_parent->get_scene();
    }

    std::size_t Variable::get_number_of_children() const
    {
        return 0; // `Variable` has no children.
    }

    std::size_t Variable::get_number_of_descendants() const
    {
        return 0; // `Variable` has no children.
    }

    std::string Variable::help() const
    {
        // this function returns the help string for this variable.
        std::string help_string = this->local_name + " TODO: create helptext for " + this->local_name;
        return help_string;
    }

    std::optional<yli::data::AnyValue> Variable::get() const
    {
        yli::ontology::Entity* const entity_parent = this->get_parent();

        if (entity_parent == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Variable::get`: `entity_parent` is `nullptr`!");
        }

        if (this->read_callback == nullptr)
        {
            return this->variable_value;
        }

        return this->read_callback(*entity_parent);
    }

    void Variable::set(const yli::data::AnyValue& new_value)
    {
        yli::ontology::Entity* const entity_parent = this->get_parent();

        if (entity_parent == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Variable::set`: `entity_parent` is `nullptr`!");
        }

        this->variable_value = new_value;

        if (this->activate_callback != nullptr)
        {
            this->activate_callback(*entity_parent, *this);
        }
    }

    void Variable::set(const std::string& new_value)
    {
        yli::ontology::Entity* const entity_parent = this->get_parent();

        if (entity_parent == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Variable::set`: `entity_parent` is `nullptr`!");
        }

        this->variable_value.set_new_value(new_value);

        if (this->activate_callback != nullptr)
        {
            this->activate_callback(*entity_parent, *this);
        }
    }

    // Public callbacks.

    std::optional<yli::data::AnyValue> Variable::set_variable_const_std_string(
            yli::ontology::Variable& variable,
            const std::string& new_value)
    {
        // Usage:
        // to set variable: set2 <variable-name> <variable-value>

        // Set a new value and call activate callback if there is such.
        variable.set(new_value);
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Variable::set_variable_variable(
            yli::ontology::Variable& dest_variable,
            const yli::ontology::Universe&,              // A context is needed so that correct `Variable` is bound to the function call.
            const yli::ontology::Variable& src_variable)
    {
        // Usage:
        // to set variable: set <dest-variable-name> <src-variable-name>

        // Set a new value and call activate callback if there is such.

        std::optional<yli::data::AnyValue> any_value = src_variable.get();

        if (any_value)
        {
            dest_variable.set(*any_value);
        }

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Variable::print_value1(
            yli::ontology::Console& console,
            const yli::ontology::Universe&,          // A context is needed so that correct `Variable` is bound to the function call.
            const yli::ontology::Variable& variable)
    {
        // Usage:
        // to get variable value: get1 <variable-name>

        std::optional<yli::data::AnyValue> variable_value = variable.get();

        if (variable_value)
        {
            console.print_text((*variable_value).get_string());
        }

        return std::nullopt;
    }

    // Public callbacks end here.

    void Variable::activate()
    {
        if (this->activate_callback != nullptr)
        {
            this->activate_callback(*this->get_parent(), *this);
        }
    }
}
