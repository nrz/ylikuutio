// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
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

#include "bmp_texture_loader.hpp"
#include "bmp_loader.hpp"
#include "texture_loader.hpp"

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <memory>   // std::make_shared, std::shared_ptr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli
{
    namespace load
    {
        bool load_BMP_texture(
                const std::string& filename,
                std::size_t& image_width,
                std::size_t& image_height,
                std::size_t& image_size,
                GLuint& textureID,
                const bool is_headless)
        {
            const std::shared_ptr<std::vector<uint8_t>> image_data = load_BMP_file(filename, image_width, image_height, image_size);

            if (image_data == nullptr)
            {
                std::cerr << "ERROR: `image_data` is `nullptr`!\n";
                return false;
            }

            if (is_headless)
            {
                return true;
            }
            else
            {
                return yli::load::load_texture(image_data, image_width, image_height, textureID);
            }
        }
    }
}
