// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2022 Antti Nuortimo.
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
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.
#include "code/ylikuutio/render/graphics_api_backend.hpp"

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr

namespace yli::sdl
{
    [[nodiscard]] yli::render::GraphicsApiBackend init_sdl(const yli::render::GraphicsApiBackend graphics_api_backend)
    {
        if (graphics_api_backend == yli::render::GraphicsApiBackend::OPENGL)
        {
            // Initialize SDL.

            if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
            {
                std::cerr << "ERROR: `yli::sdl::init_sdl`: failed to initialize SDL.\n";
                print_sdl_error();
                return yli::render::GraphicsApiBackend::HEADLESS; // Headless.
            }

#if __APPLE__
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
#else
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif

            return yli::render::GraphicsApiBackend::OPENGL; // Success.
        }

        return yli::render::GraphicsApiBackend::HEADLESS; // Headless.
    }

    [[nodiscard]] SDL_Window* create_window(const int window_width, const int window_height, const char* const title, const Uint32 flags)
    {
        SDL_Window* const window = SDL_CreateWindow(
                title,
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                window_width,
                window_height,
                flags);

        if (window != nullptr)
        {
            std::cout << "Window created successfully.\n";
            return window;
        }

        std::cerr << "ERROR: `yli::sdl::create_window`: creating window failed!\n";
        print_sdl_error();
        return window;
    }

    [[nodiscard]] SDL_Window* create_window(const int window_width, const int window_height, const char* const title, const bool is_fullscreen)
    {
        Uint32 flags = SDL_WINDOW_OPENGL; // `Uint32` is a SDL datatype.

        if (is_fullscreen)
        {
            flags |= SDL_WINDOW_FULLSCREEN;
        }

        return create_window(window_width, window_height, title, flags);
    }

    [[nodiscard]] SDL_Window* create_hidden_window(const int window_width, const int window_height, const char* const title, const bool is_fullscreen)
    {
        Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN; // `Uint32` is a SDL datatype.

        if (is_fullscreen)
        {
            flags |= SDL_WINDOW_FULLSCREEN;
        }

        return create_window(window_width, window_height, title, flags);
    }

    [[nodiscard]] SDL_GLContext create_context(SDL_Window* const window)
    {
        SDL_GLContext context = SDL_GL_CreateContext(window);

        if (context != nullptr)
        {
            std::cout << "OpenGL context created successfully.\n";
            return context;
        }

        std::cerr << "ERROR: `yli::sdl::create_context`: creating OpenGL context failed!\n";
        print_sdl_error();
        return context;
    }

    void set_window_size(SDL_Window* window, const int window_width, const int window_height)
    {
        SDL_SetWindowSize(window, window_width, window_height);
    }

    [[nodiscard]] bool set_window_windowed(SDL_Window* window)
    {
        int success = SDL_SetWindowFullscreen(window, 0);

        if (success == 0)
        {
            std::cout << "Window set to windowed successfully.\n";
            return true; // Success.
        }

        std::cerr << "ERROR: `yli::sdl::set_window_windowed`: setting window to windowed failed!\n";
        print_sdl_error();
        return false; // Fail.
    }

    [[nodiscard]] bool make_context_current(SDL_Window* window, SDL_GLContext context)
    {
        const int success = SDL_GL_MakeCurrent(window, context);

        if (success == 0)
        {
            std::cout << "OpenGL context made current successfully.\n";
            return true; // Success.
        }

        std::cerr << "ERROR: `yli::sdl::make_context_current`: making context current failed!\n";
        print_sdl_error();
        return false;
    }

    [[nodiscard]] bool set_swap_interval(const int interval)
    {
        int success = SDL_GL_SetSwapInterval(interval);

        if (success == 0)
        {
            std::cout << "Swap interval set successfully.\n";
            return true; // Success.
        }

        std::cerr << "ERROR: `yli::sdl::set_swap_interval`: setting swap interval failed!\n";
        print_sdl_error();
        return false;
    }

    void flush_sdl_event_queue()
    {
        SDL_Event sdl_event;
        while (SDL_PollEvent(&sdl_event));
    }

    void print_sdl_error()
    {
        std::cerr << "SDL error: " << SDL_GetError() << "\n";
    }
}
