#ifndef __MATRIX_FUNCTIONS_HPP_INCLUDED
#define __MATRIX_FUNCTIONS_HPP_INCLUDED

#include "matrix.hpp"

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <memory>   // std::make_shared, std::shared_ptr

namespace linear_algebra
{
    std::shared_ptr<linear_algebra::Matrix> cat(uint32_t dimension, linear_algebra::Matrix& old_matrix1, linear_algebra::Matrix& old_matrix2);
}

#endif
