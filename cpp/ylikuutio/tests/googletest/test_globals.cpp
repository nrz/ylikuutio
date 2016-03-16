#include "gtest/gtest.h"
#include "cpp/ylikuutio/common/globals.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <vector>   // std::vector

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

TEST(ObjectStruct_must_be_initialized_appropriately, ObjectStruct)
{
    ObjectStruct test_object_struct;
    ASSERT_EQ(test_object_struct.species_parent_pointer, nullptr);
    ASSERT_EQ(test_object_struct.glyph_parent_pointer, nullptr);
    ASSERT_EQ(test_object_struct.original_scale_vector, glm::vec3(1.0f, 1.0f, 1.0f));
    ASSERT_TRUE(std::isnan(test_object_struct.rotate_angle));
    ASSERT_FALSE(test_object_struct.is_character);
    ASSERT_EQ(test_object_struct.coordinate_vector, glm::vec3(0.0f, 0.0f, 0.0f));
    ASSERT_EQ(test_object_struct.rotate_vector, glm::vec3(0.0f, 0.0f, 0.0f));
    ASSERT_EQ(test_object_struct.translate_vector, glm::vec3(0.0f, 0.0f, 0.0f));
}

TEST(SpeciesStruct_must_be_initialized_appropriately, SpeciesStruct)
{
    SpeciesStruct test_species_struct;
    ASSERT_EQ(test_species_struct.parent_pointer, nullptr);
    ASSERT_FALSE(test_species_struct.is_world);
    ASSERT_TRUE(std::isnan(test_species_struct.world_radius));
    ASSERT_TRUE(test_species_struct.model_file_format.empty());
    ASSERT_TRUE(test_species_struct.model_filename.empty());
    ASSERT_TRUE(test_species_struct.color_channel.empty());
    ASSERT_EQ(test_species_struct.light_position, glm::vec3(0.0f, 0.0f, 0.0f));
    ASSERT_TRUE(test_species_struct.coordinate_system.empty());
}

TEST(FontStruct_must_be_initialized_appropriately, FontStruct)
{
    const float default_vertex_scaling_factor = 0.001f;

    FontStruct test_font_struct;
    ASSERT_EQ(test_font_struct.parent_pointer, nullptr);
    ASSERT_EQ(test_font_struct.vertex_scaling_factor, default_vertex_scaling_factor);
    ASSERT_TRUE(test_font_struct.font_file_format.empty());
    ASSERT_TRUE(test_font_struct.font_filename.empty());
}

TEST(GlyphStruct_must_be_initialized_appropriately, GlyphStruct)
{
    GlyphStruct test_glyph_struct;
    ASSERT_EQ(test_glyph_struct.parent_pointer, nullptr);
    ASSERT_EQ(test_glyph_struct.light_position, glm::vec3(0.0f, 0.0f, 0.0f));
}
