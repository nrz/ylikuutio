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

#ifndef __SHAPESHIFTER_SEQUENCE_HPP_INCLUDED
#define __SHAPESHIFTER_SEQUENCE_HPP_INCLUDED

#include "entity.hpp"
#include "shapeshifter_sequence_struct.hpp"
#include "render_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <queue>   // std::priority_queue, std::queue
#include <vector>  // std::vector

// `ShapeshifterSequence` is a child of `ShapeshifterTransformation`
// and defines in which order the and when the `ShapeshifterForm`s
// that make up the `ShapeshifterTransformation` are used in rendering
// the `Object`s that are children of the `ShapeshifterSequence`.

namespace yli
{
    namespace ontology
    {
        class Universe;
        class Object;

        class ShapeshifterSequence: public yli::ontology::Entity
        {
            public:
                void bind_Object(yli::ontology::Object* const object);
                void unbind_Object(const std::size_t childID);

                // constructor.
                ShapeshifterSequence(yli::ontology::Universe* const universe, const yli::ontology::ShapeshifterSequenceStruct& shapeshifter_sequence_struct)
                    : Entity(universe)
                {
                    // constructor.
                    this->parent = shapeshifter_sequence_struct.parent;

                    this->number_of_objects = 0;

                    this->transformation_speed        = shapeshifter_sequence_struct.transformation_speed;
                    this->initial_offset              = shapeshifter_sequence_struct.initial_offset;
                    this->is_repeating_transformation = shapeshifter_sequence_struct.is_repeating_transformation;
                    this->bounce_from_start           = shapeshifter_sequence_struct.bounce_from_start;
                    this->bounce_from_end             = shapeshifter_sequence_struct.bounce_from_end;

                    // get `childID` from `ShapeshifterTransformation` and set pointer to this `ShapeshifterSequence`.
                    this->bind_to_parent();

                    // `yli::ontology::Entity` member variables begin here.
                    this->type_string = "yli::ontology::ShapeshifterSequence*";
                    this->can_be_erased = true;
                }

                // destructor.
                virtual ~ShapeshifterSequence();

                yli::ontology::Entity* get_parent() const override;
                std::size_t get_number_of_children() const override;
                std::size_t get_number_of_descendants() const override;

                template<class T1>
                    friend void yli::hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue, std::size_t& number_of_children);
                template<class T1>
                    friend void yli::ontology::render_children(const std::vector<T1>& child_pointer_vector);

            private:
                void bind_to_parent();

                void render();

                yli::ontology::ShapeshifterTransformation* parent; // Pointer to `ShapeshifterTransformation` object.

                std::vector<yli::ontology::Object*> object_pointer_vector;
                std::queue<std::size_t> free_objectID_queue;
                std::size_t number_of_objects;

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
}

#endif
