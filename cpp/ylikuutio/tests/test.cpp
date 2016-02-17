#include "gtest/gtest.h"
#include "testable.hpp"

TEST(GetTwoTest, Two)
{
    EXPECT_EQ(2, GetTwo());
}
