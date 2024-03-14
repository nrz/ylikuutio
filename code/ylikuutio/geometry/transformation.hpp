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

#ifndef YLIKUUTIO_GEOMETRY_TRANSFORMATION_HPP_INCLUDED
#define YLIKUUTIO_GEOMETRY_TRANSFORMATION_HPP_INCLUDED

#include "code/ylikuutio/geometry/transformation_struct.hpp"

// Include GLM
#ifndef GLM_GLM_HPP_INCLUDED
#define GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <vector>   // std::vector

namespace yli::geometry
{
    glm::vec3 transform_planar_world_vertex_into_cartesian_vertex(
            const glm::vec3& planar_world_vertex,
            const float sphere_radius);

    void transform_coordinates_to_curved_surface(
            const yli::geometry::TransformationStruct& transformation_struct,
            std::vector<glm::vec3>& temp_vertices);
}

#endif
