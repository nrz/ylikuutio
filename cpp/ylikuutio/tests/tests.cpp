#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#endif

#ifndef __CATCH_HPP_INCLUDED
#define __CATCH_HPP_INCLUDED
#include "catch.hpp"
#endif

#include "cpp/ylikuutio/common/globals.hpp"
#include "cpp/ylikuutio/model/shader_loader.hpp"
#include "cpp/ylikuutio/model/texture_loader.hpp"
#include "cpp/ylikuutio/model/vboindexer.hpp"
#include "cpp/ylikuutio/model/text2D.hpp"
#include "cpp/ylikuutio/model/text3D.hpp"
#include "cpp/ylikuutio/model/world.hpp"
#include "cpp/ylikuutio/model/shader.hpp"
#include "cpp/ylikuutio/model/material.hpp"
#include "cpp/ylikuutio/model/font.hpp"
#include "cpp/ylikuutio/model/glyph.hpp"
#include "cpp/ylikuutio/model/species.hpp"
#include "cpp/ylikuutio/model/object.hpp"
#include "cpp/ylikuutio/common/transformation.hpp"
#include "cpp/ylikuutio/common/transformation.cpp"
#include "cpp/ylikuutio/common/indexing.hpp"
#include "cpp/ylikuutio/common/indexing.cpp"
#include "cpp/ylikuutio/common/bilinear_interpolation.hpp"
#include "cpp/ylikuutio/common/bilinear_interpolation.cpp"
#include "cpp/ylikuutio/common/triangulation.hpp"
#include "cpp/ylikuutio/common/triangulation.cpp"
#include "cpp/ylikuutio/model/heightmap_loader.hpp"
#include "cpp/ylikuutio/model/heightmap_loader.cpp"

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

#include <cmath>    // std::isnan
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

TEST_CASE("ShaderStruct must be initialized appropriately", "[ShaderStruct]")
{
    ShaderStruct test_shader_struct;
    REQUIRE(test_shader_struct.parent_pointer == nullptr);
    REQUIRE(test_shader_struct.vertex_shader.empty());
    REQUIRE(test_shader_struct.fragment_shader.empty());
}

TEST_CASE("MaterialStruct must be initialized appropriately", "[MaterialStruct]")
{
    MaterialStruct test_material_struct;
    REQUIRE(test_material_struct.parent_pointer == nullptr);
    REQUIRE(test_material_struct.texture_file_format.empty());
    REQUIRE(test_material_struct.texture_filename.empty());
    REQUIRE(test_material_struct.image_path.empty());
}

TEST_CASE("NodeStruct must be initialized appropriately", "[NodeStruct]")
{
    NodeStruct test_node_struct;
    REQUIRE(test_node_struct.parent_pointer == nullptr);
    REQUIRE(test_node_struct.coordinate_vector == glm::vec3(0.0f, 0.0f, 0.0f));
    REQUIRE(test_node_struct.neighbor_nodeIDs.size() == 0);
}

TEST_CASE("ObjectStruct must be initialized appropriately", "[ObjectStruct]")
{
    ObjectStruct test_object_struct;
    REQUIRE(test_object_struct.species_parent_pointer == nullptr);
    REQUIRE(test_object_struct.glyph_parent_pointer == nullptr);
    REQUIRE(test_object_struct.original_scale_vector == glm::vec3(1.0f, 1.0f, 1.0f));
    REQUIRE(std::isnan(test_object_struct.rotate_angle));
    REQUIRE(test_object_struct.is_character == false);
    REQUIRE(test_object_struct.coordinate_vector == glm::vec3(0.0f, 0.0f, 0.0f));
    REQUIRE(test_object_struct.rotate_vector == glm::vec3(0.0f, 0.0f, 0.0f));
    REQUIRE(test_object_struct.translate_vector == glm::vec3(0.0f, 0.0f, 0.0f));
}

TEST_CASE("SpeciesStruct must be initialized appropriately", "[SpeciesStruct]")
{
    SpeciesStruct test_species_struct;
    REQUIRE(test_species_struct.parent_pointer == nullptr);
    REQUIRE(test_species_struct.is_world == false);
    REQUIRE(std::isnan(test_species_struct.world_radius));
    REQUIRE(test_species_struct.model_file_format.empty());
    REQUIRE(test_species_struct.model_filename.empty());
    REQUIRE(test_species_struct.color_channel.empty());
    REQUIRE(test_species_struct.light_position == glm::vec3(0.0f, 0.0f, 0.0f));
    REQUIRE(test_species_struct.coordinate_system.empty());
}

