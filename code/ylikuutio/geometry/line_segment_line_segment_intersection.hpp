#ifndef __LINE_SEGMENT_LINE_SEGMENT_INTERSECTION_HPP_INCLUDED
#define __LINE_SEGMENT_LINE_SEGMENT_INTERSECTION_HPP_INCLUDED

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

namespace geometry
{
    class LineSegment2D;
    class LineSegment3D;

    glm::vec2 get_intersection_point(geometry::LineSegment2D* line1, geometry::LineSegment2D* line2);
    glm::vec3 get_intersection_point(geometry::LineSegment3D* line1, geometry::LineSegment3D* line2);
}

#endif
