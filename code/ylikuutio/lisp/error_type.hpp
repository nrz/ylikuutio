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

#ifndef YLIKUUTIO_LISP_ERROR_TYPE_HPP_INCLUDED
#define YLIKUUTIO_LISP_ERROR_TYPE_HPP_INCLUDED

namespace yli::lisp
{
    enum class ErrorType
    {
        CLOSING_DOUBLE_QUOTE_MISSING,
        INVALID_UNICODE,
        INVALID_CODEPOINT,
        INVALID_ESCAPE_SEQUENCE,
        INVALID_UNSIGNED_INTEGER_LITERAL,
        INVALID_SIGNED_INTEGER_LITERAL,
        INVALID_FLOATING_POINT_LITERAL,
        SYNTAX_ERROR,
        FUNCTION_CALL_EXPECTED,
        MATCHING_LEFT_PARENTHESIS_MISSING,
        MATCHING_RIGHT_PARENTHESIS_MISSING,
        MATCHING_LEFT_SQUARE_BRACKET_MISSING,
        MATCHING_RIGHT_SQUARE_BRACKET_MISSING,
        MATCHING_LEFT_CURLY_BRACE_MISSING,
        MATCHING_RIGHT_CURLY_BRACE_MISSING,
        LEFT_PARENTHESIS_WITH_RIGHT_SQUARE_BRACKET,
        LEFT_PARENTHESIS_WITH_RIGHT_CURLY_BRACE,
        LEFT_SQUARE_BRACKET_WITH_RIGHT_PARENTHESIS,
        LEFT_SQUARE_BRACKET_WITH_RIGHT_CURLY_BRACE,
        LEFT_CURLY_BRACE_WITH_RIGHT_PARENTHESIS,
        LEFT_CURLY_BRACE_WITH_RIGHT_SQUARE_BRACKET,
        EMPTY_PARENTHESIS_BLOCK
    };
}
#endif
