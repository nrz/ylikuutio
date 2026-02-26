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

#ifndef YLIKUUTIO_ONTOLOGY_CONSOLE_STRUCT_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_CONSOLE_STRUCT_HPP_INCLUDED

#include "lisp_context_struct.hpp"
#include "request.hpp"

// Include standard headers
#include <stdint.h> // uint32_t etc.

namespace yli::ontology
{
    class Font2d;

    struct ConsoleStruct : public LispContextStruct
    {
        ConsoleStruct(const uint32_t left_x, const uint32_t right_x, const uint32_t top_y, const uint32_t bottom_y)
        : left_x   { left_x },
        right_x  { right_x },
        top_y  { top_y },
        bottom_y { bottom_y }
        {
        }

        Request<Font2d> font_2d_master {};
        uint32_t left_x;
        uint32_t right_x;
        uint32_t top_y;
        uint32_t bottom_y;
    };
}

#endif
