// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2021 Antti Nuortimo.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef __YLIKUUTIO_TRIANGULATION_INDEXING_HPP_INCLUDED
#define __YLIKUUTIO_TRIANGULATION_INDEXING_HPP_INCLUDED

#include "triangulation_enums.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <vector>   // std::vector

namespace yli::triangulation
{
    // For bilinear interpolation, southeast-northwest edges, and southwest-northeast edges.
    // These functions return indices.
    constexpr std::size_t southwest(const std::size_t current_vertex_i, const std::size_t image_width)
    {
        return current_vertex_i - image_width - 1;
    }
    constexpr std::size_t southeast(const std::size_t current_vertex_i, const std::size_t image_width)
    {
        return current_vertex_i - image_width;
    }
    constexpr std::size_t northwest(const std::size_t current_vertex_i, const std::size_t image_width)
    {
        return current_vertex_i - 1;
    }
    constexpr std::size_t northeast(const std::size_t current_vertex_i, const std::size_t image_width)
    {
        return current_vertex_i;
    }

    // for bilinear interpolation.
    constexpr std::size_t get_face_normal_i(
            const std::size_t x,
            const std::size_t z,
            const yli::triangulation::BilinearDirections compass_point_code,
            const std::size_t actual_image_width)
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
            case yli::triangulation::BilinearDirections::SSW:
                return 4 * (z - 1) * (actual_image_width - 1) + (4 * x) - 1;
            case yli::triangulation::BilinearDirections::WSW:
                return 4 * (z - 1) * (actual_image_width - 1) + (4 * x) - 2;
            case yli::triangulation::BilinearDirections::WNW:
                return 4 * z * (actual_image_width - 1) + (4 * x) - 4;
            case yli::triangulation::BilinearDirections::NNW:
                return 4 * z * (actual_image_width - 1) + (4 * x) - 1;
            case yli::triangulation::BilinearDirections::NNE:
                return 4 * z * (actual_image_width - 1) + (4 * x) + 1;
            case yli::triangulation::BilinearDirections::ENE:
                return 4 * z * (actual_image_width - 1) + (4 * x);
            case yli::triangulation::BilinearDirections::ESE:
                return 4 * (z - 1) * (actual_image_width - 1) + (4 * x) + 2;
            case yli::triangulation::BilinearDirections::SSE:
                return 4 * (z - 1) * (actual_image_width - 1) + (4 * x) + 1;
            default:
                return 0; // this line should never be reached.
        }
    }
}

#endif
