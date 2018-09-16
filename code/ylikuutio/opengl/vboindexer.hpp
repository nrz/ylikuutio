#ifndef __VBOINDEXER_HPP_INCLUDED
#define __VBOINDEXER_HPP_INCLUDED

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <vector>    // std::vector

namespace yli
{
    namespace opengl
    {
        void indexVBO(
                const std::vector<glm::vec3>& in_vertices,
                const std::vector<glm::vec2>& in_uvs,
                const std::vector<glm::vec3>& in_normals,
                std::vector<GLuint>& out_indices,
                std::vector<glm::vec3>& out_vertices,
                std::vector<glm::vec2>& out_uvs,
                std::vector<glm::vec3>& out_normals
                );
    }
}

#endif
