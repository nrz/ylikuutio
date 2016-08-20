#ifndef __MATRIX_HPP_INCLUDED
#define __MATRIX_HPP_INCLUDED

// Include standard headers
#include <stdint.h> // uint32_t etc.

namespace linear_algebra
{
    class Matrix
    {
        public:
            // constructor.
            Matrix(uint32_t width, uint32_t height);

            // destructor.
            ~Matrix();

            void operator<<(float rhs);
            bool operator==(const Matrix& rhs);
            float* operator()(const uint32_t y, const uint32_t x);

        private:
            bool is_square;
            uint32_t width;
            uint32_t height;
            uint32_t array_size;

            bool is_fully_populated;
            int32_t next_i_to_populate;

            float* array;
    };

}

#endif
