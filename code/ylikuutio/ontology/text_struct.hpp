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

#ifndef __YLIKUUTIO_ONTOLOGY_TEXT_STRUCT_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_TEXT_STRUCT_HPP_INCLUDED

#include "entity_struct.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <string>  // std::string

namespace yli::ontology
{
    class Font2D;

    struct TextStruct: public yli::ontology::EntityStruct
    {
        TextStruct()
            : font2D_parent(nullptr),
            screen_width(0),
            screen_height(0),
            x(0),
            y(0),
            text_size(0),
            font_size(0)
        {
            // constructor.
        }

        yli::ontology::Font2D* font2D_parent;
        std::size_t screen_width;
        std::size_t screen_height;
        std::size_t x;
        std::size_t y;
        std::size_t text_size;
        std::size_t font_size;
        std::string text;
        std::string font_texture_file_format;
        std::string horizontal_alignment;
        std::string vertical_alignment;
    };
}

#endif
