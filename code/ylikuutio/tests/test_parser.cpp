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
#include "code/ylikuutio/lisp/parser.hpp"
#include "code/ylikuutio/lisp/syntax_tree_list.hpp"
#include "code/ylikuutio/lisp/error_log.hpp"
#include "code/ylikuutio/lisp/error.hpp"
#include "code/ylikuutio/lisp/error_type.hpp"
#include "code/ylikuutio/lisp/expr.hpp"
#include "code/ylikuutio/lisp/token.hpp"
#include "code/ylikuutio/lisp/token_type.hpp"
#include "code/ylikuutio/lisp/text_position.hpp"

// Include standard headers
#include <optional>    // std::nullopt
#include <string_view> // std::string_view
#include <variant>     // std::holds_alternative

using yli::lisp::Scanner;
using yli::lisp::Parser;
using yli::lisp::SyntaxTreeList;
using yli::lisp::ErrorLog;
using yli::lisp::Error;
using yli::lisp::ErrorType;
using yli::lisp::Expr;
using yli::lisp::Token;
using yli::lisp::TokenType;
using yli::lisp::TextPosition;

TEST(string_must_be_parsed_appropriately, empty_string)
{
    const std::string_view empty_string { "" };
    const Scanner scanner(empty_string);
    const Parser parser(scanner.get_token_list());
    ASSERT_TRUE(parser.get_is_success());
    const SyntaxTreeList& syntax_tree_list = parser.get_syntax_tree_list();
    ASSERT_TRUE(syntax_tree_list.empty());
    const ErrorLog& error_log = parser.get_error_log();
    ASSERT_TRUE(error_log.empty());
}

TEST(string_must_be_parsed_appropriately, foo_string_literal)
{
    const std::string_view foo_string { R"("foo")" };
    const Scanner scanner(foo_string);
    const Parser parser(scanner.get_token_list());
    ASSERT_TRUE(parser.get_is_success());
    const SyntaxTreeList& syntax_tree_list = parser.get_syntax_tree_list();
    ASSERT_EQ(syntax_tree_list.size(), 1);

    {
        const Expr& expr = syntax_tree_list.at(0);
        ASSERT_EQ(expr.get_number_of_children(), 0);
        const Token& parsed_token = expr.get_token();
        TextPosition text_position(foo_string.cbegin(), foo_string.cend());
        const Token expected_token(TokenType::STRING, "foo", text_position);
        ASSERT_EQ(parsed_token, expected_token);
    }

    const ErrorLog& error_log = parser.get_error_log();
    ASSERT_TRUE(error_log.empty());
}

TEST(string_must_be_parsed_appropriately, foo_bar_string_literals)
{
    const std::string_view foo_bar_string { R"("foo" "bar")" };
    const Scanner scanner(foo_bar_string);
    const Parser parser(scanner.get_token_list());
    ASSERT_TRUE(parser.get_is_success());
    const SyntaxTreeList& syntax_tree_list = parser.get_syntax_tree_list();
    ASSERT_EQ(syntax_tree_list.size(), 2);

    {
        const Expr& expr = syntax_tree_list.at(0);
        ASSERT_EQ(expr.get_number_of_children(), 0);
        const Token& parsed_token = expr.get_token();
        TextPosition text_position(foo_bar_string.cbegin(), foo_bar_string.cend());
        const Token expected_token(TokenType::STRING, "foo", text_position);
        ASSERT_EQ(parsed_token, expected_token);
    }
    {
        const Expr& expr = syntax_tree_list.at(1);
        ASSERT_EQ(expr.get_number_of_children(), 0);
        const Token& parsed_token = expr.get_token();
        TextPosition text_position(foo_bar_string.cbegin(), foo_bar_string.cend());
        const Token expected_token(TokenType::STRING, "bar", text_position);
        ASSERT_EQ(parsed_token, expected_token);
    }

    const ErrorLog& error_log = parser.get_error_log();
    ASSERT_TRUE(error_log.empty());
}

TEST(string_must_be_parsed_appropriately, foo_identifier)
{
    const std::string_view foo_identifier_string { "foo" };
    const Scanner scanner(foo_identifier_string);
    const Parser parser(scanner.get_token_list());
    ASSERT_TRUE(parser.get_is_success());
    const SyntaxTreeList& syntax_tree_list = parser.get_syntax_tree_list();
    ASSERT_EQ(syntax_tree_list.size(), 1);

    {
        const Expr& expr = syntax_tree_list.at(0);
        ASSERT_EQ(expr.get_number_of_children(), 0);
        const Token& parsed_token = expr.get_token();
        TextPosition text_position(foo_identifier_string.cbegin(), foo_identifier_string.cend());
        const Token expected_token(TokenType::IDENTIFIER, "foo", text_position);
        ASSERT_EQ(parsed_token, expected_token);
    }

    const ErrorLog& error_log = parser.get_error_log();
    ASSERT_TRUE(error_log.empty());
}

