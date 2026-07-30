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

#include "police_train.hpp"

namespace yli::core
{
    class Application;
}

namespace yli::ontology
{
    class GenericParentModule;
    class GenericMasterModule;
    class Universe;
    class Holobiont;
    struct HolobiontStruct;
    struct LocomotionModuleStruct;
}

namespace hirvi::ontology
{
    PoliceTrain::PoliceTrain(
        yli::core::Application& application,
        yli::ontology::Universe& universe,
        const yli::ontology::HolobiontStruct& police_train_struct,
        yli::ontology::GenericParentModule* const hirvi_scene_parent,
        yli::ontology::GenericMasterModule* const movable_controller_master,
        yli::ontology::GenericMasterModule* const symbiosis_master,
        yli::ontology::GenericMasterModule* police_control_center_master,
        const yli::ontology::LocomotionModuleStruct& rail_vehicle_struct)
        : Holobiont(
              application,
              universe,
              police_train_struct,
              nullptr,
              movable_controller_master,
              symbiosis_master),
          child_of_hirvi_scene(hirvi_scene_parent, *this),
          police(police_control_center_master, this),
          rail_vehicle(rail_vehicle_struct)
    {
        // `yli::ontology::Entity` member variables begin here.
        this->type_string = "hirvi::ontology::PoliceTrain*";
    }

    yli::ontology::Scene* PoliceTrain::get_scene() const
    {
        return this->child_of_hirvi_scene.get_scene();
    }

    yli::ontology::Entity* PoliceTrain::get_parent() const
    {
        return this->child_of_hirvi_scene.get_parent();
    }
}
