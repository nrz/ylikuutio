#ifndef __LINE2D_HPP_INCLUDED
#define __LINE2D_HPP_INCLUDED

#include "line.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
#include <vector>   // std::vector

namespace geometry
{
    class Line2D : public Line
    {
        public:
            // constructor.
            Line2D(std::vector<float> point1, std::vector<float> point2)
                : Line(point1, point2)
            {
                std::cout << "Hello from Line2D constructor!\n";

                // The general form of a 2D line:
                // Ax + By + C = 0
                //
                // The slope-intercept form of a 2D line:
                // y = mx + b
                //
                // The point-slope form of a 2D line:
                // y - y1 = m(x - x1)
            }

            // constructor.
            Line2D(std::vector<float> general_form_coefficients, float general_form_constant)
                : Line(general_form_coefficients, general_form_constant)
            {
                std::cout << "Hello from Line2D constructor!\n";

                // The general form of a 2D line:
                // Ax + By + C = 0
                //
                // The slope-intercept form of a 2D line:
                // y = mx + b
                //
                // The point-slope form of a 2D line:
                // y - y1 = m(x - x1)
            }

            bool do_lines2D_intersect(geometry::Line2D* line1, geometry::Line2D* line2);
            bool do_lines2D_intersect(geometry::Line2D* line);
    };
}

#endif
