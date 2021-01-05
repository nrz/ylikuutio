// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2021 Antti Nuortimo.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef __YLIKUUTIO_SDL_YLIKUUTIO_SDL_HPP_INCLUDED
#define __YLIKUUTIO_SDL_YLIKUUTIO_SDL_HPP_INCLUDED

#include "SDL.h"

#define SDL_main main

namespace yli::sdl
{
    bool init_sdl();
    SDL_Window* create_window(const int window_width, const int window_height, const char* const title, const Uint32 flags);
    SDL_Window* create_window(const int window_width, const int window_height, const char* const title, const bool is_fullscreen);
    SDL_Window* create_hidden_window(const int window_width, const int window_height, const char* const title, const bool is_fullscreen);
    SDL_GLContext create_context(SDL_Window* const window);
    void set_window_size(SDL_Window* window, const int window_width, const int window_height);
    int set_window_windowed(SDL_Window* window);
    void make_context_current(SDL_Window* window, SDL_GLContext context);
    void set_swap_interval(const int interval);
    void flush_sdl_event_queue();
}

#endif
