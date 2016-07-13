#include "line_line_intersection.hpp"
#include "line2D.hpp"
#include "line3D.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

namespace geometry
{
    glm::vec2 do_lines_intersect(geometry::Line2D line1, geometry::Line2D line2)
    {
        // TODO: implement this function!
        glm::vec2 intersection_point;
        return intersection_point;
    }

    glm::vec3 do_lines_intersect(geometry::Line3D line1, geometry::Line3D line2)
    {
        // TODO: implement this function!
        glm::vec3 intersection_point;
        return intersection_point;
    }
}
