#ifndef __INPUT_HPP_INCLUDED
#define __INPUT_HPP_INCLUDED

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

#endif
