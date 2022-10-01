// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2022 Antti Nuortimo.
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

#ifndef YLIKUUTIO_GEOMETRY_LINE_3D_HPP_INCLUDED
#define YLIKUUTIO_GEOMETRY_LINE_3D_HPP_INCLUDED

#include "line.hpp"

// Include GLM
#ifndef GLM_GLM_HPP_INCLUDED
#define GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <vector>   // std::vector

namespace yli::geometry
{
    class Line3D : public Line
    {
        public:
            // constructor.
            Line3D(const std::vector<float>& point1, const std::vector<float>& point2)
                : Line(point1, point2)
            {
            }

            // constructor.
            Line3D(const std::vector<float>& general_form_coefficients, const float general_form_constant)
                : Line(general_form_coefficients, general_form_constant)
            {
            }

            bool do_lines_3d_intersect(const yli::geometry::Line3D& line1, const yli::geometry::Line3D& line2) const;
            bool do_lines_3d_intersect(const yli::geometry::Line3D& line) const;
    };
}

#endif
