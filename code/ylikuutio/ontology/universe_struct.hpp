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

#ifndef __UNIVERSE_STRUCT_HPP_INCLUDED
#define __UNIVERSE_STRUCT_HPP_INCLUDED

#include "code/ylikuutio/callback_system/key_and_callback_struct.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <string>   // std::string

namespace yli
{
    namespace ontology
    {
        struct UniverseStruct
        {
            UniverseStruct()
                : window_title("Ylikuutio 0.0.4"),
                window_width(1600),
                window_height(900),
                framebuffer_width(8000),
                framebuffer_height(4500),
                text_size(40),
                font_size(16),
                max_FPS(50000),         // default value max 50000 frames per second.
                speed(5.0f),            // default value 5.0 units / second.
                mouse_speed(0.005f),
                gravity(9.81f / 60.0f), // default Earth gravity (9.81 m/s^2).
                znear(1.0f),
                zfar(5000.0f),          // visibility: from 1 to 5000 units.
                is_headless(false),
                current_keypress_callback_engine_vector_pointer_pointer(nullptr),
                current_keyrelease_callback_engine_vector_pointer_pointer(nullptr)
            {
                // constructor.
            }

            std::string window_title;
            std::size_t window_width;
            std::size_t window_height;
            std::size_t framebuffer_width;
            std::size_t framebuffer_height;
            std::size_t text_size;
            std::size_t font_size;
            std::size_t max_FPS;
            float speed;
            float mouse_speed;
            float gravity;
            float znear;
            float zfar;
            bool is_headless;

            // These are for `yli::console::Console`.
            std::vector<yli::callback_system::KeyAndCallbackStruct>** current_keypress_callback_engine_vector_pointer_pointer;
            std::vector<yli::callback_system::KeyAndCallbackStruct>** current_keyrelease_callback_engine_vector_pointer_pointer;
        };
    }
}

#endif
