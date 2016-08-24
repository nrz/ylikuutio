#include "gtest/gtest.h"
#include "code/ylikuutio/linear_algebra/matrix.hpp"

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr

TEST(matrices_must_function_as_expected, matrices)
{
    linear_algebra::Matrix identity3x3(3, 3);
    identity3x3 << 1; identity3x3 << 0; identity3x3 << 0;
    identity3x3 << 0; identity3x3 << 1; identity3x3 << 0;
    identity3x3 << 0; identity3x3 << 0; identity3x3 << 1;

    linear_algebra::Matrix zeros3x3(3, 3);
    zeros3x3 << 0; zeros3x3 << 0; zeros3x3 << 0;
    zeros3x3 << 0; zeros3x3 << 0; zeros3x3 << 0;
    zeros3x3 << 0; zeros3x3 << 0; zeros3x3 << 0;

    linear_algebra::Matrix ones3x3(3, 3);
    ones3x3 << 1; ones3x3 << 1; ones3x3 << 1;
    ones3x3 << 1; ones3x3 << 1; ones3x3 << 1;
    ones3x3 << 1; ones3x3 << 1; ones3x3 << 1;

    linear_algebra::Matrix magic3x3(3, 3);
    magic3x3 << 8; magic3x3 << 1; magic3x3 << 6;
    magic3x3 << 3; magic3x3 << 5; magic3x3 << 7;
    magic3x3 << 4; magic3x3 << 9; magic3x3 << 2;

    ASSERT_EQ(magic3x3[0][0], 8);
    ASSERT_EQ(magic3x3[1][0], 3);
    ASSERT_EQ(magic3x3[2][0], 4);
    ASSERT_EQ(magic3x3[0][1], 1);
    ASSERT_EQ(magic3x3[1][1], 5);
    ASSERT_EQ(magic3x3[2][1], 9);
    ASSERT_EQ(magic3x3[0][2], 6);
    ASSERT_EQ(magic3x3[1][2], 7);
    ASSERT_EQ(magic3x3[2][2], 2);

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
    zeros3x3++;
    ASSERT_TRUE(zeros3x3 == ones3x3);
    zeros3x3--;
    ASSERT_FALSE(zeros3x3 == ones3x3);
    ones3x3--;
    ASSERT_TRUE(zeros3x3 == ones3x3);
    ones3x3++;
    ASSERT_FALSE(zeros3x3 == ones3x3);

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
}
