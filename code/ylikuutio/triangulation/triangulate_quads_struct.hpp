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

#ifndef __YLIKUUTIO_TRIANGULATION_TRIANGULATE_QUADS_STRUCT_HPP_INCLUDED
#define __YLIKUUTIO_TRIANGULATION_TRIANGULATE_QUADS_STRUCT_HPP_INCLUDED

#include "code/ylikuutio/geometry/spherical_terrain_struct.hpp"

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <cstddef>  // std::size_t
#include <string>   // std::string

namespace yli::triangulation
{
    struct TriangulateQuadsStruct
    {
        TriangulateQuadsStruct()
            : image_width(0),
            image_height(0),
            x_step(1),
            z_step(1),
            use_real_texture_coordinates(true),
            sphere_radius(NAN),
            spherical_terrain_struct(yli::geometry::SphericalTerrainStruct())
        {
            // constructor.
        }
        std::size_t image_width;
        std::size_t image_height;
        std::size_t x_step;
        std::size_t z_step;
        std::string triangulation_type;
        bool use_real_texture_coordinates;
        float sphere_radius;
        yli::geometry::SphericalTerrainStruct spherical_terrain_struct;
    };
}

#endif
