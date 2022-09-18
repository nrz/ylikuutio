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

#include "shapeshifter_sequence.hpp"
#include "shapeshifter_transformation.hpp"
#include "shapeshifter_sequence_struct.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr

namespace yli::ontology
{
    class GenericParentModule;
    class Entity;
    class Universe;
    class Scene;
    class Pipeline;

    ShapeshifterSequence::ShapeshifterSequence(
            yli::ontology::Universe& universe,
            const yli::ontology::ShapeshifterSequenceStruct& shapeshifter_sequence_struct,
            yli::ontology::GenericParentModule* const shapeshifter_transformation_parent_module)
        : Entity(universe, shapeshifter_sequence_struct),
        child_of_shapeshifter_transformation(shapeshifter_transformation_parent_module, this),
        master_of_objects(this, &this->registry, "objects")
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

    ShapeshifterSequence::~ShapeshifterSequence()
    {
        // destructor.

        // requirements for further actions:
        // `this->child_of_shapeshifter_transformation.get_parent()` must not be `nullptr`.

        yli::ontology::ShapeshifterTransformation* const shapeshifter_transformation =
            static_cast<yli::ontology::ShapeshifterTransformation*>(this->child_of_shapeshifter_transformation.get_parent());

        if (shapeshifter_transformation == nullptr)
        {
            std::cerr << "ERROR: `ShapeshifterSequence::~ShapeshifterSequence`: `shapeshifter_transformation` is `nullptr`!\n";
            return;
        }

        shapeshifter_transformation->parent_of_shapeshifter_sequences.unbind_child(this->childID);
    }

    yli::ontology::Entity* ShapeshifterSequence::get_parent() const
    {
        return this->child_of_shapeshifter_transformation.get_parent();
    }

    yli::ontology::Scene* ShapeshifterSequence::get_scene() const
    {
        const yli::ontology::Entity* const parent = this->get_parent();

        if (parent != nullptr)
        {
            return parent->get_scene();
        }

        return nullptr;
    }

    yli::ontology::Pipeline* ShapeshifterSequence::get_pipeline() const
    {
        const yli::ontology::ShapeshifterTransformation* const shapeshifter_transformation =
            static_cast<yli::ontology::ShapeshifterTransformation*>(this->get_parent());

        if (shapeshifter_transformation != nullptr)
        {
            return shapeshifter_transformation->get_pipeline();
        }

        return nullptr;
    }

    std::size_t ShapeshifterSequence::get_number_of_children() const
    {
        return 0; // `ShapeshifterSequence` has no children.
    }

    std::size_t ShapeshifterSequence::get_number_of_descendants() const
    {
        return 0; // `ShapeshifterSequence` has no children.
    }

    void ShapeshifterSequence::render(const yli::ontology::Scene* const target_scene)
    {
        // Render this `ShapeshifterSequence`.

        // TODO.
    }
}
