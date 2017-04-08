#ifndef __SPECIES_STRUCT_HPP_INCLUDED
#define __SPECIES_STRUCT_HPP_INCLUDED

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <string>   // std::string

namespace ontology
{
    class Material;
}

typedef struct SpeciesStruct
{
    SpeciesStruct()
        : parent_pointer(nullptr), is_world(false), world_radius(NAN), divisor(1.0f), triangulation_type("bilinear_interpolation")
    {
        // constructor.
    }
    // used for all files (for all species).
    ontology::Material* parent_pointer;      // pointer to the material object.
    bool is_world;                           // worlds currently do not rotate nor translate.
    float world_radius;                      // radius of sea level in kilometers. used only for worlds.
    float divisor;                           // value by which SRTM values are divided to convert them to kilometers.
    std::string model_file_format;           // type of the model file. supported file formats so far: `"bmp"`/`"BMP"`, `"obj"`/`"OBJ"`.
                                             // TODO: add support for `"SRTM"`.
    std::string model_filename;              // filename of the model file.
    // for `"bmp"` model files.
    std::string color_channel;               // color channel to use for altitude data.

    glm::vec3 light_position;                // light position.
    std::string coordinate_system;           // used only for worlds (`is_world` == `true`). valid values: `"cartesian"`.
                                             // TODO: add support for `"spherical"`. `"spherical"` is used eg. in SRTM heightmaps.
    std::string triangulation_type;
} SpeciesStruct;

#endif
