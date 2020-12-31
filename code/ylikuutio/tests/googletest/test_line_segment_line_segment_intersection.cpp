// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2021 Antti Nuortimo.
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
#include "code/ylikuutio/geometry/line_segment_line_segment_intersection.hpp"
#include "code/ylikuutio/geometry/line_segment2D.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow

TEST(line_segment2D_line_segment2D_intersection, parallel_line_segments)
{
    // ^............ a1 = point 1 of line segment a at (2, 2).
    // |.....b1..... a2 = point 2 of line segment a at (11, 5).
    // |..b2.....a2.
    // |*......*.... b1 = point 1 of line segment b at (7, 6).
    // |....*....... b2 = point 2 of line segment b at (4, 5).
    // |a1..........
    // |............
    // +----------->
    const yli::geometry::LineSegment2D line_segment_a = yli::geometry::LineSegment2D(glm::vec2(2.0f, 2.0f), glm::vec2(11.0f, 5.0f));
    const yli::geometry::LineSegment2D line_segment_b = yli::geometry::LineSegment2D(glm::vec2(7.0f, 6.0f), glm::vec2(4.0f, 5.0f));

    const glm::vec2 intersection_point_a_a = yli::geometry::get_intersection_point(&line_segment_a, &line_segment_a);
    ASSERT_TRUE(std::isnan(intersection_point_a_a.x));
    ASSERT_TRUE(std::isnan(intersection_point_a_a.y));

    const glm::vec2 intersection_point_a_b = yli::geometry::get_intersection_point(&line_segment_a, &line_segment_b);
    ASSERT_TRUE(std::isnan(intersection_point_a_b.x));
    ASSERT_TRUE(std::isnan(intersection_point_a_b.y));

    const glm::vec2 intersection_point_b_a = yli::geometry::get_intersection_point(&line_segment_b, &line_segment_a);
    ASSERT_TRUE(std::isnan(intersection_point_b_a.x));
    ASSERT_TRUE(std::isnan(intersection_point_b_a.y));

    const glm::vec2 intersection_point_b_b = yli::geometry::get_intersection_point(&line_segment_b, &line_segment_b);
    ASSERT_TRUE(std::isnan(intersection_point_b_b.x));
    ASSERT_TRUE(std::isnan(intersection_point_b_b.y));

    // LineSegment c is same as but point order is changed.
    const yli::geometry::LineSegment2D line_segment_c = yli::geometry::LineSegment2D(glm::vec2(11.0f, 5.0f), glm::vec2(2.0f, 2.0f));

    const glm::vec2 intersection_point_a_c = yli::geometry::get_intersection_point(&line_segment_a, &line_segment_c);
    ASSERT_TRUE(std::isnan(intersection_point_a_c.x));
    ASSERT_TRUE(std::isnan(intersection_point_a_c.y));

    const glm::vec2 intersection_point_b_c = yli::geometry::get_intersection_point(&line_segment_b, &line_segment_c);
    ASSERT_TRUE(std::isnan(intersection_point_b_c.x));
    ASSERT_TRUE(std::isnan(intersection_point_b_c.y));

    const glm::vec2 intersection_point_c_c = yli::geometry::get_intersection_point(&line_segment_c, &line_segment_c);
    ASSERT_TRUE(std::isnan(intersection_point_c_c.x));
    ASSERT_TRUE(std::isnan(intersection_point_c_c.y));

    const glm::vec2 intersection_point_c_a = yli::geometry::get_intersection_point(&line_segment_c, &line_segment_a);
    ASSERT_TRUE(std::isnan(intersection_point_c_a.x));
    ASSERT_TRUE(std::isnan(intersection_point_c_a.y));

    const glm::vec2 intersection_point_c_b = yli::geometry::get_intersection_point(&line_segment_c, &line_segment_b);
    ASSERT_TRUE(std::isnan(intersection_point_c_b.x));
    ASSERT_TRUE(std::isnan(intersection_point_c_b.y));
}

TEST(line_segment2D_line_segment2D_intersection, intersecting_line_segments)
{
    // ^..........*. a1 = point 1 of line segment a at (5, 1).
    // |*.......a2.. a2 = point 2 of line segment a at (10, 6).
    // |.b1.....*...
    // |....*..*.... b1 = point 1 of line segment b at (3, 5).
    // |......x..... b2 = point 2 of line segment b at (9, 2).
    // |.....*.b2...
    // |...a1.....*. x = intersection point at (7, 3).
    // +----------->
    const yli::geometry::LineSegment2D line_segment_a = yli::geometry::LineSegment2D(glm::vec2(5.0f, 1.0f), glm::vec2(10.0f, 6.0f));
    ASSERT_EQ(line_segment_a.determinant, 20.0f);
    ASSERT_EQ(line_segment_a.x1_minus_x2, -5.0f);
    ASSERT_EQ(line_segment_a.y1_minus_y2, -5.0f);

    const yli::geometry::LineSegment2D line_segment_b = yli::geometry::LineSegment2D(glm::vec2(3.0f, 5.0f), glm::vec2(9.0f, 2.0f));
    ASSERT_EQ(line_segment_b.determinant, -39.0f);
    ASSERT_EQ(line_segment_b.x1_minus_x2, -6.0f);
    ASSERT_EQ(line_segment_b.y1_minus_y2, 3.0f);

    const glm::vec2 intersection_point = yli::geometry::get_intersection_point(&line_segment_a, &line_segment_b);
    ASSERT_EQ(intersection_point.x, 7.0f);
    ASSERT_EQ(intersection_point.y, 3.0f);
}

