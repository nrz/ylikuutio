#ifndef __AJOKKI_DEBUG_HPP_INCLUDED
#define __AJOKKI_DEBUG_HPP_INCLUDED

namespace yli
{
    namespace config
    {
        class SettingMaster;
    }
}

namespace ajokki
{
    void set_debug_variables(yli::config::SettingMaster* setting_master);
}

#endif
