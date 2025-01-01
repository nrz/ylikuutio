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

#include "gtest/gtest.h"
#include "code/ylikuutio/linear_algebra/matrix.hpp"
#include "code/ylikuutio/linear_algebra/matrix_functions.hpp"
#include "code/ylikuutio/linear_algebra/tensor3.hpp"
#include "code/ylikuutio/linear_algebra/vector_functions.hpp"

// Include standard headers
#include <vector>   // std::vector

TEST(matrices_must_function_as_expected, matrices)
{
    // populate matrices and matrix equality.

    yli::linear_algebra::Matrix identity3x3(3, 3);
    ASSERT_TRUE(identity3x3.get_is_square());
    ASSERT_EQ(identity3x3.get_height(), 3);
    ASSERT_EQ(identity3x3.get_height(), 3);
    identity3x3 << 1; identity3x3 << 0; identity3x3 << 0;
    identity3x3 << 0; identity3x3 << 1; identity3x3 << 0;
    identity3x3 << 0; identity3x3 << 0; identity3x3 << 1;

    yli::linear_algebra::Matrix identity3x3_populate_with_vector(3, 3);
    identity3x3_populate_with_vector << std::vector<float> {
            1, 0, 0,
            0, 1, 0,
            0, 0, 1 };
    ASSERT_TRUE(identity3x3 == identity3x3_populate_with_vector);
    ASSERT_FALSE(identity3x3 != identity3x3_populate_with_vector);

    ASSERT_TRUE(identity3x3_populate_with_vector == identity3x3);
    ASSERT_FALSE(identity3x3_populate_with_vector != identity3x3);

    yli::linear_algebra::Matrix zeros3x3(3, 3);
    zeros3x3 << 0; zeros3x3 << 0; zeros3x3 << 0;
    zeros3x3 << 0; zeros3x3 << 0; zeros3x3 << 0;
    zeros3x3 << 0; zeros3x3 << 0; zeros3x3 << 0;

    yli::linear_algebra::Matrix zeros3x3_populate_with_vector(3, 3);
    zeros3x3_populate_with_vector << std::vector<float> {
            0, 0, 0,
            0, 0, 0,
            0, 0, 0 };
    ASSERT_TRUE(zeros3x3 == zeros3x3_populate_with_vector);
    ASSERT_FALSE(zeros3x3 != zeros3x3_populate_with_vector);

    ASSERT_TRUE(zeros3x3_populate_with_vector == zeros3x3);
    ASSERT_FALSE(zeros3x3_populate_with_vector != zeros3x3);

    yli::linear_algebra::Matrix ones3x3(3, 3);
    ones3x3 << 1; ones3x3 << 1; ones3x3 << 1;
    ones3x3 << 1; ones3x3 << 1; ones3x3 << 1;
    ones3x3 << 1; ones3x3 << 1; ones3x3 << 1;

    yli::linear_algebra::Matrix ones3x3_populate_with_vector(3, 3);
    ones3x3_populate_with_vector << std::vector<float> {
            1, 1, 1,
            1, 1, 1,
            1, 1, 1 };
    ASSERT_TRUE(ones3x3 == ones3x3_populate_with_vector);
    ASSERT_FALSE(ones3x3 != ones3x3_populate_with_vector);

    ASSERT_TRUE(ones3x3_populate_with_vector == ones3x3);
    ASSERT_FALSE(ones3x3_populate_with_vector != ones3x3);

    yli::linear_algebra::Matrix magic3x3(3, 3);
    magic3x3 << 8; magic3x3 << 1; magic3x3 << 6;
    magic3x3 << 3; magic3x3 << 5; magic3x3 << 7;
    magic3x3 << 4; magic3x3 << 9; magic3x3 << 2;

    yli::linear_algebra::Matrix magic3x3_populate_with_vector(3, 3);
    magic3x3_populate_with_vector << std::vector<float> {
            8, 1, 6,
            3, 5, 7,
            4, 9, 2 };
    ASSERT_TRUE(magic3x3 == magic3x3_populate_with_vector);
    ASSERT_FALSE(magic3x3 != magic3x3_populate_with_vector);

    ASSERT_TRUE(magic3x3_populate_with_vector == magic3x3);
    ASSERT_FALSE(magic3x3_populate_with_vector != magic3x3);

    ASSERT_EQ(magic3x3[0][0], 8);
    ASSERT_EQ(magic3x3[1][0], 3);
    ASSERT_EQ(magic3x3[2][0], 4);
    ASSERT_EQ(magic3x3[0][1], 1);
    ASSERT_EQ(magic3x3[1][1], 5);
    ASSERT_EQ(magic3x3[2][1], 9);
    ASSERT_EQ(magic3x3[0][2], 6);
    ASSERT_EQ(magic3x3[1][2], 7);
    ASSERT_EQ(magic3x3[2][2], 2);

    // transpose.

    yli::linear_algebra::Matrix magic3x3_transposed(magic3x3.transpose());
    ASSERT_EQ(magic3x3_transposed[0][0], 8);
    ASSERT_EQ(magic3x3_transposed[1][0], 1);
    ASSERT_EQ(magic3x3_transposed[2][0], 6);
    ASSERT_EQ(magic3x3_transposed[0][1], 3);
    ASSERT_EQ(magic3x3_transposed[1][1], 5);
    ASSERT_EQ(magic3x3_transposed[2][1], 7);
    ASSERT_EQ(magic3x3_transposed[0][2], 4);
    ASSERT_EQ(magic3x3_transposed[1][2], 9);
    ASSERT_EQ(magic3x3_transposed[2][2], 2);

    // determinants.

    int32_t det_identity3x3 = identity3x3.det();
    ASSERT_EQ(det_identity3x3, 1);

    int32_t det_zeros3x3 = zeros3x3.det();
    ASSERT_EQ(det_zeros3x3, 0);

    int32_t det_ones3x3 = ones3x3.det();
    ASSERT_EQ(det_ones3x3, 0);

    int32_t det_magic3x3 = magic3x3.det();
    ASSERT_EQ(det_magic3x3, -360);

    // matrix equality, increment, and decrement.

    ASSERT_FALSE(zeros3x3 == ones3x3);
    ASSERT_TRUE(zeros3x3 != ones3x3);
    ASSERT_FALSE(ones3x3 == zeros3x3);
    ASSERT_TRUE(ones3x3 != zeros3x3);
    zeros3x3++;
    ASSERT_TRUE(zeros3x3 == ones3x3);
    ASSERT_FALSE(zeros3x3 != ones3x3);
    ASSERT_TRUE(ones3x3 == zeros3x3);
    ASSERT_FALSE(ones3x3 != zeros3x3 );
    zeros3x3--;
    ASSERT_FALSE(zeros3x3 == ones3x3);
    ASSERT_TRUE(zeros3x3 != ones3x3);
    ASSERT_FALSE(ones3x3 == zeros3x3);
    ASSERT_TRUE(ones3x3 != zeros3x3);
    ones3x3--;
    ASSERT_TRUE(zeros3x3 == ones3x3);
    ASSERT_FALSE(zeros3x3 != ones3x3);
    ASSERT_TRUE(ones3x3 == zeros3x3);
    ASSERT_FALSE(ones3x3 != zeros3x3);
    ones3x3++;
    ASSERT_FALSE(zeros3x3 == ones3x3);
    ASSERT_TRUE(zeros3x3 != ones3x3);
    ASSERT_FALSE(ones3x3 == zeros3x3);
    ASSERT_TRUE(ones3x3 != zeros3x3);

    // copy constructor.

    yli::linear_algebra::Matrix magic3x3_plus_ones3x3_with_augmented_assignment(magic3x3);
    ASSERT_EQ(magic3x3_plus_ones3x3_with_augmented_assignment[0][0], 8);
    ASSERT_EQ(magic3x3_plus_ones3x3_with_augmented_assignment[1][0], 3);
    ASSERT_EQ(magic3x3_plus_ones3x3_with_augmented_assignment[2][0], 4);
    ASSERT_EQ(magic3x3_plus_ones3x3_with_augmented_assignment[0][1], 1);
    ASSERT_EQ(magic3x3_plus_ones3x3_with_augmented_assignment[1][1], 5);
    ASSERT_EQ(magic3x3_plus_ones3x3_with_augmented_assignment[2][1], 9);
    ASSERT_EQ(magic3x3_plus_ones3x3_with_augmented_assignment[0][2], 6);
    ASSERT_EQ(magic3x3_plus_ones3x3_with_augmented_assignment[1][2], 7);
    ASSERT_EQ(magic3x3_plus_ones3x3_with_augmented_assignment[2][2], 2);

    ASSERT_EQ(magic3x3[0][0], 8);
    ASSERT_EQ(magic3x3[1][0], 3);
    ASSERT_EQ(magic3x3[2][0], 4);
    ASSERT_EQ(magic3x3[0][1], 1);
    ASSERT_EQ(magic3x3[1][1], 5);
    ASSERT_EQ(magic3x3[2][1], 9);
    ASSERT_EQ(magic3x3[0][2], 6);
    ASSERT_EQ(magic3x3[1][2], 7);
    ASSERT_EQ(magic3x3[2][2], 2);

    // copy constructor.

    yli::linear_algebra::Matrix magic3x3_plus_magic3x3_with_augmented_assignment(magic3x3);
    ASSERT_EQ(magic3x3_plus_magic3x3_with_augmented_assignment[0][0], 8);
    ASSERT_EQ(magic3x3_plus_magic3x3_with_augmented_assignment[1][0], 3);
    ASSERT_EQ(magic3x3_plus_magic3x3_with_augmented_assignment[2][0], 4);
    ASSERT_EQ(magic3x3_plus_magic3x3_with_augmented_assignment[0][1], 1);
    ASSERT_EQ(magic3x3_plus_magic3x3_with_augmented_assignment[1][1], 5);
    ASSERT_EQ(magic3x3_plus_magic3x3_with_augmented_assignment[2][1], 9);
    ASSERT_EQ(magic3x3_plus_magic3x3_with_augmented_assignment[0][2], 6);
    ASSERT_EQ(magic3x3_plus_magic3x3_with_augmented_assignment[1][2], 7);
    ASSERT_EQ(magic3x3_plus_magic3x3_with_augmented_assignment[2][2], 2);

    ASSERT_EQ(magic3x3[0][0], 8);
    ASSERT_EQ(magic3x3[1][0], 3);
    ASSERT_EQ(magic3x3[2][0], 4);
    ASSERT_EQ(magic3x3[0][1], 1);
    ASSERT_EQ(magic3x3[1][1], 5);
    ASSERT_EQ(magic3x3[2][1], 9);
    ASSERT_EQ(magic3x3[0][2], 6);
    ASSERT_EQ(magic3x3[1][2], 7);
    ASSERT_EQ(magic3x3[2][2], 2);

    // matrix addition (augmented assignment).

    magic3x3_plus_ones3x3_with_augmented_assignment += ones3x3;
    ASSERT_EQ(magic3x3_plus_ones3x3_with_augmented_assignment[0][0], 9);
    ASSERT_EQ(magic3x3_plus_ones3x3_with_augmented_assignment[1][0], 4);
    ASSERT_EQ(magic3x3_plus_ones3x3_with_augmented_assignment[2][0], 5);
    ASSERT_EQ(magic3x3_plus_ones3x3_with_augmented_assignment[0][1], 2);
    ASSERT_EQ(magic3x3_plus_ones3x3_with_augmented_assignment[1][1], 6);
    ASSERT_EQ(magic3x3_plus_ones3x3_with_augmented_assignment[2][1], 10);
    ASSERT_EQ(magic3x3_plus_ones3x3_with_augmented_assignment[0][2], 7);
    ASSERT_EQ(magic3x3_plus_ones3x3_with_augmented_assignment[1][2], 8);
    ASSERT_EQ(magic3x3_plus_ones3x3_with_augmented_assignment[2][2], 3);

    // matrix addition (augmented assignment).

    magic3x3_plus_magic3x3_with_augmented_assignment += magic3x3;
    ASSERT_EQ(magic3x3_plus_magic3x3_with_augmented_assignment[0][0], 16);
    ASSERT_EQ(magic3x3_plus_magic3x3_with_augmented_assignment[1][0], 6);
    ASSERT_EQ(magic3x3_plus_magic3x3_with_augmented_assignment[2][0], 8);
    ASSERT_EQ(magic3x3_plus_magic3x3_with_augmented_assignment[0][1], 2);
    ASSERT_EQ(magic3x3_plus_magic3x3_with_augmented_assignment[1][1], 10);
    ASSERT_EQ(magic3x3_plus_magic3x3_with_augmented_assignment[2][1], 18);
    ASSERT_EQ(magic3x3_plus_magic3x3_with_augmented_assignment[0][2], 12);
    ASSERT_EQ(magic3x3_plus_magic3x3_with_augmented_assignment[1][2], 14);
    ASSERT_EQ(magic3x3_plus_magic3x3_with_augmented_assignment[2][2], 4);

    ASSERT_EQ(magic3x3[0][0], 8);
    ASSERT_EQ(magic3x3[1][0], 3);
    ASSERT_EQ(magic3x3[2][0], 4);
    ASSERT_EQ(magic3x3[0][1], 1);
    ASSERT_EQ(magic3x3[1][1], 5);
    ASSERT_EQ(magic3x3[2][1], 9);
    ASSERT_EQ(magic3x3[0][2], 6);
    ASSERT_EQ(magic3x3[1][2], 7);
    ASSERT_EQ(magic3x3[2][2], 2);

    // matrix addition (binary addition).

    yli::linear_algebra::Matrix magic3x3_plus_ones3x3(3, 3);
    magic3x3_plus_ones3x3 = magic3x3 + ones3x3;
    ASSERT_EQ(magic3x3_plus_ones3x3[0][0], 9);
    ASSERT_EQ(magic3x3_plus_ones3x3[1][0], 4);
    ASSERT_EQ(magic3x3_plus_ones3x3[2][0], 5);
    ASSERT_EQ(magic3x3_plus_ones3x3[0][1], 2);
    ASSERT_EQ(magic3x3_plus_ones3x3[1][1], 6);
    ASSERT_EQ(magic3x3_plus_ones3x3[2][1], 10);
    ASSERT_EQ(magic3x3_plus_ones3x3[0][2], 7);
    ASSERT_EQ(magic3x3_plus_ones3x3[1][2], 8);
    ASSERT_EQ(magic3x3_plus_ones3x3[2][2], 3);

    ASSERT_EQ(magic3x3[0][0], 8);
    ASSERT_EQ(magic3x3[1][0], 3);
    ASSERT_EQ(magic3x3[2][0], 4);
    ASSERT_EQ(magic3x3[0][1], 1);
    ASSERT_EQ(magic3x3[1][1], 5);
    ASSERT_EQ(magic3x3[2][1], 9);
    ASSERT_EQ(magic3x3[0][2], 6);
    ASSERT_EQ(magic3x3[1][2], 7);
    ASSERT_EQ(magic3x3[2][2], 2);

    // matrix addition (binary addition).

    yli::linear_algebra::Matrix magic3x3_plus_magic3x3(3, 3);
    magic3x3_plus_magic3x3 = magic3x3 + magic3x3;
    ASSERT_EQ(magic3x3_plus_magic3x3[0][0], 16);
    ASSERT_EQ(magic3x3_plus_magic3x3[1][0], 6);
    ASSERT_EQ(magic3x3_plus_magic3x3[2][0], 8);
    ASSERT_EQ(magic3x3_plus_magic3x3[0][1], 2);
    ASSERT_EQ(magic3x3_plus_magic3x3[1][1], 10);
    ASSERT_EQ(magic3x3_plus_magic3x3[2][1], 18);
    ASSERT_EQ(magic3x3_plus_magic3x3[0][2], 12);
    ASSERT_EQ(magic3x3_plus_magic3x3[1][2], 14);
    ASSERT_EQ(magic3x3_plus_magic3x3[2][2], 4);

    ASSERT_EQ(magic3x3[0][0], 8);
    ASSERT_EQ(magic3x3[1][0], 3);
    ASSERT_EQ(magic3x3[2][0], 4);
    ASSERT_EQ(magic3x3[0][1], 1);
    ASSERT_EQ(magic3x3[1][1], 5);
    ASSERT_EQ(magic3x3[2][1], 9);
    ASSERT_EQ(magic3x3[0][2], 6);
    ASSERT_EQ(magic3x3[1][2], 7);
    ASSERT_EQ(magic3x3[2][2], 2);

    // matrix multiplication.

    yli::linear_algebra::Matrix ones3x3squared(3, 3);
    ones3x3squared = ones3x3 * ones3x3;
    ASSERT_EQ(ones3x3squared[0][0], 3);
    ASSERT_EQ(ones3x3squared[1][0], 3);
    ASSERT_EQ(ones3x3squared[2][0], 3);
    ASSERT_EQ(ones3x3squared[0][1], 3);
    ASSERT_EQ(ones3x3squared[1][1], 3);
    ASSERT_EQ(ones3x3squared[2][1], 3);
    ASSERT_EQ(ones3x3squared[0][2], 3);
    ASSERT_EQ(ones3x3squared[1][2], 3);
    ASSERT_EQ(ones3x3squared[2][2], 3);

    // matrix multiplication.

    yli::linear_algebra::Matrix magic3x3squared(3, 3);
    magic3x3squared = magic3x3 * magic3x3;
    ASSERT_EQ(magic3x3squared[0][0], 91);
    ASSERT_EQ(magic3x3squared[1][0], 67);
    ASSERT_EQ(magic3x3squared[2][0], 67);
    ASSERT_EQ(magic3x3squared[0][1], 67);
    ASSERT_EQ(magic3x3squared[1][1], 91);
    ASSERT_EQ(magic3x3squared[2][1], 67);
    ASSERT_EQ(magic3x3squared[0][2], 67);
    ASSERT_EQ(magic3x3squared[1][2], 67);
    ASSERT_EQ(magic3x3squared[2][2], 91);

    ASSERT_EQ(magic3x3[0][0], 8);
    ASSERT_EQ(magic3x3[1][0], 3);
    ASSERT_EQ(magic3x3[2][0], 4);
    ASSERT_EQ(magic3x3[0][1], 1);
    ASSERT_EQ(magic3x3[1][1], 5);
    ASSERT_EQ(magic3x3[2][1], 9);
    ASSERT_EQ(magic3x3[0][2], 6);
    ASSERT_EQ(magic3x3[1][2], 7);
    ASSERT_EQ(magic3x3[2][2], 2);

    // matrix transpose.
    yli::linear_algebra::Matrix magic3x3transposed = magic3x3.transpose();
    ASSERT_EQ(magic3x3transposed[0][0], 8);
    ASSERT_EQ(magic3x3transposed[1][0], 1);
    ASSERT_EQ(magic3x3transposed[2][0], 6);
    ASSERT_EQ(magic3x3transposed[0][1], 3);
    ASSERT_EQ(magic3x3transposed[1][1], 5);
    ASSERT_EQ(magic3x3transposed[2][1], 7);
    ASSERT_EQ(magic3x3transposed[0][2], 4);
    ASSERT_EQ(magic3x3transposed[1][2], 9);
    ASSERT_EQ(magic3x3transposed[2][2], 2);

    ASSERT_EQ(magic3x3[0][0], 8);
    ASSERT_EQ(magic3x3[1][0], 3);
    ASSERT_EQ(magic3x3[2][0], 4);
    ASSERT_EQ(magic3x3[0][1], 1);
    ASSERT_EQ(magic3x3[1][1], 5);
    ASSERT_EQ(magic3x3[2][1], 9);
    ASSERT_EQ(magic3x3[0][2], 6);
    ASSERT_EQ(magic3x3[1][2], 7);
    ASSERT_EQ(magic3x3[2][2], 2);

    // matrix concatenation.

    // use `Matrix(yli::linear_algebra::Matrix& old_matrix)`.
    yli::linear_algebra::Matrix magic3x3_above_magic3x3_transposed_below(cat(1, magic3x3, magic3x3_transposed));
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below[0][0], 8);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below[1][0], 3);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below[2][0], 4);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below[3][0], 8);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below[4][0], 1);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below[5][0], 6);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below[0][1], 1);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below[1][1], 5);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below[2][1], 9);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below[3][1], 3);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below[4][1], 5);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below[5][1], 7);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below[0][2], 6);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below[1][2], 7);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below[2][2], 2);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below[3][2], 4);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below[4][2], 9);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below[5][2], 2);

    ASSERT_EQ(magic3x3[0][0], 8);
    ASSERT_EQ(magic3x3[1][0], 3);
    ASSERT_EQ(magic3x3[2][0], 4);
    ASSERT_EQ(magic3x3[0][1], 1);
    ASSERT_EQ(magic3x3[1][1], 5);
    ASSERT_EQ(magic3x3[2][1], 9);
    ASSERT_EQ(magic3x3[0][2], 6);
    ASSERT_EQ(magic3x3[1][2], 7);
    ASSERT_EQ(magic3x3[2][2], 2);

    // matrix concatenation.

    yli::linear_algebra::Matrix magic3x3_left_magic3x3_transposed_right(cat(2, magic3x3, magic3x3_transposed));
    ASSERT_EQ(magic3x3_left_magic3x3_transposed_right[0][0], 8);
    ASSERT_EQ(magic3x3_left_magic3x3_transposed_right[1][0], 3);
    ASSERT_EQ(magic3x3_left_magic3x3_transposed_right[2][0], 4);
    ASSERT_EQ(magic3x3_left_magic3x3_transposed_right[0][1], 1);
    ASSERT_EQ(magic3x3_left_magic3x3_transposed_right[1][1], 5);
    ASSERT_EQ(magic3x3_left_magic3x3_transposed_right[2][1], 9);
    ASSERT_EQ(magic3x3_left_magic3x3_transposed_right[0][2], 6);
    ASSERT_EQ(magic3x3_left_magic3x3_transposed_right[1][2], 7);
    ASSERT_EQ(magic3x3_left_magic3x3_transposed_right[2][2], 2);
    ASSERT_EQ(magic3x3_left_magic3x3_transposed_right[0][3], 8);
    ASSERT_EQ(magic3x3_left_magic3x3_transposed_right[1][3], 1);
    ASSERT_EQ(magic3x3_left_magic3x3_transposed_right[2][3], 6);
    ASSERT_EQ(magic3x3_left_magic3x3_transposed_right[0][4], 3);
    ASSERT_EQ(magic3x3_left_magic3x3_transposed_right[1][4], 5);
    ASSERT_EQ(magic3x3_left_magic3x3_transposed_right[2][4], 7);
    ASSERT_EQ(magic3x3_left_magic3x3_transposed_right[0][5], 4);
    ASSERT_EQ(magic3x3_left_magic3x3_transposed_right[1][5], 9);
    ASSERT_EQ(magic3x3_left_magic3x3_transposed_right[2][5], 2);

    ASSERT_EQ(magic3x3[0][0], 8);
    ASSERT_EQ(magic3x3[1][0], 3);
    ASSERT_EQ(magic3x3[2][0], 4);
    ASSERT_EQ(magic3x3[0][1], 1);
    ASSERT_EQ(magic3x3[1][1], 5);
    ASSERT_EQ(magic3x3[2][1], 9);
    ASSERT_EQ(magic3x3[0][2], 6);
    ASSERT_EQ(magic3x3[1][2], 7);
    ASSERT_EQ(magic3x3[2][2], 2);
}

