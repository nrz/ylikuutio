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

#ifndef __SHAPESHIFTER_TRANSFORMATION_HPP_INCLUDED
#define __SHAPESHIFTER_TRANSFORMATION_HPP_INCLUDED

#include "entity.hpp"
#include "parent_module.hpp"
#include "species_struct.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <queue>   // std::priority_queue, std::queue
#include <vector>  // std::vector

// `ShapeshifterTransformation` is a series of `ShapeshifterForm`s that
// make up the transition that may be e.g. a walk cycle or
// a metamorphosis of some kind.

namespace yli
{
    namespace ontology
    {
        class Universe;

        class ShapeshifterTransformation: public yli::ontology::Entity
        {
            public:
                // This method sets pointer to this `ShapeshifterTransformation` to `nullptr`,
                // sets `parent` according to the input, and requests a new `childID` from the new `Material`.
                void bind_to_new_parent(yli::ontology::Material* const new_parent);
                void bind_to_new_parent(yli::ontology::Entity* const new_parent) override;

                // constructor.
                ShapeshifterTransformation(yli::ontology::Universe* const universe, const yli::ontology::SpeciesStruct& species_struct)
                    : Entity(universe),
                    parent_of_shapeshifter_forms(yli::ontology::ParentModule()),
                    parent_of_shapeshifter_sequences(yli::ontology::ParentModule())
                {
                    // constructor.
                    this->parent = species_struct.material;

                    // get `childID` from `Material` and set pointer to this `Species`.
                    this->bind_to_parent();

                    // `yli::ontology::Entity` member variables begin here.
                    this->type_string = "yli::ontology::ShapeshifterTransformation*";
                    this->can_be_erased = true;
                }

                // destructor.
                virtual ~ShapeshifterTransformation();

                yli::ontology::Entity* get_parent() const override;
                std::size_t get_number_of_children() const override;
                std::size_t get_number_of_descendants() const override;

                template<class T1>
                    friend void yli::hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue, std::size_t& number_of_children);

                yli::ontology::ParentModule parent_of_shapeshifter_forms;
                yli::ontology::ParentModule parent_of_shapeshifter_sequences;

            private:
                void bind_to_parent();

                void render() override;

                yli::ontology::Material* parent; // pointer to the `Material`.
        };
    }
}

#endif
