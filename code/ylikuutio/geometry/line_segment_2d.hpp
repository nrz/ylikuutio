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

#ifndef __YLIKUUTIO_GEOMETRY_LINE_SEGMENT_2D_HPP_INCLUDED
#define __YLIKUUTIO_GEOMETRY_LINE_SEGMENT_2D_HPP_INCLUDED

#include "line_2d.hpp"
#include "line_segment.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <vector>   // std::vector

namespace yli::geometry
{
    class LineSegment2D final : public Line2D
    {
        public:
            // constructor.
            LineSegment2D(const std::vector<float>& point1, const std::vector<float>& point2)
                : Line2D(point1, point2)
            {
            }

            // constructor (delegate the constructor).
            LineSegment2D(const glm::vec2& point1, const glm::vec2& point2)
                : LineSegment2D(std::vector<float>{ point1.x, point1.y }, std::vector<float>{ point2.x, point2.y })
                {
                }
    };
}

#endif
