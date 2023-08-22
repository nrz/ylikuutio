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

#include "line_line_intersection.hpp"
#include "line_2d.hpp"
#include "line_3d.hpp"
#include "code/ylikuutio/linear_algebra/matrix.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow

namespace yli::geometry
{
    glm::vec2 get_intersection_point(const yli::geometry::Line2D* const line1, const yli::geometry::Line2D* const line2)
    {
        // See http://mathworld.wolfram.com/Line-LineIntersection.html

        yli::linear_algebra::Matrix lower_matrix_for_solving_x_and_y(2, 2);
        lower_matrix_for_solving_x_and_y << line1->x1_minus_x2; lower_matrix_for_solving_x_and_y << line1->y1_minus_y2;
        lower_matrix_for_solving_x_and_y << line2->x1_minus_x2; lower_matrix_for_solving_x_and_y << line2->y1_minus_y2;
        float det_lower_matrix_for_solving_x_and_y = lower_matrix_for_solving_x_and_y.det();

        if (det_lower_matrix_for_solving_x_and_y == 0.0f)
        {
            // Lines are parallel, they do not intersect!
            return glm::vec2(NAN, NAN);
        }

        // Lines do intersect, so let's compute where!
        // TODO: Implement support for vertical lines!

        yli::linear_algebra::Matrix upper_matrix_for_solving_x(2, 2);
        upper_matrix_for_solving_x << line1->determinant; upper_matrix_for_solving_x << line1->x1_minus_x2;
        upper_matrix_for_solving_x << line2->determinant; upper_matrix_for_solving_x << line2->x1_minus_x2;
        float det_upper_matrix_for_solving_x = upper_matrix_for_solving_x.det();

        yli::linear_algebra::Matrix upper_matrix_for_solving_y(2, 2);
        upper_matrix_for_solving_y << line1->determinant; upper_matrix_for_solving_y << line1->y1_minus_y2;
        upper_matrix_for_solving_y << line2->determinant; upper_matrix_for_solving_y << line2->y1_minus_y2;
        float det_upper_matrix_for_solving_y = upper_matrix_for_solving_y.det();

        // Compute x and y coordinates.
        float x = det_upper_matrix_for_solving_x / det_lower_matrix_for_solving_x_and_y;
        float y = det_upper_matrix_for_solving_y / det_lower_matrix_for_solving_x_and_y;
        return glm::vec2(x, y);
    }

    glm::vec3 get_intersection_point(const yli::geometry::Line3D* const /* line1 */, const yli::geometry::Line3D* const /* line2 */)
    {
        // TODO: implement this function!
        glm::vec3 intersection_point { NAN, NAN, NAN };
        return intersection_point;
    }
}
