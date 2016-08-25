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

            // Inspired by http://stackoverflow.com/questions/6969881/operator-overload/6969904#6969904
            class Proxy2D
            {
                public:
                    Proxy2D(float** array_of_arrays) : array_of_arrays(array_of_arrays) { }

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

                    Proxy operator[](const uint32_t index)
                    {
                        return array_of_arrays[index];
                    }

                private:
                    float** array_of_arrays;
            };

            void operator<<(const float rhs);
            void operator<<(const std::vector<float>& rhs);
            Proxy2D operator[](const uint32_t index)
            {
                return Proxy2D(array_of_arrays_of_arrays[index]);
            }

        private:
            bool is_cube;
            uint32_t width;
            uint32_t height;
            uint32_t depth;

            bool is_fully_populated;

            // For populating, the order of coordinates from
            // the one changing fastest to the one changing slowest is:
            // x, y, z
            int32_t next_x_to_populate;
            int32_t next_y_to_populate;
            int32_t next_z_to_populate;

            float*** array_of_arrays_of_arrays;
    };
}

#endif
