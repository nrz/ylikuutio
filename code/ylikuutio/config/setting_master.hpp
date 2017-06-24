#ifndef __SETTING_MASTER_HPP_INCLUDED
#define __SETTING_MASTER_HPP_INCLUDED

#include "code/ylikuutio/console/console.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/common/any_value.hpp"

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
            SettingMaster(ontology::Universe* universe_pointer);

            // destructor.
            ~SettingMaster();

            // does setting `setting` exist?
            bool is_setting(const std::string setting_name);

            // this function returns general help.
            std::string help();

            // this function returns help string for setting `setting`.
            std::string help(const std::string setting_name);

            // Public callbacks.

            static datatypes::AnyValue* set(
                    console::Console* console,
                    ontology::Universe* universe,
                    std::vector<std::string>& command_parameters);

            static datatypes::AnyValue* get(
                    console::Console* console,
                    ontology::Universe* universe,
                    std::vector<std::string>& command_parameters);

            static datatypes::AnyValue* activate_world_radius(ontology::Universe* universe, config::SettingMaster* setting_master);

            static datatypes::AnyValue* activate_background_color(ontology::Universe* universe, config::SettingMaster* setting_master);

            // Public callbacks end here.

            friend class Setting;
            friend class ontology::Universe;
            friend class console::Console;

        private:
            ontology::Universe* parent_pointer;

            std::vector<config::Setting*> setting_pointer_vector;
            std::queue<uint32_t> free_settingID_queue;

            std::unordered_map<std::string, config::Setting*> setting_pointer_map;
    };
}

#endif
