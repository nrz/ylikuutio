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

#ifndef __SETTING_MASTER_HPP_INCLUDED
#define __SETTING_MASTER_HPP_INCLUDED

// Include standard headers
#include <cstddef>       // std::size_t
#include <memory>        // std::make_shared, std::shared_ptr
#include <queue>         // std::queue
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

// `yli::config::SettingMaster` is the parent of `yli::config::Setting`.
// `SettingMaster` may be either global or bound to an `yli::ontology::Entity`.
// Each `SettingMaster` instance may have several `Setting`s.

namespace yli::data
{
    class AnyValue;
}

namespace yli::ontology
{
    class Entity;
    class Universe;
    class Console;
}

namespace yli::config
{
    class Setting;
    struct SettingStruct;

    class SettingMaster
    {
        public:
            // constructor.
            SettingMaster(yli::ontology::Entity* const entity);

            // destructor.
            ~SettingMaster();

            void create_setting(const yli::config::SettingStruct& setting_struct);

            // does setting `setting` exist?
            bool is_setting(const std::string& setting_name) const;

            // this function returns general help.
            std::string help() const;

            // this function returns help string for setting `setting`.
            std::string help(const std::string& setting_name) const;

            bool set(const std::string& setting_name, std::shared_ptr<yli::data::AnyValue> setting_new_any_value);

            yli::config::Setting* get(const std::string& setting_name) const;

            // Public callbacks.

            static std::shared_ptr<yli::data::AnyValue> print_settings0(
                    yli::ontology::Universe* const universe,
                    yli::ontology::Console* const console);

            static std::shared_ptr<yli::data::AnyValue> print_settings1(
                    yli::ontology::Universe* const universe,
                    yli::ontology::Console* const console,
                    yli::ontology::Entity* const entity);

            static std::shared_ptr<yli::data::AnyValue> activate_planet_radius(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);

            static std::shared_ptr<yli::data::AnyValue> activate_window_size(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);
            static std::shared_ptr<yli::data::AnyValue> activate_framebuffer_size(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);
            static std::shared_ptr<yli::data::AnyValue> activate_background_color(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);

            static std::shared_ptr<yli::data::AnyValue> activate_wireframe(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);

            static std::shared_ptr<yli::data::AnyValue> activate_should_be_rendered(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);
            static std::shared_ptr<yli::data::AnyValue> activate_spherical_coordinates(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);
            static std::shared_ptr<yli::data::AnyValue> activate_rho(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);
            static std::shared_ptr<yli::data::AnyValue> activate_theta(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);
            static std::shared_ptr<yli::data::AnyValue> activate_phi(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);

            static std::shared_ptr<yli::data::AnyValue> activate_cartesian_coordinates(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);
            static std::shared_ptr<yli::data::AnyValue> activate_x(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);
            static std::shared_ptr<yli::data::AnyValue> activate_y(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);
            static std::shared_ptr<yli::data::AnyValue> activate_z(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);

            static std::shared_ptr<yli::data::AnyValue> activate_horizontal_angle(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);

            static std::shared_ptr<yli::data::AnyValue> activate_vertical_angle(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);

            static std::shared_ptr<yli::data::AnyValue> activate_speed(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);

            static std::shared_ptr<yli::data::AnyValue> activate_turbo_factor(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);

            static std::shared_ptr<yli::data::AnyValue> activate_twin_turbo_factor(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);

            static std::shared_ptr<yli::data::AnyValue> activate_mouse_speed(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);

            static std::shared_ptr<yli::data::AnyValue> activate_is_flight_mode_in_use(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);
            static std::shared_ptr<yli::data::AnyValue> activate_console_top_y(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);
            static std::shared_ptr<yli::data::AnyValue> activate_console_bottom_y(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);
            static std::shared_ptr<yli::data::AnyValue> activate_console_left_x(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);
            static std::shared_ptr<yli::data::AnyValue> activate_console_right_x(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);

            static std::shared_ptr<yli::data::AnyValue> read_should_be_rendered(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);
            static std::shared_ptr<yli::data::AnyValue> read_cartesian_coordinates(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);
            static std::shared_ptr<yli::data::AnyValue> read_x(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);
            static std::shared_ptr<yli::data::AnyValue> read_y(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);
            static std::shared_ptr<yli::data::AnyValue> read_z(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);

            static std::shared_ptr<yli::data::AnyValue> read_rho(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);
            static std::shared_ptr<yli::data::AnyValue> read_theta(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);
            static std::shared_ptr<yli::data::AnyValue> read_phi(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);

            static std::shared_ptr<yli::data::AnyValue> read_up(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);
            static std::shared_ptr<yli::data::AnyValue> read_right(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);

            static std::shared_ptr<yli::data::AnyValue> read_horizontal_angle(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);
            static std::shared_ptr<yli::data::AnyValue> read_vertical_angle(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);

            static std::shared_ptr<yli::data::AnyValue> read_is_flight_mode_in_use(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master);

            // Public callbacks end here.

            friend class Setting;

        private:
            yli::ontology::Entity* parent;

            std::vector<yli::config::Setting*> setting_pointer_vector;
            std::queue<std::size_t> free_settingID_queue;
            std::size_t number_of_settings;

            std::unordered_map<std::string, yli::config::Setting*> setting_pointer_map;
    };
}

#endif
