// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2026 Antti Nuortimo.
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
#include <cstddef>   // std::size_t
#include <iostream>  // std::cout, std::cerr
#include <string>    // std::to_string
#include <stdexcept> // std::runtime_error

namespace yli::sdl
{
    [[nodiscard]] yli::render::GraphicsApiBackend init_sdl(const yli::render::GraphicsApiBackend graphics_api_backend)
    {
        if (graphics_api_backend == yli::render::GraphicsApiBackend::OPENGL)
        {
            // Initialize SDL.

            if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) [[unlikely]]
            {
                print_sdl_error();
                throw std::runtime_error("ERROR: `yli::sdl::init_sdl`: failed to initialize SDL.");
            }

            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

            return yli::render::GraphicsApiBackend::OPENGL; // Success.
        }
        else if (graphics_api_backend == yli::render::GraphicsApiBackend::VULKAN)
        {
            throw std::runtime_error("ERROR: `yli::sdl::init_sdl`: Vulkan support not implemented yet!");
        }

        return yli::render::GraphicsApiBackend::HEADLESS; // Headless.
    }

    [[nodiscard]] std::vector<SDL_DisplayMode> get_display_modes(const yli::render::GraphicsApiBackend graphics_api_backend)
    {
        std::vector<SDL_DisplayMode> display_modes;

        if (graphics_api_backend == yli::render::GraphicsApiBackend::HEADLESS ||
            graphics_api_backend == yli::render::GraphicsApiBackend::SOFTWARE)
        {
            return display_modes;
        }

        int n_displays { 0 };

        const SDL_DisplayID* const display_ids = SDL_GetDisplays(&n_displays);

        if (display_ids == nullptr)
        {
            throw std::runtime_error("ERROR: `yli::sdl::get_display_modes`: `SDL_GetDisplays` failed!");
        }

        if (n_displays == 0)
        {
            throw std::runtime_error("ERROR: `yli::sdl::get_display_modes`: `n_displays` is 0!");
        }

        if (n_displays < 0)
        {
            throw std::runtime_error("ERROR: `yli::sdl::get_display_modes`: `n_displays` is negative: " + std::to_string(n_displays));
        }

        if (graphics_api_backend == yli::render::GraphicsApiBackend::OPENGL)
        {
            display_modes.resize(n_displays);

            for (std::size_t i = 0; display_ids[i] != 0; i++)
            {
                const SDL_DisplayMode* display_mode_ptr = SDL_GetCurrentDisplayMode(display_ids[i]);

                if (display_mode_ptr == nullptr)
                {
                    throw std::runtime_error("ERROR: `yli::sdl::get_display_modes`: `SDL_GetCurrentDisplayMode` failed!");
                }

                display_modes.at(i) = *display_mode_ptr;
            }
        }

        return display_modes;
    }

    [[nodiscard]] SDL_Window* create_window(
            const SDL_DisplayID display_id,
            const int window_width,
            const int window_height,
            const char* const title,
            const SDL_WindowFlags flags)
    {
        SDL_Rect bounds;
        SDL_Window* window = nullptr;

        if (flags & SDL_WINDOW_FULLSCREEN)
        {
            // Fullscreen.
            if (!SDL_GetDisplayBounds(display_id, &bounds))
            {
                print_sdl_error();
                throw std::runtime_error("ERROR: `yli::sdl::create_window`: getting usable display bounds failed!");
            }

            window = SDL_CreateWindow(
                    title,
                    bounds.w,
                    bounds.h,
                    flags);
        }
        else
        {
            // Windowed.
            if (!SDL_GetDisplayUsableBounds(display_id, &bounds))
            {
                print_sdl_error();
                throw std::runtime_error("ERROR: `yli::sdl::create_window`: getting display bounds failed!");
            }

            window = SDL_CreateWindow(
                    title,
                    (window_width < bounds.w ? window_width : bounds.w),
                    (window_height < bounds.h ? window_height : bounds.h),
                    flags);
        }

        if (window != nullptr)
        {
            std::cout << "Window created successfully.\n";
            return window;
        }

        print_sdl_error();
        throw std::runtime_error("ERROR: `yli::sdl::create_window`: creating window failed!");
    }

    [[nodiscard]] SDL_Window* create_hidden_window(SDL_DisplayID display_id, const int window_width, const int window_height, const char* const title, const bool is_fullscreen)
    {
        Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN; // `Uint32` is a SDL datatype.

        if (is_fullscreen)
        {
            flags |= SDL_WINDOW_FULLSCREEN;
        }

        return create_window(display_id, window_width, window_height, title, flags);
    }

    [[nodiscard]] SDL_GLContext create_context(SDL_Window* const window)
    {
        SDL_GLContext context = SDL_GL_CreateContext(window);

        if (context != nullptr)
        {
            std::cout << "OpenGL context created successfully.\n";
            return context;
        }

        print_sdl_error();
        throw std::runtime_error("ERROR: `yli::sdl::create_context`: creating OpenGL context failed!");
    }

    void set_window_size(SDL_Window* window, const int window_width, const int window_height)
    {
        SDL_SetWindowSize(window, window_width, window_height);
    }

    [[nodiscard]] bool set_window_windowed(SDL_Window* window)
    {
        if (SDL_SetWindowFullscreen(window, 0))
        {
            std::cout << "Window set to windowed successfully.\n";
            return true; // Success.
        }

        print_sdl_error();
        throw std::runtime_error("ERROR: `yli::sdl::set_window_windowed`: setting window to windowed failed!");
    }

    [[nodiscard]] bool make_context_current(SDL_Window* window, SDL_GLContext context)
    {
        if (SDL_GL_MakeCurrent(window, context))
        {
            std::cout << "OpenGL context made current successfully.\n";
            return true; // Success.
        }

        print_sdl_error();
        throw std::runtime_error("ERROR: `yli::sdl::make_context_current`: making context current failed!");
    }

    [[nodiscard]] bool set_swap_interval(const int interval)
    {
        if (SDL_GL_SetSwapInterval(interval))
        {
            std::cout << "Swap interval set successfully.\n";
            return true; // Success.
        }

        print_sdl_error();
        throw std::runtime_error("ERROR: `yli::sdl::set_swap_interval`: setting swap interval failed!");
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
