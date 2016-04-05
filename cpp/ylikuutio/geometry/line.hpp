#ifndef __LINE_HPP_INCLUDED
#define __LINE_HPP_INCLUDED

// Include standard headers
#include <string>   // std::string
#include <vector>   // std::vector

namespace geometry
{
    class Line
    {
        public:
            // constructor.
            Line(std::vector<float> point1, std::vector<float> point2);

            // constructor.
            Line(std::vector<float> general_form_coefficients, float general_form_constant);

            std::string get_general_form_equation();

        protected:
            std::vector<float> general_form_coefficients;
            float general_form_constant;
            bool is_valid;
    };
}

#endif
