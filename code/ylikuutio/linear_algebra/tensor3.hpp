// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2025 Antti Nuortimo.
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

#ifndef YLIKUUTIO_LINEAR_ALGEBRA_TENSOR3_HPP_INCLUDED
#define YLIKUUTIO_LINEAR_ALGEBRA_TENSOR3_HPP_INCLUDED

#include "matrix.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <vector>   // std::vector

namespace yli::linear_algebra
{
    class Tensor3 final
    {
        // `class Tensor3` uses the coordinate order x, y, z:
        // x = 0 is the leftmost slice.
        // y = 0 is the uppermost slice
        // z = 0 is the front slice.

        public:
            Tensor3(std::size_t width, std::size_t height, std::size_t depth);

            ~Tensor3() = default;

            // copy constructor.
            Tensor3(const yli::linear_algebra::Tensor3& old_tensor3) = default;

            explicit Tensor3(const yli::linear_algebra::Matrix& old_matrix);

            // Inspired by http://stackoverflow.com/questions/6969881/operator-overload/6969904#6969904
            class Proxy2D
            {
                public:
                    explicit Proxy2D(const std::vector<std::vector<float>>& array_of_arrays)
                        : array_of_arrays(array_of_arrays)
                    {
                    }

                    class Proxy
                    {
                        public:
                            explicit Proxy(std::vector<float>& proxy_array)
                                : proxy_array(proxy_array)
                            {
                            }

                            float& operator[](const std::size_t index)
                            {
                                return proxy_array[index];
                            }

                        private:
                            std::vector<float>& proxy_array;
                    };

                    Proxy operator[](const std::size_t index)
                    {
                        return Proxy(array_of_arrays[index]);
                    }

                private:
                    std::vector<std::vector<float>> array_of_arrays;
            };

            void operator<<(const float rhs);
            void operator<<(const std::vector<float>& rhs);
            bool operator==(const yli::linear_algebra::Tensor3& rhs) const noexcept;
            bool operator!=(const yli::linear_algebra::Tensor3& rhs) const = default;
            yli::linear_algebra::Tensor3& operator=(const yli::linear_algebra::Tensor3& rhs) = default;
            Proxy2D operator[](const std::size_t index)
            {
                return Proxy2D(this->array_of_arrays_of_arrays[index]);
            }

            bool is_cube;
            std::size_t width;
            std::size_t height;
            std::size_t depth;

        private:
            bool is_fully_populated;

            // For populating, the order of coordinates from
            // the one changing fastest to the one changing slowest is:
            // x, y, z
            std::size_t next_x_to_populate;
            std::size_t next_y_to_populate;
            std::size_t next_z_to_populate;

            std::vector<std::vector<std::vector<float>>> array_of_arrays_of_arrays;
    };
}

#endif
