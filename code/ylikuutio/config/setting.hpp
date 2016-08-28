#ifndef __SETTING_HPP_INCLUDED
#define __SETTING_HPP_INCLUDED

#include "code/ylikuutio/callback_system/callback_engine.hpp"

// Include standard headers
#include <string>   // std::string

namespace config
{
    class Setting
    {
        public:
            // constructor.
            Setting(std::string name, callback_system::CallbackEngine* activate_callback_engine);

            // destructor.
            ~Setting();

            std::string help();

        private:
            std::string name;

            // The setting value (may be a pointer a some datatype).
            datatypes::AnyValue setting_value;

            // pointer to `CallbackEngine` used to activate the new value after setting it.
            callback_system::CallbackEngine* activate_callback_engine;
    };
}

#endif
