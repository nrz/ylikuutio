#ifndef __TRANSFORMATION_STRUCT_HPP_INCLUDED
#define __TRANSFORMATION_STRUCT_HPP_INCLUDED

#include "spherical_terrain_struct.hpp"

// Include standard headers
#include <stdint.h>      // uint32_t etc.

namespace geometry
{
    typedef struct
    {
        uint32_t image_width;
        uint32_t image_height;
        double sphere_radius;
        bool is_bilinear_interpolation_in_use;
        geometry::SphericalTerrainStruct spherical_terrain_struct;
    } TransformationStruct;
}

#endif
