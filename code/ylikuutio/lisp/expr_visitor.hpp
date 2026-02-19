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

#ifndef YLIKUUTIO_LISP_EXPR_VISITOR_HPP_INCLUDED
#define YLIKUUTIO_LISP_EXPR_VISITOR_HPP_INCLUDED

namespace yli::lisp
{
    class IdentifierExpr;
    class LiteralExpr;
    class FunctionCallExpr;
    class DefunExpr;
    class LambdaExpr;

    class ExprVisitor
    {
        public:
            virtual void visit_identifier_expr(IdentifierExpr& identifier_expr) = 0;
            virtual void visit_literal_expr(LiteralExpr& literal_expr) = 0;
            virtual void visit_function_call_expr(FunctionCallExpr& function_call_expr) = 0;
            virtual void visit_defun_expr(DefunExpr& defun_expr) = 0;
            virtual void visit_lambda_expr(LambdaExpr& lambda_expr) = 0;
    };
}

#endif
