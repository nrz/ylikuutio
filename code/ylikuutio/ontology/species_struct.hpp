#ifndef __SPECIES_STRUCT_HPP_INCLUDED
#define __SPECIES_STRUCT_HPP_INCLUDED

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <limits>   // std::numeric_limits
#include <string>   // std::string

namespace ontology
{
    class Material;
}

typedef struct SpeciesStruct
{
    SpeciesStruct()
        : parent_pointer(nullptr), is_world(false), world_radius(NAN), divisor(1.0f), water_level(-1.0f * std::numeric_limits<float>::infinity()), light_position(glm::vec3(0.0f, 0.0f, 0.0f)), latitude(0.0f), longitude(0.0f), x_step(1), z_step(1), triangulation_type("bilinear_interpolation")
    {
        // constructor.
    }
    // used for all files (for all species).
    ontology::Material* parent_pointer;      // pointer to `Material` object.
    bool is_world;                           // worlds currently neither rotate nor translate.
    float world_radius;                      // radius of sea level in kilometers. used only for worlds.
    float divisor;                           // value by which SRTM values are divided to convert them to kilometers.
    float water_level;                       // water level in meters.
    std::string model_file_format;           // type of the model file. supported file formats so far: `"bmp"`/`"BMP"`, `"obj"`/`"OBJ"`.
                                             // TODO: add support for `"SRTM"`.
    std::string model_filename;              // filename of the model file.
    std::string color_channel;               // color channel to use for altitude data, for BMP model files.
    glm::vec3 light_position;                // light position.
    double latitude;                         // in degrees, for SRTM model files.
    double longitude;                        // in degrees, for SRTM model files.
    uint32_t x_step;                         // Step in x-dimension for input data (set to 1 to load all data points/measurements).
    uint32_t z_step;                         // Step in z-dimension for input data (set to 1 to load all data points/measurements).
    std::string triangulation_type;          // `"bilinear_interpolation"`, `"southwest_northeast_edges"`, `"southeast_northwest_edges"`.
} SpeciesStruct;

#endif
