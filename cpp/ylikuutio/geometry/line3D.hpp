#ifndef __LINE3D_HPP_INCLUDED
#define __LINE3D_HPP_INCLUDED

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
    class Line3D : public Line
    {
        public:
            // constructor.
            Line3D(std::vector<float> point1, std::vector<float> point2)
                : Line(point1, point2)
            {
                std::cout << "Hello from Line3D constructor!\n";
            }

            // constructor.
            Line3D(std::vector<float> general_form_coefficients, float general_form_constant)
                : Line(general_form_coefficients, general_form_constant)
            {
                std::cout << "Hello from Line3D constructor!\n";
            }
    };
}

#endif
