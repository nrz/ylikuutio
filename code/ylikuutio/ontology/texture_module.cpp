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

#include "texture_module.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string

namespace yli::ontology
{
    TextureModule::~TextureModule()
    {
        // destructor.

        if (this->is_texture_loaded)
        {
            // Delete texture.
            glDeleteTextures(1, &this->texture);
        }
    }

    const std::string& TextureModule::get_texture_filename() const
    {
        return this->texture_filename;
    }

    const std::string& TextureModule::get_texture_file_format() const
    {
        return this->texture_file_format;
    }

    uint32_t TextureModule::get_image_width() const
    {
        return this->image_width;
    }

    uint32_t TextureModule::get_image_height() const
    {
        return this->image_height;
    }

    uint32_t TextureModule::get_image_size() const
    {
        return this->image_size;
    }

    uint32_t TextureModule::get_n_color_channels() const
    {
        return this->n_color_channels;
    }

    GLuint TextureModule::get_texture() const
    {
        return this->texture;
    }

    bool TextureModule::get_is_texture_loaded() const
    {
        return this->is_texture_loaded;
    }
}
