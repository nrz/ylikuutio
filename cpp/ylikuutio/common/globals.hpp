#ifndef __GLOBALS_HPP_INCLUDED
#define __GLOBALS_HPP_INCLUDED

#include "any_value.hpp"

// GCC (at least g++ 4.7.2) and Visual Studio 2015 do support
// setting default values of a struct using C++11 syntax.
// Clang 3.7.0 and Visual Studio 2013 do not support
// setting default values of a struct using C++11 syntax.
// Visual Studio 2013 fails to compile, whereas Clang-compiled
// executable with code with setting default values of a struct
// causes Segmentation fault upon execution of the program.
// Compilers that don't support setting default values of a struct
// are handled by setting the default values in a macro.
// http://stackoverflow.com/questions/16782103/initializing-default-values-in-a-struct/16783513#16783513
#ifdef __clang__
#elif defined(__GNUC__)
#define __STRUCT_DEFAULT_VALUES_ARE_ACCEPTED
#elif defined(_WIN32)
#if (_MSC_VER >= 1900)
#define __STRUCT_DEFAULT_VALUES_ARE_ACCEPTED
#endif
#endif

// Include GLEW
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

#ifndef PI
#define PI 3.14159265359f
#endif

#ifndef EARTH_RADIUS
#define EARTH_RADIUS 6371000.0f
#endif

namespace ontology
{
    class Universe;
    class Scene;
    class Shader;
    class Graph;
    class Material;
    class VectorFont;
    class Species;
    class Glyph;
    class Text3D;
}

typedef struct ShaderStruct
{
    ShaderStruct()
        : parent_pointer(nullptr)
    {
        // constructor.
    }
    ontology::Scene* parent_pointer; // pointer to the scene (draw list).
    std::string vertex_shader;    // filename of vertex shader.
    std::string fragment_shader;  // filename of fragment shader.
} ShaderStruct;

typedef struct MaterialStruct
{
    MaterialStruct()
        : parent_pointer(nullptr)
    {
        // constructor.
    }
    ontology::Shader* parent_pointer;   // pointer to the shader.
    std::string texture_file_format; // type of the texture file. supported file formats so far: `"bmp"`/`"BMP"`, `"dds"`/`"DDS"`.
    std::string texture_filename;    // filename of the model file.
    std::string image_path;
} MaterialStruct;

typedef struct NodeStruct
{
    NodeStruct()
        : parent_pointer(nullptr)
    {
        // constructor.
    }
    GLuint nodeID;
    ontology::Graph* parent_pointer;
    glm::vec3 coordinate_vector;
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
    GLfloat rotate_angle;            // rotate angle.
    bool is_character;               // The parent of a character object is a Glyph. The parent of a regular object is a Species.
    glm::vec3 coordinate_vector;     // coordinate vector.
    glm::vec3 rotate_vector;         // rotate vector.
    glm::vec3 translate_vector;      // translate vector.
} ObjectStruct;

typedef struct SpeciesStruct
{
    SpeciesStruct()
        : parent_pointer(nullptr), is_world(false), world_radius(NAN), triangulation_type("bilinear_interpolation")
    {
        // constructor.
    }
    // used for all files (for all species).
    ontology::Material* parent_pointer;         // pointer to the material object.
    bool is_world;                           // worlds currently do not rotate nor translate.
    double world_radius;                     // radius of sea level in meters. used only for worlds.
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
    ontology::Material* parent_pointer;        // pointer to the material object.
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
    glm::vec3 original_scale_vector;   // original scale vector.
    GLfloat rotate_angle;              // rotate angle.
    glm::vec3 coordinate_vector;       // coordinate vector.
    glm::vec3 rotate_vector;           // rotate vector.
    glm::vec3 translate_vector;        // translate vector.
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
    const char* glyph_name_pointer;          // we need only a pointer, because glyphs are always created by the `VectorFont` constructor.
    const char* unicode_char_pointer;      // we need only a pointer, because glyphs are always created by the `VectorFont` constructor.
    ontology::VectorFont* parent_pointer;       // pointer to the font object.
    glm::vec3 light_position;                // light position.
} GlyphStruct;

typedef struct
{
    GLuint screen_width;
    GLuint screen_height;
    GLuint x;
    GLuint y;
    GLuint text_size;
    GLuint font_size;
    std::string text;
    const char* text_char;
    const char* char_font_texture_file_format;
    const char* horizontal_alignment;
    const char* vertical_alignment;
} PrintingStruct;

typedef struct
{
    double rho;
    double theta;
    double phi;
} SphericalCoordinatesStruct;

typedef struct SphericalWorldStruct
{
    SphericalWorldStruct()
        :SRTM_latitude_step_in_degrees(1.0f/1200.0f), SRTM_longitude_step_in_degrees(1.0f/1200.0f)
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

typedef struct TriangulateQuadsStruct
{
    TriangulateQuadsStruct()
        : should_ylikuutio_use_real_texture_coordinates(true)
    {
        // constructor.
    }
    GLuint* input_vertex_pointer;
    uint32_t image_width;
    uint32_t image_height;
    std::string triangulation_type;
    bool should_ylikuutio_use_real_texture_coordinates;
    double sphere_radius;
    SphericalWorldStruct spherical_world_struct;
} TriangulateQuadsStruct;

typedef struct TriangulatePolygonsStruct
{
    TriangulatePolygonsStruct()
        : should_ylikuutio_use_real_texture_coordinates(true)
    {
        // constructor.
    }
    std::vector<std::vector<glm::vec2>>* input_vertices;
    bool should_ylikuutio_use_real_texture_coordinates;
} TriangulatePolygonsStruct;

typedef struct
{
    uint32_t* input_vertex_pointer;
    uint32_t image_width;
    uint32_t image_height;
    bool should_ylikuutio_use_real_texture_coordinates;
} BilinearInterpolationStruct;

typedef struct
{
    uint32_t image_width;
    uint32_t image_height;
    double sphere_radius;
    bool is_bilinear_interpolation_in_use;
    SphericalWorldStruct spherical_world_struct;
} TransformationStruct;

namespace callback_system
{
    class CallbackEngine;
    class CallbackObject;
    class CallbackParameter;
}
typedef datatypes::AnyValue* (*InputParametersToAnyValueCallback) (
        callback_system::CallbackEngine*,
        callback_system::CallbackObject*,
        std::vector<callback_system::CallbackParameter*>);

namespace console
{
    class Console;
}
typedef datatypes::AnyValue* (*InputParametersToAnyValueCallbackWithConsole) (
        callback_system::CallbackEngine*,
        callback_system::CallbackObject*,
        std::vector<callback_system::CallbackParameter*>&,
        console::Console*);
#endif
