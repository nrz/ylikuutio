#include "shortest_paths.hpp"
#include "code/ylikuutio/linear_algebra/matrix.hpp"

// Include standard headers
#include <algorithm> // std::min, std::max, etc.
#include <limits>    // std::numeric_limits
#include <cstddef>   // std::size_t
#include <memory>    // std::make_shared, std::shared_ptr

namespace yli
{
    namespace graph
    {
        std::shared_ptr<yli::linear_algebra::Matrix> floyd_warshall(yli::linear_algebra::Matrix& adjacency_matrix)
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

            std::size_t n_nodes = adjacency_matrix.get_width();

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
                        *distance_matrix << adjacency_matrix[j][i];
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
                        float distance_i_j = (*distance_matrix)[i][j];
                        float distance_i_k = (*distance_matrix)[i][k];
                        float distance_j_k = (*distance_matrix)[j][k];

                        if (distance_i_k == std::numeric_limits<float>::infinity() || 
                                distance_j_k == std::numeric_limits<float>::infinity())
                        {
                            // This can not be a shorter path, as at least 1 of these paths has infinite length.
                            continue;
                        }

                        if (distance_i_j == std::numeric_limits<float>::infinity())
                        {
                            // Update is to be without checking `distance_i_j` further. 
                            // FIXME: floats can be added without a check for overflow, but integers can not.
                            (*distance_matrix)[i][j] = distance_i_k + distance_j_k;
                            continue;
                        }

                        // FIXME: floats can be added without a check for overflow, but integers can not.
                        (*distance_matrix)[i][j] = std::min(distance_i_j, distance_i_k + distance_j_k);
                    }
                }
            }

            return distance_matrix;
        }
    }
}
