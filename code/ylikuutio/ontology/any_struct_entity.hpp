// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2019 Antti Nuortimo.
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

#ifndef __ANY_STRUCT_ENTITY_HPP_INCLUDED
#define __ANY_STRUCT_ENTITY_HPP_INCLUDED

#include "entity.hpp"
#include "universe.hpp"
#include "code/ylikuutio/common/any_struct.hpp"

// Include standard headers
#include <cstddef> // std::size_t

namespace yli
{
    namespace ontology
    {
        class AnyStructEntity: public yli::datatypes::AnyStruct, public yli::ontology::Entity
        {
            public:
                // constructor.
                AnyStructEntity(yli::ontology::Universe* const universe)
                    : yli::datatypes::AnyStruct(), yli::ontology::Entity(universe)
                {
                    // `yli::ontology::Entity` member variables begin here.
                    this->type_string = "yli::ontology::AnyStructEntity*";
                    this->can_be_erased = true;
                }

                // constructor.
                // use the default copy constructor of `yli::datatypes::AnyStruct`.
                AnyStructEntity(yli::ontology::Universe* const universe, const yli::datatypes::AnyStruct& any_struct)
                    : yli::datatypes::AnyStruct(any_struct), yli::ontology::Entity(universe)
                {
                    // `yli::ontology::Entity` member variables begin here.
                    this->type_string = "yli::ontology::AnyStructEntity*";
                    this->can_be_erased = true;
                }

                AnyStructEntity(const AnyStructEntity&) = delete;            // Delete copy constructor.
                AnyStructEntity &operator=(const AnyStructEntity&) = delete; // Delete copy assignment.

                // destructor.
                virtual ~AnyStructEntity()
                {
                    // destructor.
                }

                yli::ontology::Entity* get_parent() const override
                {
                    // Every `AnyStructEntity` is a child of the `Universe`.
                    return this->yli::ontology::Entity::universe;
                }

                std::size_t get_number_of_children() const override
                {
                    return 0; // `AnyStructEntity` has no children.
                }

                std::size_t get_number_of_descendants() const override
                {
                    return 0; // `AnyStructEntity` has no children.
                }
        };
    }
}

#endif
