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

#ifndef YLIKUUTIO_LISP_TOKEN_LIST_HPP_INCLUDED
#define YLIKUUTIO_LISP_TOKEN_LIST_HPP_INCLUDED

#include "token.hpp"
#include "token_type.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <string>  // std::string
#include <vector>  // std::vector

namespace yli::lisp
{
    class TokenList
    {
        public:
            void add_token(Token&& token);
            void add_token(TokenType token_type, std::string&& lexeme);

            const Token& at(const std::size_t index) const;

            const std::vector<Token>& data() const;

            bool empty() const;
            std::size_t size() const;

        private:
            std::vector<Token> tokens;
    };
}

#endif
