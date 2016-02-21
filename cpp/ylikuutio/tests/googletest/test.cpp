#include "gtest/gtest.h"
#include "cpp/ylikuutio/common/globals.hpp"
#include "cpp/ylikuutio/common/transformation.hpp"
#include "cpp/ylikuutio/common/indexing.hpp"
#include "cpp/ylikuutio/common/bilinear_interpolation.hpp"
#include "cpp/ylikuutio/common/triangulation.hpp"
#include "cpp/ylikuutio/model/heightmap_loader.hpp"
#include "cpp/ylikuutio/model/heightmap_loader.cpp"
#include "cpp/ylikuutio/string/ylikuutio_string.hpp"
#include "cpp/ylikuutio/string/ylikuutio_string.cpp"

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

// Include standard headers
#include <cmath>    // std::isnan
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
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

TEST(a_2x2_world_must_be_triangulated_appropriately, bilinear_interpolation)
{
    uint32_t image_width = 2;
    uint32_t image_height = 2;
    uint32_t world_size = image_width * image_height;

    GLuint* vertex_data;
    vertex_data = new GLuint [world_size];
    GLuint* vertex_pointer = vertex_data;
    // x, z: height (y).
    GLuint southwest_height = 1;
    GLuint southeast_height = 2;
    GLuint northwest_height = 4;
    GLuint northeast_height = 8;
    GLfloat center_x = 0.5f;
    GLfloat center_z = 0.5f;

    // 0, 0: 1.
    *vertex_pointer++ = southwest_height;
    // 1, 0: 2.
    *vertex_pointer++ = southeast_height;
    // 0, 1: 4.
    *vertex_pointer++ = northwest_height;
    // 1, 1: 8.
    *vertex_pointer++ = northeast_height;

    std::vector<glm::vec3> vertices; // vertices of the object.
    std::vector<glm::vec2> UVs;      // UVs of the object.
    std::vector<glm::vec3> normals;  // normals of the object.

    TriangulateQuadsStruct triangulate_quads_struct;
    triangulate_quads_struct.input_vertex_pointer = vertex_data;
    triangulate_quads_struct.image_width = image_width;
    triangulate_quads_struct.image_height = image_height;
    triangulate_quads_struct.sphere_radius = NAN;
    triangulate_quads_struct.spherical_world_struct = SphericalWorldStruct(); // not used, but is needed in the function call.

    triangulate_quads_struct.triangulation_type = "bilinear_interpolation";

    bool is_success = geometry::triangulate_quads(triangulate_quads_struct, vertices, UVs, normals);
    ASSERT_TRUE(is_success);
    ASSERT_EQ(vertices.size(), 12);
    ASSERT_EQ(UVs.size(), 12);
    ASSERT_EQ(normals.size(), 12);

    std::cout << " 0: " << vertices[0].x << ", " << vertices[0].y << ", " << vertices[0].z << "\n";
    std::cout << " 1: " << vertices[1].x << ", " << vertices[1].y << ", " << vertices[1].z << "\n";
    std::cout << " 2: " << vertices[2].x << ", " << vertices[2].y << ", " << vertices[2].z << "\n";
    std::cout << " 3: " << vertices[3].x << ", " << vertices[3].y << ", " << vertices[3].z << "\n";
    std::cout << " 4: " << vertices[4].x << ", " << vertices[4].y << ", " << vertices[4].z << "\n";
    std::cout << " 5: " << vertices[5].x << ", " << vertices[5].y << ", " << vertices[5].z << "\n";
    std::cout << " 6: " << vertices[6].x << ", " << vertices[6].y << ", " << vertices[6].z << "\n";
    std::cout << " 7: " << vertices[7].x << ", " << vertices[7].y << ", " << vertices[7].z << "\n";
    std::cout << " 8: " << vertices[8].x << ", " << vertices[8].y << ", " << vertices[8].z << "\n";
    std::cout << " 9: " << vertices[9].x << ", " << vertices[9].y << ", " << vertices[9].z << "\n";
    std::cout << "10: " << vertices[10].x << ", " << vertices[10].y << ", " << vertices[10].z << "\n";
    std::cout << "11: " << vertices[11].x << ", " << vertices[11].y << ", " << vertices[11].z << "\n";

    // 1st vertex is the center vertex of the 1st triangle.
    ASSERT_EQ(vertices[0].x, center_x);
    ASSERT_EQ(vertices[0].z, center_z);
    ASSERT_EQ(vertices[0].y, (GLfloat) (southwest_height + southeast_height + northwest_height + northeast_height) / 4);

    // 2nd vertex is the southwest vertex of the 1st triangle.
    ASSERT_EQ(vertices[1].x, 1.0f);
    ASSERT_EQ(vertices[1].z, 0.0f);
    ASSERT_EQ(vertices[1].y, southeast_height);

    // 3rd vertex is the northwest vertex of the 1st triangle.
    ASSERT_EQ(vertices[2].x, 0.0f);
    ASSERT_EQ(vertices[2].z, 0.0f);
    ASSERT_EQ(vertices[2].y, southwest_height);

    // 4th vertex is the center vertex of the 2nd triangle.
    ASSERT_EQ(vertices[3].x, center_x);
    ASSERT_EQ(vertices[3].z, center_z);
    ASSERT_EQ(vertices[3].y, (GLfloat) (southwest_height + southeast_height + northwest_height + northeast_height) / 4);

    // 5th vertex is the southwest vertex of the 2nd triangle.
    ASSERT_EQ(vertices[4].x, 0.0f);
    ASSERT_EQ(vertices[4].z, 0.0f);
    ASSERT_EQ(vertices[4].y, southwest_height);

    // 6th vertex is the northwest vertex of the 2nd triangle.
    ASSERT_EQ(vertices[5].x, 0.0f);
    ASSERT_EQ(vertices[5].z, 1.0f);
    ASSERT_EQ(vertices[5].y, northwest_height);

    // 7th vertex is the center vertex of the 3rd triangle.
    ASSERT_EQ(vertices[6].x, center_x);
    ASSERT_EQ(vertices[6].z, center_z);
    ASSERT_EQ(vertices[6].y, (GLfloat) (southwest_height + southeast_height + northwest_height + northeast_height) / 4);

    // 8th vertex is the northwest vertex of the 3rd triangle.
    ASSERT_EQ(vertices[7].x, 0.0f);
    ASSERT_EQ(vertices[7].z, 1.0f);
    ASSERT_EQ(vertices[7].y, northwest_height);

    // 9th vertex is the northeast vertex of the 3rd triangle.
    ASSERT_EQ(vertices[8].x, 1.0f);
    ASSERT_EQ(vertices[8].z, 1.0f);
    ASSERT_EQ(vertices[8].y, northeast_height);

    // 10th vertex is the center vertex of the 4th triangle.
    ASSERT_EQ(vertices[9].x, center_x);
    ASSERT_EQ(vertices[9].z, center_z);
    ASSERT_EQ(vertices[9].y, (GLfloat) (southwest_height + southeast_height + northwest_height + northeast_height) / 4);

    // 11th vertex is the northeast vertex of the 4th triangle.
    ASSERT_EQ(vertices[10].x, 1.0f);
    ASSERT_EQ(vertices[10].z, 1.0f);
    ASSERT_EQ(vertices[10].y, northeast_height);

    // 12th vertex is the southeast vertex of the 4th triangle.
    ASSERT_EQ(vertices[11].x, 1.0f);
    ASSERT_EQ(vertices[11].z, 0.0f);
    ASSERT_EQ(vertices[11].y, southeast_height);
}