TEST(tensors_must_function_as_expected, tensors)
{
    // populate tensors and tensor equality.

    yli::linear_algebra::Tensor3 some_tensor3x3x3(3, 3, 3);
    some_tensor3x3x3 << 1; some_tensor3x3x3 << 2; some_tensor3x3x3 << 3;
    some_tensor3x3x3 << 4; some_tensor3x3x3 << 5; some_tensor3x3x3 << 6;
    some_tensor3x3x3 << 7; some_tensor3x3x3 << 8; some_tensor3x3x3 << 9;

    some_tensor3x3x3 << 10; some_tensor3x3x3 << 11; some_tensor3x3x3 << 12;
    some_tensor3x3x3 << 13; some_tensor3x3x3 << 14; some_tensor3x3x3 << 15;
    some_tensor3x3x3 << 16; some_tensor3x3x3 << 17; some_tensor3x3x3 << 18;

    some_tensor3x3x3 << 19; some_tensor3x3x3 << 20; some_tensor3x3x3 << 21;
    some_tensor3x3x3 << 22; some_tensor3x3x3 << 23; some_tensor3x3x3 << 24;
    some_tensor3x3x3 << 25; some_tensor3x3x3 << 26; some_tensor3x3x3 << 27;

    ASSERT_EQ(some_tensor3x3x3[0][0][0], 1);
    ASSERT_EQ(some_tensor3x3x3[0][1][0], 4);
    ASSERT_EQ(some_tensor3x3x3[0][2][0], 7);

    ASSERT_EQ(some_tensor3x3x3[1][0][0], 2);
    ASSERT_EQ(some_tensor3x3x3[1][1][0], 5);
    ASSERT_EQ(some_tensor3x3x3[1][2][0], 8);

    ASSERT_EQ(some_tensor3x3x3[2][0][0], 3);
    ASSERT_EQ(some_tensor3x3x3[2][1][0], 6);
    ASSERT_EQ(some_tensor3x3x3[2][2][0], 9);

    ASSERT_EQ(some_tensor3x3x3[0][0][1], 10);
    ASSERT_EQ(some_tensor3x3x3[0][1][1], 13);
    ASSERT_EQ(some_tensor3x3x3[0][2][1], 16);

    ASSERT_EQ(some_tensor3x3x3[1][0][1], 11);
    ASSERT_EQ(some_tensor3x3x3[1][1][1], 14);
    ASSERT_EQ(some_tensor3x3x3[1][2][1], 17);

    ASSERT_EQ(some_tensor3x3x3[2][0][1], 12);
    ASSERT_EQ(some_tensor3x3x3[2][1][1], 15);
    ASSERT_EQ(some_tensor3x3x3[2][2][1], 18);

    ASSERT_EQ(some_tensor3x3x3[0][0][2], 19);
    ASSERT_EQ(some_tensor3x3x3[0][1][2], 22);
    ASSERT_EQ(some_tensor3x3x3[0][2][2], 25);

    ASSERT_EQ(some_tensor3x3x3[1][0][2], 20);
    ASSERT_EQ(some_tensor3x3x3[1][1][2], 23);
    ASSERT_EQ(some_tensor3x3x3[1][2][2], 26);

    ASSERT_EQ(some_tensor3x3x3[2][0][2], 21);
    ASSERT_EQ(some_tensor3x3x3[2][1][2], 24);
    ASSERT_EQ(some_tensor3x3x3[2][2][2], 27);

    yli::linear_algebra::Tensor3 some_tensor3x3x3_populate_with_vector(3, 3, 3);
    some_tensor3x3x3_populate_with_vector << std::vector<float> {
        1, 2, 3,
        4, 5, 6,
        7, 8, 9,

        10, 11, 12,
        13, 14, 15,
        16, 17, 18,

        19, 20, 21,
        22, 23, 24,
        25, 26, 27 };
    ASSERT_TRUE(some_tensor3x3x3 == some_tensor3x3x3_populate_with_vector);
    ASSERT_FALSE(some_tensor3x3x3 != some_tensor3x3x3_populate_with_vector);

    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[0][0][0], 1);
    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[0][1][0], 4);
    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[0][2][0], 7);

    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[1][0][0], 2);
    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[1][1][0], 5);
    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[1][2][0], 8);

    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[2][0][0], 3);
    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[2][1][0], 6);
    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[2][2][0], 9);

    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[0][0][1], 10);
    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[0][1][1], 13);
    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[0][2][1], 16);

    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[1][0][1], 11);
    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[1][1][1], 14);
    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[1][2][1], 17);

    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[2][0][1], 12);
    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[2][1][1], 15);
    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[2][2][1], 18);

    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[0][0][2], 19);
    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[0][1][2], 22);
    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[0][2][2], 25);

    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[1][0][2], 20);
    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[1][1][2], 23);
    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[1][2][2], 26);

    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[2][0][2], 21);
    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[2][1][2], 24);
    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[2][2][2], 27);

    // copy constructor.

    yli::linear_algebra::Tensor3 copy_of_some_tensor3x3x3(some_tensor3x3x3);

    ASSERT_TRUE(some_tensor3x3x3 == copy_of_some_tensor3x3x3);
    ASSERT_FALSE(some_tensor3x3x3 != copy_of_some_tensor3x3x3);

    ASSERT_TRUE(copy_of_some_tensor3x3x3 == some_tensor3x3x3);
    ASSERT_FALSE(copy_of_some_tensor3x3x3 != some_tensor3x3x3);

    ASSERT_EQ(copy_of_some_tensor3x3x3[0][0][0], 1);
    ASSERT_EQ(copy_of_some_tensor3x3x3[0][1][0], 4);
    ASSERT_EQ(copy_of_some_tensor3x3x3[0][2][0], 7);

    ASSERT_EQ(copy_of_some_tensor3x3x3[1][0][0], 2);
    ASSERT_EQ(copy_of_some_tensor3x3x3[1][1][0], 5);
    ASSERT_EQ(copy_of_some_tensor3x3x3[1][2][0], 8);

    ASSERT_EQ(copy_of_some_tensor3x3x3[2][0][0], 3);
    ASSERT_EQ(copy_of_some_tensor3x3x3[2][1][0], 6);
    ASSERT_EQ(copy_of_some_tensor3x3x3[2][2][0], 9);

    ASSERT_EQ(copy_of_some_tensor3x3x3[0][0][1], 10);
    ASSERT_EQ(copy_of_some_tensor3x3x3[0][1][1], 13);
    ASSERT_EQ(copy_of_some_tensor3x3x3[0][2][1], 16);

    ASSERT_EQ(copy_of_some_tensor3x3x3[1][0][1], 11);
    ASSERT_EQ(copy_of_some_tensor3x3x3[1][1][1], 14);
    ASSERT_EQ(copy_of_some_tensor3x3x3[1][2][1], 17);

    ASSERT_EQ(copy_of_some_tensor3x3x3[2][0][1], 12);
    ASSERT_EQ(copy_of_some_tensor3x3x3[2][1][1], 15);
    ASSERT_EQ(copy_of_some_tensor3x3x3[2][2][1], 18);

    ASSERT_EQ(copy_of_some_tensor3x3x3[0][0][2], 19);
    ASSERT_EQ(copy_of_some_tensor3x3x3[0][1][2], 22);
    ASSERT_EQ(copy_of_some_tensor3x3x3[0][2][2], 25);

    ASSERT_EQ(copy_of_some_tensor3x3x3[1][0][2], 20);
    ASSERT_EQ(copy_of_some_tensor3x3x3[1][1][2], 23);
    ASSERT_EQ(copy_of_some_tensor3x3x3[1][2][2], 26);

    ASSERT_EQ(copy_of_some_tensor3x3x3[2][0][2], 21);
    ASSERT_EQ(copy_of_some_tensor3x3x3[2][1][2], 24);
    ASSERT_EQ(copy_of_some_tensor3x3x3[2][2][2], 27);

    ASSERT_TRUE(some_tensor3x3x3 == copy_of_some_tensor3x3x3);
    ASSERT_FALSE(some_tensor3x3x3 != copy_of_some_tensor3x3x3);

    ASSERT_TRUE(copy_of_some_tensor3x3x3 == some_tensor3x3x3);
    ASSERT_FALSE(copy_of_some_tensor3x3x3 != some_tensor3x3x3);

    ASSERT_EQ(some_tensor3x3x3[0][0][0], 1);
    ASSERT_EQ(some_tensor3x3x3[0][1][0], 4);
    ASSERT_EQ(some_tensor3x3x3[0][2][0], 7);

    ASSERT_EQ(some_tensor3x3x3[1][0][0], 2);
    ASSERT_EQ(some_tensor3x3x3[1][1][0], 5);
    ASSERT_EQ(some_tensor3x3x3[1][2][0], 8);

    ASSERT_EQ(some_tensor3x3x3[2][0][0], 3);
    ASSERT_EQ(some_tensor3x3x3[2][1][0], 6);
    ASSERT_EQ(some_tensor3x3x3[2][2][0], 9);

    ASSERT_EQ(some_tensor3x3x3[0][0][1], 10);
    ASSERT_EQ(some_tensor3x3x3[0][1][1], 13);
    ASSERT_EQ(some_tensor3x3x3[0][2][1], 16);

    ASSERT_EQ(some_tensor3x3x3[1][0][1], 11);
    ASSERT_EQ(some_tensor3x3x3[1][1][1], 14);
    ASSERT_EQ(some_tensor3x3x3[1][2][1], 17);

    ASSERT_EQ(some_tensor3x3x3[2][0][1], 12);
    ASSERT_EQ(some_tensor3x3x3[2][1][1], 15);
    ASSERT_EQ(some_tensor3x3x3[2][2][1], 18);

    ASSERT_EQ(some_tensor3x3x3[0][0][2], 19);
    ASSERT_EQ(some_tensor3x3x3[0][1][2], 22);
    ASSERT_EQ(some_tensor3x3x3[0][2][2], 25);

    ASSERT_EQ(some_tensor3x3x3[1][0][2], 20);
    ASSERT_EQ(some_tensor3x3x3[1][1][2], 23);
    ASSERT_EQ(some_tensor3x3x3[1][2][2], 26);

    ASSERT_EQ(some_tensor3x3x3[2][0][2], 21);
    ASSERT_EQ(some_tensor3x3x3[2][1][2], 24);
    ASSERT_EQ(some_tensor3x3x3[2][2][2], 27);
}

