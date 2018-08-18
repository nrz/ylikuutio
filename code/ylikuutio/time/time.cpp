#include "time.hpp"

#include "SDL.h"

// Include standard headers
#include <stdint.h> // uint32_t etc.

namespace yli
{
    namespace time
    {
        double get_time()
        {
            return static_cast<double>(SDL_GetTicks()) / 1000; // `SDL_GetTicks` return milliseconds.
        }
    }
}
