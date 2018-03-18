#include "ajokki_wireframe.hpp"
#include "code/ylikuutio/config/setting.hpp"
#include "code/ylikuutio/config/setting_master.hpp"
#include "code/ylikuutio/config/setting_struct.hpp"
#include "code/ylikuutio/common/any_value.hpp"

// Include standard headers
#include <memory> // std::make_shared, std::shared_ptr

namespace ajokki
{
    void set_wireframe(config::SettingMaster* setting_master)
    {
        // Do not use wireframe by default.

        bool bool_false = false;

        SettingStruct wireframe_setting_struct(std::make_shared<datatypes::AnyValue>(bool_false));
        wireframe_setting_struct.name = "wireframe";
        wireframe_setting_struct.setting_master = setting_master;
        wireframe_setting_struct.activate_callback = &config::SettingMaster::activate_wireframe;
        wireframe_setting_struct.should_ylikuutio_call_activate_callback_now = true;
        new config::Setting(wireframe_setting_struct);
    }
}
