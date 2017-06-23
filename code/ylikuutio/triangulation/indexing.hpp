#ifndef __INDEXING_HPP_INCLUDED
#define __INDEXING_HPP_INCLUDED

#include "triangulation_enums.hpp"
#include "code/ylikuutio/common/globals.hpp"

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace geometry
{
    GLuint southwest(int32_t current_vertex_i, int32_t image_width);
    GLuint southeast(int32_t current_vertex_i, int32_t image_width);
    GLuint northwest(int32_t current_vertex_i, int32_t image_width);
    GLuint northeast(int32_t current_vertex_i, int32_t image_width);

    int32_t get_face_normal_i(
            int32_t x,
            int32_t z,
            BilinearDirections compass_point_code,
            int32_t actual_image_width);
}

#endif
