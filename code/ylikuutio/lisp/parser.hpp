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

#ifndef YLIKUUTIO_LISP_PARSER_HPP_INCLUDED
#define YLIKUUTIO_LISP_PARSER_HPP_INCLUDED

#include "token_list.hpp"
#include "token.hpp"
#include "syntax_tree_list.hpp"
#include "error_log.hpp"
#include "error_type.hpp"

namespace yli::lisp
{
    class TextPosition;

    class Parser
    {
        // The parser works by keeping a stack of lists of tokens.
        // When an expression is completed, then the topmost list of tokens is taken from the stack.
        //
        // Example:
        // (foo (bar baz qux) quux)
        // 1. initialize the stack of lists of tokens.
        // 2. initialize the list of tokens on top of the stack.
        // 3. Upon foo, push foo to the list of tokens.
        // 4. Upon ( , initialize a new list of tokens and push it to the top of the stack.
        // 5. Upon bar,  push bar to the list of tokens.
        // 6. Upon bar,  push bar to the list of tokens.
        // 7. Upon ) , 
        //
        // foo
        // + bar
        // | + baz
        // | + qux
        // + quux

        public:
            explicit Parser(const TokenList& token_list);

            const SyntaxTreeList& get_syntax_tree_list() const;
            const ErrorLog& get_error_log() const;

            bool get_is_success() const;

        private:
            bool parse();

            void add_error(ErrorType error_type, const TextPosition& text_position);

            const TokenList& token_list;
            SyntaxTreeList syntax_tree_list;
            ErrorLog error_log;

            const bool is_success;
    };
}

#endif
