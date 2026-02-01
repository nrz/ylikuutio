// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2026 Antti Nuortimo.
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

#include "string_literal.hpp"
#include "text_position.hpp"
#include "error_log.hpp"
#include "token.hpp"

// Include standard headers
#include <optional> // std::optional, std::nullopt
#include <utility>  // std::move

namespace yli::lisp
{
    std::optional<Token> scan_string_literal(TextPosition& text_position, ErrorLog& error_log)
    {
        // Read until `"`.
        // `\` is an escape character:
        // `\\` is `\`.
        // `\"` is `"`.
        // `\n` is newline.

        std::string current_string;

        const TextPosition start_position = text_position;
        text_position.next(U'"');

        while (text_position.get_it() != text_position.get_cend())
        {
            std::optional<char32_t> maybe_codepoint = text_position.peek_codepoint();

            if (!maybe_codepoint.has_value()) [[unlikely]]
            {
                error_log.add_error(text_position, ErrorType::INVALID_UNICODE);
                return std::nullopt;
            }

            const char32_t codepoint = maybe_codepoint.value();

            if (codepoint < 0x20) [[unlikely]]
            {
                // Invalid codepoint. Report an error.
                error_log.add_error(text_position, ErrorType::INVALID_CODEPOINT);
            }

            text_position.next(codepoint);

            switch (codepoint)
            {
                case U'"':
                    {
                        // End of string.
                        return Token(TokenType::STRING, std::move(current_string), start_position);
                    }
                case U'\\':
                    {
                        // Escape. Read next codepoint.
                        std::optional<char32_t> maybe_second_codepoint = text_position.scan_codepoint_and_advance();

                        if (!maybe_second_codepoint.has_value())
                        {
                            // Scanning failed.
                            error_log.add_error(text_position, ErrorType::INVALID_UNICODE);
                            return std::nullopt;
                        }

                        const char32_t second_codepoint = maybe_codepoint.value();

                        if (second_codepoint == U'n') [[likely]]
                        {
                            // Newline.
                            current_string.push_back(U'\n');
                        }
                        else if (second_codepoint == U'\\')
                        {
                            // Backslash.
                            current_string.push_back(U'\\');
                        }
                        else if (second_codepoint == U'"')
                        {
                            // Double quote.
                            current_string.push_back(U'"');
                        }
                        else if (second_codepoint == U't')
                        {
                            // Tab.
                            current_string.push_back(U'\t');
                        }
                        else
                        {
                            // ERROR: Invalid character after `\` escape. Report an error.
                            error_log.add_error(text_position, ErrorType::INVALID_ESCAPE_SEQUENCE);
                        }

                        break;
                    }
                default:
                    {
                        // This codepoint is a part of the string. Advance to the next codepoint.
                        current_string.push_back(codepoint);
                    }
            }
        }

        // No closing double quote was found.

        // Invalid codepoint. Report an error with the text position of the opening double parenthesis.
        TextPosition opening_double_quote_position(
                text_position.get_token_start_it(),
                text_position.get_it(),
                text_position.get_offset(),
                text_position.get_line(),
                text_position.get_token_start_it() - text_position.get_cbegin() + 1);
        error_log.add_error(opening_double_quote_position, ErrorType::CLOSING_DOUBLE_QUOTE_MISSING);
        return std::nullopt;
    }
}
