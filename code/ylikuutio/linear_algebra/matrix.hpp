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

            // copy constructor.
            Matrix(Matrix& old_matrix);

            // destructor.
            ~Matrix();

            // Inspired by http://stackoverflow.com/questions/6969881/operator-overload/6969904#6969904
            class Proxy
            {
                public:
                    Proxy(float* proxy_array) : proxy_array(proxy_array) { }

                    float& operator[](const uint32_t index)
                    {
                        return proxy_array[index];
                    }

                private:
                    float* proxy_array;
            };

            void operator<<(const float rhs);
            bool operator==(const Matrix& rhs);
            Proxy operator[](const uint32_t index)
            {
                return Proxy(array_of_arrays[index]);
            }

            float det();

        private:
            bool is_square;
            uint32_t width;
            uint32_t height;
            uint32_t array_size;

            bool is_fully_populated;
            int32_t next_y_to_populate;
            int32_t next_x_to_populate;

            float** array_of_arrays;
    };

}

#endif
