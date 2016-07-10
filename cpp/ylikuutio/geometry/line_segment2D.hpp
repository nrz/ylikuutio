#ifndef __LINE_SEGMENT2D_HPP_INCLUDED
#define __LINE_SEGMENT2D_HPP_INCLUDED

#include "line_segment.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

namespace geometry
{
    class LineSegment2D : public LineSegment
    {
        public:
            // constructor.
            LineSegment2D(std::vector<float> point1, std::vector<float> point2)
                : LineSegment(point1, point2)
            {
                std::cout << "Hello from LineSegment2D constructor!\n";
            }
    };
}

#endif
