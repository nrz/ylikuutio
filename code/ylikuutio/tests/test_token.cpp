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

#include "gtest/gtest.h"
#include "code/ylikuutio/lisp/token.hpp"
#include "code/ylikuutio/lisp/token_type.hpp"

// Include standard headers
#include <limits>   // std::numeric_limits
#include <optional> // std::nullopt
#include <stdint.h> // int64_t, uint64_t

using yli::lisp::TokenType;

TEST(token_must_be_initialized_appropriately, left_parenthesis)
{
    yli::lisp::Token token(TokenType::LEFT_PARENTHESIS, "(");
    ASSERT_EQ(token.get_type(), TokenType::LEFT_PARENTHESIS);
    ASSERT_EQ(token.get_lexeme(), "(");
    ASSERT_EQ(token.get_line_number(), std::nullopt);
}

TEST(token_must_be_initialized_appropriately, right_parenthesis)
{
    yli::lisp::Token token(TokenType::RIGHT_PARENTHESIS, ")");
    ASSERT_EQ(token.get_type(), TokenType::RIGHT_PARENTHESIS);
    ASSERT_EQ(token.get_lexeme(), ")");
    ASSERT_EQ(token.get_line_number(), std::nullopt);
}

TEST(token_must_be_initialized_appropriately, quote)
{
    yli::lisp::Token token(TokenType::QUOTE, "'");
    ASSERT_EQ(token.get_type(), TokenType::QUOTE);
    ASSERT_EQ(token.get_lexeme(), "'");
    ASSERT_EQ(token.get_line_number(), std::nullopt);
}

TEST(token_must_be_initialized_appropriately, dot)
{
    yli::lisp::Token token(TokenType::DOT, ".");
    ASSERT_EQ(token.get_type(), TokenType::DOT);
    ASSERT_EQ(token.get_lexeme(), ".");
    ASSERT_EQ(token.get_line_number(), std::nullopt);
}

TEST(token_must_be_initialized_appropriately, semicolon)
{
    yli::lisp::Token token(TokenType::SEMICOLON, ";");
    ASSERT_EQ(token.get_type(), TokenType::SEMICOLON);
    ASSERT_EQ(token.get_lexeme(), ";");
    ASSERT_EQ(token.get_line_number(), std::nullopt);
}

TEST(token_must_be_initialized_appropriately, identifier_a)
{
    yli::lisp::Token token(TokenType::IDENTIFIER, "a");
    ASSERT_EQ(token.get_type(), TokenType::IDENTIFIER);
    ASSERT_EQ(token.get_lexeme(), "a");
    ASSERT_EQ(token.get_line_number(), std::nullopt);
}

TEST(token_must_be_initialized_appropriately, identifier_abc)
{
    yli::lisp::Token token(TokenType::IDENTIFIER, "abc");
    ASSERT_EQ(token.get_type(), TokenType::IDENTIFIER);
    ASSERT_EQ(token.get_lexeme(), "abc");
    ASSERT_EQ(token.get_line_number(), std::nullopt);
}

TEST(token_must_be_initialized_appropriately, string_a)
{
    yli::lisp::Token token(TokenType::STRING, R"("a")");
    ASSERT_EQ(token.get_type(), TokenType::STRING);
    ASSERT_EQ(token.get_lexeme(), R"("a")");
    ASSERT_EQ(token.get_line_number(), std::nullopt);
}

TEST(token_must_be_initialized_appropriately, string_abc)
{
    yli::lisp::Token token(TokenType::STRING, R"("abc")");
    ASSERT_EQ(token.get_type(), TokenType::STRING);
    ASSERT_EQ(token.get_lexeme(), R"("abc")");
    ASSERT_EQ(token.get_line_number(), std::nullopt);
}

TEST(token_must_be_initialized_appropriately, unsigned_integer_0)
{
    yli::lisp::Token token(TokenType::UNSIGNED_INTEGER, "0", std::nullopt, static_cast<uint64_t>(0));
    ASSERT_EQ(token.get_type(), TokenType::UNSIGNED_INTEGER);
    ASSERT_EQ(token.get_lexeme(), "0");
    ASSERT_EQ(token.get_line_number(), std::nullopt);
    std::optional<uint64_t> maybe_value = token.get_numeric_value<uint64_t>();
    ASSERT_TRUE(maybe_value.has_value());
    ASSERT_EQ(maybe_value.value(), 0);
}

TEST(token_must_be_initialized_appropriately, unsigned_integer_1)
{
    yli::lisp::Token token(TokenType::UNSIGNED_INTEGER, "1", std::nullopt, static_cast<uint64_t>(1));
    ASSERT_EQ(token.get_type(), TokenType::UNSIGNED_INTEGER);
    ASSERT_EQ(token.get_lexeme(), "1");
    ASSERT_EQ(token.get_line_number(), std::nullopt);
    std::optional<uint64_t> maybe_value = token.get_numeric_value<uint64_t>();
    ASSERT_TRUE(maybe_value.has_value());
    ASSERT_EQ(maybe_value.value(), 1);
}

TEST(token_must_be_initialized_appropriately, unsigned_integer_18446744073709551615)
{
    yli::lisp::Token token(TokenType::UNSIGNED_INTEGER, "18446744073709551615", std::nullopt, static_cast<uint64_t>(18446744073709551615));
    ASSERT_EQ(token.get_type(), TokenType::UNSIGNED_INTEGER);
    ASSERT_EQ(token.get_lexeme(), "18446744073709551615");
    ASSERT_EQ(token.get_line_number(), std::nullopt);
    std::optional<uint64_t> maybe_value = token.get_numeric_value<uint64_t>();
    ASSERT_TRUE(maybe_value.has_value());
    ASSERT_EQ(maybe_value.value(), 18446744073709551615);
}

