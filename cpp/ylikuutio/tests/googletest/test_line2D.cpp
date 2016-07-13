#include "gtest/gtest.h"
#include "cpp/ylikuutio/geometry/line2D.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include Eigen
#include <Eigen/Dense>

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
#include <vector>   // std::vector

TEST(line2D_must_be_defined_as_expected, line2D_std_vector_float_x1_0_y1_0_x2_1_y2_1)
{
    std::vector<float> point1;
    point1.push_back(0.0f); // x = 0.0
    point1.push_back(0.0f); // y = 0.0

    std::vector<float> point2;
    point2.push_back(1.0f); // x = 1.0
    point2.push_back(1.0f); // y = 1.0

    geometry::Line2D line1 = geometry::Line2D(point1, point2);
    ASSERT_EQ(line1.x1, 0.0f);
    ASSERT_EQ(line1.y1, 0.0f);
    ASSERT_EQ(line1.x2, 1.0f);
    ASSERT_EQ(line1.y2, 1.0f);
    ASSERT_EQ(line1.x1_minus_x2, -1.0f);
    ASSERT_EQ(line1.y1_minus_y2, -1.0f);
    ASSERT_EQ(line1.determinant, 0.0f);

    geometry::Line2D line2 = geometry::Line2D(std::vector<float>{ 0.0f, 0.0f }, std::vector<float>{ 1.0f, 1.0f });
    ASSERT_EQ(line2.determinant, 0.0f);
}

TEST(line2D_must_be_defined_as_expected, line2D_glm_vec2_x1_0_y1_0_x2_1_y2_1)
{
    glm::vec2 point1 = glm::vec2(0.0f, 0.0f); // x = 0.0, y = 0.0
    glm::vec2 point2 = glm::vec2(1.0f, 1.0f); // x = 1.0, y = 1.0

    geometry::Line2D line1 = geometry::Line2D(point1, point2);
    ASSERT_EQ(line1.x1, 0.0f);
    ASSERT_EQ(line1.y1, 0.0f);
    ASSERT_EQ(line1.x2, 1.0f);
    ASSERT_EQ(line1.y2, 1.0f);
    ASSERT_EQ(line1.x1_minus_x2, -1.0f);
    ASSERT_EQ(line1.y1_minus_y2, -1.0f);
    ASSERT_EQ(line1.determinant, 0.0f);
}

TEST(lines2D_defined_with_std_vector_float_and_glm_vec2_must_be_identical, x1_0_y1_0_x2_1_y2_1)
{
    geometry::Line2D line_std_vector_float = geometry::Line2D(std::vector<float>{ 0.0f, 0.0f }, std::vector<float>{ 1.0f, 1.0f });
    geometry::Line2D line_glm_vec2 = geometry::Line2D(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f));
    ASSERT_TRUE(line_std_vector_float.is_identical_with(&line_glm_vec2));
    ASSERT_TRUE(line_glm_vec2.is_identical_with(&line_std_vector_float));
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
