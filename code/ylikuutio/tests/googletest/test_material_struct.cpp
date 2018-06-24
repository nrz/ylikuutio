#include "gtest/gtest.h"
#include "code/ylikuutio/ontology/material_struct.hpp"

TEST(MaterialStruct_must_be_initialized_appropriately, MaterialStruct)
{
    const MaterialStruct test_material_struct;
    ASSERT_EQ(test_material_struct.shader, nullptr);
    ASSERT_EQ(test_material_struct.symbiosis, nullptr);
    ASSERT_TRUE(test_material_struct.texture_file_format.empty());
    ASSERT_TRUE(test_material_struct.texture_filename.empty());
    ASSERT_TRUE(test_material_struct.image_path.empty());
    ASSERT_FALSE(test_material_struct.is_symbiont_material);
}
