#ifndef __MODEL_COMMON_FUNCTIONS_HPP_INCLUDED
#define __MODEL_COMMON_FUNCTIONS_HPP_INCLUDED

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
#include <vector>    // std::vector
#include <queue>     // std::queue

namespace model
{
    void set_child_pointer(GLuint childID, void* child_pointer, std::vector<void*> &child_pointer_vector, std::queue<GLuint> &free_childID_queue);
    GLuint get_childID(std::vector<void*> &child_pointer_vector, std::queue<GLuint> &free_childID_queue);
}

#endif
