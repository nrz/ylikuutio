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

#include "parser.hpp"
#include "token_list.hpp"
#include "token.hpp"
#include "text_position.hpp"
#include "error_type.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <deque>   // std::deque
#include <stack>   // std::stack
#include <utility> // std::move

#include <iostream>

namespace yli::lisp
{
    class ErrorLog;

    Parser::Parser(const TokenList& token_list)
        : token_list { token_list },
        is_success { this->parse() }
    {
    }

    const SyntaxTreeList& Parser::get_syntax_tree_list() const
    {
        return this->syntax_tree_list;
    }

    const ErrorLog& Parser::get_error_log() const
    {
        return this->error_log;
    }

    bool Parser::get_is_success() const
    {
        return this->is_success;
    }

    bool Parser::parse()
    {
        std::stack<Token> paren_token_stack;

        Expr* current_parent { nullptr };
        std::stack<Expr*> parent_stack;

        for (std::size_t token_i = 0; token_i < this->token_list.data().size(); token_i++)
        {
            const Token& token = this->token_list.at(token_i);

            if (token.get_type() == TokenType::LEFT_PARENTHESIS)
            {
                // This token is the beginning of a parenthesis expression.
                paren_token_stack.push(token);
                parent_stack.push(current_parent);
                current_parent = nullptr;
            }
            else if (token.get_type() == TokenType::LEFT_SQUARE_BRACKET)
            {
                // This token is the beginning of a square bracket expression.
                paren_token_stack.push(token);
                parent_stack.push(current_parent);
                current_parent = nullptr;
            }
            else if (token.get_type() == TokenType::LEFT_CURLY_BRACE)
            {
                // This token is the beginning of a curly brace expression.
                paren_token_stack.push(token);
                parent_stack.push(current_parent);
                current_parent = nullptr;
            }
            else if (token.get_type() == TokenType::RIGHT_PARENTHESIS &&
                    !paren_token_stack.empty() &&
                    paren_token_stack.top().get_type() == TokenType::LEFT_PARENTHESIS &&
                    current_parent == nullptr)
            {
                // This token is the end of an empty parenthesized expression.
                // `()` is not supported. Use `null` instead.
                paren_token_stack.pop();

                // Restore the parent from stack (if any).
                current_parent = parent_stack.top();
                parent_stack.pop();

                // Error: empty parenthesis block.
                const TextPosition text_position = token.get_text_position();
                this->error_log.add_error(text_position, ErrorType::EMPTY_PARENTHESIS_BLOCK);
            }
            else if (token.get_type() == TokenType::RIGHT_PARENTHESIS &&
                    !paren_token_stack.empty() &&
                    paren_token_stack.top().get_type() == TokenType::LEFT_PARENTHESIS)
            {
                // This token is the end of a parenthesized expression.
                // The current expression is complete.
                paren_token_stack.pop();

                // Restore the parent from stack (if any).
                current_parent = parent_stack.top();
                parent_stack.pop();
            }
            else if (token.get_type() == TokenType::RIGHT_SQUARE_BRACKET &&
                    !paren_token_stack.empty() &&
                    paren_token_stack.top().get_type() == TokenType::LEFT_SQUARE_BRACKET)
            {
                // This token is the end of a horizontal concatenation.
                // The current expression is complete.
                paren_token_stack.pop();

                // Restore the parent from stack (if any).
                current_parent = parent_stack.top();
                parent_stack.pop();
            }
            else if (token.get_type() == TokenType::RIGHT_CURLY_BRACE &&
                    !paren_token_stack.empty() &&
                    paren_token_stack.top().get_type() == TokenType::LEFT_CURLY_BRACE)
            {
                // This token is the end of a vertical concatenation.
                // The current expression is complete.
                paren_token_stack.pop();

                // Restore the parent from stack (if any).
                current_parent = parent_stack.top();
                parent_stack.pop();
            }
            else if (token.get_type() == TokenType::RIGHT_PARENTHESIS &&
                    !paren_token_stack.empty() &&
                    paren_token_stack.top().get_type() == TokenType::LEFT_SQUARE_BRACKET)
            {
                // Error: left square bracket and right parenthesis do not match!
                const TextPosition text_position = token.get_text_position();
                this->error_log.add_error(text_position, ErrorType::LEFT_SQUARE_BRACKET_WITH_RIGHT_PARENTHESIS);
            }
            else if (token.get_type() == TokenType::RIGHT_PARENTHESIS &&
                    !paren_token_stack.empty() &&
                    paren_token_stack.top().get_type() == TokenType::LEFT_CURLY_BRACE)
            {
                // Error: left square bracket and right parenthesis do not match!
                const TextPosition text_position = token.get_text_position();
                this->error_log.add_error(text_position, ErrorType::LEFT_CURLY_BRACE_WITH_RIGHT_PARENTHESIS);
            }
            else if (token.get_type() == TokenType::RIGHT_SQUARE_BRACKET &&
                    !paren_token_stack.empty() &&
                    paren_token_stack.top().get_type() == TokenType::LEFT_PARENTHESIS)
            {
                // Error: left parenthesis and right square bracket do not match!
                const TextPosition text_position = token.get_text_position();
                this->error_log.add_error(text_position, ErrorType::LEFT_PARENTHESIS_WITH_RIGHT_SQUARE_BRACKET);
            }
            else if (token.get_type() == TokenType::RIGHT_SQUARE_BRACKET &&
                    !paren_token_stack.empty() &&
                    paren_token_stack.top().get_type() == TokenType::LEFT_CURLY_BRACE)
            {
                // Error: left parenthesis and right square bracket do not match!
                const TextPosition text_position = token.get_text_position();
                this->error_log.add_error(text_position, ErrorType::LEFT_CURLY_BRACE_WITH_RIGHT_SQUARE_BRACKET);
            }
            else if (token.get_type() == TokenType::RIGHT_CURLY_BRACE &&
                    !paren_token_stack.empty() &&
                    paren_token_stack.top().get_type() == TokenType::LEFT_PARENTHESIS)
            {
                // Error: left parenthesis and right curly brace do not match!
                const TextPosition text_position = token.get_text_position();
                this->error_log.add_error(text_position, ErrorType::LEFT_PARENTHESIS_WITH_RIGHT_CURLY_BRACE);
            }
            else if (token.get_type() == TokenType::RIGHT_CURLY_BRACE &&
                    !paren_token_stack.empty() &&
                    paren_token_stack.top().get_type() == TokenType::LEFT_SQUARE_BRACKET)
            {
                // Error: left square bracket and right curly brace do not match!
                const TextPosition text_position = token.get_text_position();
                this->error_log.add_error(text_position, ErrorType::LEFT_SQUARE_BRACKET_WITH_RIGHT_CURLY_BRACE);
            }
            else if (token.get_type() == TokenType::RIGHT_PARENTHESIS)
            {
                // Error: no matching left parenthesis!
                const TextPosition text_position = token.get_text_position();
                this->error_log.add_error(text_position, ErrorType::MATCHING_LEFT_PARENTHESIS_MISSING);
            }
            else if (token.get_type() == TokenType::IDENTIFIER && current_parent == nullptr && paren_token_stack.empty())
            {
                // This is a top-level identifier evaluation.
                this->syntax_tree_list.emplace_back(Expr(token));
            }
            else if (token.get_type() == TokenType::IDENTIFIER && current_parent == nullptr && paren_token_stack.size() == 1)
            {
                // This is a top-level function call.
                Token function_call = token;
                function_call.set_type(TokenType::FUNCTION_CALL);
                this->syntax_tree_list.emplace_back(Expr(function_call));
                current_parent = this->syntax_tree_list.last();
            }
            else if (token.get_type() == TokenType::IDENTIFIER && current_parent == nullptr)
            {
                // This is a function call (not top level).
                Expr* parent_expr = parent_stack.top();

                Token function_call = token;
                function_call.set_type(TokenType::FUNCTION_CALL);
                parent_expr->emplace_back(Expr(function_call));
                current_parent = &parent_expr->last();
            }
            else if (!paren_token_stack.empty() && current_parent == nullptr)
            {
                // Syntax error: an identifier is expected after opening parenthesis.
                const TextPosition text_position = token.get_text_position();
                this->error_log.add_error(text_position, ErrorType::FUNCTION_CALL_EXPECTED);
            }
            else if (token.get_type() == TokenType::IDENTIFIER && !paren_token_stack.empty())
            {
                // This is an identifier given as argument.
                current_parent->emplace_back(Expr(token));
            }
            else if (token.get_type() == TokenType::QUOTE)
            {
                // TODO: implement quoting!
            }
            else if (token.get_type() == TokenType::DOT)
            {
                // TODO: implement member access!
            }
            else if (token.get_type() == TokenType::STRING && current_parent != nullptr)
            {
                // String argument.
                current_parent->emplace_back(Expr(token));
            }
            else if (token.get_type() == TokenType::UNSIGNED_INTEGER && current_parent != nullptr)
            {
                // Unsigned integer argument.
                current_parent->emplace_back(Expr(token));
            }
            else if (token.get_type() == TokenType::SIGNED_INTEGER && current_parent != nullptr)
            {
                // Signed integer argument.
                current_parent->emplace_back(Expr(token));
            }
            else if (token.get_type() == TokenType::FLOATING_POINT && current_parent != nullptr)
            {
                // Floating point number argument.
                current_parent->emplace_back(Expr(token));
            }
            else if (paren_token_stack.empty())
            {
                // This is a non-parenthesized expression.
                this->syntax_tree_list.emplace_back(Expr(token));
            }
        }

        while (!paren_token_stack.empty())
        {
            Token token = paren_token_stack.top();
            paren_token_stack.pop();
            const TextPosition text_position = token.get_text_position();
            this->error_log.add_error(text_position, ErrorType::MATCHING_RIGHT_PARENTHESIS_MISSING);
        }

        return this->error_log.empty();
    }

    void Parser::add_error(ErrorType error_type, const TextPosition& text_position)
    {
        this->error_log.add_error(text_position, error_type);
    }
}
