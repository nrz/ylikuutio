// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2023 Antti Nuortimo.
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

#ifndef YLIKUUTIO_GEOMETRY_LINE_SEGMENT_HPP_INCLUDED
#define YLIKUUTIO_GEOMETRY_LINE_SEGMENT_HPP_INCLUDED

#include "line.hpp"

// Include standard headers
#include <iostream> // std::cout, std::cerr
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::geometry
{
    class LineSegment : public Line
    {
        public:
            // constructor.
            // can be used for creating n-dimensional line segments.
            LineSegment(const std::vector<float>& point1, const std::vector<float>& point2)
                : Line(point1, point2)
            {
                std::cout << "Hello from LineSegment constructor!\n";
            }

            std::string get_equation();
    };
}

#endif
