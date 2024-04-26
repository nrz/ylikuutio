// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2024 Antti Nuortimo.
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

#include "waypoint.hpp"
#include "scene.hpp"
#include "waypoint_struct.hpp"

// Include standard headers
#include <cstddef> // std::size_t

namespace yli::core
{
    class Application;
}

namespace yli::ontology
{
    class GenericParentModule;
    class GenericMasterModule;
    class Entity;
    class Universe;

    yli::ontology::Entity* Waypoint::get_parent() const
    {
        return this->child_of_scene.get_parent();
    }

    Waypoint::Waypoint(
            yli::core::Application& application,
            yli::ontology::Universe& universe,
            const yli::ontology::WaypointStruct& waypoint_struct,
            yli::ontology::GenericParentModule* const parent_module,
            yli::ontology::GenericMasterModule* const brain_master_module)
        : Movable(
                application,
                universe,
                waypoint_struct,
                brain_master_module),
        child_of_scene(parent_module, *this)
    {
        // `yli::ontology::Entity` member variables begin here.
        this->type_string = "yli::ontology::Waypoint*";
        this->can_be_erased = true;
    }

    std::size_t Waypoint::get_number_of_children() const
    {
        return 0; // `Waypoint` has no children.
    }

    std::size_t Waypoint::get_number_of_descendants() const
    {
        return 0; // `Waypoint` has no children.
    }

    yli::ontology::Scene* Waypoint::get_scene() const
    {
        return static_cast<yli::ontology::Scene*>(this->get_parent());
    }
}
