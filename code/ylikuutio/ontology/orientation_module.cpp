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

#include "orientation_module.hpp"

namespace yli::ontology
{
    bool OrientationModule::operator==(const yli::ontology::OrientationModule& rhs) const noexcept
    {
        return this->roll == rhs.roll &&
            this->yaw == rhs.yaw &&
            this->pitch == rhs.pitch;
    }

    yli::ontology::OrientationModule& OrientationModule::operator=(const yli::ontology::OrientationModule& other) noexcept
    {
        if (&other == this)
        {
            return *this;
        }

        this->roll  = other.roll;
        this->yaw   = other.yaw;
        this->pitch = other.pitch;
        return *this;
    }

    glm::vec3 OrientationModule::get() const
    {
        return glm::vec3 { this->roll, this->yaw, this->pitch };
    }
}
