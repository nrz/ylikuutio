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

#include "expr.hpp"

// Include standard headers
#include <stdexcept> // std::runtime_error
#include <memory>    // std::make_unique, std::unique_ptr
#include <utility>   // std::move
#include <variant>   // std::holds_alternative, std::monostate

namespace yli::lisp
{
    class Token;

    Expr::Expr(const Token& token, const ExprType expr_type)
        : token { token },
        type    { expr_type }
    {
    }

    bool Expr::operator==(const Expr& other) const
    {
        // Equal `Expr`s have identical data.
        return this->type == other.type && this->token == other.token;
    }

    bool Expr::operator!=(const Expr& other) const
    {
        return !this->operator==(other);
    }

    ExprType Expr::get_type() const
    {
        return this->type;
    }

    const Token& Expr::get_token() const
    {
        return this->token;
    }

    std::size_t Expr::get_number_of_children() const
    {
        return this->children.size();
    }

    const Expr& Expr::at(const std::size_t index) const
    {
        return *this->children.at(index);
    }

    Expr& Expr::last()
    {
        return *this->children.back();
    }

    void Expr::emplace_back(std::unique_ptr<Expr> expr)
    {
        this->children.emplace_back(std::move(expr));
    }
}
