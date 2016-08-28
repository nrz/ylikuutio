#ifndef __SETTING_MASTER_HPP_INCLUDED
#define __SETTING_MASTER_HPP_INCLUDED

// Include standard headers
#include <string>        // std::string
#include <unordered_map> // std::unordered_map

namespace config
{
    class Setting;

    class SettingMaster
    {
        public:
            // constructor.
            SettingMaster();

            // destructor.
            ~SettingMaster();

            // does setting `setting` exist?
            bool is_setting(std::string setting);

            // this function returns help string for setting `setting`.
            std::string help(std::string setting);

        private:
            std::unordered_map<std::string, config::Setting*> setting_pointer_map;
    };
}

#endif
