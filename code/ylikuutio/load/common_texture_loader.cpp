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

#include "common_texture_loader.hpp"
#include "image_file_loader.hpp"
#include "code/ylikuutio/load/image_loader_struct.hpp"
#include "code/ylikuutio/opengl/opengl_texture.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.
#include "code/ylikuutio/render/graphics_api_backend.hpp"

// Include standard headers
#include <iostream> // std::cerr
#include <memory>   // std::shared_ptr
#include <stdint.h> // uint32_t etc.
#include <stdexcept> // std::runtime_error
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::load
{
    bool load_common_texture(
            const std::string& filename,
            const yli::load::ImageLoaderStruct& image_loader_struct,
            uint32_t& image_width,
            uint32_t& image_height,
            uint32_t& image_size,
            uint32_t& n_color_channels,
            GLuint& textureID,
            const yli::render::GraphicsApiBackend graphics_api_backend)
    {
        const std::shared_ptr<std::vector<uint8_t>> image_data = load_image_file(
                filename,
                image_loader_struct,
                image_width,
                image_height,
                image_size,
                n_color_channels);

        if (image_data == nullptr)
        {
            std::cerr << "ERROR: `image_data` is `nullptr`!\n";
            return false;
        }

        if (graphics_api_backend == yli::render::GraphicsApiBackend::OPENGL)
        {
            return yli::opengl::prepare_opengl_texture(*image_data.get(), image_width, image_height, textureID);
        }
        else if (graphics_api_backend == yli::render::GraphicsApiBackend::VULKAN)
        {
            // TODO: implement.
            throw std::runtime_error("ERROR: `yli::load::load_common_texture`: Vulkan is not supported yet!");
        }
        else if (graphics_api_backend == yli::render::GraphicsApiBackend::SOFTWARE)
        {
            // TODO: implement.
            return false;
        }

        // Headless.
        return true;
    }
}
