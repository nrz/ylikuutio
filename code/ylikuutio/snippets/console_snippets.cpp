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

#include "console_snippets.hpp"
#include "code/ylikuutio/ontology/entity.hpp"
#include "code/ylikuutio/ontology/variable.hpp"
#include "code/ylikuutio/ontology/variable_struct.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <stdint.h> // uint32_t etc.

namespace yli::snippets
{
    void set_console(
            yli::ontology::Entity* const entity,
            const uint32_t console_top_y,
            const uint32_t console_bottom_y,
            const uint32_t console_left_x,
            const uint32_t console_right_x)
    {
        // Variables related to console.
        yli::ontology::VariableStruct console_top_y_variable_struct(entity->get_universe(), *entity);
        console_top_y_variable_struct.local_name = "console_top_y";
        console_top_y_variable_struct.activate_callback = &yli::ontology::Variable::activate_console_top_y;
        console_top_y_variable_struct.should_call_activate_callback_now = true;
        entity->create_variable(console_top_y_variable_struct, yli::data::AnyValue(console_top_y));

        yli::ontology::VariableStruct console_bottom_y_variable_struct(entity->get_universe(), *entity);
        console_bottom_y_variable_struct.local_name = "console_bottom_y";
        console_bottom_y_variable_struct.activate_callback = &yli::ontology::Variable::activate_console_bottom_y;
        console_bottom_y_variable_struct.should_call_activate_callback_now = true;
        entity->create_variable(console_bottom_y_variable_struct, yli::data::AnyValue(console_bottom_y));

        yli::ontology::VariableStruct console_left_x_variable_struct(entity->get_universe(), *entity);
        console_left_x_variable_struct.local_name = "console_left_x";
        console_left_x_variable_struct.activate_callback = &yli::ontology::Variable::activate_console_left_x;
        console_left_x_variable_struct.should_call_activate_callback_now = true;
        entity->create_variable(console_left_x_variable_struct, yli::data::AnyValue(console_left_x));

        yli::ontology::VariableStruct console_right_x_variable_struct(entity->get_universe(), *entity);
        console_right_x_variable_struct.local_name = "console_right_x";
        console_right_x_variable_struct.activate_callback = &yli::ontology::Variable::activate_console_right_x;
        console_right_x_variable_struct.should_call_activate_callback_now = true;
        entity->create_variable(console_right_x_variable_struct, yli::data::AnyValue(console_right_x));
    }
}
