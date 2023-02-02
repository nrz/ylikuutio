// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2023 Antti Nuortimo.
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

#ifndef YLIKUUTIO_ONTOLOGY_SHAPESHIFTER_TRANSFORMATION_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_SHAPESHIFTER_TRANSFORMATION_HPP_INCLUDED

#include "entity.hpp"
#include "child_module.hpp"
#include "generic_parent_module.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <optional> // std::optional

// `ShapeshifterTransformation` is a series of `ShapeshifterForm`s that
// make up the transition that may be e.g. a walk cycle or
// a metamorphosis of some kind.

namespace yli::ontology
{
    class Universe;
    class Scene;
    class Pipeline;
    class Material;
    struct ModelStruct;

    class ShapeshifterTransformation final : public yli::ontology::Entity
    {
        public:
            // Set pointer to `shapeshifter_transformation` to `nullptr`, set parent according to the input,
            // and request a new childID from `new_parent`.
            static std::optional<yli::data::AnyValue> bind_to_new_material_parent(
                    yli::ontology::ShapeshifterTransformation& shapeshifter_transformation,
                    yli::ontology::Material& new_parent) noexcept;

            ShapeshifterTransformation(
                    yli::ontology::Universe& universe,
                    const yli::ontology::ModelStruct& model_struct,
                    yli::ontology::GenericParentModule* const material_parent_module);

            // destructor.
            ~ShapeshifterTransformation();

            yli::ontology::Entity* get_parent() const override;

            yli::ontology::ChildModule child_of_material;
            yli::ontology::GenericParentModule parent_of_shapeshifter_forms;
            yli::ontology::GenericParentModule parent_of_shapeshifter_sequences;

        private:
            void bind_to_parent() noexcept;

        public:
            yli::ontology::Scene* get_scene() const override;

            yli::ontology::Pipeline* get_pipeline() const;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            void render(const yli::ontology::Scene* const target_scene);
    };
}

#endif
