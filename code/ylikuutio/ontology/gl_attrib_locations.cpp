#include "gl_attrib_locations.hpp"
#include "shader.hpp"
#include "glyph.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

namespace yli
{
    namespace ontology
    {
        void store_gl_attrib_locations(yli::ontology::Shader* const shader, yli::ontology::Glyph* const glyph)
        {
            glyph->store_vertex_position_modelspaceID(glGetAttribLocation(shader->get_programID(), "vertexPosition_modelspace"));
            glyph->store_vertexUVID(glGetAttribLocation(shader->get_programID(), "vertexUV"));
            glyph->store_vertex_normal_modelspaceID(glGetAttribLocation(shader->get_programID(), "vertexNormal_modelspace"));
        }
    }
}
