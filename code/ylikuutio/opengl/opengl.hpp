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

namespace opengl
{
    bool init_window();
    GLFWwindow* create_window(int window_width, int window_height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
}
