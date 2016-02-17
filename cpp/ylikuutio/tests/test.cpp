#include "gtest/gtest.h"
#include "testable.hpp"
#include "cpp/ylikuutio/common/globals.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

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

TEST(MaterialStruct_must_be_initialized_appropriately, MaterialStruct)
{
    MaterialStruct test_material_struct;
    ASSERT_EQ(test_material_struct.parent_pointer, nullptr);
    ASSERT_TRUE(test_material_struct.texture_file_format.empty());
    ASSERT_TRUE(test_material_struct.texture_filename.empty());
    ASSERT_TRUE(test_material_struct.image_path.empty());
}

TEST(NodeStruct_must_be_initialized_appropriately, NodeStruct)
{
    NodeStruct test_node_struct;
    ASSERT_EQ(test_node_struct.parent_pointer, nullptr);
    ASSERT_EQ(test_node_struct.coordinate_vector, glm::vec3(0.0f, 0.0f, 0.0f));
    ASSERT_EQ(test_node_struct.neighbor_nodeIDs.size(), 0);
}
