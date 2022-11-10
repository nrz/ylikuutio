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

#ifndef HIRVI_POLICE_TRAIN_HPP_INCLUDED
#define HIRVI_POLICE_TRAIN_HPP_INCLUDED

#include "code/ylikuutio/ontology/holobiont.hpp"
#include "code/ylikuutio/snippets/locomotion/rail_vehicle_module.hpp"
#include "police_module.hpp"

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
    struct LocomotionModuleStruct;
}

namespace hirvi
{
    class PoliceTrain : public yli::ontology::Holobiont
    {
        public:
            explicit PoliceTrain(
                    yli::core::Application& application,
                    yli::ontology::Universe& universe,
                    const yli::ontology::HolobiontStruct& police_train_struct,
                    const yli::ontology::LocomotionModuleStruct& rail_vehicle_struct,
                    yli::ontology::GenericParentModule* const scene_parent,
                    yli::ontology::GenericMasterModule* const symbiosis_master,
                    yli::ontology::GenericMasterModule* const brain_master);

            PoliceTrain(const PoliceTrain&) = delete;            // Delete copy constructor.
            PoliceTrain &operator=(const PoliceTrain&) = delete; // Delete copy assignment.

            ~PoliceTrain() = default;

        private:
            yli::snippets::locomotion::RailVehicleModule rail_vehicle;
            hirvi::PoliceModule police;
    };
}

#endif
