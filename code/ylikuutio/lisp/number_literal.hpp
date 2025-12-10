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

#ifndef YLIKUUTIO_LISP_NUMBER_LITERAL_HPP_INCLUDED
#define YLIKUUTIO_LISP_NUMBER_LITERAL_HPP_INCLUDED

#include "token.hpp"

// Include standard headers
#include <optional>      // std::optional
#include <string_view>   // std::string_view
#include <unordered_set> // std::unordered_set

namespace yli::lisp
{
    class TextPosition;
    class ErrorLog;

    std::optional<Token> scan_number_literal(TextPosition& text_position, ErrorLog& error_log, const std::unordered_set<char32_t>& reserved_codepoints);
    std::optional<Token> convert_string_to_value(TextPosition& text_position, ErrorLog& error_log, const std::unordered_set<char32_t>& reserved_codepoints);
}

#endif
