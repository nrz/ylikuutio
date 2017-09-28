#ifndef __SPHERICAL_WORLD_STRUCT_HPP_INCLUDED
#define __SPHERICAL_WORLD_STRUCT_HPP_INCLUDED

namespace geometry
{
    typedef struct SphericalWorldStruct
    {
        SphericalWorldStruct()
            : SRTM_latitude_step_in_degrees(1.0f/1200.0f), SRTM_longitude_step_in_degrees(1.0f/1200.0f)
        {
            // constructor.
        }
        double southern_latitude;
        double northern_latitude;
        double western_longitude;
        double eastern_longitude;
        double SRTM_latitude_step_in_degrees;
        double SRTM_longitude_step_in_degrees;
    } SphericalWorldStruct;
}

#endif
