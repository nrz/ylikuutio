#ifndef __LINE_SEGMENT3D_HPP_INCLUDED
#define __LINE_SEGMENT3D_HPP_INCLUDED

#include "line_segment.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <vector>   // std::vector

namespace yli
{
    namespace geometry
    {
        class LineSegment3D : public LineSegment
        {
            public:
                // constructor.
                LineSegment3D(const std::vector<float> point1, const std::vector<float> point2)
                    : LineSegment(point1, point2)
                {
                }
        };
    }
}

#endif
