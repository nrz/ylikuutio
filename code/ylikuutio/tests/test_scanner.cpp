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

#include "gtest/gtest.h"
#include "code/ylikuutio/lisp/scanner.hpp"
#include "code/ylikuutio/lisp/error_log.hpp"
#include "code/ylikuutio/lisp/error.hpp"
#include "code/ylikuutio/lisp/error_type.hpp"
#include "code/ylikuutio/lisp/token_list.hpp"
#include "code/ylikuutio/lisp/token.hpp"
#include "code/ylikuutio/lisp/token_type.hpp"
#include "code/ylikuutio/lisp/text_position.hpp"

// Include standard headers
#include <optional> // std::nullopt, std::optional
#include <string_view> // std::string_view
#include <utility>  // std::move
#include <vector>   // std::vector

using yli::lisp::Scanner;
using yli::lisp::ErrorLog;
using yli::lisp::Error;
using yli::lisp::ErrorType;
using yli::lisp::TokenList;
using yli::lisp::Token;
using yli::lisp::TokenType;
using yli::lisp::TextPosition;

// Successful scans.

TEST(string_must_be_scanned_appropriately, empty_string)
{
    const std::string_view empty_string { "" };
    const Scanner scanner(empty_string);
    ASSERT_TRUE(scanner.get_is_success());
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_TRUE(token_list.empty());
    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_TRUE(error_log.empty());
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);   // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), 1); // 1 is the leftmost column and for empty input it is already past end.
}

TEST(string_must_be_scanned_appropriately, left_parenthesis)
{
    std::string_view left_parenthesis_string { "(" };
    const Scanner scanner(left_parenthesis_string);
    ASSERT_TRUE(scanner.get_is_success());
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_EQ(token_list.size(), 1);

    {
        TextPosition text_position(left_parenthesis_string.cbegin(), left_parenthesis_string.cend());
        ASSERT_EQ(token_list.at(0), Token(TokenType::LEFT_PARENTHESIS, "(", text_position));
        ASSERT_EQ(token_list.at(0).get_line(), 1);
        ASSERT_EQ(token_list.at(0).get_column(), 1);
    }

    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_TRUE(error_log.empty());
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);   // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), 2); // 2 is past end here.
}

TEST(string_must_be_scanned_appropriately, right_parenthesis)
{
    const std::string_view right_parenthesis_string { ")" };
    const Scanner scanner(right_parenthesis_string);
    ASSERT_TRUE(scanner.get_is_success());
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_EQ(token_list.size(), 1);

    {
        TextPosition text_position(right_parenthesis_string.cbegin(), right_parenthesis_string.cend());
        ASSERT_EQ(token_list.at(0), Token(TokenType::RIGHT_PARENTHESIS, ")", text_position));
        ASSERT_EQ(token_list.at(0).get_line(), 1);
        ASSERT_EQ(token_list.at(0).get_column(), 1);
    }

    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_TRUE(error_log.empty());
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);   // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), 2); // 2 is past end here.
}

TEST(string_must_be_scanned_appropriately, left_square_bracket)
{
    std::string_view left_square_bracket_string { "[" };
    const Scanner scanner(left_square_bracket_string);
    ASSERT_TRUE(scanner.get_is_success());
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_EQ(token_list.size(), 1);

    {
        TextPosition text_position(left_square_bracket_string.cbegin(), left_square_bracket_string.cend());
        ASSERT_EQ(token_list.at(0), Token(TokenType::LEFT_SQUARE_BRACKET, "[", text_position));
        ASSERT_EQ(token_list.at(0).get_line(), 1);
        ASSERT_EQ(token_list.at(0).get_column(), 1);
    }

    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_TRUE(error_log.empty());
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);   // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), 2); // 2 is past end here.
}

TEST(string_must_be_scanned_appropriately, right_square_bracket)
{
    const std::string_view right_square_bracket_string { "]" };
    const Scanner scanner(right_square_bracket_string);
    ASSERT_TRUE(scanner.get_is_success());
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_EQ(token_list.size(), 1);

    {
        TextPosition text_position(right_square_bracket_string.cbegin(), right_square_bracket_string.cend());
        ASSERT_EQ(token_list.at(0), Token(TokenType::RIGHT_SQUARE_BRACKET, "]", text_position));
        ASSERT_EQ(token_list.at(0).get_line(), 1);
        ASSERT_EQ(token_list.at(0).get_column(), 1);
    }

    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_TRUE(error_log.empty());
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);   // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), 2); // 2 is past end here.
}

TEST(string_must_be_scanned_appropriately, left_curly_brace)
{
    std::string_view left_curly_brace_string { "{" };
    const Scanner scanner(left_curly_brace_string);
    ASSERT_TRUE(scanner.get_is_success());
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_EQ(token_list.size(), 1);

    {
        TextPosition text_position(left_curly_brace_string.cbegin(), left_curly_brace_string.cend());
        ASSERT_EQ(token_list.at(0), Token(TokenType::LEFT_CURLY_BRACE, "{", text_position));
        ASSERT_EQ(token_list.at(0).get_line(), 1);
        ASSERT_EQ(token_list.at(0).get_column(), 1);
    }

    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_TRUE(error_log.empty());
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);   // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), 2); // 2 is past end here.
}

TEST(string_must_be_scanned_appropriately, right_curly_brace)
{
    const std::string_view right_curly_brace_string { "}" };
    const Scanner scanner(right_curly_brace_string);
    ASSERT_TRUE(scanner.get_is_success());
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_EQ(token_list.size(), 1);

    {
        TextPosition text_position(right_curly_brace_string.cbegin(), right_curly_brace_string.cend());
        ASSERT_EQ(token_list.at(0), Token(TokenType::RIGHT_CURLY_BRACE, "}", text_position));
        ASSERT_EQ(token_list.at(0).get_line(), 1);
        ASSERT_EQ(token_list.at(0).get_column(), 1);
    }

    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_TRUE(error_log.empty());
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);   // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), 2); // 2 is past end here.
}

TEST(string_must_be_scanned_appropriately, quote)
{
    const std::string_view quote_string { "'" };
    const Scanner scanner(quote_string);
    ASSERT_TRUE(scanner.get_is_success());
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_EQ(token_list.size(), 1);

    {
        TextPosition text_position(quote_string.cbegin(), quote_string.cend());
        ASSERT_EQ(token_list.at(0), Token(TokenType::QUOTE, "'", text_position));
        ASSERT_EQ(token_list.at(0).get_line(), 1);
        ASSERT_EQ(token_list.at(0).get_column(), 1);
    }

    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_TRUE(error_log.empty());
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);   // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), 2); // 2 is past end here.
}

TEST(string_must_be_scanned_appropriately, dot)
{
    const std::string_view dot_string { "." };
    const Scanner scanner(dot_string);
    ASSERT_TRUE(scanner.get_is_success());
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_EQ(token_list.size(), 1);

    {
        TextPosition text_position(dot_string.cbegin(), dot_string.cend());
        ASSERT_EQ(token_list.at(0), Token(TokenType::DOT, ".", text_position));
        ASSERT_EQ(token_list.at(0).get_line(), 1);
        ASSERT_EQ(token_list.at(0).get_column(), 1);
    }

    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_TRUE(error_log.empty());
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);   // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), 2); // 2 is past end here.
}

