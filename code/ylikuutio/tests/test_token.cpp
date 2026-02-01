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
#include "code/ylikuutio/lisp/token.hpp"
#include "code/ylikuutio/lisp/token_type.hpp"
#include "code/ylikuutio/lisp/text_position.hpp"

// Include standard headers
#include <limits>   // std::numeric_limits
#include <optional> // std::nullopt
#include <stdint.h> // int64_t, uint64_t
#include <string>   // std::string
#include <string_view> // std::string_view

using yli::lisp::Token;
using yli::lisp::TokenType;
using yli::lisp::TextPosition;

TEST(token_must_be_initialized_appropriately, left_parenthesis)
{
    std::string_view left_parenthesis { "(" };
    TextPosition text_position(left_parenthesis.cbegin(), left_parenthesis.cend());
    Token token(TokenType::LEFT_PARENTHESIS, std::string(left_parenthesis), text_position);
    ASSERT_EQ(token.get_type(), TokenType::LEFT_PARENTHESIS);
    ASSERT_EQ(token.get_lexeme(), "(");
    ASSERT_EQ(token.get_text_position().get_line(), 1);
    ASSERT_EQ(token.get_text_position().get_column(), 1);
}

TEST(token_must_be_initialized_appropriately, right_parenthesis)
{
    std::string_view right_parenthesis { ")" };
    TextPosition text_position(right_parenthesis.cbegin(), right_parenthesis.cend());
    Token token(TokenType::RIGHT_PARENTHESIS, std::string(right_parenthesis), text_position);
    ASSERT_EQ(token.get_type(), TokenType::RIGHT_PARENTHESIS);
    ASSERT_EQ(token.get_lexeme(), ")");
    ASSERT_EQ(token.get_text_position().get_line(), 1);
    ASSERT_EQ(token.get_text_position().get_column(), 1);
}

TEST(token_must_be_initialized_appropriately, quote)
{
    std::string_view quote { "'" };
    TextPosition text_position(quote.cbegin(), quote.cend());
    Token token(TokenType::QUOTE, std::string(quote), text_position);
    ASSERT_EQ(token.get_type(), TokenType::QUOTE);
    ASSERT_EQ(token.get_lexeme(), "'");
    ASSERT_EQ(token.get_text_position().get_line(), 1);
    ASSERT_EQ(token.get_text_position().get_column(), 1);
}

TEST(token_must_be_initialized_appropriately, dot)
{
    std::string_view dot { "." };
    TextPosition text_position(dot.cbegin(), dot.cend());
    Token token(TokenType::DOT, std::string(dot), text_position);
    ASSERT_EQ(token.get_type(), TokenType::DOT);
    ASSERT_EQ(token.get_lexeme(), ".");
    ASSERT_EQ(token.get_text_position().get_line(), 1);
    ASSERT_EQ(token.get_text_position().get_column(), 1);
}

TEST(token_must_be_initialized_appropriately, semicolon)
{
    std::string_view semicolon { ";" };
    TextPosition text_position(semicolon.cbegin(), semicolon.cend());
    Token token(TokenType::SEMICOLON, std::string(semicolon), text_position);
    ASSERT_EQ(token.get_type(), TokenType::SEMICOLON);
    ASSERT_EQ(token.get_lexeme(), ";");
    ASSERT_EQ(token.get_text_position().get_line(), 1);
    ASSERT_EQ(token.get_text_position().get_column(), 1);
}

TEST(token_must_be_initialized_appropriately, identifier_a)
{
    std::string_view identifier_a { "a" };
    TextPosition text_position(identifier_a.cbegin(), identifier_a.cend());
    Token token(TokenType::IDENTIFIER, std::string(identifier_a), text_position);
    ASSERT_EQ(token.get_type(), TokenType::IDENTIFIER);
    ASSERT_EQ(token.get_lexeme(), "a");
    ASSERT_EQ(token.get_text_position().get_line(), 1);
    ASSERT_EQ(token.get_text_position().get_column(), 1);
}

TEST(token_must_be_initialized_appropriately, identifier_abc)
{
    std::string_view identifier_abc { "abc" };
    TextPosition text_position(identifier_abc.cbegin(), identifier_abc.cend());
    Token token(TokenType::IDENTIFIER, std::string(identifier_abc), text_position);
    ASSERT_EQ(token.get_type(), TokenType::IDENTIFIER);
    ASSERT_EQ(token.get_lexeme(), "abc");
    ASSERT_EQ(token.get_text_position().get_line(), 1);
    ASSERT_EQ(token.get_text_position().get_column(), 1);
}

TEST(token_must_be_initialized_appropriately, string_a)
{
    std::string_view string_a { R"("a")" };
    TextPosition text_position(string_a.cbegin(), string_a.cend());
    Token token(TokenType::STRING, std::string(string_a), text_position);
    ASSERT_EQ(token.get_type(), TokenType::STRING);
    ASSERT_EQ(token.get_lexeme(), R"("a")");
    ASSERT_EQ(token.get_text_position().get_line(), 1);
    ASSERT_EQ(token.get_text_position().get_column(), 1);
}

