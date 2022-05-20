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

#include "ecosystem.hpp"
#include "ecosystem_struct.hpp"
#include "family_templates.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr

namespace yli::ontology
{
    class Universe;
    class Scene;

    Ecosystem::Ecosystem(
            yli::ontology::Universe& universe,
            const yli::ontology::EcosystemStruct& ecosystem_struct,
            yli::ontology::GenericParentModule* const parent_module)
        : Entity(universe, ecosystem_struct),
        child_of_universe(parent_module, this),
        parent_of_shaders(this, &this->registry, "shaders")
    {
        // constructor.

        // `yli::ontology::Entity` member variables begin here.
        this->type_string = "yli::ontology::Ecosystem*";
        this->can_be_erased = true;
    }

    Ecosystem::~Ecosystem()
    {
        // destructor.
        std::cout << "This `Ecosystem` will be destroyed.\n";
    }

    yli::ontology::Entity* Ecosystem::get_parent() const
    {
        return this->child_of_universe.get_parent();
    }

    yli::ontology::Scene* Ecosystem::get_scene() const
    {
        // `Ecosystem` does not belong in any `Scene`.
        return nullptr;
    }

    std::size_t Ecosystem::get_number_of_children() const
    {
        return this->parent_of_shaders.get_number_of_children();
    }

    std::size_t Ecosystem::get_number_of_descendants() const
    {
        return yli::ontology::get_number_of_descendants(this->parent_of_shaders.child_pointer_vector);
    }
}
