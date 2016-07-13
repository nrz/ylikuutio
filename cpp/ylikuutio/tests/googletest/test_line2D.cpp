#include "gtest/gtest.h"
#include "cpp/ylikuutio/geometry/line2D.hpp"

// Include Eigen
#include <Eigen/Dense>

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
#include <vector>   // std::vector

TEST(line2D_must_be_defined_as_expected, line2D_x1_0_y1_0_x2_1_y2_1)
{
    std::vector<float> point1;
    point1.push_back(0.0f); // x = 0.0
    point1.push_back(0.0f); // y = 0.0

    std::vector<float> point2;
    point2.push_back(1.0f); // x = 1.0
    point2.push_back(1.0f); // y = 1.0

    geometry::Line2D* line1 = new geometry::Line2D(point1, point2);
    ASSERT_EQ(line1->determinant, 0.0f);
    delete line1;
}

TEST(line2D_must_be_defined_as_expected, line2D_x1_340_y1_150_x2_100_y2_50)
{
    std::vector<float> point1;
    point1.push_back(340.0f); // x = 340.0
    point1.push_back(150.0f); // y = 150.0

    std::vector<float> point2;
    point2.push_back(100.0f); // x = 100.0
    point2.push_back(50.0f); // y = 50.0

    geometry::Line2D* line1 = new geometry::Line2D(point1, point2);
    ASSERT_EQ(line1->determinant, 2000.0f);
    delete line1;
}
