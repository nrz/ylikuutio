#ifndef __SHORTEST_PATHS_HPP_INCLUDED
#define __SHORTEST_PATHS_HPP_INCLUDED

// Include standard headers
#include <memory>  // std::make_shared, std::shared_ptr

namespace yli
{
    namespace linear_algebra
    {
        class Matrix;
    }

    namespace graph
    {
        // TODO: convert `yli::linear_algebra::Matrix` into a class template.
        // TODO: convert this function into a function template.
        // Then, the maximum value of `T` is considered as infinite distance (no link).
        std::shared_ptr<yli::linear_algebra::Matrix> floyd_warshall(yli::linear_algebra::Matrix& adjacency_matrix);
    }
}

#endif