TEST(string_must_be_scanned_appropriately, semicolon)
{
    const std::string_view semicolon_string { ";" };
    const Scanner scanner(semicolon_string);
    ASSERT_TRUE(scanner.get_is_success());
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_TRUE(token_list.empty());
    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_TRUE(error_log.empty());
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);   // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), 2); // 2 is past end here.
}

TEST(string_must_be_scanned_appropriately, space)
{
    const std::string_view space_string { " " };
    const Scanner scanner(space_string);
    ASSERT_TRUE(scanner.get_is_success());
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_TRUE(token_list.empty());
    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_TRUE(error_log.empty());
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);   // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), 2); // 2 is past end here.
}

TEST(string_must_be_scanned_appropriately, carriage_return)
{
    const std::string_view carriage_return_string { "\r" };
    const Scanner scanner(carriage_return_string);
    ASSERT_TRUE(scanner.get_is_success());
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_TRUE(token_list.empty());
    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_TRUE(error_log.empty());
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);   // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), 2); // 2 is past end here.
}

TEST(string_must_be_scanned_appropriately, tab)
{
    const std::string_view tab_string { "\t" };
    const Scanner scanner(tab_string);
    ASSERT_TRUE(scanner.get_is_success());
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_TRUE(token_list.empty());
    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_TRUE(error_log.empty());
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);   // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), 2); // 2 is past end here.
}

TEST(string_must_be_scanned_appropriately, newline)
{
    const std::string_view newline_string { "\n" };
    const Scanner scanner(newline_string);
    ASSERT_TRUE(scanner.get_is_success());
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_TRUE(token_list.empty());
    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_TRUE(error_log.empty());
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 2);   // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), 1); // 2 is past end here.
}

TEST(string_must_be_scanned_appropriately, foo_string_literal)
{
    const std::string_view foo_string { R"("foo")" };
    const Scanner scanner(foo_string);
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_EQ(token_list.size(), 1);

    {
        TextPosition text_position(foo_string.cbegin(), foo_string.cend());
        ASSERT_EQ(token_list.at(0), Token(TokenType::STRING, "foo", text_position));
        ASSERT_EQ(token_list.at(0).get_line(), 1);
        ASSERT_EQ(token_list.at(0).get_column(), 1);
    }

    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_TRUE(error_log.empty());
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);   // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), 6); // 6 is past end here.
}

TEST(string_must_be_scanned_appropriately, backslash_backslash)
{
    const std::string_view backslash_backslash_string { R"("\\")" };
    const Scanner scanner(backslash_backslash_string);
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_EQ(token_list.size(), 1);

    {
        TextPosition text_position(backslash_backslash_string.cbegin(), backslash_backslash_string.cend());
        ASSERT_EQ(token_list.at(0), Token(TokenType::STRING, R"(\)", text_position));
        ASSERT_EQ(token_list.at(0).get_line(), 1);
        ASSERT_EQ(token_list.at(0).get_column(), 1);
    }

    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_TRUE(error_log.empty());
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);   // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), 5); // 5 is past end here.
}

TEST(string_must_be_scanned_appropriately, foo_bar_string_literals)
{
    const std::string_view foo_bar_string { R"("foo" "bar")" };
    const Scanner scanner(foo_bar_string);
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_EQ(token_list.size(), 2);

    {
        TextPosition text_position(foo_bar_string.cbegin(), foo_bar_string.cend());
        ASSERT_EQ(token_list.at(0), Token(TokenType::STRING, "foo", text_position));
        ASSERT_EQ(token_list.at(0).get_line(), 1);
        ASSERT_EQ(token_list.at(0).get_column(), 1);
    }
    {
        TextPosition text_position(foo_bar_string.cbegin(), foo_bar_string.cend());
        ASSERT_EQ(token_list.at(1), Token(TokenType::STRING, "bar", text_position));
        ASSERT_EQ(token_list.at(1).get_line(), 1);
        ASSERT_EQ(token_list.at(1).get_column(), 7);
    }

    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_TRUE(error_log.empty());
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);    // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), 12); // 12 is past end here.
}

TEST(integer_literal_must_be_scanned_appropriately, integer_literal_0)
{
    const std::string_view integer_literal_0_string { "0" };
    const yli::lisp::Scanner scanner(integer_literal_0_string);
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_EQ(token_list.size(), 1);

    {
        TextPosition text_position(integer_literal_0_string.cbegin(), integer_literal_0_string.cend());
        ASSERT_EQ(token_list.at(0), Token(TokenType::UNSIGNED_INTEGER, "0", text_position, static_cast<uint64_t>(0)));
        ASSERT_EQ(token_list.at(0).get_line(), 1);
        ASSERT_EQ(token_list.at(0).get_column(), 1);
    }

    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_TRUE(error_log.empty());
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);   // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), 2); // 2 is past end here.
}

TEST(integer_literal_must_be_scanned_appropriately, integer_literal_1)
{
    const std::string_view integer_literal_1_string { "1" };
    const yli::lisp::Scanner scanner(integer_literal_1_string);
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_EQ(token_list.size(), 1);

    {
        TextPosition text_position(integer_literal_1_string.cbegin(), integer_literal_1_string.cend());
        ASSERT_EQ(token_list.at(0), Token(TokenType::UNSIGNED_INTEGER, "1", text_position, static_cast<uint64_t>(1)));
        ASSERT_EQ(token_list.at(0).get_line(), 1);
        ASSERT_EQ(token_list.at(0).get_column(), 1);
    }

    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_TRUE(error_log.empty());
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);   // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), 2); // 2 is past end here.
}

TEST(integer_literal_must_be_scanned_appropriately, integer_literal_minus_1)
{
    const std::string_view integer_literal_minus_1_string { "-1" };
    const yli::lisp::Scanner scanner(integer_literal_minus_1_string);
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_EQ(token_list.size(), 1);

    {
        TextPosition text_position(integer_literal_minus_1_string.cbegin(), integer_literal_minus_1_string.cend());
        ASSERT_EQ(token_list.at(0), Token(TokenType::SIGNED_INTEGER, "-1", text_position, static_cast<int64_t>(-1)));
        ASSERT_EQ(token_list.at(0).get_line(), 1);
        ASSERT_EQ(token_list.at(0).get_column(), 1);
    }

    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_TRUE(error_log.empty());
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);   // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), 3); // 3 is past end here.
}

TEST(integer_literal_must_be_scanned_appropriately, unsigned_integer_18446744073709551615)
{
    const std::string_view integer_literal_18446744073709551615_string { "18446744073709551615" };
    const yli::lisp::Scanner scanner(integer_literal_18446744073709551615_string);
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_EQ(token_list.size(), 1);

    {
        TextPosition text_position(integer_literal_18446744073709551615_string.cbegin(), integer_literal_18446744073709551615_string.cend());
        ASSERT_EQ(token_list.at(0), Token(TokenType::UNSIGNED_INTEGER, "18446744073709551615", text_position, static_cast<uint64_t>(18446744073709551615)));
        ASSERT_EQ(token_list.at(0).get_line(), 1);
        ASSERT_EQ(token_list.at(0).get_column(), 1);
    }

    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_TRUE(error_log.empty());
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);                                                          // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), (integer_literal_18446744073709551615_string.size() + 1)); // Past end here.
}