TEST(insert_elements_must_function_as_expected, char_data_vector_is_empty_char_left_filler_vector_is_empty_char_right_filler_vector_is_empty)
{
    std::vector<char> data_vector;
    std::vector<char> left_filler_vector;
    std::vector<char> right_filler_vector;

    std::vector<char> result_vector = yli::linear_algebra::insert_elements(data_vector, left_filler_vector, right_filler_vector);
    ASSERT_TRUE(result_vector.empty());
}

TEST(insert_elements_must_function_as_expected, char_data_vector_is_empty_char_left_filler_vector_is_1_char_char_right_filler_vector_is_empty)
{
    std::vector<char> data_vector;
    std::vector<char> left_filler_vector { 'a' };
    std::vector<char> right_filler_vector;

    std::vector<char> result_vector = yli::linear_algebra::insert_elements(data_vector, left_filler_vector, right_filler_vector);
    ASSERT_TRUE(result_vector.empty());
}

TEST(insert_elements_must_function_as_expected, char_data_vector_is_empty_char_left_filler_vector_is_empty_char_right_filler_vector_is_1_char)
{
    std::vector<char> data_vector;
    std::vector<char> left_filler_vector;
    std::vector<char> right_filler_vector { 'a' };

    std::vector<char> result_vector = yli::linear_algebra::insert_elements(data_vector, left_filler_vector, right_filler_vector);
    ASSERT_TRUE(result_vector.empty());
}

