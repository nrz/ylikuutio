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

#ifndef __TRANSFORMATION_STRUCT_HPP_INCLUDED
#define __TRANSFORMATION_STRUCT_HPP_INCLUDED

#include "spherical_terrain_struct.hpp"

// Include standard headers
#include <cstddef>       // std::size_t

namespace yli::geometry
{
    struct TransformationStruct
    {
        std::size_t image_width;
        std::size_t image_height;
        double sphere_radius;
        bool is_bilinear_interpolation_in_use;
        yli::geometry::SphericalTerrainStruct spherical_terrain_struct;
    };
}

#endif
