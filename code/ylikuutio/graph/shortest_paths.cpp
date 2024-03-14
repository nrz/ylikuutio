// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2024 Antti Nuortimo.
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

#include "shortest_paths.hpp"
#include "code/ylikuutio/linear_algebra/matrix.hpp"

// Include standard headers
#include <algorithm> // std::min, std::max, etc.
#include <limits>    // std::numeric_limits
#include <cstddef>   // std::size_t
#include <memory>    // std::make_shared, std::shared_ptr

namespace yli::graph
{
    std::shared_ptr<yli::linear_algebra::Matrix> floyd_warshall(const yli::linear_algebra::Matrix& adjacency_matrix)
    {
        // This function computes the distance matrix using Floyd-Warshall.
        //
        // TODO: convert `yli::linear_algebra::Matrix` into a class template.
        // TODO: convert this function into a function template.
        // Then, the maximum value of `T` is considered as infinite distance (no link).

        if (!adjacency_matrix.get_is_square() || adjacency_matrix.get_width() != adjacency_matrix.get_height())
        {
            // Adjacency matrix must be square.
            return nullptr;
        }

        const std::size_t n_nodes = adjacency_matrix.get_width();

        std::shared_ptr<yli::linear_algebra::Matrix> distance_matrix = std::make_shared<yli::linear_algebra::Matrix>(n_nodes, n_nodes);

        // Populate the distance matrix so that distance from any node to the same node is 0,
        // and distance for everything else is infinity.

        for (std::size_t j = 0; j < n_nodes; j++)
        {
            for (std::size_t i = 0; i < n_nodes; i++)
            {
                if (i == j)
                {
                    *distance_matrix << 0.0f;
                }
                else
                {
                    *distance_matrix << adjacency_matrix.get_value(i, j);
                }
            }
        }

        // OK, compute the distances using Floyd-Warshall.
        for (std::size_t k = 0; k < n_nodes; k++)
        {
            for (std::size_t i = 0; i < n_nodes; i++)
            {
                for (std::size_t j = 0; j < n_nodes; j++)
                {
                    const float distance_i_j = (*distance_matrix)[i][j];
                    const float distance_i_k = (*distance_matrix)[i][k];
                    const float distance_j_k = (*distance_matrix)[j][k];

                    if (distance_i_k == std::numeric_limits<float>::infinity() || 
                            distance_j_k == std::numeric_limits<float>::infinity())
                    {
                        // This can not be a shorter path, as at least 1 of these paths has infinite length.
                        continue;
                    }

                    if (distance_i_j == std::numeric_limits<float>::max())
                    {
                        // Check for overflow (needed for integers).
                        if (std::numeric_limits<float>::max() - distance_i_k >= distance_j_k)
                        {
                            (*distance_matrix)[i][j] = distance_i_k + distance_j_k;
                        }

                        continue;
                    }

                    // Check for overflow (needed for integers).
                    if (std::numeric_limits<float>::max() - distance_i_k >= distance_j_k)
                    {
                        (*distance_matrix)[i][j] = std::min(distance_i_j, distance_i_k + distance_j_k);
                    }
                }
            }
        }

        return distance_matrix;
    }
}
