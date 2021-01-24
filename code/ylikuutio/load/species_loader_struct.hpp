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

#ifndef __YLIKUUTIO_LOAD_SPECIES_LOADER_STRUCT_HPP_INCLUDED
#define __YLIKUUTIO_LOAD_SPECIES_LOADER_STRUCT_HPP_INCLUDED

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <cstddef>  // std::size_t
#include <string>   // std::string

namespace yli::load
{
    struct SpeciesLoaderStruct
    {
        SpeciesLoaderStruct()
            : triangulation_type("bilinear_interpolation"),
            mesh_i(0),
            x_step(1),
            z_step(1),
            image_width_pointer(nullptr),
            image_height_pointer(nullptr),
            latitude(NAN),
            longitude(NAN),
            planet_radius(NAN),
            divisor(NAN),
            is_headless(false),
            opengl_in_use(true),
            use_real_texture_coordinates(true)
        {
            // constructor.
        }
        std::string model_filename;
        std::string model_file_format;
        std::string color_channel;      // for BMP.
        std::string triangulation_type; // for all.
        std::size_t mesh_i;             // for FBX.
        std::size_t x_step;
        std::size_t z_step;
        std::size_t* image_width_pointer;
        std::size_t* image_height_pointer;
        float latitude;                 // in degrees, for SRTM.
        float longitude;                // in degrees, for SRTM.
        float planet_radius;            // for SRTM. can be a planet or a moon.
        float divisor;                  // for SRTM.
        bool is_headless;
        bool opengl_in_use;
        bool use_real_texture_coordinates;
    };
}

#endif
