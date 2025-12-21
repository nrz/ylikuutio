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

#include "scanner.hpp"
#include "error_type.hpp"
#include "token.hpp"
#include "token_type.hpp"
#include "identifier.hpp"
#include "number_literal.hpp"
#include "string_literal.hpp"
#include "code/ylikuutio/string/unicode.hpp"

// Include standard headers
#include <cstddef>     // std::size_t
#include <optional>    // std::optional, std::nullopt
#include <string_view> // std::string_view
#include <utility>     // std::move
#include <vector>      // std::vector

namespace yli::lisp
{
    class TokenList;
    class ErrorLog;

    Scanner::Scanner(std::string_view input_string)
        : string { input_string },
        text_position { this->string.cbegin(), this->string.cend() },
        is_success { this->scan_tokens() }
    {
    }

    const TokenList& Scanner::get_token_list() const
    {
        return this->token_list;
    }

    const ErrorLog& Scanner::get_error_log() const
    {
        return this->error_log;
    }

    const TextPosition& Scanner::get_text_position() const
    {
        return this->text_position;
    }

    bool Scanner::get_is_success() const
    {
        return this->is_success;
    }

    bool Scanner::scan_tokens()
    {
        while (this->text_position.get_it() != this->string.cend())
        {
            this->text_position.advance_to_next_token();

            std::optional<Token> maybe_token = this->scan_token();

            if (maybe_token.has_value())
            {
                Token token = maybe_token.value();
                this->token_list.add_token(std::move(token));
            }
        }

        if (this->error_log.empty())
        {
            return true; // Scanning successful.
        }

        return false; // Scanning failed.
    }

    std::optional<Token> Scanner::scan_token()
    {
        while (this->text_position.get_it() != this->text_position.get_cend())
        {
            std::optional<char32_t> maybe_codepoint = this->text_position.peek_codepoint();

            if (!maybe_codepoint.has_value())
            {
                // Scanning failed. End scanning now.
                this->add_error(ErrorType::INVALID_UNICODE);
                return std::nullopt;
            }

            const char32_t codepoint = maybe_codepoint.value();

            switch (codepoint)
            {
                case U'(':
                    {
                        // Left parenthesis is a token on its own, used for grouping.
                        return Token(TokenType::LEFT_PARENTHESIS, std::string(this->text_position.get_token_start_it(), this->text_position.next(codepoint)));
                    }
                case U')':
                    {
                        // Right parenthesis is a token on its own, used for grouping.
                        return Token(TokenType::RIGHT_PARENTHESIS, std::string(this->text_position.get_token_start_it(), this->text_position.next(codepoint)));
                    }
                case U'\'':
                    {
                        // Quote is a token on its own, used for quoting.
                        return Token(TokenType::QUOTE, std::string(this->text_position.get_token_start_it(), this->text_position.next(codepoint)));
                    }
                case U'.':
                    {
                        // Dot is a token on its own, used for member access.
                        return Token(TokenType::DOT, std::string(this->text_position.get_token_start_it(), this->text_position.next(codepoint)));
                    }
                case U';':
                    {
                        // Beginning of a comment. Scan until newline.
                        while (this->text_position.get_it() != this->string.cend())
                        {
                            std::optional<char32_t> maybe_codepoint = this->text_position.scan_codepoint_and_advance();

                            if (!maybe_codepoint.has_value()) [[unlikely]]
                            {
                                this->add_error(ErrorType::INVALID_UNICODE);
                                break;
                            }

                            if (maybe_codepoint.value() == U'\n')
                            {
                                break;
                            }
                        }

                        break;
                    }
                case U' ':
                case U'\r':
                case U'\t':
                    {
                        // Ignore whitespace.
                        this->text_position.next(codepoint);
                        this->text_position.advance_to_next_token();
                        break;
                    }
                case U'\n':
                    {
                        // Next line.
                        this->text_position.next(codepoint);
                        break;
                    }
                case U'"':
                    {
                        this->text_position.next(codepoint);
                        std::optional<Token> maybe_token = yli::lisp::scan_string_literal(this->text_position, this->error_log);

                        if (maybe_token.has_value()) [[likely]]
                        {
                            Token token = maybe_token.value();
                            return Token(std::move(token));
                        }

                        return std::nullopt;
                    }
                default:
                    {
                        if (codepoint < 0x20) [[unlikely]]
                        {
                            // Codepoints below 0x20 (32) except the ones already processed are invalid in YliLisp.
                            this->add_error(ErrorType::INVALID_CODEPOINT);
                            this->text_position.next(codepoint);
                            this->text_position.advance_to_next_token();
                            return std::nullopt;
                        }
                        else if (this->get_is_digit_or_dot_or_minus())
                        {
                            // Number literal.
                            std::optional<Token> maybe_token = yli::lisp::scan_number_literal(this->text_position, this->error_log, this->reserved_codepoints);

                            if (maybe_token.has_value()) [[likely]]
                            {
                                Token token = maybe_token.value();
                                return Token(std::move(token));
                            }

                            return std::nullopt;
                        }
                        else [[likely]]
                        {
                            // Identifier.
                            std::optional<Token> maybe_token = yli::lisp::scan_identifier(this->text_position, this->error_log, this->reserved_codepoints);

                            if (maybe_token.has_value()) [[likely]]
                            {
                                Token token = maybe_token.value();
                                return Token(std::move(token));
                            }

                            return std::nullopt;
                        }

                        break;
                    }
            }
        }

        return std::nullopt;
    }

    void Scanner::add_error(ErrorType error_type)
    {
        this->error_log.add_error(this->text_position, error_type);
    }

    bool Scanner::get_is_digit_or_dot_or_minus() const
    {
        std::optional<char32_t> maybe_codepoint = yli::string::peek_codepoint(this->text_position.get_it(), this->string.cend());

        return maybe_codepoint.has_value() && (
                (maybe_codepoint.value() >= U'0' && maybe_codepoint.value() <= U'9') ||
                (maybe_codepoint.value() == U'.') ||
                (maybe_codepoint.value() == U'-'));
    }
}
