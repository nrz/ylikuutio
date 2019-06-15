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

#include "ajokki_wireframe.hpp"
#include "code/ylikuutio/config/setting.hpp"
#include "code/ylikuutio/config/setting_master.hpp"
#include "code/ylikuutio/config/setting_struct.hpp"
#include "code/ylikuutio/common/any_value.hpp"

// Include standard headers
#include <memory> // std::make_shared, std::shared_ptr

namespace ajokki
{
    void set_wireframe(yli::config::SettingMaster* setting_master)
    {
        // Do not use wireframe by default.

        bool bool_false = false;

        yli::config::SettingStruct wireframe_setting_struct(std::make_shared<yli::datatypes::AnyValue>(bool_false));
        wireframe_setting_struct.name = "wireframe";
        wireframe_setting_struct.setting_master = setting_master;
        wireframe_setting_struct.activate_callback = &yli::config::SettingMaster::activate_wireframe;
        wireframe_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        new yli::config::Setting(wireframe_setting_struct);
    }
}
