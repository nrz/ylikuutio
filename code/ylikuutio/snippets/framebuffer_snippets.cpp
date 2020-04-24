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

#include "framebuffer_snippets.hpp"
#include "code/ylikuutio/config/setting_master.hpp"
#include "code/ylikuutio/config/setting_struct.hpp"
#include "code/ylikuutio/common/any_value.hpp"

// Include standard headers
#include <stdint.h> // uint32_t etc.

namespace yli::snippets
{
    void set_framebuffer_size(yli::config::SettingMaster* setting_master, const uint32_t framebuffer_width, const uint32_t framebuffer_height)
    {
        yli::config::SettingStruct framebuffer_width_setting_struct(std::make_shared<yli::common::AnyValue>(framebuffer_width));
        framebuffer_width_setting_struct.name = "framebuffer_width";
        framebuffer_width_setting_struct.activate_callback = &yli::config::SettingMaster::activate_framebuffer_size;
        framebuffer_width_setting_struct.should_ylikuutio_call_activate_callback_now = false;
        setting_master->create_Setting(framebuffer_width_setting_struct);

        yli::config::SettingStruct framebuffer_height_setting_struct(std::make_shared<yli::common::AnyValue>(framebuffer_height));
        framebuffer_height_setting_struct.name = "framebuffer_height";
        framebuffer_height_setting_struct.activate_callback = &yli::config::SettingMaster::activate_framebuffer_size;
        framebuffer_height_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        setting_master->create_Setting(framebuffer_height_setting_struct);
    }
}
