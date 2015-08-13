#ifndef __MODEL_TEMPLATES_HPP_INCLUDED
#define __MODEL_TEMPLATES_HPP_INCLUDED

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

#ifndef __GLM_GTC_MATRIX_TRANSFORM_HPP_INCLUDED
#define __GLM_GTC_MATRIX_TRANSFORM_HPP_INCLUDED
#include <glm/gtc/matrix_transform.hpp>
#endif

#ifndef __GLM_GTC_QUATERNION_HPP_INCLUDED
#define __GLM_GTC_QUATERNION_HPP_INCLUDED
#include <glm/gtc/quaternion.hpp> // glm::quat
#endif

#ifndef __GLM_GTX_QUATERNION_HPP_INCLUDED
#define __GLM_GTX_QUATERNION_HPP_INCLUDED
#include <glm/gtx/quaternion.hpp> // glm::toMat4
#endif

#include "model_common_functions.hpp"

namespace model
{
    void set_child_pointer(GLuint childID, void* child_pointer, std::vector<void*> &child_pointer_vector, std::queue<GLuint> &free_childID_queue);
    GLuint get_childID(std::vector<void*> &child_pointer_vector, std::queue<GLuint> &free_childID_queue);

    // template<typename T1>
    template<class T1>
        void bind_child_to_parent(T1 child_pointer, std::vector<void*> &child_pointer_vector, std::queue<GLuint> &free_childID_queue)
        {
            // get childID from the parent, because every child deserves a unique ID!
            child_pointer->childID = get_childID(child_pointer_vector, free_childID_queue);
            // set pointer to the child in parent's child pointer vector so that parent knows about children's whereabouts!
            set_child_pointer(child_pointer->childID, child_pointer, child_pointer_vector, free_childID_queue);
        }

    template <class T1, class T2>
        void bind_child_to_new_parent(
                T1 child_pointer,
                T2 new_parent_pointer,
                std::vector<void*> &old_child_pointer_vector,
                std::queue<GLuint> &old_free_childID_queue)
        {
            // set pointer to this child to NULL in the old parent.
            set_child_pointer(child_pointer->childID, NULL, old_child_pointer_vector, old_free_childID_queue);
            // set the new parent pointer.
            child_pointer->parent_pointer = new_parent_pointer;
            // bind to the new parent.
            child_pointer->bind_to_parent();
        }

    // template<typename T1>
    template<class T1>
        void delete_children(std::vector<void*> &child_pointer_vector)
        {
            for (GLuint child_i = 0; child_i < child_pointer_vector.size(); child_i++)
            {
                delete static_cast<T1>(child_pointer_vector[child_i]);
            }
        }

    // template<typename T1>
    template<class T1>
        void render_children(std::vector<void*> &child_pointer_vector)
        {
            for (GLuint child_i = 0; child_i < child_pointer_vector.size(); child_i++)
            {
                T1 child_pointer;
                child_pointer = static_cast<T1>(child_pointer_vector[child_i]);

                if (child_pointer != NULL)
                {
                    child_pointer->render();
                }
            }
        }
}

#endif