TEST(integer_literal_must_be_scanned_appropriately, signed_integer_minus_9223372036854775808)
{
    const std::string_view integer_literal_minus_9223372036854775808_string { "-9223372036854775808" };
    const yli::lisp::Scanner scanner(integer_literal_minus_9223372036854775808_string);
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_EQ(token_list.size(), 1);

    {
        TextPosition text_position(integer_literal_minus_9223372036854775808_string.cbegin(), integer_literal_minus_9223372036854775808_string.cend());
        ASSERT_EQ(token_list.at(0), Token(TokenType::SIGNED_INTEGER, "-9223372036854775808", text_position, static_cast<int64_t>(-9223372036854775808)));
        ASSERT_EQ(token_list.at(0).get_line(), 1);
        ASSERT_EQ(token_list.at(0).get_column(), 1);
    }

    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_TRUE(error_log.empty());
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);                                                               // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), (integer_literal_minus_9223372036854775808_string.size() + 1)); // Past end here.
}

TEST(floating_point_literal_must_be_scanned_appropriately, floating_point_literal_0_dot_0)
{
    const std::string_view floating_point_literal_0_dot_0_string { "0.0" };
    const yli::lisp::Scanner scanner(floating_point_literal_0_dot_0_string);
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_EQ(token_list.size(), 1);

    {
        TextPosition text_position(floating_point_literal_0_dot_0_string.cbegin(), floating_point_literal_0_dot_0_string.cend());
        ASSERT_EQ(token_list.at(0), Token(TokenType::FLOATING_POINT, "0.0", text_position, static_cast<double>(0.0)));
        ASSERT_EQ(token_list.at(0).get_line(), 1);
        ASSERT_EQ(token_list.at(0).get_column(), 1);
    }

    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_TRUE(error_log.empty());
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);                                                    // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), (floating_point_literal_0_dot_0_string.size() + 1)); // Past end here.
}

TEST(floating_point_literal_must_be_scanned_appropriately, floating_point_literal_minus_0_dot_0)
{
    const std::string_view floating_point_literal_minus_0_dot_0_string { "-0.0" };
    const yli::lisp::Scanner scanner(floating_point_literal_minus_0_dot_0_string);
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_EQ(token_list.size(), 1);

    {
        TextPosition text_position(floating_point_literal_minus_0_dot_0_string.cbegin(), floating_point_literal_minus_0_dot_0_string.cend());
        ASSERT_EQ(token_list.at(0), Token(TokenType::FLOATING_POINT, "-0.0", text_position, static_cast<double>(0.0)));
        ASSERT_EQ(token_list.at(0).get_line(), 1);
        ASSERT_EQ(token_list.at(0).get_column(), 1);
    }

    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_TRUE(error_log.empty());
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);                                                          // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), (floating_point_literal_minus_0_dot_0_string.size() + 1)); // Past end here.
}

TEST(string_must_be_scanned_appropriately, foo_identifier)
{
    const std::string_view foo_string { "foo" };
    const Scanner scanner(foo_string);
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_EQ(token_list.size(), 1);

    {
        TextPosition text_position(foo_string.cbegin(), foo_string.cend());
        ASSERT_EQ(token_list.at(0), Token(TokenType::IDENTIFIER, "foo", text_position));
        ASSERT_EQ(token_list.at(0).get_line(), 1);
        ASSERT_EQ(token_list.at(0).get_column(), 1);
    }

    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_TRUE(error_log.empty());
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);                         // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), (foo_string.size() + 1)); // Past end here.
}

TEST(string_must_be_scanned_appropriately, foo_bar_identifiers)
{
    const std::string_view foo_space_bar_string { "foo bar" };
    const yli::lisp::Scanner scanner(foo_space_bar_string);
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_EQ(token_list.size(), 2);

    {
        TextPosition text_position(foo_space_bar_string.cbegin(), foo_space_bar_string.cend());
        ASSERT_EQ(token_list.at(0), Token(TokenType::IDENTIFIER, "foo", text_position));
        ASSERT_EQ(token_list.at(0).get_line(), 1);
        ASSERT_EQ(token_list.at(0).get_column(), 1);
    }
    {
        TextPosition text_position(foo_space_bar_string.cbegin(), foo_space_bar_string.cend());
        ASSERT_EQ(token_list.at(1), Token(TokenType::IDENTIFIER, "bar", text_position));
        ASSERT_EQ(token_list.at(1).get_line(), 1);
        ASSERT_EQ(token_list.at(1).get_column(), 5);
    }

    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_TRUE(error_log.empty());
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);                                   // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), (foo_space_bar_string.size() + 1)); // Past end here.
}

TEST(string_must_be_scanned_appropriately, foo_bar_baz_identifiers)
{
    const std::string_view foo_space_bar_space_baz_string { "foo bar baz" };
    const yli::lisp::Scanner scanner(foo_space_bar_space_baz_string);
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_EQ(token_list.size(), 3);

    {
        TextPosition text_position(foo_space_bar_space_baz_string.cbegin(), foo_space_bar_space_baz_string.cend());
        ASSERT_EQ(token_list.at(0), Token(TokenType::IDENTIFIER, "foo", text_position));
        ASSERT_EQ(token_list.at(0).get_line(), 1);
        ASSERT_EQ(token_list.at(0).get_column(), 1);
    }
    {
        TextPosition text_position(foo_space_bar_space_baz_string.cbegin(), foo_space_bar_space_baz_string.cend());
        ASSERT_EQ(token_list.at(1), Token(TokenType::IDENTIFIER, "bar", text_position));
        ASSERT_EQ(token_list.at(1).get_line(), 1);
        ASSERT_EQ(token_list.at(1).get_column(), 5);
    }
    {
        TextPosition text_position(foo_space_bar_space_baz_string.cbegin(), foo_space_bar_space_baz_string.cend());
        ASSERT_EQ(token_list.at(2), Token(TokenType::IDENTIFIER, "baz", text_position));
        ASSERT_EQ(token_list.at(2).get_line(), 1);
        ASSERT_EQ(token_list.at(2).get_column(), 9);
    }

    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_TRUE(error_log.empty());
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);                                             // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), (foo_space_bar_space_baz_string.size() + 1)); // Past end here.
}

TEST(string_must_be_scanned_appropriately, empty_block)
{
    const std::string_view empty_block_string { "()" };
    const yli::lisp::Scanner scanner(empty_block_string);
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_EQ(token_list.size(), 2);

    {
        TextPosition text_position(empty_block_string.cbegin(), empty_block_string.cend());
        ASSERT_EQ(token_list.at(0), Token(TokenType::LEFT_PARENTHESIS, "(", text_position));
        ASSERT_EQ(token_list.at(0).get_line(), 1);
        ASSERT_EQ(token_list.at(0).get_column(), 1);
    }
    {
        TextPosition text_position(empty_block_string.cbegin(), empty_block_string.cend());
        ASSERT_EQ(token_list.at(1), Token(TokenType::RIGHT_PARENTHESIS, ")", text_position));
        ASSERT_EQ(token_list.at(1).get_line(), 1);
        ASSERT_EQ(token_list.at(1).get_column(), 2);
    }

    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_TRUE(error_log.empty());
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);                                 // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), (empty_block_string.size() + 1)); // Past end here.
}

