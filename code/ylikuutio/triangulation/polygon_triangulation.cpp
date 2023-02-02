// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2023 Antti Nuortimo.
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

#include "polygon_triangulation.hpp"
#include "triangulate_polygons_struct.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace yli::triangulation
{
    bool triangulate_simple_polygon(
            const yli::triangulation::TriangulatePolygonsStruct& /* triangulate_polygons_struct */,
            std::vector<glm::vec3>& /* out_vertices */,
            std::vector<glm::vec2>& /* out_uvs */,
            std::vector<glm::vec3>& /* out_normals */)
    {
        // TODO: implement this function!
        return false;
    }

    bool triangulate_polygons(
            const yli::triangulation::TriangulatePolygonsStruct& triangulate_polygons_struct,
            std::vector<glm::vec3>& /* out_vertices */,
            std::vector<glm::vec2>& /* out_uvs */,
            std::vector<glm::vec3>& /* out_normals */)
    {
        // TODO: implement this function!

        // Find hidden vertices using `get_intersection_point(yli::geometry::LineSegment2D* line_segment1, yli::geometry::LineSegment2D* line_segment2)`.
        std::vector<std::vector<glm::vec2>>* vertex_data = triangulate_polygons_struct.input_vertices;

        // Each edge may have intersections with any other intersections
        // except immediately previous and immediately next intersections.
        // TODO: write the code!

        for (std::size_t vertex_i = 0; vertex_i < vertex_data->size(); vertex_i++)
        {
        }

        // All vertices (3D, explicitly defined and hidden) should be known now.

        // Divide complex polygons into simple polygons. Each vertex belongs to 1 or more simple polygons.
        // TODO: write the code!
        std::vector<std::vector<glm::vec3>> simple_polygons;

        for (std::size_t  vertex_i = 0; vertex_i < vertex_data->size(); vertex_i++)
        {
        }

        // Loop through simple polygons and triangulate them.
        // TODO: write the code!

        return false;
    }
}
