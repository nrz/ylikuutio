#include "gtest/gtest.h"
#include "code/ylikuutio/ontology/vector_font_struct.hpp"

TEST(VectorFontStruct_must_be_initialized_appropriately, VectorFontStruct)
{
    const float default_vertex_scaling_factor = 0.001f;

    const VectorFontStruct test_vector_font_struct;
    ASSERT_EQ(test_vector_font_struct.parent, nullptr);
    ASSERT_EQ(test_vector_font_struct.vertex_scaling_factor, default_vertex_scaling_factor);
    ASSERT_TRUE(test_vector_font_struct.font_file_format.empty());
    ASSERT_TRUE(test_vector_font_struct.font_filename.empty());
}