TEST(token_must_be_initialized_appropriately, signed_integer_0)
{
    yli::lisp::Token token(TokenType::SIGNED_INTEGER, "0", std::nullopt, static_cast<int64_t>(0));
    ASSERT_EQ(token.get_type(), TokenType::SIGNED_INTEGER);
    ASSERT_EQ(token.get_lexeme(), "0");
    ASSERT_EQ(token.get_line_number(), std::nullopt);
    std::optional<int64_t> maybe_value = token.get_numeric_value<int64_t>();
    ASSERT_TRUE(maybe_value.has_value());
    ASSERT_EQ(maybe_value.value(), 0);
}

TEST(token_must_be_initialized_appropriately, signed_integer_1)
{
    yli::lisp::Token token(TokenType::SIGNED_INTEGER, "1", std::nullopt, static_cast<int64_t>(1));
    ASSERT_EQ(token.get_type(), TokenType::SIGNED_INTEGER);
    ASSERT_EQ(token.get_lexeme(), "1");
    ASSERT_EQ(token.get_line_number(), std::nullopt);
    std::optional<int64_t> maybe_value = token.get_numeric_value<int64_t>();
    ASSERT_TRUE(maybe_value.has_value());
    ASSERT_EQ(maybe_value.value(), 1);
}

TEST(token_must_be_initialized_appropriately, signed_integer_minus_1)
{
    yli::lisp::Token token(TokenType::SIGNED_INTEGER, "-1", std::nullopt, static_cast<int64_t>(-1));
    ASSERT_EQ(token.get_type(), TokenType::SIGNED_INTEGER);
    ASSERT_EQ(token.get_lexeme(), "-1");
    ASSERT_EQ(token.get_line_number(), std::nullopt);
    std::optional<int64_t> maybe_value = token.get_numeric_value<int64_t>();
    ASSERT_TRUE(maybe_value.has_value());
    ASSERT_EQ(maybe_value.value(), -1);
}

TEST(token_must_be_initialized_appropriately, signed_integer_9223372036854775807)
{
    yli::lisp::Token token(TokenType::SIGNED_INTEGER, "9223372036854775807", std::nullopt, static_cast<int64_t>(9223372036854775807));
    ASSERT_EQ(token.get_type(), TokenType::SIGNED_INTEGER);
    ASSERT_EQ(token.get_lexeme(), "9223372036854775807");
    ASSERT_EQ(token.get_line_number(), std::nullopt);
    std::optional<int64_t> maybe_value = token.get_numeric_value<int64_t>();
    ASSERT_TRUE(maybe_value.has_value());
    ASSERT_EQ(maybe_value.value(), 9223372036854775807);
}

TEST(token_must_be_initialized_appropriately, signed_integer_minus_9223372036854775808)
{
    yli::lisp::Token token(TokenType::SIGNED_INTEGER, "-9223372036854775808", std::nullopt, static_cast<int64_t>(-9223372036854775808));
    ASSERT_EQ(token.get_type(), TokenType::SIGNED_INTEGER);
    ASSERT_EQ(token.get_lexeme(), "-9223372036854775808");
    ASSERT_EQ(token.get_line_number(), std::nullopt);
    std::optional<int64_t> maybe_value = token.get_numeric_value<int64_t>();
    ASSERT_TRUE(maybe_value.has_value());
    ASSERT_EQ(maybe_value.value(), -9223372036854775808);
}

TEST(token_must_be_initialized_appropriately, floating_point_0_dot_0)
{
    yli::lisp::Token token(TokenType::FLOATING_POINT, "0.0", std::nullopt, 0.0);
    ASSERT_EQ(token.get_type(), TokenType::FLOATING_POINT);
    ASSERT_EQ(token.get_lexeme(), "0.0");
    ASSERT_EQ(token.get_line_number(), std::nullopt);
    std::optional<double> maybe_value = token.get_numeric_value<double>();
    ASSERT_TRUE(maybe_value.has_value());
    ASSERT_EQ(maybe_value.value(), 0.0);
}

TEST(token_must_be_initialized_appropriately, floating_point_3_dot_14159)
{
    yli::lisp::Token token(TokenType::FLOATING_POINT, "3.14159", std::nullopt, static_cast<double>(3.14159));
    ASSERT_EQ(token.get_type(), TokenType::FLOATING_POINT);
    ASSERT_EQ(token.get_lexeme(), "3.14159");
    ASSERT_EQ(token.get_line_number(), std::nullopt);
    std::optional<double> maybe_value = token.get_numeric_value<double>();
    ASSERT_TRUE(maybe_value.has_value());
    ASSERT_GT(maybe_value.value(), 3.14158);
    ASSERT_LT(maybe_value.value(), 3.14160);
}

TEST(token_must_be_initialized_appropriately, identifier_a_on_line_123)
{
    yli::lisp::Token token(TokenType::IDENTIFIER, "a", 123);
    ASSERT_EQ(token.get_type(), TokenType::IDENTIFIER);
    ASSERT_EQ(token.get_lexeme(), "a");
    ASSERT_EQ(token.get_line_number(), 123);
}
