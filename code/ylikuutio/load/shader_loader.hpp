#ifndef __SHADER_LOADER_HPP_INCLUDED
#define __SHADER_LOADER_HPP_INCLUDED

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

namespace yli
{
    namespace load
    {
        GLuint load_shaders(const char* const vertex_file_path, const char* const fragment_file_path);
    }
}

#endif
