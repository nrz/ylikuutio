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

#ifndef YLIKUUTIO_ONTOLOGY_PRINT_CONSOLE_STRUCT_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_PRINT_CONSOLE_STRUCT_HPP_INCLUDED

#include "position_struct.hpp"
#include "code/ylikuutio/console/text_input.hpp"

// Include standard headers
#include <cstdint>  // std::uint32_t
#include <span>     // std::span
#include <string>   // std::string

namespace yli::ontology
{
    struct PrintConsoleStruct
    {
        PrintConsoleStruct(
                const std::span<const std::string> buffer_text,
                const yli::console::TextInput* const text_input,
                const std::uint32_t font_size,
                const std::uint32_t n_columns)
            : buffer_text { buffer_text },
            text_input { text_input },
            font_size { font_size },
            n_columns { n_columns }
        {
        }

        const std::span<const std::string> buffer_text;
        const yli::console::TextInput* const text_input;
        std::string prompt;
        PositionStruct position;
        std::uint32_t font_size;
        std::uint32_t n_columns;
    };
}

#endif
