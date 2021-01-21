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

#ifndef __YLIKUUTIO_ONTOLOGY_VARIABLE_STRUCT_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_VARIABLE_STRUCT_HPP_INCLUDED

#include "entity_struct.hpp"
#include "activate_callback.hpp"
#include "read_callback.hpp"

// Include standard headers
#include <memory>   // std::make_shared, std::shared_ptr

namespace yli::data
{
    class AnyValue;
}

namespace yli::ontology
{
    class Entity;

    struct VariableStruct: public yli::ontology::EntityStruct
    {
        VariableStruct()
        {
            // constructor.
            this->is_variable = true;
        }

        VariableStruct(std::shared_ptr<yli::data::AnyValue> initial_value)
            : initial_value { initial_value }
        {
            // constructor.
            this->is_variable = true;
        }

        VariableStruct(const yli::ontology::VariableStruct& variable_struct)
            : EntityStruct(variable_struct),
            parent { variable_struct.parent },
            initial_value { variable_struct.initial_value },
            activate_callback { variable_struct.activate_callback },
            read_callback { variable_struct.read_callback },
            should_ylikuutio_call_activate_callback_now { variable_struct.should_ylikuutio_call_activate_callback_now }
        {
            // copy constructor.
            this->global_name = variable_struct.global_name;
            this->local_name = variable_struct.local_name;
            this->is_variable = true;
        }

        yli::ontology::Entity* parent                      { nullptr };
        std::shared_ptr<yli::data::AnyValue> initial_value { nullptr };
        ActivateCallback activate_callback                 { nullptr };
        ReadCallback read_callback                         { nullptr };
        bool should_ylikuutio_call_activate_callback_now   { true };
    };
}

#endif