TEST(insert_elements_must_function_as_expected, char_data_vector_is_empty_char_left_filler_vector_is_1_char_char_right_filler_vector_is_1_char)
{
    std::vector<char> data_vector;
    std::vector<char> left_filler_vector { 'a' };
    std::vector<char> right_filler_vector { 'b' };

    std::vector<char> result_vector = yli::linear_algebra::insert_elements(data_vector, left_filler_vector, right_filler_vector);
    ASSERT_TRUE(result_vector.empty());
}

TEST(insert_elements_must_function_as_expected, char_data_vector_is_empty_char_left_filler_vector_is_2_chars_char_right_filler_vector_is_empty)
{
    std::vector<char> data_vector;
    std::vector<char> left_filler_vector { 'a', 'b' };
    std::vector<char> right_filler_vector;

    std::vector<char> result_vector = yli::linear_algebra::insert_elements(data_vector, left_filler_vector, right_filler_vector);
    ASSERT_TRUE(result_vector.empty());
}

TEST(insert_elements_must_function_as_expected, char_data_vector_is_empty_char_left_filler_vector_is_empty_char_right_filler_vector_is_2_chars)
{
    std::vector<char> data_vector;
    std::vector<char> left_filler_vector;
    std::vector<char> right_filler_vector { 'a', 'b' };

    std::vector<char> result_vector = yli::linear_algebra::insert_elements(data_vector, left_filler_vector, right_filler_vector);
    ASSERT_TRUE(result_vector.empty());
}

