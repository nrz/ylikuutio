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

#include "number_literal.hpp"
#include "text_position.hpp"
#include "error_log.hpp"
#include "token.hpp"
#include "code/ylikuutio/string/ylikuutio_string.hpp"

// Include standard headers
#include <optional>      // std::optional, std::nullopt
#include <stdint.h>      // int64_t
#include <string>        // std::string
#include <string_view>   // std::string_view
#include <unordered_set> // std::unordered_set

namespace yli::lisp
{
    std::optional<Token> scan_number_literal(TextPosition& text_position, ErrorLog& error_log, const std::unordered_set<char32_t>& reserved_codepoints)
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
                // Reserved codepoint. End of number literal.
                return convert_string_to_value(text_position, error_log, reserved_codepoints);
            }

            text_position.next(codepoint);
        }

        // End of source. End of number literal.
        return convert_string_to_value(text_position, error_log, reserved_codepoints);
    }

    std::optional<Token> convert_string_to_value(TextPosition& text_position, ErrorLog& error_log, const std::unordered_set<char32_t>& reserved_codepoints)
    {
        if (const bool is_uint64_t_string = yli::string::check_if_unsigned_integer_string(std::string_view(text_position.get_token_start_it(), text_position.get_it()));
                is_uint64_t_string)
        {
            // OK, so this is a unsigned integer string.
            std::optional<uint64_t> maybe_uint64_t = yli::string::convert_string_to_value<uint64_t>(
                    std::string_view(text_position.get_token_start_it(), text_position.get_it()));

            if (maybe_uint64_t.has_value()) [[likely]]
            {
                return Token(
                        TokenType::UNSIGNED_INTEGER,
                        std::string(text_position.get_token_start_it(), text_position.get_it()),
                        std::nullopt,
                        maybe_uint64_t.value());
            }

            error_log.add_error(text_position);
            return std::nullopt;
        }
        else if (const bool is_int64_t_string = yli::string::check_if_signed_integer_string(std::string_view(text_position.get_token_start_it(), text_position.get_it()));
                is_int64_t_string)
        {
            // OK, so this is a signed integer string.
            std::optional<int64_t> maybe_int64_t = yli::string::convert_string_to_value<int64_t>(
                    std::string_view(text_position.get_token_start_it(), text_position.get_it()));

            if (maybe_int64_t.has_value()) [[likely]]
            {
                return Token(
                        TokenType::SIGNED_INTEGER,
                        std::string(text_position.get_token_start_it(), text_position.get_it()),
                        std::nullopt,
                        maybe_int64_t.value());
            }

            error_log.add_error(text_position);
            return std::nullopt;
        }
        else if (const bool is_double_string = yli::string::check_if_double_string(std::string_view(text_position.get_token_start_it(), text_position.get_it()));
                is_double_string)
        {
            // OK, this is a floating point string that can fit in IEEE-754 double precision variable (`double` in C++).
            std::optional<double> maybe_double = yli::string::convert_string_to_value<double>(
                    std::string_view(text_position.get_token_start_it(), text_position.get_it()));

            if (maybe_double.has_value()) [[likely]]
            {
                return Token(
                        TokenType::FLOATING_POINT,
                        std::string(text_position.get_token_start_it(), text_position.get_it()),
                        std::nullopt,
                        maybe_double.value());
            }

            error_log.add_error(text_position);
            return std::nullopt;
        }

        error_log.add_error(text_position);
        return std::nullopt;
    }
}
