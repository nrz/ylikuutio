// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2019 Antti Nuortimo.
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

#include "ylikuutio_sdl.hpp"

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

        void set_window_size(SDL_Window* window, const int window_width, const int window_height)
        {
            SDL_SetWindowSize(window, window_width, window_height);
        }

        int set_window_windowed(SDL_Window* window)
        {
            return SDL_SetWindowFullscreen(window, 0);
        }

        void make_context_current(SDL_Window* window, SDL_GLContext context)
        {
            SDL_GL_MakeCurrent(window, context);
        }

        void flush_sdl_event_queue()
        {
            SDL_Event sdl_event;
            while (SDL_PollEvent(&sdl_event));
        }
    }
}