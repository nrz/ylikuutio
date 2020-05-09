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

#ifndef __UNIVERSE_STRUCT_HPP_INCLUDED
#define __UNIVERSE_STRUCT_HPP_INCLUDED

#include "code/ylikuutio/input/input.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::ontology
{
    struct UniverseStruct
    {
        UniverseStruct()
            : window_title(""),
            window_width(1600),
            window_height(900),
            framebuffer_width(8000),
            framebuffer_height(4500),
            text_size(40),
            font_size(16),
            max_fps(50000),         // default value max 50000 frames per second.
            speed(5.0f),            // default value 5.0 units / second.
            turbo_factor(5.0f),        // default value 5.0 x speed.
            twin_turbo_factor(100.0f), // default value 100.0 x speed.
            mouse_speed(0.005f),
            znear(1.0f),
            zfar(5000.0f),          // visibility: from 1 to 5000 units.
            is_physical(true),      // physics simulation in use.
            is_fullscreen(false),   // windowed mode in use.
            is_headless(false),
            is_silent(false),
            input_method(yli::input::InputMethod::KEYBOARD)
        {
            // constructor.
        }

        std::string window_title;
        uint32_t window_width;
        uint32_t window_height;
        uint32_t framebuffer_width;
        uint32_t framebuffer_height;
        std::size_t text_size;
        std::size_t font_size;
        std::size_t max_fps;
        float speed;
        float turbo_factor;
        float twin_turbo_factor;
        float mouse_speed;
        float znear;
        float zfar;
        bool is_physical;
        bool is_fullscreen;
        bool is_headless;
        bool is_silent;
        yli::input::InputMethod input_method;
    };
}

#endif
