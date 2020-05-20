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

#ifndef __SETTING_HPP_INCLUDED
#define __SETTING_HPP_INCLUDED

#include "activate_callback.hpp"
#include "read_callback.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <memory>   // std::make_shared, std::shared_ptr
#include <queue>    // std::queue
#include <string>   // std::string
#include <vector>   // std::vector

// `yli::ontology::Setting` provides setting-related functionality.
// `Setting`s must be bound to a `SettingMaster`, which may be either
// global or bound to a specific `yli::ontology::Entity`.
// Each `Setting` may have `activate_callback` and `read_callback`.
//
// If `activate_callback` is defined, then it is used to activate the
// new value of a `Setting` after defining it.
//
// If `read_callback` is defined, then it is used to read the value
// instead of reading it from the corresponding value in the
// `setting_pointer_map` member variable of `SettingMaster`.
//
// The value of each `Setting` is stored as `yli::data::AnyValue`.

namespace yli::ontology
{
    class Entity;
    class Console;
}

namespace yli::data
{
    class AnyValue;
}

namespace yli::config
{
    class SettingMaster;
    struct SettingStruct;

    class Setting
    {
        public:
            // constructor (to be called from `SettingMaster::create_setting`).
            Setting(yli::config::SettingMaster* const setting_master, const yli::config::SettingStruct& setting_struct);

            // destructor.
            ~Setting();

            std::string help() const;

            std::shared_ptr<yli::data::AnyValue> get();
            void set(std::shared_ptr<yli::data::AnyValue> new_value);
            void set(const std::string& new_value);

            // Public callbacks.

            static std::shared_ptr<yli::data::AnyValue> set2(
                    yli::config::Setting* const setting,
                    std::shared_ptr<std::string> new_value);

            static std::shared_ptr<yli::data::AnyValue> set3(
                    yli::ontology::Entity* const context,
                    yli::config::Setting* const setting,
                    std::shared_ptr<std::string> new_value);

            static std::shared_ptr<yli::data::AnyValue> print_value1(
                    yli::ontology::Console* const console,
                    yli::ontology::Universe* const context, // A context is needed so that correct `Setting is bound to the function call.
                    yli::config::Setting* const setting);

            static std::shared_ptr<yli::data::AnyValue> print_value2(
                    yli::ontology::Console* const console,
                    yli::ontology::Entity* const context,   // A context is needed so that correct `Setting is bound to the function call.
                    yli::config::Setting* const setting);

            static std::shared_ptr<yli::data::AnyValue> activate_planet_radius(yli::ontology::Entity* const entity, yli::config::Setting* const setting);

            static std::shared_ptr<yli::data::AnyValue> activate_window_size(yli::ontology::Entity* const entity, yli::config::Setting* const setting);
            static std::shared_ptr<yli::data::AnyValue> activate_framebuffer_size(yli::ontology::Entity* const entity, yli::config::Setting* const setting);
            static std::shared_ptr<yli::data::AnyValue> activate_background_color(yli::ontology::Entity* const entity, yli::config::Setting* const setting);

            static std::shared_ptr<yli::data::AnyValue> activate_wireframe(yli::ontology::Entity* const entity, yli::config::Setting* const setting);

            static std::shared_ptr<yli::data::AnyValue> activate_should_be_rendered(yli::ontology::Entity* const entity, yli::config::Setting* const setting);
            static std::shared_ptr<yli::data::AnyValue> activate_spherical_coordinates(yli::ontology::Entity* const entity, yli::config::Setting* const setting);
            static std::shared_ptr<yli::data::AnyValue> activate_rho(yli::ontology::Entity* const entity, yli::config::Setting* const setting);
            static std::shared_ptr<yli::data::AnyValue> activate_theta(yli::ontology::Entity* const entity, yli::config::Setting* const setting);
            static std::shared_ptr<yli::data::AnyValue> activate_phi(yli::ontology::Entity* const entity, yli::config::Setting* const setting);

