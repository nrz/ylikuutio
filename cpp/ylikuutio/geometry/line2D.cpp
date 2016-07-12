#include "line2D.hpp"

namespace geometry
{
    bool Line2D::do_lines2D_intersect(geometry::Line2D* line1, geometry::Line2D* line2)
    {
        // TODO: implement the function!
        return false;
    }

    bool Line2D::do_lines2D_intersect(geometry::Line2D* line)
    {
        return geometry::Line2D::do_lines2D_intersect(line, this);
    }
}