TEST(string_must_be_parsed_appropriately, foo_bar_identifiers)
{
    const std::string_view foo_bar_identifiers_string { "foo bar" };
    const Scanner scanner(foo_bar_identifiers_string);
    const Parser parser(scanner.get_token_list());
    ASSERT_TRUE(parser.get_is_success());
    const SyntaxTreeList& syntax_tree_list = parser.get_syntax_tree_list();
    ASSERT_EQ(syntax_tree_list.size(), 2);

    {
        const Expr& expr = syntax_tree_list.at(0);
        ASSERT_EQ(expr.get_number_of_children(), 0);
        const Token& parsed_token = expr.get_token();
        TextPosition text_position(foo_bar_identifiers_string.cbegin(), foo_bar_identifiers_string.cend());
        const Token expected_token(TokenType::IDENTIFIER, "foo", text_position);
        ASSERT_EQ(parsed_token, expected_token);
    }
    {
        const Expr& expr = syntax_tree_list.at(1);
        ASSERT_EQ(expr.get_number_of_children(), 0);
        const Token& parsed_token = expr.get_token();
        TextPosition text_position(foo_bar_identifiers_string.cbegin(), foo_bar_identifiers_string.cend());
        const Token expected_token(TokenType::IDENTIFIER, "bar", text_position);
        ASSERT_EQ(parsed_token, expected_token);
    }

    const ErrorLog& error_log = parser.get_error_log();
    ASSERT_TRUE(error_log.empty());
}

TEST(string_must_be_parsed_appropriately, block_with_foo_identifier)
{
    const std::string_view block_with_foo_identifier_string { "(foo)" };
    const Scanner scanner(block_with_foo_identifier_string);
    const Parser parser(scanner.get_token_list());
    ASSERT_TRUE(parser.get_is_success());
    const SyntaxTreeList& syntax_tree_list = parser.get_syntax_tree_list();
    ASSERT_EQ(syntax_tree_list.size(), 1);

    {
        const Expr& expr = syntax_tree_list.at(0);
        ASSERT_EQ(expr.get_number_of_children(), 0);
        const Token& token = expr.get_token();
        ASSERT_EQ(token.get_type(), TokenType::FUNCTION_CALL);
        ASSERT_EQ(token.get_lexeme(), "foo");
    }

    const ErrorLog& error_log = parser.get_error_log();
    ASSERT_TRUE(error_log.empty());
}

TEST(string_must_be_parsed_appropriately, block_with_foo_identifier_and_block_with_bar_identifier)
{
    const std::string_view block_with_foo_identifier_and_block_with_bar_identifier_string { "(foo) (bar)" };
    const Scanner scanner(block_with_foo_identifier_and_block_with_bar_identifier_string);
    const Parser parser(scanner.get_token_list());
    ASSERT_TRUE(parser.get_is_success());
    const SyntaxTreeList& syntax_tree_list = parser.get_syntax_tree_list();
    ASSERT_EQ(syntax_tree_list.size(), 2);

    {
        const Expr& expr = syntax_tree_list.at(0);
        ASSERT_EQ(expr.get_number_of_children(), 0);
        const Token& token = expr.get_token();
        ASSERT_EQ(token.get_type(), TokenType::FUNCTION_CALL);
        ASSERT_EQ(token.get_lexeme(), "foo");
    }
    {
        const Expr& expr = syntax_tree_list.at(1);
        ASSERT_EQ(expr.get_number_of_children(), 0);
        const Token& token = expr.get_token();
        ASSERT_EQ(token.get_type(), TokenType::FUNCTION_CALL);
        ASSERT_EQ(token.get_lexeme(), "bar");
    }

    const ErrorLog& error_log = parser.get_error_log();
    ASSERT_TRUE(error_log.empty());
}