TEST_CASE("FontStruct must be initialized appropriately", "[FontStruct]")
{
    FontStruct test_font_struct;
    REQUIRE(test_font_struct.parent_pointer == nullptr);
    REQUIRE(test_font_struct.vertex_scaling_factor == DEFAULT_VERTEX_SCALING_FACTOR);
    REQUIRE(test_font_struct.font_file_format.empty());
    REQUIRE(test_font_struct.font_filename.empty());
}

TEST_CASE("GlyphStruct must be initialized appropriately", "[GlyphStruct]")
{
    GlyphStruct test_glyph_struct;
    REQUIRE(test_glyph_struct.parent_pointer == nullptr);
    REQUIRE(test_glyph_struct.light_position == glm::vec3(0.0f, 0.0f, 0.0f));
}

TEST_CASE("2x2 world must be triangulated appropriately", "[triangulate_2x2_world]")
{
    GIVEN("a 2x2 world with heights 1, 2, 4 and 8")
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

        WHEN("bilinear interpolation is used")
        {
            triangulate_quads_struct.triangulation_type = "bilinear_interpolation";

            bool is_success = geometry::triangulate_quads(triangulate_quads_struct, vertices, UVs, normals);
            REQUIRE(is_success == true);
            REQUIRE(vertices.size() == 12);
            REQUIRE(UVs.size() == 12);
            REQUIRE(normals.size() == 12);

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
            REQUIRE(vertices[0].x == center_x);
            REQUIRE(vertices[0].z == center_z);
            REQUIRE(vertices[0].y == (GLfloat) (southwest_height + southeast_height + northwest_height + northeast_height) / 4);

            // 2nd vertex is the southwest vertex of the 1st triangle.
            REQUIRE(vertices[1].x == 1.0f);
            REQUIRE(vertices[1].z == 0.0f);
            REQUIRE(vertices[1].y == southeast_height);

            // 3rd vertex is the northwest vertex of the 1st triangle.
            REQUIRE(vertices[2].x == 0.0f);
            REQUIRE(vertices[2].z == 0.0f);
            REQUIRE(vertices[2].y == southwest_height);

            // 4th vertex is the center vertex of the 2nd triangle.
            REQUIRE(vertices[3].x == center_x);
            REQUIRE(vertices[3].z == center_z);
            REQUIRE(vertices[3].y == (GLfloat) (southwest_height + southeast_height + northwest_height + northeast_height) / 4);

            // 5th vertex is the southwest vertex of the 2nd triangle.
            REQUIRE(vertices[4].x == 0.0f);
            REQUIRE(vertices[4].z == 0.0f);
            REQUIRE(vertices[4].y == southwest_height);

            // 6th vertex is the northwest vertex of the 2nd triangle.
            REQUIRE(vertices[5].x == 0.0f);
            REQUIRE(vertices[5].z == 1.0f);
            REQUIRE(vertices[5].y == northwest_height);

            // 7th vertex is the center vertex of the 3rd triangle.
            REQUIRE(vertices[6].x == center_x);
            REQUIRE(vertices[6].z == center_z);
            REQUIRE(vertices[6].y == (GLfloat) (southwest_height + southeast_height + northwest_height + northeast_height) / 4);

            // 8th vertex is the northwest vertex of the 3rd triangle.
            REQUIRE(vertices[7].x == 0.0f);
            REQUIRE(vertices[7].z == 1.0f);
            REQUIRE(vertices[7].y == northwest_height);

            // 9th vertex is the northeast vertex of the 3rd triangle.
            REQUIRE(vertices[8].x == 1.0f);
            REQUIRE(vertices[8].z == 1.0f);
            REQUIRE(vertices[8].y == northeast_height);

            // 10th vertex is the center vertex of the 4th triangle.
            REQUIRE(vertices[9].x == center_x);
            REQUIRE(vertices[9].z == center_z);
            REQUIRE(vertices[9].y == (GLfloat) (southwest_height + southeast_height + northwest_height + northeast_height) / 4);

            // 11th vertex is the northeast vertex of the 4th triangle.
            REQUIRE(vertices[10].x == 1.0f);
            REQUIRE(vertices[10].z == 1.0f);
            REQUIRE(vertices[10].y == northeast_height);

            // 12th vertex is the southeast vertex of the 4th triangle.
            REQUIRE(vertices[11].x == 1.0f);
            REQUIRE(vertices[11].z == 0.0f);
            REQUIRE(vertices[11].y == southeast_height);
        }
        WHEN("southeast-northwest edges are used")
        {
            triangulate_quads_struct.triangulation_type = "southeast_northwest_edges";

            bool is_success = geometry::triangulate_quads(triangulate_quads_struct, vertices, UVs, normals);
            REQUIRE(is_success == true);
            REQUIRE(vertices.size() == 6);
            REQUIRE(UVs.size() == 6);
            REQUIRE(normals.size() == 6);

            std::cout << " 0: " << vertices[0].x << ", " << vertices[0].y << ", " << vertices[0].z << "\n";
            std::cout << " 1: " << vertices[1].x << ", " << vertices[1].y << ", " << vertices[1].z << "\n";
            std::cout << " 2: " << vertices[2].x << ", " << vertices[2].y << ", " << vertices[2].z << "\n";
            std::cout << " 3: " << vertices[3].x << ", " << vertices[3].y << ", " << vertices[3].z << "\n";
            std::cout << " 4: " << vertices[4].x << ", " << vertices[4].y << ", " << vertices[4].z << "\n";
            std::cout << " 5: " << vertices[5].x << ", " << vertices[5].y << ", " << vertices[5].z << "\n";

            // 1st vertex is the southwest vertex of the 1st triangle.
            REQUIRE(vertices[0].x == 0.0f);
            REQUIRE(vertices[0].z == 0.0f);
            REQUIRE(vertices[0].y == southwest_height);

            // 2nd vertex is the northwest vertex of the 1st triangle.
            REQUIRE(vertices[1].x == 0.0f);
            REQUIRE(vertices[1].z == 1.0f);
            REQUIRE(vertices[1].y == northwest_height);

            // 3rd vertex is the southeast vertex of the 1st triangle.
            REQUIRE(vertices[2].x == 1.0f);
            REQUIRE(vertices[2].z == 0.0f);
            REQUIRE(vertices[2].y == southeast_height);

            // 4th vertex is the northeast vertex of the 2nd triangle.
            REQUIRE(vertices[3].x == 1.0f);
            REQUIRE(vertices[3].z == 1.0f);
            REQUIRE(vertices[3].y == northeast_height);

            // 5th vertex is the southeast vertex of the 2nd triangle.
            REQUIRE(vertices[4].x == 1.0f);
            REQUIRE(vertices[4].z == 0.0f);
            REQUIRE(vertices[4].y == southeast_height);

            // 6th vertex is the northwest vertex of the 2nd triangle.
            REQUIRE(vertices[5].x == 0.0f);
            REQUIRE(vertices[5].z == 1.0f);
            REQUIRE(vertices[5].y == northwest_height);
        }
    }
}

