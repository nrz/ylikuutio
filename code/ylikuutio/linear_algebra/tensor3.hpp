#ifndef __TENSOR3_HPP_INCLUDED
#define __TENSOR3_HPP_INCLUDED

#include "matrix.hpp"

// Include standard headers
#include <stdint.h> // uint32_t etc.

namespace linear_algebra
{
    class Tensor3
    {
        public:
            // constructor.
            Tensor3(uint32_t height, uint32_t width, uint32_t depth);

            // copy constructor.
            Tensor3(Tensor3& old_tensor3);

            // constructor.
            Tensor3(Matrix& old_matrix);

            // destructor.
            ~Tensor3();

        private:
            bool is_cube;
            uint32_t width;
            uint32_t height;
            uint32_t depth;

            bool is_fully_populated;

            // `class Tensor3` uses the same coordinate order as MATLAB,
            // to make testing easier. So: y, x, z.
            int32_t next_y_to_populate;
            int32_t next_x_to_populate;
            int32_t next_z_to_populate;

            float*** array_of_arrays_of_arrays;
    };
}

#endif
