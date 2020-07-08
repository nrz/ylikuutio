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

#ifndef __ANY_STRUCT_ENTITY_HPP_INCLUDED
#define __ANY_STRUCT_ENTITY_HPP_INCLUDED

#include "entity.hpp"
#include "code/ylikuutio/data/any_struct.hpp"
#include "child_module.hpp"
#include "parent_module.hpp"
#include "any_struct_entity_struct.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <queue>   // std::queue
#include <vector>  // std::vector

// `AnyStructEntity` is a child of the `Universe`.
//
// `AnyStructEntity` inherits both `yli::data::AnyStruct` and `yli::ontology::Entity`.
// Therefore, `AnyStructEntity` is an `Entity` but it functions also as an `AnyStruct`.
// Each `AnyStructEntity` may have 0 or more `AnyValueEntity` objects as its children.
// Each `AnyValueEntity` child of a `AnyStructEntity` needs to have a name from its
// parent's namespace. The name controls how the `AnyValueEntity` child is used when
// creating a particular `struct` from this `AnyStructEntity`.
// TODO: implement the described functionality!
//
// Note: do not confuse `AnyStruct`, `AnyStructEntity`, and `AnyStructEntityStruct`.

namespace yli::ontology
{
    class Universe;

    class AnyStructEntity: public yli::data::AnyStruct, public yli::ontology::Entity
    {
        public:
            // constructor (creates an empty `.AnyStructEntity`).
            AnyStructEntity(
                    yli::ontology::Universe* const universe,
                    const yli::ontology::AnyStructEntityStruct& any_struct_entity_struct,
                    yli::ontology::ParentModule* const parent_module)
                : yli::data::AnyStruct(),
                yli::ontology::Entity(universe, any_struct_entity_struct),
                child_of_entity(parent_module, this)
            {
                // `yli::ontology::Entity` member variables begin here.
                this->type_string = "yli::ontology::AnyStructEntity*";
                this->can_be_erased = true;
            }

            // constructor.
            // use the default copy constructor of `yli::data::AnyStruct`.
            // constructor (copies an existing `.AnyStructEntity`).
            AnyStructEntity(
                    yli::ontology::Universe* const universe,
                    const yli::data::AnyStruct& any_struct,
                    const yli::ontology::AnyStructEntityStruct& any_struct_entity_struct,
                    yli::ontology::ParentModule* const parent_module)
                : yli::data::AnyStruct(any_struct),
                yli::ontology::Entity(universe, any_struct_entity_struct),
                child_of_entity(parent_module, this)
            {
                // `yli::ontology::Entity` member variables begin here.
                this->type_string = "yli::ontology::AnyStructEntity*";
                this->can_be_erased = true;
            }

            AnyStructEntity(const AnyStructEntity&) = delete;            // Delete copy constructor.
            AnyStructEntity &operator=(const AnyStructEntity&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~AnyStructEntity();

            yli::ontology::Entity* get_parent() const override;

            yli::ontology::ChildModule child_of_entity;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;
    };
}

#endif
