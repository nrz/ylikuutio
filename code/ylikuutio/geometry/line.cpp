#include "line.hpp"

// Include standard headers
#include <cmath>     // NAN, std::isnan, std::pow
#include <string>    // std::string
#include <vector>    // std::vector

namespace geometry
{
    // constructor.
    // can be used for creating n-dimensional lines.
    Line::Line(const std::vector<float> point1, const std::vector<float> point2)
    {
        this->general_form_constant = NAN;

        if (point1 == point2 || point1.size() != point2.size())
        {
            this->is_valid = false; // two identical points do not define a line.
            this->are_points_defined = false;
            this->general_form_coefficients.push_back(NAN);
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
    Line::Line(const std::vector<float> general_form_coefficients, const float general_form_constant)
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
