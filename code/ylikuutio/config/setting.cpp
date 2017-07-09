#include "setting.hpp"
#include "setting_master.hpp"
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

    Setting::Setting(const SettingStruct setting_struct)
    {
        // constructor.
        this->name = setting_struct.name;
        this->setting_value = setting_struct.initial_value;
        this->parent_pointer = setting_struct.setting_master_pointer;
        this->activate_callback = setting_struct.activate_callback;
        this->read_callback = setting_struct.read_callback;

        if (this->parent_pointer == nullptr)
        {
            return;
        }

        // get `childID` from the `SettingMaster` and set pointer to this `Setting`.
        this->bind_to_parent();

        this->parent_pointer->setting_pointer_map[this->name] = this;

        if (setting_struct.should_ylikuutio_call_activate_callback_now)
        {
            this->activate_callback(this->parent_pointer->parent_pointer, this->parent_pointer);
        }
    }

    Setting::~Setting()
    {
        // destructor.
    }

    std::string Setting::help()
    {
        // this function returns the help string for this setting.
        std::string help_string = this->name + " TODO: create helptext for " + this->name;
        return help_string;
    }
}
