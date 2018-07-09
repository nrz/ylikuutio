#ifndef __SPHERICAL_WORLD_STRUCT_HPP_INCLUDED
#define __SPHERICAL_WORLD_STRUCT_HPP_INCLUDED

// Include standard headers
#include <cmath> // NAN, std::isnan, std::pow

namespace yli
{
    namespace geometry
    {
        typedef struct SphericalTerrainStruct
        {
            SphericalTerrainStruct()
                : southern_latitude(NAN), northern_latitude(NAN), western_longitude(NAN), eastern_longitude(NAN), SRTM_latitude_step_in_degrees(1.0f/1200.0f), SRTM_longitude_step_in_degrees(1.0f/1200.0f)
            {
                // constructor.
            }
            double southern_latitude;
            double northern_latitude;
            double western_longitude;
            double eastern_longitude;
            double SRTM_latitude_step_in_degrees;
            double SRTM_longitude_step_in_degrees;
        } SphericalTerrainStruct;
    }
}

#endif
