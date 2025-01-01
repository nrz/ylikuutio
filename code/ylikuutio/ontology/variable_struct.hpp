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

#ifndef YLIKUUTIO_ONTOLOGY_VARIABLE_STRUCT_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_VARIABLE_STRUCT_HPP_INCLUDED

#include "entity_struct.hpp"
#include "activate_callback.hpp"
#include "read_callback.hpp"

// Include standard headers
#include <string>  // std::string
#include <variant> // std::variant

namespace yli::ontology
{
    class Entity;
    class Universe;

    struct VariableStruct final : public EntityStruct
    {
        // The `Universe&` needs to be stored into `VariableStruct`
        // because `Universe` constructor creates its `Variable`
        // instances using `EntityFactory` before `EntityFactory::create_universe`
        // has initialized `universe` member variable of `EntityFactory`.

        VariableStruct(Universe& universe, Entity* const entity_parent)
            : universe { universe },
            entity_parent { entity_parent }
        {
            this->is_variable = true;
        }

        VariableStruct(Universe& universe, const std::string& entity_parent)
            : universe { universe },
            entity_parent { entity_parent }
        {
            this->is_variable = true;
        }

        VariableStruct(const VariableStruct& variable_struct) = default;

        VariableStruct(Entity* const entity_parent, const VariableStruct& variable_struct)
            : EntityStruct(variable_struct),
            universe { variable_struct.universe },
            entity_parent { entity_parent },
            activate_callback { variable_struct.activate_callback },
            read_callback { variable_struct.read_callback },
            should_call_activate_callback_now { variable_struct.should_call_activate_callback_now }
        {
            this->global_name = variable_struct.global_name;
            this->local_name = variable_struct.local_name;
            this->is_variable = true;
        }

        ~VariableStruct() = default;

        Universe& universe;
        std::variant<Entity*, std::string> entity_parent {};
        ActivateCallback activate_callback                 { nullptr };
        ReadCallback read_callback                         { nullptr };
        bool is_variable_of_universe                       { false };
        bool should_call_activate_callback_now             { true };
    };
}

#endif
