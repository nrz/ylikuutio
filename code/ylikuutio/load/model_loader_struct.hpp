// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2025 Antti Nuortimo.
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

#ifndef YLIKUUTIO_LOAD_MODEL_LOADER_STRUCT_HPP_INCLUDED
#define YLIKUUTIO_LOAD_MODEL_LOADER_STRUCT_HPP_INCLUDED

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string

namespace yli::load
{
    struct ModelLoaderStruct
    {
        std::string model_filename;    // Filename of the model file.
        std::string model_file_format; // Type of the model file. Supported file formats so far:
                                       // `"png"`/`"PNG"` - PNG heightmap.
                                       // `"fbx"`/`"FBX"` - FBX model.
                                       // `"obj"`/`"OBJ"` - OBJ model.
                                       // `"srtm"`/`"SRTM"` - SRTM heightmap.
                                       // `"asc"`/`"ascii_grid"`/`"ASCII_grid"` - ASCII grid.
        std::string color_channel;     // color channel to use for altitude data, for PNG model files.
        float divisor       { 1.0f };  // Value by which SRTM values are divided to convert them to kilometers.
        float latitude      { 0.0f };  // In degrees, for SRTM model files.
        float longitude     { 0.0f };  // In degrees, for SRTM model files.
        uint32_t mesh_i     { 0 };     // For FBX.
        uint32_t x_step     { 1 };     // Step in x-dimension for input data (set to 1 to load all data points/measurements).
        uint32_t y_step     { 1 };     // Step in y-dimension for input data (set to 1 to load all data points/measurements).
        bool use_real_texture_coordinates { true };

        uint32_t* image_width_pointer  { nullptr };
        uint32_t* image_height_pointer { nullptr };
    };
}

#endif
