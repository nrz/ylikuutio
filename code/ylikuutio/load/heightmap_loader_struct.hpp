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
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string

namespace yli::load
{
    struct HeightmapLoaderStruct
    {
        std::string filename;
        std::string file_format;
        float latitude      { NAN };
        float longitude     { NAN };
        float planet_radius { NAN };
        float divisor       { NAN };
        uint32_t x_step     { 1 };
        uint32_t z_step     { 1 };
        std::string triangulation_type;
        bool use_real_texture_coordinates { true };
        bool triangulate                  { true };
    };
}

#endif
