#include "gtest/gtest.h"
#include "code/ylikuutio/geometry/line2D.hpp"
#include "code/ylikuutio/linear_algebra/matrix.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

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

TEST(lines2D_defined_with_std_vector_float_and_glm_vec2_must_be_identical, x1_0_y1_0_x2_0_y2_1)
{
    geometry::Line2D line_std_vector_float = geometry::Line2D(std::vector<float>{ 0.0f, 0.0f }, std::vector<float>{ 0.0f, 1.0f });
    geometry::Line2D line_glm_vec2 = geometry::Line2D(glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 1.0f));
    ASSERT_TRUE(line_std_vector_float.is_identical_with(&line_glm_vec2));
    ASSERT_TRUE(line_glm_vec2.is_identical_with(&line_std_vector_float));
}

TEST(lines2D_defined_with_std_vector_float_and_glm_vec2_must_be_identical, x1_0_y1_0_x2_1_y2_0)
{
    geometry::Line2D line_std_vector_float = geometry::Line2D(std::vector<float>{ 0.0f, 0.0f }, std::vector<float>{ 1.0f, 0.0f });
    geometry::Line2D line_glm_vec2 = geometry::Line2D(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f));
    ASSERT_TRUE(line_std_vector_float.is_identical_with(&line_glm_vec2));
    ASSERT_TRUE(line_glm_vec2.is_identical_with(&line_std_vector_float));
}

TEST(lines2D_defined_with_std_vector_float_and_glm_vec2_must_be_identical, x1_0_y1_0_x2_1_y2_1)
{
    geometry::Line2D line_std_vector_float = geometry::Line2D(std::vector<float>{ 0.0f, 0.0f }, std::vector<float>{ 1.0f, 1.0f });
    geometry::Line2D line_glm_vec2 = geometry::Line2D(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f));
    ASSERT_TRUE(line_std_vector_float.is_identical_with(&line_glm_vec2));
    ASSERT_TRUE(line_glm_vec2.is_identical_with(&line_std_vector_float));
}

TEST(lines2D_defined_with_std_vector_float_and_glm_vec2_must_not_be_identical, x1_0_y1_0_x2_0_y2_1_x1_0_y1_1_x2_0_y2_0)
{
    geometry::Line2D line1_std_vector_float = geometry::Line2D(std::vector<float>{ 0.0f, 0.0f }, std::vector<float>{ 0.0f, 1.0f });
    geometry::Line2D line2_std_vector_float = geometry::Line2D(std::vector<float>{ 0.0f, 1.0f }, std::vector<float>{ 0.0f, 0.0f });
    ASSERT_FALSE(line1_std_vector_float.is_identical_with(&line2_std_vector_float));
    ASSERT_FALSE(line2_std_vector_float.is_identical_with(&line1_std_vector_float));
}

TEST(lines2D_defined_with_std_vector_float_and_glm_vec2_must_not_be_identical, x1_1_y1_2_x2_3_y2_4_x1_3_y1_4_x2_1_y2_2)
{
    geometry::Line2D line1_std_vector_float = geometry::Line2D(std::vector<float>{ 1.0f, 2.0f }, std::vector<float>{ 3.0f, 4.0f });
    geometry::Line2D line2_std_vector_float = geometry::Line2D(std::vector<float>{ 3.0f, 4.0f }, std::vector<float>{ 1.0f, 2.0f });
    ASSERT_FALSE(line1_std_vector_float.is_identical_with(&line2_std_vector_float));
    ASSERT_FALSE(line2_std_vector_float.is_identical_with(&line1_std_vector_float));
}

TEST(lines2D_defined_with_std_vector_float_and_glm_vec2_must_not_be_identical, x1_1_y1_2_x2_3_y2_4_x1_2_y1_1_x2_4_y2_3)
{
    geometry::Line2D line1_std_vector_float = geometry::Line2D(std::vector<float>{ 1.0f, 2.0f }, std::vector<float>{ 3.0f, 4.0f });
    geometry::Line2D line2_std_vector_float = geometry::Line2D(std::vector<float>{ 2.0f, 1.0f }, std::vector<float>{ 4.0f, 3.0f });
    ASSERT_FALSE(line1_std_vector_float.is_identical_with(&line2_std_vector_float));
    ASSERT_FALSE(line2_std_vector_float.is_identical_with(&line1_std_vector_float));
}

TEST(line2D_must_be_defined_as_expected, line2D_x1_340_y1_150_x2_100_y2_50)
{
    std::vector<float> point1;
    float x1 = 340.0f;
    float y1 = 150.0f;
    point1.push_back(x1); // x = 340.0
    point1.push_back(y1); // y = 150.0

    std::vector<float> point2;
    float x2 = 100.0f;
    float y2 = 50.0f;
    point2.push_back(x2); // x = 100.0
    point2.push_back(y2); // y = 50.0

    geometry::Line2D* line1 = new geometry::Line2D(point1, point2);
    geometry::Line2D* line2 = new geometry::Line2D(std::vector<float>{ x1, y1 }, std::vector<float>{ x2, y2 });
    ASSERT_TRUE(line1->is_identical_with(line2));
    ASSERT_EQ(line1->determinant, 2000.0f);
    delete line1;
    delete line2;
}
