#include "input.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include GLFW
#ifndef __GLFW3_H_INCLUDED
#define __GLFW3_H_INCLUDED
#include <GLFW/glfw3.h>
#endif

namespace yli
{
    namespace input
    {
        void disable_cursor(GLFWwindow* window)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }

        void set_sticky_keys(GLFWwindow* window)
        {
            glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
        }

        void set_cursor_position(GLFWwindow* window, double xpos, double ypos)
        {
            glfwSetCursorPos(window, xpos, ypos);
        }
    }
}
