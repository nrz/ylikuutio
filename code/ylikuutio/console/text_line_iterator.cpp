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

#include "text_line_iterator.hpp"
#include "text_line_const_iterator.hpp"

namespace yli::console
{
    bool TextLineIterator::operator==(const TextLineConstIterator& other_it) const
    {
        return this->it == other_it.it;
    }

    bool TextLineIterator::operator!=(const TextLineConstIterator& other_it) const
    {
        return this->it != other_it.it;
    }
}
