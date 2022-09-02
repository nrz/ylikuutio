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

#include "orientation_module.hpp"

namespace yli::ontology
{
    bool OrientationModule::operator==(const yli::ontology::OrientationModule& rhs) const
    {
        return this->roll == rhs.roll &&
            this->yaw == rhs.yaw &&
            this->pitch == rhs.pitch;
    }

    bool OrientationModule::operator!=(const yli::ontology::OrientationModule& rhs) const
    {
        return !this->operator==(rhs);
    }

    OrientationModule::OrientationModule(const yli::ontology::OrientationModule& original)
        : roll { original.roll },
        yaw    { original.yaw },
        pitch  { original.pitch }
    {
    }
}
