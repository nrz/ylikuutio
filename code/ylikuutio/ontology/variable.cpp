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

#include "variable.hpp"
#include "entity.hpp"
#include "universe.hpp"
#include "console.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <optional> // std::optional
#include <string>   // std::string

namespace yli::ontology
{
    class Entity;
    class Scene;

    void Variable::bind_to_parent()
    {
        // Requirements:
        // `this->parent` must not be `nullptr`.

        yli::ontology::Entity* const entity = this->parent;

        if (entity == nullptr)
        {
            std::cerr << "ERROR: `Variable::bind_to_parent`: `entity` is `nullptr`!\n";
            return;
        }

        // Get `childID` from `Entity` and set pointer to this `Variable`.
        entity->bind_variable(this);
    }

    Variable::~Variable()
    {
        // destructor.
        std::cout << "This `Variable` will be destroyed.\n";

        if (this->parent == nullptr)
        {
            return;
        }

        this->parent->unbind_variable(this->childID, this->local_name);
    }

    yli::ontology::Entity* Variable::get_parent() const
    {
        return this->parent;
    }

    yli::ontology::Scene* Variable::get_scene() const
    {
        yli::ontology::Entity* const parent = this->get_parent();

        if (parent != nullptr)
        {
            return parent->get_scene();
        }

        return nullptr;
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

    std::optional<yli::data::AnyValue> Variable::get()
    {
        if (this->parent == nullptr)
        {
            std::cerr << "ERROR: `Variable::get`: the parent of a `Variable` must not be `nullptr`!";
            return std::nullopt;
        }

        if (this->read_callback == nullptr)
        {
            return this->variable_value;
        }

        return this->read_callback(this->parent);
    }

    void Variable::set(const yli::data::AnyValue& new_value)
    {
        if (this->parent == nullptr)
        {
            return;
        }

        this->variable_value = new_value;

        if (this->activate_callback != nullptr)
        {
            this->activate_callback(this->parent, this);
        }
    }

    void Variable::set(const std::string& new_value)
    {
        if (this->parent == nullptr)
        {
            return;
        }

        this->variable_value.set_new_value(new_value);

        if (this->activate_callback != nullptr)
        {
            this->activate_callback(this->parent, this);
        }
    }

    // Public callbacks.

    std::optional<yli::data::AnyValue> Variable::set_variable_const_std_string(
            yli::ontology::Variable* const variable,
            const std::string& new_value)
    {
        // Usage:
        // to set variable: set2 <variable-name> <variable-value>

        if (variable == nullptr)
        {
            return std::nullopt;
        }

        // Set a new value and call activate callback if there is such.
        variable->set(new_value);
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Variable::set_variable_variable(
            yli::ontology::Variable* const dest_variable,
            yli::ontology::Universe* const /* context */, // A context is needed so that correct `Variable is bound to the function call.
            yli::ontology::Variable* const src_variable)
    {
        // Usage:
        // to set variable: set <dest-variable-name> <src-variable-name>

        if (dest_variable == nullptr || src_variable == nullptr)
        {
            return std::nullopt;
        }

        // Set a new value and call activate callback if there is such.

        std::optional<yli::data::AnyValue> any_value = src_variable->get();

        if (any_value)
        {
            dest_variable->set(*any_value);
        }

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Variable::print_value1(
            yli::ontology::Console* const console,
            yli::ontology::Universe* const /* context */, // A context is needed so that correct `Variable` is bound to the function call.
            yli::ontology::Variable* const variable)
    {
        // Usage:
        // to get variable value: get1 <variable-name>

        if (console == nullptr || variable == nullptr)
        {
            return std::nullopt;
        }

        std::optional<yli::data::AnyValue> variable_value = variable->get();

        if (variable_value)
        {
            console->print_text((*variable_value).get_string());
        }

        return std::nullopt;
    }

    // Public callbacks end here.

    void Variable::activate()
    {
        if (this->activate_callback != nullptr)
        {
            this->activate_callback(this->parent, this);
        }
    }
}
