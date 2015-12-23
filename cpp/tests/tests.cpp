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
#include "cpp/common/heightmap_loader.hpp"
#include "cpp/common/heightmap_loader.cpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

#include <cmath>  // std::isnan
#include <string>
#include <vector> // std::vector

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

TEST_CASE("256x256 BMP world must be loaded appropriately", "[load_256x256_BMP_world]")
{
    std::string image_path = "noise256x256.bmp";
    std::vector<glm::vec3> out_vertices;
    std::vector<glm::vec2> out_UVs;
    std::vector<glm::vec3> out_normals;
    GLuint image_width = 0;
    GLuint image_height = 0;
    std::string color_channel = "mean";

    bool model_loading_result = model::load_BMP_world(
            image_path,
            *&out_vertices,
            *&out_UVs,
            *&out_normals,
            *&image_width,
            *&image_height,
            color_channel);
#define N_VERTICES_FOR_FACE 3
#define N_FACES_FOR_BILINEAR_TRIANGULATION 4
#define N_WIDTH_OF_IMAGE_FILE 256
#define N_HEIGHT_OF_IMAGE_FILE 256

    REQUIRE(out_vertices.size() == N_VERTICES_FOR_FACE * N_FACES_FOR_BILINEAR_TRIANGULATION * (N_WIDTH_OF_IMAGE_FILE - 1) * (N_HEIGHT_OF_IMAGE_FILE - 1));
    REQUIRE(out_UVs.size() == N_VERTICES_FOR_FACE * N_FACES_FOR_BILINEAR_TRIANGULATION * (N_WIDTH_OF_IMAGE_FILE - 1) * (N_HEIGHT_OF_IMAGE_FILE - 1));
    REQUIRE(out_normals.size() == N_VERTICES_FOR_FACE * N_FACES_FOR_BILINEAR_TRIANGULATION * (N_WIDTH_OF_IMAGE_FILE - 1) * (N_HEIGHT_OF_IMAGE_FILE - 1));

#undef N_VERTICES_FOR_FACE
#undef N_FACES_FOR_BILINEAR_TRIANGULATION
#undef N_WIDTH_OF_IMAGE_FILE
#undef N_HEIGHT_OF_IMAGE_FILE
}