TEST(token_must_be_initialized_appropriately, string_abc)
{
    std::string_view string_abc { R"("abc")" };
    TextPosition text_position(string_abc.cbegin(), string_abc.cend());
    Token token(TokenType::STRING, std::string(string_abc), text_position);
    ASSERT_EQ(token.get_type(), TokenType::STRING);
    ASSERT_EQ(token.get_lexeme(), R"("abc")");
    ASSERT_EQ(token.get_text_position().get_line(), 1);
    ASSERT_EQ(token.get_text_position().get_column(), 1);
}

TEST(token_must_be_initialized_appropriately, unsigned_integer_0)
{
    std::string_view integer_0 { "0" };
    TextPosition text_position(integer_0.cbegin(), integer_0.cend());
    Token token(TokenType::UNSIGNED_INTEGER, std::string(integer_0), text_position, static_cast<uint64_t>(0));
    ASSERT_EQ(token.get_type(), TokenType::UNSIGNED_INTEGER);
    ASSERT_EQ(token.get_lexeme(), "0");
    ASSERT_EQ(token.get_text_position().get_line(), 1);
    ASSERT_EQ(token.get_text_position().get_column(), 1);
    std::optional<uint64_t> maybe_value = token.get_numeric_value<uint64_t>();
    ASSERT_TRUE(maybe_value.has_value());
    ASSERT_EQ(maybe_value.value(), 0);
}

TEST(token_must_be_initialized_appropriately, unsigned_integer_1)
{
    std::string_view integer_1 { "1" };
    TextPosition text_position(integer_1.cbegin(), integer_1.cend());
    Token token(TokenType::UNSIGNED_INTEGER, std::string(integer_1), text_position, static_cast<uint64_t>(1));
    ASSERT_EQ(token.get_type(), TokenType::UNSIGNED_INTEGER);
    ASSERT_EQ(token.get_lexeme(), "1");
    ASSERT_EQ(token.get_text_position().get_line(), 1);
    ASSERT_EQ(token.get_text_position().get_column(), 1);
    std::optional<uint64_t> maybe_value = token.get_numeric_value<uint64_t>();
    ASSERT_TRUE(maybe_value.has_value());
    ASSERT_EQ(maybe_value.value(), 1);
}

TEST(token_must_be_initialized_appropriately, unsigned_integer_18446744073709551615)
{
    std::string_view integer_18446744073709551615 { "18446744073709551615" };
    TextPosition text_position(integer_18446744073709551615.cbegin(), integer_18446744073709551615.cend());
    Token token(TokenType::UNSIGNED_INTEGER, std::string(integer_18446744073709551615), text_position, static_cast<uint64_t>(18446744073709551615));
    ASSERT_EQ(token.get_type(), TokenType::UNSIGNED_INTEGER);
    ASSERT_EQ(token.get_lexeme(), "18446744073709551615");
    ASSERT_EQ(token.get_text_position().get_line(), 1);
    ASSERT_EQ(token.get_text_position().get_column(), 1);
    std::optional<uint64_t> maybe_value = token.get_numeric_value<uint64_t>();
    ASSERT_TRUE(maybe_value.has_value());
    ASSERT_EQ(maybe_value.value(), 18446744073709551615);
}

TEST(token_must_be_initialized_appropriately, signed_integer_0)
{
    std::string_view integer_0 { "0" };
    TextPosition text_position(integer_0.cbegin(), integer_0.cend());
    Token token(TokenType::SIGNED_INTEGER, std::string(integer_0), text_position, static_cast<int64_t>(0));
    ASSERT_EQ(token.get_type(), TokenType::SIGNED_INTEGER);
    ASSERT_EQ(token.get_lexeme(), "0");
    ASSERT_EQ(token.get_text_position().get_line(), 1);
    ASSERT_EQ(token.get_text_position().get_column(), 1);
    std::optional<int64_t> maybe_value = token.get_numeric_value<int64_t>();
    ASSERT_TRUE(maybe_value.has_value());
    ASSERT_EQ(maybe_value.value(), 0);
}

TEST(token_must_be_initialized_appropriately, signed_integer_1)
{
    std::string_view integer_1 { "1" };
    TextPosition text_position(integer_1.cbegin(), integer_1.cend());
    Token token(TokenType::SIGNED_INTEGER, std::string(integer_1), text_position, static_cast<int64_t>(1));
    ASSERT_EQ(token.get_type(), TokenType::SIGNED_INTEGER);
    ASSERT_EQ(token.get_lexeme(), "1");
    ASSERT_EQ(token.get_text_position().get_line(), 1);
    ASSERT_EQ(token.get_text_position().get_column(), 1);
    std::optional<int64_t> maybe_value = token.get_numeric_value<int64_t>();
    ASSERT_TRUE(maybe_value.has_value());
    ASSERT_EQ(maybe_value.value(), 1);
}

