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

std::optional<char32_t> yli::string::read_codepoint(std::string::const_iterator& it, std::string::const_iterator cend)
{
    if (it == cend)
    {
        return std::nullopt;
    }

    // Read a codepoint and advance the iterator.
    // If the codepoint is invalid, return `std::nullopt`.

    const unsigned char byte1 = *it++;

    if (byte1 < 0b1000'0000)
    {
        // ASCII.
        return static_cast<char32_t>(byte1);
    }
    else if (byte1 < 0b1110'0000)
    {
        // 2 bytes.
        if (it == cend)
        {
            return std::nullopt;
        }

        const unsigned char byte2 = *it++;
        if ((byte2 & 0b1100'0000) != 0b1000'0000)
        {
            // Invalid codepoint.
            return std::nullopt;
        }

        const char32_t codepoint = ((static_cast<char32_t>(byte1) & 0b0001'1111) << 6) |
            (static_cast<char32_t>(byte2) & 0b0011'1111);
        return codepoint;
    }
    else if (byte1 < 0b1111'0000)
    {
        // 3 bytes.
        if (it == cend)
        {
            return std::nullopt;
        }

        const unsigned char byte2 = *it++;
        if ((byte2 & 0b1100'0000) != 0b1000'0000)
        {
            // Invalid codepoint.
            return std::nullopt;
        }

        if (it == cend)
        {
            return std::nullopt;
        }

        const unsigned char byte3 = *it++;
        if ((byte3 & 0b1100'0000) != 0b1000'0000)
        {
            // Invalid codepoint.
            return std::nullopt;
        }

        const char32_t codepoint = ((static_cast<char32_t>(byte1) & 0b0000'1111) << 12) |
            ((static_cast<char32_t>(byte2) & 0b0011'1111) << 6) |
            (static_cast<char32_t>(byte3) & 0b0011'1111);
        return codepoint;
    }
    else if (byte1 < 0b1111'1000)
    {
        // 4 bytes.
        if (it == cend)
        {
            return std::nullopt;
        }

        const unsigned char byte2 = *it++;
        if ((byte2 & 0b1100'0000) != 0b1000'0000)
        {
            // Invalid codepoint.
            return std::nullopt;
        }

        if (it == cend)
        {
            return std::nullopt;
        }

        const unsigned char byte3 = *it++;
        if ((byte3 & 0b1100'0000) != 0b1000'0000)
        {
            // Invalid codepoint.
            return std::nullopt;
        }

        if (it == cend)
        {
            return std::nullopt;
        }

        const unsigned char byte4 = *it++;
        if ((byte4 & 0b1100'0000) != 0b1000'0000)
        {
            // Invalid codepoint.
            return std::nullopt;
        }

        const char32_t codepoint = ((static_cast<char32_t>(byte1) & 0b0000'0111) << 18) |
            ((static_cast<char32_t>(byte2) & 0b0011'1111) << 12) |
            ((static_cast<char32_t>(byte3) & 0b0011'1111) << 6) |
            (static_cast<char32_t>(byte4) & 0b0011'1111);
        return codepoint;
    }
    else
    {
        // Invalid codepoint.
        return std::nullopt;
    }
}

std::optional<std::u32string> yli::string::u8_to_u32(const std::string& my_string)
{
    std::u32string u32_string;

    for (std::string::const_iterator it = my_string.cbegin(); it != my_string.cend(); )
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

std::optional<std::string> yli::string::u32_to_u8(const std::u32string& my_string)
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
