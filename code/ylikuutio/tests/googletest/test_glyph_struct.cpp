#include "gtest/gtest.h"
#include "code/ylikuutio/ontology/glyph_struct.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

TEST(GlyphStruct_must_be_initialized_appropriately, GlyphStruct)
{
    GlyphStruct test_glyph_struct;
    ASSERT_EQ(test_glyph_struct.glyph_vertex_data, nullptr);
    ASSERT_EQ(test_glyph_struct.glyph_name_pointer, nullptr);
    ASSERT_EQ(test_glyph_struct.unicode_char_pointer, nullptr);
    ASSERT_EQ(test_glyph_struct.universe, nullptr);
    ASSERT_EQ(test_glyph_struct.shader_pointer, nullptr);
    ASSERT_EQ(test_glyph_struct.parent, nullptr);
    ASSERT_EQ(test_glyph_struct.light_position, glm::vec3(0.0f, 0.0f, 0.0f));
}
