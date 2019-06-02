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

#include "texture_loader.hpp"
#include "bmp_loader.hpp"
#include "csv_loader.hpp"
#include "code/ylikuutio/common/any_value.hpp"
#include "code/ylikuutio/linear_algebra/vector_functions.hpp"
#include "code/ylikuutio/opengl/opengl.hpp"
#include "code/ylikuutio/string/ylikuutio_string.hpp"
#include "code/ylikuutio/memory/memory_templates.hpp"

// Include OpenFBX
#include <ofbx.h>

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <cstddef>  // std::size_t
#include <cstdio>   // std::FILE, std::fclose, std::fopen, std::fread, std::getchar, std::printf etc.
#include <iostream> // std::cout, std::cin, std::cerr
#include <memory>   // std::make_shared, std::shared_ptr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

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
                uint32_t& textureID)
        {
            if (image_data == nullptr)
            {
                std::cerr << "ERROR: `image_data` is `nullptr`!\n";
                return false;
            }

            // Create one OpenGL texture.
            glGenTextures(1, &textureID);

            // Bind the newly created texture: all future texture functions will modify this texture.
            glBindTexture(GL_TEXTURE_2D, textureID);

            // Give the image to OpenGL.
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_width, image_height, 0, GL_BGR, GL_UNSIGNED_BYTE, image_data);

            if (should_image_data_be_deleted)
            {
                // OpenGL has now copied the data. Free our own version.
                delete[] image_data;
            }

            yli::opengl::set_filtering_parameters();

            return true;
        }

        // Load texture from memory.
        bool load_FBX_texture(
                const ofbx::Texture* const ofbx_texture,
                std::size_t& image_width,
                std::size_t& image_height,
                std::size_t& image_size,
                uint32_t& textureID)
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
                uint32_t& textureID)
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
            char filecode_char[dds_magic_number_size_in_bytes + 1];
            filecode_char[dds_magic_number_size_in_bytes] = 0;      // Terminate with 0.

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
            uint8_t* const buffer = new uint8_t[bufsize];

            if (std::fread(buffer, 1, bufsize, fp) != bufsize)
            {
                std::cerr << "Error while reading " << filename << "\n";
                delete[] buffer;
                std::fclose(fp);
                return false;
            }

            // Close the file.
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
                    delete[] buffer;
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

            delete[] buffer;

            return true;
        }

        bool load_CSV_texture(
                const std::string& filename,
                const GLenum format,
                const GLenum internal_format,
                const GLenum type,
                const std::shared_ptr<yli::datatypes::AnyValue> left_filler_vector_any_value,
                const std::shared_ptr<yli::datatypes::AnyValue> right_filler_vector_any_value,
                std::size_t& image_width,
                std::size_t& image_height,
                std::size_t& image_size,
                uint32_t& textureID)
        {
            GLvoid* image_data = nullptr;

            // Shared pointers are created here so that they stay in scope
            // until `glTexImage2D` call.
            std::shared_ptr<std::vector<int8_t>> image_data_int8_t = nullptr;
            std::shared_ptr<std::vector<uint8_t>> image_data_uint8_t = nullptr;
            std::shared_ptr<std::vector<int16_t>> image_data_int16_t = nullptr;
            std::shared_ptr<std::vector<uint16_t>> image_data_uint16_t = nullptr;
            std::shared_ptr<std::vector<int32_t>> image_data_int32_t = nullptr;
            std::shared_ptr<std::vector<uint32_t>> image_data_uint32_t = nullptr;
            std::shared_ptr<std::vector<float>> image_data_float = nullptr;

            switch (type)
            {
                case GL_BYTE:
                    image_data_int8_t = load_CSV_file<int8_t>(filename, image_width, image_height, image_size);
                    if (image_data_int8_t == nullptr)
                    {
                        std::cerr << "ERROR: `yli::load::load_CSV_texture`: `image_data_int8_t` is `nullptr`!\n";
                        return false;
                    }
                    if (left_filler_vector_any_value != nullptr &&
                            right_filler_vector_any_value != nullptr &&
                            left_filler_vector_any_value->type == yli::datatypes::STD_VECTOR_INT8_T_SHARED_PTR &&
                            right_filler_vector_any_value->type == yli::datatypes::STD_VECTOR_INT8_T_SHARED_PTR &&
                            left_filler_vector_any_value->std_vector_int8_t_shared_ptr != nullptr &&
                            right_filler_vector_any_value->std_vector_int8_t_shared_ptr != nullptr)
                    {
                        image_data_int8_t = yli::linear_algebra::insert_elements(
                                *image_data_int8_t,
                                *left_filler_vector_any_value->std_vector_int8_t_shared_ptr,
                                *right_filler_vector_any_value->std_vector_int8_t_shared_ptr);
                        image_data = image_data_int8_t != nullptr ? &(*image_data_int8_t)[0] : nullptr;
                    }
                    else
                    {
                        image_data = &(*image_data_int8_t)[0];
                    }
                    break;
                case GL_UNSIGNED_BYTE:
                    image_data_uint8_t = load_CSV_file<uint8_t>(filename, image_width, image_height, image_size);
                    if (image_data_uint8_t == nullptr)
                    {
                        std::cerr << "ERROR: `yli::load::load_CSV_texture`: `image_data_uint8_t` is `nullptr`!\n";
                        return false;
                    }
                    if (left_filler_vector_any_value != nullptr &&
                            right_filler_vector_any_value != nullptr &&
                            left_filler_vector_any_value->type == yli::datatypes::STD_VECTOR_UINT8_T_SHARED_PTR &&
                            right_filler_vector_any_value->type == yli::datatypes::STD_VECTOR_UINT8_T_SHARED_PTR &&
                            left_filler_vector_any_value->std_vector_uint8_t_shared_ptr != nullptr &&
                            right_filler_vector_any_value->std_vector_uint8_t_shared_ptr != nullptr)
                    {
                        image_data_uint8_t = yli::linear_algebra::insert_elements(
                                *image_data_uint8_t,
                                *left_filler_vector_any_value->std_vector_uint8_t_shared_ptr,
                                *right_filler_vector_any_value->std_vector_uint8_t_shared_ptr);
                        image_data = image_data_uint8_t != nullptr ? &(*image_data_uint8_t)[0] : nullptr;
                    }
                    else
                    {
                        image_data = &(*image_data_uint8_t)[0];
                    }
                    break;
                case GL_SHORT:
                    image_data_int16_t = load_CSV_file<int16_t>(filename, image_width, image_height, image_size);
                    if (image_data_int16_t == nullptr)
                    {
                        std::cerr << "ERROR: `yli::load::load_CSV_texture`: `image_data_int16_t` is `nullptr`!\n";
                        return false;
                    }
                    if (left_filler_vector_any_value != nullptr &&
                            right_filler_vector_any_value != nullptr &&
                            left_filler_vector_any_value->type == yli::datatypes::STD_VECTOR_INT16_T_SHARED_PTR &&
                            right_filler_vector_any_value->type == yli::datatypes::STD_VECTOR_INT16_T_SHARED_PTR &&
                            left_filler_vector_any_value->std_vector_int16_t_shared_ptr != nullptr &&
                            right_filler_vector_any_value->std_vector_int16_t_shared_ptr != nullptr)
                    {
                        image_data_int16_t = yli::linear_algebra::insert_elements(
                                *image_data_int16_t,
                                *left_filler_vector_any_value->std_vector_int16_t_shared_ptr,
                                *right_filler_vector_any_value->std_vector_int16_t_shared_ptr);
                        image_data = image_data_int16_t != nullptr ? &(*image_data_int16_t)[0] : nullptr;
                    }
                    else
                    {
                        image_data = &(*image_data_int16_t)[0];
                    }
                    break;
                case GL_UNSIGNED_SHORT:
                    image_data_uint16_t = load_CSV_file<uint16_t>(filename, image_width, image_height, image_size);
                    if (image_data_uint16_t == nullptr)
                    {
                        std::cerr << "ERROR: `yli::load::load_CSV_texture`: `image_data_uint16_t` is `nullptr`!\n";
                        return false;
                    }
                    if (left_filler_vector_any_value != nullptr &&
                            right_filler_vector_any_value != nullptr &&
                            left_filler_vector_any_value->type == yli::datatypes::STD_VECTOR_UINT16_T_SHARED_PTR &&
                            right_filler_vector_any_value->type == yli::datatypes::STD_VECTOR_UINT16_T_SHARED_PTR &&
                            left_filler_vector_any_value->std_vector_uint16_t_shared_ptr != nullptr &&
                            right_filler_vector_any_value->std_vector_uint16_t_shared_ptr != nullptr)
                    {
                        image_data_uint16_t = yli::linear_algebra::insert_elements(
                                *image_data_uint16_t,
                                *left_filler_vector_any_value->std_vector_uint16_t_shared_ptr,
                                *right_filler_vector_any_value->std_vector_uint16_t_shared_ptr);
                        image_data = image_data_uint16_t != nullptr ? &(*image_data_uint16_t)[0] : nullptr;
                    }
                    else
                    {
                        image_data = &(*image_data_uint16_t)[0];
                    }
                    break;
                case GL_INT:
                    image_data_int32_t = load_CSV_file<int32_t>(filename, image_width, image_height, image_size);
                    if (image_data_int32_t == nullptr)
                    {
                        std::cerr << "ERROR: `yli::load::load_CSV_texture`: `image_data_int32_t` is `nullptr`!\n";
                        return false;
                    }
                    if (left_filler_vector_any_value != nullptr &&
                            right_filler_vector_any_value != nullptr &&
                            left_filler_vector_any_value->type == yli::datatypes::STD_VECTOR_INT32_T_SHARED_PTR &&
                            right_filler_vector_any_value->type == yli::datatypes::STD_VECTOR_INT32_T_SHARED_PTR &&
                            left_filler_vector_any_value->std_vector_int32_t_shared_ptr != nullptr &&
                            right_filler_vector_any_value->std_vector_int32_t_shared_ptr != nullptr)
                    {
                        image_data_int32_t = yli::linear_algebra::insert_elements(
                                *image_data_int32_t,
                                *left_filler_vector_any_value->std_vector_int32_t_shared_ptr,
                                *right_filler_vector_any_value->std_vector_int32_t_shared_ptr);
                        image_data = image_data_int32_t != nullptr ? &(*image_data_int32_t)[0] : nullptr;
                    }
                    else
                    {
                        image_data = &(*image_data_int32_t)[0];
                    }
                    break;
                case GL_UNSIGNED_INT:
                    image_data_uint32_t = load_CSV_file<uint32_t>(filename, image_width, image_height, image_size);
                    if (image_data_uint32_t == nullptr)
                    {
                        std::cerr << "ERROR: `yli::load::load_CSV_texture`: `image_data_uint32_t` is `nullptr`!\n";
                        return false;
                    }
                    if (left_filler_vector_any_value != nullptr &&
                            right_filler_vector_any_value != nullptr &&
                            left_filler_vector_any_value->type == yli::datatypes::STD_VECTOR_UINT32_T_SHARED_PTR &&
                            right_filler_vector_any_value->type == yli::datatypes::STD_VECTOR_UINT32_T_SHARED_PTR &&
                            left_filler_vector_any_value->std_vector_uint32_t_shared_ptr != nullptr &&
                            right_filler_vector_any_value->std_vector_uint32_t_shared_ptr != nullptr)
                    {
                        image_data_uint32_t = yli::linear_algebra::insert_elements(
                                *image_data_uint32_t,
                                *left_filler_vector_any_value->std_vector_uint32_t_shared_ptr,
                                *right_filler_vector_any_value->std_vector_uint32_t_shared_ptr);
                        image_data = image_data_uint32_t != nullptr ? &(*image_data_uint32_t)[0] : nullptr;
                    }
                    else
                    {
                        image_data = &(*image_data_uint32_t)[0];
                    }
                    break;
                case GL_FIXED:
                    return false; // TODO: add support for `GL_FIXED`!
                case GL_HALF_FLOAT:
                    return false; // TODO: add support for `GL_HALF_FLOAT`!
                case GL_FLOAT:
                    image_data_float = load_CSV_file<float>(filename, image_width, image_height, image_size);
                    if (image_data_float == nullptr)
                    {
                        std::cerr << "ERROR: `yli::load::load_CSV_texture`: `image_data_float` is `nullptr`!\n";
                        return false;
                    }
                    if (left_filler_vector_any_value != nullptr &&
                            right_filler_vector_any_value != nullptr &&
                            left_filler_vector_any_value->type == yli::datatypes::STD_VECTOR_FLOAT_SHARED_PTR &&
                            right_filler_vector_any_value->type == yli::datatypes::STD_VECTOR_FLOAT_SHARED_PTR &&
                            left_filler_vector_any_value->std_vector_float_shared_ptr != nullptr &&
                            right_filler_vector_any_value->std_vector_float_shared_ptr != nullptr)
                    {
                        image_data_float = yli::linear_algebra::insert_elements(
                                *image_data_float,
                                *left_filler_vector_any_value->std_vector_float_shared_ptr,
                                *right_filler_vector_any_value->std_vector_float_shared_ptr);
                        image_data = image_data_float != nullptr ? &(*image_data_float)[0] : nullptr;
                    }
                    else
                    {
                        image_data = &(*image_data_float)[0];
                    }
                    break;
                case GL_DOUBLE:
                    return false; // TODO: add support for `GL_DOUBLE`!
                default:
                    // Unknown or unsupported type.
                    return false;
            }

            if (image_data == nullptr)
            {
                std::cerr << "ERROR: `image_data` is `nullptr`!\n";
                return false;
            }

            // Create one OpenGL texture.
            glGenTextures(1, &textureID);

            // Bind the newly created texture: all future texture functions will modify this texture.
            glBindTexture(GL_TEXTURE_2D, textureID);

            // Give the image to OpenGL.
            if (internal_format == GL_INVALID_ENUM)
            {
                // Internal format not defined, use format as internal format.
                glTexImage2D(GL_TEXTURE_2D, 0, format, image_width, image_height, 0, format, type, image_data);
            }
            else
            {
                // Internal format is defined.
                glTexImage2D(GL_TEXTURE_2D, 0, internal_format, image_width, image_height, 0, format, type, image_data);
            }

            yli::opengl::set_nearest_filtering_parameters();

            return true;
        }

        bool load_CSV_texture(
                const std::string& filename,
                const GLenum format,
                const GLenum internal_format,
                const GLenum type,
                std::size_t& image_width,
                std::size_t& image_height,
                std::size_t& image_size,
                uint32_t& textureID)
        {
            return yli::load::load_CSV_texture(
                    filename,
                    format,
                    internal_format,
                    type,
                    nullptr,
                    nullptr,
                    image_width,
                    image_height,
                    image_size,
                    textureID);
        }
    }
}