TEST(insert_elements_must_function_as_expected, char_data_vector_is_empty_char_left_filler_vector_is_1_char_char_right_filler_vector_is_2_chars)
{
    std::vector<char> data_vector;
    std::vector<char> left_filler_vector { 'a' };
    std::vector<char> right_filler_vector { 'b', 'c' };

    std::vector<char> result_vector = yli::linear_algebra::insert_elements(data_vector, left_filler_vector, right_filler_vector);
    ASSERT_TRUE(result_vector.empty());
}

TEST(insert_elements_must_function_as_expected, char_data_vector_is_empty_char_left_filler_vector_is_2_chars_char_right_filler_vector_is_1_char)
{
    std::vector<char> data_vector;
    std::vector<char> left_filler_vector { 'a', 'b' };
    std::vector<char> right_filler_vector { 'c' };

    std::vector<char> result_vector = yli::linear_algebra::insert_elements(data_vector, left_filler_vector, right_filler_vector);
    ASSERT_TRUE(result_vector.empty());
}

TEST(insert_elements_must_function_as_expected, char_data_vector_is_empty_char_left_filler_vector_is_2_chars_char_right_filler_vector_is_2_chars)
{
    std::vector<char> data_vector;
    std::vector<char> left_filler_vector { 'a', 'b' };
    std::vector<char> right_filler_vector { 'c', 'd' };

    std::vector<char> result_vector = yli::linear_algebra::insert_elements(data_vector, left_filler_vector, right_filler_vector);
    ASSERT_TRUE(result_vector.empty());
}

