#ifndef __SETTING_HPP_INCLUDED
#define __SETTING_HPP_INCLUDED

#include "setting_struct.hpp"
#include "activate_callback.hpp"
#include "read_callback.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <memory>   // std::make_shared, std::shared_ptr
#include <queue>    // std::queue
#include <string>   // std::string

namespace yli
{
    namespace console
    {
        class Console;
    }

    namespace config
    {
        class SettingMaster;

        class Setting
        {
            public:
                // constructor.
                Setting(const SettingStruct& setting_struct);

                // destructor.
                ~Setting();

                std::string help();

                friend SettingMaster;
                friend yli::console::Console;

                template<class T1>
                    friend void yli::hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue, std::size_t& number_of_children);

            private:
                void bind_to_parent();

                std::string name;

                // The setting value (may be a pointer a some datatype).
                std::shared_ptr<yli::datatypes::AnyValue> setting_value;

                // pointer to `ActivateCallback` used to activate the new value after setting it.
                ActivateCallback activate_callback;

                // pointer to `ReadCallback` used to read the value. Leave to `nullptr` to read the value from `setting_value` of `class Setting`.
                ReadCallback read_callback;

                yli::config::SettingMaster* parent; // pointer to `SettingMaster`.

                std::size_t childID;                // setting ID, returned by `yli::config::SettingMaster->get_settingID()`.
        };
    }
}

#endif
