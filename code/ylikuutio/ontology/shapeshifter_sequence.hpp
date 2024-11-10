// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2024 Antti Nuortimo.
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

#ifndef YLIKUUTIO_ONTOLOGY_SHAPESHIFTER_SEQUENCE_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_SHAPESHIFTER_SEQUENCE_HPP_INCLUDED

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

namespace yli::core
{
    class Application;
}

namespace yli::memory
{
    template<typename T1, std::size_t DataSize>
        class MemoryStorage;
}

namespace yli::ontology
{
    class GenericParentModule;
    class Entity;
    class Universe;
    class Scene;
    class Pipeline;
    class Shapeshifter;
    struct ShapeshifterSequenceStruct;

    class ShapeshifterSequence final : public Entity
    {
        private:
            ShapeshifterSequence(
                    yli::core::Application& application,
                    Universe& universe,
                    const ShapeshifterSequenceStruct& shapeshifter_sequence_struct,
                    GenericParentModule* const shapeshifter_transformation_parent_module);

            ~ShapeshifterSequence() = default;

        public:
            Entity* get_parent() const override;

            template<typename T1, std::size_t DataSize>
                friend class yli::memory::MemoryStorage;

        private:
            ChildModule child_of_shapeshifter_transformation;

        public:
            GenericMasterModule master_of_shapeshifters;

        private:
            void bind_to_parent() noexcept;

        public:
            Scene* get_scene() const override;

            Pipeline* get_pipeline() const;

            template<typename ApprenticeType>
                GenericMasterModule* get_generic_master_module() = delete;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

        public:
            void render(const Scene* const target_scene);

        private:
            float transformation_speed; // Negative speed means inverse initial transition direction.
            std::size_t initial_offset; // Index of the `ShapeshifterForm` from which to begin the transition.

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

    template<>
        inline GenericMasterModule* ShapeshifterSequence::get_generic_master_module<Shapeshifter>()
        {
            return &this->master_of_shapeshifters;
        }
}

#endif
