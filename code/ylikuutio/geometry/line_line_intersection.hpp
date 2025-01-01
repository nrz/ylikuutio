// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2025 Antti Nuortimo.
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

#ifndef YLIKUUTIO_GEOMETRY_LINE_LINE_INTERSECTION_HPP_INCLUDED
#define YLIKUUTIO_GEOMETRY_LINE_LINE_INTERSECTION_HPP_INCLUDED

// Include GLM
#ifndef GLM_GLM_HPP_INCLUDED
#define GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

namespace yli::geometry
{
    class Line2D;
    class Line3D;

    glm::vec2 get_intersection_point(const yli::geometry::Line2D* const line1, const yli::geometry::Line2D* const line2);
    glm::vec3 get_intersection_point(const yli::geometry::Line3D* const line1, const yli::geometry::Line3D* const line2);
}

#endif
