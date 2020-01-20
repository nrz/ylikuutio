// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
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

#include "ascendant.hpp"

// Include standard headers
#include <cstddef> // std::size_t

namespace yli
{
    namespace ontology
    {
        class Entity;

        Ascendant::~Ascendant()
        {
            // destructor.
        }

        yli::ontology::Entity* Ascendant::get_parent() const
        {
            return nullptr;
        }

        std::size_t Ascendant::get_number_of_children() const
        {
            return this->parent_module.number_of_children;
        }

        std::size_t Ascendant::get_number_of_descendants() const
        {
            return this->parent_module.get_number_of_descendants();
        }
    }
}
