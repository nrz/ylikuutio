#ifndef __HEIGHTMAP_LOADER_STRUCT_HPP_INCLUDED
#define __HEIGHTMAP_LOADER_STRUCT_HPP_INCLUDED

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <cstddef>  // std::size_t

typedef struct HeightmapLoaderStruct
{
    HeightmapLoaderStruct()
        : latitude(NAN),
        longitude(NAN),
        planet_radius(NAN),
        divisor(NAN)
    {
        // constructor.
    }

    float latitude;
    float longitude;
    float planet_radius;
    float divisor;
} HeightmapLoaderStruct;

#endif
