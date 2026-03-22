// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2026 Antti Nuortimo.
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

#include "ability.hpp"
#include "symbiosis.hpp"
#include "ability_struct.hpp"

// Include standard headers
#include <cstddef> // std::size_t

namespace yli::core
{
    class Application;
}

namespace yli::ontology
{
    class GenericParentModule;
    class Entity;
    class Universe;
    class Scene;

    Symbiosis* Ability::get_symbiosis() const
    {
        return static_cast<Symbiosis*>(this->get_parent());
    }

    Entity* Ability::get_parent() const
    {
        return this->child_of_symbiosis.get_parent();
    }

    Ability::Ability(
            yli::core::Application& application,
            Universe& universe,
            const AbilityStruct& ability_struct,
            GenericParentModule* const parent_module)
        : Capability(application, universe, ability_struct),
        child_of_symbiosis(parent_module, *this)
    {
        // `yli::ontology::Entity` member variables begin here.
        this->type_string = "yli::ontology::Ability*";
    }

    std::size_t Ability::get_number_of_children() const
    {
        return 0; // `Ability` has no children.
    }

    std::size_t Ability::get_number_of_descendants() const
    {
        return 0; // `Ability` has no children.
    }

    Scene* Ability::get_scene() const
    {
        return this->child_of_symbiosis.get_scene();
    }
}
