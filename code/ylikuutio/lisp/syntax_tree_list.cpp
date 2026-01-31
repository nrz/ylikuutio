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

#include "syntax_tree_list.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <deque>   // std::deque
#include <utility> // std::move

namespace yli::lisp
{
    class Expr;

    SyntaxTreeList::SyntaxTreeList()
    {
    }

    const std::deque<Expr>& SyntaxTreeList::data() const
    {
        return this->syntax_trees;
    }

    const Expr& SyntaxTreeList::at(const std::size_t i) const
    {
        return this->syntax_trees.at(i);
    }

    Expr* SyntaxTreeList::last()
    {
        if (this->syntax_trees.empty()) [[unlikely]]
        {
            return nullptr;
        }

        return &this->syntax_trees.back();
    }

    bool SyntaxTreeList::empty() const
    {
        return this->syntax_trees.empty();
    }

    std::size_t SyntaxTreeList::size() const
    {
        return this->syntax_trees.size();
    }

    void SyntaxTreeList::emplace_back(Expr&& expr)
    {
        this->syntax_trees.emplace_back(std::move(expr));
    }
}
