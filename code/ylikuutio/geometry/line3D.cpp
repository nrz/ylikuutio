#include "line3D.hpp"

namespace geometry
{
    bool Line3D::do_lines3D_intersect(geometry::Line3D* line1, geometry::Line3D* line2)
    {
        // TODO: implement the function!
        return false;
    }

    bool Line3D::do_lines3D_intersect(geometry::Line3D* line)
    {
        return geometry::Line3D::do_lines3D_intersect(line, this);
    }
}
