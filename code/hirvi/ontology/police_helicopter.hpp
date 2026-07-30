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

#ifndef HIRVI_ONTOLOGY_POLICE_HELICOPTER_HPP_INCLUDED
#define HIRVI_ONTOLOGY_POLICE_HELICOPTER_HPP_INCLUDED

#include "code/ylikuutio/ontology/holobiont.hpp"
#include "code/ylikuutio/ontology/child_module.hpp"
#include "code/ylikuutio/snippets/locomotion/fly_module.hpp"
#include "police_module.hpp"

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
    struct HolobiontStruct;
    struct LocomotionModuleStruct;
}

namespace hirvi::ontology
{
    struct PoliceHelicopterStruct;

    class PoliceHelicopter : public yli::ontology::Holobiont
    {
    public:
        explicit PoliceHelicopter(
            yli::core::Application& application,
            yli::ontology::Universe& universe,
            const PoliceHelicopterStruct& police_helicopter_struct,
            yli::ontology::GenericParentModule* hirvi_scene_parent,
            yli::ontology::GenericMasterModule* movable_controller_master,
            yli::ontology::GenericMasterModule* symbiosis_master,
            yli::ontology::GenericMasterModule* police_control_center_master,
            const yli::ontology::LocomotionModuleStruct& fly_struct);

        PoliceHelicopter(const PoliceHelicopter&) = delete; // Delete copy constructor.
        PoliceHelicopter& operator=(const PoliceHelicopter&) = delete; // Delete copy assignment.

        ~PoliceHelicopter() override = default;

        yli::ontology::Scene* get_scene() const override;

        Entity* get_parent() const override;

        yli::ontology::ChildModule child_of_hirvi_scene;
        PoliceModule police;
        yli::snippets::locomotion::FlyModule fly;
    };
}

#endif
