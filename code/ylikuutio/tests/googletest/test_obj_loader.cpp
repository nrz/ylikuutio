#include "gtest/gtest.h"
#include "code/ylikuutio/loaders/obj_loader.cpp"

// Include standard headers
#include <string>  // std::string
#include <vector>  // std::vector

TEST(obj_files_must_be_loaded_approriately, suzanne_obj)
{
    const std::string obj_filename = "suzanne.obj";
    std::vector<glm::vec3> out_vertices;
    std::vector<glm::vec2> out_UVs;
    std::vector<glm::vec3> out_normals;

    const bool result = loaders::load_OBJ(obj_filename.c_str(), out_vertices, out_UVs, out_normals);
    ASSERT_TRUE(result);

    // note: `load_OBJ` only loads the OBJ file. `load_OBJ` does not remove duplicate vertices.
    const int32_t number_of_faces = 968;
    const int32_t number_of_vertices_in_triangle = 3;
    ASSERT_EQ(out_vertices.size(), number_of_faces * number_of_vertices_in_triangle);
    ASSERT_EQ(out_UVs.size(), number_of_faces * number_of_vertices_in_triangle);
    ASSERT_EQ(out_normals.size(), number_of_faces * number_of_vertices_in_triangle);
}
