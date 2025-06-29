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

#ifndef YLIKUUTIO_LISP_TOKEN_TYPE_HPP_INCLUDED
#define YLIKUUTIO_LISP_TOKEN_TYPE_HPP_INCLUDED

namespace yli::lisp
{
    enum class TokenType
    {
        // Parentheses.
        LEFT_PARENTHESIS,  // ( ... used in grouping.
        RIGHT_PARENTHESIS, // ) ... used in grouping.
        // Other single-character token types in ASCII order.
        QUOTE,             // ' ... used in quoting.
        DOT,               // . ... used in member access.
        SEMICOLON,         // ; ... used in comments.
        // n-character token types.
        IDENTIFIER,        // Identifiers for function names, and variable names.
        STRING,            // A Unicode string starting and ending with double quotes.
        NUMBER             // Consisting of Arabic numerals (0-9), may contain one dot as well.
    };
}
#endif
