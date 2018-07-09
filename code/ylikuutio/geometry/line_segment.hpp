#ifndef __LINE_SEGMENT_HPP_INCLUDED
#define __LINE_SEGMENT_HPP_INCLUDED

#include "line.hpp"

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli
{
    namespace geometry
    {
        class LineSegment : public Line
        {
            public:
                // constructor.
                // can be used for creating n-dimensional line segments.
                LineSegment(const std::vector<float> point1, const std::vector<float> point2)
                    : Line(point1, point2)
                {
                    std::cout << "Hello from LineSegment constructor!\n";
                }

                std::string get_equation();
        };
    }
}

#endif
