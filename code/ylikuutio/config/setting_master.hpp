// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2019 Antti Nuortimo.
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

#ifndef __SETTING_MASTER_HPP_INCLUDED
#define __SETTING_MASTER_HPP_INCLUDED

// Include standard headers
#include <cstddef>       // std::size_t
#include <memory>        // std::make_shared, std::shared_ptr
#include <queue>         // std::queue
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

namespace yli
{
    namespace console
    {
        class Console;
    }

    namespace datatypes
    {
        class AnyValue;
    }

    namespace ontology
    {
        class Entity;
    }

    namespace config
    {
        class Setting;

        class SettingMaster
        {
            public:
                // constructor.
                SettingMaster(yli::ontology::Entity* const entity);

                // destructor.
                ~SettingMaster();

                // does setting `setting` exist?
                bool is_setting(const std::string& setting_name);

                // this function returns general help.
                std::string help();

                // this function returns help string for setting `setting`.
                std::string help(const std::string& setting_name);

                bool set(std::string& setting_name, std::shared_ptr<yli::datatypes::AnyValue> setting_new_any_value);

                yli::config::Setting* get(std::string& setting_name);

                // Public callbacks.

                static std::shared_ptr<yli::datatypes::AnyValue> set_and_print(
                        yli::console::Console* const console,
                        yli::ontology::Entity* const entity,
                        const std::vector<std::string>& command_parameters);

                static std::shared_ptr<yli::datatypes::AnyValue> get_and_print(
                        yli::console::Console* const console,
                        yli::ontology::Entity* const entity,
                        const std::vector<std::string>& command_parameters);

                static std::shared_ptr<yli::datatypes::AnyValue> activate_planet_radius(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);

                static std::shared_ptr<yli::datatypes::AnyValue> activate_background_color(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);

                static std::shared_ptr<yli::datatypes::AnyValue> activate_wireframe(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);

                static std::shared_ptr<yli::datatypes::AnyValue> activate_should_be_rendered(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);
                static std::shared_ptr<yli::datatypes::AnyValue> activate_spherical_coordinates(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);
                static std::shared_ptr<yli::datatypes::AnyValue> activate_rho(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);
                static std::shared_ptr<yli::datatypes::AnyValue> activate_theta(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);
                static std::shared_ptr<yli::datatypes::AnyValue> activate_phi(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);

                static std::shared_ptr<yli::datatypes::AnyValue> activate_cartesian_coordinates(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);
                static std::shared_ptr<yli::datatypes::AnyValue> activate_x(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);
                static std::shared_ptr<yli::datatypes::AnyValue> activate_y(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);
                static std::shared_ptr<yli::datatypes::AnyValue> activate_z(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);

                static std::shared_ptr<yli::datatypes::AnyValue> activate_horizontal_angle(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);

                static std::shared_ptr<yli::datatypes::AnyValue> activate_vertical_angle(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);

                static std::shared_ptr<yli::datatypes::AnyValue> activate_speed(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);

                static std::shared_ptr<yli::datatypes::AnyValue> activate_turbo_factor(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);

                static std::shared_ptr<yli::datatypes::AnyValue> activate_twin_turbo_factor(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);

                static std::shared_ptr<yli::datatypes::AnyValue> activate_mouse_speed(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);

                static std::shared_ptr<yli::datatypes::AnyValue> activate_is_flight_mode_in_use(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);
                static std::shared_ptr<yli::datatypes::AnyValue> activate_console_top_y(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);
                static std::shared_ptr<yli::datatypes::AnyValue> activate_console_bottom_y(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);
                static std::shared_ptr<yli::datatypes::AnyValue> activate_console_left_x(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);
                static std::shared_ptr<yli::datatypes::AnyValue> activate_console_right_x(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);

                static std::shared_ptr<yli::datatypes::AnyValue> read_should_be_rendered(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);
                static std::shared_ptr<yli::datatypes::AnyValue> read_cartesian_coordinates(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);
                static std::shared_ptr<yli::datatypes::AnyValue> read_x(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);
                static std::shared_ptr<yli::datatypes::AnyValue> read_y(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);
                static std::shared_ptr<yli::datatypes::AnyValue> read_z(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);

                static std::shared_ptr<yli::datatypes::AnyValue> read_rho(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);
                static std::shared_ptr<yli::datatypes::AnyValue> read_theta(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);
                static std::shared_ptr<yli::datatypes::AnyValue> read_phi(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);

                static std::shared_ptr<yli::datatypes::AnyValue> read_up(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);
                static std::shared_ptr<yli::datatypes::AnyValue> read_right(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);

                static std::shared_ptr<yli::datatypes::AnyValue> read_horizontal_angle(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);
                static std::shared_ptr<yli::datatypes::AnyValue> read_vertical_angle(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);

                static std::shared_ptr<yli::datatypes::AnyValue> read_is_flight_mode_in_use(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);

                // Public callbacks end here.

                friend class Setting;
                friend class yli::ontology::Entity;
                friend class yli::console::Console;

            private:
                yli::ontology::Entity* parent;

                std::vector<yli::config::Setting*> setting_pointer_vector;
                std::queue<std::size_t> free_settingID_queue;
                std::size_t number_of_settings;

                std::unordered_map<std::string, yli::config::Setting*> setting_pointer_map;
        };
    }
}

#endif
