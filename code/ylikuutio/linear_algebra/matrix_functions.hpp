#ifndef __MATRIX_FUNCTIONS_HPP_INCLUDED
#define __MATRIX_FUNCTIONS_HPP_INCLUDED

#include "matrix.hpp"

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <cstddef>  // std::size_t
#include <memory>   // std::make_shared, std::shared_ptr
#include <stdint.h> // uint32_t etc.

namespace yli
{
    namespace linear_algebra
    {
        std::shared_ptr<yli::linear_algebra::Matrix> cat(std::size_t dimension, yli::linear_algebra::Matrix& old_matrix1, yli::linear_algebra::Matrix& old_matrix2);
    }
}

#endif
