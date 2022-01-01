// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2022 Antti Nuortimo.
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

#ifndef __YLIKUUTIO_ONTOLOGY_TEXTURE_MODULE_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_TEXTURE_MODULE_HPP_INCLUDED

#include "universe.hpp"
#include "code/ylikuutio/load/common_texture_loader.hpp"
#include "code/ylikuutio/load/fbx_texture_loader.hpp"
#include "code/ylikuutio/load/image_loader_struct.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.
#include <ofbx.h>

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string

namespace yli::ontology
{
    class TextureModule
    {
        public:
            TextureModule(
                    yli::ontology::Universe* const universe,
                    yli::ontology::Registry* const registry,
                    const std::string& texture_filename,
                    const std::string& texture_file_format,
                    const yli::load::ImageLoaderStruct& image_loader_struct,
                    const std::string& name)
                : texture_filename { texture_filename },
                texture_file_format { texture_file_format },
                ofbx_texture { image_loader_struct.ofbx_texture }
            {
                // constructor.

                // If software rendering is in use, the texture can not be loaded into GPU memory,
                // but it can still be loaded into CPU memory to be used by the software rendering.
                const bool should_load_texture = (universe != nullptr &&
                        (universe->get_is_opengl_in_use() ||
                         universe->get_is_vulkan_in_use() ||
                         universe->get_is_software_rendering_in_use()));

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
                                universe->get_graphics_api_backend());
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

            TextureModule(
                    yli::ontology::Universe* const universe,
                    yli::ontology::Registry* const registry,
                    const ofbx::Texture* ofbx_texture,
                    const yli::load::ImageLoaderStruct& image_loader_struct,
                    const std::string& name)
                : ofbx_texture { ofbx_texture }
            {
                // If software rendering is in use, the texture can not be loaded into GPU memory,
                // but it can still be loaded into CPU memory to be used by the software rendering.
                const bool should_load_texture = (universe != nullptr &&
                        (universe->get_is_opengl_in_use() ||
                         universe->get_is_vulkan_in_use() ||
                         universe->get_is_software_rendering_in_use()));

                if (should_load_texture)
                {
                    bool is_texture_loading_successful = yli::load::load_fbx_texture(
                                this->ofbx_texture,
                                this->image_width,
                                this->image_height,
                                this->image_size,
                                n_color_channels,
                                this->texture,
                                universe->get_graphics_api_backend());

                    if (!is_texture_loading_successful)
                    {
                        std::cerr << "ERROR: `TextureModule::TextureModule`: loading " << texture_file_format << " texture failed!\n";
                    }
                }
            }

            TextureModule(const TextureModule&) = delete;            // Delete copy constructor.
            TextureModule &operator=(const TextureModule&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~TextureModule();

            const std::string& get_texture_filename() const;
            const std::string& get_texture_file_format() const;
            uint32_t get_image_width() const;
            uint32_t get_image_height() const;
            uint32_t get_image_size() const;
            uint32_t get_n_color_channels() const;
            GLuint get_texture() const;
            bool get_is_texture_loaded() const;

        private:
            std::string texture_filename;
            std::string texture_file_format; // Supported formats; `"png"`/`"PNG"`.
            const ofbx::Texture* ofbx_texture { nullptr };
            uint32_t image_width              { 0 };
            uint32_t image_height             { 0 };
            uint32_t image_size               { 0 };
            uint32_t n_color_channels         { 0 };
            GLuint texture                    { GL_INVALID_VALUE };
    };
}

#endif
