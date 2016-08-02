#include "gtest/gtest.h"
#include "code/ylikuutio/ontology/heightmap_loader.hpp"
#include "code/ylikuutio/ontology/heightmap_loader.cpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

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

    bool model_loading_result = ontology::load_BMP_world(
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

    bool model_loading_result = ontology::load_BMP_world(
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
