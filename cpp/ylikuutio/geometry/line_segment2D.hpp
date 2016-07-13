#ifndef __LINE_SEGMENT2D_HPP_INCLUDED
#define __LINE_SEGMENT2D_HPP_INCLUDED

#include "line2D.hpp"
#include "line_segment.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

namespace geometry
{
    class LineSegment2D : public Line2D
    {
        public:
            // constructor.
            LineSegment2D(std::vector<float> point1, std::vector<float> point2)
                : Line2D(point1, point2)
            {
                std::cout << "Hello from LineSegment2D constructor!\n";
            }

            // constructor (delegate the constructor).
            LineSegment2D(glm::vec2 point1, glm::vec2 point2)
                : LineSegment2D(std::vector<float>{ point1.x, point1.y }, std::vector<float>{ point2.x, point2.y })
                {
                    std::cout << "Hello from LineSegment2D constructor!\n";
                }
    };
}

#endif