TEST(string_must_be_scanned_appropriately, empty_block_empty_block)
{
    const std::string_view empty_block_empty_block_string { "()()" };
    const yli::lisp::Scanner scanner(empty_block_empty_block_string);
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_EQ(token_list.size(), 4);

    {
        TextPosition text_position(empty_block_empty_block_string.cbegin(), empty_block_empty_block_string.cend());
        ASSERT_EQ(token_list.at(0), Token(TokenType::LEFT_PARENTHESIS, "(", text_position));
        ASSERT_EQ(token_list.at(0).get_line(), 1);
        ASSERT_EQ(token_list.at(0).get_column(), 1);
    }
    {
        TextPosition text_position(empty_block_empty_block_string.cbegin(), empty_block_empty_block_string.cend());
        ASSERT_EQ(token_list.at(1), Token(TokenType::RIGHT_PARENTHESIS, ")", text_position));
        ASSERT_EQ(token_list.at(1).get_line(), 1);
        ASSERT_EQ(token_list.at(1).get_column(), 2);
    }
    {
        TextPosition text_position(empty_block_empty_block_string.cbegin(), empty_block_empty_block_string.cend());
        ASSERT_EQ(token_list.at(2), Token(TokenType::LEFT_PARENTHESIS, "(", text_position));
        ASSERT_EQ(token_list.at(2).get_line(), 1);
        ASSERT_EQ(token_list.at(2).get_column(), 3);
    }
    {
        TextPosition text_position(empty_block_empty_block_string.cbegin(), empty_block_empty_block_string.cend());
        ASSERT_EQ(token_list.at(3), Token(TokenType::RIGHT_PARENTHESIS, ")", text_position));
        ASSERT_EQ(token_list.at(3).get_line(), 1);
        ASSERT_EQ(token_list.at(3).get_column(), 4);
    }

    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_TRUE(error_log.empty());
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);                                             // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), (empty_block_empty_block_string.size() + 1)); // Past end here.
}

TEST(string_must_be_scanned_appropriately, empty_block_space_empty_block)
{
    const std::string_view empty_block_space_empty_block_string { "() ()" };
    const yli::lisp::Scanner scanner(empty_block_space_empty_block_string);
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_EQ(token_list.size(), 4);

    {
        TextPosition text_position(empty_block_space_empty_block_string.cbegin(), empty_block_space_empty_block_string.cend());
        ASSERT_EQ(token_list.at(0), Token(TokenType::LEFT_PARENTHESIS, "(", text_position));
        ASSERT_EQ(token_list.at(0).get_line(), 1);
        ASSERT_EQ(token_list.at(0).get_column(), 1);
    }
    {
        TextPosition text_position(empty_block_space_empty_block_string.cbegin(), empty_block_space_empty_block_string.cend());
        ASSERT_EQ(token_list.at(1), Token(TokenType::RIGHT_PARENTHESIS, ")", text_position));
        ASSERT_EQ(token_list.at(1).get_line(), 1);
        ASSERT_EQ(token_list.at(1).get_column(), 2);
    }
    {
        TextPosition text_position(empty_block_space_empty_block_string.cbegin(), empty_block_space_empty_block_string.cend());
        ASSERT_EQ(token_list.at(2), Token(TokenType::LEFT_PARENTHESIS, "(", text_position));
        ASSERT_EQ(token_list.at(2).get_line(), 1);
        ASSERT_EQ(token_list.at(2).get_column(), 4);
    }
    {
        TextPosition text_position(empty_block_space_empty_block_string.cbegin(), empty_block_space_empty_block_string.cend());
        ASSERT_EQ(token_list.at(3), Token(TokenType::RIGHT_PARENTHESIS, ")", text_position));
        ASSERT_EQ(token_list.at(3).get_line(), 1);
        ASSERT_EQ(token_list.at(3).get_column(), 5);
    }

    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_TRUE(error_log.empty());
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);                                                   // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), (empty_block_space_empty_block_string.size() + 1)); // Past end here.
}

TEST(string_must_be_scanned_appropriately, block_foo)
{
    const std::string_view block_with_foo_string { "(foo)" };
    const yli::lisp::Scanner scanner(block_with_foo_string);
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_EQ(token_list.size(), 3);

    {
        TextPosition text_position(block_with_foo_string.cbegin(), block_with_foo_string.cend());
        ASSERT_EQ(token_list.at(0), Token(TokenType::LEFT_PARENTHESIS, "(", text_position));
        ASSERT_EQ(token_list.at(0).get_line(), 1);
        ASSERT_EQ(token_list.at(0).get_column(), 1);
    }
    {
        TextPosition text_position(block_with_foo_string.cbegin(), block_with_foo_string.cend());
        ASSERT_EQ(token_list.at(1), Token(TokenType::IDENTIFIER, "foo", text_position));
        ASSERT_EQ(token_list.at(1).get_line(), 1);
        ASSERT_EQ(token_list.at(1).get_column(), 2);
    }
    {
        TextPosition text_position(block_with_foo_string.cbegin(), block_with_foo_string.cend());
        ASSERT_EQ(token_list.at(2), Token(TokenType::RIGHT_PARENTHESIS, ")", text_position));
        ASSERT_EQ(token_list.at(2).get_line(), 1);
        ASSERT_EQ(token_list.at(2).get_column(), 5);
    }

    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_TRUE(error_log.empty());
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);                                    // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), (block_with_foo_string.size() + 1)); // Past end here.
}

TEST(string_must_be_scanned_appropriately, block_space_foo)
{
    const std::string_view block_with_space_foo_string { "( foo)" };
    const yli::lisp::Scanner scanner(block_with_space_foo_string);
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_EQ(token_list.size(), 3);

    {
        TextPosition text_position(block_with_space_foo_string.cbegin(), block_with_space_foo_string.cend());
        ASSERT_EQ(token_list.at(0), Token(TokenType::LEFT_PARENTHESIS, "(", text_position));
        ASSERT_EQ(token_list.at(0).get_line(), 1);
        ASSERT_EQ(token_list.at(0).get_column(), 1);
    }
    {
        TextPosition text_position(block_with_space_foo_string.cbegin(), block_with_space_foo_string.cend());
        ASSERT_EQ(token_list.at(1), Token(TokenType::IDENTIFIER, "foo", text_position));
        ASSERT_EQ(token_list.at(1).get_line(), 1);
        ASSERT_EQ(token_list.at(1).get_column(), 3);
    }
    {
        TextPosition text_position(block_with_space_foo_string.cbegin(), block_with_space_foo_string.cend());
        ASSERT_EQ(token_list.at(2), Token(TokenType::RIGHT_PARENTHESIS, ")", text_position));
        ASSERT_EQ(token_list.at(2).get_line(), 1);
        ASSERT_EQ(token_list.at(2).get_column(), 6);
    }

    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_TRUE(error_log.empty());
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);                                          // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), (block_with_space_foo_string.size() + 1)); // Past end here.
}

