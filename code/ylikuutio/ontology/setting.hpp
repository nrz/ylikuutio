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

#include "entity.hpp"
#include "activate_callback.hpp"
#include "read_callback.hpp"
#include "setting_struct.hpp"

// Include standard headers
#include <memory>   // std::make_shared, std::shared_ptr
#include <queue>    // std::queue
#include <string>   // std::string
#include <vector>   // std::vector

// `yli::ontology::Setting` provides setting-related functionality.
// `Setting`s must be bound to an `Entity`.
//
// Each `Setting` may have `activate_callback` and `read_callback`.
//
// If `activate_callback` is defined, then it is used to activate the
// new value of a `Setting` after defining it.
//
// If `read_callback` is defined, then it is used to read the value
// instead of reading it from `setting_value` member variable, that
// stores the value as `std::shared_ptr<yli::data::AnyValue>`.
//
// `read_callback` may, of course, compute the returned value
// based on some other variables as well etc.

namespace yli::data
{
    class AnyValue;
}

namespace yli::ontology
{
    class Entity;
    class Universe;
    class Console;

    class Setting: public yli::ontology::Entity 
    {
        public:
            // constructor (to be called from `Entity::create_setting`).
            Setting(yli::ontology::Universe* const universe, const yli::ontology::SettingStruct& setting_struct)
                : Entity(universe, setting_struct)
            {
                // constructor.
                this->parent = setting_struct.parent;
                this->setting_value = setting_struct.initial_value;
                this->activate_callback = setting_struct.activate_callback;
                this->read_callback = setting_struct.read_callback;

                // Get `childID` from `Entity` and set pointer to this `Setting`.
                this->bind_to_parent();

                // `yli::ontology::Entity` member variables begin here.
                this->type_string = "yli::ontology::Setting*";
                this->can_be_erased = true;
            }

            Setting(const Setting&) = delete;            // Delete copy constructor.
            Setting &operator=(const Setting&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~Setting();

            yli::ontology::Entity* get_parent() const override;
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            std::string help() const;

            std::shared_ptr<yli::data::AnyValue> get();
            void set(std::shared_ptr<yli::data::AnyValue> new_value);
            void set(const std::string& new_value);

            // Public callbacks.

            static std::shared_ptr<yli::data::AnyValue> set2(
                    yli::ontology::Setting* const setting,
                    std::shared_ptr<std::string> new_value);

            static std::shared_ptr<yli::data::AnyValue> print_value1(
                    yli::ontology::Console* const console,
                    yli::ontology::Universe* const context, // A context is needed so that correct `Setting is bound to the function call.
                    yli::ontology::Setting* const setting);

            static std::shared_ptr<yli::data::AnyValue> activate_planet_radius(yli::ontology::Entity* const entity, yli::ontology::Setting* const setting);

            static std::shared_ptr<yli::data::AnyValue> activate_window_size(yli::ontology::Entity* const entity, yli::ontology::Setting* const setting);
            static std::shared_ptr<yli::data::AnyValue> activate_framebuffer_size(yli::ontology::Entity* const entity, yli::ontology::Setting* const setting);
            static std::shared_ptr<yli::data::AnyValue> activate_background_color(yli::ontology::Entity* const entity, yli::ontology::Setting* const setting);

            static std::shared_ptr<yli::data::AnyValue> activate_wireframe(yli::ontology::Entity* const entity, yli::ontology::Setting* const setting);

            static std::shared_ptr<yli::data::AnyValue> activate_speed(yli::ontology::Entity* const entity, yli::ontology::Setting* const setting);
            static std::shared_ptr<yli::data::AnyValue> activate_turbo_factor(yli::ontology::Entity* const entity, yli::ontology::Setting* const setting);
            static std::shared_ptr<yli::data::AnyValue> activate_twin_turbo_factor(yli::ontology::Entity* const entity, yli::ontology::Setting* const setting);
            static std::shared_ptr<yli::data::AnyValue> activate_mouse_speed(yli::ontology::Entity* const entity, yli::ontology::Setting* const setting);

            static std::shared_ptr<yli::data::AnyValue> activate_is_flight_mode_in_use(yli::ontology::Entity* const entity, yli::ontology::Setting* const setting);
            static std::shared_ptr<yli::data::AnyValue> activate_console_top_y(yli::ontology::Entity* const entity, yli::ontology::Setting* const setting);
            static std::shared_ptr<yli::data::AnyValue> activate_console_bottom_y(yli::ontology::Entity* const entity, yli::ontology::Setting* const setting);
            static std::shared_ptr<yli::data::AnyValue> activate_console_left_x(yli::ontology::Entity* const entity, yli::ontology::Setting* const setting);
            static std::shared_ptr<yli::data::AnyValue> activate_console_right_x(yli::ontology::Entity* const entity, yli::ontology::Setting* const setting);

            static std::shared_ptr<yli::data::AnyValue> read_is_flight_mode_in_use(yli::ontology::Entity* const entity);

            // Public callbacks and here.

        private:
            void bind_to_parent();

            void activate() override;

            yli::ontology::Entity* parent;

        public:
            // The setting value (may be a pointer a some datatype).
            std::shared_ptr<yli::data::AnyValue> setting_value;

        private:
            // pointer to `ActivateCallback` used to activate the new value after setting it.
            ActivateCallback activate_callback;

            // pointer to `ReadCallback` used to read the value. Leave to `nullptr` to read the value from `setting_value` of `class Setting`.
            ReadCallback read_callback;
    };
}

#endif
