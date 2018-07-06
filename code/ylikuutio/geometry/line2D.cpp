#include "line2D.hpp"

namespace ylikuutio
{
    namespace geometry
    {
        bool Line2D::do_lines2D_intersect(const ylikuutio::geometry::Line2D* const line1, const ylikuutio::geometry::Line2D* const line2) const
        {
            // TODO: implement the function!
            return false;
        }

        bool Line2D::do_lines2D_intersect(const ylikuutio::geometry::Line2D* const line) const
        {
            return ylikuutio::geometry::Line2D::do_lines2D_intersect(line, this);
        }

        bool Line2D::is_identical_with(const ylikuutio::geometry::Line2D* const line) const
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
}
