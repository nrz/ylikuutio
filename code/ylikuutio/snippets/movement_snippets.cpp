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

#include "movement_snippets.hpp"
#include "code/ylikuutio/ontology/variable.hpp"
#include "code/ylikuutio/ontology/entity.hpp"
#include "code/ylikuutio/ontology/variable_struct.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <memory> // std::make_shared, std::shared_ptr

namespace yli::snippets
{
    void set_movement(
            yli::ontology::Entity* const entity,
            const float speed,
            const float turbo_factor,
            const float twin_turbo_factor,
            const float mouse_speed)
    {
        // Variables related to voluntary movement.
        std::shared_ptr<yli::data::AnyValue> any_value_speed = std::make_shared<yli::data::AnyValue>(speed);
        yli::ontology::VariableStruct speed_variable_struct(any_value_speed);
        speed_variable_struct.local_name = "speed";
        speed_variable_struct.activate_callback = &yli::ontology::Variable::activate_speed;
        speed_variable_struct.should_call_activate_callback_now = true;
        entity->create_variable(speed_variable_struct);

        std::shared_ptr<yli::data::AnyValue> any_value_turbo_factor = std::make_shared<yli::data::AnyValue>(turbo_factor);
        yli::ontology::VariableStruct turbo_factor_variable_struct(any_value_turbo_factor);
        turbo_factor_variable_struct.local_name = "turbo_factor";
        turbo_factor_variable_struct.activate_callback = &yli::ontology::Variable::activate_turbo_factor;
        turbo_factor_variable_struct.should_call_activate_callback_now = true;
        entity->create_variable(turbo_factor_variable_struct);

        std::shared_ptr<yli::data::AnyValue> any_value_twin_turbo_factor = std::make_shared<yli::data::AnyValue>(twin_turbo_factor);
        yli::ontology::VariableStruct twin_turbo_factor_variable_struct(any_value_twin_turbo_factor);
        twin_turbo_factor_variable_struct.local_name = "twin_turbo_factor";
        twin_turbo_factor_variable_struct.activate_callback = &yli::ontology::Variable::activate_twin_turbo_factor;
        twin_turbo_factor_variable_struct.should_call_activate_callback_now = true;
        entity->create_variable(twin_turbo_factor_variable_struct);

        std::shared_ptr<yli::data::AnyValue> any_value_mouse_speed = std::make_shared<yli::data::AnyValue>(mouse_speed);
        yli::ontology::VariableStruct mouse_speed_variable_struct(any_value_mouse_speed);
        mouse_speed_variable_struct.local_name = "mouse_speed";
        mouse_speed_variable_struct.activate_callback = &yli::ontology::Variable::activate_mouse_speed;
        mouse_speed_variable_struct.should_call_activate_callback_now = true;
        entity->create_variable(mouse_speed_variable_struct);
    }
}
