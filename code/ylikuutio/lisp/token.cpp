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

#include "token.hpp"
#include "token_type.hpp"

// Include standard headers
#include <cstddef>     // std::size_t
#include <optional>    // std::optional
#include <string_view> // std::u32string_view

namespace yli::lisp
{
    Token::Token(TokenType type, std::u32string_view lexeme)
        : type { type },
        lexeme { lexeme }
    {
    }

    Token::Token(TokenType type, std::u32string_view lexeme, std::optional<std::size_t> line_number)
        : type { type },
        lexeme { lexeme },
        line_number { line_number }
    {
    }

    TokenType Token::get_type() const
    {
        return this->type;
    }

    std::u32string_view Token::get_lexeme() const
    {
        return this->lexeme;
    }

    std::optional<std::size_t> Token::get_line_number() const
    {
        return this->line_number;
    }
}
