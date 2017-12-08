#include "line3D.hpp"

namespace geometry
{
    bool Line3D::do_lines3D_intersect(const geometry::Line3D* const line1, const geometry::Line3D* const line2) const
    {
        // TODO: implement the function!
        return false;
    }

    bool Line3D::do_lines3D_intersect(const geometry::Line3D* const line) const
    {
        return geometry::Line3D::do_lines3D_intersect(line, this);
    }
}