TEST(a_2x2_world_must_be_triangulated_appropriately, southeast_northwest_edges)
{
    uint32_t image_width = 2;
    uint32_t image_height = 2;
    uint32_t world_size = image_width * image_height;

    GLuint* vertex_data;
    vertex_data = new GLuint [world_size];
    GLuint* vertex_pointer = vertex_data;
    // x, z: height (y).
    GLuint southwest_height = 1;
    GLuint southeast_height = 2;
    GLuint northwest_height = 4;
    GLuint northeast_height = 8;
    GLfloat center_x = 0.5f;
    GLfloat center_z = 0.5f;

    // 0, 0: 1.
    *vertex_pointer++ = southwest_height;
    // 1, 0: 2.
    *vertex_pointer++ = southeast_height;
    // 0, 1: 4.
    *vertex_pointer++ = northwest_height;
    // 1, 1: 8.
    *vertex_pointer++ = northeast_height;

    std::vector<glm::vec3> vertices; // vertices of the object.
    std::vector<glm::vec2> UVs;      // UVs of the object.
    std::vector<glm::vec3> normals;  // normals of the object.

    TriangulateQuadsStruct triangulate_quads_struct;
    triangulate_quads_struct.input_vertex_pointer = vertex_data;
    triangulate_quads_struct.image_width = image_width;
    triangulate_quads_struct.image_height = image_height;
    triangulate_quads_struct.sphere_radius = NAN;
    triangulate_quads_struct.spherical_world_struct = SphericalWorldStruct(); // not used, but is needed in the function call.

    triangulate_quads_struct.triangulation_type = "southeast_northwest_edges";

    bool is_success = geometry::triangulate_quads(triangulate_quads_struct, vertices, UVs, normals);
    ASSERT_TRUE(is_success);
    ASSERT_EQ(vertices.size(), 6);
    ASSERT_EQ(UVs.size(), 6);
    ASSERT_EQ(normals.size(), 6);

    std::cout << " 0: " << vertices[0].x << ", " << vertices[0].y << ", " << vertices[0].z << "\n";
    std::cout << " 1: " << vertices[1].x << ", " << vertices[1].y << ", " << vertices[1].z << "\n";
    std::cout << " 2: " << vertices[2].x << ", " << vertices[2].y << ", " << vertices[2].z << "\n";
    std::cout << " 3: " << vertices[3].x << ", " << vertices[3].y << ", " << vertices[3].z << "\n";
    std::cout << " 4: " << vertices[4].x << ", " << vertices[4].y << ", " << vertices[4].z << "\n";
    std::cout << " 5: " << vertices[5].x << ", " << vertices[5].y << ", " << vertices[5].z << "\n";

    // 1st vertex is the southwest vertex of the 1st triangle.
    ASSERT_EQ(vertices[0].x, 0.0f);
    ASSERT_EQ(vertices[0].z, 0.0f);
    ASSERT_EQ(vertices[0].y, southwest_height);

    // 2nd vertex is the northwest vertex of the 1st triangle.
    ASSERT_EQ(vertices[1].x, 0.0f);
    ASSERT_EQ(vertices[1].z, 1.0f);
    ASSERT_EQ(vertices[1].y, northwest_height);

    // 3rd vertex is the southeast vertex of the 1st triangle.
    ASSERT_EQ(vertices[2].x, 1.0f);
    ASSERT_EQ(vertices[2].z, 0.0f);
    ASSERT_EQ(vertices[2].y, southeast_height);

    // 4th vertex is the northeast vertex of the 2nd triangle.
    ASSERT_EQ(vertices[3].x, 1.0f);
    ASSERT_EQ(vertices[3].z, 1.0f);
    ASSERT_EQ(vertices[3].y, northeast_height);

    // 5th vertex is the southeast vertex of the 2nd triangle.
    ASSERT_EQ(vertices[4].x, 1.0f);
    ASSERT_EQ(vertices[4].z, 0.0f);
    ASSERT_EQ(vertices[4].y, southeast_height);

    // 6th vertex is the northwest vertex of the 2nd triangle.
    ASSERT_EQ(vertices[5].x, 0.0f);
    ASSERT_EQ(vertices[5].z, 1.0f);
    ASSERT_EQ(vertices[5].y, northwest_height);
}

