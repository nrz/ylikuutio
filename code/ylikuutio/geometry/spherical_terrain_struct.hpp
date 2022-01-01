// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2022 Antti Nuortimo.
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

#ifndef __YLIKUUTIO_GEOMETRY_SPHERICAL_TERRAIN_STRUCT_HPP_INCLUDED
#define __YLIKUUTIO_GEOMETRY_SPHERICAL_TERRAIN_STRUCT_HPP_INCLUDED

// Include standard headers
#include <cmath> // NAN, std::isnan, std::pow

namespace yli::geometry
{
    struct SphericalTerrainStruct
    {
        SphericalTerrainStruct()
            : southern_latitude(NAN),
            northern_latitude(NAN),
            western_longitude(NAN),
            eastern_longitude(NAN),
            SRTM_latitude_step_in_degrees(1.0f/1200.0f),
            SRTM_longitude_step_in_degrees(1.0f/1200.0f)
        {
            // constructor.
        }
        float southern_latitude;
        float northern_latitude;
        float western_longitude;
        float eastern_longitude;
        float SRTM_latitude_step_in_degrees;
        float SRTM_longitude_step_in_degrees;
    };
}

#endif
