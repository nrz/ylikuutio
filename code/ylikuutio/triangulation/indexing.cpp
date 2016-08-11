#include "indexing.hpp"
#include "triangulation_enums.hpp"
#include "code/ylikuutio/common/globals.hpp"

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace geometry
{
    // for bilinear interpolation.
    int32_t get_face_normal_i(
            uint32_t x,
            uint32_t z,
            BilinearDirections compass_point_code,
            uint32_t image_width)
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
                return 4 * (z - 1) * (image_width - 1) + (4 * x) - 1;
            case WSW:
                return 4 * (z - 1) * (image_width - 1) + (4 * x) - 2;
            case WNW:
                return 4 * z * (image_width - 1) + (4 * x) - 4;
            case NNW:
                return 4 * z * (image_width - 1) + (4 * x) - 1;
            case NNE:
                return 4 * z * (image_width - 1) + (4 * x) + 1;
            case ENE:
                return 4 * z * (image_width - 1) + (4 * x);
            case ESE:
                return 4 * (z - 1) * (image_width - 1) + (4 * x) + 2;
            case SSE:
                return 4 * (z - 1) * (image_width - 1) + (4 * x) + 1;
            default:
                return -1;
        }
    }
}
