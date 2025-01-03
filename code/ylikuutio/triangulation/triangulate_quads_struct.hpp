// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2025 Antti Nuortimo.
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

#ifndef YLIKUUTIO_TRIANGULATION_TRIANGULATE_QUADS_STRUCT_HPP_INCLUDED
#define YLIKUUTIO_TRIANGULATION_TRIANGULATE_QUADS_STRUCT_HPP_INCLUDED

// Include standard headers
#include <cstddef>  // std::size_t

namespace yli::triangulation
{
    struct TriangulateQuadsStruct
    {
        TriangulateQuadsStruct()
            : image_width(0),
            image_height(0),
            x_step(1),
            y_step(1),
            use_real_texture_coordinates(true)
        {
        }
        std::size_t image_width;
        std::size_t image_height;
        std::size_t x_step;
        std::size_t y_step;
        bool use_real_texture_coordinates;
    };
}

#endif
