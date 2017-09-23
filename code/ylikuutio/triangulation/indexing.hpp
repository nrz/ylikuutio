#ifndef __INDEXING_HPP_INCLUDED
#define __INDEXING_HPP_INCLUDED

#include "triangulation_enums.hpp"
#include "code/ylikuutio/common/globals.hpp"

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace geometry
{
    // For bilinear interpolation, southeast-northwest edges, and southwest-northeast edges.
    // These functions return indices.
    constexpr GLuint southwest(const int32_t current_vertex_i, const int32_t image_width)
    {
        return current_vertex_i - image_width - 1;
    }
    constexpr GLuint southeast(const int32_t current_vertex_i, const int32_t image_width)
    {
        return current_vertex_i - image_width;
    }
    constexpr GLuint northwest(const int32_t current_vertex_i, const int32_t image_width)
    {
        return current_vertex_i - 1;
    }
    constexpr GLuint northeast(const int32_t current_vertex_i, const int32_t image_width)
    {
        return current_vertex_i;
    }

    int32_t get_face_normal_i(
            const int32_t x,
            const int32_t z,
            const BilinearDirections compass_point_code,
            const int32_t actual_image_width);
}

#endif
