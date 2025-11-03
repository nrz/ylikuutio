// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2025 Antti Nuortimo.
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

#ifndef YLIKUUTIO_INPUT_INPUT_HPP_INCLUDED
#define YLIKUUTIO_INPUT_INPUT_HPP_INCLUDED

#include "code/ylikuutio/sdl/ylikuutio_sdl.hpp"

namespace yli::input
{
    enum class InputMethod
    {
        KEYBOARD,                 // regular keyboard input.
        INPUT_FILE,               // input from file (TODO: implement).
        AI,                       // AI input (TODO: implement).
        INPUT_FILE_THEN_KEYBOARD, // input from file, then regular keyboard input (TODO: implement).
        INPUT_FILE_THEN_AI        // input from file, then AI input (TODO: implement).
    };

    void disable_cursor();
    void set_sticky_keys(SDL_Window* window);
    void set_cursor_position(SDL_Window* window, float xpos, float ypos);
    void enable_relative_mouse_mode(SDL_Window* window);
}

#endif
