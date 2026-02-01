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

#include "fbx_texture_loader.hpp"
#include "common_texture_loader.hpp"
#include "code/ylikuutio/load/image_loader_struct.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.
#include "code/ylikuutio/string/ylikuutio_string.hpp"

// Include OpenFBX
#include <ofbx.h>

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cerr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string

namespace yli::render
{
    enum class GraphicsApiBackend;
}

namespace yli::load
{
    // Load texture from memory.
    bool load_fbx_texture(
            const ofbx::Texture* const ofbx_texture,
            uint32_t& image_width,
            uint32_t& image_height,
            uint32_t& image_size,
            uint32_t& n_color_channels,
            GLuint& textureID,
            const yli::render::GraphicsApiBackend graphics_api_backend)
    {
        // Requirements:
        // `ofbx_texture` must not be `nullptr`.

        if (ofbx_texture == nullptr)
        {
            std::cerr << "ERROR: `yli::load::load_fbx_texture`: `ofbx_texture` is `nullptr`!\n";
            return false;
        }

        // Load the texture.
        const std::string filename = std::string(ofbx_texture->getFileName().begin, ofbx_texture->getFileName().end);

        yli::string::print_hexdump<char>(filename);

        // Find out the filename.
        const char separator = '/'; // FIXME: don't assume slash as some operating systems may use other characters.

        std::string filename_buffer = yli::string::extract_last_part_of_string<char>(
                filename,
                separator);

        std::cout << "Filename length: " << filename_buffer.size() << " characters.\n";

        std::cout << "Texture file: " << filename_buffer << "\n";

        // Find out the file suffix (filetype).
        const char suffix_separator = '.';

        std::string file_suffix_buffer = yli::string::extract_last_part_of_string<char>(
                filename_buffer,
                suffix_separator);

        std::cout << "Texture file suffix: " << file_suffix_buffer << "\n";

        if (file_suffix_buffer == "png")
        {
            yli::load::ImageLoaderStruct image_loader_struct;
            image_loader_struct.should_discard_alpha_channel = true;
            image_loader_struct.should_flip_vertically = true;
            return yli::load::load_common_texture(filename_buffer, image_loader_struct, image_width, image_height, image_size, n_color_channels, textureID, graphics_api_backend);
        }

        return false;
    }
}
