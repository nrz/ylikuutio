// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2022 Antti Nuortimo.
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
#include <optional> // std::optional
#include <string> // std::string

namespace yli::ontology
{
    class Console;

    std::optional<yli::data::AnyValue> Entity::create_variable_with_parent_name_type_value(
            yli::ontology::Entity& parent,
            const std::string& variable_name,
            const std::string& variable_type,
            const std::string& variable_value)
    {
        yli::ontology::VariableStruct variable_struct(parent.get_universe());
        variable_struct.local_name    = variable_name;
        parent.create_variable(variable_struct, yli::data::AnyValue(variable_type, variable_value));
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Entity::print_children(
            yli::ontology::Console& console,
            const yli::ontology::Entity& entity)
    {
        // OK, let's print the children of this `Entity`.
        yli::map::print_keys_to_console(entity.registry.get_entity_map(), &console);

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Entity::print_variables0(
            const yli::ontology::Universe& universe,
            yli::ontology::Console& console)
    {
        // Print global variable names.

        yli::map::print_keys_of_specific_type_to_console<yli::ontology::Entity*, yli::ontology::Variable*>(universe.registry.get_entity_map(), console);

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Entity::print_variables1(
            const yli::ontology::Universe&,
            yli::ontology::Console& console,
            const yli::ontology::Entity& entity)
    {
        // Print the variable names of the `Entity`.

        yli::map::print_keys_of_specific_type_to_console<yli::ontology::Entity*, yli::ontology::Variable*>(entity.registry.get_entity_map(), console);

        return std::nullopt;
    }
}
