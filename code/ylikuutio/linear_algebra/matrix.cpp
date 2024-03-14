// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2023 Antti Nuortimo.
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

#include "matrix.hpp"

// Include standard headers
#include <cmath>    // NAN
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cerr
#include <memory>   // std::make_shared, std::shared_ptr
#include <vector>   // std::vector

namespace yli::linear_algebra
{
    Matrix::Matrix(std::size_t height, std::size_t width)
    {
        // constructor.
        this->width = width;
        this->height = height;
        this->array_of_arrays.resize(this->height);

        for (std::size_t i = 0; i < this->height; i++)
        {
            this->array_of_arrays[i].resize(this->width);
        }

        this->next_x_to_populate = 0;
        this->next_y_to_populate = 0;
        this->is_fully_populated = false;

        if (this->width == this->height)
        {
            this->is_square = true;
        }
        else
        {
            this->is_square = false;
        }
    }

    Matrix::Matrix(const yli::linear_algebra::Matrix& old_matrix)
    {
        // copy constructor.
        this->width = old_matrix.width;
        this->height = old_matrix.height;
        this->array_of_arrays.resize(this->height);

        for (std::size_t i = 0; i < this->height; i++)
        {
            this->array_of_arrays[i].resize(this->width);
        }

        this->next_x_to_populate = old_matrix.next_x_to_populate;
        this->next_y_to_populate = old_matrix.next_y_to_populate;
        this->is_fully_populated = old_matrix.is_fully_populated;

        // Copy values from old matrix (deep copy).
        // Don't care whether `old_matrix` is fully populated or not.
        for (std::size_t y = 0; y < this->height; y++)
        {
            // Get the slices of both arrays.
            std::vector<float>& my_array = this->array_of_arrays[y];
            const std::vector<float>& other_array = old_matrix.array_of_arrays[y];

            for (std::size_t x = 0; x < this->width; x++)
            {
                my_array[x] = other_array[x];
            }
        }

        if (this->width == this->height)
        {
            this->is_square = true;
        }
        else
        {
            this->is_square = false;
        }
    }

    bool Matrix::get_is_square() const
    {
        return this->is_square;
    }

    std::size_t Matrix::get_width() const
    {
        return this->width;
    }

    std::size_t Matrix::get_height() const
    {
        return this->height;
    }

    float Matrix::get_value(const std::size_t y, const std::size_t x) const
    {
        return this->array_of_arrays[y][x];
    }

    std::shared_ptr<yli::linear_algebra::Matrix> Matrix::transpose()
    {
        std::shared_ptr<yli::linear_algebra::Matrix> new_matrix = std::make_shared<yli::linear_algebra::Matrix>(this->width, this->height); // Flip width and height.

        for (std::size_t x = 0; x < this->width; x++)
        {
            for (std::size_t y = 0; y < this->height; y++)
            {
                *new_matrix << this->operator[](y).operator[](x);
            }
        }

        return new_matrix;
    }

    float Matrix::det()
    {
        if (!this->is_square)
        {
            // Non-square matrices do not have determinant.
            return NAN;
        }

        switch (this->width)
        {
            case 1:
                // det(scalar) = scalar
                return this->array_of_arrays[0][0];
            case 2:
                //     | a b |
                // det |     | = ad - bc
                //     | c d |
                return this->array_of_arrays[0][0] * this->array_of_arrays[1][1] - this->array_of_arrays[0][1] * this->array_of_arrays[1][0];
            case 3:
                //     | a b c |
                // det | d e f | = aei + bfg + cdh - ceg - bdi - afh
                //     | g h i |
                return this->array_of_arrays[0][0] * this->array_of_arrays[1][1] * this->array_of_arrays[2][2] + // aei +
                    this->array_of_arrays[0][1] * this->array_of_arrays[1][2] * this->array_of_arrays[2][0] +    // bfg +
                    this->array_of_arrays[0][2] * this->array_of_arrays[1][0] * this->array_of_arrays[2][1] -    // cdh -
                    this->array_of_arrays[0][2] * this->array_of_arrays[1][1] * this->array_of_arrays[2][0] -    // ceg -
                    this->array_of_arrays[0][1] * this->array_of_arrays[1][0] * this->array_of_arrays[2][2] -    // bdi -
                    this->array_of_arrays[0][0] * this->array_of_arrays[1][2] * this->array_of_arrays[2][1];     // afh
            default:
                // TODO: implement determinant for larger matrices!
                return NAN;
        }
    }

