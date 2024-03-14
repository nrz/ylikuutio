// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2024 Antti Nuortimo.
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

#include "line_3d.hpp"

namespace yli::geometry
{
    bool Line3D::do_lines_3d_intersect(const yli::geometry::Line3D& /* line1 */, const yli::geometry::Line3D& /* line2 */) const
    {
        // TODO: implement the function!
        return false;
    }

    bool Line3D::do_lines_3d_intersect(const yli::geometry::Line3D& line) const
    {
        return yli::geometry::Line3D::do_lines_3d_intersect(line, *this);
    }
}
