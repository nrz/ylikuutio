// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2019 Antti Nuortimo.
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

#include "dds_texture_loader.hpp"
#include "code/ylikuutio/memory/memory_templates.hpp"

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <cstddef>  // std::size_t
#include <cstdio>   // std::FILE, std::fclose, std::fopen, std::fread, std::getchar, std::printf etc.
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

#ifndef FOURCC_DXT1
#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#endif

#ifndef FOURCC_DXT3
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#endif

#ifndef FOURCC_DXT5
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII
#endif

namespace yli
{
    namespace load
    {
        bool load_DDS_texture(
                const std::string& filename,
                std::size_t& image_width,
                std::size_t& image_height,
                std::size_t& image_size,
                uint32_t& textureID)
        {
            const char* const imagepath = filename.c_str();

            uint8_t header[124];

            // Try to open the file.
            std::FILE* const fp = std::fopen(imagepath, "rb");
            if (fp == nullptr)
            {
                std::printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", imagepath);
                return false;
            }

            // Verify the type of the file.
            const std::size_t dds_magic_number_size_in_bytes = 4;   // "DDS "
            char filecode_char[dds_magic_number_size_in_bytes + 1] { 0, 0, 0, 0, 0 };

            if (std::fread(filecode_char, 1, dds_magic_number_size_in_bytes, fp) != dds_magic_number_size_in_bytes)
            {
                std::cerr << "Error while reading " << filename << "\n";
                std::fclose(fp);
                return false;
            }

            const std::string filecode = std::string(filecode_char);

            if (filecode != "DDS ")
            {
                std::fclose(fp);
                return false;
            }

            /* get the surface desc */
            if (std::fread(&header, 124, 1, fp) != 1)
            {
                std::cerr << "Error while reading " << filename << "\n";
                std::fclose(fp);
                return false;
            }

            image_height                = yli::memory::read_nonaligned_32_bit<uint8_t, uint32_t>(header, 8);
            image_width                 = yli::memory::read_nonaligned_32_bit<uint8_t, uint32_t>(header, 12);
            const uint32_t linear_size  = yli::memory::read_nonaligned_32_bit<uint8_t, uint32_t>(header, 16);
            const uint32_t mipmap_count = yli::memory::read_nonaligned_32_bit<uint8_t, uint32_t>(header, 24);
            const uint32_t dwFourCC     = yli::memory::read_nonaligned_32_bit<uint8_t, uint32_t>(header, 80);

            /* how big is it going to be including all mipmaps? */
            const std::size_t bufsize = mipmap_count > 1 ? 2 * static_cast<std::size_t>(linear_size) : linear_size;
            std::vector<uint8_t> buffer;
            buffer.reserve(bufsize);

            if (std::fread(&buffer[0], 1, bufsize, fp) != bufsize)
            {
                std::cerr << "Error while reading " << filename << "\n";
                std::fclose(fp);
                return false;
            }

            // Close the file.
            std::fclose(fp);

            uint32_t format;
            switch (dwFourCC)
            {
                case FOURCC_DXT1:
                    format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
                    break;
                case FOURCC_DXT3:
                    format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
                    break;
                case FOURCC_DXT5:
                    format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
                    break;
                default:
                    return false;
            }

            // Create one OpenGL texture.
            glGenTextures(1, &textureID);

            // Bind the newly created texture: all future texture functions will modify this texture.
            glBindTexture(GL_TEXTURE_2D, textureID);
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

            const std::size_t blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
            std::size_t offset = 0;

            std::size_t temp_width = image_width;
            std::size_t temp_height = image_height;

            // Load the mipmaps.
            for (std::size_t level = 0; level < mipmap_count && (temp_width || temp_height); ++level)
            {
                std::size_t size = ((temp_width + 3) / 4) * ((temp_height + 3) / 4) * blockSize;
                glCompressedTexImage2D(
                        GL_TEXTURE_2D,
                        level,
                        format,
                        temp_width,
                        temp_height,
                        0,
                        size,
                        &buffer[0] + offset);

                offset += size;
                temp_width /= 2;
                temp_height /= 2;

                // Deal with non-power-of-two textures.
                if (temp_width < 1)
                {
                    temp_width = 1;
                }
                if (temp_height < 1)
                {
                    temp_height = 1;
                }
            }

            return true;
        }
    }
}
