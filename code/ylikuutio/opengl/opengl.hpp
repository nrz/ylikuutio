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
    namespace opengl
    {
        bool init_window();
        GLFWwindow* create_window(const int window_width, const int window_height, const char* const title, GLFWmonitor* const monitor, GLFWwindow* const share);
        void make_context_current(GLFWwindow* const window);
        bool init_glew();
        void enable_depth_test();
        void disable_depth_test();
        void set_depth_func_to_less();
        void cull_triangles();
        void set_background_color(const float red, const float green, const float blue, const float alpha);
        void set_wireframe(const bool wireframe);
    }
}
