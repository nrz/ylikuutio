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

#include "line_segment_line_segment_intersection.hpp"
#include "line_2d.hpp"
#include "line_3d.hpp"
#include "line_segment_2d.hpp"
#include "line_line_intersection.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>    // NAN

namespace yli::geometry
{
    glm::vec2 get_intersection_point(const yli::geometry::LineSegment2D* const line_segment1, const yli::geometry::LineSegment2D* const line_segment2)
    {
        // See http://mathworld.wolfram.com/Line-LineIntersection.html

        // Line segment 1.
        glm::vec2 line_segment1_point1 = glm::vec2(line_segment1->x1, line_segment1->y1);
        glm::vec2 line_segment1_point2 = glm::vec2(line_segment1->x2, line_segment1->y2);

        // Line segment 2.
        glm::vec2 line_segment2_point1 = glm::vec2(line_segment2->x1, line_segment2->y1);
        glm::vec2 line_segment2_point2 = glm::vec2(line_segment2->x2, line_segment2->y2);

        yli::geometry::Line2D line1 = yli::geometry::Line2D(line_segment1_point1, line_segment1_point2);
        yli::geometry::Line2D line2 = yli::geometry::Line2D(line_segment2_point1, line_segment2_point2);

        glm::vec2 potential_intersection_point = yli::geometry::get_intersection_point(&line1, &line2);

        glm::vec2 line_segment1_point_with_lower_x;
        glm::vec2 line_segment1_point_with_higher_x;

        if (line_segment1_point1.x < line_segment1_point2.x)
        {
            line_segment1_point_with_lower_x = line_segment1_point1;
            line_segment1_point_with_higher_x = line_segment1_point2;
        }
        else
        {
            line_segment1_point_with_lower_x = line_segment1_point2;
            line_segment1_point_with_higher_x = line_segment1_point1;
        }

        glm::vec2 line_segment2_point_with_lower_x;
        glm::vec2 line_segment2_point_with_higher_x;

        if (line_segment2_point1.x < line_segment2_point2.x)
        {
            line_segment2_point_with_lower_x = line_segment2_point1;
            line_segment2_point_with_higher_x = line_segment2_point2;
        }
        else
        {
            line_segment2_point_with_lower_x = line_segment2_point2;
            line_segment2_point_with_higher_x = line_segment2_point1;
        }

        glm::vec2 line_segment1_point_with_lower_y;
        glm::vec2 line_segment1_point_with_higher_y;

        if (line_segment1_point1.y < line_segment1_point2.y)
        {
            line_segment1_point_with_lower_y = line_segment1_point1;
            line_segment1_point_with_higher_y = line_segment1_point2;
        }
        else
        {
            line_segment1_point_with_lower_y = line_segment1_point2;
            line_segment1_point_with_higher_y = line_segment1_point1;
        }

        glm::vec2 line_segment2_point_with_lower_y;
        glm::vec2 line_segment2_point_with_higher_y;

        if (line_segment2_point1.y < line_segment2_point2.y)
        {
            line_segment2_point_with_lower_y = line_segment2_point1;
            line_segment2_point_with_higher_y = line_segment2_point2;
        }
        else
        {
            line_segment2_point_with_lower_y = line_segment2_point2;
            line_segment2_point_with_higher_y = line_segment2_point1;
        }

        if (potential_intersection_point.x >= line_segment1_point_with_lower_x.x
                && potential_intersection_point.x <= line_segment1_point_with_higher_x.x
                && potential_intersection_point.y >= line_segment1_point_with_lower_y.y
                && potential_intersection_point.y <= line_segment1_point_with_higher_y.y
                && potential_intersection_point.x >= line_segment2_point_with_lower_x.x
                && potential_intersection_point.x <= line_segment2_point_with_higher_x.x
                && potential_intersection_point.y >= line_segment2_point_with_lower_y.y
                && potential_intersection_point.y <= line_segment2_point_with_higher_y.y)
        {
            return potential_intersection_point;
        }

        return glm::vec2(NAN, NAN);
    }
}
