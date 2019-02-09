#include "sdl.hpp"

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

#include "SDL.h"

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr

namespace yli
{
    namespace sdl
    {
        bool init_SDL()
        {
            if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
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
    }
}
