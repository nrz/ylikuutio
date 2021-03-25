// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2021 Antti Nuortimo.
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

#ifndef __YLIKUUTIO_LOAD_FBX_TEXTURE_LOADER_HPP_INCLUDED
#define __YLIKUUTIO_LOAD_FBX_TEXTURE_LOADER_HPP_INCLUDED

#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

#include <ofbx.h>

// Include standard headers
#include <stdint.h> // uint32_t etc.

namespace yli::load
{
    // Load texture from memory.
    bool load_fbx_texture(
            const ofbx::Texture* const ofbx_texture,
            uint32_t& image_width,
            uint32_t& image_height,
            uint32_t& image_size,
            GLuint& textureID,
            const bool is_headless);
}

#endif
