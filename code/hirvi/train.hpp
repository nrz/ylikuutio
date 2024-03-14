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

#ifndef HIRVI_TRAIN_HPP_INCLUDED
#define HIRVI_TRAIN_HPP_INCLUDED

#include "code/ylikuutio/ontology/holobiont.hpp"
#include "code/ylikuutio/snippets/locomotion/rail_vehicle_module.hpp"

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
    class Train : public yli::ontology::Holobiont
    {
        public:
            explicit Train(
                    yli::core::Application& application,
                    yli::ontology::Universe& universe,
                    const yli::ontology::HolobiontStruct& train_struct,
                    const yli::ontology::LocomotionModuleStruct& rail_vehicle_struct,
                    yli::ontology::GenericParentModule* const scene_parent,
                    yli::ontology::GenericMasterModule* const symbiosis_master,
                    yli::ontology::GenericMasterModule* const brain_master);

            Train(const Train&) = delete;            // Delete copy constructor.
            Train &operator=(const Train&) = delete; // Delete copy assignment.

            ~Train() = default;

            yli::snippets::locomotion::RailVehicleModule rail_vehicle;
    };
}

#endif
