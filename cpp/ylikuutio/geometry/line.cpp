#include "line.hpp"

// Include standard headers
#include <string>   // std::string

namespace geometry
{
    Line::Line(std::vector<float> point1, std::vector<float> point2)
    {
    }

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
