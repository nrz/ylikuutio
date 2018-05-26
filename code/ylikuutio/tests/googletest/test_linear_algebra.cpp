#include "gtest/gtest.h"
#include "code/ylikuutio/linear_algebra/matrix.hpp"
#include "code/ylikuutio/linear_algebra/matrix_functions.hpp"
#include "code/ylikuutio/linear_algebra/tensor3.hpp"

// Include standard headers
#include <vector>   // std::vector

TEST(matrices_must_function_as_expected, matrices)
{
    // populate matrices and matrix equality.

    linear_algebra::Matrix identity3x3(3, 3);
    identity3x3 << 1; identity3x3 << 0; identity3x3 << 0;
    identity3x3 << 0; identity3x3 << 1; identity3x3 << 0;
    identity3x3 << 0; identity3x3 << 0; identity3x3 << 1;

    linear_algebra::Matrix identity3x3_populate_with_vector(3, 3);
    identity3x3_populate_with_vector << std::vector<float> {
            1, 0, 0,
            0, 1, 0,
            0, 0, 1 };
    ASSERT_TRUE(identity3x3 == identity3x3_populate_with_vector);
    ASSERT_FALSE(identity3x3 != identity3x3_populate_with_vector);

    linear_algebra::Matrix zeros3x3(3, 3);
    zeros3x3 << 0; zeros3x3 << 0; zeros3x3 << 0;
    zeros3x3 << 0; zeros3x3 << 0; zeros3x3 << 0;
    zeros3x3 << 0; zeros3x3 << 0; zeros3x3 << 0;

    linear_algebra::Matrix zeros3x3_populate_with_vector(3, 3);
    zeros3x3_populate_with_vector << std::vector<float> {
            0, 0, 0,
            0, 0, 0,
            0, 0, 0 };
    ASSERT_TRUE(zeros3x3 == zeros3x3_populate_with_vector);
    ASSERT_FALSE(zeros3x3 != zeros3x3_populate_with_vector);

    linear_algebra::Matrix ones3x3(3, 3);
    ones3x3 << 1; ones3x3 << 1; ones3x3 << 1;
    ones3x3 << 1; ones3x3 << 1; ones3x3 << 1;
    ones3x3 << 1; ones3x3 << 1; ones3x3 << 1;

    linear_algebra::Matrix ones3x3_populate_with_vector(3, 3);
    ones3x3_populate_with_vector << std::vector<float> {
            1, 1, 1,
            1, 1, 1,
            1, 1, 1 };
    ASSERT_TRUE(ones3x3 == ones3x3_populate_with_vector);
    ASSERT_FALSE(ones3x3 != ones3x3_populate_with_vector);

    linear_algebra::Matrix magic3x3(3, 3);
    magic3x3 << 8; magic3x3 << 1; magic3x3 << 6;
    magic3x3 << 3; magic3x3 << 5; magic3x3 << 7;
    magic3x3 << 4; magic3x3 << 9; magic3x3 << 2;

    linear_algebra::Matrix magic3x3_populate_with_vector(3, 3);
    magic3x3_populate_with_vector << std::vector<float> {
            8, 1, 6,
            3, 5, 7,
            4, 9, 2 };
    ASSERT_TRUE(magic3x3 == magic3x3_populate_with_vector);
    ASSERT_FALSE(magic3x3 != magic3x3_populate_with_vector);

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

    linear_algebra::Matrix magic3x3_transposed(*magic3x3.transpose());
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
    zeros3x3++;
    ASSERT_TRUE(zeros3x3 == ones3x3);
    ASSERT_FALSE(zeros3x3 != ones3x3);
    zeros3x3--;
    ASSERT_FALSE(zeros3x3 == ones3x3);
    ASSERT_TRUE(zeros3x3 != ones3x3);
    ones3x3--;
    ASSERT_TRUE(zeros3x3 == ones3x3);
    ASSERT_FALSE(zeros3x3 != ones3x3);
    ones3x3++;
    ASSERT_FALSE(zeros3x3 == ones3x3);
    ASSERT_TRUE(zeros3x3 != ones3x3);

    // copy constructor.

    linear_algebra::Matrix magic3x3_plus_ones3x3_with_augmented_assignment(magic3x3);
    ASSERT_EQ(magic3x3_plus_ones3x3_with_augmented_assignment[0][0], 8);
    ASSERT_EQ(magic3x3_plus_ones3x3_with_augmented_assignment[1][0], 3);
    ASSERT_EQ(magic3x3_plus_ones3x3_with_augmented_assignment[2][0], 4);
    ASSERT_EQ(magic3x3_plus_ones3x3_with_augmented_assignment[0][1], 1);
    ASSERT_EQ(magic3x3_plus_ones3x3_with_augmented_assignment[1][1], 5);
    ASSERT_EQ(magic3x3_plus_ones3x3_with_augmented_assignment[2][1], 9);
    ASSERT_EQ(magic3x3_plus_ones3x3_with_augmented_assignment[0][2], 6);
    ASSERT_EQ(magic3x3_plus_ones3x3_with_augmented_assignment[1][2], 7);
    ASSERT_EQ(magic3x3_plus_ones3x3_with_augmented_assignment[2][2], 2);

    // copy constructor.

    linear_algebra::Matrix magic3x3_plus_magic3x3_with_augmented_assignment(magic3x3);
    ASSERT_EQ(magic3x3_plus_magic3x3_with_augmented_assignment[0][0], 8);
    ASSERT_EQ(magic3x3_plus_magic3x3_with_augmented_assignment[1][0], 3);
    ASSERT_EQ(magic3x3_plus_magic3x3_with_augmented_assignment[2][0], 4);
    ASSERT_EQ(magic3x3_plus_magic3x3_with_augmented_assignment[0][1], 1);
    ASSERT_EQ(magic3x3_plus_magic3x3_with_augmented_assignment[1][1], 5);
    ASSERT_EQ(magic3x3_plus_magic3x3_with_augmented_assignment[2][1], 9);
    ASSERT_EQ(magic3x3_plus_magic3x3_with_augmented_assignment[0][2], 6);
    ASSERT_EQ(magic3x3_plus_magic3x3_with_augmented_assignment[1][2], 7);
    ASSERT_EQ(magic3x3_plus_magic3x3_with_augmented_assignment[2][2], 2);

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

    // matrix addition (binary addition).

    linear_algebra::Matrix magic3x3_plus_ones3x3(3, 3);
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

    // matrix addition (binary addition).

    linear_algebra::Matrix magic3x3_plus_magic3x3(3, 3);
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

    // matrix multiplication.

    linear_algebra::Matrix ones3x3squared(3, 3);
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

    linear_algebra::Matrix magic3x3squared(3, 3);
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

    // matrix transpose.
    linear_algebra::Matrix magic3x3transposed = *magic3x3.transpose();
    ASSERT_EQ(magic3x3transposed[0][0], 8);
    ASSERT_EQ(magic3x3transposed[1][0], 1);
    ASSERT_EQ(magic3x3transposed[2][0], 6);
    ASSERT_EQ(magic3x3transposed[0][1], 3);
    ASSERT_EQ(magic3x3transposed[1][1], 5);
    ASSERT_EQ(magic3x3transposed[2][1], 7);
    ASSERT_EQ(magic3x3transposed[0][2], 4);
    ASSERT_EQ(magic3x3transposed[1][2], 9);
    ASSERT_EQ(magic3x3transposed[2][2], 2);

    // matrix concatenation.

    // use `Matrix(std::shared_ptr<linear_algebra::Matrix> old_matrix)`.
    linear_algebra::Matrix magic3x3_above_magic3x3_transposed_below_with_shared_ptr(cat(1, magic3x3, magic3x3_transposed));
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below_with_shared_ptr[0][0], 8);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below_with_shared_ptr[1][0], 3);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below_with_shared_ptr[2][0], 4);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below_with_shared_ptr[3][0], 8);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below_with_shared_ptr[4][0], 1);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below_with_shared_ptr[5][0], 6);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below_with_shared_ptr[0][1], 1);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below_with_shared_ptr[1][1], 5);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below_with_shared_ptr[2][1], 9);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below_with_shared_ptr[3][1], 3);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below_with_shared_ptr[4][1], 5);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below_with_shared_ptr[5][1], 7);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below_with_shared_ptr[0][2], 6);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below_with_shared_ptr[1][2], 7);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below_with_shared_ptr[2][2], 2);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below_with_shared_ptr[3][2], 4);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below_with_shared_ptr[4][2], 9);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below_with_shared_ptr[5][2], 2);

    // use `Matrix(linear_algebra::Matrix& old_matrix)`.
    linear_algebra::Matrix magic3x3_above_magic3x3_transposed_below_without_shared_ptr(*cat(1, magic3x3, magic3x3_transposed));
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below_without_shared_ptr[0][0], 8);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below_without_shared_ptr[1][0], 3);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below_without_shared_ptr[2][0], 4);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below_without_shared_ptr[3][0], 8);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below_without_shared_ptr[4][0], 1);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below_without_shared_ptr[5][0], 6);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below_without_shared_ptr[0][1], 1);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below_without_shared_ptr[1][1], 5);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below_without_shared_ptr[2][1], 9);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below_without_shared_ptr[3][1], 3);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below_without_shared_ptr[4][1], 5);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below_without_shared_ptr[5][1], 7);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below_without_shared_ptr[0][2], 6);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below_without_shared_ptr[1][2], 7);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below_without_shared_ptr[2][2], 2);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below_without_shared_ptr[3][2], 4);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below_without_shared_ptr[4][2], 9);
    ASSERT_EQ(magic3x3_above_magic3x3_transposed_below_without_shared_ptr[5][2], 2);

    ASSERT_TRUE(magic3x3_above_magic3x3_transposed_below_with_shared_ptr == magic3x3_above_magic3x3_transposed_below_without_shared_ptr);

    // matrix concatenation.

    linear_algebra::Matrix magic3x3_left_magic3x3_transposed_right(*cat(2, magic3x3, magic3x3_transposed));
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
}

