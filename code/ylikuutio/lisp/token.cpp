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
#include <stdint.h>    // int64_t, uint64_t
#include <string_view> // std::string_view
#include <utility>     // std::move

namespace yli::lisp
{
    class TextPosition;

    Token::Token(TokenType type, std::string&& lexeme, const TextPosition& text_position)
        : type      { type },
        lexeme      { std::move(lexeme) },
        text_position { text_position }
    {
    }

    Token::Token(TokenType type, std::string&& lexeme, const TextPosition& text_position, const int64_t value)
        : type      { type },
        lexeme      { std::move(lexeme) },
        text_position { text_position },
        numeric_value { value }
    {
    }

    Token::Token(TokenType type, std::string&& lexeme, const TextPosition& text_position, const uint64_t value)
        : type        { type },
        lexeme        { std::move(lexeme) },
        text_position { text_position },
        numeric_value { value }
    {
    }

    Token::Token(TokenType type, std::string&& lexeme, const TextPosition& text_position, const double value)
        : type        { type },
        lexeme        { std::move(lexeme) },
        text_position { text_position },
        numeric_value { value }
    {
    }

    bool Token::operator==(const Token& other) const
    {
        // Equal `Token`s have identical type and identical lexeme.
        // Line numbers may differ.
        return this->type == other.type && this->lexeme == other.lexeme && this->numeric_value == other.numeric_value;
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

    const TextPosition& Token::get_text_position() const
    {
        return this->text_position;
    }

    std::size_t Token::get_line() const
    {
        return this->text_position.get_line();
    }

    std::size_t Token::get_column() const
    {
        return this->text_position.get_column();
    }

    std::size_t Token::size() const
    {
        return this->lexeme.size();
    }
}
