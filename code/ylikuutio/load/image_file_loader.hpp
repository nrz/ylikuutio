// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2026 Antti Nuortimo.
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

#ifndef YLIKUUTIO_LOAD_IMAGE_FILE_LOADER_HPP_INCLUDED
#define YLIKUUTIO_LOAD_IMAGE_FILE_LOADER_HPP_INCLUDED

#include "code/ylikuutio/load/image_loader_struct.hpp"

// Include standard headers
#include <cstdint>  // std::uint8_t, std::uint32_t
#include <memory>   // std::shared_ptr
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::load
{
    std::shared_ptr<std::vector<std::uint8_t>> load_image_file(
            const std::string& filename,
            const yli::load::ImageLoaderStruct& image_loader_struct,
            std::uint32_t& image_width,
            std::uint32_t& image_height,
            std::uint32_t& image_size,
            std::uint32_t& n_color_channels);
}

#endif
