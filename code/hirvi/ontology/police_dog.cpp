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

#include "police_dog.hpp"
#include "police_dog_struct.hpp"

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
    class Scene;
    class Holobiont;
    struct LocomotionModuleStruct;
}

namespace hirvi::ontology
{
    PoliceDog::PoliceDog(
        yli::core::Application& application,
        yli::ontology::Universe& universe,
        const PoliceDogStruct& police_dog_struct,
        yli::ontology::GenericParentModule* const hirvi_scene_parent,
        yli::ontology::GenericMasterModule* const movable_controller_master,
        yli::ontology::GenericMasterModule* const symbiosis_master,
        yli::ontology::GenericMasterModule* const master_of_polices,
        const yli::ontology::LocomotionModuleStruct& walk_struct,
        const yli::ontology::LocomotionModuleStruct& run_struct,
        const yli::ontology::LocomotionModuleStruct& canter_struct,
        const yli::ontology::LocomotionModuleStruct& gallop_struct)
        : Holobiont(
              application,
              universe,
              police_dog_struct,
              nullptr,
              movable_controller_master,
              symbiosis_master),
          child_of_hirvi_scene(hirvi_scene_parent, *this),
          police(master_of_polices, this),
          emancipation(this->police),
          walk(walk_struct),
          run(run_struct),
          canter(canter_struct),
          gallop(gallop_struct)
    {
        // `yli::ontology::Entity` member variables begin here.
        this->type_string = "hirvi::ontology::PoliceDog*";
    }

    yli::ontology::Scene* PoliceDog::get_scene() const
    {
        return this->child_of_hirvi_scene.get_scene();
    }

    yli::ontology::Entity* PoliceDog::get_parent() const
    {
        return this->child_of_hirvi_scene.get_parent();
    }
}
