#ifndef __SETTING_MASTER_HPP_INCLUDED
#define __SETTING_MASTER_HPP_INCLUDED

// Include standard headers
#include <queue>         // std::queue
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

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

            friend class Setting;

        private:
            std::vector<config::Setting*> setting_pointer_vector;
            std::queue<uint32_t> free_settingID_queue;

            std::unordered_map<std::string, config::Setting*> setting_pointer_map;
    };
}

#endif
