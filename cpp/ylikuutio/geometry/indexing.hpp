#ifndef __INDEXING_HPP_INCLUDED
#define __INDEXING_HPP_INCLUDED

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include standard headers
#include <stdint.h> // uint32_t etc.

namespace geometry
{
    GLuint get_y(
            GLuint* vertex_data,
            uint32_t x,
            uint32_t z,
            uint32_t image_width);
}

#endif
