#include "line2D.hpp"

namespace geometry
{
    bool Line2D::do_lines2D_intersect(const geometry::Line2D* const line1, const geometry::Line2D* const line2) const
    {
        // TODO: implement the function!
        return false;
    }

    bool Line2D::do_lines2D_intersect(const geometry::Line2D* const line) const
    {
        return geometry::Line2D::do_lines2D_intersect(line, this);
    }

    bool Line2D::is_identical_with(const geometry::Line2D* const line) const
    {
        if (this->x1 == line->x1 &&
                this->y1 == line->y1 &&
                this->x2 == line->x2 &&
                this->y2 == line->y2)
        {
            return true;
        }
        return false;
    }
}
