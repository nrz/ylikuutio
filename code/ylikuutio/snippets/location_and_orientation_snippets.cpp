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

#include "location_and_orientation_snippets.hpp"
#include "code/ylikuutio/ontology/entity.hpp"
#include "code/ylikuutio/ontology/movable_variable_activation.hpp"
#include "code/ylikuutio/ontology/movable_variable_read.hpp"
#include "code/ylikuutio/ontology/variable_struct.hpp"
#include "code/ylikuutio/data/spherical_coordinates_struct.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>         // NAN, std::isnan, std::pow
#include <iostream>      // std::cout, std::cin, std::cerr
#include <memory>        // std::make_shared, std::shared_ptr

namespace yli::snippets
{
    void set_location_and_orientation(
            yli::ontology::Entity* const entity,
            const float rho,
            const float theta,
            const float phi,
            const float x,
            const float y,
            const float z)
    {
        // Variables related to location and orientation.
        yli::data::SphericalCoordinatesStruct spherical_coordinates_struct;
        spherical_coordinates_struct.rho = rho;
        spherical_coordinates_struct.theta = theta;
        spherical_coordinates_struct.phi = phi;
        yli::ontology::VariableStruct spherical_coordinates_variable_struct(std::make_shared<yli::data::AnyValue>(&spherical_coordinates_struct));
        spherical_coordinates_variable_struct.local_name = "spherical_coordinates";
        spherical_coordinates_variable_struct.activate_callback = &yli::ontology::activate_spherical_coordinates;
        spherical_coordinates_variable_struct.should_ylikuutio_call_activate_callback_now = true;
        std::cout << "Executing `entity->create_variable(spherical_coordinates_variable_struct);` ...\n";
        entity->create_variable(spherical_coordinates_variable_struct);

        yli::ontology::VariableStruct rho_variable_struct(std::make_shared<yli::data::AnyValue>(rho));
        rho_variable_struct.local_name = "rho";
        rho_variable_struct.activate_callback = &yli::ontology::activate_rho;
        rho_variable_struct.read_callback = &yli::ontology::read_rho;
        rho_variable_struct.should_ylikuutio_call_activate_callback_now = true;
        std::cout << "Executing `entity->create_variable(rho_variable_struct);` ...\n";
        entity->create_variable(rho_variable_struct);

        yli::ontology::VariableStruct theta_variable_struct(std::make_shared<yli::data::AnyValue>(theta));
        theta_variable_struct.local_name = "theta";
        theta_variable_struct.activate_callback = &yli::ontology::activate_theta;
        theta_variable_struct.read_callback = &yli::ontology::read_theta;
        theta_variable_struct.should_ylikuutio_call_activate_callback_now = true;
        std::cout << "Executing `entity->create_variable(theta_variable_struct);` ...\n";
        entity->create_variable(theta_variable_struct);

        yli::ontology::VariableStruct phi_variable_struct(std::make_shared<yli::data::AnyValue>(phi));
        phi_variable_struct.local_name = "phi";
        phi_variable_struct.activate_callback = &yli::ontology::activate_phi;
        phi_variable_struct.read_callback = &yli::ontology::read_phi;
        phi_variable_struct.should_ylikuutio_call_activate_callback_now = true;
        std::cout << "Executing `entity->create_variable(phi_variable_struct);` ...\n";
        entity->create_variable(phi_variable_struct);

        yli::ontology::VariableStruct cartesian_coordinates_variable_struct(std::make_shared<yli::data::AnyValue>(std::make_shared<glm::vec3>(x, y, z)));
        cartesian_coordinates_variable_struct.local_name = "cartesian_coordinates";
        cartesian_coordinates_variable_struct.activate_callback = &yli::ontology::activate_cartesian_coordinates;
        cartesian_coordinates_variable_struct.read_callback = &yli::ontology::read_cartesian_coordinates;
        cartesian_coordinates_variable_struct.should_ylikuutio_call_activate_callback_now = true;
        std::cout << "Executing `entity->create_variable(cartesian_coordinates_variable_struct);` ...\n";
        entity->create_variable(cartesian_coordinates_variable_struct);

        yli::ontology::VariableStruct x_variable_struct(std::make_shared<yli::data::AnyValue>(x));
        x_variable_struct.local_name = "x";
        x_variable_struct.activate_callback = &yli::ontology::activate_x;
        x_variable_struct.read_callback = &yli::ontology::read_x;
        x_variable_struct.should_ylikuutio_call_activate_callback_now = true;
        std::cout << "Executing `entity->create_variable(x_variable_struct);` ...\n";
        entity->create_variable(x_variable_struct);

        yli::ontology::VariableStruct y_variable_struct(std::make_shared<yli::data::AnyValue>(y));
        y_variable_struct.local_name = "y";
        y_variable_struct.activate_callback = &yli::ontology::activate_y;
        y_variable_struct.read_callback = &yli::ontology::read_y;
        y_variable_struct.should_ylikuutio_call_activate_callback_now = true;
        std::cout << "Executing `entity->create_variable(y_variable_struct);` ...\n";
        entity->create_variable(y_variable_struct);

        yli::ontology::VariableStruct z_variable_struct(std::make_shared<yli::data::AnyValue>(z));
        z_variable_struct.local_name = "z";
        z_variable_struct.activate_callback = &yli::ontology::activate_z;
        z_variable_struct.read_callback = &yli::ontology::read_z;
        z_variable_struct.should_ylikuutio_call_activate_callback_now = true;
        std::cout << "Executing `entity->create_variable(z_variable_struct);` ...\n";
        entity->create_variable(z_variable_struct);

        const float yaw = 0.31f;
        yli::ontology::VariableStruct horizontal_angle_variable_struct(std::make_shared<yli::data::AnyValue>(yaw));
        horizontal_angle_variable_struct.local_name = "yaw";
        horizontal_angle_variable_struct.activate_callback = &yli::ontology::activate_horizontal_angle;
        horizontal_angle_variable_struct.read_callback = &yli::ontology::read_horizontal_angle;
        horizontal_angle_variable_struct.should_ylikuutio_call_activate_callback_now = true;
        std::cout << "Executing `entity->create_variable(horizontal_angle_variable_struct);` ...\n";
        entity->create_variable(horizontal_angle_variable_struct);

        const float pitch = -0.38f;
        yli::ontology::VariableStruct vertical_angle_variable_struct(std::make_shared<yli::data::AnyValue>(pitch));
        vertical_angle_variable_struct.local_name = "pitch";
        vertical_angle_variable_struct.activate_callback = &yli::ontology::activate_vertical_angle;
        vertical_angle_variable_struct.read_callback = &yli::ontology::read_vertical_angle;
        vertical_angle_variable_struct.should_ylikuutio_call_activate_callback_now = true;
        std::cout << "Executing `entity->create_variable(vertical_angle_variable_struct);` ...\n";
        entity->create_variable(vertical_angle_variable_struct);

        const float right = NAN; // the value does not matter, `right` is read with a read callback.
        yli::ontology::VariableStruct right_variable_struct(std::make_shared<yli::data::AnyValue>(right));
        right_variable_struct.local_name = "right";
        right_variable_struct.read_callback = &yli::ontology::read_right;
        right_variable_struct.should_ylikuutio_call_activate_callback_now = false;
        std::cout << "Executing `entity->create_variable(right_variable_struct);` ...\n";
        entity->create_variable(right_variable_struct);

        const float up = NAN; // the value does not matter, `up` is read with a read callback.
        yli::ontology::VariableStruct up_variable_struct(std::make_shared<yli::data::AnyValue>(up));
        up_variable_struct.local_name = "up";
        up_variable_struct.read_callback = &yli::ontology::read_up;
        up_variable_struct.should_ylikuutio_call_activate_callback_now = false;
        std::cout << "Executing `entity->create_variable(up_variable_struct);` ...\n";
        entity->create_variable(up_variable_struct);

        std::cout << "Setting up location and orientation ... ready.\n";
    }
}
