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

namespace yli
{
    namespace config
    {
        class SettingMaster;
        struct SettingStruct;

        class Setting
        {
            public:
                // destructor.
                ~Setting();

                std::string help() const;

                friend SettingMaster;

                template<class T1>
                    friend void yli::hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue, std::size_t& number_of_children);

            private:
                // constructor (to be called from `SettingMaster::create_Setting`).
                Setting(yli::config::SettingMaster* const setting_master, const yli::config::SettingStruct& setting_struct);

                void bind_to_parent();

                std::string name;

                // The setting value (may be a pointer a some datatype).
                std::shared_ptr<yli::common::AnyValue> setting_value;

                // pointer to `ActivateCallback` used to activate the new value after setting it.
                ActivateCallback activate_callback;

                // pointer to `ReadCallback` used to read the value. Leave to `nullptr` to read the value from `setting_value` of `class Setting`.
                ReadCallback read_callback;

                yli::config::SettingMaster* parent; // pointer to `SettingMaster`.

                std::size_t childID;                // setting ID, returned by `yli::config::SettingMaster->get_settingID()`.
        };
    }
}

#endif
