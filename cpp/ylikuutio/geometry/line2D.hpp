#ifndef __LINE2D_HPP_INCLUDED
#define __LINE2D_HPP_INCLUDED

#include "line.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

namespace geometry
{
    class Line2D : public Line
    {
        public:
            // constructor.
            Line2D(std::vector<float> point1, std::vector<float> point2) : Line(point1, point2) {}

            // constructor.
            Line2D(glm::vec2 point1, glm::vec2 point2) : Line2D(std::vector<float> { point1.x, point1.y }, std::vector<float> { point2.x, point2.y }) {}
    };
}

#endif
