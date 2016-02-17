#include "gtest/gtest.h"
#include "testable.hpp"
#include "cpp/ylikuutio/common/globals.hpp"

TEST(GetTwoTest, Two)
{
    EXPECT_EQ(2, getTwo());
}

TEST(ShaderStruct_must_be_initialized_appropriately, ShaderStruct)
{
    ShaderStruct test_shader_struct;
    ASSERT_EQ(test_shader_struct.parent_pointer, nullptr);
    ASSERT_TRUE(test_shader_struct.vertex_shader.empty());
    ASSERT_TRUE(test_shader_struct.fragment_shader.empty());
}
