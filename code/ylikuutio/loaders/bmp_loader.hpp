#ifndef __BMP_LOADER_HPP_INCLUDED
#define __BMP_LOADER_HPP_INCLUDED

// Include standard headers
#include <cstddef>  // std::size_t
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli
{
    namespace loaders
    {
        uint8_t* load_BMP_file(
                const std::string& bmp_filename,
                std::size_t& image_width,
                std::size_t& image_height,
                std::size_t& image_size);
    }
}

#endif
