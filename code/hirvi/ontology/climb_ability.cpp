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

#include "climb_ability.hpp"
#include "code/ylikuutio/ontology/symbiosis.hpp"

// Include standard headers
#include <cstddef> // std::size_t

namespace yli::core
{
    class Application;
}

namespace yli::ontology
{
    class GenericParentModule;
    class Universe;
    class Scene;
    struct AbilityStruct;
}

namespace hirvi
{
    ClimbAbility::ClimbAbility(
            yli::core::Application& application,
            yli::ontology::Universe& universe,
            const yli::ontology::AbilityStruct& ability_struct,
            yli::ontology::GenericParentModule* const parent_module)
        : yli::ontology::Ability(application, universe, ability_struct, parent_module)
    {
        // `yli::ontology::Entity` member variables begin here.
        this->type_string = "hirvi::ClimbAbility*";
    }
}
