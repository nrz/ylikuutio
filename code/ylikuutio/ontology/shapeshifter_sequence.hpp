// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2022 Antti Nuortimo.
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
#include "generic_master_module.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <vector>  // std::vector

// `ShapeshifterSequence` is a child of `ShapeshifterTransformation`
// and defines in which order the and when the `ShapeshifterForm`s
// that make up the `ShapeshifterTransformation` are used in rendering
// the `Object`s that are children of the `ShapeshifterSequence`.

namespace yli::ontology
{
    class GenericParentModule;
    class Universe;
    class Scene;
    class Shader;
    class ShapeshifterSequenceStruct;

    class ShapeshifterSequence: public yli::ontology::Entity
    {
        public:
            ShapeshifterSequence(
                    yli::ontology::Universe& universe,
                    const yli::ontology::ShapeshifterSequenceStruct& shapeshifter_sequence_struct,
                    yli::ontology::GenericParentModule* const shapeshifter_transformation_parent_module);

            // destructor.
            virtual ~ShapeshifterSequence();

            yli::ontology::Entity* get_parent() const override;

        private:
            yli::ontology::ChildModule child_of_shapeshifter_transformation;

        public:
            yli::ontology::GenericMasterModule master_of_objects;

        private:
            void bind_to_parent();

        public:
            yli::ontology::Scene* get_scene() const override;

            yli::ontology::Shader* get_shader() const;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

        public:
            void render(const yli::ontology::Scene* const target_scene);

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
