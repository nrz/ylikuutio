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

#include "opengl_texture.hpp"
#include "opengl.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace yli::opengl
{
    // Load texture from memory.
    bool prepare_opengl_texture(
            const std::vector<uint8_t>& image_data,
            const std::size_t image_width,
            const std::size_t image_height,
            GLuint& textureID)
    {
        if (image_data.size() != 3 * image_width * image_height)
        {
            std::cerr << "ERROR: `image_data.size()` " << image_data.size() << " does not match `3 * image_width * image_height` (RGB)! " <<
                " 3 * " << image_width << " * " << image_height << " = " << 3 * image_width * image_height << "!\n";
            return false;
        }

        // Create one OpenGL texture.
        glGenTextures(1, &textureID);

        // Bind the newly created texture: all future texture functions will modify this texture.
        glBindTexture(GL_TEXTURE_2D, textureID);

        // Give the image to OpenGL.
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_width, image_height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data.data());

        yli::opengl::set_filtering_parameters();

        return true;
    }
}
