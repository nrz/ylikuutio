#ifndef __TRIANGULATE_QUADS_STRUCT_HPP_INCLUDED
#define __TRIANGULATE_QUADS_STRUCT_HPP_INCLUDED

#include "code/ylikuutio/geometry/spherical_terrain_struct.hpp"

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <cstddef>  // std::size_t
#include <string>   // std::string

namespace yli
{
    namespace geometry
    {
        typedef struct TriangulateQuadsStruct
        {
            TriangulateQuadsStruct()
                : image_width(0), image_height(0), x_step(1), z_step(1), should_ylikuutio_use_real_texture_coordinates(true), sphere_radius(NAN)
            {
                // constructor.
            }
            std::size_t image_width;
            std::size_t image_height;
            std::size_t x_step;
            std::size_t z_step;
            std::string triangulation_type;
            bool should_ylikuutio_use_real_texture_coordinates;
            double sphere_radius;
            yli::geometry::SphericalTerrainStruct spherical_terrain_struct;
        } TriangulateQuadsStruct;
    }
}

#endif
