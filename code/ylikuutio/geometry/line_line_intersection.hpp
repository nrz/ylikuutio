#ifndef __LINE_LINE_INTERSECTION_HPP_INCLUDED
#define __LINE_LINE_INTERSECTION_HPP_INCLUDED

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

namespace yli
{
    namespace geometry
    {
        class Line2D;
        class Line3D;

        glm::vec2 get_intersection_point(const yli::geometry::Line2D* const line1, const yli::geometry::Line2D* const line2);
        glm::vec3 get_intersection_point(const yli::geometry::Line3D* const line1, const yli::geometry::Line3D* const line2);
    }
}

#endif
