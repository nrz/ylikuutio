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

#ifndef __SETTING_STRUCT_HPP_INCLUDED
#define __SETTING_STRUCT_HPP_INCLUDED

#include "entity_struct.hpp"
#include "activate_callback.hpp"
#include "read_callback.hpp"

// Include standard headers
#include <memory>   // std::make_shared, std::shared_ptr

namespace yli::data
{
    class AnyValue;
}

namespace yli::ontology
{
    class Entity;

    struct SettingStruct: public yli::ontology::EntityStruct
    {
        SettingStruct()
            : EntityStruct(),
            parent(nullptr),
            initial_value(nullptr),
            activate_callback(nullptr),
            read_callback(nullptr),
            should_ylikuutio_call_activate_callback_now(true)
        {
            // constructor.
            this->is_setting = true;
        }

        SettingStruct(std::shared_ptr<yli::data::AnyValue> initial_value)
            : EntityStruct(),
            parent(nullptr),
            initial_value(initial_value),
            activate_callback(nullptr),
            read_callback(nullptr),
            should_ylikuutio_call_activate_callback_now(true)
        {
            // constructor.
            this->is_setting = true;
        }

        SettingStruct(const yli::ontology::SettingStruct& setting_struct)
            : EntityStruct(setting_struct),
            parent(setting_struct.parent),
            initial_value(setting_struct.initial_value),
            activate_callback(setting_struct.activate_callback),
            read_callback(setting_struct.read_callback),
            should_ylikuutio_call_activate_callback_now(setting_struct.should_ylikuutio_call_activate_callback_now)
        {
            // copy constructor.
            this->global_name = setting_struct.global_name;
            this->local_name = setting_struct.local_name;
            this->is_setting = true;
        }

        yli::ontology::Entity* parent;
        std::shared_ptr<yli::data::AnyValue> initial_value;
        ActivateCallback activate_callback;
        ReadCallback read_callback;
        bool should_ylikuutio_call_activate_callback_now;
    };
}

#endif
