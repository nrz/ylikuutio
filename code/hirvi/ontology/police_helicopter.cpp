// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2025 Antti Nuortimo.
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

#include "police_helicopter.hpp"
#include "code/ylikuutio/ontology/holobiont.hpp"
#include "code/ylikuutio/ontology/locomotion_module_struct.hpp"

namespace yli::core
{
    class Application;
}

namespace yli::ontology
{
    class GenericParentModule;
    class GenericMasterModule;
    class Universe;
    struct HolobiontStruct;
}

namespace hirvi
{
    PoliceHelicopter::PoliceHelicopter(
            yli::core::Application& application,
            yli::ontology::Universe& universe,
            const yli::ontology::HolobiontStruct& police_helicopter_struct,
            yli::ontology::GenericParentModule* const scene_parent,
            yli::ontology::GenericMasterModule* const symbiosis_master,
            yli::ontology::GenericMasterModule* const brain_master,
            const yli::ontology::LocomotionModuleStruct& fly_struct)
        : yli::ontology::Holobiont(application, universe, police_helicopter_struct, scene_parent, symbiosis_master, brain_master),
        fly(fly_struct)
    {
        // `yli::ontology::Entity` member variables begin here.
        this->type_string = "hirvi::PoliceHelicopter*";
    }
}
