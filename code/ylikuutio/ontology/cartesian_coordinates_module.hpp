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

#ifndef __YLIKUUTIO_ONTOLOGY_CARTESIAN_COORDINATES_MODULE_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_CARTESIAN_COORDINATES_MODULE_HPP_INCLUDED

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <utility> // std::move

namespace yli::ontology
{
    class CartesianCoordinatesModule
    {
        public:
            bool operator==(const yli::ontology::CartesianCoordinatesModule& rhs) const noexcept;
            bool operator!=(const yli::ontology::CartesianCoordinatesModule& rhs) const noexcept;

            CartesianCoordinatesModule(const yli::ontology::CartesianCoordinatesModule& original) noexcept;

            CartesianCoordinatesModule(const glm::vec3& xyz) noexcept;

            CartesianCoordinatesModule(const float x, const float y, const float z) noexcept;

            void set_x(const float x) noexcept;
            float get_x() const noexcept;

            void set_y(const float y) noexcept;
            float get_y() const noexcept;

            void set_z(const float z) noexcept;
            float get_z() const noexcept;

            glm::vec3 xyz;
    };
}

#endif