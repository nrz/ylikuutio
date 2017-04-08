#ifndef __ONTOLOGY_STRUCTS_HPP_INCLUDED
#define __ONTOLOGY_STRUCTS_HPP_INCLUDED

// GLEW must be included here, because `globals.hpp` may be compiled
// first, and if `GL/glew.h` is not included before `glfw3.h` (?),
// then g++ prints the following error:
// `error: #error gl.h included before glew.h`
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include GLFW
#ifndef __GLFW3_H_INCLUDED
#define __GLFW3_H_INCLUDED
#include <glfw3.h>
#endif

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace graph
{
    class Graph;
}

namespace ontology
{
    class Universe;
    class Material;
    class VectorFont;
    class Species;
    class Glyph;
    class Text3D;
}

typedef struct NodeStruct
{
    NodeStruct()
        : parent_pointer(nullptr)
    {
        // constructor.
    }
    uint32_t nodeID;
    graph::Graph* parent_pointer;
    std::vector<uint32_t> neighbor_nodeIDs;
} NodeStruct;

typedef struct ObjectStruct
{
    ObjectStruct()
        : species_parent_pointer(nullptr), glyph_parent_pointer(nullptr), text3D_parent_pointer(nullptr), original_scale_vector(glm::vec3(1.0f, 1.0f, 1.0f)), rotate_angle(NAN), is_character(false)
    {
        // constructor.
    }
    ontology::Species* species_parent_pointer; // pointer to the parent `Species`.
    ontology::Glyph* glyph_parent_pointer;     // pointer to the parent `Glyph`.
    ontology::Text3D* text3D_parent_pointer;   // pointer to the parent `Text3D`.
    glm::vec3 original_scale_vector; // original scale vector.
    float rotate_angle;              // rotate angle.
    bool is_character;               // The parent of a character object is a Glyph. The parent of a regular object is a Species.
    glm::vec3 coordinate_vector;     // coordinate vector.
    glm::vec3 rotate_vector;         // rotate vector.
    glm::vec3 translate_vector;      // translate vector.
} ObjectStruct;

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

#define DEFAULT_VERTEX_SCALING_FACTOR (0.001f)

typedef struct VectorFontStruct
{
    VectorFontStruct()
        : parent_pointer(nullptr), vertex_scaling_factor(DEFAULT_VERTEX_SCALING_FACTOR)
    {
        // constructor.
    }
    // used for all files (for all font).
    ontology::Material* parent_pointer;     // pointer to the material object.
    GLfloat vertex_scaling_factor;
    std::string font_file_format;           // type of the font file. supported file formats so far: `"svg"`/`"SVG"`.
    std::string font_filename;              // filename of the font file.
} VectorFontStruct;

typedef struct Text3DStruct
{
    Text3DStruct()
        : parent_pointer(nullptr), original_scale_vector(glm::vec3(1.0f, 1.0f, 1.0f)), rotate_angle(NAN)
    {
        // constructor.
    }
    ontology::VectorFont* parent_pointer; // pointer to the parent `VectorFont`.
    std::string text_string;
    const char* text_string_char;
    glm::vec3 original_scale_vector;      // original scale vector.
    float rotate_angle;                   // rotate angle.
    glm::vec3 coordinate_vector;          // coordinate vector.
    glm::vec3 rotate_vector;              // rotate vector.
    glm::vec3 translate_vector;           // translate vector.
} Text3DStruct;

typedef struct GlyphStruct
{
    GlyphStruct()
        : parent_pointer(nullptr)
    {
        // constructor.
    }
    // used for all files (for all glyph).
    std::vector<std::vector<glm::vec2>>* glyph_vertex_data;
    const char* glyph_name_pointer;       // we need only a pointer, because glyphs are always created by the `VectorFont` constructor.
    const char* unicode_char_pointer;     // we need only a pointer, because glyphs are always created by the `VectorFont` constructor.
    ontology::VectorFont* parent_pointer; // pointer to the font object.
    glm::vec3 light_position;             // light position.
} GlyphStruct;

#endif
