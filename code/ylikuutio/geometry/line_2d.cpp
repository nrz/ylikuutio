// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2021 Antti Nuortimo.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "line_2d.hpp"

namespace yli::geometry
{
    bool Line2D::do_lines2D_intersect(const yli::geometry::Line2D* const line1, const yli::geometry::Line2D* const line2) const
    {
        // TODO: implement the function!
        return false;
    }

    bool Line2D::do_lines2D_intersect(const yli::geometry::Line2D* const line) const
    {
        return yli::geometry::Line2D::do_lines2D_intersect(line, this);
    }

    bool Line2D::is_identical_with(const yli::geometry::Line2D* const line) const
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
