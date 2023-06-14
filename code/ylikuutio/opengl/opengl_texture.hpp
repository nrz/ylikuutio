// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2023 Antti Nuortimo.
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

#ifndef YLIKUUTIO_OPENGL_OPENGL_TEXTURE_HPP_INCLUDED
#define YLIKUUTIO_OPENGL_OPENGL_TEXTURE_HPP_INCLUDED

#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <cstddef>  // std::size_t
#include <memory>   // std::shared_ptr
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace yli::opengl
{
    // Load texture from memory.
    bool prepare_opengl_texture(
            const std::shared_ptr<std::vector<uint8_t>> image_data,
            const std::size_t image_width,
            const std::size_t image_height,
            GLuint& textureID);
}

#endif
