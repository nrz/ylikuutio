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

#ifndef YLIKUUTIO_ONTOLOGY_TEXTURE_MODULE_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_TEXTURE_MODULE_HPP_INCLUDED

#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.
#include <ofbx.h>

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string

namespace yli::load
{
    struct ImageLoaderStruct;
}

namespace yli::ontology
{
    class Registry;
    class Universe;

    class TextureModule final
    {
        public:
            TextureModule(
                    yli::ontology::Universe& universe,
                    yli::ontology::Registry* const registry,
                    const std::string& texture_filename,
                    const std::string& texture_file_format,
                    const yli::load::ImageLoaderStruct& image_loader_struct,
                    const std::string& name);

            TextureModule(
                    yli::ontology::Universe& universe,
                    yli::ontology::Registry* const registry,
                    const ofbx::Texture* ofbx_texture,
                    const yli::load::ImageLoaderStruct& image_loader_struct,
                    const std::string& name);

            TextureModule(const TextureModule&) = delete;            // Delete copy constructor.
            TextureModule &operator=(const TextureModule&) = delete; // Delete copy assignment.

            // destructor.
            ~TextureModule();

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
