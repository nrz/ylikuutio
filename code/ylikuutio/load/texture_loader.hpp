#ifndef __TEXTURE_LOADER_HPP_INCLUDED
#define __TEXTURE_LOADER_HPP_INCLUDED

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

#include <ofbx.h>

// Include standard headers
#include <cstddef>  // std::size_t
#include <stdint.h> // uint32_t etc.
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
                uint32_t& textureID);

        // Load texture from memory.
        bool load_FBX_texture(
                const ofbx::Texture* const ofbx_texture,
                std::size_t& image_width,
                std::size_t& image_height,
                std::size_t& image_size,
                uint32_t& textureID);

        // Load a .BMP file using our custom loader.
        bool load_BMP_texture(
                const std::string& filename,
                std::size_t& image_width,
                std::size_t& image_height,
                std::size_t& image_size,
                uint32_t& textureID);

        // Load a .DDS file using our custom loader.
        bool load_DDS_texture(
                const std::string& filename,
                std::size_t& image_width,
                std::size_t& image_height,
                std::size_t& image_size,
                uint32_t& textureID);

        // Load a .CSV file using our custom loader.
        bool load_CSV_texture(
                const std::string& filename,
                const GLenum format,
                const GLenum internal_format,
                const GLenum type,
                std::size_t& image_width,
                std::size_t& image_height,
                std::size_t& image_size,
                uint32_t& textureID);
    }
}

#endif