TEST(string_must_be_scanned_appropriately, block_foo_space)
{
    const std::string_view block_with_foo_space_string { "(foo )" };
    const yli::lisp::Scanner scanner(block_with_foo_space_string);
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_EQ(token_list.size(), 3);

    {
        TextPosition text_position(block_with_foo_space_string.cbegin(), block_with_foo_space_string.cend());
        ASSERT_EQ(token_list.at(0), Token(TokenType::LEFT_PARENTHESIS, "(", text_position));
        ASSERT_EQ(token_list.at(0).get_line(), 1);
        ASSERT_EQ(token_list.at(0).get_column(), 1);
    }
    {
        TextPosition text_position(block_with_foo_space_string.cbegin(), block_with_foo_space_string.cend());
        ASSERT_EQ(token_list.at(1), Token(TokenType::IDENTIFIER, "foo", text_position));
        ASSERT_EQ(token_list.at(1).get_line(), 1);
        ASSERT_EQ(token_list.at(1).get_column(), 2);
    }
    {
        TextPosition text_position(block_with_foo_space_string.cbegin(), block_with_foo_space_string.cend());
        ASSERT_EQ(token_list.at(2), Token(TokenType::RIGHT_PARENTHESIS, ")", text_position));
        ASSERT_EQ(token_list.at(2).get_line(), 1);
        ASSERT_EQ(token_list.at(2).get_column(), 6);
    }

    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_TRUE(error_log.empty());
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);                                          // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), (block_with_foo_space_string.size() + 1)); // Past end here.
}

TEST(string_must_be_scanned_appropriately, block_space_foo_space)
{
    const std::string_view block_with_space_foo_space_string { "( foo )" };
    const yli::lisp::Scanner scanner(block_with_space_foo_space_string);
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_EQ(token_list.size(), 3);

    {
        TextPosition text_position(block_with_space_foo_space_string.cbegin(), block_with_space_foo_space_string.cend());
        ASSERT_EQ(token_list.at(0), Token(TokenType::LEFT_PARENTHESIS, "(", text_position));
        ASSERT_EQ(token_list.at(0).get_line(), 1);
        ASSERT_EQ(token_list.at(0).get_column(), 1);
    }
    {
        TextPosition text_position(block_with_space_foo_space_string.cbegin(), block_with_space_foo_space_string.cend());
        ASSERT_EQ(token_list.at(1), Token(TokenType::IDENTIFIER, "foo", text_position));
        ASSERT_EQ(token_list.at(1).get_line(), 1);
        ASSERT_EQ(token_list.at(1).get_column(), 3);
    }
    {
        TextPosition text_position(block_with_space_foo_space_string.cbegin(), block_with_space_foo_space_string.cend());
        ASSERT_EQ(token_list.at(2), Token(TokenType::RIGHT_PARENTHESIS, ")", text_position));
        ASSERT_EQ(token_list.at(2).get_line(), 1);
        ASSERT_EQ(token_list.at(2).get_column(), 7);
    }

    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_TRUE(error_log.empty());
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);                                                // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), (block_with_space_foo_space_string.size() + 1)); // Past end here.
}

TEST(string_must_be_scanned_appropriately, block_foo_space_bar)
{
    const std::string_view block_with_foo_space_bar_string { "(foo bar)" };
    const yli::lisp::Scanner scanner(block_with_foo_space_bar_string);
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_EQ(token_list.size(), 4);

    {
        TextPosition text_position(block_with_foo_space_bar_string.cbegin(), block_with_foo_space_bar_string.cend());
        ASSERT_EQ(token_list.at(0), Token(TokenType::LEFT_PARENTHESIS, "(", text_position));
        ASSERT_EQ(token_list.at(0).get_line(), 1);
        ASSERT_EQ(token_list.at(0).get_column(), 1);
    }
    {
        TextPosition text_position(block_with_foo_space_bar_string.cbegin(), block_with_foo_space_bar_string.cend());
        ASSERT_EQ(token_list.at(1), Token(TokenType::IDENTIFIER, "foo", text_position));
        ASSERT_EQ(token_list.at(1).get_line(), 1);
        ASSERT_EQ(token_list.at(1).get_column(), 2);
    }
    {
        TextPosition text_position(block_with_foo_space_bar_string.cbegin(), block_with_foo_space_bar_string.cend());
        ASSERT_EQ(token_list.at(2), Token(TokenType::IDENTIFIER, "bar", text_position));
        ASSERT_EQ(token_list.at(2).get_line(), 1);
        ASSERT_EQ(token_list.at(2).get_column(), 6);
    }
    {
        TextPosition text_position(block_with_foo_space_bar_string.cbegin(), block_with_foo_space_bar_string.cend());
        ASSERT_EQ(token_list.at(3), Token(TokenType::RIGHT_PARENTHESIS, ")", text_position));
        ASSERT_EQ(token_list.at(3).get_line(), 1);
        ASSERT_EQ(token_list.at(3).get_column(), 9);
    }

    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_TRUE(error_log.empty());
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);                                              // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), (block_with_foo_space_bar_string.size() + 1)); // Past end here.
}

TEST(string_must_be_scanned_appropriately, block_with_foo_block_bar)
{
    const std::string_view block_with_foo_with_block_bar_string { "(foo(bar))" };
    const yli::lisp::Scanner scanner(block_with_foo_with_block_bar_string);
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_EQ(token_list.size(), 6);

    {
        TextPosition text_position(block_with_foo_with_block_bar_string.cbegin(), block_with_foo_with_block_bar_string.cend());
        ASSERT_EQ(token_list.at(0), Token(TokenType::LEFT_PARENTHESIS, "(", text_position));
        ASSERT_EQ(token_list.at(0).get_line(), 1);
        ASSERT_EQ(token_list.at(0).get_column(), 1);
    }
    {
        TextPosition text_position(block_with_foo_with_block_bar_string.cbegin(), block_with_foo_with_block_bar_string.cend());
        ASSERT_EQ(token_list.at(1), Token(TokenType::IDENTIFIER, "foo", text_position));
        ASSERT_EQ(token_list.at(1).get_line(), 1);
        ASSERT_EQ(token_list.at(1).get_column(), 2);
    }
    {
        TextPosition text_position(block_with_foo_with_block_bar_string.cbegin(), block_with_foo_with_block_bar_string.cend());
        ASSERT_EQ(token_list.at(2), Token(TokenType::LEFT_PARENTHESIS, "(", text_position));
        ASSERT_EQ(token_list.at(2).get_line(), 1);
        ASSERT_EQ(token_list.at(2).get_column(), 5);
    }
    {
        TextPosition text_position(block_with_foo_with_block_bar_string.cbegin(), block_with_foo_with_block_bar_string.cend());
        ASSERT_EQ(token_list.at(3), Token(TokenType::IDENTIFIER, "bar", text_position));
        ASSERT_EQ(token_list.at(3).get_line(), 1);
        ASSERT_EQ(token_list.at(3).get_column(), 6);
    }
    {
        TextPosition text_position(block_with_foo_with_block_bar_string.cbegin(), block_with_foo_with_block_bar_string.cend());
        ASSERT_EQ(token_list.at(4), Token(TokenType::RIGHT_PARENTHESIS, ")", text_position));
        ASSERT_EQ(token_list.at(4).get_line(), 1);
        ASSERT_EQ(token_list.at(4).get_column(), 9);
    }
    {
        TextPosition text_position(block_with_foo_with_block_bar_string.cbegin(), block_with_foo_with_block_bar_string.cend());
        ASSERT_EQ(token_list.at(5), Token(TokenType::RIGHT_PARENTHESIS, ")", text_position));
        ASSERT_EQ(token_list.at(5).get_line(), 1);
        ASSERT_EQ(token_list.at(5).get_column(), 10);
    }

    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_TRUE(error_log.empty());
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);                                                   // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), (block_with_foo_with_block_bar_string.size() + 1)); // Past end here.
}

