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

#include "swim_module.hpp"
#include "code/ylikuutio/ontology/locomotion_module.hpp"
#include "code/ylikuutio/ontology/locomotion_module_struct.hpp"
#include "code/ylikuutio/ontology/locomotion_environment.hpp"

namespace yli::snippets::locomotion
{
    SwimModule::SwimModule(const yli::ontology::LocomotionModuleStruct& swim_module_struct)
        : yli::ontology::LocomotionModule(yli::ontology::LocomotionEnvironment::WATER),
        max_speed         { swim_module_struct.max_speed },
        acceleration      { swim_module_struct.acceleration },
        deceleration      { swim_module_struct.deceleration },
        max_angular_speed { swim_module_struct.max_angular_speed }
    {
    }
}
