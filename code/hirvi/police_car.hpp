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

#ifndef HIRVI_POLICE_CAR_HPP_INCLUDED
#define HIRVI_POLICE_CAR_HPP_INCLUDED

#include "code/ylikuutio/ontology/holobiont.hpp"
#include "code/ylikuutio/snippets/locomotion/road_vehicle_module.hpp"
#include "police_module.hpp"

namespace yli::ontology
{
    class Universe;
    class GenericParentModule;
    class GenericMasterModule;
    struct HolobiontStruct;
    struct LocomotionModuleStruct;
}

namespace hirvi
{
    class PoliceCar : public yli::ontology::Holobiont
    {
        public:
            explicit PoliceCar(
                    yli::ontology::Universe& universe,
                    const yli::ontology::HolobiontStruct& police_car_struct,
                    const yli::ontology::LocomotionModuleStruct& road_vehicle_struct,
                    yli::ontology::GenericParentModule* const scene_parent,
                    yli::ontology::GenericMasterModule* const symbiosis_master,
                    yli::ontology::GenericMasterModule* const brain_master);

            PoliceCar(const PoliceCar&) = delete;            // Delete copy constructor.
            PoliceCar &operator=(const PoliceCar&) = delete; // Delete copy assignment.

            ~PoliceCar() = default;

        private:
            yli::snippets::locomotion::RoadVehicleModule road_vehicle;
            hirvi::PoliceModule police;
    };
}

#endif