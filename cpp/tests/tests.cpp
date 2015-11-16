#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#endif

#ifndef __CATCH_HPP_INCLUDED
#define __CATCH_HPP_INCLUDED
#include "catch.hpp"
#endif

#include "cpp/common/globals.hpp"
#include "cpp/common/shader_loader.hpp"
#include "cpp/common/texture_loader.hpp"
#include "cpp/common/vboindexer.hpp"
#include "cpp/common/text2D.hpp"
#include "cpp/common/text3D.hpp"
#include "cpp/common/world.hpp"
#include "cpp/common/shader.hpp"
#include "cpp/common/material.hpp"
#include "cpp/common/font.hpp"
#include "cpp/common/glyph.hpp"
#include "cpp/common/species.hpp"
#include "cpp/common/object.hpp"

#include <cmath> // std::isnan

TEST_CASE("SHADERSTRUCT must be initialized appropriately", "[SHADERSTRUCT]")
{
    SHADERSTRUCT(test_shader_struct);
    REQUIRE(test_shader_struct.parent_pointer == NULL);
    REQUIRE(test_shader_struct.vertex_shader.empty());
    REQUIRE(test_shader_struct.fragment_shader.empty());
}

TEST_CASE("MATERIALSTRUCT must be initialized appropriately", "[MATERIALSTRUCT]")
{
    MATERIALSTRUCT(test_material_struct);
    REQUIRE(test_material_struct.parent_pointer == NULL);
    REQUIRE(test_material_struct.texture_file_format.empty());
    REQUIRE(test_material_struct.texture_filename.empty());
    REQUIRE(test_material_struct.image_path.empty());
}

TEST_CASE("NODESTRUCT must be initialized appropriately", "[NODESTRUCT]")
{
    NODESTRUCT(test_node_struct);
    REQUIRE(test_node_struct.parent_pointer == NULL);
    REQUIRE(test_node_struct.coordinate_vector == glm::vec3(0.0f, 0.0f, 0.0f));
    REQUIRE(test_node_struct.neighbor_nodeIDs.size() == 0);
}

TEST_CASE("OBJECTSTRUCT must be initialized appropriately", "[OBJECTSTRUCT]")
{
    OBJECTSTRUCT(test_object_struct);
    REQUIRE(test_object_struct.species_parent_pointer == NULL);
    REQUIRE(test_object_struct.glyph_parent_pointer == NULL);
    REQUIRE(test_object_struct.original_scale_vector == glm::vec3(1.0f, 1.0f, 1.0f));
    REQUIRE(std::isnan(test_object_struct.rotate_angle));
    REQUIRE(test_object_struct.is_character == false);
    REQUIRE(test_object_struct.coordinate_vector == glm::vec3(0.0f, 0.0f, 0.0f));
    REQUIRE(test_object_struct.rotate_vector == glm::vec3(0.0f, 0.0f, 0.0f));
    REQUIRE(test_object_struct.translate_vector == glm::vec3(0.0f, 0.0f, 0.0f));
}

TEST_CASE("SPECIESSTRUCT must be initialized appropriately", "[SPECIESSTRUCT]")
{
    SPECIESSTRUCT(test_species_struct);
    REQUIRE(test_species_struct.parent_pointer == NULL);
    REQUIRE(test_species_struct.is_world == false);
    REQUIRE(std::isnan(test_species_struct.world_radius));
    REQUIRE(test_species_struct.model_file_format.empty());
    REQUIRE(test_species_struct.model_filename.empty());
    REQUIRE(test_species_struct.color_channel.empty());
    REQUIRE(test_species_struct.light_position == glm::vec3(0.0f, 0.0f, 0.0f));
    REQUIRE(test_species_struct.coordinate_system.empty());
}

TEST_CASE("FONTSTRUCT must be initialized appropriately", "[FONTSTRUCT]")
{
    FONTSTRUCT(test_font_struct);
    REQUIRE(test_font_struct.parent_pointer == NULL);
    REQUIRE(test_font_struct.vertex_scaling_factor == DEFAULT_VERTEX_SCALING_FACTOR);
    REQUIRE(test_font_struct.font_file_format.empty());
    REQUIRE(test_font_struct.font_filename.empty());
}

TEST_CASE("GLYPHSTRUCT must be initialized appropriately", "[GLYPHSTRUCT]")
{
    GLYPHSTRUCT(test_glyph_struct);
    REQUIRE(test_glyph_struct.parent_pointer == NULL);
    REQUIRE(test_glyph_struct.light_position == glm::vec3(0.0f, 0.0f, 0.0f));
}
