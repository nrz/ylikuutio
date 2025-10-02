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

#ifndef YLIKUUTIO_ONTOLOGY_PRINT_TEXT_STRUCT_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_PRINT_TEXT_STRUCT_HPP_INCLUDED

#include "position_struct.hpp"
#include "texture_file_format.hpp"
#include "code/ylikuutio/console/text_line.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <span>    // std::span
#include <string>  // std::string
#include <variant> // std::variant

namespace yli::ontology
{
    struct PrintTextStruct
    {
        explicit PrintTextStruct(const TextureFileFormat font_texture_file_format)
            : font_texture_file_format { font_texture_file_format }
        {
        }

        PositionStruct position;
        std::size_t font_size     { 0 };
        std::variant<std::string, std::span<const yli::console::TextLine>> text;
        const TextureFileFormat font_texture_file_format;
    };
}

#endif
