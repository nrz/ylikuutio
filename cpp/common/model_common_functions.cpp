#include "model_common_functions.hpp"
#include "species.hpp"

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
#include <cmath>     // NAN
#include <vector>    // std::vector

namespace model
{
    void set_child_pointer(GLuint childID, void* child_pointer, std::vector<void*> &child_pointer_vector, std::queue<GLuint> &free_childID_queue)
    {
        child_pointer_vector[childID] = child_pointer;

        if (child_pointer == NULL)
        {
            if (childID == child_pointer_vector.size() - 1)
            {
                // OK, this is the biggest childID of all childID's of this 'object'.
                // We can reduce the size of the child pointer vector at least by 1.
                while ((!child_pointer_vector.empty()) && (child_pointer_vector.back() == NULL))
                {
                    // Reduce the size of child pointer vector by 1.
                    child_pointer_vector.pop_back();
                }
            }
        }
    }

    GLuint get_childID(std::vector<void*> &child_pointer_vector, std::queue<GLuint> &free_childID_queue)
    {
        GLuint childID;

        while (!free_childID_queue.empty())
        {
            // return the first (oldest) free childID.
            childID = free_childID_queue.front();
            free_childID_queue.pop();

            // check that the child index does not exceed current child pointer vector.
            if (childID < child_pointer_vector.size())
            {
                // OK, it does not exceed current child pointer vector.
                return childID;
            }
        }
        // OK, the queue is empty.
        // A new child index must be created.
        childID = child_pointer_vector.size();

        // child pointer vector must also be extended with an appropriate NULL pointer.
        child_pointer_vector.push_back(NULL);

        return childID;
    }

}
