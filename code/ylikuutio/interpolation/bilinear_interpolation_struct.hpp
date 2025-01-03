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

#ifndef YLIKUUTIO_INTERPOLATION_BILINEAR_INTERPOLATION_STRUCT_HPP_INCLUDED
#define YLIKUUTIO_INTERPOLATION_BILINEAR_INTERPOLATION_STRUCT_HPP_INCLUDED

// Include standard headers
#include <cstddef>  // std::size_t

namespace yli::interpolation
{
    struct BilinearInterpolationStruct
    {
        BilinearInterpolationStruct()
            : input_image_width(0),
            input_image_height(0),
            output_image_width(0),
            output_image_height(0)
        {
        }

        std::size_t input_image_width;
        std::size_t input_image_height;
        std::size_t output_image_width;
        std::size_t output_image_height;
    };
}

#endif
