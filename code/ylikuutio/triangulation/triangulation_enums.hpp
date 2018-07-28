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
