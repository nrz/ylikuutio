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

#include "text3D.hpp"
#include "vector_font.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <ios>      // std::defaultfloat, std::dec, std::fixed, std::hex, std::ios
#include <iostream> // std::cout, std::cin, std::cerr

namespace yli::ontology
{
    Text3D::~Text3D()
    {
        // destructor.
        std::cout << "This `Text3D` (\"" << this->text_string << "\", childID " << std::dec << this->childID << ") will be destroyed.\n";
    }

    std::size_t Text3D::get_number_of_children() const
    {
        return this->parent_of_objects.get_number_of_children();
    }

    std::size_t Text3D::get_number_of_descendants() const
    {
        return yli::ontology::get_number_of_descendants(this->parent_of_objects.child_pointer_vector);
    }
}
