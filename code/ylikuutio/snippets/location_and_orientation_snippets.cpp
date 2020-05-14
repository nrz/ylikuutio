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
#include "code/ylikuutio/config/setting_master.hpp"
#include "code/ylikuutio/config/setting_struct.hpp"
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

namespace yli::config
{
    class SettingMaster;
}

namespace yli::snippets
{
    void set_location_and_orientation(
            yli::config::SettingMaster* const setting_master,
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
        yli::config::SettingStruct spherical_coordinates_setting_struct(std::make_shared<yli::data::AnyValue>(&spherical_coordinates_struct));
        spherical_coordinates_setting_struct.name = "spherical_coordinates";
        spherical_coordinates_setting_struct.activate_callback = &yli::config::SettingMaster::activate_spherical_coordinates;
        spherical_coordinates_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        std::cout << "Executing `setting_master->create_setting(spherical_coordinates_setting_struct);` ...\n";
        setting_master->create_setting(spherical_coordinates_setting_struct);

        yli::config::SettingStruct rho_setting_struct(std::make_shared<yli::data::AnyValue>(rho));
        rho_setting_struct.name = "rho";
        rho_setting_struct.activate_callback = &yli::config::SettingMaster::activate_rho;
        rho_setting_struct.read_callback = &yli::config::SettingMaster::read_rho;
        rho_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        std::cout << "Executing `setting_master->create_setting(rho_setting_struct);` ...\n";
        setting_master->create_setting(rho_setting_struct);

        yli::config::SettingStruct theta_setting_struct(std::make_shared<yli::data::AnyValue>(theta));
        theta_setting_struct.name = "theta";
        theta_setting_struct.activate_callback = &yli::config::SettingMaster::activate_theta;
        theta_setting_struct.read_callback = &yli::config::SettingMaster::read_theta;
        theta_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        std::cout << "Executing `setting_master->create_setting(theta_setting_struct);` ...\n";
        setting_master->create_setting(theta_setting_struct);

        yli::config::SettingStruct phi_setting_struct(std::make_shared<yli::data::AnyValue>(phi));
        phi_setting_struct.name = "phi";
        phi_setting_struct.activate_callback = &yli::config::SettingMaster::activate_phi;
        phi_setting_struct.read_callback = &yli::config::SettingMaster::read_phi;
        phi_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        std::cout << "Executing `setting_master->create_setting(phi_setting_struct);` ...\n";
        setting_master->create_setting(phi_setting_struct);

        yli::config::SettingStruct cartesian_coordinates_setting_struct(std::make_shared<yli::data::AnyValue>(std::make_shared<glm::vec3>(x, y, z)));
        cartesian_coordinates_setting_struct.name = "cartesian_coordinates";
        cartesian_coordinates_setting_struct.activate_callback = &yli::config::SettingMaster::activate_cartesian_coordinates;
        cartesian_coordinates_setting_struct.read_callback = &yli::config::SettingMaster::read_cartesian_coordinates;
        cartesian_coordinates_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        std::cout << "Executing `setting_master->create_setting(cartesian_coordinates_setting_struct);` ...\n";
        setting_master->create_setting(cartesian_coordinates_setting_struct);

        yli::config::SettingStruct x_setting_struct(std::make_shared<yli::data::AnyValue>(x));
        x_setting_struct.name = "x";
        x_setting_struct.activate_callback = &yli::config::SettingMaster::activate_x;
        x_setting_struct.read_callback = &yli::config::SettingMaster::read_x;
        x_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        std::cout << "Executing `setting_master->create_setting(x_setting_struct);` ...\n";
        setting_master->create_setting(x_setting_struct);

        yli::config::SettingStruct y_setting_struct(std::make_shared<yli::data::AnyValue>(y));
        y_setting_struct.name = "y";
        y_setting_struct.activate_callback = &yli::config::SettingMaster::activate_y;
        y_setting_struct.read_callback = &yli::config::SettingMaster::read_y;
        y_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        std::cout << "Executing `setting_master->create_setting(y_setting_struct);` ...\n";
        setting_master->create_setting(y_setting_struct);

        yli::config::SettingStruct z_setting_struct(std::make_shared<yli::data::AnyValue>(z));
        z_setting_struct.name = "z";
        z_setting_struct.activate_callback = &yli::config::SettingMaster::activate_z;
        z_setting_struct.read_callback = &yli::config::SettingMaster::read_z;
        z_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        std::cout << "Executing `setting_master->create_setting(z_setting_struct);` ...\n";
        setting_master->create_setting(z_setting_struct);

        const double horizontal_angle = 0.31f;
        yli::config::SettingStruct horizontal_angle_setting_struct(std::make_shared<yli::data::AnyValue>(horizontal_angle));
        horizontal_angle_setting_struct.name = "horizontal_angle";
        horizontal_angle_setting_struct.activate_callback = &yli::config::SettingMaster::activate_horizontal_angle;
        horizontal_angle_setting_struct.read_callback = &yli::config::SettingMaster::read_horizontal_angle;
        horizontal_angle_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        std::cout << "Executing `setting_master->create_setting(horizontal_angle_setting_struct);` ...\n";
        setting_master->create_setting(horizontal_angle_setting_struct);

        const double vertical_angle = -0.38f;
        yli::config::SettingStruct vertical_angle_setting_struct(std::make_shared<yli::data::AnyValue>(vertical_angle));
        vertical_angle_setting_struct.name = "vertical_angle";
        vertical_angle_setting_struct.activate_callback = &yli::config::SettingMaster::activate_vertical_angle;
        vertical_angle_setting_struct.read_callback = &yli::config::SettingMaster::read_vertical_angle;
        vertical_angle_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        std::cout << "Executing `setting_master->create_setting(vertical_angle_setting_struct);` ...\n";
        setting_master->create_setting(vertical_angle_setting_struct);

        const float right = NAN; // the value does not matter, `right` is read with a read callback.
        yli::config::SettingStruct right_setting_struct(std::make_shared<yli::data::AnyValue>(right));
        right_setting_struct.name = "right";
        right_setting_struct.read_callback = &yli::config::SettingMaster::read_right;
        right_setting_struct.should_ylikuutio_call_activate_callback_now = false;
        std::cout << "Executing `setting_master->create_setting(right_setting_struct);` ...\n";
        setting_master->create_setting(right_setting_struct);

        const float up = NAN; // the value does not matter, `up` is read with a read callback.
        yli::config::SettingStruct up_setting_struct(std::make_shared<yli::data::AnyValue>(up));
        up_setting_struct.name = "up";
        up_setting_struct.read_callback = &yli::config::SettingMaster::read_up;
        up_setting_struct.should_ylikuutio_call_activate_callback_now = false;
        std::cout << "Executing `setting_master->create_setting(up_setting_struct);` ...\n";
        setting_master->create_setting(up_setting_struct);

        std::cout << "Setting up location and orientation ... ready.\n";
    }
}
