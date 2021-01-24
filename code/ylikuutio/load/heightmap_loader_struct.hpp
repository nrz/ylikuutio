// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2021 Antti Nuortimo.
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

#ifndef __YLIKUUTIO_LOAD_HEIGHTMAP_LOADER_STRUCT_HPP_INCLUDED
#define __YLIKUUTIO_LOAD_HEIGHTMAP_LOADER_STRUCT_HPP_INCLUDED

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <cstddef>  // std::size_t
#include <string>   // std::string

namespace yli::load
{
    struct HeightmapLoaderStruct
    {
        HeightmapLoaderStruct()
            : latitude(NAN),
            longitude(NAN),
            planet_radius(NAN),
            divisor(NAN),
            x_step(1),
            z_step(1),
            use_real_texture_coordinates(true),
            triangulate(true)
        {
            // constructor.
        }

        std::string filename;
        std::string file_format;
        float latitude;
        float longitude;
        float planet_radius;
        float divisor;
        std::size_t x_step;
        std::size_t z_step;
        std::string triangulation_type;
        bool use_real_texture_coordinates;
        bool triangulate;
    };
}

#endif
