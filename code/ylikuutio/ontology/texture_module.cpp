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

#include "texture_module.hpp"
#include "universe.hpp"
#include "code/ylikuutio/load/common_texture_loader.hpp"
#include "code/ylikuutio/load/fbx_texture_loader.hpp"
#include "code/ylikuutio/load/image_loader_struct.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.
#include <ofbx.h>

// Include standard headers
#include <iostream> // std::cout, std::cerr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string

namespace yli::ontology
{
    class Registry;

    TextureModule::TextureModule(
            yli::ontology::Universe& universe,
            yli::ontology::Registry* const /* registry */,
            const std::string& texture_filename,
            const std::string& texture_file_format,
            const yli::load::ImageLoaderStruct& image_loader_struct,
            const std::string& /* name */)
        : texture_filename { texture_filename },
        texture_file_format { texture_file_format },
        ofbx_texture { image_loader_struct.ofbx_texture }
    {
        // constructor.

        // If software rendering is in use, the texture can not be loaded into GPU memory,
        // but it can still be loaded into CPU memory to be used by the software rendering.
        const bool should_load_texture =
            universe.get_is_opengl_in_use() ||
            universe.get_is_vulkan_in_use() ||
            universe.get_is_software_rendering_in_use();

        if (should_load_texture)
        {
            bool is_texture_loading_successful = false;

            if (texture_file_format == "png" || texture_file_format == "PNG")
            {
                is_texture_loading_successful = yli::load::load_common_texture(
                        this->texture_filename,
                        image_loader_struct,
                        this->image_width,
                        this->image_height,
                        this->image_size,
                        n_color_channels,
                        this->texture,
                        universe.get_graphics_api_backend());
            }
            else
            {
                std::cerr << "ERROR: `TextureModule::TextureModule`: unsupported texture file format: " << texture_file_format << "\n";
            }

            if (!is_texture_loading_successful)
            {
                std::cerr << "ERROR: `TextureModule::TextureModule`: loading " << texture_file_format << " texture failed!\n";
            }
        }
    }

    TextureModule::TextureModule(
            yli::ontology::Universe& universe,
            yli::ontology::Registry* const /* registry */,
            const ofbx::Texture* ofbx_texture,
            const yli::load::ImageLoaderStruct& /* image_loader_struct */,
            const std::string& /* name */)
        : ofbx_texture { ofbx_texture }
    {
        // If software rendering is in use, the texture can not be loaded into GPU memory,
        // but it can still be loaded into CPU memory to be used by the software rendering.
        const bool should_load_texture =
            universe.get_is_opengl_in_use() ||
            universe.get_is_vulkan_in_use() ||
            universe.get_is_software_rendering_in_use();

        if (should_load_texture)
        {
            bool is_texture_loading_successful = yli::load::load_fbx_texture(
                    this->ofbx_texture,
                    this->image_width,
                    this->image_height,
                    this->image_size,
                    n_color_channels,
                    this->texture,
                    universe.get_graphics_api_backend());

            if (!is_texture_loading_successful)
            {
                std::cerr << "ERROR: `TextureModule::TextureModule`: loading " << texture_file_format << " texture failed!\n";
            }
        }
    }

    TextureModule::~TextureModule()
    {
        // destructor.

        if (this->get_is_texture_loaded())
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
        return this->texture != GL_INVALID_VALUE;
    }
}
