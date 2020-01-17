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

#include "shapeshifter_form.hpp"
#include "shapeshifter_transformation.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr

namespace yli
{
    namespace ontology
    {
        class Entity;

        void ShapeshifterForm::bind_to_parent()
        {
            // requirements:
            // `this->parent` must not be `nullptr`.
            yli::ontology::ShapeshifterTransformation* const shapeshifter_transformation = this->parent;

            if (shapeshifter_transformation == nullptr)
            {
                std::cerr << "ERROR: `ShapeshifterForm::bind_to_parent`: `shapeshifter_transformation` is `nullptr`!\n";
                return;
            }

            // get `childID` from `ShapeshifterTransformation` and set pointer to this `ShapeshifterForm`.
            this->parent->bind_ShapeshifterForm(this);
        }

        ShapeshifterForm::~ShapeshifterForm()
        {
            // destructor.

            // requirements for further actions:
            // `this->parent` must not be `nullptr`.

            yli::ontology::ShapeshifterTransformation* const shapeshifter_transformation = this->parent;

            if (shapeshifter_transformation == nullptr)
            {
                std::cerr << "ERROR: `ShapeshifterForm::~ShapeshifterForm`: `shapeshifter_transformation` is `nullptr`!\n";
                return;
            }

            shapeshifter_transformation->unbind_ShapeshifterForm(this->childID);
        }

        yli::ontology::Entity* ShapeshifterForm::get_parent() const
        {
            return this->parent;
        }

        std::size_t ShapeshifterForm::get_number_of_children() const
        {
            return 0; // `ShapeshifterForm` has no children.
        }

        std::size_t ShapeshifterForm::get_number_of_descendants() const
        {
            return 0; // `ShapeshifterForm` has no children.
        }

        void ShapeshifterForm::render()
        {
            // Render this `ShapeshifterForm`.
        }
    }
}
