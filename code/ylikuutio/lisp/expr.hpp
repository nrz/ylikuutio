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

#ifndef YLIKUUTIO_LISP_EXPR_HPP_INCLUDED
#define YLIKUUTIO_LISP_EXPR_HPP_INCLUDED

#include "expr_type.hpp"
#include "token.hpp"
#include "code/ylikuutio/data/codepoint.hpp"

// Include standard headers
#include <memory>  // std::unique_ptr
#include <variant> // std::monostate, std::variant
#include <vector>  // std::vector

namespace yli::lisp
{
    class Expr
    {
        // YliLisp expression grammar:
        //
        // expression  -> atom
        //             -> fun-call
        //             -> matrix
        //             -> string-cat
        //
        // atom        -> IDENTIFIER
        //             -> STRING
        //             -> NUMBER
        //             -> #t
        //             -> #f
        //             -> null
        //
        // fun-call    -> "(" IDENTIFIER ")"
        // fun-call    -> "(" IDENTIFIER expression ")"
        //
        // matrix      -> horiz-cat
        // matrix      -> vert-cat
        //
        // horiz-cat   -> "[" numbers  "]"
        // horiz-cat   -> "[" matrices "]"
        //
        // vert-cat    -> "{" numbers  "}"
        // vert-cat    -> "{" matrices "}"
        //
        // matrices    -> matrix matrices
        // matrices    -> matrix
        //
        // numbers     -> NUMBER numbers
        // numbers     -> NUMBER
        //
        // string-cat  -> "[" strings "]"
        // strings     -> STRING strings
        // strings     -> STRING
        //
        // string-cat  -> "{" strings "}"
        // strings     -> STRING strings
        // strings     -> STRING

        public:
            // Terminal expression.
            explicit Expr(const Token& expr);

            bool operator==(const Expr& other) const; // Equal `Expr`s have identical data.
            bool operator!=(const Expr& other) const;

            ExprType get_type() const;
            const Token& get_token() const;
            const Expr& at(const std::size_t index) const;
            Expr& last();

            std::size_t get_number_of_children() const;

            void emplace_back(std::unique_ptr<Expr> expr);

        private:
            ExprType type;
            Token token;

            // Every expression may either terminal expressions or it may consist of subexpressions (children `Expr` instances).
            std::vector<std::unique_ptr<Expr>> children;
    };
}

#endif
