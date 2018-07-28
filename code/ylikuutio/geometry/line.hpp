#ifndef __LINE_HPP_INCLUDED
#define __LINE_HPP_INCLUDED

// Include standard headers
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli
{
    namespace geometry
    {
        class Line
        {
            public:
                // constructor.
                // can be used for creating n-dimensional lines.
                Line(const std::vector<float> point1, const std::vector<float> point2);

                // constructor.
                // can be used for creating n-dimensional lines.
                Line(const std::vector<float> general_form_coefficients, const float general_form_constant);

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
}

#endif
