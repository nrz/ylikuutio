#include "bilinear_interpolation.hpp"
#include "triangulation_helper_functions.hpp"
#include "code/ylikuutio/common/globals.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace geometry
{
    // for bilinear interpolation.
    glm::vec3 get_face_normal(
            std::vector<glm::vec3>& face_normal_data,
            uint32_t x,
            uint32_t z,
            BilinearDirections compass_point_code,
            uint32_t image_width)
    {
        uint32_t face_normal_i;

        switch (compass_point_code)
        {
            case SSW:
                face_normal_i = 4 * (z - 1) * (image_width - 1) + (4 * x) - 1;
                break;
            case WSW:
                face_normal_i = 4 * (z - 1) * (image_width - 1) + (4 * x) - 2;
                break;
            case WNW:
                face_normal_i = 4 * z * (image_width - 1) + (4 * x) - 4;
                break;
            case NNW:
                face_normal_i = 4 * z * (image_width - 1) + (4 * x) - 1;
                break;
            case NNE:
                face_normal_i = 4 * z * (image_width - 1) + (4 * x) + 1;
                break;
            case ENE:
                face_normal_i = 4 * z * (image_width - 1) + (4 * x);
                break;
            case ESE:
                face_normal_i = 4 * (z - 1) * (image_width - 1) + (4 * x) + 2;
                break;
            case SSE:
                face_normal_i = 4 * (z - 1) * (image_width - 1) + (4 * x) + 1;
                break;
            default:
                std::cerr << "invalid compass point code!\n";
                return glm::vec3(NAN, NAN, NAN);
        }
        return face_normal_data[face_normal_i];
    }

    // Face indices example for a 4x4 image file and bilinear interpolation.
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
    //  |\  3  /|\  6  /|\ 10  /|
    //  | \   / | \   / | \   / |
    //  |  \ /  |  \ /  |  \ /  |
    //  |1  x  2|5  x  7|9  x 11|
    //  |  / \  |  / \  |  / \  |
    //  | /   \ | /   \ | /   \ |
    //  |/  0  \|/  4  \|/  8  \|
    //  +-------+-------+-------+

}