TEST(a_BMP_world_must_be_loaded_appropriately, load_3x3_BMP_world)
{
    std::string image_path = "test3x3.bmp";
    std::vector<glm::vec3> out_vertices;
    std::vector<glm::vec2> out_UVs;
    std::vector<glm::vec3> out_normals;
    uint32_t image_width = 0;
    uint32_t image_height = 0;
    std::string color_channel = "mean";

    std::string triangulation_type = "bilinear_interpolation";

    bool model_loading_result = model::load_BMP_world(
            image_path,
            *&out_vertices,
            *&out_UVs,
            *&out_normals,
            *&image_width,
            *&image_height,
            color_channel,
            triangulation_type);

    const uint32_t n_vertices_for_face = 3;
    const uint32_t n_faces_for_bilinear_triangulation = 4;
    const uint32_t n_width_of_image_file = 3;
    const uint32_t n_height_of_image_file = 3;

    ASSERT_EQ(out_vertices.size(), n_vertices_for_face * n_faces_for_bilinear_triangulation * (n_width_of_image_file - 1) * (n_height_of_image_file - 1));
    ASSERT_EQ(out_UVs.size(), n_vertices_for_face * n_faces_for_bilinear_triangulation * (n_width_of_image_file - 1) * (n_height_of_image_file - 1));
    ASSERT_EQ(out_normals.size(), n_vertices_for_face * n_faces_for_bilinear_triangulation * (n_width_of_image_file - 1) * (n_height_of_image_file - 1));
}