            static std::shared_ptr<yli::data::AnyValue> activate_cartesian_coordinates(yli::ontology::Entity* const entity, yli::config::Setting* const setting);
            static std::shared_ptr<yli::data::AnyValue> activate_x(yli::ontology::Entity* const entity, yli::config::Setting* const setting);
            static std::shared_ptr<yli::data::AnyValue> activate_y(yli::ontology::Entity* const entity, yli::config::Setting* const setting);
            static std::shared_ptr<yli::data::AnyValue> activate_z(yli::ontology::Entity* const entity, yli::config::Setting* const setting);

            static std::shared_ptr<yli::data::AnyValue> activate_horizontal_angle(yli::ontology::Entity* const entity, yli::config::Setting* const setting);

            static std::shared_ptr<yli::data::AnyValue> activate_vertical_angle(yli::ontology::Entity* const entity, yli::config::Setting* const setting);

            static std::shared_ptr<yli::data::AnyValue> activate_speed(yli::ontology::Entity* const entity, yli::config::Setting* const setting);

            static std::shared_ptr<yli::data::AnyValue> activate_turbo_factor(yli::ontology::Entity* const entity, yli::config::Setting* const setting);

            static std::shared_ptr<yli::data::AnyValue> activate_twin_turbo_factor(yli::ontology::Entity* const entity, yli::config::Setting* const setting);

            static std::shared_ptr<yli::data::AnyValue> activate_mouse_speed(yli::ontology::Entity* const entity, yli::config::Setting* const setting);

            static std::shared_ptr<yli::data::AnyValue> activate_is_flight_mode_in_use(yli::ontology::Entity* const entity, yli::config::Setting* const setting);
            static std::shared_ptr<yli::data::AnyValue> activate_console_top_y(yli::ontology::Entity* const entity, yli::config::Setting* const setting);
            static std::shared_ptr<yli::data::AnyValue> activate_console_bottom_y(yli::ontology::Entity* const entity, yli::config::Setting* const setting);
            static std::shared_ptr<yli::data::AnyValue> activate_console_left_x(yli::ontology::Entity* const entity, yli::config::Setting* const setting);
            static std::shared_ptr<yli::data::AnyValue> activate_console_right_x(yli::ontology::Entity* const entity, yli::config::Setting* const setting);

            static std::shared_ptr<yli::data::AnyValue> read_should_be_rendered(yli::ontology::Entity* const entity);
            static std::shared_ptr<yli::data::AnyValue> read_cartesian_coordinates(yli::ontology::Entity* const entity);
            static std::shared_ptr<yli::data::AnyValue> read_x(yli::ontology::Entity* const entity);
            static std::shared_ptr<yli::data::AnyValue> read_y(yli::ontology::Entity* const entity);
            static std::shared_ptr<yli::data::AnyValue> read_z(yli::ontology::Entity* const entity);

            static std::shared_ptr<yli::data::AnyValue> read_rho(yli::ontology::Entity* const entity);
            static std::shared_ptr<yli::data::AnyValue> read_theta(yli::ontology::Entity* const entity);
            static std::shared_ptr<yli::data::AnyValue> read_phi(yli::ontology::Entity* const entity);

            static std::shared_ptr<yli::data::AnyValue> read_up(yli::ontology::Entity* const entity);
            static std::shared_ptr<yli::data::AnyValue> read_right(yli::ontology::Entity* const entity);

            static std::shared_ptr<yli::data::AnyValue> read_horizontal_angle(yli::ontology::Entity* const entity);
            static std::shared_ptr<yli::data::AnyValue> read_vertical_angle(yli::ontology::Entity* const entity);

            static std::shared_ptr<yli::data::AnyValue> read_is_flight_mode_in_use(yli::ontology::Entity* const entity);

            // Public callbacks and here.

            template<class T1>
                friend void yli::hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue, std::size_t& number_of_children);

        private:
            void bind_to_parent();

            std::string name;

            // The setting value (may be a pointer a some datatype).
            std::shared_ptr<yli::data::AnyValue> setting_value;

            // pointer to `ActivateCallback` used to activate the new value after setting it.
            ActivateCallback activate_callback;

            // pointer to `ReadCallback` used to read the value. Leave to `nullptr` to read the value from `setting_value` of `class Setting`.
            ReadCallback read_callback;

            yli::config::SettingMaster* parent; // pointer to `SettingMaster`.

            std::size_t childID;                // setting ID, returned by `yli::config::SettingMaster->get_settingID()`.
    };
}

#endif
