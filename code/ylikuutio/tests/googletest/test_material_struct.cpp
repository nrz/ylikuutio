#include "gtest/gtest.h"
#include "code/ylikuutio/ontology/material_struct.hpp"

TEST(MaterialStruct_must_be_initialized_appropriately, MaterialStruct)
{
    MaterialStruct test_material_struct;
    ASSERT_EQ(test_material_struct.parent, nullptr);
    ASSERT_TRUE(test_material_struct.texture_file_format.empty());
    ASSERT_TRUE(test_material_struct.texture_filename.empty());
    ASSERT_TRUE(test_material_struct.image_path.empty());
}
