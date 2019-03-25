#ifndef __SPECIES_STRUCT_HPP_INCLUDED
#define __SPECIES_STRUCT_HPP_INCLUDED

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
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
        : triangulation_type("bilinear_interpolation"),
        light_position(glm::vec3(0.0f, 0.0f, 0.0f)),
        scene(nullptr),
        shader(nullptr),
        material(nullptr),
        symbiont_material(nullptr),
        vertex_count(std::numeric_limits<std::size_t>::max()), // `std::numeric_limits<std::size_t>::max()` means that `vertex_count` is not defined.
        mesh_i(0),
        x_step(1),
        z_step(1),
        latitude(0.0f),
        longitude(0.0f),
        planet_radius(NAN),
        divisor(1.0f),
        water_level(-1.0f * std::numeric_limits<float>::infinity()),
        is_terrain(false),
        is_symbiont_species(false),
        vram_buffer_in_use(true),
        should_ylikuutio_use_real_texture_coordinates(true)
    {
        // constructor.
    }

    std::string model_filename;                         // filename of the model file.
    std::string model_file_format;                      // type of the model file. supported file formats so far: `"bmp"`/`"BMP"`, `"obj"`/`"OBJ"`.
    std::string color_channel;                          // color channel to use for altitude data, for BMP model files.
    std::string triangulation_type;                     // `"bilinear_interpolation"`, `"southwest_northeast_edges"`, `"southeast_northwest_edges"`.
    std::vector<glm::vec3> vertices;                    // for `SymbiontSpecies`.
    std::vector<glm::vec2> uvs;                         // for `SymbiontSpecies`.
    std::vector<glm::vec3> normals;                     // for `SymbiontSpecies`.
    glm::vec3 light_position;                           // light position.
    yli::ontology::Scene* scene;                        // pointer to `Scene` object.
    yli::ontology::Shader* shader;                      // pointer to `Shader` object.
    yli::ontology::Material* material;                  // pointer to `Material` object.
    yli::ontology::SymbiontMaterial* symbiont_material; // pointer to `SymbiontMaterial` object.
    std::size_t vertex_count;                           // for `SymbiontSpecies`.
    std::size_t mesh_i;                                 // for FBX.
    std::size_t x_step;                                 // step in x-dimension for input data (set to 1 to load all data points/measurements).
    std::size_t z_step;                                 // step in z-dimension for input data (set to 1 to load all data points/measurements).
    double latitude;                                    // in degrees, for SRTM model files.
    double longitude;                                   // in degrees, for SRTM model files.
    float planet_radius;                                // radius of sea level in kilometers. used only for terrains (planets and moons).
    float divisor;                                      // value by which SRTM values are divided to convert them to kilometers.
    float water_level;                                  // water level in meters. used only for terrains (planets and moons).
    bool is_terrain;                                    // Terrains (planets and moons) currently neither rotate nor translate.
    bool is_symbiont_species;
    bool vram_buffer_in_use;
    bool should_ylikuutio_use_real_texture_coordinates;
} SpeciesStruct;

#endif
