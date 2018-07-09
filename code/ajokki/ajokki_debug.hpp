#ifndef __AJOKKI_DEBUG_HPP_INCLUDED
#define __AJOKKI_DEBUG_HPP_INCLUDED

namespace ylikuutio
{
    namespace config
    {
        class SettingMaster;
    }
}

namespace ajokki
{
    void set_debug_variables(ylikuutio::config::SettingMaster* setting_master);
}

#endif
