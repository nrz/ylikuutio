#ifndef __LINE_SEGMENT_HPP_INCLUDED
#define __LINE_SEGMENT_HPP_INCLUDED

// Include standard headers
#include <string>   // std::string

namespace geometry
{
    class LineSegment
    {
        // constructor.
        LineSegment();

        std::string get_equation();
    };
}

#endif
