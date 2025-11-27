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

#include "unicode.hpp"

// Include standard headers
#include <optional> // std::optional
#include <string>   // std::string, std::u32string
#include <string_view> // std::string_view, std::u32string_view

std::optional<char32_t> yli::string::read_codepoint(std::string_view::const_iterator& it, std::string_view::const_iterator cend)
{
    return read_or_peek_codepoint(it, cend);
}

std::optional<char32_t> yli::string::peek_codepoint(std::string_view::const_iterator it, std::string_view::const_iterator cend)
{
    return read_or_peek_codepoint(it, cend);
}

std::optional<std::u32string> yli::string::u8_to_u32(std::string_view my_string)
{
    std::u32string u32_string;

    for (std::string_view::const_iterator it = my_string.cbegin(); it != my_string.cend(); )
    {
        std::optional<char32_t> codepoint = read_codepoint(it, my_string.cend());

        if (codepoint.has_value())
        {
            u32_string.push_back(static_cast<char32_t>(codepoint.value()));
        }
        else
        {
            return std::nullopt;
        }
    }

    return u32_string;
}

std::optional<std::string> yli::string::u32_to_u8(std::u32string_view my_string)
{
    std::string u8_string;

    for (const char32_t u32_codepoint : my_string)
    {
        if (u32_codepoint <= 0x7f)
        {
            // ASCII.
            u8_string.push_back(static_cast<char>(u32_codepoint));
        }
        else if (u32_codepoint <= 0x7ff)
        {
            // 2 bytes.
            u8_string.push_back(static_cast<char>(0b1100'0000 | (u32_codepoint >> 6)));
            u8_string.push_back(static_cast<char>(0b1000'0000 | (u32_codepoint & 0b0011'1111)));
        }
        else if (u32_codepoint <= 0xd7ff)
        {
            // 3 bytes.
            u8_string.push_back(static_cast<char>(0b1110'0000 | (u32_codepoint >> 12)));
            u8_string.push_back(static_cast<char>(0b1000'0000 | ((u32_codepoint >> 6) & 0b0011'1111)));
            u8_string.push_back(static_cast<char>(0b1000'0000 | (u32_codepoint & 0b0011'1111)));
        }
        else if (u32_codepoint < 0xe000)
        {
            // Invalid codepoint.
            return std::nullopt;
        }
        else if (u32_codepoint <= 0xffff)
        {
            // 3 bytes.
            u8_string.push_back(static_cast<char>(0b1110'0000 | (u32_codepoint >> 12)));
            u8_string.push_back(static_cast<char>(0b1000'0000 | ((u32_codepoint >> 6) & 0b0011'1111)));
            u8_string.push_back(static_cast<char>(0b1000'0000 | (u32_codepoint & 0b0011'1111)));
        }
        else if (u32_codepoint <= 0x10ffff)
        {
            // 4 bytes.
            u8_string.push_back(static_cast<char>(0b1111'0000 | (u32_codepoint >> 18)));
            u8_string.push_back(static_cast<char>(0b1000'0000 | ((u32_codepoint >> 12) & 0b0011'1111)));
            u8_string.push_back(static_cast<char>(0b1000'0000 | ((u32_codepoint >> 6) & 0b0011'1111)));
            u8_string.push_back(static_cast<char>(0b1000'0000 | (u32_codepoint & 0b0011'1111)));
        }
        else
        {
            // Invalid codepoint.
            return std::nullopt;
        }
    }

    return u8_string;
}
