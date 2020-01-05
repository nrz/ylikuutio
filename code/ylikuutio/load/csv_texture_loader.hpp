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

#ifndef __CSV_TEXTURE_LOADER_HPP_INCLUDED
#define __CSV_TEXTURE_LOADER_HPP_INCLUDED

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <cstddef>  // std::size_t
#include <memory>   // std::make_shared, std::shared_ptr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string

namespace yli
{
    namespace common
    {
        class AnyValue;
    }

    namespace load
    {
        // Load a .CSV file using our custom loader.
        // Insert elementes of `left_filler_vector_any_value` to the left side of each element,
        // and elementes of `right_filler_vector_any_value` to the right side of each element.
        bool load_CSV_texture(
                const std::string& filename,
                const GLenum format,
                const GLenum internal_format,
                const GLenum type,
                const std::shared_ptr<yli::common::AnyValue> left_filler_vector_any_value,
                const std::shared_ptr<yli::common::AnyValue> right_filler_vector_any_value,
                std::size_t& image_width,
                std::size_t& image_height,
                std::size_t& image_size,
                uint32_t& textureID);

        // Load a .CSV file using our custom loader.
        bool load_CSV_texture(
                const std::string& filename,
                const GLenum format,
                const GLenum internal_format,
                const GLenum type,
                std::size_t& image_width,
                std::size_t& image_height,
                std::size_t& image_size,
                uint32_t& textureID);
    }
}

#endif
