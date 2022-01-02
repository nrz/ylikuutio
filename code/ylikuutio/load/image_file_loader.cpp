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

#include "image_file_loader.hpp"
#include "png_loader.hpp"
#include "code/ylikuutio/load/image_loader_struct.hpp"

#include "png.h"

// Include standard headers
#include <cstddef>   // std::size_t
#include <iostream>  // std::cout, std::cin, std::cerr
#include <memory>    // std::make_shared, std::shared_ptr
#include <stdint.h>  // uint32_t etc.
#include <string>    // std::string
#include <vector>    // std::vector

namespace yli::load
{
    std::shared_ptr<std::vector<uint8_t>> load_image_file(
            const std::string& filename,
            const yli::load::ImageLoaderStruct& image_loader_struct,
            uint32_t& image_width,
            uint32_t& image_height,
            uint32_t& image_size,
            uint32_t& n_color_channels)
    {
        std::cout << "Loading image file " << filename << " ...\n";

        const std::size_t dot_position = filename.find_last_of('.');

        if (dot_position == std::string::npos)
        {
            std::cerr << filename << "ERROR: `yli::load::load_image_file`: filename " << filename << " does not have a dot!\n";
            return nullptr;
        }

        const std::string suffix = std::string(&filename[dot_position]);

        if (suffix == ".png")
        {
            return yli::load::load_png_file(filename, image_loader_struct, image_width, image_height, image_size, n_color_channels);
        }

        return nullptr;
    }
}
