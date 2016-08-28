#include "setting.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/common/globals.hpp"

// Include standard headers
#include <string>   // std::string

namespace config
{
    void Setting::bind_to_parent()
    {
        hierarchy::bind_child_to_parent<config::Setting*>(this, this->parent_pointer->setting_pointer_vector, this->parent_pointer->free_settingID_queue);
    }

    Setting::Setting(SettingStruct setting_struct)
    {
        // constructor.
        this->name = setting_struct.name;
        this->parent_pointer = setting_struct.parent_pointer;
        this->activate_callback_engine_pointer = setting_struct.activate_callback_engine_pointer;

        // get `childID` from the `SettingMaster` and set pointer to this `Setting`.
        this->bind_to_parent();
    }

    Setting::~Setting()
    {
        // destructor.
    }

    std::string help()
    {
        // this function returns the help string for this setting.
    }
}
