// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2021 Antti Nuortimo.
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

#ifndef __YLIKUUTIO_LOAD_PNG_LOADER_HPP_INCLUDED
#define __YLIKUUTIO_LOAD_PNG_LOADER_HPP_INCLUDED

#include "code/ylikuutio/load/image_loader_struct.hpp"

// Include standard headers
#include <memory>   // std::make_shared, std::shared_ptr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::load
{
    std::shared_ptr<std::vector<uint8_t>> load_png_file(
            const std::string& filename,
            const yli::load::ImageLoaderStruct& image_loader_struct,
            uint32_t& image_width,
            uint32_t& image_height,
            uint32_t& image_size);
}

#endif
