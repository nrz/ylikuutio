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

#include "token_list.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <utility> // std::move
#include <vector>  // std::vector

namespace yli::lisp
{
    void TokenList::add_token(Token&& token)
    {
        this->tokens.emplace_back(std::move(token));
    }

    const Token& TokenList::at(const std::size_t index) const
    {
        return this->tokens.at(index);
    }

    const std::vector<Token>& TokenList::data() const
    {
        return this->tokens;
    }

    bool TokenList::empty() const
    {
        return this->tokens.empty();
    }

    std::size_t TokenList::size() const
    {
        return this->tokens.size();
    }
}