TEST(string_must_be_parsed_appropriately, block_with_foo_bar_identifiers)
{
    const std::string_view block_with_foo_bar_identifiers_string { "(foo bar)" };
    const Scanner scanner(block_with_foo_bar_identifiers_string);
    const Parser parser(scanner.get_token_list());
    ASSERT_TRUE(parser.get_is_success());
    const SyntaxTreeList& syntax_tree_list = parser.get_syntax_tree_list();
    ASSERT_EQ(syntax_tree_list.size(), 1);

    {
        const Expr& foo_expr = syntax_tree_list.at(0);
        ASSERT_EQ(foo_expr.get_number_of_children(), 1);
        const Token& foo_token = foo_expr.get_token();
        ASSERT_EQ(foo_token.get_type(), TokenType::FUNCTION_CALL);
        ASSERT_EQ(foo_token.get_lexeme(), "foo");

        const Expr& bar_expr = foo_expr.at(0);
        ASSERT_EQ(bar_expr.get_number_of_children(), 0);
        const Token& bar_token = bar_expr.get_token();
        ASSERT_EQ(bar_token.get_type(), TokenType::IDENTIFIER);
        ASSERT_EQ(bar_token.get_lexeme(), "bar");
    }

    const ErrorLog& error_log = parser.get_error_log();
    ASSERT_TRUE(error_log.empty());
}

TEST(string_must_be_parsed_appropriately, block_with_foo_bar_baz_identifiers)
{
    const std::string_view block_with_foo_bar_identifiers_string { "(foo bar baz)" };
    const Scanner scanner(block_with_foo_bar_identifiers_string);
    const Parser parser(scanner.get_token_list());
    ASSERT_TRUE(parser.get_is_success());
    const SyntaxTreeList& syntax_tree_list = parser.get_syntax_tree_list();
    ASSERT_EQ(syntax_tree_list.size(), 1);

    {
        const Expr& foo_expr = syntax_tree_list.at(0);
        ASSERT_EQ(foo_expr.get_number_of_children(), 2);
        const Token& foo_token = foo_expr.get_token();
        ASSERT_EQ(foo_token.get_type(), TokenType::FUNCTION_CALL);
        ASSERT_EQ(foo_token.get_lexeme(), "foo");

        const Expr& bar_expr = foo_expr.at(0);
        ASSERT_EQ(bar_expr.get_number_of_children(), 0);
        const Token& bar_token = bar_expr.get_token();
        ASSERT_EQ(bar_token.get_type(), TokenType::IDENTIFIER);
        ASSERT_EQ(bar_token.get_lexeme(), "bar");

        const Expr& baz_expr = foo_expr.at(1);
        ASSERT_EQ(baz_expr.get_number_of_children(), 0);
        const Token& baz_token = baz_expr.get_token();
        ASSERT_EQ(baz_token.get_type(), TokenType::IDENTIFIER);
        ASSERT_EQ(baz_token.get_lexeme(), "baz");
    }

    const ErrorLog& error_log = parser.get_error_log();
    ASSERT_TRUE(error_log.empty());
}

TEST(string_must_be_parsed_appropriately, block_with_foo_with_block_with_bar_identifiers)
{
    const std::string_view block_with_foo_with_block_with_bar_identifiers_string { "(foo (bar))" };
    const Scanner scanner(block_with_foo_with_block_with_bar_identifiers_string);
    const Parser parser(scanner.get_token_list());
    ASSERT_TRUE(parser.get_is_success());
    const SyntaxTreeList& syntax_tree_list = parser.get_syntax_tree_list();
    ASSERT_EQ(syntax_tree_list.size(), 1);

    {
        const Expr& foo_expr = syntax_tree_list.at(0);
        ASSERT_EQ(foo_expr.get_number_of_children(), 1);
        const Token& foo_token = foo_expr.get_token();
        ASSERT_EQ(foo_token.get_type(), TokenType::FUNCTION_CALL);
        ASSERT_EQ(foo_token.get_lexeme(), "foo");

        const Expr& bar_expr = foo_expr.at(0);
        ASSERT_EQ(bar_expr.get_number_of_children(), 0);
        const Token& bar_token = bar_expr.get_token();
        ASSERT_EQ(bar_token.get_type(), TokenType::FUNCTION_CALL);
        ASSERT_EQ(bar_token.get_lexeme(), "bar");
    }

    const ErrorLog& error_log = parser.get_error_log();
    ASSERT_TRUE(error_log.empty());
}

