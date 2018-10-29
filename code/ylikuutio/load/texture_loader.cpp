#include "texture_loader.hpp"
#include "bmp_loader.hpp"
#include "code/ylikuutio/string/ylikuutio_string.hpp"
#include "code/ylikuutio/memory/memory_templates.hpp"

// Include OpenFBX
#include <ofbx.h>

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <cstdio>   // std::FILE, std::fclose, std::fopen, std::fread, std::getchar, std::printf etc.
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.
#include <stdlib.h> // free, malloc
#include <string>   // std::string

namespace yli
{
    namespace load
    {
        // Load texture from memory.
        bool load_texture(
                const uint8_t* const image_data,
                const std::size_t image_width,
                const std::size_t image_height,
                const bool should_image_data_be_deleted,
                GLuint& textureID)
        {
            if (image_data == nullptr)
            {
                std::cerr << "ERROR: `image_data` is `nullptr`!\n";
                return false;
            }

            // Create one OpenGL texture
            glGenTextures(1, &textureID);

            // "Bind" the newly created texture : all future texture functions will modify this texture
            glBindTexture(GL_TEXTURE_2D, textureID);

            // Give the image to OpenGL
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_width, image_height, 0, GL_BGR, GL_UNSIGNED_BYTE, image_data);

            if (should_image_data_be_deleted)
            {
                // OpenGL has now copied the data. Free our own version
                delete[] image_data;
            }

            // Poor filtering, or ...
            //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

#define CLAMP_TEXTURES
            // #define REPEAT_TEXTURES

#ifdef CLAMP_TEXTURES
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
#endif

#ifdef REPEAT_TEXTURES
            // ... nice trilinear filtering.
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
#endif

#ifdef MIRRORED_REPEAT_TEXTURES
            // ... nice trilinear filtering.
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
#endif

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glGenerateMipmap(GL_TEXTURE_2D);

            // success.
            return true;
        }

        // Load texture from memory.
        bool load_FBX_texture(
                const ofbx::Texture* const ofbx_texture,
                std::size_t& image_width,
                std::size_t& image_height,
                std::size_t& image_size,
                GLuint& textureID)
        {
            // requirements:
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
                return yli::load::load_BMP_texture(filename_string, image_width, image_height, image_size, textureID);
            }
            else if (texture_file_suffix == "png")
            {
                // TODO: implement PNG loading!
                return false;
            }

            return false;
        }

        bool load_BMP_texture(
                const std::string& filename,
                std::size_t& image_width,
                std::size_t& image_height,
                std::size_t& image_size,
                GLuint& textureID)
        {
            const uint8_t* const image_data = load_BMP_file(filename, image_width, image_height, image_size);

            if (image_data == nullptr)
            {
                std::cerr << "ERROR: `image_data` is `nullptr`!\n";
                return false;
            }

            return yli::load::load_texture(image_data, image_width, image_height, true, textureID);
        }

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

        bool load_DDS_texture(
                const std::string& filename,
                std::size_t& image_width,
                std::size_t& image_height,
                std::size_t& image_size,
                GLuint& textureID)
        {
            const char* const imagepath = filename.c_str();

            uint8_t header[124];

            /* try to open the file */
            std::FILE* const fp = std::fopen(imagepath, "rb");
            if (fp == nullptr)
            {
                std::printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", imagepath);
                return false;
            }

            /* verify the type of file */
            const std::size_t dds_magic_number_size_in_bytes = 4; // "DDS "
            char filecode_char[dds_magic_number_size_in_bytes + 1];
            filecode_char[dds_magic_number_size_in_bytes] = 0; // terminate with 0.

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

            image_height               = yli::memory::read_nonaligned_32_bit<uint8_t, uint32_t>(header, 8);
            image_width                = yli::memory::read_nonaligned_32_bit<uint8_t, uint32_t>(header, 12);
            const uint32_t linearSize  = yli::memory::read_nonaligned_32_bit<uint8_t, uint32_t>(header, 16);
            const uint32_t mipMapCount = yli::memory::read_nonaligned_32_bit<uint8_t, uint32_t>(header, 24);
            const uint32_t fourCC      = yli::memory::read_nonaligned_32_bit<uint8_t, uint32_t>(header, 80);

            /* how big is it going to be including all mipmaps? */
            const std::size_t bufsize = mipMapCount > 1 ? 2 * static_cast<std::size_t>(linearSize) : linearSize;
            uint8_t* const buffer = (uint8_t*) malloc(bufsize * sizeof(uint8_t));

            if (std::fread(buffer, 1, bufsize, fp) != bufsize)
            {
                std::cerr << "Error while reading " << filename << "\n";
                free(buffer);
                std::fclose(fp);
                return false;
            }

            /* close the file pointer */
            std::fclose(fp);

            uint32_t format;
            switch(fourCC)
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
                    free(buffer);
                    return false;
            }

            // Create one OpenGL texture
            glGenTextures(1, &textureID);

            // "Bind" the newly created texture : all future texture functions will modify this texture
            glBindTexture(GL_TEXTURE_2D, textureID);
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

            const std::size_t blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
            std::size_t offset = 0;

            std::size_t temp_width = image_width;
            std::size_t temp_height = image_height;

            /* load the mipmaps */
            for (std::size_t level = 0; level < mipMapCount && (temp_width || temp_height); ++level)
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
                        buffer + offset);

                offset += size;
                temp_width /= 2;
                temp_height /= 2;

                // Deal with Non-Power-Of-Two textures. This code is not included in the webpage to reduce clutter.
                if (temp_width < 1)
                {
                    temp_width = 1;
                }
                if (temp_height < 1)
                {
                    temp_height = 1;
                }
            }
            free(buffer);

            return true;
        }
    }
}
