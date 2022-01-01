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
#include "family_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr

namespace yli::ontology
{
    class Entity;
    class Scene;
    class Shader;

    ShapeshifterSequence::~ShapeshifterSequence()
    {
        // destructor.

        // requirements for further actions:
        // `this->child_of_shapeshifter_transformation.get_parent()` must not be `nullptr`.

        yli::ontology::ShapeshifterTransformation* const shapeshifter_transformation = static_cast<yli::ontology::ShapeshifterTransformation*>(this->child_of_shapeshifter_transformation.get_parent());

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
        yli::ontology::Entity* parent = this->get_parent();

        if (parent != nullptr)
        {
            return parent->get_scene();
        }

        return nullptr;
    }

    yli::ontology::Shader* ShapeshifterSequence::get_shader() const
    {
        yli::ontology::ShapeshifterTransformation* const shapeshifter_transformation = static_cast<yli::ontology::ShapeshifterTransformation*>(this->get_parent());

        if (shapeshifter_transformation != nullptr)
        {
            return shapeshifter_transformation->get_shader();
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

    void ShapeshifterSequence::render()
    {
        // Render this `ShapeshifterSequence`.

        // TODO.
    }
}
