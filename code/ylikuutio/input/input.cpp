// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
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

#include "input.hpp"

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
