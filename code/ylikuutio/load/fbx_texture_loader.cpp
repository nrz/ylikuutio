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

#include "fbx_texture_loader.hpp"
#include "common_texture_loader.hpp"
#include "code/ylikuutio/string/ylikuutio_string.hpp"

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include OpenFBX
#include <ofbx.h>

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <string>   // std::string

namespace yli
{
    namespace load
    {
        // Load texture from memory.
        bool load_FBX_texture(
                const ofbx::Texture* const ofbx_texture,
                std::size_t& image_width,
                std::size_t& image_height,
                std::size_t& image_size,
                GLuint& textureID,
                const bool is_headless)
        {
            // Requirements:
            // `ofbx_texture` must not be `nullptr`.

            if (ofbx_texture == nullptr)
            {
                std::cerr << "ERROR: `yli::load::load_FBX_texture`: `ofbx_texture` is `nullptr`!\n";
                return false;
            }

            // Load the texture.
            const std::string filename = std::string((const char*) ofbx_texture->getFileName().begin, (const char*) ofbx_texture->getFileName().end);

            yli::string::print_hexdump(filename);

            // Find out the filename.
            const std::size_t filename_buffer_size = 1024;
            char filename_buffer[filename_buffer_size];
            const char separator = '/'; // FIXME: don't assume slash as some operating systems may use other characters.

            const std::size_t filename_length = yli::string::extract_last_part_of_string(
                    filename.c_str(),
                    filename.size(),
                    filename_buffer,
                    filename_buffer_size,
                    separator);

            std::cout << "Filename length: " << filename_length << " bytes.\n";

            const char* const texture_filename = static_cast<char*>(static_cast<void*>(filename_buffer));
            std::cout << "Texture file: " << texture_filename << "\n";

            // Find out the file suffix (filetype).
            const std::size_t file_suffix_buffer_size = 16;
            char file_suffix_buffer[file_suffix_buffer_size];
            const char suffix_separator = '.';

            yli::string::extract_last_part_of_string(
                    filename_buffer,
                    filename_length + 1,
                    file_suffix_buffer,
                    file_suffix_buffer_size,
                    suffix_separator);

            const char* const texture_file_suffix_char = static_cast<char*>(static_cast<void*>(file_suffix_buffer));
            const std::string texture_file_suffix = std::string(texture_file_suffix_char);

            std::cout << "Texture file suffix: " << texture_file_suffix << "\n";

            if (texture_file_suffix == "bmp")
            {
                const std::string filename_string = std::string((char*) &filename_buffer);
                return yli::load::load_common_texture(filename_string, image_width, image_height, image_size, textureID, is_headless);
            }
            else if (texture_file_suffix == "png")
            {
                // TODO: implement PNG loading!
                return false;
            }

            return false;
        }
    }
}
