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

#include "shapeshifter_transformation.hpp"
#include "shapeshifter_form.hpp"
#include "shapeshifter_sequence.hpp"
#include "material.hpp"
#include "render_templates.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr

namespace yli
{
    namespace ontology
    {
        void ShapeshifterTransformation::bind_ShapeshifterForm(yli::ontology::ShapeshifterForm* const shapeshifter_form)
        {
            // get `childID` from `ShapeshifterTransformation` and set pointer to `shapeshifter_form`.
            yli::hierarchy::bind_child_to_parent<yli::ontology::ShapeshifterForm*>(
                    shapeshifter_form,
                    this->shapeshifter_form_pointer_vector,
                    this->free_shapeshifter_formID_queue,
                    this->number_of_shapeshifter_forms);
        }

        void ShapeshifterTransformation::bind_ShapeshifterSequence(yli::ontology::ShapeshifterSequence* const shapeshifter_sequence)
        {
            // get `childID` from `ShapeshifterTransformation` and set pointer to `shapeshifter_sequence`.
            yli::hierarchy::bind_child_to_parent<yli::ontology::ShapeshifterSequence*>(
                    shapeshifter_sequence,
                    this->shapeshifter_sequence_pointer_vector,
                    this->free_shapeshifter_sequenceID_queue,
                    this->number_of_shapeshifter_sequences);
        }

        void ShapeshifterTransformation::unbind_ShapeshifterForm(const std::size_t childID)
        {
            yli::hierarchy::unbind_child_from_parent(
                    childID,
                    this->shapeshifter_form_pointer_vector,
                    this->free_shapeshifter_formID_queue,
                    this->number_of_shapeshifter_forms);
        }

        void ShapeshifterTransformation::unbind_ShapeshifterSequence(const std::size_t childID)
        {
            yli::hierarchy::unbind_child_from_parent(
                    childID,
                    this->shapeshifter_sequence_pointer_vector,
                    this->free_shapeshifter_sequenceID_queue,
                    this->number_of_shapeshifter_sequences);
        }

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
            this->parent->bind_ShapeshifterTransformation(this);
        }

        void ShapeshifterTransformation::bind_to_new_parent(yli::ontology::Material* const new_parent)
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
                std::cerr << "ERROR: `ShapeshifterTransformation::bind_to_new_parent`: `material` is `nullptr`!\n";
                return;
            }

            if (new_parent == nullptr)
            {
                std::cerr << "ERROR: `ShapeshifterTransformation::bind_to_new_parent`: `new_parent` is `nullptr`!\n";
                return;
            }

            // unbind from the old parent `Material`.
            material->unbind_ShapeshifterTransformation(this->childID);

            // get `childID` from `Material` and set pointer to this `ShapeshifterTransformation`.
            this->parent = new_parent;
            this->parent->bind_ShapeshifterTransformation(this);
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

            this->bind_to_new_parent(material_parent);
        }

        ShapeshifterTransformation::~ShapeshifterTransformation()
        {
            // destructor.

            // destroy all shapeshifter_sequences of this species.
            std::cout << "All `ShapeshifterSequence`s of this `ShapeshifterTransformation` will be destroyed.\n";
            yli::hierarchy::delete_children<yli::ontology::ShapeshifterSequence*>(this->shapeshifter_sequence_pointer_vector, this->number_of_shapeshifter_sequences);

            // destroy all shapeshifter_forms of this species.
            std::cout << "All `ShapeshifterForm`s of this `ShapeshifterTransformation` will be destroyed.\n";
            yli::hierarchy::delete_children<yli::ontology::ShapeshifterForm*>(this->shapeshifter_form_pointer_vector, this->number_of_shapeshifter_forms);

            // requirements for further actions:
            // `this->parent` must not be `nullptr`.

            yli::ontology::Material* const material = this->parent;

            if (material == nullptr)
            {
                std::cerr << "ERROR: `ShapeshifterTransformation::~ShapeshifterTransformation`: `material` is `nullptr`!\n";
                return;
            }

            material->unbind_ShapeshifterTransformation(this->childID);
        }

        void ShapeshifterTransformation::render()
        {
            // Render this `ShapeshifterTransformation` by calling `render` function of each `ShapeshifterSequence`.
            yli::ontology::render_children<yli::ontology::ShapeshifterSequence*>(this->shapeshifter_sequence_pointer_vector);
        }

        yli::ontology::Entity* ShapeshifterTransformation::get_parent() const
        {
            return this->parent;
        }

        std::size_t ShapeshifterTransformation::get_number_of_children() const
        {
            return this->number_of_shapeshifter_forms + this->number_of_shapeshifter_sequences;
        }

        std::size_t ShapeshifterTransformation::get_number_of_descendants() const
        {
            return yli::ontology::get_number_of_descendants(this->shapeshifter_form_pointer_vector) +
                yli::ontology::get_number_of_descendants(this->shapeshifter_sequence_pointer_vector);
        }
    }
}
