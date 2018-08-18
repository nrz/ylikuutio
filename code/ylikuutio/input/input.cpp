#include "input.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

#include "SDL.h"

namespace yli
{
    namespace input
    {
        void disable_cursor()
        {
            SDL_ShowCursor(SDL_DISABLE);
        }

        void set_cursor_position(SDL_Window* window, double xpos, double ypos)
        {
            SDL_WarpMouseInWindow(window, static_cast<int>(xpos), static_cast<int>(ypos));
        }

        void enable_relative_mouse_mode()
        {
            SDL_SetRelativeMouseMode(SDL_TRUE);
        }
    }
}