TEST(tensors_must_function_as_expected, tensors)
{
    // populate tensors and tensor equality.

    linear_algebra::Tensor3 some_tensor3x3x3(3, 3, 3);
    some_tensor3x3x3 << 1; some_tensor3x3x3 << 2; some_tensor3x3x3 << 3;
    some_tensor3x3x3 << 4; some_tensor3x3x3 << 5; some_tensor3x3x3 << 6;
    some_tensor3x3x3 << 7; some_tensor3x3x3 << 8; some_tensor3x3x3 << 9;

    some_tensor3x3x3 << 10; some_tensor3x3x3 << 11; some_tensor3x3x3 << 12;
    some_tensor3x3x3 << 13; some_tensor3x3x3 << 14; some_tensor3x3x3 << 15;
    some_tensor3x3x3 << 16; some_tensor3x3x3 << 17; some_tensor3x3x3 << 18;

    some_tensor3x3x3 << 19; some_tensor3x3x3 << 20; some_tensor3x3x3 << 21;
    some_tensor3x3x3 << 22; some_tensor3x3x3 << 23; some_tensor3x3x3 << 24;
    some_tensor3x3x3 << 25; some_tensor3x3x3 << 26; some_tensor3x3x3 << 27;

    linear_algebra::Tensor3 some_tensor3x3x3_populate_with_vector(3, 3, 3);
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
    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[1][0][0], 4);
    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[2][0][0], 7);

    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[0][1][0], 2);
    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[1][1][0], 5);
    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[2][1][0], 8);

    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[0][2][0], 3);
    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[1][2][0], 6);
    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[2][2][0], 9);

    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[0][0][1], 10);
    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[1][0][1], 13);
    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[2][0][1], 16);

    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[0][1][1], 11);
    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[1][1][1], 14);
    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[2][1][1], 17);

    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[0][2][1], 12);
    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[1][2][1], 15);
    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[2][2][1], 18);

    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[0][0][2], 19);
    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[1][0][2], 22);
    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[2][0][2], 25);

    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[0][1][2], 20);
    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[1][1][2], 23);
    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[2][1][2], 26);

    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[0][2][2], 21);
    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[1][2][2], 24);
    ASSERT_EQ(some_tensor3x3x3_populate_with_vector[2][2][2], 27);
}
