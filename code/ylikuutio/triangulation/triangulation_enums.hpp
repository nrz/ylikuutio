// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2019 Antti Nuortimo.
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

#ifndef __TRIANGULATION_ENUMS_HPP_INCLUDED
#define __TRIANGULATION_ENUMS_HPP_INCLUDED

namespace yli
{
    namespace geometry
    {
        // for bilinear interpolation.
        enum BilinearDirections { SSW, WSW, WNW, NNW, NNE, ENE, ESE, SSE };

        // for southeast-northwest edges.
        enum SoutheastNorthwestEdgesDirections { SSE_CODE_FOR_SE_NW, WNW_CODE_FOR_SE_NW, ESE_CODE_FOR_SE_NW, NNW_CODE_FOR_SE_NW, SW_CODE_FOR_SE_NW, NE_CODE_FOR_SE_NW };

        // for southeast-northwest edges.
        enum SouthwestNortheastEdgesDirections { SSW_CODE_FOR_SW_NE, ENE_CODE_FOR_SW_NE, WSW_CODE_FOR_SW_NE, NNE_CODE_FOR_SW_NE, SE_CODE_FOR_SW_NE, NW_CODE_FOR_SW_NE };
    }
}

#endif
