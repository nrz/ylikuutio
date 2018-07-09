#include "ajokki_debug.hpp"
#include "code/ylikuutio/config/setting.hpp"
#include "code/ylikuutio/config/setting_master.hpp"
#include "code/ylikuutio/config/setting_struct.hpp"
#include "code/ylikuutio/common/any_value.hpp"

// Include standard headers
#include <memory> // std::make_shared, std::shared_ptr

namespace ajokki
{
    void set_debug_variables(yli::config::SettingMaster* setting_master)
    {
        bool is_flight_mode_in_use = true;
        std::shared_ptr<datatypes::AnyValue> any_value_is_flight_mode_in_use = std::make_shared<datatypes::AnyValue>(is_flight_mode_in_use);
        SettingStruct is_flight_mode_in_use_setting_struct(any_value_is_flight_mode_in_use);
        is_flight_mode_in_use_setting_struct.name = "is_flight_mode_in_use";
        is_flight_mode_in_use_setting_struct.setting_master = setting_master;
        is_flight_mode_in_use_setting_struct.activate_callback = &yli::config::SettingMaster::activate_is_flight_mode_in_use;
        is_flight_mode_in_use_setting_struct.read_callback = &yli::config::SettingMaster::read_is_flight_mode_in_use;
        is_flight_mode_in_use_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        new yli::config::Setting(is_flight_mode_in_use_setting_struct);
    }
}
