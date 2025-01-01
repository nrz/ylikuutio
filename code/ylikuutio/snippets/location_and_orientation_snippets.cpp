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

#include "location_and_orientation_snippets.hpp"
#include "code/ylikuutio/ontology/entity.hpp"
#include "code/ylikuutio/ontology/movable_variable_activation.hpp"
#include "code/ylikuutio/ontology/movable_variable_read.hpp"
#include "code/ylikuutio/ontology/variable_struct.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>         // NAN
#include <iostream>      // std::cout

namespace yli::snippets
{
    void set_location_and_orientation(
            yli::ontology::Entity* const entity,
            const float x,
            const float y,
            const float z)
    {
        // Variables related to location and orientation.

        yli::ontology::VariableStruct cartesian_coordinates_variable_struct(entity->get_universe(), entity);
        cartesian_coordinates_variable_struct.local_name = "cartesian";
        cartesian_coordinates_variable_struct.activate_callback = &yli::ontology::activate_cartesian_coordinates;
        cartesian_coordinates_variable_struct.read_callback = &yli::ontology::read_cartesian_coordinates;
        cartesian_coordinates_variable_struct.should_call_activate_callback_now = true;
        std::cout << "Executing `entity->create_variable(cartesian_coordinates_variable_struct);` ...\n";
        entity->create_variable(cartesian_coordinates_variable_struct, yli::data::AnyValue(glm::vec3(x, y, z)));

        yli::ontology::VariableStruct x_variable_struct(entity->get_universe(), entity);
        x_variable_struct.local_name = "x";
        x_variable_struct.activate_callback = &yli::ontology::activate_x;
        x_variable_struct.read_callback = &yli::ontology::read_x;
        x_variable_struct.should_call_activate_callback_now = true;
        std::cout << "Executing `entity->create_variable(x_variable_struct);` ...\n";
        entity->create_variable(x_variable_struct, yli::data::AnyValue(x));

        yli::ontology::VariableStruct y_variable_struct(entity->get_universe(), entity);
        y_variable_struct.local_name = "y";
        y_variable_struct.activate_callback = &yli::ontology::activate_y;
        y_variable_struct.read_callback = &yli::ontology::read_y;
        y_variable_struct.should_call_activate_callback_now = true;
        std::cout << "Executing `entity->create_variable(y_variable_struct);` ...\n";
        entity->create_variable(y_variable_struct, yli::data::AnyValue(y));

        yli::ontology::VariableStruct z_variable_struct(entity->get_universe(), entity);
        z_variable_struct.local_name = "z";
        z_variable_struct.activate_callback = &yli::ontology::activate_z;
        z_variable_struct.read_callback = &yli::ontology::read_z;
        z_variable_struct.should_call_activate_callback_now = true;
        std::cout << "Executing `entity->create_variable(z_variable_struct);` ...\n";
        entity->create_variable(z_variable_struct, yli::data::AnyValue(z));

        const float roll = 0.0f;
        yli::ontology::VariableStruct roll_variable_struct(entity->get_universe(), entity);
        roll_variable_struct.local_name = "roll";
        roll_variable_struct.activate_callback = &yli::ontology::activate_roll;
        roll_variable_struct.read_callback = &yli::ontology::read_roll;
        roll_variable_struct.should_call_activate_callback_now = true;
        std::cout << "Executing `entity->create_variable(roll_variable_struct);` ...\n";
        entity->create_variable(roll_variable_struct, yli::data::AnyValue(roll));

        const float yaw = -0.41f;
        yli::ontology::VariableStruct yaw_variable_struct(entity->get_universe(), entity);
        yaw_variable_struct.local_name = "yaw";
        yaw_variable_struct.activate_callback = &yli::ontology::activate_yaw;
        yaw_variable_struct.read_callback = &yli::ontology::read_yaw;
        yaw_variable_struct.should_call_activate_callback_now = true;
        std::cout << "Executing `entity->create_variable(yaw_variable_struct);` ...\n";
        entity->create_variable(yaw_variable_struct, yli::data::AnyValue(yaw));

        const float pitch = -0.19f;
        yli::ontology::VariableStruct pitch_variable_struct(entity->get_universe(), entity);
        pitch_variable_struct.local_name = "pitch";
        pitch_variable_struct.activate_callback = &yli::ontology::activate_pitch;
        pitch_variable_struct.read_callback = &yli::ontology::read_pitch;
        pitch_variable_struct.should_call_activate_callback_now = true;
        std::cout << "Executing `entity->create_variable(pitch_variable_struct);` ...\n";
        entity->create_variable(pitch_variable_struct, yli::data::AnyValue(pitch));

        const float azimuth = 0.0f;
        yli::ontology::VariableStruct azimuth_variable_struct(entity->get_universe(), entity);
        azimuth_variable_struct.local_name = "azimuth";
        azimuth_variable_struct.activate_callback = &yli::ontology::activate_azimuth;
        azimuth_variable_struct.read_callback = &yli::ontology::read_azimuth;
        azimuth_variable_struct.should_call_activate_callback_now = false;
        std::cout << "Executing `entity->create_variable(azimuth_variable_struct);` ...\n";
        entity->create_variable(azimuth_variable_struct, yli::data::AnyValue(azimuth));

        // the value does not matter, `right` is read with a read callback.
        yli::ontology::VariableStruct right_variable_struct(entity->get_universe(), entity);
        right_variable_struct.local_name = "right";
        right_variable_struct.read_callback = &yli::ontology::read_right;
        right_variable_struct.should_call_activate_callback_now = false;
        std::cout << "Executing `entity->create_variable(right_variable_struct);` ...\n";
        entity->create_variable(right_variable_struct, yli::data::AnyValue(glm::vec3(NAN, NAN, NAN)));

        // the value does not matter, `up` is read with a read callback.
        yli::ontology::VariableStruct up_variable_struct(entity->get_universe(), entity);
        up_variable_struct.local_name = "up";
        up_variable_struct.read_callback = &yli::ontology::read_up;
        up_variable_struct.should_call_activate_callback_now = false;
        std::cout << "Executing `entity->create_variable(up_variable_struct);` ...\n";
        entity->create_variable(up_variable_struct, yli::data::AnyValue(glm::vec3(NAN, NAN, NAN)));

        std::cout << "Setting up location and orientation ... ready.\n";
    }
}
