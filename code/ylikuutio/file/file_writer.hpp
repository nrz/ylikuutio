#ifndef __FILE_WRITER_HPP_INCLUDED
#define __FILE_WRITER_HPP_INCLUDED

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli
{
    namespace file
    {
        bool binary_write(const std::vector<uint8_t>& data, const std::string& file_path);
    }
}

#endif
