#ifndef __AJOKKI_CONSOLE_HPP_INCLUDED
#define __AJOKKI_CONSOLE_HPP_INCLUDED

namespace yli
{
    namespace config
    {
        class SettingMaster;
    }
}

namespace ajokki
{
    void set_console(yli::config::SettingMaster* const setting_master);
}

#endif
