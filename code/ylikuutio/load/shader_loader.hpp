#ifndef __SHADER_LOADER_HPP_INCLUDED
#define __SHADER_LOADER_HPP_INCLUDED

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

namespace yli
{
    namespace load
    {
        GLuint load_shaders(const char* const vertex_file_path, const char* const fragment_file_path);
    }
}

#endif