TEST(string_must_be_scanned_appropriately, block_with_foo_space_block_bar)
{
    const std::string_view block_with_foo_space_block_bar_string { "(foo (bar))" };
    const yli::lisp::Scanner scanner(block_with_foo_space_block_bar_string);
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_EQ(token_list.size(), 6);

    {
        TextPosition text_position(block_with_foo_space_block_bar_string.cbegin(), block_with_foo_space_block_bar_string.cend());
        ASSERT_EQ(token_list.at(0), Token(TokenType::LEFT_PARENTHESIS, "(", text_position));
        ASSERT_EQ(token_list.at(0).get_line(), 1);
        ASSERT_EQ(token_list.at(0).get_column(), 1);
    }
    {
        TextPosition text_position(block_with_foo_space_block_bar_string.cbegin(), block_with_foo_space_block_bar_string.cend());
        ASSERT_EQ(token_list.at(1), Token(TokenType::IDENTIFIER, "foo", text_position));
        ASSERT_EQ(token_list.at(1).get_line(), 1);
        ASSERT_EQ(token_list.at(1).get_column(), 2);
    }
    {
        TextPosition text_position(block_with_foo_space_block_bar_string.cbegin(), block_with_foo_space_block_bar_string.cend());
        ASSERT_EQ(token_list.at(2), Token(TokenType::LEFT_PARENTHESIS, "(", text_position));
        ASSERT_EQ(token_list.at(2).get_line(), 1);
        ASSERT_EQ(token_list.at(2).get_column(), 6);
    }
    {
        TextPosition text_position(block_with_foo_space_block_bar_string.cbegin(), block_with_foo_space_block_bar_string.cend());
        ASSERT_EQ(token_list.at(3), Token(TokenType::IDENTIFIER, "bar", text_position));
        ASSERT_EQ(token_list.at(3).get_line(), 1);
        ASSERT_EQ(token_list.at(3).get_column(), 7);
    }
    {
        TextPosition text_position(block_with_foo_space_block_bar_string.cbegin(), block_with_foo_space_block_bar_string.cend());
        ASSERT_EQ(token_list.at(4), Token(TokenType::RIGHT_PARENTHESIS, ")", text_position));
        ASSERT_EQ(token_list.at(4).get_line(), 1);
        ASSERT_EQ(token_list.at(4).get_column(), 10);
    }
    {
        TextPosition text_position(block_with_foo_space_block_bar_string.cbegin(), block_with_foo_space_block_bar_string.cend());
        ASSERT_EQ(token_list.at(5), Token(TokenType::RIGHT_PARENTHESIS, ")", text_position));
        ASSERT_EQ(token_list.at(5).get_line(), 1);
        ASSERT_EQ(token_list.at(5).get_column(), 11);
    }

    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_TRUE(error_log.empty());
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);                                                    // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), (block_with_foo_space_block_bar_string.size() + 1)); // Past end here.
}

TEST(string_must_be_scanned_appropriately, block_with_foo_space_block_with_bar_space_block_baz)
{
    const std::string_view block_with_foo_space_block_with_bar_space_block_baz_string { "(foo (bar (baz)))" };
    const yli::lisp::Scanner scanner(block_with_foo_space_block_with_bar_space_block_baz_string);
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_EQ(token_list.size(), 9);

    {
        TextPosition text_position(block_with_foo_space_block_with_bar_space_block_baz_string.cbegin(), block_with_foo_space_block_with_bar_space_block_baz_string.cend());
        ASSERT_EQ(token_list.at(0), Token(TokenType::LEFT_PARENTHESIS, "(", text_position));
        ASSERT_EQ(token_list.at(0).get_line(), 1);
        ASSERT_EQ(token_list.at(0).get_column(), 1);
    }
    {
        TextPosition text_position(block_with_foo_space_block_with_bar_space_block_baz_string.cbegin(), block_with_foo_space_block_with_bar_space_block_baz_string.cend());
        ASSERT_EQ(token_list.at(1), Token(TokenType::IDENTIFIER, "foo", text_position));
        ASSERT_EQ(token_list.at(1).get_line(), 1);
        ASSERT_EQ(token_list.at(1).get_column(), 2);
    }
    {
        TextPosition text_position(block_with_foo_space_block_with_bar_space_block_baz_string.cbegin(), block_with_foo_space_block_with_bar_space_block_baz_string.cend());
        ASSERT_EQ(token_list.at(2), Token(TokenType::LEFT_PARENTHESIS, "(", text_position));
        ASSERT_EQ(token_list.at(2).get_line(), 1);
        ASSERT_EQ(token_list.at(2).get_column(), 6);
    }
    {
        TextPosition text_position(block_with_foo_space_block_with_bar_space_block_baz_string.cbegin(), block_with_foo_space_block_with_bar_space_block_baz_string.cend());
        ASSERT_EQ(token_list.at(3), Token(TokenType::IDENTIFIER, "bar", text_position));
        ASSERT_EQ(token_list.at(3).get_line(), 1);
        ASSERT_EQ(token_list.at(3).get_column(), 7);
    }
    {
        TextPosition text_position(block_with_foo_space_block_with_bar_space_block_baz_string.cbegin(), block_with_foo_space_block_with_bar_space_block_baz_string.cend());
        ASSERT_EQ(token_list.at(4), Token(TokenType::LEFT_PARENTHESIS, "(", text_position));
        ASSERT_EQ(token_list.at(4).get_line(), 1);
        ASSERT_EQ(token_list.at(4).get_column(), 11);
    }
    {
        TextPosition text_position(block_with_foo_space_block_with_bar_space_block_baz_string.cbegin(), block_with_foo_space_block_with_bar_space_block_baz_string.cend());
        ASSERT_EQ(token_list.at(5), Token(TokenType::IDENTIFIER, "baz", text_position));
        ASSERT_EQ(token_list.at(5).get_line(), 1);
        ASSERT_EQ(token_list.at(5).get_column(), 12);
    }
    {
        TextPosition text_position(block_with_foo_space_block_with_bar_space_block_baz_string.cbegin(), block_with_foo_space_block_with_bar_space_block_baz_string.cend());
        ASSERT_EQ(token_list.at(6), Token(TokenType::RIGHT_PARENTHESIS, ")", text_position));
        ASSERT_EQ(token_list.at(6).get_line(), 1);
        ASSERT_EQ(token_list.at(6).get_column(), 15);
    }
    {
        TextPosition text_position(block_with_foo_space_block_with_bar_space_block_baz_string.cbegin(), block_with_foo_space_block_with_bar_space_block_baz_string.cend());
        ASSERT_EQ(token_list.at(7), Token(TokenType::RIGHT_PARENTHESIS, ")", text_position));
        ASSERT_EQ(token_list.at(7).get_line(), 1);
        ASSERT_EQ(token_list.at(7).get_column(), 16);
    }
    {
        TextPosition text_position(block_with_foo_space_block_with_bar_space_block_baz_string.cbegin(), block_with_foo_space_block_with_bar_space_block_baz_string.cend());
        ASSERT_EQ(token_list.at(8), Token(TokenType::RIGHT_PARENTHESIS, ")", text_position));
        ASSERT_EQ(token_list.at(8).get_line(), 1);
        ASSERT_EQ(token_list.at(8).get_column(), 17);
    }

    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_TRUE(error_log.empty());
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);                                                                         // Line indices start from 1.
    ASSERT_EQ(text_position.get_column(), (block_with_foo_space_block_with_bar_space_block_baz_string.size() + 1)); // Past end here.
}

