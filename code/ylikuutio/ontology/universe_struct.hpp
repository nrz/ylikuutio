// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2024 Antti Nuortimo.
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

#ifndef YLIKUUTIO_ONTOLOGY_UNIVERSE_STRUCT_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_UNIVERSE_STRUCT_HPP_INCLUDED

#include "entity_struct.hpp"
#include "framebuffer_module_struct.hpp"
#include "code/ylikuutio/input/input.hpp"
#include "code/ylikuutio/render/graphics_api_backend.hpp"

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string

namespace yli::ontology
{
    struct UniverseStruct : public yli::ontology::EntityStruct
    {
        explicit UniverseStruct(const yli::render::GraphicsApiBackend graphics_api_backend) noexcept
            : graphics_api_backend { graphics_api_backend }
        {
            this->is_universe = true;
        }

        UniverseStruct(const yli::ontology::UniverseStruct& universe_struct) = default;
        yli::ontology::UniverseStruct& operator=(const yli::ontology::UniverseStruct& universe_struct) = default;

        std::string application_name;
        std::string window_title;
        uint32_t window_width      { 1600 };
        uint32_t window_height     { 900 };
        uint32_t text_size         { 40 };
        uint32_t font_size         { 16 };
        uint32_t max_fps           { 50000 };   // Default value max 50000 frames per second.
        float speed                { 0.1f };    // Default value 0.1 units / second.
        float turbo_factor         { 5.0f };    // Default value 5.0 x speed.
        float twin_turbo_factor    { 100.0f };  // Default value 100.0 x speed.
        float mouse_speed          { 0.005f };
        float znear                { 1.0f };    // Visibility: from 1 to 5000 units.
        float zfar                 { 5000.0f }; // Visibility: from 1 to 5000 units.
        yli::render::GraphicsApiBackend graphics_api_backend;
        bool is_silent             { false };
        bool is_physical           { true };    // Physics simulation in use.
        bool is_fullscreen         { false };   // Windowed mode in use.
        bool is_desktop_fullscreen { false };   // Windowed mode in use.
        yli::input::InputMethod input_method { yli::input::InputMethod::KEYBOARD };
        yli::ontology::FramebufferModuleStruct framebuffer_module_struct;
    };
}

#endif