TEST(string_must_be_parsed_appropriately, block_with_foo_with_block_with_bar_with_block_with_baz_identifiers)
{
    const std::string_view block_with_foo_with_block_with_bar_with_block_with_baz_identifiers_string { "(foo (bar (baz)))" };
    const Scanner scanner(block_with_foo_with_block_with_bar_with_block_with_baz_identifiers_string);
    const Parser parser(scanner.get_token_list());
    ASSERT_TRUE(parser.get_is_success());
    const SyntaxTreeList& syntax_tree_list = parser.get_syntax_tree_list();
    ASSERT_EQ(syntax_tree_list.size(), 1);

    {
        const Expr& foo_expr = syntax_tree_list.at(0);
        ASSERT_EQ(foo_expr.get_number_of_children(), 1);
        const Token& foo_token = foo_expr.get_token();
        ASSERT_EQ(foo_token.get_type(), TokenType::FUNCTION_CALL);
        ASSERT_EQ(foo_token.get_lexeme(), "foo");

        const Expr& bar_expr = foo_expr.at(0);
        ASSERT_EQ(bar_expr.get_number_of_children(), 1);
        const Token& bar_token = bar_expr.get_token();
        ASSERT_EQ(bar_token.get_type(), TokenType::FUNCTION_CALL);
        ASSERT_EQ(bar_token.get_lexeme(), "bar");

        const Expr& baz_expr = bar_expr.at(0);
        ASSERT_EQ(baz_expr.get_number_of_children(), 0);
        const Token& baz_token = baz_expr.get_token();
        ASSERT_EQ(baz_token.get_type(), TokenType::FUNCTION_CALL);
        ASSERT_EQ(baz_token.get_lexeme(), "baz");
    }

    const ErrorLog& error_log = parser.get_error_log();
    ASSERT_TRUE(error_log.empty());
}

TEST(string_must_be_parsed_appropriately, one_plus_two)
{
    const std::string_view one_plus_two_string { "(+ 1 2)" };
    const Scanner scanner(one_plus_two_string);
    const Parser parser(scanner.get_token_list());
    ASSERT_TRUE(parser.get_is_success());
    const SyntaxTreeList& syntax_tree_list = parser.get_syntax_tree_list();
    ASSERT_EQ(syntax_tree_list.size(), 1);

    {
        const Expr& plus_expr = syntax_tree_list.at(0);
        ASSERT_EQ(plus_expr.get_number_of_children(), 2);
        const Token& plus_token = plus_expr.get_token();
        ASSERT_EQ(plus_token.get_type(), TokenType::FUNCTION_CALL);
        ASSERT_EQ(plus_token.get_lexeme(), "+");

        const Expr& one_expr = plus_expr.at(0);
        ASSERT_EQ(one_expr.get_number_of_children(), 0);
        const Token& one_token = one_expr.get_token();
        ASSERT_EQ(one_token.get_type(), TokenType::UNSIGNED_INTEGER);
        ASSERT_EQ(one_token.get_lexeme(), "1");

        const Expr& two_expr = plus_expr.at(1);
        ASSERT_EQ(two_expr.get_number_of_children(), 0);
        const Token& two_token = two_expr.get_token();
        ASSERT_EQ(two_token.get_type(), TokenType::UNSIGNED_INTEGER);
        ASSERT_EQ(two_token.get_lexeme(), "2");
    }

    const ErrorLog& error_log = parser.get_error_log();
    ASSERT_TRUE(error_log.empty());
}

TEST(string_must_be_parsed_appropriately, pi_times_r_squared)
{
    const std::string_view pi_times_r_squared_string { "(* 3.14 (* r r))" };
    const Scanner scanner(pi_times_r_squared_string);
    const Parser parser(scanner.get_token_list());
    ASSERT_TRUE(parser.get_is_success());
    const SyntaxTreeList& syntax_tree_list = parser.get_syntax_tree_list();
    ASSERT_EQ(syntax_tree_list.size(), 1);

    {
        const Expr& outer_multiplication_expr = syntax_tree_list.at(0);
        {
            ASSERT_EQ(outer_multiplication_expr.get_number_of_children(), 2);
            const Token& outer_multiplication_token = outer_multiplication_expr.get_token();
            ASSERT_EQ(outer_multiplication_token.get_type(), TokenType::FUNCTION_CALL);
            ASSERT_EQ(outer_multiplication_token.get_lexeme(), "*");
        }

        const Expr& pi_expr = outer_multiplication_expr.at(0);
        {
            ASSERT_EQ(pi_expr.get_number_of_children(), 0);
            const Token& pi_token = pi_expr.get_token();
            ASSERT_EQ(pi_token.get_type(), TokenType::FLOATING_POINT);
            ASSERT_EQ(pi_token.get_lexeme(), "3.14");
        }

        const Expr& inner_multiplication_expr = outer_multiplication_expr.at(1);
        {
            ASSERT_EQ(inner_multiplication_expr.get_number_of_children(), 2);
            const Token& inner_multiplication_token = inner_multiplication_expr.get_token();
            ASSERT_EQ(inner_multiplication_token.get_type(), TokenType::FUNCTION_CALL);
            ASSERT_EQ(inner_multiplication_token.get_lexeme(), "*");
        }

        const Expr& first_r_expr = inner_multiplication_expr.at(0);
        {
            ASSERT_EQ(first_r_expr.get_number_of_children(), 0);
            const Token& first_r_token = first_r_expr.get_token();
            ASSERT_EQ(first_r_token.get_type(), TokenType::IDENTIFIER);
            ASSERT_EQ(first_r_token.get_lexeme(), "r");
        }

        const Expr& second_r_expr = inner_multiplication_expr.at(1);
        {
            ASSERT_EQ(second_r_expr.get_number_of_children(), 0);
            const Token& second_r_token = second_r_expr.get_token();
            ASSERT_EQ(second_r_token.get_type(), TokenType::IDENTIFIER);
            ASSERT_EQ(second_r_token.get_lexeme(), "r");
        }
    }
}

