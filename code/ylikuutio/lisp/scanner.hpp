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

#ifndef YLIKUUTIO_LISP_SCANNER_HPP_INCLUDED
#define YLIKUUTIO_LISP_SCANNER_HPP_INCLUDED

#include "token.hpp"
#include "error_log.hpp"
#include "error_type.hpp"
#include "token_list.hpp"
#include "token_type.hpp"
#include "text_position.hpp"

// Include standard headers
#include <cstddef>       // std::size_t
#include <optional>      // std::optional
#include <string_view>   // std::string_view
#include <unordered_set> // std::unordered_set

namespace yli::lisp
{
    class Scanner
    {
        public:
            explicit Scanner(std::string_view input_string);

            const TokenList& get_token_list() const;
            const ErrorLog& get_error_log() const;
            const TextPosition& get_text_position() const;

            bool get_is_success() const;

        private:
            bool scan_tokens();

            std::optional<Token> scan_token();

            void add_error(ErrorType error_type);

            bool get_is_digit_or_dot_or_minus() const;

            const std::unordered_set<char32_t> reserved_codepoints { U'(', U')', U'\'', U';', U' ', U'\r', U'\t', U'\n', U'"' };

            std::string_view string;
            ErrorLog error_log;
            TokenList token_list;
            TextPosition text_position;

            const bool is_success;
    };
}

#endif
