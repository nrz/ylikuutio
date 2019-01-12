#ifndef __TEXTURE_LOADER_HPP_INCLUDED
#define __TEXTURE_LOADER_HPP_INCLUDED

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

        // Load a .BMP file using our custom loader
        bool load_BMP_texture(
                const std::string& filename,
                std::size_t& image_width,
                std::size_t& image_height,
                std::size_t& image_size,
                uint32_t& textureID);

        //// Since GLFW 3, glfwLoadTexture2D() has been removed. You have to use another texture loading library,
        //// or do it yourself (just like load_BMP_texture and load_DDS_texture)
        //// Load a .TGA file using GLFW's own loader
        //uint32_t loadTGA_glfw(const char*  imagepath);

        // Load a .DDS file using GLFW's own loader
        bool load_DDS_texture(
                const std::string& filename,
                std::size_t& image_width,
                std::size_t& image_height,
                std::size_t& image_size,
                uint32_t& textureID);
    }
}

#endif
