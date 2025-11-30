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

#ifndef YLIKUUTIO_LISP_TOKEN_HPP_INCLUDED
#define YLIKUUTIO_LISP_TOKEN_HPP_INCLUDED

#include "token_type.hpp"

// Include standard headers
#include <cstddef>     // std::size_t
#include <optional>    // std::optional
#include <string>      // std::string
#include <string_view> // std::string_view

namespace yli::lisp
{
    class Token
    {
        public:
            Token(TokenType type, std::string&& lexeme);
            Token(TokenType type, std::string&& lexeme, std::optional<std::size_t> line_number);

            bool operator==(const Token& other) const; // Equal `Token`s have identical type and identical lexeme.
            bool operator!=(const Token& other) const; // Line numbers may differ.

            TokenType get_type() const;
            std::string_view get_lexeme() const;
            std::optional<std::size_t> get_line_number() const;

        private:
            TokenType type;
            std::string lexeme;

            std::optional<std::size_t> line_number;
    };
}

#endif
