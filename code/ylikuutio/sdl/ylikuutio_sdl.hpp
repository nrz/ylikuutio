#ifndef __YLIKUUTIO_SDL_HPP_INCLUDED
#define __YLIKUUTIO_SDL_HPP_INCLUDED

#include "SDL.h"

namespace yli
{
    namespace sdl
    {
        bool init_SDL();
        SDL_Window* create_window(const int window_width, const int window_height, const char* const title);
        int set_window_windowed(SDL_Window* window);
        void make_context_current(SDL_Window* window, SDL_GLContext context);
        void flush_sdl_event_queue();
    }
}

#endif
