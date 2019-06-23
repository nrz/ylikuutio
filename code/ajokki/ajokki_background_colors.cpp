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

#include "ajokki_background_colors.hpp"
#include "code/ylikuutio/config/setting.hpp"
#include "code/ylikuutio/config/setting_master.hpp"
#include "code/ylikuutio/common/any_value.hpp"

// Include standard headers
#include <memory> // std::make_shared, std::shared_ptr

namespace ajokki
{
    void set_background_colors(yli::config::SettingMaster* setting_master)
    {
        // Blue background.

        float float_zero = 0.0f;
        float float_one = 1.0f;

        yli::config::SettingStruct red_setting_struct(std::make_shared<yli::common::AnyValue>(float_zero));
        red_setting_struct.name = "red";
        red_setting_struct.setting_master = setting_master;
        red_setting_struct.activate_callback = &yli::config::SettingMaster::activate_background_color;
        red_setting_struct.should_ylikuutio_call_activate_callback_now = false;
        new yli::config::Setting(red_setting_struct);

        yli::config::SettingStruct green_setting_struct(std::make_shared<yli::common::AnyValue>(float_zero));
        green_setting_struct.name = "green";
        green_setting_struct.setting_master = setting_master;
        green_setting_struct.activate_callback = &yli::config::SettingMaster::activate_background_color;
        green_setting_struct.should_ylikuutio_call_activate_callback_now = false;
        new yli::config::Setting(green_setting_struct);

        yli::config::SettingStruct blue_setting_struct(std::make_shared<yli::common::AnyValue>(float_one));
        blue_setting_struct.name = "blue";
        blue_setting_struct.setting_master = setting_master;
        blue_setting_struct.activate_callback = &yli::config::SettingMaster::activate_background_color;
        blue_setting_struct.should_ylikuutio_call_activate_callback_now = false;
        new yli::config::Setting(blue_setting_struct);

        yli::config::SettingStruct alpha_setting_struct(std::make_shared<yli::common::AnyValue>(float_zero));
        alpha_setting_struct.name = "alpha";
        alpha_setting_struct.setting_master = setting_master;
        alpha_setting_struct.activate_callback = &yli::config::SettingMaster::activate_background_color;
        alpha_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        new yli::config::Setting(alpha_setting_struct);
    }
}
