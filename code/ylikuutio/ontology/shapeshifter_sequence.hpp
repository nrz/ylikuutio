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

#ifndef __YLIKUUTIO_ONTOLOGY_SHAPESHIFTER_SEQUENCE_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_SHAPESHIFTER_SEQUENCE_HPP_INCLUDED

#include "entity.hpp"
#include "child_module.hpp"
#include "parent_module.hpp"
#include "shapeshifter_sequence_struct.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <vector>  // std::vector

// `ShapeshifterSequence` is a child of `ShapeshifterTransformation`
// and defines in which order the and when the `ShapeshifterForm`s
// that make up the `ShapeshifterTransformation` are used in rendering
// the `Object`s that are children of the `ShapeshifterSequence`.

namespace yli::ontology
{
    class Universe;
    class Scene;

    class ShapeshifterSequence: public yli::ontology::Entity
    {
        public:
            ShapeshifterSequence(yli::ontology::Universe* const universe, const yli::ontology::ShapeshifterSequenceStruct& shapeshifter_sequence_struct, yli::ontology::ParentModule* const shapeshifter_transformation_parent_module)
                : Entity(universe, shapeshifter_sequence_struct),
                child_of_shapeshifter_transformation(shapeshifter_transformation_parent_module, this),
                parent_of_objects(this, &this->registry, "objects")
            {
                // constructor.

                this->transformation_speed        = shapeshifter_sequence_struct.transformation_speed;
                this->initial_offset              = shapeshifter_sequence_struct.initial_offset;
                this->is_repeating_transformation = shapeshifter_sequence_struct.is_repeating_transformation;
                this->bounce_from_start           = shapeshifter_sequence_struct.bounce_from_start;
                this->bounce_from_end             = shapeshifter_sequence_struct.bounce_from_end;

                // `yli::ontology::Entity` member variables begin here.
                this->type_string = "yli::ontology::ShapeshifterSequence*";
                this->can_be_erased = true;
            }

            // destructor.
            virtual ~ShapeshifterSequence();

            yli::ontology::Entity* get_parent() const override;

        private:
            yli::ontology::ChildModule child_of_shapeshifter_transformation;

        public:
            yli::ontology::ParentModule parent_of_objects;

        private:
            void bind_to_parent();

        public:
            yli::ontology::Scene* get_scene() const override;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

        public:
            void render();

        private:
            float transformation_speed;                        // Negative speed means inverse initial transition direction.
            std::size_t initial_offset;                        // Index of the `ShapeshifterForm` from which to begin the transition.

            // Repeating transitions begin from the `initial_offset`
            // endlessly in the same initial transition direction,
            // after all potential bouncing has ended.
            bool is_repeating_transformation;

            // If both `bounce_from_start` and `bounce_from_end` are `true`,
            // then bouncing continues endlessly and the value of
            // `is_repeating_transformation` has no effect.
            bool bounce_from_start;
            bool bounce_from_end;
    };
}

#endif