TEST(token_must_be_initialized_appropriately, signed_integer_minus_1)
{
    std::string_view integer_minus_1 { "-1" };
    TextPosition text_position(integer_minus_1.cbegin(), integer_minus_1.cend());
    Token token(TokenType::SIGNED_INTEGER, std::string(integer_minus_1), text_position, static_cast<int64_t>(-1));
    ASSERT_EQ(token.get_type(), TokenType::SIGNED_INTEGER);
    ASSERT_EQ(token.get_lexeme(), "-1");
    ASSERT_EQ(token.get_text_position().get_line(), 1);
    ASSERT_EQ(token.get_text_position().get_column(), 1);
    std::optional<int64_t> maybe_value = token.get_numeric_value<int64_t>();
    ASSERT_TRUE(maybe_value.has_value());
    ASSERT_EQ(maybe_value.value(), -1);
}

TEST(token_must_be_initialized_appropriately, signed_integer_9223372036854775807)
{
    std::string_view integer_9223372036854775807 { "9223372036854775807" };
    TextPosition text_position(integer_9223372036854775807.cbegin(), integer_9223372036854775807.cend());
    Token token(TokenType::SIGNED_INTEGER, std::string(integer_9223372036854775807), text_position, static_cast<int64_t>(9223372036854775807));
    ASSERT_EQ(token.get_type(), TokenType::SIGNED_INTEGER);
    ASSERT_EQ(token.get_lexeme(), "9223372036854775807");
    ASSERT_EQ(token.get_text_position().get_line(), 1);
    ASSERT_EQ(token.get_text_position().get_column(), 1);
    std::optional<int64_t> maybe_value = token.get_numeric_value<int64_t>();
    ASSERT_TRUE(maybe_value.has_value());
    ASSERT_EQ(maybe_value.value(), 9223372036854775807);
}

TEST(token_must_be_initialized_appropriately, signed_integer_minus_9223372036854775808)
{
    std::string_view integer_minus_9223372036854775808 { "-9223372036854775808" };
    TextPosition text_position(integer_minus_9223372036854775808.cbegin(), integer_minus_9223372036854775808.cend());
    Token token(TokenType::SIGNED_INTEGER, std::string(integer_minus_9223372036854775808), text_position, static_cast<int64_t>(-9223372036854775808));
    ASSERT_EQ(token.get_type(), TokenType::SIGNED_INTEGER);
    ASSERT_EQ(token.get_lexeme(), "-9223372036854775808");
    ASSERT_EQ(token.get_text_position().get_line(), 1);
    ASSERT_EQ(token.get_text_position().get_column(), 1);
    std::optional<int64_t> maybe_value = token.get_numeric_value<int64_t>();
    ASSERT_TRUE(maybe_value.has_value());
    ASSERT_EQ(maybe_value.value(), -9223372036854775808);
}

TEST(token_must_be_initialized_appropriately, floating_point_0_dot_0)
{
    std::string_view floating_point_0_dot_0 { "0.0" };
    TextPosition text_position(floating_point_0_dot_0.cbegin(), floating_point_0_dot_0.cend());
    Token token(TokenType::FLOATING_POINT, std::string(floating_point_0_dot_0), text_position, static_cast<double>(0.0));
    ASSERT_EQ(token.get_type(), TokenType::FLOATING_POINT);
    ASSERT_EQ(token.get_lexeme(), "0.0");
    ASSERT_EQ(token.get_text_position().get_line(), 1);
    ASSERT_EQ(token.get_text_position().get_column(), 1);
    std::optional<double> maybe_value = token.get_numeric_value<double>();
    ASSERT_TRUE(maybe_value.has_value());
    ASSERT_EQ(maybe_value.value(), 0.0);
}

TEST(token_must_be_initialized_appropriately, floating_point_3_dot_14159)
{
    std::string_view floating_point_3_dot_14159 { "3.14159" };
    TextPosition text_position(floating_point_3_dot_14159.cbegin(), floating_point_3_dot_14159.cend());
    Token token(TokenType::FLOATING_POINT, std::string(floating_point_3_dot_14159), text_position, static_cast<double>(3.14159));
    ASSERT_EQ(token.get_type(), TokenType::FLOATING_POINT);
    ASSERT_EQ(token.get_lexeme(), "3.14159");
    ASSERT_EQ(token.get_text_position().get_line(), 1);
    ASSERT_EQ(token.get_text_position().get_column(), 1);
    std::optional<double> maybe_value = token.get_numeric_value<double>();
    ASSERT_TRUE(maybe_value.has_value());
    ASSERT_GT(maybe_value.value(), 3.14158);
    ASSERT_LT(maybe_value.value(), 3.14160);
}
