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

#include "police_control_center.hpp"
#include "hirvi_scene.hpp"
#include "police_control_center_struct.hpp"

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
}

namespace hirvi::ontology
{
    yli::ontology::Entity* PoliceControlCenter::get_parent() const
    {
        return this->child_of_hirvi_scene.get_parent();
    }

    PoliceControlCenter::PoliceControlCenter(
        yli::core::Application& application,
        yli::ontology::Universe& universe,
        const PoliceControlCenterStruct& police_control_center_struct,
        yli::ontology::GenericParentModule* const hirvi_scene_parent_module)
        : Entity(application, universe, police_control_center_struct),
          child_of_hirvi_scene(hirvi_scene_parent_module, *this),
          master_of_polices(*this, &this->registry, "polices")
    {
        // `yli::ontology::Entity` member variables begin here.
        this->type_string = "hirvi::ontology::PoliceControlCenter*";
    }

    std::size_t PoliceControlCenter::get_number_of_children() const
    {
        return 0; // `PoliceControlCenter` has no children.
    }

    std::size_t PoliceControlCenter::get_number_of_descendants() const
    {
        return 0; // `PoliceControlCenter` has no children.
    }

    yli::ontology::Scene* PoliceControlCenter::get_scene() const
    {
        return this->child_of_hirvi_scene.get_scene();
    }
}
