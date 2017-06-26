#include "ajokki_background_colors.hpp"
#include "code/ylikuutio/config/setting.hpp"
#include "code/ylikuutio/config/setting_master.hpp"
#include "code/ylikuutio/common/any_value.hpp"
#include "code/ylikuutio/common/globals.hpp"

namespace ajokki
{
    void set_background_colors(config::SettingMaster* setting_master)
    {
        // Blue background.

        float float_zero = 0.0f;
        datatypes::AnyValue any_value_float_zero = datatypes::AnyValue(float_zero);

        float float_one = 1.0f;
        datatypes::AnyValue any_value_float_one = datatypes::AnyValue(float_one);

        SettingStruct red_setting_struct(any_value_float_zero);
        red_setting_struct.name = "red";
        red_setting_struct.setting_master_pointer = setting_master;
        red_setting_struct.activate_callback = &config::SettingMaster::activate_background_color;
        red_setting_struct.should_ylikuutio_call_activate_callback_now = false;
        config::Setting* my_background_red = new config::Setting(red_setting_struct);

        SettingStruct green_setting_struct(any_value_float_zero);
        green_setting_struct.name = "green";
        green_setting_struct.setting_master_pointer = setting_master;
        green_setting_struct.activate_callback = &config::SettingMaster::activate_background_color;
        green_setting_struct.should_ylikuutio_call_activate_callback_now = false;
        config::Setting* my_background_green = new config::Setting(green_setting_struct);

        SettingStruct blue_setting_struct(any_value_float_one);
        blue_setting_struct.name = "blue";
        blue_setting_struct.setting_master_pointer = setting_master;
        blue_setting_struct.activate_callback = &config::SettingMaster::activate_background_color;
        blue_setting_struct.should_ylikuutio_call_activate_callback_now = false;
        config::Setting* my_background_blue = new config::Setting(blue_setting_struct);

        SettingStruct alpha_setting_struct(any_value_float_zero);
        alpha_setting_struct.name = "alpha";
        alpha_setting_struct.initial_value = any_value_float_zero;
        alpha_setting_struct.setting_master_pointer = setting_master;
        alpha_setting_struct.activate_callback = &config::SettingMaster::activate_background_color;
        alpha_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        config::Setting* my_background_alpha = new config::Setting(alpha_setting_struct);
    }
}
