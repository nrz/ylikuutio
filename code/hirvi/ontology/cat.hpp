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

#ifndef HIRVI_ONTOLOGY_CAT_HPP_INCLUDED
#define HIRVI_ONTOLOGY_CAT_HPP_INCLUDED

#include "code/ylikuutio/ontology/object.hpp"
#include "code/ylikuutio/snippets/locomotion/gait_module.hpp"
#include "code/ylikuutio/snippets/locomotion/climb_module.hpp"

namespace yli::core
{
    class Application;
}

namespace yli::ontology
{
    class GenericParentModule;
    class GenericMasterModule;
    class Universe;
    struct ObjectStruct;
    struct LocomotionModuleStruct;
}

namespace hirvi
{
    class Cat : public yli::ontology::Object
    {
        public:
            explicit Cat(
                    yli::core::Application& application,
                    yli::ontology::Universe& universe,
                    const yli::ontology::ObjectStruct& cat_struct,
                    yli::ontology::GenericParentModule* const scene_parent,
                    yli::ontology::GenericMasterModule* const species_master,
                    yli::ontology::GenericMasterModule* const brain_master,
                    const yli::ontology::LocomotionModuleStruct& walk_struct,
                    const yli::ontology::LocomotionModuleStruct& trot_struct,
                    const yli::ontology::LocomotionModuleStruct& canter_struct,
                    const yli::ontology::LocomotionModuleStruct& gallop_struct,
                    const yli::ontology::LocomotionModuleStruct& climb_struct);

            Cat(const Cat&) = delete;            // Delete copy constructor.
            Cat &operator=(const Cat&) = delete; // Delete copy assignment.

            ~Cat() = default;

            yli::snippets::locomotion::GaitModule walk;
            yli::snippets::locomotion::GaitModule trot;
            yli::snippets::locomotion::GaitModule canter;
            yli::snippets::locomotion::GaitModule gallop;
            yli::snippets::locomotion::ClimbModule climb;
    };
}

#endif
