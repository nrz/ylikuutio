#include "ajokki_background_colors.hpp"
#include "code/ylikuutio/config/setting.hpp"
#include "code/ylikuutio/config/setting_master.hpp"
#include "code/ylikuutio/common/any_value.hpp"
#include "code/ylikuutio/common/globals.hpp"

// Include standard headers
#include <memory> // std::make_shared, std::shared_ptr

namespace ajokki
{
    void set_background_colors(config::SettingMaster* setting_master)
    {
        // Blue background.

        float float_zero = 0.0f;
        float float_one = 1.0f;

        SettingStruct red_setting_struct(std::make_shared<datatypes::AnyValue>(float_zero));
        red_setting_struct.name = "red";
        red_setting_struct.setting_master = setting_master;
        red_setting_struct.activate_callback = &config::SettingMaster::activate_background_color;
        red_setting_struct.should_ylikuutio_call_activate_callback_now = false;
        new config::Setting(red_setting_struct);

        SettingStruct green_setting_struct(std::make_shared<datatypes::AnyValue>(float_zero));
        green_setting_struct.name = "green";
        green_setting_struct.setting_master = setting_master;
        green_setting_struct.activate_callback = &config::SettingMaster::activate_background_color;
        green_setting_struct.should_ylikuutio_call_activate_callback_now = false;
        new config::Setting(green_setting_struct);

        SettingStruct blue_setting_struct(std::make_shared<datatypes::AnyValue>(float_one));
        blue_setting_struct.name = "blue";
        blue_setting_struct.setting_master = setting_master;
        blue_setting_struct.activate_callback = &config::SettingMaster::activate_background_color;
        blue_setting_struct.should_ylikuutio_call_activate_callback_now = false;
        new config::Setting(blue_setting_struct);

        SettingStruct alpha_setting_struct(std::make_shared<datatypes::AnyValue>(float_zero));
        alpha_setting_struct.name = "alpha";
        alpha_setting_struct.setting_master = setting_master;
        alpha_setting_struct.activate_callback = &config::SettingMaster::activate_background_color;
        alpha_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        new config::Setting(alpha_setting_struct);
    }
}
