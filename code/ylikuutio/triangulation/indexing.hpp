#ifndef __INDEXING_HPP_INCLUDED
#define __INDEXING_HPP_INCLUDED

#include "triangulation_enums.hpp"
#include "code/ylikuutio/common/globals.hpp"

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace geometry
{
    GLuint southwest(const int32_t current_vertex_i, const int32_t image_width);
    GLuint southeast(const int32_t current_vertex_i, const int32_t image_width);
    GLuint northwest(const int32_t current_vertex_i, const int32_t image_width);
    GLuint northeast(const int32_t current_vertex_i, const int32_t image_width);

    int32_t get_face_normal_i(
            const int32_t x,
            const int32_t z,
            const BilinearDirections compass_point_code,
            const int32_t actual_image_width);
}

#endif
