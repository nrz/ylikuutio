#include "setting.hpp"
#include "code/ylikuutio/callback_system/callback_engine.hpp"

// Include standard headers
#include <string>   // std::string

namespace config
{
    Setting::Setting(std::string name, callback_system::CallbackEngine* activate_callback_engine)
    {
        // constructor.
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