// Failing parses.

TEST(string_parsing_must_fail_appropriately, left_paren)
{
    const std::string_view left_paren_string { "(" };
    const Scanner scanner(left_paren_string);
    const Parser parser(scanner.get_token_list());
    ASSERT_FALSE(parser.get_is_success());
    const ErrorLog& error_log = parser.get_error_log();
    ASSERT_EQ(error_log.size(), 1);
    const Error& error = error_log.at(0);
    ASSERT_EQ(error.get_filename(), "");
    ASSERT_EQ(error.get_line(), 1);
    ASSERT_EQ(error.get_column(), 1);
    ASSERT_EQ(error.get_type(), ErrorType::MATCHING_RIGHT_PARENTHESIS_MISSING);
}

TEST(string_parsing_must_fail_appropriately, right_paren)
{
    const std::string_view right_paren_string { ")" };
    const Scanner scanner(right_paren_string);
    const Parser parser(scanner.get_token_list());
    ASSERT_FALSE(parser.get_is_success());
    const ErrorLog& error_log = parser.get_error_log();
    ASSERT_EQ(error_log.size(), 1);
    const Error& error = error_log.at(0);
    ASSERT_EQ(error.get_filename(), "");
    ASSERT_EQ(error.get_line(), 1);
    ASSERT_EQ(error.get_column(), 1);
    ASSERT_EQ(error.get_type(), ErrorType::MATCHING_LEFT_PARENTHESIS_MISSING);
}

TEST(string_parsing_must_fail_appropriately, empty_block_string)
{
    const std::string_view empty_block_string { "()" };
    const Scanner scanner(empty_block_string);
    const Parser parser(scanner.get_token_list());
    ASSERT_FALSE(parser.get_is_success());
    const ErrorLog& error_log = parser.get_error_log();
    ASSERT_EQ(error_log.size(), 1);
    ASSERT_EQ(error_log.at(0).get_type(), ErrorType::EMPTY_PARENTHESIS_BLOCK);
}

TEST(string_parsing_must_fail_appropriately, two_empty_blocks_string)
{
    const std::string_view two_empty_blocks_string { "()()" };
    const Scanner scanner(two_empty_blocks_string);
    const Parser parser(scanner.get_token_list());
    ASSERT_FALSE(parser.get_is_success());
    const ErrorLog& error_log = parser.get_error_log();
    ASSERT_EQ(error_log.size(), 2);
    ASSERT_EQ(error_log.at(0).get_type(), ErrorType::EMPTY_PARENTHESIS_BLOCK);
    ASSERT_EQ(error_log.at(1).get_type(), ErrorType::EMPTY_PARENTHESIS_BLOCK);
}

TEST(string_parsing_must_fail_appropriately, three_empty_blocks_string)
{
    const std::string_view three_empty_blocks_string { "()()()" };
    const Scanner scanner(three_empty_blocks_string);
    const Parser parser(scanner.get_token_list());
    ASSERT_FALSE(parser.get_is_success());
    const ErrorLog& error_log = parser.get_error_log();
    ASSERT_EQ(error_log.size(), 3);
    ASSERT_EQ(error_log.at(0).get_type(), ErrorType::EMPTY_PARENTHESIS_BLOCK);
    ASSERT_EQ(error_log.at(1).get_type(), ErrorType::EMPTY_PARENTHESIS_BLOCK);
    ASSERT_EQ(error_log.at(2).get_type(), ErrorType::EMPTY_PARENTHESIS_BLOCK);
}
