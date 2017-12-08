#ifndef __LINE2D_HPP_INCLUDED
#define __LINE2D_HPP_INCLUDED

#include "line.hpp"
#include "code/ylikuutio/linear_algebra/matrix.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <vector>   // std::vector

namespace geometry
{
    class Line2D : public Line
    {
        public:
            // constructor.
            Line2D(const std::vector<float> point1, const std::vector<float> point2)
                : Line(point1, point2)
            {
                linear_algebra::Matrix line_points_matrix(2, 2);
                line_points_matrix << this->point1.at(0); line_points_matrix << this->point1.at(1);
                line_points_matrix << this->point2.at(0); line_points_matrix << this->point2.at(1);
                this->determinant = line_points_matrix.det();

                this->x1 = this->point1.at(0);
                this->y1 = this->point1.at(1);
                this->x2 = this->point2.at(0);
                this->y2 = this->point2.at(1);
                this->x1_minus_x2 = this->x1 - this->x2;
                this->y1_minus_y2 = this->y1 - this->y2;

                // The general form of a 2D line:
                // Ax + By + C = 0
                //
                // The slope-intercept form of a 2D line:
                // y = mx + b
                //
                // The point-slope form of a 2D line:
                // y - y1 = m(x - x1)
            }

            // constructor (delegate the constructor).
            Line2D(const glm::vec2 point1, const glm::vec2 point2)
                : Line2D(std::vector<float>{ point1.x, point1.y }, std::vector<float>{ point2.x, point2.y })
                {
                }

            // constructor.
            Line2D(const std::vector<float> general_form_coefficients, const float general_form_constant)
                : Line(general_form_coefficients, general_form_constant)
            {
                // The general form of a 2D line:
                // Ax + By + C = 0
                //
                // The slope-intercept form of a 2D line:
                // y = mx + b
                //
                // The point-slope form of a 2D line:
                // y - y1 = m(x - x1)
            }

            bool is_identical_with(const geometry::Line2D* const line) const;   // Here, identical means that points are identical.

            bool do_lines2D_intersect(const geometry::Line2D* const line1, const geometry::Line2D* const line2) const;
            bool do_lines2D_intersect(const geometry::Line2D* const line) const;

            glm::vec2 vec2_point1;
            glm::vec2 vec2_point2;

            float x1;
            float y1;
            float x2;
            float y2;

            float x1_minus_x2;
            float y1_minus_y2;

            // | x1 y1 |
            // | x2 y2 |
            float determinant;
    };
}

#endif
