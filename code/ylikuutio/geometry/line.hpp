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

#ifndef YLIKUUTIO_GEOMETRY_LINE_HPP_INCLUDED
#define YLIKUUTIO_GEOMETRY_LINE_HPP_INCLUDED

// Include standard headers
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::geometry
{
    class Line
    {
        public:
            // constructor.
            // can be used for creating n-dimensional lines.
            Line(const std::vector<float>& point1, const std::vector<float>& point2);

            // constructor.
            // can be used for creating n-dimensional lines.
            Line(const std::vector<float>& general_form_coefficients, const float general_form_constant);

            std::string get_general_form_equation() const;

        protected:
            bool is_valid;
            std::vector<float> general_form_coefficients;
            float general_form_constant;

            bool are_points_defined;
            std::vector<float> point1;
            std::vector<float> point2;
    };
}

#endif
