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

#include "identifier_expr.hpp"
#include "expr.hpp"
#include "expr_type.hpp"
#include "expr_visitor.hpp"

namespace yli::lisp
{
    class Token;

    IdentifierExpr::IdentifierExpr(const Token& token)
        : Expr(token, ExprType::IDENTIFIER)
    {
    }

    void IdentifierExpr::accept(ExprVisitor& visitor)
    {
        visitor.visit_identifier_expr(*this);
    }
}
