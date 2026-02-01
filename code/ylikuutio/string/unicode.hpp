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

#ifndef YLIKUUTIO_STRING_UNICODE_HPP_INCLUDED
#define YLIKUUTIO_STRING_UNICODE_HPP_INCLUDED

// Include standard headers
#include <optional> // std::optional
#include <string>   // std::string, std::u32string
#include <string_view> // std::string_view, std::u32string_view

namespace yli::string
{
    std::optional<char32_t> read_codepoint(std::string_view::const_iterator& it, std::string_view::const_iterator cend);
    std::optional<char32_t> peek_codepoint(std::string_view::const_iterator it, std::string_view::const_iterator cend);
    std::optional<std::u32string> u8_to_u32(std::string_view my_string);
    std::optional<std::string> u32_to_u8(std::u32string_view my_string);

    template<typename StringIteratorType>
        std::optional<char32_t> read_or_peek_codepoint(StringIteratorType& it, StringIteratorType cend)
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
}

#endif
