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

#include "setting.hpp"
#include "setting_master.hpp"
#include "setting_struct.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <limits>   // std::numeric_limits
#include <string>   // std::string

namespace yli
{
    namespace config
    {
        void Setting::bind_to_parent()
        {
            yli::hierarchy::bind_child_to_parent<yli::config::Setting*>(this, this->parent->setting_pointer_vector, this->parent->free_settingID_queue, this->parent->number_of_settings);
        }

        Setting::Setting(yli::config::SettingMaster* const setting_master, const yli::config::SettingStruct& setting_struct)
        {
            // constructor.
            this->name = setting_struct.name;
            this->setting_value = setting_struct.initial_value;
            this->parent = setting_master;
            this->activate_callback = setting_struct.activate_callback;
            this->read_callback = setting_struct.read_callback;
            this->childID = std::numeric_limits<std::size_t>::max();

            if (this->parent == nullptr)
            {
                return;
            }

            // get `childID` from the `SettingMaster` and set pointer to this `Setting`.
            this->bind_to_parent();

            this->parent->setting_pointer_map[this->name] = this;

            if (setting_struct.should_ylikuutio_call_activate_callback_now && this->activate_callback != nullptr && this->parent->parent != nullptr)
            {
                this->activate_callback(this->parent->parent, this->parent);
            }
        }

        Setting::~Setting()
        {
            // destructor.
        }

        std::string Setting::help() const
        {
            // this function returns the help string for this setting.
            std::string help_string = this->name + " TODO: create helptext for " + this->name;
            return help_string;
        }
    }
}
