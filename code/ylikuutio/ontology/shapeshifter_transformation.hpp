// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2021 Antti Nuortimo.
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

#ifndef __YLIKUUTIO_ONTOLOGY_SHAPESHIFTER_TRANSFORMATION_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_SHAPESHIFTER_TRANSFORMATION_HPP_INCLUDED

#include "entity.hpp"
#include "parent_module.hpp"
#include "model_struct.hpp"

// Include standard headers
#include <cstddef> // std::size_t

// `ShapeshifterTransformation` is a series of `ShapeshifterForm`s that
// make up the transition that may be e.g. a walk cycle or
// a metamorphosis of some kind.

namespace yli::ontology
{
    class Universe;
    class Scene;
    class Material;

    class ShapeshifterTransformation: public yli::ontology::Entity
    {
        public:
            // This method sets pointer to this `ShapeshifterTransformation` to `nullptr`,
            // sets `parent` according to the input, and requests a new `childID` from the new `Material`.
            void bind_to_new_material_parent(yli::ontology::Material* const new_parent);
            void bind_to_new_parent(yli::ontology::Entity* const new_parent) override;

            ShapeshifterTransformation(yli::ontology::Universe* const universe, const yli::ontology::ModelStruct& model_struct)
                : Entity(universe, model_struct),
                parent_of_shapeshifter_forms(this, &this->registry, "shapeshifter_forms"),
                parent_of_shapeshifter_sequences(this, &this->registry, "shapeshifter_sequences")
            {
                // constructor.
                this->parent = model_struct.material;

                // get `childID` from `Material` and set pointer to this `Species`.
                this->bind_to_parent();

                // `yli::ontology::Entity` member variables begin here.
                this->type_string = "yli::ontology::ShapeshifterTransformation*";
                this->can_be_erased = true;
            }

            // destructor.
            virtual ~ShapeshifterTransformation();

            yli::ontology::Entity* get_parent() const override;

            yli::ontology::ParentModule parent_of_shapeshifter_forms;
            yli::ontology::ParentModule parent_of_shapeshifter_sequences;

        private:
            void bind_to_parent();

        public:
            yli::ontology::Scene* get_scene() const override;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            void render();

            yli::ontology::Material* parent; // pointer to the `Material`.
    };
}

#endif