TEST_CASE("3x3 BMP world must be loaded appropriately", "[load_3x3_BMP_world]")
{
    std::string image_path = "test3x3.bmp";
    std::vector<glm::vec3> out_vertices;
    std::vector<glm::vec2> out_UVs;
    std::vector<glm::vec3> out_normals;
    GLuint image_width = 0;
    GLuint image_height = 0;
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
#define N_VERTICES_FOR_FACE 3
#define N_FACES_FOR_BILINEAR_TRIANGULATION 4
#define N_WIDTH_OF_IMAGE_FILE 3
#define N_HEIGHT_OF_IMAGE_FILE 3

    REQUIRE(out_vertices.size() == N_VERTICES_FOR_FACE * N_FACES_FOR_BILINEAR_TRIANGULATION * (N_WIDTH_OF_IMAGE_FILE - 1) * (N_HEIGHT_OF_IMAGE_FILE - 1));
    REQUIRE(out_UVs.size() == N_VERTICES_FOR_FACE * N_FACES_FOR_BILINEAR_TRIANGULATION * (N_WIDTH_OF_IMAGE_FILE - 1) * (N_HEIGHT_OF_IMAGE_FILE - 1));
    REQUIRE(out_normals.size() == N_VERTICES_FOR_FACE * N_FACES_FOR_BILINEAR_TRIANGULATION * (N_WIDTH_OF_IMAGE_FILE - 1) * (N_HEIGHT_OF_IMAGE_FILE - 1));

#undef N_VERTICES_FOR_FACE
#undef N_FACES_FOR_BILINEAR_TRIANGULATION
#undef N_WIDTH_OF_IMAGE_FILE
#undef N_HEIGHT_OF_IMAGE_FILE
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
