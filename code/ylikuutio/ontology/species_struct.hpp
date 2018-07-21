#ifndef __SPECIES_STRUCT_HPP_INCLUDED
#define __SPECIES_STRUCT_HPP_INCLUDED

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <limits>   // std::numeric_limits
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli
{
    namespace ontology
    {
        class Scene;
        class Shader;
        class Material;
        class SymbiontMaterial;
    }
}

typedef struct SpeciesStruct
{
    SpeciesStruct()
        : scene(nullptr),
        shader(nullptr),
        material(nullptr),
        symbiont_material(nullptr),
        is_terrain(false),
        planet_radius(NAN),
        divisor(1.0f),
        water_level(-1.0f * std::numeric_limits<float>::infinity()),
        is_symbiont_species(false),
        vertex_count(std::numeric_limits<std::size_t>::max()),
        light_position(glm::vec3(0.0f, 0.0f, 0.0f)),
        latitude(0.0f),
        longitude(0.0f),
        mesh_i(0),
        x_step(1),
        z_step(1),
        triangulation_type("bilinear_interpolation")
    {
        // constructor.
    }
    // used for all files (for all species).
    yli::ontology::Scene* scene;                        // pointer to `Scene` object.
    yli::ontology::Shader* shader;                      // pointer to `Shader` object.
    yli::ontology::Material* material;                  // pointer to `Material` object.
    yli::ontology::SymbiontMaterial* symbiont_material; // pointer to `SymbiontMaterial` object.
    bool is_terrain;                           // worlds currently neither rotate nor translate.
    float planet_radius;                      // radius of sea level in kilometers. used only for worlds.
    float divisor;                           // value by which SRTM values are divided to convert them to kilometers.
    float water_level;                       // water level in meters.
    std::string model_file_format;           // type of the model file. supported file formats so far: `"bmp"`/`"BMP"`, `"obj"`/`"OBJ"`.
    // TODO: add support for `"SRTM"`.
    std::string model_filename;              // filename of the model file.
    std::string color_channel;               // color channel to use for altitude data, for BMP model files.
    bool is_symbiont_species;
    std::size_t vertex_count;                // For `SymbiontSpecies`.
    std::vector<glm::vec3> vertices;         // For `SymbiontSpecies`.
    std::vector<glm::vec2> uvs;              // For `SymbiontSpecies`.
    std::vector<glm::vec3> normals;          // For `SymbiontSpecies`.
    glm::vec3 light_position;                // light position.
    double latitude;                         // in degrees, for SRTM model files.
    double longitude;                        // in degrees, for SRTM model files.
    std::size_t mesh_i;                      // for FBX.
    std::size_t x_step;                      // Step in x-dimension for input data (set to 1 to load all data points/measurements).
    std::size_t z_step;                      // Step in z-dimension for input data (set to 1 to load all data points/measurements).
    std::string triangulation_type;          // `"bilinear_interpolation"`, `"southwest_northeast_edges"`, `"southeast_northwest_edges"`.
} SpeciesStruct;

#endif
