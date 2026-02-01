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

#ifndef YLIKUUTIO_LOAD_COMMON_TEXTURE_LOADER_HPP_INCLUDED
#define YLIKUUTIO_LOAD_COMMON_TEXTURE_LOADER_HPP_INCLUDED

#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string

namespace yli::load
{
    struct ImageLoaderStruct;
}

namespace yli::render
{
    enum class GraphicsApiBackend;
}

namespace yli::load
{
    // Load a PNG file.
    bool load_common_texture(
            const std::string& filename,
            const yli::load::ImageLoaderStruct& image_loader_struct,
            uint32_t& image_width,
            uint32_t& image_height,
            uint32_t& image_size,
            uint32_t& n_color_channels,
            GLuint& textureID,
            const yli::render::GraphicsApiBackend graphics_api_backend);
}

#endif