TEST(insert_elements_must_function_as_expected, char_data_vector_is_1_char_char_left_filler_vector_is_empty_char_right_filler_vector_is_empty)
{
    std::vector<char> data_vector { 'a' };
    std::vector<char> left_filler_vector;
    std::vector<char> right_filler_vector;

    std::vector<char> result_vector = yli::linear_algebra::insert_elements(data_vector, left_filler_vector, right_filler_vector);
    ASSERT_FALSE(result_vector.empty());
    ASSERT_EQ(result_vector.size(), 1);
    ASSERT_EQ(result_vector[0], 'a');
}

TEST(insert_elements_must_function_as_expected, char_data_vector_is_1_char_char_left_filler_vector_is_1_char_char_right_filler_vector_is_empty)
{
    std::vector<char> data_vector { 'a' };
    std::vector<char> left_filler_vector { 'b' };
    std::vector<char> right_filler_vector;

    std::vector<char> result_vector = yli::linear_algebra::insert_elements(data_vector, left_filler_vector, right_filler_vector);
    ASSERT_FALSE(result_vector.empty());
    ASSERT_EQ(result_vector.size(), 2);
    ASSERT_EQ(result_vector[0], 'b');
    ASSERT_EQ(result_vector[1], 'a');
}

TEST(insert_elements_must_function_as_expected, char_data_vector_is_1_char_char_left_filler_vector_is_empty_char_right_filler_vector_is_1_char)
{
    std::vector<char> data_vector { 'a' };
    std::vector<char> left_filler_vector;
    std::vector<char> right_filler_vector { 'b' };

    std::vector<char> result_vector = yli::linear_algebra::insert_elements(data_vector, left_filler_vector, right_filler_vector);
    ASSERT_FALSE(result_vector.empty());
    ASSERT_EQ(result_vector.size(), 2);
    ASSERT_EQ(result_vector[0], 'a');
    ASSERT_EQ(result_vector[1], 'b');
}

