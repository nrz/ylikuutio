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
#include <string_view> // std::string_view
#include <utility>     // std::move

namespace yli::lisp
{
    Token::Token(TokenType type, std::string&& lexeme)
        : type { type },
        lexeme { std::move(lexeme) }
    {
    }

    Token::Token(TokenType type, std::string&& lexeme, std::optional<std::size_t> line_number)
        : type { type },
        lexeme { std::move(lexeme) },
        line_number { line_number }
    {
    }

    bool Token::operator==(const Token& other) const
    {
        // Equal `Token`s have identical type and identical lexeme.
        // Line numbers may differ.
        return this->type == other.type && this->lexeme == other.lexeme;
    }

    bool Token::operator!=(const Token& other) const
    {
        return !this->operator==(other);
    }

    TokenType Token::get_type() const
    {
        return this->type;
    }

    std::string_view Token::get_lexeme() const
    {
        return this->lexeme;
    }

    std::optional<std::size_t> Token::get_line_number() const
    {
        return this->line_number;
    }
}
