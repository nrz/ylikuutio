#ifndef __BMP_LOADER_HPP_INCLUDED
#define __BMP_LOADER_HPP_INCLUDED

// Include standard headers
#include <cstddef>  // std::size_t
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace loaders
{
    uint8_t* load_BMP_file(
            const std::string& bmp_filename,
            int32_t& image_width,
            int32_t& image_height,
            std::size_t& image_size);
}

#endif