    void Matrix::operator<<(const float rhs)
    {
        if (this->is_fully_populated)
        {
            // Array is already fully populated. Nothing to do.
            return;
        }

        // First, get the slice.
        std::vector<float>& my_array = this->array_of_arrays[this->next_y_to_populate];

        // Then store the value.
        my_array[this->next_x_to_populate++] = rhs;

        if (this->next_x_to_populate >= this->width)
        {
            this->next_x_to_populate = 0;

            if (++this->next_y_to_populate >= this->height)
            {
                this->is_fully_populated = true;
            }
        }
    }

    void Matrix::operator<<(const std::vector<float>& rhs)
    {
        std::size_t rhs_i = 0;

        while (!this->is_fully_populated && rhs_i < rhs.size())
        {
            // First, get the slice.
            std::vector<float>& my_array = this->array_of_arrays[this->next_y_to_populate];

            // Then store the value.
            my_array[this->next_x_to_populate++] = rhs[rhs_i++];

            if (this->next_x_to_populate >= this->width)
            {
                this->next_x_to_populate = 0;

                if (++this->next_y_to_populate >= this->height)
                {
                    this->is_fully_populated = true;
                }
            }
        }
    }

    bool Matrix::operator==(const yli::linear_algebra::Matrix& rhs) const noexcept
    {
        // compare if matrices are equal.
        if (this->width != rhs.width ||
                this->height != rhs.height)
        {
            // Matrices are not equal, if they have different sizes.
            return false;
        }

        for (std::size_t y = 0; y < this->height; y++)
        {
            // Get the slices of both arrays.
            const std::vector<float>& my_array = this->array_of_arrays[y];
            const std::vector<float>& other_array = rhs.array_of_arrays[y];

            for (std::size_t x = 0; x < this->width; x++)
            {
                if (my_array[x] != other_array[x])
                {
                    // Arrays are not identical.
                    return false;
                }
            }
        }

        // Everything matches. Arrays are identical.
        return true;
    }

    yli::linear_algebra::Matrix& Matrix::operator++()
    {
        for (std::size_t y = 0; y < this->height; y++)
        {
            // Get the slice.
            std::vector<float>& my_array = this->array_of_arrays[y];

            for (std::size_t x = 0; x < this->width; x++)
            {
                my_array[x]++;
            }
        }

        return *this;
    }

    yli::linear_algebra::Matrix Matrix::operator++(const int)
    {
        yli::linear_algebra::Matrix tmp(*this); // Make a copy.
        this->operator++();
        return tmp; // Return old matrix.
    }

    yli::linear_algebra::Matrix& Matrix::operator--()
    {
        for (std::size_t y = 0; y < this->height; y++)
        {
            // Get the slice.
            std::vector<float>& my_array = this->array_of_arrays[y];

            for (std::size_t x = 0; x < this->width; x++)
            {
                my_array[x]--;
            }
        }

        return *this;
    }

    yli::linear_algebra::Matrix Matrix::operator--(const int)
    {
        Matrix tmp(*this); // Make a copy.
        this->operator--();
        return tmp; // Return old matrix.
    }

    yli::linear_algebra::Matrix& Matrix::operator+=(const float rhs)
    {
        for (std::size_t y = 0; y < this->height; y++)
        {
            // Get the slice.
            std::vector<float>& my_array = this->array_of_arrays[y];

            for (std::size_t x = 0; x < this->width; x++)
            {
                my_array[x] += rhs;
            }
        }

        return *this;
    }

    yli::linear_algebra::Matrix& Matrix::operator-=(const float rhs)
    {
        for (std::size_t y = 0; y < this->height; y++)
        {
            // Get the slice.
            std::vector<float>& my_array = this->array_of_arrays[y];

            for (std::size_t x = 0; x < this->width; x++)
            {
                my_array[x] -= rhs;
            }
        }

        return *this;
    }

    yli::linear_algebra::Matrix& Matrix::operator*=(const float rhs)
    {
        for (std::size_t y = 0; y < this->height; y++)
        {
            // Get the slice.
            std::vector<float>& my_array = this->array_of_arrays[y];

            for (std::size_t x = 0; x < this->width; x++)
            {
                my_array[x] *= rhs;
            }
        }

        return *this;
    }

    yli::linear_algebra::Matrix& Matrix::operator/=(const float rhs)
    {
        for (std::size_t y = 0; y < this->height; y++)
        {
            // Get the slice.
            std::vector<float>& my_array = this->array_of_arrays[y];

            for (std::size_t x = 0; x < this->width; x++)
            {
                my_array[x] *= rhs;
            }
        }

        return *this;
    }