TEST(insert_elements_must_function_as_expected, char_data_vector_is_1_char_char_left_filler_vector_is_1_char_char_right_filler_vector_is_1_char)
{
    std::vector<char> data_vector { 'a' };
    std::vector<char> left_filler_vector { 'b' };
    std::vector<char> right_filler_vector { 'c' };

    std::vector<char> result_vector = yli::linear_algebra::insert_elements(data_vector, left_filler_vector, right_filler_vector);
    ASSERT_FALSE(result_vector.empty());
    ASSERT_EQ(result_vector.size(), 3);
    ASSERT_EQ(result_vector[0], 'b');
    ASSERT_EQ(result_vector[1], 'a');
    ASSERT_EQ(result_vector[2], 'c');
}

TEST(insert_elements_must_function_as_expected, char_data_vector_is_1_char_char_left_filler_vector_is_2_chars_char_right_filler_vector_is_empty)
{
    std::vector<char> data_vector { 'a' };
    std::vector<char> left_filler_vector { 'b', 'c' };
    std::vector<char> right_filler_vector;

    std::vector<char> result_vector = yli::linear_algebra::insert_elements(data_vector, left_filler_vector, right_filler_vector);
    ASSERT_FALSE(result_vector.empty());
    ASSERT_EQ(result_vector.size(), 3);
    ASSERT_EQ(result_vector[0], 'b');
    ASSERT_EQ(result_vector[1], 'c');
    ASSERT_EQ(result_vector[2], 'a');
}

TEST(insert_elements_must_function_as_expected, char_data_vector_is_1_char_char_left_filler_vector_is_empty_char_right_filler_vector_is_2_chars)
{
    std::vector<char> data_vector { 'a' };
    std::vector<char> left_filler_vector;
    std::vector<char> right_filler_vector { 'b', 'c' };

    std::vector<char> result_vector = yli::linear_algebra::insert_elements(data_vector, left_filler_vector, right_filler_vector);
    ASSERT_FALSE(result_vector.empty());
    ASSERT_EQ(result_vector.size(), 3);
    ASSERT_EQ(result_vector[0], 'a');
    ASSERT_EQ(result_vector[1], 'b');
    ASSERT_EQ(result_vector[2], 'c');
}

TEST(insert_elements_must_function_as_expected, char_data_vector_is_1_char_char_left_filler_vector_is_1_char_char_right_filler_vector_is_2_chars)
{
    std::vector<char> data_vector { 'a' };
    std::vector<char> left_filler_vector { 'b' };
    std::vector<char> right_filler_vector { 'c', 'd' };

    std::vector<char> result_vector = yli::linear_algebra::insert_elements(data_vector, left_filler_vector, right_filler_vector);
    ASSERT_FALSE(result_vector.empty());
    ASSERT_EQ(result_vector.size(), 4);
    ASSERT_EQ(result_vector[0], 'b');
    ASSERT_EQ(result_vector[1], 'a');
    ASSERT_EQ(result_vector[2], 'c');
    ASSERT_EQ(result_vector[3], 'd');
}

TEST(insert_elements_must_function_as_expected, char_data_vector_is_1_char_char_left_filler_vector_is_2_chars_char_right_filler_vector_is_1_char)
{
    std::vector<char> data_vector { 'a' };
    std::vector<char> left_filler_vector { 'b', 'c' };
    std::vector<char> right_filler_vector { 'd' };

    std::vector<char> result_vector = yli::linear_algebra::insert_elements(data_vector, left_filler_vector, right_filler_vector);
    ASSERT_FALSE(result_vector.empty());
    ASSERT_EQ(result_vector.size(), 4);
    ASSERT_EQ(result_vector[0], 'b');
    ASSERT_EQ(result_vector[1], 'c');
    ASSERT_EQ(result_vector[2], 'a');
    ASSERT_EQ(result_vector[3], 'd');
}

TEST(insert_elements_must_function_as_expected, char_data_vector_is_1_char_char_left_filler_vector_is_2_chars_char_right_filler_vector_is_2_chars)
{
    std::vector<char> data_vector { 'a' };
    std::vector<char> left_filler_vector { 'b', 'c' };
    std::vector<char> right_filler_vector { 'd', 'e' };

    std::vector<char> result_vector = yli::linear_algebra::insert_elements(data_vector, left_filler_vector, right_filler_vector);
    ASSERT_FALSE(result_vector.empty());
    ASSERT_EQ(result_vector.size(), 5);
    ASSERT_EQ(result_vector[0], 'b');
    ASSERT_EQ(result_vector[1], 'c');
    ASSERT_EQ(result_vector[2], 'a');
    ASSERT_EQ(result_vector[3], 'd');
    ASSERT_EQ(result_vector[4], 'e');
}

TEST(insert_elements_must_function_as_expected, char_data_vector_is_2_chars_char_left_filler_vector_is_empty_char_right_filler_vector_is_empty)
{
    std::vector<char> data_vector { 'a', 'b' };
    std::vector<char> left_filler_vector;
    std::vector<char> right_filler_vector;

    std::vector<char> result_vector = yli::linear_algebra::insert_elements(data_vector, left_filler_vector, right_filler_vector);
    ASSERT_FALSE(result_vector.empty());
    ASSERT_EQ(result_vector.size(), 2);
    ASSERT_EQ(result_vector[0], 'a');
    ASSERT_EQ(result_vector[1], 'b');
}

TEST(insert_elements_must_function_as_expected, char_data_vector_is_2_chars_char_left_filler_vector_is_1_char_char_right_filler_vector_is_empty)
{
    std::vector<char> data_vector { 'a', 'b' };
    std::vector<char> left_filler_vector { 'c' };
    std::vector<char> right_filler_vector;

    std::vector<char> result_vector = yli::linear_algebra::insert_elements(data_vector, left_filler_vector, right_filler_vector);
    ASSERT_FALSE(result_vector.empty());
    ASSERT_EQ(result_vector.size(), 4);
    ASSERT_EQ(result_vector[0], 'c');
    ASSERT_EQ(result_vector[1], 'a');
    ASSERT_EQ(result_vector[2], 'c');
    ASSERT_EQ(result_vector[3], 'b');
}

