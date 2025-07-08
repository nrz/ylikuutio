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

#include "ylikuutio_string.hpp"

// Include standard headers
#include <cstddef>     // std::byte, std::size_t
#include <iomanip>     // std::setfill, std::setw
#include <ios>         // std::dec, std::hex
#include <iostream>    // std::cout, std::cerr
#include <stdint.h>    // uint32_t etc.
#include <string>      // std::string
#include <sstream>     // std::stringstream
#include <string_view> // std::string_view

namespace yli::string
{
    void print_hexdump(const std::byte* const start_address, const std::byte* const end_address) // `begin` is inclusive, `end` is exclusive.
    {
        const std::size_t line_width_in_bytes = 16;
        std::size_t characters_on_this_line = 0;
        std::string current_line_ascii = "";
        std::string current_line_hex = "";

        for (const std::byte* data_pointer = start_address; data_pointer < end_address; data_pointer++)
        {
            const uint8_t data_byte = static_cast<uint8_t>(*data_pointer);
            const char data_char = (data_byte >= 0x20 && data_byte <= 0x7f ? static_cast<char>(data_byte) : '.');
            current_line_ascii += data_char;

            const uint32_t data_32_bit = static_cast<uint32_t>(data_byte); // to get the hexadecimal representation instead of the actual value.
            std::stringstream my_stream;
            my_stream << std::setfill('0') << std::setw(2) << std::hex << data_32_bit << std::dec; // std::hex does not work on char values.
            current_line_hex += my_stream.str();
            current_line_hex += " ";

            if (++characters_on_this_line >= line_width_in_bytes)
            {
                std::cout << current_line_hex << " " << current_line_ascii << "\n";
                current_line_hex = "";
                current_line_ascii = "";
                characters_on_this_line = 0;
            }
        }

        if (characters_on_this_line > 0)
        {
            const std::size_t size_of_each_bytes_hexdump = 3; // each byte's hexdump takes 3 characters.
            const std::size_t number_of_spaces_needed = (line_width_in_bytes - characters_on_this_line) * size_of_each_bytes_hexdump + 1;
            std::cout << current_line_hex << std::string(number_of_spaces_needed, ' ') << current_line_ascii << "\n";
        }

        std::cout << "\n";
    }
}
