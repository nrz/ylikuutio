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

#include "line.hpp"

// Include standard headers
#include <cmath>     // NAN, std::isnan, std::pow
#include <string>    // std::string
#include <vector>    // std::vector

namespace yli::geometry
{
    // constructor.
    // can be used for creating n-dimensional lines.
    Line::Line(const std::vector<float>& point1, const std::vector<float>& point2)
    {
        this->general_form_constant = NAN;

        if (point1 == point2 || point1.size() != point2.size())
        {
            this->is_valid = false; // two identical points do not define a line.
            this->are_points_defined = false;
            this->general_form_coefficients.emplace_back(NAN);
        }
        else
        {
            this->is_valid = true; // two distinct points define a line.
            this->are_points_defined = true;
            this->point1 = point1;
            this->point2 = point2;
        }
    }

    // constructor.
    // can be used for creating n-dimensional lines.
    Line::Line(const std::vector<float>& general_form_coefficients, const float general_form_constant)
    {
        // TODO: add checks for the validity of general form coefficients and general form constant!
        this->is_valid = true;
        this->are_points_defined = true;
        this->general_form_coefficients = general_form_coefficients;
        this->general_form_constant = general_form_constant;
    }

    std::string Line::get_general_form_equation() const
    {
        // TODO: implement this function!
        std::string line_equation;
        return line_equation;
    }
}
