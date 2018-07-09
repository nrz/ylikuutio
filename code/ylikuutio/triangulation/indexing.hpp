#ifndef __INDEXING_HPP_INCLUDED
#define __INDEXING_HPP_INCLUDED

#include "triangulation_enums.hpp"
#include "code/ylikuutio/common/globals.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace yli
{
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

        // for bilinear interpolation.
        constexpr int32_t get_face_normal_i(
                const int32_t x,
                const int32_t z,
                const BilinearDirections compass_point_code,
                const int32_t actual_image_width)
        {
            // Face indices example for a 4x4 image file using bilinear interpolation.
            //
            //  +-------+-------+-------+
            //  |\ 26  /|\ 30  /|\ 34  /|
            //  | \   / | \   / | \   / |
            //  |  \ /  |  \ /  |  \ /  |
            //  |25 x 27|29 x 31|33 x 35|
            //  |  / \  |  / \  |  / \  |
            //  | /   \ | /   \ | /   \ |
            //  |/ 24  \|/ 28  \|/ 32  \|
            //  +-------+-------+-------+
            //  |\ 14  /|\ 18  /|\ 22  /|
            //  | \   / | \   / | \   / |
            //  |  \ /  |  \ /  |  \ /  |
            //  |13 x 15|17 x 19|21 x 23|
            //  |  / \  |  / \  |  / \  |
            //  | /   \ | /   \ | /   \ |
            //  |/ 12  \|/ 16  \|/ 20  \|
            //  +-------+-------+-------+
            //  |\  2  /|\  6  /|\ 10  /|
            //  | \   / | \   / | \   / |
            //  |  \ /  |  \ /  |  \ /  |
            //  |1  x  3|5  x  7|9  x 11|
            //  |  / \  |  / \  |  / \  |
            //  | /   \ | /   \ | /   \ |
            //  |/  0  \|/  4  \|/  8  \|
            //  +-------+-------+-------+

            switch (compass_point_code)
            {
                case SSW:
                    return 4 * (z - 1) * (actual_image_width - 1) + (4 * x) - 1;
                case WSW:
                    return 4 * (z - 1) * (actual_image_width - 1) + (4 * x) - 2;
                case WNW:
                    return 4 * z * (actual_image_width - 1) + (4 * x) - 4;
                case NNW:
                    return 4 * z * (actual_image_width - 1) + (4 * x) - 1;
                case NNE:
                    return 4 * z * (actual_image_width - 1) + (4 * x) + 1;
                case ENE:
                    return 4 * z * (actual_image_width - 1) + (4 * x);
                case ESE:
                    return 4 * (z - 1) * (actual_image_width - 1) + (4 * x) + 2;
                case SSE:
                    return 4 * (z - 1) * (actual_image_width - 1) + (4 * x) + 1;
                default:
                    return -1;
            }
        }
    }
}

#endif
