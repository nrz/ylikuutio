#include "gtest/gtest.h"
#include "code/ylikuutio/ontology/shader_struct.hpp"

TEST(ShaderStruct_must_be_initialized_appropriately, ShaderStruct)
{
    const ShaderStruct test_shader_struct;
    ASSERT_EQ(test_shader_struct.parent, nullptr);
    ASSERT_TRUE(test_shader_struct.vertex_shader.empty());
    ASSERT_TRUE(test_shader_struct.fragment_shader.empty());
}
