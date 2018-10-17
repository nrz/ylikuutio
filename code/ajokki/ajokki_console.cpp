#include "ajokki_console.hpp"
#include "code/ylikuutio/config/setting.hpp"
#include "code/ylikuutio/config/setting_master.hpp"
#include "code/ylikuutio/config/setting_struct.hpp"
#include "code/ylikuutio/common/any_value.hpp"

// Include standard headers
#include <memory> // std::make_shared, std::shared_ptr
#include <stdint.h> // uint32_t etc.

namespace yli
{
    namespace config
    {
        class SettingMaster;
    }
}

namespace ajokki
{
    void set_console(yli::config::SettingMaster* const setting_master)
    {
        // Variables related to console.
        const uint32_t console_top_y = 15;
        SettingStruct console_top_y_setting_struct(std::make_shared<yli::datatypes::AnyValue>(console_top_y));
        console_top_y_setting_struct.name = "console_top_y";
        console_top_y_setting_struct.setting_master = setting_master;
        console_top_y_setting_struct.activate_callback = &yli::config::SettingMaster::activate_console_top_y;
        console_top_y_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        new yli::config::Setting(console_top_y_setting_struct);

        const uint32_t console_bottom_y = 0;
        SettingStruct console_bottom_y_setting_struct(std::make_shared<yli::datatypes::AnyValue>(console_bottom_y));
        console_bottom_y_setting_struct.name = "console_bottom_y";
        console_bottom_y_setting_struct.setting_master = setting_master;
        console_bottom_y_setting_struct.activate_callback = &yli::config::SettingMaster::activate_console_bottom_y;
        console_bottom_y_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        new yli::config::Setting(console_bottom_y_setting_struct);

        const uint32_t console_right_x = 39;
        SettingStruct console_right_x_setting_struct(std::make_shared<yli::datatypes::AnyValue>(console_right_x));
        console_right_x_setting_struct.name = "console_right_x";
        console_right_x_setting_struct.setting_master = setting_master;
        console_right_x_setting_struct.activate_callback = &yli::config::SettingMaster::activate_console_right_x;
        console_right_x_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        new yli::config::Setting(console_right_x_setting_struct);

        const uint32_t console_left_x = 0;
        SettingStruct console_left_x_setting_struct(std::make_shared<yli::datatypes::AnyValue>(console_left_x));
        console_left_x_setting_struct.name = "console_left_x";
        console_left_x_setting_struct.setting_master = setting_master;
        console_left_x_setting_struct.activate_callback = &yli::config::SettingMaster::activate_console_left_x;
        console_left_x_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        new yli::config::Setting(console_left_x_setting_struct);
    }
}