TEST(insert_elements_must_function_as_expected, char_data_vector_is_2_chars_char_left_filler_vector_is_empty_char_right_filler_vector_is_1_char)
{
    std::vector<char> data_vector { 'a', 'b' };
    std::vector<char> left_filler_vector;
    std::vector<char> right_filler_vector { 'c' };

    std::vector<char> result_vector = yli::linear_algebra::insert_elements(data_vector, left_filler_vector, right_filler_vector);
    ASSERT_FALSE(result_vector.empty());
    ASSERT_EQ(result_vector.size(), 4);
    ASSERT_EQ(result_vector[0], 'a');
    ASSERT_EQ(result_vector[1], 'c');
    ASSERT_EQ(result_vector[2], 'b');
    ASSERT_EQ(result_vector[3], 'c');
}

TEST(insert_elements_must_function_as_expected, char_data_vector_is_2_chars_char_left_filler_vector_is_1_char_char_right_filler_vector_is_1_char)
{
    std::vector<char> data_vector { 'a', 'b' };
    std::vector<char> left_filler_vector { 'c' };
    std::vector<char> right_filler_vector { 'd' };

    std::vector<char> result_vector = yli::linear_algebra::insert_elements(data_vector, left_filler_vector, right_filler_vector);
    ASSERT_FALSE(result_vector.empty());
    ASSERT_EQ(result_vector.size(), 6);
    ASSERT_EQ(result_vector[0], 'c');
    ASSERT_EQ(result_vector[1], 'a');
    ASSERT_EQ(result_vector[2], 'd');
    ASSERT_EQ(result_vector[3], 'c');
    ASSERT_EQ(result_vector[4], 'b');
    ASSERT_EQ(result_vector[5], 'd');
}

TEST(insert_elements_must_function_as_expected, char_data_vector_is_2_chars_char_left_filler_vector_is_2_chars_char_right_filler_vector_is_empty)
{
    std::vector<char> data_vector { 'a', 'b' };
    std::vector<char> left_filler_vector { 'c', 'd' };
    std::vector<char> right_filler_vector;

    std::vector<char> result_vector = yli::linear_algebra::insert_elements(data_vector, left_filler_vector, right_filler_vector);
    ASSERT_FALSE(result_vector.empty());
    ASSERT_EQ(result_vector.size(), 6);
    ASSERT_EQ(result_vector[0], 'c');
    ASSERT_EQ(result_vector[1], 'd');
    ASSERT_EQ(result_vector[2], 'a');
    ASSERT_EQ(result_vector[3], 'c');
    ASSERT_EQ(result_vector[4], 'd');
    ASSERT_EQ(result_vector[5], 'b');
}

TEST(insert_elements_must_function_as_expected, char_data_vector_is_2_chars_char_left_filler_vector_is_empty_char_right_filler_vector_is_2_chars)
{
    std::vector<char> data_vector { 'a', 'b' };
    std::vector<char> left_filler_vector;
    std::vector<char> right_filler_vector { 'c', 'd' };

    std::vector<char> result_vector = yli::linear_algebra::insert_elements(data_vector, left_filler_vector, right_filler_vector);
    ASSERT_FALSE(result_vector.empty());
    ASSERT_EQ(result_vector.size(), 6);
    ASSERT_EQ(result_vector[0], 'a');
    ASSERT_EQ(result_vector[1], 'c');
    ASSERT_EQ(result_vector[2], 'd');
    ASSERT_EQ(result_vector[3], 'b');
    ASSERT_EQ(result_vector[4], 'c');
    ASSERT_EQ(result_vector[5], 'd');
}

TEST(insert_elements_must_function_as_expected, char_data_vector_is_2_chars_char_left_filler_vector_is_1_char_char_right_filler_vector_is_2_chars)
{
    std::vector<char> data_vector { 'a', 'b' };
    std::vector<char> left_filler_vector { 'c' };
    std::vector<char> right_filler_vector { 'd', 'e' };

    std::vector<char> result_vector = yli::linear_algebra::insert_elements(data_vector, left_filler_vector, right_filler_vector);
    ASSERT_FALSE(result_vector.empty());
    ASSERT_EQ(result_vector.size(), 8);
    ASSERT_EQ(result_vector[0], 'c');
    ASSERT_EQ(result_vector[1], 'a');
    ASSERT_EQ(result_vector[2], 'd');
    ASSERT_EQ(result_vector[3], 'e');
    ASSERT_EQ(result_vector[4], 'c');
    ASSERT_EQ(result_vector[5], 'b');
    ASSERT_EQ(result_vector[6], 'd');
    ASSERT_EQ(result_vector[7], 'e');
}

TEST(insert_elements_must_function_as_expected, char_data_vector_is_2_chars_char_left_filler_vector_is_2_chars_char_right_filler_vector_is_1_char)
{
    std::vector<char> data_vector { 'a', 'b' };
    std::vector<char> left_filler_vector { 'c', 'd' };
    std::vector<char> right_filler_vector { 'e' };

    std::vector<char> result_vector = yli::linear_algebra::insert_elements(data_vector, left_filler_vector, right_filler_vector);
    ASSERT_FALSE(result_vector.empty());
    ASSERT_EQ(result_vector.size(), 8);
    ASSERT_EQ(result_vector[0], 'c');
    ASSERT_EQ(result_vector[1], 'd');
    ASSERT_EQ(result_vector[2], 'a');
    ASSERT_EQ(result_vector[3], 'e');
    ASSERT_EQ(result_vector[4], 'c');
    ASSERT_EQ(result_vector[5], 'd');
    ASSERT_EQ(result_vector[6], 'b');
    ASSERT_EQ(result_vector[7], 'e');
}

TEST(insert_elements_must_function_as_expected, char_data_vector_is_2_chars_char_left_filler_vector_is_2_chars_char_right_filler_vector_is_2_chars)
{
    std::vector<char> data_vector { 'a', 'b' };
    std::vector<char> left_filler_vector { 'c', 'd' };
    std::vector<char> right_filler_vector { 'e', 'f' };

    std::vector<char> result_vector = yli::linear_algebra::insert_elements(data_vector, left_filler_vector, right_filler_vector);
    ASSERT_FALSE(result_vector.empty());
    ASSERT_EQ(result_vector.size(), 10);
    ASSERT_EQ(result_vector[0], 'c');
    ASSERT_EQ(result_vector[1], 'd');
    ASSERT_EQ(result_vector[2], 'a');
    ASSERT_EQ(result_vector[3], 'e');
    ASSERT_EQ(result_vector[4], 'f');
    ASSERT_EQ(result_vector[5], 'c');
    ASSERT_EQ(result_vector[6], 'd');
    ASSERT_EQ(result_vector[7], 'b');
    ASSERT_EQ(result_vector[8], 'e');
    ASSERT_EQ(result_vector[9], 'f');
}
