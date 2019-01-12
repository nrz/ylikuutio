#include "opengl.hpp"

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

#include "SDL.h"

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr

namespace yli
{
    namespace opengl
    {
        bool init_window()
        {
            if (SDL_Init(SDL_INIT_VIDEO) < 0)
            {
                std::cerr << "Failed to initialize SDL.\n";
                return false;
            }

            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
            return true;
        }

        SDL_Window* create_window(const int window_width, const int window_height, const char* const title)
        {
            return SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_OPENGL);
        }

        int set_window_windowed(SDL_Window* window)
        {
            return SDL_SetWindowFullscreen(window, 0);
        }

        void make_context_current(SDL_Window* window, SDL_GLContext context)
        {
            SDL_GL_MakeCurrent(window, context);
        }

        bool init_glew()
        {
            if (glewInit() != GLEW_OK)
            {
                std::cerr << "Failed to initialize GLEW.\n";
                return false;
            }
            return true;
        }

        void enable_depth_test()
        {
            // Enable depth test.
            glEnable(GL_DEPTH_TEST);
        }

        void disable_depth_test()
        {
            // Disable depth test.
            glDisable(GL_DEPTH_TEST);
        }

        void set_depth_func_to_less()
        {
            // Accept a fragment if it closer to the camera than the former one.
            glDepthFunc(GL_LESS);
        }

        void cull_triangles()
        {
            // Cull triangles whose normal is not towards the camera.
            glEnable(GL_CULL_FACE);
        }

        void set_background_color(const float red, const float green, const float blue, const float alpha)
        {
            glClearColor(red, green, blue, alpha);
        }

        void set_filtering_parameters()
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glGenerateMipmap(GL_TEXTURE_2D);
        }

        void set_wireframe(const bool wireframe)
        {
            if (wireframe)
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            }
            else
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }
        }

        bool has_ext_framebuffer_object()
        {
            return GLEW_EXT_framebuffer_object;
        }

        bool has_arb_shader_objects()
        {
            return GLEW_ARB_shader_objects;
        }

        bool has_arb_vertex_shader()
        {
            return GLEW_ARB_vertex_shader;
        }

        bool has_arb_fragment_shader()
        {
            return GLEW_ARB_fragment_shader;
        }
    }
}
