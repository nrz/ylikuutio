#include "line.hpp"

// Include standard headers
#include <cmath>     // NAN, std::isnan, std::pow
#include <string>    // std::string
#include <vector>    // std::vector

namespace geometry
{
    // constructor.
    // can be used for creating n-dimensional lines.
    Line::Line(std::vector<float> point1, std::vector<float> point2)
    {
        if (point1 == point2)
        {
            this->is_valid = false; // two identical points do not define a line.
            this->general_form_coefficients.push_back(NAN);
            this->general_form_constant = NAN;
        }
        else
        {
            this->is_valid = true; // two distinct points define a line.
        }
    }

    // constructor.
    // can be used for creating n-dimensional lines.
    Line::Line(std::vector<float> general_form_coefficients, float general_form_constant)
    {
        this->general_form_coefficients = general_form_coefficients;
        this->general_form_constant = general_form_constant;
    }

    std::string Line::get_general_form_equation()
    {
        std::string line_equation;
        return line_equation;
    }
}
