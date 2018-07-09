#include "line_line_intersection.hpp"
#include "line2D.hpp"
#include "line3D.hpp"
#include "code/ylikuutio/linear_algebra/matrix.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow

namespace yli
{
    namespace geometry
    {
        glm::vec2 get_intersection_point(const yli::geometry::Line2D* const line1, const yli::geometry::Line2D* const line2)
        {
            // See http://mathworld.wolfram.com/Line-LineIntersection.html

            linear_algebra::Matrix lower_matrix_for_solving_x_and_y(2, 2);
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

            linear_algebra::Matrix upper_matrix_for_solving_x(2, 2);
            upper_matrix_for_solving_x << line1->determinant; upper_matrix_for_solving_x << line1->x1_minus_x2;
            upper_matrix_for_solving_x << line2->determinant; upper_matrix_for_solving_x << line2->x1_minus_x2;
            float det_upper_matrix_for_solving_x = upper_matrix_for_solving_x.det();

            linear_algebra::Matrix upper_matrix_for_solving_y(2, 2);
            upper_matrix_for_solving_y << line1->determinant; upper_matrix_for_solving_y << line1->y1_minus_y2;
            upper_matrix_for_solving_y << line2->determinant; upper_matrix_for_solving_y << line2->y1_minus_y2;
            float det_upper_matrix_for_solving_y = upper_matrix_for_solving_y.det();

            // Compute x and y coordinates.
            float x = det_upper_matrix_for_solving_x / det_lower_matrix_for_solving_x_and_y;
            float y = det_upper_matrix_for_solving_y / det_lower_matrix_for_solving_x_and_y;
            return glm::vec2(x, y);
        }

        glm::vec3 get_intersection_point(const yli::geometry::Line3D* const line1, const yli::geometry::Line3D* const line2)
        {
            // TODO: implement this function!
            glm::vec3 intersection_point;
            return intersection_point;
        }
    }
}
