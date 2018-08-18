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
        enum input_method
        {
            KEYBOARD,                 // regular keyboard input.
            INPUT_FILE,               // input from file (TODO: implement).
            AI,                       // AI input (TODO: implement).
            INPUT_FILE_THEN_KEYBOARD, // input from file, then regular keyboard input (TODO: implement).
            INPUT_FILE_THEN_AI        // input from file, then AI input (TODO: implement).
        };

        void disable_cursor();
        void set_sticky_keys(SDL_Window* window);
        void set_cursor_position(SDL_Window* window, double xpos, double ypos);
        void enable_relative_mouse_mode();
    }
}
