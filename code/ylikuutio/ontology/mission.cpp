// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2023 Antti Nuortimo.
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

#include "mission.hpp"
#include "universe.hpp"
#include "mission_struct.hpp"

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

    yli::ontology::Entity* Mission::get_parent() const
    {
        return this->child_of_universe.get_parent();
    }

    Mission::Mission(
            yli::core::Application& application,
            yli::ontology::Universe& universe,
            const yli::ontology::MissionStruct& mission_struct,
            yli::ontology::GenericParentModule* const parent_module)
        : Entity(application, universe, mission_struct),
        child_of_universe(parent_module, this),
        callback_engine(
                application,
                this->universe,
                &this->universe.parent_of_callback_engines)
    {
        // `yli::ontology::Entity` member variables begin here.
        this->type_string = "yli::ontology::Mission*";
        // TODO: add other `yli::ontology::Entity` member variables such as `can_be_erased` if needed!
    }

    std::size_t Mission::get_number_of_children() const
    {
        return 0; // TODO: modify this line if this class has children!
    }

    std::size_t Mission::get_number_of_descendants() const
    {
        return 0; // TODO: modify this line if this class has children!
    }
}
