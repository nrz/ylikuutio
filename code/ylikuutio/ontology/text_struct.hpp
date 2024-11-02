// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2024 Antti Nuortimo.
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

#ifndef YLIKUUTIO_ONTOLOGY_TEXT_STRUCT_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_TEXT_STRUCT_HPP_INCLUDED

#include "entity_struct.hpp"
#include "request.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <string>  // std::string
#include <utility> // std::move

namespace yli::ontology
{
    class Font2d;

    struct TextStruct : public EntityStruct
    {
        TextStruct() = default;

        explicit TextStruct(Request<Font2d>&& font_2d_parent)
            : font_2d_parent { std::move(font_2d_parent) }
        {
        }

        Request<Font2d> font_2d_parent {};
        std::size_t screen_width  { 0 };
        std::size_t screen_height { 0 };
        std::size_t x             { 0 };
        std::size_t y             { 0 };
        std::size_t text_size     { 0 };
        std::size_t font_size     { 0 };
        std::string text;
        std::string font_texture_file_format;
        std::string horizontal_alignment;
        std::string vertical_alignment;
    };
}

#endif
