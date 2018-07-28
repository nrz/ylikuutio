#include "terrain_generation_callbacks.hpp"
#include "FastNoiseSIMD/FastNoiseSIMD.h"

// Include standard headers
#include <stdint.h> // uint32_t etc.

namespace yli
{
    namespace ontology
    {
        float* get_noise(int32_t x_start, int32_t y_start, int32_t z_start, int32_t x_size, int32_t y_size, int32_t z_size, float scale_modifier)
        {
            FastNoiseSIMD* myNoise = FastNoiseSIMD::NewFastNoiseSIMD();

            // Get a set of 16 x 16 x 16 Simplex Fractal noise
            float* noiseSet = myNoise->GetSimplexFractalSet(x_start, y_start, z_start, x_size, y_size, z_size, scale_modifier);    

            FastNoiseSIMD::FreeNoiseSet(noiseSet);

            return noiseSet;
        }
    }
}
