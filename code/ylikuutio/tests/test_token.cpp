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
#include <string_view> // std::u32string_view

using yli::lisp::TokenType;

TEST(token_must_be_initialized_appropriately, left_parenthesis)
{
    yli::lisp::Token a_token(TokenType::LEFT_PARENTHESIS, U"(");
    ASSERT_EQ(a_token.get_type(), TokenType::LEFT_PARENTHESIS);
    ASSERT_EQ(a_token.get_lexeme(), U"(");
}

TEST(token_must_be_initialized_appropriately, right_parenthesis)
{
    yli::lisp::Token a_token(TokenType::RIGHT_PARENTHESIS, U")");
    ASSERT_EQ(a_token.get_type(), TokenType::RIGHT_PARENTHESIS);
    ASSERT_EQ(a_token.get_lexeme(), U")");
}

TEST(token_must_be_initialized_appropriately, quote)
{
    yli::lisp::Token a_token(TokenType::QUOTE, U"'");
    ASSERT_EQ(a_token.get_type(), TokenType::QUOTE);
    ASSERT_EQ(a_token.get_lexeme(), U"'");
}

TEST(token_must_be_initialized_appropriately, dot)
{
    yli::lisp::Token a_token(TokenType::DOT, U".");
    ASSERT_EQ(a_token.get_type(), TokenType::DOT);
    ASSERT_EQ(a_token.get_lexeme(), U".");
}

TEST(token_must_be_initialized_appropriately, semicolon)
{
    yli::lisp::Token a_token(TokenType::SEMICOLON, U";");
    ASSERT_EQ(a_token.get_type(), TokenType::SEMICOLON);
    ASSERT_EQ(a_token.get_lexeme(), U";");
}

TEST(token_must_be_initialized_appropriately, identifier_a)
{
    yli::lisp::Token a_token(TokenType::IDENTIFIER, U"a");
    ASSERT_EQ(a_token.get_type(), TokenType::IDENTIFIER);
    ASSERT_EQ(a_token.get_lexeme(), U"a");
}

TEST(token_must_be_initialized_appropriately, identifier_abc)
{
    yli::lisp::Token a_token(TokenType::IDENTIFIER, U"abc");
    ASSERT_EQ(a_token.get_type(), TokenType::IDENTIFIER);
    ASSERT_EQ(a_token.get_lexeme(), U"abc");
}

TEST(token_must_be_initialized_appropriately, string_a)
{
    yli::lisp::Token a_token(TokenType::STRING, UR"("a")");
    ASSERT_EQ(a_token.get_type(), TokenType::STRING);
    ASSERT_EQ(a_token.get_lexeme(), UR"("a")");
}

TEST(token_must_be_initialized_appropriately, string_abc)
{
    yli::lisp::Token a_token(TokenType::STRING, UR"("abc")");
    ASSERT_EQ(a_token.get_type(), TokenType::STRING);
    ASSERT_EQ(a_token.get_lexeme(), UR"("abc")");
}

TEST(token_must_be_initialized_appropriately, number_0)
{
    yli::lisp::Token a_token(TokenType::NUMBER, U"0");
    ASSERT_EQ(a_token.get_type(), TokenType::NUMBER);
    ASSERT_EQ(a_token.get_lexeme(), U"0");
}

TEST(token_must_be_initialized_appropriately, number_3_dot_14159)
{
    yli::lisp::Token a_token(TokenType::NUMBER, U"3.14159");
    ASSERT_EQ(a_token.get_type(), TokenType::NUMBER);
    ASSERT_EQ(a_token.get_lexeme(), U"3.14159");
}
