#ifndef __FILE_LOADER_HPP_INCLUDED
#define __FILE_LOADER_HPP_INCLUDED

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli
{
    namespace file
    {
        std::string slurp(const std::string& file_path);
        std::vector<uint8_t> binary_slurp(const std::string& file_path);
    }
}

#endif
