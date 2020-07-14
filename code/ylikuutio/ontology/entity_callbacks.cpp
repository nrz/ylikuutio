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

#include "entity.hpp"
#include "variable.hpp"
#include "universe.hpp"
#include "variable_struct.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/map/ylikuutio_map.hpp"

// Include standard headers
#include <memory> // std::make_shared, std::shared_ptr

namespace yli::data
{
    class AnyValue;
}

namespace yli::ontology
{
    class Console;

    std::shared_ptr<yli::data::AnyValue> Entity::create_variable_with_parent_name_type_value(
            yli::ontology::Entity* const parent,
            std::shared_ptr<std::string> variable_name,
            std::shared_ptr<std::string> variable_type,
            std::shared_ptr<std::string> variable_value)
    {
        if (parent == nullptr || variable_name == nullptr || variable_type == nullptr || variable_value == nullptr)
        {
            return nullptr;
        }

        yli::ontology::VariableStruct variable_struct;
        variable_struct.local_name    = *variable_name;
        variable_struct.initial_value = std::make_shared<yli::data::AnyValue>(*variable_type, *variable_value);
        parent->create_variable(variable_struct);
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Entity::print_children(
            yli::ontology::Console* const console,
            yli::ontology::Entity* const entity)
    {
        if (console == nullptr || entity == nullptr)
        {
            return nullptr;
        }

        // OK, let's print the children of this `Entity`.
        yli::map::print_keys_to_console(entity->entity_map, console);

        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Entity::print_variables0(
            yli::ontology::Universe* const universe,
            yli::ontology::Console* const console)
    {
        if (universe == nullptr || console == nullptr)
        {
            return nullptr;
        }

        // Print global variable names.

        yli::map::print_keys_of_specific_type_to_console<yli::ontology::Entity*, yli::ontology::Variable*>(universe->entity_map, console);

        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Entity::print_variables1(
            yli::ontology::Universe* const universe,
            yli::ontology::Console* const console,
            yli::ontology::Entity* const entity)
    {
        if (universe == nullptr || console == nullptr || entity == nullptr)
        {
            return nullptr;
        }

        // Print the variable names of the `Entity`.

        yli::map::print_keys_of_specific_type_to_console<yli::ontology::Entity*, yli::ontology::Variable*>(entity->entity_map, console);

        return nullptr;
    }
}
