#ifndef __TRANSFORMATION_STRUCT_HPP_INCLUDED
#define __TRANSFORMATION_STRUCT_HPP_INCLUDED

#include "spherical_terrain_struct.hpp"

// Include standard headers
#include <cstddef>       // std::size_t

namespace yli
{
    namespace geometry
    {
        typedef struct
        {
            std::size_t image_width;
            std::size_t image_height;
            double sphere_radius;
            bool is_bilinear_interpolation_in_use;
            yli::geometry::SphericalTerrainStruct spherical_terrain_struct;
        } TransformationStruct;
    }
}

#endif