TEST(a_BMP_world_must_be_loaded_appropriately, load_256x256_BMP_world)
{
    std::string image_path = "noise256x256.bmp";
    std::vector<glm::vec3> out_vertices;
    std::vector<glm::vec2> out_UVs;
    std::vector<glm::vec3> out_normals;
    uint32_t image_width = 0;
    uint32_t image_height = 0;
    std::string color_channel = "mean";
    std::string triangulation_type = "bilinear_interpolation";

    bool model_loading_result = model::load_BMP_world(
            image_path,
            *&out_vertices,
            *&out_UVs,
            *&out_normals,
            *&image_width,
            *&image_height,
            color_channel,
            triangulation_type);

    const uint32_t n_vertices_for_face = 3;
    const uint32_t n_faces_for_bilinear_triangulation = 4;
    const uint32_t n_width_of_image_file = 256;
    const uint32_t n_height_of_image_file = 256;

    ASSERT_EQ(out_vertices.size(), n_vertices_for_face * n_faces_for_bilinear_triangulation * (n_width_of_image_file - 1) * (n_height_of_image_file - 1));
    ASSERT_EQ(out_UVs.size(), n_vertices_for_face * n_faces_for_bilinear_triangulation * (n_width_of_image_file - 1) * (n_height_of_image_file - 1));
    ASSERT_EQ(out_normals.size(), n_vertices_for_face * n_faces_for_bilinear_triangulation * (n_width_of_image_file - 1) * (n_height_of_image_file - 1));
}