TEST(string_must_be_scanned_appropriately, two_blocks_block_foo_block_bar)
{
    const std::string_view block_foo_block_bar_string { "(foo)(bar)" };
    const yli::lisp::Scanner scanner(block_foo_block_bar_string);
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_EQ(token_list.size(), 6);

    {
        TextPosition text_position(block_foo_block_bar_string.cbegin(), block_foo_block_bar_string.cend());
        ASSERT_EQ(token_list.at(0), Token(TokenType::LEFT_PARENTHESIS, "(", text_position));
        ASSERT_EQ(token_list.at(0).get_line(), 1);
        ASSERT_EQ(token_list.at(0).get_column(), 1);
    }
    {
        TextPosition text_position(block_foo_block_bar_string.cbegin(), block_foo_block_bar_string.cend());
        ASSERT_EQ(token_list.at(1), Token(TokenType::IDENTIFIER, "foo", text_position));
        ASSERT_EQ(token_list.at(1).get_line(), 1);
        ASSERT_EQ(token_list.at(1).get_column(), 2);
    }
    {
        TextPosition text_position(block_foo_block_bar_string.cbegin(), block_foo_block_bar_string.cend());
        ASSERT_EQ(token_list.at(2), Token(TokenType::RIGHT_PARENTHESIS, ")", text_position));
        ASSERT_EQ(token_list.at(2).get_line(), 1);
        ASSERT_EQ(token_list.at(2).get_column(), 5);
    }
    {
        TextPosition text_position(block_foo_block_bar_string.cbegin(), block_foo_block_bar_string.cend());
        ASSERT_EQ(token_list.at(3), Token(TokenType::LEFT_PARENTHESIS, "(", text_position));
        ASSERT_EQ(token_list.at(3).get_line(), 1);
        ASSERT_EQ(token_list.at(3).get_column(), 6);
    }
    {
        TextPosition text_position(block_foo_block_bar_string.cbegin(), block_foo_block_bar_string.cend());
        ASSERT_EQ(token_list.at(4), Token(TokenType::IDENTIFIER, "bar", text_position));
        ASSERT_EQ(token_list.at(4).get_line(), 1);
        ASSERT_EQ(token_list.at(4).get_column(), 7);
    }
    {
        TextPosition text_position(block_foo_block_bar_string.cbegin(), block_foo_block_bar_string.cend());
        ASSERT_EQ(token_list.at(5), Token(TokenType::RIGHT_PARENTHESIS, ")", text_position));
        ASSERT_EQ(token_list.at(5).get_line(), 1);
        ASSERT_EQ(token_list.at(5).get_column(), 10);
    }

    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_TRUE(error_log.empty());
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);                                         // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), (block_foo_block_bar_string.size() + 1)); // Past end here.
}

TEST(string_must_be_scanned_appropriately, two_blocks_block_foo_space_block_bar)
{
    const std::string_view block_foo_space_block_bar_string { "(foo) (bar)" };
    const yli::lisp::Scanner scanner(block_foo_space_block_bar_string);
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_EQ(token_list.size(), 6);

    {
        TextPosition text_position(block_foo_space_block_bar_string.cbegin(), block_foo_space_block_bar_string.cend());
        ASSERT_EQ(token_list.at(0), Token(TokenType::LEFT_PARENTHESIS, "(", text_position));
        ASSERT_EQ(token_list.at(0).get_line(), 1);
        ASSERT_EQ(token_list.at(0).get_column(), 1);
    }
    {
        TextPosition text_position(block_foo_space_block_bar_string.cbegin(), block_foo_space_block_bar_string.cend());
        ASSERT_EQ(token_list.at(1), Token(TokenType::IDENTIFIER, "foo", text_position));
        ASSERT_EQ(token_list.at(1).get_line(), 1);
        ASSERT_EQ(token_list.at(1).get_column(), 2);
    }
    {
        TextPosition text_position(block_foo_space_block_bar_string.cbegin(), block_foo_space_block_bar_string.cend());
        ASSERT_EQ(token_list.at(2), Token(TokenType::RIGHT_PARENTHESIS, ")", text_position));
        ASSERT_EQ(token_list.at(2).get_line(), 1);
        ASSERT_EQ(token_list.at(2).get_column(), 5);
    }
    {
        TextPosition text_position(block_foo_space_block_bar_string.cbegin(), block_foo_space_block_bar_string.cend());
        ASSERT_EQ(token_list.at(3), Token(TokenType::LEFT_PARENTHESIS, "(", text_position));
        ASSERT_EQ(token_list.at(3).get_line(), 1);
        ASSERT_EQ(token_list.at(3).get_column(), 7);
    }
    {
        TextPosition text_position(block_foo_space_block_bar_string.cbegin(), block_foo_space_block_bar_string.cend());
        ASSERT_EQ(token_list.at(4), Token(TokenType::IDENTIFIER, "bar", text_position));
        ASSERT_EQ(token_list.at(4).get_line(), 1);
        ASSERT_EQ(token_list.at(4).get_column(), 8);
    }
    {
        TextPosition text_position(block_foo_space_block_bar_string.cbegin(), block_foo_space_block_bar_string.cend());
        ASSERT_EQ(token_list.at(5), Token(TokenType::RIGHT_PARENTHESIS, ")", text_position));
        ASSERT_EQ(token_list.at(5).get_line(), 1);
        ASSERT_EQ(token_list.at(5).get_column(), 11);
    }

    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_TRUE(error_log.empty());
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);                                               // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), (block_foo_space_block_bar_string.size() + 1)); // Past end here.
}

// Failing scans.

TEST(scanning_must_fail_appropriately, missing_closing_double_quote)
{
    const std::string_view double_quote_string { "\"" };
    const Scanner scanner(double_quote_string);
    ASSERT_FALSE(scanner.get_is_success());
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_TRUE(token_list.empty());
    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_EQ(error_log.size(), 1);
    const Error& error = error_log.at(0);
    ASSERT_EQ(error.get_filename(), "");
    ASSERT_EQ(error.get_line(), 1);
    ASSERT_EQ(error.get_column(), 1);
    ASSERT_EQ(error.get_type(), ErrorType::CLOSING_DOUBLE_QUOTE_MISSING);
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);                                  // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), (double_quote_string.size() + 1)); // Past end here.
}

TEST(scanning_must_fail_appropriately, missing_closing_double_quote_with_space)
{
    const std::string_view double_quote_with_space_string { "\" " };
    const Scanner scanner(double_quote_with_space_string);
    ASSERT_FALSE(scanner.get_is_success());
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_TRUE(token_list.empty());
    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_EQ(error_log.size(), 1);
    const Error& error = error_log.at(0);
    ASSERT_EQ(error.get_filename(), "");
    ASSERT_EQ(error.get_line(), 1);
    ASSERT_EQ(error.get_column(), 1);
    ASSERT_EQ(error.get_type(), ErrorType::CLOSING_DOUBLE_QUOTE_MISSING);
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);                                             // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), (double_quote_with_space_string.size() + 1)); // Past end here.
}

