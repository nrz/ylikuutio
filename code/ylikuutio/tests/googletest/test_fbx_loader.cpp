#include "gtest/gtest.h"
#include "code/ylikuutio/loaders/fbx_species_loader.hpp"
#include "code/ylikuutio/loaders/fbx_species_loader.cpp"
#include <miniz.c>
#include <miniz.h>
#include <ofbx.cpp>
#include <ofbx.h>

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

typedef unsigned char u8;

TEST(OpenFBX_must_function_appropriately, rigged_and_animated_cat)
{
    std::string filename = "cat.fbx";
    std::vector<unsigned char> data_vector = file::binary_slurp(filename);
    ASSERT_EQ(data_vector.size(), 7550684);                                // size of `cat.fbx` in bytes.

    const u8* data = reinterpret_cast<unsigned char*>(data_vector.data());
    ASSERT_NE(data, nullptr);

    int size = data_vector.size();
    ASSERT_EQ(size, 7550684);                                             // size of `cat.fbx` in bytes.

    ofbx::IScene* ofbx_iscene = ofbx::load(data, size);
    ASSERT_NE(ofbx_iscene, nullptr);

    const ofbx::IElement* ofbx_ielement = ofbx_iscene->getRootElement();
    ASSERT_NE(ofbx_ielement, nullptr);

    const ofbx::Object* ofbx_object = ofbx_iscene->getRoot();
    ASSERT_NE(ofbx_object, nullptr);
    ofbx::Object::Type ofbx_object_type = ofbx_object->getType();
    ASSERT_EQ(ofbx_object_type, ofbx::Object::Type::ROOT);

    int ofbx_mesh_count = ofbx_iscene->getMeshCount();
    std::cout << filename << ": getMeshCount(): " << ofbx_mesh_count << "\n";
    ASSERT_GT(ofbx_mesh_count, 0);

    for (int i = 0; i < ofbx_mesh_count; i++)
    {
        std::cout << "mesh " << i << "\n";
        const ofbx::Mesh* mesh = ofbx_iscene->getMesh(i);
        ASSERT_NE(mesh, nullptr);

        const ofbx::Geometry* geometry = mesh->getGeometry();
        ASSERT_NE(geometry, nullptr);

        const ofbx::Vec3* vertices = geometry->getVertices();

        int vertex_count = geometry->getVertexCount();
        std::cout << "mesh " << i << ": getVertexCount(): " << vertex_count << "\n";
        ASSERT_GE(vertex_count, 0);

        const ofbx::Vec3* normals = geometry->getNormals();

        const ofbx::Vec2* uvs = geometry->getUVs();

        const ofbx::Vec4* colors = geometry->getColors();

        const ofbx::Vec3* tangents = geometry->getTangents();

        const ofbx::Skin* skin = geometry->getSkin();

        const int* materials = geometry->getMaterials();

        ofbx::Matrix geometric_matrix = mesh->getGeometricMatrix();

        int material_count = mesh->getMaterialCount();
        std::cout << "mesh " << i << ": getMaterialCount(): " << material_count << "\n";
        ASSERT_GT(material_count, 0);

        for (int j = 0; j < material_count; j++)
        {
            std::cout << "mesh " << i << ", material " << j << "\n";
            const ofbx::Material* material = mesh->getMaterial(j);
            ASSERT_NE(material, nullptr);
        }
    }

    int ofbx_animation_stack_count = ofbx_iscene->getAnimationStackCount();
    std::cout << filename << ": getAnimationStackCount(): " << ofbx_animation_stack_count << "\n";
    ASSERT_NE(ofbx_mesh_count, 0);

    const ofbx::Object* const* ofbx_all_objects = ofbx_iscene->getAllObjects();
    ASSERT_NE(ofbx_all_objects, nullptr);

    const int all_object_count = ofbx_iscene->getAllObjectCount();
    std::cout << filename << ": getAllObjectCount(): " << all_object_count << "\n";
    ASSERT_NE(all_object_count, 0);
}
TEST(fbx_file_must_be_loaded_appropriately, rigged_and_animated_cat)
{
    std::string filename = "cat.fbx";
    std::vector<glm::vec3> out_vertices;
    std::vector<glm::vec2> out_UVs;
    std::vector<glm::vec3> out_normals;

    int32_t mesh_i = 0;
    bool result = loaders::load_FBX(filename, mesh_i, out_vertices, out_UVs, out_normals);
    ASSERT_TRUE(result);
}
