#ifndef __SHADER_LOADER_HPP_INCLUDED
#define __SHADER_LOADER_HPP_INCLUDED

// Include standard headers
#include <stdint.h> // uint32_t etc.

namespace yli
{
    namespace load
    {
        uint32_t load_shaders(const char* const vertex_file_path, const char* const fragment_file_path);
    }
}

#endif
