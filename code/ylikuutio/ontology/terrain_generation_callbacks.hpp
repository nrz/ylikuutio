#ifndef __TERRAIN_GENERATION_CALLBACKS_HPP_INCLUDED
#define __TERRAIN_GENERATION_CALLBACKS_HPP_INCLUDED

// Include standard headers
#include <stdint.h> // uint32_t etc.

namespace yli
{
    namespace ontology
    {
        float* get_noise(int32_t x_start, int32_t y_start, int32_t z_start, int32_t x_size, int32_t y_size, int32_t z_size, float scale_modifier);
    }
}

#endif
