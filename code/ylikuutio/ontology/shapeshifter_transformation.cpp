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

#include "shapeshifter_transformation.hpp"
#include "entity.hpp"
#include "universe.hpp"
#include "material.hpp"
#include "shapeshifter_sequence.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/render/render_master.hpp"
#include "code/ylikuutio/render/render_templates.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr

namespace yli::ontology
{
    void ShapeshifterTransformation::bind_to_parent()
    {
        // requirements:
        // `this->parent` must not be `nullptr`.
        yli::ontology::Material* const material = this->parent;

        if (material == nullptr)
        {
            std::cerr << "ERROR: `ShapeshifterTransformation::bind_to_parent`: `material` is `nullptr`!\n";
            return;
        }

        // get `childID` from `Material` and set pointer to this `ShapeshifterTransformation`.
        this->parent->parent_of_shapeshifter_transformations.bind_child(this);
    }

    void ShapeshifterTransformation::bind_to_new_material_parent(yli::ontology::Material* const new_parent)
    {
        // this method sets pointer to this `ShapeshifterTransformation` to `nullptr`,
        // sets `material_parent` according to the input,
        // and requests a new `childID` from the new `Material`.
        //
        // requirements:
        // `this->material_parent` must not be `nullptr`.
        // `new_parent` must not be `nullptr`.

        yli::ontology::Material* const material = this->parent;

        if (material == nullptr)
        {
            std::cerr << "ERROR: `ShapeshifterTransformation::bind_to_new_material_parent`: `material` is `nullptr`!\n";
            return;
        }

        if (new_parent == nullptr)
        {
            std::cerr << "ERROR: `ShapeshifterTransformation::bind_to_new_material_parent`: `new_parent` is `nullptr`!\n";
            return;
        }

        if (new_parent->has_child(this->local_name))
        {
            std::cerr << "ERROR: `ShapeshifterTransformation::bind_to_new_material_parent`: local name is already in use!\n";
            return;
        }

        // unbind from the old parent `Material`.
        material->parent_of_shapeshifter_transformations.unbind_child(this->childID);

        // get `childID` from `Material` and set pointer to this `ShapeshifterTransformation`.
        this->parent = new_parent;
        this->parent->parent_of_shapeshifter_transformations.bind_child(this);
    }

    void ShapeshifterTransformation::bind_to_new_parent(yli::ontology::Entity* const new_parent)
    {
        // this method sets pointer to this `ShapeshifterTransformation` to `nullptr`, sets `material_parent` according to the input,
        // and requests a new `childID` from the new `Material`.
        //
        // requirements:
        // `this->material_parent` must not be `nullptr`.
        // `new_parent` must not be `nullptr`.

        yli::ontology::Material* const material_parent = dynamic_cast<yli::ontology::Material*>(new_parent);

        if (material_parent == nullptr)
        {
            std::cerr << "ERROR: `ShapeshifterTransformation::bind_to_new_parent`: `new_parent` is not `yli::ontology::Material*`!\n";
            return;
        }

        this->bind_to_new_material_parent(material_parent);
    }

    ShapeshifterTransformation::~ShapeshifterTransformation()
    {
        // destructor.

        // requirements for further actions:
        // `this->parent` must not be `nullptr`.

        yli::ontology::Material* const material = this->parent;

        if (material == nullptr)
        {
            std::cerr << "ERROR: `ShapeshifterTransformation::~ShapeshifterTransformation`: `material` is `nullptr`!\n";
            return;
        }

        material->parent_of_shapeshifter_transformations.unbind_child(this->childID);
    }

    void ShapeshifterTransformation::render()
    {
        if (!this->should_be_rendered || this->universe == nullptr)
        {
            return;
        }

        yli::render::RenderMaster* const render_master = this->universe->get_render_master();

        if (render_master == nullptr)
        {
            return;
        }

        this->prerender();
        render_master->render_shapeshifter_sequences(this->parent_of_shapeshifter_sequences.child_pointer_vector);
        this->postrender();
    }

    yli::ontology::Entity* ShapeshifterTransformation::get_parent() const
    {
        return this->parent;
    }

    std::size_t ShapeshifterTransformation::get_number_of_children() const
    {
        return this->parent_of_shapeshifter_forms.get_number_of_children() +
            this->parent_of_shapeshifter_sequences.get_number_of_children();
    }

    std::size_t ShapeshifterTransformation::get_number_of_descendants() const
    {
        return yli::ontology::get_number_of_descendants(this->parent_of_shapeshifter_forms.child_pointer_vector) +
            yli::ontology::get_number_of_descendants(this->parent_of_shapeshifter_sequences.child_pointer_vector);
    }
}
