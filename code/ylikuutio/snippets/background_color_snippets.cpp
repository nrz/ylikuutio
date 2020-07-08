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

#include "background_color_snippets.hpp"
#include "code/ylikuutio/ontology/setting.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/setting_struct.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <memory> // std::make_shared, std::shared_ptr

namespace yli::snippets
{
    void set_background_colors(yli::ontology::Universe* universe, const float red, const float green, const float blue, const float alpha)
    {
        if (universe == nullptr)
        {
            return;
        }

        yli::ontology::SettingStruct red_setting_struct(std::make_shared<yli::data::AnyValue>(red));
        red_setting_struct.local_name = "red";
        red_setting_struct.activate_callback = &yli::ontology::Setting::activate_background_color;
        red_setting_struct.should_ylikuutio_call_activate_callback_now = false;
        universe->create_setting(red_setting_struct);

        yli::ontology::SettingStruct green_setting_struct(std::make_shared<yli::data::AnyValue>(green));
        green_setting_struct.local_name = "green";
        green_setting_struct.activate_callback = &yli::ontology::Setting::activate_background_color;
        green_setting_struct.should_ylikuutio_call_activate_callback_now = false;
        universe->create_setting(green_setting_struct);

        yli::ontology::SettingStruct blue_setting_struct(std::make_shared<yli::data::AnyValue>(blue));
        blue_setting_struct.local_name = "blue";
        blue_setting_struct.activate_callback = &yli::ontology::Setting::activate_background_color;
        blue_setting_struct.should_ylikuutio_call_activate_callback_now = false;
        universe->create_setting(blue_setting_struct);

        yli::ontology::SettingStruct alpha_setting_struct(std::make_shared<yli::data::AnyValue>(alpha));
        alpha_setting_struct.local_name = "alpha";
        alpha_setting_struct.activate_callback = &yli::ontology::Setting::activate_background_color;
        alpha_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        universe->create_setting(alpha_setting_struct);
    }
}
