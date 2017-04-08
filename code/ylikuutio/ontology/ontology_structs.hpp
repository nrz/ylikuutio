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

namespace ontology
{
    class Material;
    class VectorFont;
    class Species;
    class Glyph;
    class Text3D;
}

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
