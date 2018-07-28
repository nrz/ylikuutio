#ifndef __VECTOR_FONT_STRUCT_HPP_INCLUDED
#define __VECTOR_FONT_STRUCT_HPP_INCLUDED

#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include standard headers
#include <string>   // std::string

#define DEFAULT_VERTEX_SCALING_FACTOR (0.001f)

namespace yli
{
    namespace ontology
    {
        class Material;
    }
}

typedef struct VectorFontStruct
{
    VectorFontStruct()
        : parent(nullptr), vertex_scaling_factor(DEFAULT_VERTEX_SCALING_FACTOR)
    {
        // constructor.
    }
    // used for all files (for all font).
    yli::ontology::Material* parent;     // pointer to the material object.
    GLfloat vertex_scaling_factor;
    std::string font_file_format;           // type of the font file. supported file formats so far: `"svg"`/`"SVG"`.
    std::string font_filename;              // filename of the font file.
} VectorFontStruct;

#endif
