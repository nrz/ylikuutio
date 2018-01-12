#include "gl_attrib_locations.hpp"
#include "shader.hpp"
#include "glyph.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

namespace ontology
{
    void get_gl_attrib_locations(ontology::Shader* shader, ontology::Glyph* glyph)
    {
        glyph->vertexPosition_modelspaceID = glGetAttribLocation(shader->get_programID(), "vertexPosition_modelspace");
        glyph->vertexUVID = glGetAttribLocation(shader->get_programID(), "vertexUV");
        glyph->vertexNormal_modelspaceID = glGetAttribLocation(shader->get_programID(), "vertexNormal_modelspace");
    }
}
