#include "ajokki_location_and_orientation.hpp"
#include "code/ylikuutio/config/setting.hpp"
#include "code/ylikuutio/config/setting_master.hpp"
#include "code/ylikuutio/config/setting_struct.hpp"
#include "code/ylikuutio/common/spherical_coordinates_struct.hpp"
#include "code/ylikuutio/common/any_value.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>         // NAN, std::isnan, std::pow
#include <iostream>      // std::cout, std::cin, std::cerr
#include <memory>        // std::make_shared, std::shared_ptr

namespace yli
{
    namespace config
    {
        class SettingMaster;
    }
}

namespace ajokki
{
    void set_location_and_orientation(yli::config::SettingMaster* const setting_master)
    {
        // Variables related to location and orientation.
        const float float_rho = -5682.32f;
        const float float_theta = -1641.20f;
        const float float_phi = 2376.45f;
        SphericalCoordinatesStruct spherical_coordinates_struct;
        spherical_coordinates_struct.rho = float_rho;
        spherical_coordinates_struct.theta = float_theta;
        spherical_coordinates_struct.phi = float_phi;
        SettingStruct spherical_coordinates_setting_struct(std::make_shared<yli::datatypes::AnyValue>(&spherical_coordinates_struct));
        spherical_coordinates_setting_struct.name = "spherical_coordinates";
        spherical_coordinates_setting_struct.setting_master = setting_master;
        spherical_coordinates_setting_struct.activate_callback = &yli::config::SettingMaster::activate_spherical_coordinates;
        spherical_coordinates_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        std::cout << "Executing `new yli::config::Setting(spherical_coordinates_setting_struct);` ...\n";
        new yli::config::Setting(spherical_coordinates_setting_struct);

        SettingStruct rho_setting_struct(std::make_shared<yli::datatypes::AnyValue>(float_rho));
        rho_setting_struct.name = "rho";
        rho_setting_struct.setting_master = setting_master;
        rho_setting_struct.activate_callback = &yli::config::SettingMaster::activate_rho;
        rho_setting_struct.read_callback = &yli::config::SettingMaster::read_rho;
        rho_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        std::cout << "Executing `new yli::config::Setting(rho_setting_struct);` ...\n";
        new yli::config::Setting(rho_setting_struct);

        SettingStruct theta_setting_struct(std::make_shared<yli::datatypes::AnyValue>(float_theta));
        theta_setting_struct.name = "theta";
        theta_setting_struct.setting_master = setting_master;
        theta_setting_struct.activate_callback = &yli::config::SettingMaster::activate_theta;
        theta_setting_struct.read_callback = &yli::config::SettingMaster::read_theta;
        theta_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        std::cout << "Executing `new yli::config::Setting(theta_setting_struct);` ...\n";
        new yli::config::Setting(theta_setting_struct);

        SettingStruct phi_setting_struct(std::make_shared<yli::datatypes::AnyValue>(float_phi));
        phi_setting_struct.name = "phi";
        phi_setting_struct.setting_master = setting_master;
        phi_setting_struct.activate_callback = &yli::config::SettingMaster::activate_phi;
        phi_setting_struct.read_callback = &yli::config::SettingMaster::read_phi;
        phi_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        std::cout << "Executing `new yli::config::Setting(phi_setting_struct);` ...\n";
        new yli::config::Setting(phi_setting_struct);

        const float float_x = 100.0f;
        const float float_y = 100.0f;
        const float float_z = 100.0f;

        SettingStruct cartesian_coordinates_setting_struct(std::make_shared<yli::datatypes::AnyValue>(new glm::vec3(float_x, float_y, float_z)));
        cartesian_coordinates_setting_struct.name = "cartesian_coordinates";
        cartesian_coordinates_setting_struct.setting_master = setting_master;
        cartesian_coordinates_setting_struct.activate_callback = &yli::config::SettingMaster::activate_cartesian_coordinates;
        cartesian_coordinates_setting_struct.read_callback = &yli::config::SettingMaster::read_cartesian_coordinates;
        cartesian_coordinates_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        std::cout << "Executing `new yli::config::Setting(cartesian_coordinates_setting_struct);` ...\n";
        new yli::config::Setting(cartesian_coordinates_setting_struct);

        SettingStruct x_setting_struct(std::make_shared<yli::datatypes::AnyValue>(float_x));
        x_setting_struct.name = "x";
        x_setting_struct.setting_master = setting_master;
        x_setting_struct.activate_callback = &yli::config::SettingMaster::activate_x;
        x_setting_struct.read_callback = &yli::config::SettingMaster::read_x;
        x_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        std::cout << "Executing `new yli::config::Setting(x_setting_struct);` ...\n";
        new yli::config::Setting(x_setting_struct);

        SettingStruct y_setting_struct(std::make_shared<yli::datatypes::AnyValue>(float_y));
        y_setting_struct.name = "y";
        y_setting_struct.setting_master = setting_master;
        y_setting_struct.activate_callback = &yli::config::SettingMaster::activate_y;
        y_setting_struct.read_callback = &yli::config::SettingMaster::read_y;
        y_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        std::cout << "Executing `new yli::config::Setting(y_setting_struct);` ...\n";
        new yli::config::Setting(y_setting_struct);

        SettingStruct z_setting_struct(std::make_shared<yli::datatypes::AnyValue>(float_z));
        z_setting_struct.name = "z";
        z_setting_struct.setting_master = setting_master;
        z_setting_struct.activate_callback = &yli::config::SettingMaster::activate_z;
        z_setting_struct.read_callback = &yli::config::SettingMaster::read_z;
        z_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        std::cout << "Executing `new yli::config::Setting(z_setting_struct);` ...\n";
        new yli::config::Setting(z_setting_struct);

        const double horizontal_angle = 42.42f;
        SettingStruct horizontal_angle_setting_struct(std::make_shared<yli::datatypes::AnyValue>(horizontal_angle));
        horizontal_angle_setting_struct.name = "horizontal_angle";
        horizontal_angle_setting_struct.setting_master = setting_master;
        horizontal_angle_setting_struct.activate_callback = &yli::config::SettingMaster::activate_horizontal_angle;
        horizontal_angle_setting_struct.read_callback = &yli::config::SettingMaster::read_horizontal_angle;
        horizontal_angle_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        std::cout << "Executing `new yli::config::Setting(horizontal_angle_setting_struct);` ...\n";
        new yli::config::Setting(horizontal_angle_setting_struct);

        const double vertical_angle = 7.44f;
        SettingStruct vertical_angle_setting_struct(std::make_shared<yli::datatypes::AnyValue>(vertical_angle));
        vertical_angle_setting_struct.name = "vertical_angle";
        vertical_angle_setting_struct.setting_master = setting_master;
        vertical_angle_setting_struct.activate_callback = &yli::config::SettingMaster::activate_vertical_angle;
        vertical_angle_setting_struct.read_callback = &yli::config::SettingMaster::read_vertical_angle;
        vertical_angle_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        std::cout << "Executing `new yli::config::Setting(vertical_angle_setting_struct);` ...\n";
        new yli::config::Setting(vertical_angle_setting_struct);

        const float right = NAN; // the value does not matter, `right` is read with a read callback.
        SettingStruct right_setting_struct(std::make_shared<yli::datatypes::AnyValue>(right));
        right_setting_struct.name = "right";
        right_setting_struct.setting_master = setting_master;
        right_setting_struct.read_callback = &yli::config::SettingMaster::read_right;
        right_setting_struct.should_ylikuutio_call_activate_callback_now = false;
        std::cout << "Executing `new yli::config::Setting(right_setting_struct);` ...\n";
        new yli::config::Setting(right_setting_struct);

        const float up = NAN; // the value does not matter, `up` is read with a read callback.
        SettingStruct up_setting_struct(std::make_shared<yli::datatypes::AnyValue>(up));
        up_setting_struct.name = "up";
        up_setting_struct.setting_master = setting_master;
        up_setting_struct.read_callback = &yli::config::SettingMaster::read_up;
        up_setting_struct.should_ylikuutio_call_activate_callback_now = false;
        std::cout << "Executing `new yli::config::Setting(up_setting_struct);` ...\n";
        new yli::config::Setting(up_setting_struct);

        std::cout << "Setting up location and orientation ... ready.\n";
    }
}
