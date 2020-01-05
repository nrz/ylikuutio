// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef __APP_LOCATION_AND_ORIENTATION_HPP_INCLUDED
#define __APP_LOCATION_AND_ORIENTATION_HPP_INCLUDED

namespace yli
{
    namespace config
    {
        class SettingMaster;
    }
}

namespace app
{
    void set_location_and_orientation(
            yli::config::SettingMaster* const setting_master,
            const float rho,
            const float theta,
            const float phi,
            const float x,
            const float y,
            const float z);
}

#endif
