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

#ifndef YLIKUUTIO_ONTOLOGY_PRINT_CONSOLE_STRUCT_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_PRINT_CONSOLE_STRUCT_HPP_INCLUDED

#include "position_struct.hpp"
#include "code/ylikuutio/console/text_input.hpp"

// Include standard headers
#include <span>     // std::span
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string

namespace yli::ontology
{
    struct PrintConsoleStruct
    {
        PrintConsoleStruct(
                const std::span<const std::string> buffer_text,
                const yli::console::TextInput* const text_input)
            : buffer_text { buffer_text },
            text_input { text_input }
        {
        }

        PositionStruct position;
        uint32_t font_size { 0 };
        uint32_t n_columns { 0 };
        const std::span<const std::string> buffer_text;
        const yli::console::TextInput* const text_input;
        std::string prompt;
    };
}

#endif