TEST(scanning_must_fail_appropriately, space_missing_closing_double_quote)
{
    const std::string_view space_double_quote_string { " \"" };
    const Scanner scanner(space_double_quote_string);
    ASSERT_FALSE(scanner.get_is_success());
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_TRUE(token_list.empty());
    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_EQ(error_log.size(), 1);
    const Error& error = error_log.at(0);
    ASSERT_EQ(error.get_filename(), "");
    ASSERT_EQ(error.get_line(), 1);
    ASSERT_EQ(error.get_column(), 2);
    ASSERT_EQ(error.get_type(), ErrorType::CLOSING_DOUBLE_QUOTE_MISSING);
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);                                        // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), (space_double_quote_string.size() + 1)); // Past end here.
}

TEST(scanning_must_fail_appropriately, audible_bell)
{
    const std::string_view audible_bell_string { "\a" };
    const Scanner scanner(audible_bell_string);
    ASSERT_FALSE(scanner.get_is_success());
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_TRUE(token_list.empty());
    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_EQ(error_log.size(), 1);
    const Error& error = error_log.at(0);
    ASSERT_EQ(error.get_filename(), "");
    ASSERT_EQ(error.get_line(), 1);
    ASSERT_EQ(error.get_column(), 1);
    ASSERT_EQ(error.get_type(), ErrorType::INVALID_CODEPOINT);
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);                                  // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), (audible_bell_string.size() + 1)); // Past end here.
}

TEST(scanning_must_fail_appropriately, audible_bell_three_times)
{
    const std::string_view audible_bell_three_times_string { "\a\a\a" };
    const Scanner scanner(audible_bell_three_times_string);
    ASSERT_FALSE(scanner.get_is_success());
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_TRUE(token_list.empty());
    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_EQ(error_log.size(), 3);

    {
        const Error& error = error_log.at(0);
        ASSERT_EQ(error.get_filename(), "");
        ASSERT_EQ(error.get_line(), 1);
        ASSERT_EQ(error.get_column(), 1);
        ASSERT_EQ(error.get_type(), ErrorType::INVALID_CODEPOINT);
    }
    {
        const Error& error = error_log.at(1);
        ASSERT_EQ(error.get_filename(), "");
        ASSERT_EQ(error.get_line(), 1);
        ASSERT_EQ(error.get_column(), 2);
        ASSERT_EQ(error.get_type(), ErrorType::INVALID_CODEPOINT);
    }
    {
        const Error& error = error_log.at(2);
        ASSERT_EQ(error.get_filename(), "");
        ASSERT_EQ(error.get_line(), 1);
        ASSERT_EQ(error.get_column(), 3);
        ASSERT_EQ(error.get_type(), ErrorType::INVALID_CODEPOINT);
    }

    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);                                              // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), (audible_bell_three_times_string.size() + 1)); // Past end here.
}

TEST(scanning_must_fail_appropriately, audible_bell_and_a_identifier)
{
    const std::string_view audible_bell_and_a_string { "\aa" };
    const Scanner scanner(audible_bell_and_a_string);
    ASSERT_FALSE(scanner.get_is_success());
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_EQ(token_list.size(), 1);

    {
        TextPosition text_position(audible_bell_and_a_string.cbegin(), audible_bell_and_a_string.cend());
        ASSERT_EQ(token_list.at(0), Token(TokenType::IDENTIFIER, "a", text_position));
        ASSERT_EQ(token_list.at(0).get_line(), 1);
        ASSERT_EQ(token_list.at(0).get_column(), 2);
    }

    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_EQ(error_log.size(), 1);
    const Error& error = error_log.at(0);
    ASSERT_EQ(error.get_filename(), "");
    ASSERT_EQ(error.get_line(), 1);
    ASSERT_EQ(error.get_column(), 1);
    ASSERT_EQ(error.get_type(), ErrorType::INVALID_CODEPOINT);
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);                                        // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), (audible_bell_and_a_string.size() + 1)); // Past end here.
}

TEST(scanning_must_fail_appropriately, audible_bell_and_foo_identifier)
{
    const std::string_view audible_bell_and_foo_string { "\afoo" };
    const Scanner scanner(audible_bell_and_foo_string);
    ASSERT_FALSE(scanner.get_is_success());
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_EQ(token_list.size(), 1);

    {
        TextPosition text_position(audible_bell_and_foo_string.cbegin(), audible_bell_and_foo_string.cend());
        ASSERT_EQ(token_list.at(0), Token(TokenType::IDENTIFIER, "foo", text_position));
        ASSERT_EQ(token_list.at(0).get_line(), 1);
        ASSERT_EQ(token_list.at(0).get_column(), 2);
    }

    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_EQ(error_log.size(), 1);
    const Error& error = error_log.at(0);
    ASSERT_EQ(error.get_filename(), "");
    ASSERT_EQ(error.get_line(), 1);
    ASSERT_EQ(error.get_column(), 1);
    ASSERT_EQ(error.get_type(), ErrorType::INVALID_CODEPOINT);
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);                                          // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), (audible_bell_and_foo_string.size() + 1)); // Past end here.
}

TEST(scanning_must_fail_appropriately, foo_identifier_and_audible_bell)
{
    const std::string_view foo_identifier_and_audible_bell_string { "foo\a" };
    const Scanner scanner(foo_identifier_and_audible_bell_string);
    ASSERT_FALSE(scanner.get_is_success());
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_EQ(token_list.size(), 1);

    {
        TextPosition text_position(foo_identifier_and_audible_bell_string.cbegin(), foo_identifier_and_audible_bell_string.cend());
        ASSERT_EQ(token_list.at(0), Token(TokenType::IDENTIFIER, "foo", text_position));
        ASSERT_EQ(token_list.at(0).get_line(), 1);
        ASSERT_EQ(token_list.at(0).get_column(), 1);
    }

    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_EQ(error_log.size(), 1);
    const Error& error = error_log.at(0);
    ASSERT_EQ(error.get_filename(), "");
    ASSERT_EQ(error.get_line(), 1);
    ASSERT_EQ(error.get_column(), 4);
    ASSERT_EQ(error.get_type(), ErrorType::INVALID_CODEPOINT);
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);                                                     // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), (foo_identifier_and_audible_bell_string.size() + 1)); // Past end here.
}

TEST(string_must_be_scanned_appropriately, audible_bell_string_literal)
{
    const std::string_view audible_bell_string { "\"\a\"" };
    const Scanner scanner(audible_bell_string);
    const TokenList& token_list = scanner.get_token_list();
    ASSERT_EQ(token_list.size(), 1);

    {
        TextPosition text_position(audible_bell_string.cbegin(), audible_bell_string.cend());
        ASSERT_EQ(token_list.at(0), Token(TokenType::STRING, "\a", text_position));
        ASSERT_EQ(token_list.at(0).get_line(), 1);
        ASSERT_EQ(token_list.at(0).get_column(), 1);
    }

    const ErrorLog& error_log = scanner.get_error_log();
    ASSERT_EQ(error_log.size(), 1);
    const Error& error = error_log.at(0);
    ASSERT_EQ(error.get_filename(), "");
    ASSERT_EQ(error.get_line(), 1);
    ASSERT_EQ(error.get_column(), 2);
    ASSERT_EQ(error.get_type(), ErrorType::INVALID_CODEPOINT);
    const TextPosition& text_position = scanner.get_text_position();
    ASSERT_EQ(text_position.get_line(), 1);                                  // Line indices start from 1 and we have not changed line.
    ASSERT_EQ(text_position.get_column(), (audible_bell_string.size() + 1)); // Past end here.
}
