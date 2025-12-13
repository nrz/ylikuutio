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

#include "identifier.hpp"
#include "text_position.hpp"
#include "error_log.hpp"
#include "token.hpp"

// Include standard headers
#include <optional>      // std::optional, std::nullopt
#include <string>        // std::string
#include <unordered_set> // std::unordered_set
#include <utility>       // std::move

namespace yli::lisp
{
    std::optional<Token> scan_identifier(TextPosition& text_position, ErrorLog& error_log, const std::unordered_set<char32_t>& reserved_codepoints)
    {
        while (text_position.get_it() != text_position.get_cend())
        {
            std::optional<char32_t> maybe_codepoint = text_position.peek_codepoint();

            if (!maybe_codepoint.has_value()) [[unlikely]]
            {
                error_log.add_error(text_position);
                return std::nullopt;
            }

            const char32_t codepoint = maybe_codepoint.value();

            if (reserved_codepoints.contains(codepoint) || codepoint < 0x20) [[unlikely]]
            {
                // Reserved codepoint. End of identifier.
                std::string identifier_string(text_position.get_token_start_it(), text_position.get_it());
                return Token(TokenType::IDENTIFIER, std::move(identifier_string));
            }

            text_position.next(codepoint);
        }

        // End of source. End of identifier.
        std::string identifier_string(text_position.get_token_start_it(), text_position.get_it());
        return Token(TokenType::IDENTIFIER, std::move(identifier_string));
    }
}
