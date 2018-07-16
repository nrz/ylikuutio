#include "setting.hpp"
#include "setting_master.hpp"
#include "setting_struct.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <limits>   // std::numeric_limits
#include <string>   // std::string

namespace yli
{
    namespace config
    {
        void Setting::bind_to_parent()
        {
            yli::hierarchy::bind_child_to_parent<yli::config::Setting*>(this, this->parent->setting_pointer_vector, this->parent->free_settingID_queue, &this->parent->number_of_settings);
        }

        Setting::Setting(const SettingStruct& setting_struct)
        {
            // constructor.
            this->name = setting_struct.name;
            this->setting_value = setting_struct.initial_value;
            this->parent = setting_struct.setting_master;
            this->activate_callback = setting_struct.activate_callback;
            this->read_callback = setting_struct.read_callback;
            this->childID = std::numeric_limits<std::size_t>::max();

            if (this->parent == nullptr)
            {
                return;
            }

            // get `childID` from the `SettingMaster` and set pointer to this `Setting`.
            this->bind_to_parent();

            this->parent->setting_pointer_map[this->name] = this;

            if (setting_struct.should_ylikuutio_call_activate_callback_now)
            {
                this->activate_callback(this->parent->parent, this->parent);
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
}
