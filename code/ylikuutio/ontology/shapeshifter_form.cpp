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

#include "shapeshifter_form.hpp"
#include "shapeshifter_transformation.hpp"

// Include standard headers
#include <cstddef>  // std::size_t

namespace yli::ontology
{
    class Entity;

    ShapeshifterForm::~ShapeshifterForm()
    {
        // destructor.
    }

    yli::ontology::Entity* ShapeshifterForm::get_parent() const
    {
        return this->child_of_shapeshifter_transformation.get_parent();
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

        // TODO.
    }
}
