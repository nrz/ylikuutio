#include "ajokki_console.hpp"
#include "code/ylikuutio/config/setting.hpp"
#include "code/ylikuutio/config/setting_master.hpp"
#include "code/ylikuutio/common/any_value.hpp"
#include "code/ylikuutio/common/globals.hpp"

// Include standard headers
#include <memory> // std::make_shared, std::shared_ptr

namespace config
{
    class SettingMaster;
}

namespace ajokki
{
    void set_console(config::SettingMaster* const setting_master)
    {
        // Variables related to console.
        uint32_t console_top_y = 15;
        std::shared_ptr<datatypes::AnyValue> any_value_console_top_y = std::make_shared<datatypes::AnyValue>(console_top_y);
        SettingStruct console_top_y_setting_struct(any_value_console_top_y);
        console_top_y_setting_struct.name = "console_top_y";
        console_top_y_setting_struct.setting_master_pointer = setting_master;
        console_top_y_setting_struct.activate_callback = nullptr;
        console_top_y_setting_struct.should_ylikuutio_call_activate_callback_now = false;
        new config::Setting(console_top_y_setting_struct);

        uint32_t console_bottom_y = 0;
        std::shared_ptr<datatypes::AnyValue> any_value_console_bottom_y = std::make_shared<datatypes::AnyValue>(console_bottom_y);
        SettingStruct console_bottom_y_setting_struct(any_value_console_bottom_y);
        console_bottom_y_setting_struct.name = "console_bottom_y";
        console_bottom_y_setting_struct.setting_master_pointer = setting_master;
        console_bottom_y_setting_struct.activate_callback = nullptr;
        console_bottom_y_setting_struct.should_ylikuutio_call_activate_callback_now = false;
        new config::Setting(console_bottom_y_setting_struct);
    }
}
