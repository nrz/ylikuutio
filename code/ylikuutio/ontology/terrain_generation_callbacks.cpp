// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2022 Antti Nuortimo.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "terrain_generation_callbacks.hpp"
#include "FastNoiseSIMD/FastNoiseSIMD.h"

// Include standard headers
#include <stdint.h> // uint32_t etc.

namespace yli::ontology
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
