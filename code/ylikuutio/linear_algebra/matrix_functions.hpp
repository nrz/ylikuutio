#ifndef __MATRIX_FUNCTIONS_HPP_INCLUDED
#define __MATRIX_FUNCTIONS_HPP_INCLUDED

#include "matrix.hpp"

namespace linear_algebra
{
    Matrix cat(uint32_t dimension, Matrix& old_matrix1, Matrix& old_matrix2);
}

#endif
