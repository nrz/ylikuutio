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

#include "shapeshifter_sequence.hpp"
#include "shapeshifter_transformation.hpp"
#include "object.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr

namespace yli
{
    namespace ontology
    {
        void ShapeshifterSequence::bind_Object(yli::ontology::Object* const object)
        {
            // get `childID` from `ShapeshifterSequence` and set pointer to `object`.
            yli::hierarchy::bind_child_to_parent<yli::ontology::Object*>(
                    object,
                    this->object_pointer_vector,
                    this->free_objectID_queue,
                    this->number_of_objects);
        }

        void ShapeshifterSequence::unbind_Object(const std::size_t childID)
        {
            yli::hierarchy::unbind_child_from_parent(
                    childID,
                    this->object_pointer_vector,
                    this->free_objectID_queue,
                    this->number_of_objects);
        }

        void ShapeshifterSequence::bind_to_parent()
        {
            // requirements:
            // `this->parent` must not be `nullptr`.
            yli::ontology::ShapeshifterTransformation* const shapeshifter_transformation = this->parent;

            if (shapeshifter_transformation == nullptr)
            {
                std::cerr << "ERROR: `ShapeshifterSequence::bind_to_parent`: `shapeshifter_transformation` is `nullptr`!\n";
                return;
            }

            // get `childID` from `ShapeshifterTransformation` and set pointer to this `ShapeshifterSequence`.
            this->parent->parent_of_shapeshifter_sequences.bind_child(this);
        }

        ShapeshifterSequence::~ShapeshifterSequence()
        {
            // destructor.

            // destroy all objects of this `ShapeshifterSequence`.
            std::cout << "All `Object`s of this `ShapeshifterSequence` will be destroyed.\n";
            yli::hierarchy::delete_children<yli::ontology::Object*>(this->object_pointer_vector, this->number_of_objects);

            // requirements for further actions:
            // `this->parent` must not be `nullptr`.

            yli::ontology::ShapeshifterTransformation* const shapeshifter_transformation = this->parent;

            if (shapeshifter_transformation == nullptr)
            {
                std::cerr << "ERROR: `ShapeshifterSequence::~ShapeshifterSequence`: `shapeshifter_transformation` is `nullptr`!\n";
                return;
            }

            shapeshifter_transformation->parent_of_shapeshifter_sequences.unbind_child(this->childID);
        }

        yli::ontology::Entity* ShapeshifterSequence::get_parent() const
        {
            return this->parent;
        }

        std::size_t ShapeshifterSequence::get_number_of_children() const
        {
            return this->number_of_objects;
        }

        std::size_t ShapeshifterSequence::get_number_of_descendants() const
        {
            return yli::ontology::get_number_of_descendants(this->object_pointer_vector);
        }

        void ShapeshifterSequence::render()
        {
            // Render this `ShapeshifterSequence`.

            // TODO.
        }
    }
}
