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

#include "cartesian_coordinates_module.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

namespace yli::ontology
{
    bool CartesianCoordinatesModule::operator==(const yli::ontology::CartesianCoordinatesModule& rhs) const noexcept
    {
        return this->xyz == rhs.xyz;
    }

    bool CartesianCoordinatesModule::operator!=(const yli::ontology::CartesianCoordinatesModule& rhs) const noexcept
    {
        return !this->operator==(rhs);
    }

    CartesianCoordinatesModule::CartesianCoordinatesModule(const yli::ontology::CartesianCoordinatesModule& original) noexcept
        : xyz { original.xyz }
    {
    }

    CartesianCoordinatesModule::CartesianCoordinatesModule(const glm::vec3& xyz) noexcept
        : xyz { xyz }
    {
    }

    CartesianCoordinatesModule::CartesianCoordinatesModule(const float x, const float y, const float z) noexcept
        : xyz { glm::vec3(x, y, z) }
    {
    }

    void CartesianCoordinatesModule::set_x(const float x) noexcept
    {
        this->xyz.x = x;
    }

    float CartesianCoordinatesModule::get_x() const noexcept
    {
        return this->xyz.x;
    }

    void CartesianCoordinatesModule::set_y(const float y) noexcept
    {
        this->xyz.y = y;
    }

    float CartesianCoordinatesModule::get_y() const noexcept
    {
        return this->xyz.y;
    }

    void CartesianCoordinatesModule::set_z(const float z) noexcept
    {
        this->xyz.z = z;
    }

    float CartesianCoordinatesModule::get_z() const noexcept
    {
        return this->xyz.z;
    }
}
