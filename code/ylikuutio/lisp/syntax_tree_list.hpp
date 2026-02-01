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

#ifndef YLIKUUTIO_LISP_SYNTAX_TREE_LIST_HPP_INCLUDED
#define YLIKUUTIO_LISP_SYNTAX_TREE_LIST_HPP_INCLUDED

#include "expr.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <deque>   // std::deque

namespace yli::lisp
{
    class SyntaxTreeList
    {
        public:
            SyntaxTreeList();

            const std::deque<Expr>& data() const;

            const Expr& at(const std::size_t i) const;
            Expr* last();

            bool empty() const;
            std::size_t size() const;

            void emplace_back(Expr&& expr);

        private:
            std::deque<Expr> syntax_trees; // We want to keep expressions in stable memory addresses thus `std::vector` won't do.
    };
}

#endif
