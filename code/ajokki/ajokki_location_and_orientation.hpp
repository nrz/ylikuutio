#ifndef __AJOKKI_LOCATION_AND_ORIENTATION_HPP_INCLUDED
#define __AJOKKI_LOCATION_AND_ORIENTATION_HPP_INCLUDED

namespace ylikuutio
{
    namespace config
    {
        class SettingMaster;
    }
}

namespace ajokki
{
    void set_location_and_orientation(ylikuutio::config::SettingMaster* const setting_master);
}

#endif
