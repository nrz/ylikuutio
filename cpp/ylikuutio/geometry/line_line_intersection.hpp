#ifndef __LINE_LINE_INTERSECTION_HPP_INCLUDED
#define __LINE_LINE_INTERSECTION_HPP_INCLUDED

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

namespace geometry
{
    class Line2D;
    class Line3D;

    glm::vec2 do_lines_intersect(geometry::Line2D line1, geometry::Line2D line2);
    glm::vec3 do_lines_intersect(geometry::Line3D line1, geometry::Line3D line2);
}

#endif
