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

#include "callback_engine_entity.hpp"
#include "universe.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr

namespace yli::ontology
{
    class Scene;

    // destructor.
    CallbackEngineEntity::~CallbackEngineEntity()
    {
        // destructor.
        std::cout << "This `CallbackEngineEntity` will be destroyed.\n";
    }

    yli::ontology::Entity* CallbackEngineEntity::get_parent() const
    {
        // Every `CallbackEngineEntity` is a child of the `Universe`.
        // The base class needs to be specified due to ambiguity caused by diamond inheritance.
        return static_cast<yli::ontology::Entity*>(this->yli::ontology::Entity::universe);
    }

    yli::ontology::Scene* CallbackEngineEntity::get_scene() const
    {
        // `CallbackEngineEntity` does not belong in any `Scene`.
        return nullptr;
    }

    std::size_t CallbackEngineEntity::get_number_of_children() const
    {
        return 0; // `CallbackEngineEntity` has no children.
    }

    std::size_t CallbackEngineEntity::get_number_of_descendants() const
    {
        return 0; // `CallbackEngineEntity` has no children.
    }
}
