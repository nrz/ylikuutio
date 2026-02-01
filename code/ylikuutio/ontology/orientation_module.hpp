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

#ifndef YLIKUUTIO_ONTOLOGY_ORIENTATION_MODULE_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_ORIENTATION_MODULE_HPP_INCLUDED

// Include GLM
#ifndef GLM_GLM_HPP_INCLUDED
#define GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

namespace yli::ontology
{
    class OrientationModule
    {
        public:
            bool operator==(const OrientationModule& rhs) const noexcept;
            bool operator!=(const OrientationModule& rhs) const = default;
            OrientationModule& operator=(const OrientationModule& other) = default;

            OrientationModule() = default;

            ~OrientationModule() = default;

            OrientationModule(const OrientationModule& original) = default;

            OrientationModule(const float roll, const float yaw, const float pitch)
                : roll { roll },
                yaw    { yaw },
                pitch  { pitch }
            {
            }

            glm::vec3 get() const;

            float roll  { 0.0f };
            float yaw   { 0.0f };
            float pitch { 0.0f };
    };
}

#endif