    yli::linear_algebra::Matrix& Matrix::operator+=(yli::linear_algebra::Matrix& rhs)
    {
        for (std::size_t y = 0; y < this->height; y++)
        {
            // Get the slices of both arrays.
            std::vector<float>& my_array = this->array_of_arrays[y];
            std::vector<float>& other_array = rhs.array_of_arrays[y];

            for (std::size_t x = 0; x < this->width; x++)
            {
                my_array[x] += other_array[x];
            }
        }

        return *this;
    }

    yli::linear_algebra::Matrix& Matrix::operator-=(yli::linear_algebra::Matrix& rhs)
    {
        for (std::size_t y = 0; y < this->height; y++)
        {
            // Get the slices of both arrays.
            std::vector<float>& my_array = this->array_of_arrays[y];
            std::vector<float>& other_array = rhs.array_of_arrays[y];

            for (std::size_t x = 0; x < this->width; x++)
            {
                my_array[x] -= other_array[x];
            }
        }

        return *this;
    }

    yli::linear_algebra::Matrix operator+(yli::linear_algebra::Matrix& lhs, yli::linear_algebra::Matrix& rhs)
    {
        // Matrix addition.
        if (lhs.height != rhs.height || lhs.width != rhs.width)
        {
            // Matrix dimensions do not match!
            // Matrix addition is not defined.
            // Populate `result_matrix` with NAN to signal error.
            std::cerr << "Matrix dimensions do not match!\n";
            yli::linear_algebra::Matrix result_matrix(1, 1);
            result_matrix << NAN;
            return result_matrix;
        }

        // OK, dimensions match.
        std::size_t target_height = lhs.height;
        std::size_t target_width = lhs.width;
        yli::linear_algebra::Matrix result_matrix(target_height, target_width);

        for (std::size_t y = 0; y < target_height; y++)
        {
            for (std::size_t x = 0; x < target_width; x++)
            {
                result_matrix << lhs.operator[](y).operator[](x) + rhs.operator[](y).operator[](x);
            }
        }

        return result_matrix;
    }

    yli::linear_algebra::Matrix operator-(yli::linear_algebra::Matrix& lhs, yli::linear_algebra::Matrix& rhs)
    {
        // Matrix subtraction.
        if (lhs.height != rhs.height || lhs.width != rhs.width)
        {
            // Matrix dimensions do not match!
            // Matrix addition is not defined.
            // Populate `result_matrix` with NAN to signal error.
            std::cerr << "Matrix dimensions do not match!\n";
            yli::linear_algebra::Matrix result_matrix(1, 1);
            result_matrix << NAN;
            return result_matrix;
        }

        // OK, dimensions match.
        std::size_t target_height = lhs.height;
        std::size_t target_width = lhs.width;
        yli::linear_algebra::Matrix result_matrix(target_height, target_width);

        for (std::size_t y = 0; y < target_height; y++)
        {
            for (std::size_t x = 0; x < target_width; x++)
            {
                result_matrix << lhs.operator[](y).operator[](x) - rhs.operator[](y).operator[](x);
            }
        }

        return result_matrix;
    }

    yli::linear_algebra::Matrix operator*(yli::linear_algebra::Matrix& lhs, yli::linear_algebra::Matrix& rhs)
    {
        // Matrix multiplication.
        if (lhs.width != rhs.height)
        {
            // Matrix dimensions do not match!
            // Matrix multiplication is not defined.
            // Populate `result_matrix` with NAN to signal error.
            std::cerr << "Matrix dimensions do not match!\n";
            yli::linear_algebra::Matrix result_matrix(1, 1);
            result_matrix << NAN;
            return result_matrix;
        }

        // OK, dimensions match.
        std::size_t target_height = lhs.height;
        std::size_t target_width = rhs.width;
        yli::linear_algebra::Matrix result_matrix(target_height, target_width);

        for (std::size_t target_y = 0; target_y < target_height; target_y++)
        {
            for (std::size_t target_x = 0; target_x < target_width; target_x++)
            {
                float target_value = 0.0f;

                for (std::size_t lhs_x = 0, rhs_y = 0; lhs_x < lhs.width && rhs_y < rhs.height; lhs_x++, rhs_y++)
                {
                    // target_value += lhs[target_y][lhs_x] * rhs[rhs_y][target_x];

                    target_value += lhs.operator[](target_y).operator[](lhs_x) * rhs.operator[](rhs_y).operator[](target_x);
                }
                result_matrix << target_value;
            }
        }

        return result_matrix;
    }
}
