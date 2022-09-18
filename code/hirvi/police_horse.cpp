// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2022 Antti Nuortimo.
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

#include "police_horse.hpp"
#include "code/ylikuutio/ontology/holobiont.hpp"
#include "code/ylikuutio/ontology/locomotion_module_struct.hpp"

namespace yli::ontology
{
    class Universe;
    class GenericParentModule;
    class GenericMasterModule;
    struct HolobiontStruct;
}

namespace hirvi
{
    PoliceHorse::PoliceHorse(
            yli::ontology::Universe& universe,
            const yli::ontology::HolobiontStruct& police_horse_struct,
            const yli::ontology::LocomotionModuleStruct& walk_struct,
            const yli::ontology::LocomotionModuleStruct& run_struct,
            const yli::ontology::LocomotionModuleStruct& canter_struct,
            const yli::ontology::LocomotionModuleStruct& gallop_struct,
            yli::ontology::GenericParentModule* const scene_parent,
            yli::ontology::GenericMasterModule* const symbiosis_master,
            yli::ontology::GenericMasterModule* const brain_master)
        : yli::ontology::Holobiont(universe, police_horse_struct, scene_parent, symbiosis_master, brain_master),
        walk(walk_struct),
        run(run_struct),
        canter(canter_struct),
        gallop(gallop_struct)
    {
        // constructor.

        // `yli::ontology::Entity` member variables begin here.
        this->type_string = "yli::ontology::PoliceHorse*";
    }
}
