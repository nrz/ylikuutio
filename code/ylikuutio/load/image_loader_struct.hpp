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

#ifndef YLIKUUTIO_LOAD_IMAGE_LOADER_STRUCT_HPP_INCLUDED
#define YLIKUUTIO_LOAD_IMAGE_LOADER_STRUCT_HPP_INCLUDED

#include <ofbx.h>

// Include standard headers
#include <utility> // std::pair
#include <vector>  // std::vector

namespace yli::load
{
    enum class ImageLoadingFlags
    {
        SHOULD_CONVERT_GRAYSCALE_TO_RGB,
        SHOULD_DISCARD_ALPHA_CHANNEL,
        SHOULD_FLIP_VERTICALLY
    };

    struct ImageLoaderStruct
    {
        ImageLoaderStruct() = default;

        explicit ImageLoaderStruct(const std::vector<std::pair<yli::load::ImageLoadingFlags, bool>>& values)
        {
            for (const auto& [enum_value, bool_value] : values)
            {
                if (enum_value == yli::load::ImageLoadingFlags::SHOULD_CONVERT_GRAYSCALE_TO_RGB)
                {
                    this->should_convert_grayscale_to_rgb = bool_value;
                }
                else if (enum_value == yli::load::ImageLoadingFlags::SHOULD_DISCARD_ALPHA_CHANNEL)
                {
                    this->should_discard_alpha_channel = bool_value;
                }
                else if (enum_value == yli::load::ImageLoadingFlags::SHOULD_FLIP_VERTICALLY)
                {
                    this->should_flip_vertically = bool_value;
                }
            }
        }

        ofbx::Texture* ofbx_texture          { nullptr };
        bool should_convert_grayscale_to_rgb { false };
        bool should_discard_alpha_channel    { false };
        bool should_flip_vertically          { false };
    };
}

#endif
