#ifndef __AJOKKI_CONSOLE_HPP_INCLUDED
#define __AJOKKI_CONSOLE_HPP_INCLUDED

namespace ylikuutio
{
    namespace config
    {
        class SettingMaster;
    }
}

namespace ajokki
{
    void set_console(ylikuutio::config::SettingMaster* const setting_master);
}

#endif
