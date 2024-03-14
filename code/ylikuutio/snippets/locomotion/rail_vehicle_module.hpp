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

#ifndef YLIKUUTIO_SNIPPETS_LOCOMOTION_RAIL_VEHICLE_MODULE_HPP_INCLUDED
#define YLIKUUTIO_SNIPPETS_LOCOMOTION_RAIL_VEHICLE_MODULE_HPP_INCLUDED

#include "code/ylikuutio/ontology/locomotion_module.hpp"

namespace yli::ontology
{
    struct LocomotionModuleStruct;
    enum class LocomotionEnvironment;
}

namespace yli::snippets::locomotion
{
    class RailVehicleModule final : public yli::ontology::LocomotionModule
    {
        public:
            RailVehicleModule(const yli::ontology::LocomotionModuleStruct& rail_vehicle_module_struct);

        private:
            float max_speed    { 0.0f }; // m/s.
            float acceleration { 0.0f }; // m/s^2
            float deceleration { 0.0f }; // m/s^2

        // There is no angular movement for railways.
    };
}

#endif
