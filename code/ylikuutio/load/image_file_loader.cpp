// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
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

#include "image_file_loader.hpp"
#include "code/ylikuutio/file/file_loader.hpp"
#include "code/ylikuutio/memory/memory_templates.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Include standard headers
#include <algorithm> // std::copy
#include <cstddef>   // std::size_t
#include <iostream>  // std::cout, std::cin, std::cerr
#include <limits>    // std::numeric_limits
#include <memory>    // std::make_shared, std::shared_ptr
#include <stdint.h>  // uint32_t etc.
#include <string>    // std::string
#include <vector>    // std::vector

namespace yli
{
    namespace load
    {
        std::shared_ptr<std::vector<uint8_t>> load_image_file(
                const std::string& filename,
                std::size_t& image_width,
                std::size_t& image_height,
                std::size_t& image_size)
        {
            std::cout << "Loading BMP file " << filename << " ...\n";

            int x = 0;
            int y = 0;
            int channels_in_file = 0;
            const int desired_channels = 3;

            stbi_set_flip_vertically_on_load(true);
            stbi_uc* stbi_image_data = stbi_load(&filename[0], &x, &y, &channels_in_file, desired_channels);

            bool has_file_errors = false;

            if (x < 0)
            {
                std::cerr << filename << "ERROR: `yli::load::load_image_file`: image width is negative!\n";
                has_file_errors = true;
            }

            if (y < 0)
            {
                std::cerr << filename << "ERROR: `yli::load::load_image_file`: image height is negative!\n";
                has_file_errors = true;
            }

            if (has_file_errors)
            {
                free(stbi_image_data);
                return nullptr;
            }

            image_width = x;
            image_height = y;
            const std::size_t number_of_pixels = image_width * image_height;

            if (number_of_pixels > std::numeric_limits<std::size_t>::max() / 4)
            {
                std::cerr << "BMP file is too big, number of pixels: " << number_of_pixels << "\n";
                return nullptr;
            }

            image_size = static_cast<std::size_t>(desired_channels) * number_of_pixels;

            // Create a buffer.
            std::shared_ptr<std::vector<uint8_t>> image_data = std::make_shared<std::vector<uint8_t>>();
            image_data->reserve(image_size);

            std::cout << "Copying image data ...\n";
            std::copy(stbi_image_data, stbi_image_data + image_size, image_data->begin());
            std::cout << "Image data copied.\n";

            free(stbi_image_data);
            return image_data;
        }
    }
}
