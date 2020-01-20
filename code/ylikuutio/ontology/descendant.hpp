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

#ifndef __DESCENDANT_HPP_INCLUDED
#define __DESCENDANT_HPP_INCLUDED

#include "entity.hpp"
#include "ascendant.hpp"

// Include standard headers
#include <cstddef> // std::size_t

namespace yli
{
    namespace ontology
    {
        class Ascendant;

        class Descendant: public yli::ontology::Entity
        {
            public:
                Descendant(yli::ontology::Ascendant* const ascendant)
                    : Entity(nullptr),
                    parent(ascendant)
                {
                    // constructor.
                }

                // destructor.
                ~Descendant();

                yli::ontology::Entity* get_parent() const override;
                std::size_t get_number_of_children() const override;
                std::size_t get_number_of_descendants() const override;

            private:
                yli::ontology::Ascendant* parent;
        };
    }
}

#endif
