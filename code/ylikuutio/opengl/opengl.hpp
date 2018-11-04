// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

#include "SDL.h"

namespace yli
{
    namespace opengl
    {
        bool init_window();
        SDL_Window* create_window(const int window_width, const int window_height, const char* const title);
        int set_window_windowed(SDL_Window* window);
        void make_context_current(SDL_Window* window, SDL_GLContext context);
        bool init_glew();
        void enable_depth_test();
        void disable_depth_test();
        void set_depth_func_to_less();
        void cull_triangles();
        void set_background_color(const float red, const float green, const float blue, const float alpha);
        void set_filtering_parameters();
        void set_wireframe(const bool wireframe);
        bool has_ext_framebuffer_object();
        bool has_arb_shader_objects();
        bool has_arb_vertex_shader();
        bool has_arb_fragment_shader();
    }
}
