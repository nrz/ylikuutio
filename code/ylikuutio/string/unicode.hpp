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

#ifndef YLIKUUTIO_STRING_UNICODE_HPP_INCLUDED
#define YLIKUUTIO_STRING_UNICODE_HPP_INCLUDED

// Include standard headers
#include <optional> // std::optional
#include <string>   // std::string, std::u32string

namespace yli::string
{
    std::optional<char32_t> read_codepoint(std::string::const_iterator& it, std::string::const_iterator end);
    std::optional<std::u32string> u8_to_u32(const std::string& my_string);
    std::optional<std::string> u32_to_u8(const std::u32string& my_string);
}

#endif
