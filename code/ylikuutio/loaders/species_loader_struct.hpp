#ifndef __SPECIES_LOADER_STRUCT_HPP_INCLUDED
#define __SPECIES_LOADER_STRUCT_HPP_INCLUDED

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string

typedef struct SpeciesLoaderStruct
{
    SpeciesLoaderStruct()
        : latitude(NAN),
        longitude(NAN),
        planet_radius(NAN),
        divisor(NAN),
        mesh_i(0),
        x_step(1),
        z_step(1),
        image_width_pointer(nullptr),
        image_height_pointer(nullptr),
        triangulation_type("bilinear_interpolation")
    {
        // constructor.
    }
    std::string model_filename;
    std::string model_file_format;
    double latitude;    // in degrees, for SRTM.
    double longitude;   // in degrees, for SRTM.
    float planet_radius; // for SRTM.
    float divisor;      // for SRTM.
    int32_t mesh_i;     // for FBX.
    std::string color_channel; // for BMP.
    uint32_t x_step;
    uint32_t z_step;
    int32_t* image_width_pointer;
    int32_t* image_height_pointer;
    std::string triangulation_type; // for all.
} SpeciesLoaderStruct;

#endif