TEST(line_segment2D_line_segment2D_intersection, potentially_but_not_intersecting_line_segments)
{
    // ^..........*. a1 = point 1 of line segment a at (5, 1).
    // |*.......a2.. a2 = point 2 of line segment a at (10, 6).
    // |.b1.....*...
    // |...b2..*.... b1 = point 1 of line segment b at (3, 5).
    // |......x..... b2 = point 2 of line segment b at (5, 4).
    // |.....*......
    // |...a1....... x = potential intersection point at (7, 3).
    // +----------->
    const yli::geometry::LineSegment2D line_segment_a = yli::geometry::LineSegment2D(glm::vec2(5.0f, 1.0f), glm::vec2(10.0f, 6.0f));
    ASSERT_EQ(line_segment_a.determinant, 20.0f);
    ASSERT_EQ(line_segment_a.x1_minus_x2, -5.0f);
    ASSERT_EQ(line_segment_a.y1_minus_y2, -5.0f);

    const yli::geometry::LineSegment2D line_segment_b = yli::geometry::LineSegment2D(glm::vec2(3.0f, 5.0f), glm::vec2(5.0f, 4.0f));
    ASSERT_EQ(line_segment_b.determinant, -13.0f);
    ASSERT_EQ(line_segment_b.x1_minus_x2, -2.0f);
    ASSERT_EQ(line_segment_b.y1_minus_y2, 1.0f);

    const glm::vec2 intersection_point = yli::geometry::get_intersection_point(&line_segment_a, &line_segment_b);
    ASSERT_TRUE(std::isnan(intersection_point.x));
    ASSERT_TRUE(std::isnan(intersection_point.y));
}

TEST(line_segment2D_line_segment2D_intersection, intersection_at_other_lines_point2)
{
    // ^..........*. a1 = point 1 of line segment a at (5, 1).
    // |*.......a2.. a2 = point 2 of line segment a at (10, 6).
    // |.b1.....*...
    // |....*..*.... b1 = point 1 of line segment b at (3, 5).
    // |......x..... x = point 2 of line segment b at (7, 3).
    // |.....*......
    // |...a1....... x = intersection point at (7, 3).
    // +----------->
    const yli::geometry::LineSegment2D line_segment_a = yli::geometry::LineSegment2D(glm::vec2(5.0f, 1.0f), glm::vec2(10.0f, 6.0f));
    ASSERT_EQ(line_segment_a.determinant, 20.0f);
    ASSERT_EQ(line_segment_a.x1_minus_x2, -5.0f);
    ASSERT_EQ(line_segment_a.y1_minus_y2, -5.0f);

    const yli::geometry::LineSegment2D line_segment_b = yli::geometry::LineSegment2D(glm::vec2(3.0f, 5.0f), glm::vec2(7.0f, 3.0f));
    ASSERT_EQ(line_segment_b.determinant, -26.0f);
    ASSERT_EQ(line_segment_b.x1_minus_x2, -4.0f);
    ASSERT_EQ(line_segment_b.y1_minus_y2, 2.0f);

    const glm::vec2 intersection_point = yli::geometry::get_intersection_point(&line_segment_a, &line_segment_b);
    ASSERT_EQ(intersection_point.x, 7.0f);
    ASSERT_EQ(intersection_point.y, 3.0f);
}

TEST(line_segment2D_line_segment2D_intersection, intersection_at_both_lines_point2)
{
    // ^............ a1 = point 1 of line segment a at (5, 1).
    // |*........... x = point 2 of line segment a at (7, 3).
    // |.b1.........
    // |....*....... b1 = point 1 of line segment b at (3, 5).
    // |......x..... x = point 2 of line segment b at (7, 3).
    // |.....*......
    // |...a1....... x = intersection point at (7, 3).
    // +----------->
    const yli::geometry::LineSegment2D line_segment_a = yli::geometry::LineSegment2D(glm::vec2(5.0f, 1.0f), glm::vec2(7.0f, 3.0f));
    ASSERT_EQ(line_segment_a.determinant, 8.0f);
    ASSERT_EQ(line_segment_a.x1_minus_x2, -2.0f);
    ASSERT_EQ(line_segment_a.y1_minus_y2, -2.0f);

    const yli::geometry::LineSegment2D line_segment_b = yli::geometry::LineSegment2D(glm::vec2(3.0f, 5.0f), glm::vec2(7.0f, 3.0f));
    ASSERT_EQ(line_segment_b.determinant, -26.0f);
    ASSERT_EQ(line_segment_b.x1_minus_x2, -4.0f);
    ASSERT_EQ(line_segment_b.y1_minus_y2, 2.0f);

    const glm::vec2 intersection_point = yli::geometry::get_intersection_point(&line_segment_a, &line_segment_b);
    ASSERT_EQ(intersection_point.x, 7.0f);
    ASSERT_EQ(intersection_point.y, 3.0f);
}
