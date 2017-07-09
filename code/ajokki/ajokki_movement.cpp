#include "ajokki_movement.hpp"
#include "code/ylikuutio/config/setting.hpp"
#include "code/ylikuutio/config/setting_master.hpp"
#include "code/ylikuutio/common/any_value.hpp"
#include "code/ylikuutio/common/globals.hpp"

namespace config
{
    class SettingMaster;
}

namespace ajokki
{
    void set_movement(config::SettingMaster* const setting_master)
    {
        // Variables related to voluntary movement.
        float speed = 5.0f; // 5 units / second
        datatypes::AnyValue* any_value_speed = new datatypes::AnyValue(speed);
        SettingStruct speed_setting_struct(any_value_speed);
        speed_setting_struct.name = "speed";
        speed_setting_struct.setting_master_pointer = setting_master;
        speed_setting_struct.activate_callback = &config::SettingMaster::activate_speed;
        speed_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        new config::Setting(speed_setting_struct);

        float turbo_factor = 5.0f;
        // float turbo_factor = 100.0f;
        datatypes::AnyValue* any_value_turbo_factor = new datatypes::AnyValue(turbo_factor);
        SettingStruct turbo_factor_setting_struct(any_value_turbo_factor);
        turbo_factor_setting_struct.name = "turbo_factor";
        turbo_factor_setting_struct.setting_master_pointer = setting_master;
        turbo_factor_setting_struct.activate_callback = &config::SettingMaster::activate_turbo_factor;
        turbo_factor_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        new config::Setting(turbo_factor_setting_struct);

        float twin_turbo_factor = 100.0f;
        // float twin_turbo_factor = 50000.0f;
        datatypes::AnyValue* any_value_twin_turbo_factor = new datatypes::AnyValue(twin_turbo_factor);
        SettingStruct twin_turbo_factor_setting_struct(any_value_twin_turbo_factor);
        twin_turbo_factor_setting_struct.name = "twin_turbo_factor";
        twin_turbo_factor_setting_struct.setting_master_pointer = setting_master;
        twin_turbo_factor_setting_struct.activate_callback = &config::SettingMaster::activate_twin_turbo_factor;
        twin_turbo_factor_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        new config::Setting(twin_turbo_factor_setting_struct);

        float mouse_speed = 0.005f;
        datatypes::AnyValue* any_value_mouse_speed = new datatypes::AnyValue(mouse_speed);
        SettingStruct mouse_speed_setting_struct(any_value_mouse_speed);
        mouse_speed_setting_struct.name = "mouse_speed";
        mouse_speed_setting_struct.setting_master_pointer = setting_master;
        mouse_speed_setting_struct.activate_callback = &config::SettingMaster::activate_mouse_speed;
        mouse_speed_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        new config::Setting(mouse_speed_setting_struct);
    }
}