TEST(string_matching, some_string_must_match_when_there_is_only_one_1_character_string_in_the_identifier_string_vector_and_it_matches)
{
    char text[] = "a";
    const char* text_base_pointer = text;
    char* text_data_pointer = text;
    std::vector<std::string> identifier_strings_vector = { "a" };
    ASSERT_TRUE(string::check_and_report_if_some_string_matches(text_base_pointer, text_data_pointer, identifier_strings_vector));
}
TEST(string_matching, some_string_must_match_when_there_is_only_one_2_character_string_in_the_identifier_string_vector_and_it_matches)
{
    char text[] = "ab";
    const char* text_base_pointer = text;
    char* text_data_pointer = text;
    std::vector<std::string> identifier_strings_vector = { "ab" };
    ASSERT_TRUE(string::check_and_report_if_some_string_matches(text_base_pointer, text_data_pointer, identifier_strings_vector));
}
TEST(string_matching, some_string_must_match_when_there_is_only_one_3_character_string_in_the_identifier_string_vector_and_it_matches)
{
    char text[] = "abc";
    const char* text_base_pointer = text;
    char* text_data_pointer = text;
    std::vector<std::string> identifier_strings_vector = { "abc" };
    ASSERT_TRUE(string::check_and_report_if_some_string_matches(text_base_pointer, text_data_pointer, identifier_strings_vector));
}
TEST(string_matching, some_string_must_match_when_there_are_two_1_character_strings_in_the_identifier_string_vector_and_the_1st_matches)
{
    char text[] = "a";
    const char* text_base_pointer = text;
    char* text_data_pointer = text;
    std::vector<std::string> identifier_strings_vector = { "a", "b" };
    ASSERT_TRUE(string::check_and_report_if_some_string_matches(text_base_pointer, text_data_pointer, identifier_strings_vector));
}
TEST(string_matching, some_string_must_match_when_there_are_two_1_character_strings_in_the_identifier_string_vector_and_the_2nd_matches)
{
    char text[] = "b";
    const char* text_base_pointer = text;
    char* text_data_pointer = text;
    std::vector<std::string> identifier_strings_vector = { "a", "b" };
    ASSERT_TRUE(string::check_and_report_if_some_string_matches(text_base_pointer, text_data_pointer, identifier_strings_vector));
}
TEST(string_matching, some_string_must_match_when_there_are_three_1_character_strings_in_the_identifier_string_vector_and_the_1st_matches)
{
    char text[] = "a";
    const char* text_base_pointer = text;
    char* text_data_pointer = text;
    std::vector<std::string> identifier_strings_vector = { "a", "b", "c" };
    ASSERT_TRUE(string::check_and_report_if_some_string_matches(text_base_pointer, text_data_pointer, identifier_strings_vector));
}
TEST(string_matching, some_string_must_match_when_there_are_three_1_character_strings_in_the_identifier_string_vector_and_the_2nd_matches)
{
    char text[] = "b";
    const char* text_base_pointer = text;
    char* text_data_pointer = text;
    std::vector<std::string> identifier_strings_vector = { "a", "b", "c" };
    ASSERT_TRUE(string::check_and_report_if_some_string_matches(text_base_pointer, text_data_pointer, identifier_strings_vector));
}
TEST(string_matching, some_string_must_match_when_there_are_three_1_character_strings_in_the_identifier_string_vector_and_the_3rd_matches)
{
    char text[] = "c";
    const char* text_base_pointer = text;
    char* text_data_pointer = text;
    std::vector<std::string> identifier_strings_vector = { "a", "b", "c" };
    ASSERT_TRUE(string::check_and_report_if_some_string_matches(text_base_pointer, text_data_pointer, identifier_strings_vector));
}
TEST(string_matching, no_string_must_match_when_the_identifier_string_vector_is_empty)
{
    char text[] = "a";
    const char* text_base_pointer = text;
    char* text_data_pointer = text;
    std::vector<std::string> identifier_strings_vector = {};
    ASSERT_FALSE(string::check_and_report_if_some_string_matches(text_base_pointer, text_data_pointer, identifier_strings_vector));
}
TEST(string_matching, no_string_must_match_when_there_is_only_one_1_character_string_in_the_identifier_string_vector_and_it_does_not_match)
{
    char text[] = "a";
    const char* text_base_pointer = text;
    char* text_data_pointer = text;
    std::vector<std::string> identifier_strings_vector = { "b" };
    ASSERT_FALSE(string::check_and_report_if_some_string_matches(text_base_pointer, text_data_pointer, identifier_strings_vector));
}
TEST(string_matching, no_string_must_match_when_there_is_only_one_2_character_string_in_the_identifier_string_vector_and_its_1st_character_does_not_match)
{
    char text[] = "ab";
    const char* text_base_pointer = text;
    char* text_data_pointer = text;
    std::vector<std::string> identifier_strings_vector = { "bb" };
    ASSERT_FALSE(string::check_and_report_if_some_string_matches(text_base_pointer, text_data_pointer, identifier_strings_vector));
}
TEST(string_matching, no_string_must_match_when_there_is_only_one_2_character_string_in_the_identifier_string_vector_and_its_2nd_character_does_not_match)
{
    char text[] = "ab";
    const char* text_base_pointer = text;
    char* text_data_pointer = text;
    std::vector<std::string> identifier_strings_vector = { "aa" };
    ASSERT_FALSE(string::check_and_report_if_some_string_matches(text_base_pointer, text_data_pointer, identifier_strings_vector));
}
TEST(string_matching, no_string_must_match_when_there_is_only_one_3_character_string_in_the_identifier_string_vector_and_its_1st_character_does_not_match)
{
    char text[] = "abc";
    const char* text_base_pointer = text;
    char* text_data_pointer = text;
    std::vector<std::string> identifier_strings_vector = { "bbc" };
    ASSERT_FALSE(string::check_and_report_if_some_string_matches(text_base_pointer, text_data_pointer, identifier_strings_vector));
}
TEST(string_matching, no_string_must_match_when_there_is_only_one_3_character_string_in_the_identifier_string_vector_and_its_2nd_character_does_not_match)
{
    char text[] = "abc";
    const char* text_base_pointer = text;
    char* text_data_pointer = text;
    std::vector<std::string> identifier_strings_vector = { "aac" };
    ASSERT_FALSE(string::check_and_report_if_some_string_matches(text_base_pointer, text_data_pointer, identifier_strings_vector));
}
TEST(string_matching, no_string_must_match_when_there_is_only_one_3_character_string_in_the_identifier_string_vector_and_its_3rd_character_does_not_match)
{
    char text[] = "abc";
    const char* text_base_pointer = text;
    char* text_data_pointer = text;
    std::vector<std::string> identifier_strings_vector = { "abb" };
    ASSERT_FALSE(string::check_and_report_if_some_string_matches(text_base_pointer, text_data_pointer, identifier_strings_vector));
}
TEST(string_matching, no_string_must_match_when_there_are_two_1_character_strings_in_the_identifier_string_vector_and_neither_matches)
{
    char text[] = "a";
    const char* text_base_pointer = text;
    char* text_data_pointer = text;
    std::vector<std::string> identifier_strings_vector = { "b", "c" };
    ASSERT_FALSE(string::check_and_report_if_some_string_matches(text_base_pointer, text_data_pointer, identifier_strings_vector));
}
TEST(string_matching, no_string_must_match_when_there_are_three_1_character_strings_in_the_identifier_string_vector_and_none_matches)
{
    char text[] = "a";
    const char* text_base_pointer = text;
    char* text_data_pointer = text;
    std::vector<std::string> identifier_strings_vector = { "b", "c", "d" };
    ASSERT_FALSE(string::check_and_report_if_some_string_matches(text_base_pointer, text_data_pointer, identifier_strings_vector));
}
