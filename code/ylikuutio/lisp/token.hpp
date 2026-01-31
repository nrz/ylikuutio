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
#include "text_position.hpp"

// Include standard headers
#include <cstddef>     // std::size_t
#include <optional>    // std::nullopt, std::optional
#include <stdint.h>    // int64_t, uint64_t
#include <string>      // std::string
#include <string_view> // std::string_view
#include <variant>     // std::holds_alternative, std::monostate, std::variant

namespace yli::lisp
{
    class Token
    {
        public:
            Token(TokenType type, std::string&& lexeme, const TextPosition& text_position);
            Token(TokenType type, std::string&& lexeme, const TextPosition& text_position, const int64_t value);
            Token(TokenType type, std::string&& lexeme, const TextPosition& text_position, const uint64_t value);
            Token(TokenType type, std::string&& lexeme, const TextPosition& text_position, const double value);

            bool operator==(const Token& other) const; // Equal `Token`s have identical type and identical lexeme.
            bool operator!=(const Token& other) const; // Line numbers may differ.

            TokenType get_type() const;
            void set_type(TokenType new_type);
            std::string_view get_lexeme() const;
            const TextPosition& get_text_position() const;
            std::size_t get_line() const;
            std::size_t get_column() const;

            template<typename T>
                std::optional<T> get_numeric_value() const
                {
                    if (std::holds_alternative<T>(this->numeric_value)) [[likely]]
                    {
                        return std::get<T>(this->numeric_value);
                    }

                    return std::nullopt;
                }

            std::size_t size() const;

        private:
            TokenType type;
            std::string lexeme;
            const TextPosition text_position;
            std::variant<
                std::monostate, // Uninitialized state.
                int64_t,
                uint64_t,
                double> numeric_value;
    };
}

#endif
