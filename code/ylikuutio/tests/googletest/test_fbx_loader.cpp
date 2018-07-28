#include "gtest/gtest.h"
#include "code/ylikuutio/loaders/fbx_species_loader.hpp"
#include "code/ylikuutio/loaders/fbx_species_loader.cpp"

// Include miniz (required by OpenFBX)
#include <miniz.c>
#include <miniz.h>

// Include OpenFBX
#include <ofbx.cpp>
#include <ofbx.h>

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

typedef unsigned char u8;

TEST(OpenFBX_must_function_appropriately, rigged_and_animated_cat)
{
    const std::string filename = "cat.fbx";
    std::vector<uint8_t> data_vector = yli::file::binary_slurp(filename);
    ASSERT_EQ(data_vector.size(), 7550684);                                // size of `cat.fbx` in bytes.

    const u8* const data = reinterpret_cast<unsigned char*>(data_vector.data());
    ASSERT_NE(data, nullptr);

    const int size = data_vector.size();
    ASSERT_EQ(size, 7550684);                                             // size of `cat.fbx` in bytes.

    const ofbx::IScene* const ofbx_iscene = ofbx::load(data, size);
    ASSERT_NE(ofbx_iscene, nullptr);

    const ofbx::IElement* const ofbx_ielement = ofbx_iscene->getRootElement();
    ASSERT_NE(ofbx_ielement, nullptr);

    const ofbx::Object* const ofbx_object = ofbx_iscene->getRoot();
    ASSERT_NE(ofbx_object, nullptr);
    const ofbx::Object::Type ofbx_object_type = ofbx_object->getType();
    ASSERT_EQ(ofbx_object_type, ofbx::Object::Type::ROOT);

    const int ofbx_mesh_count = ofbx_iscene->getMeshCount();
    ASSERT_GT(ofbx_mesh_count, 0);

    // FBX file may contain several meshes (`ofbx::Mesh`).
    // Each mesh may have several materials (`ofbx::Material`).
    // Each material may have up to 3 textures (`ofbx::Texture`):
    // `ofbx::Texture::DIFFUSE`,
    // `ofbx::Texture::NORMAL`,
    // `ofbx::Texture::COUNT`.

    for (int i = 0; i < ofbx_mesh_count; i++)
    {
        const ofbx::Mesh* const mesh = ofbx_iscene->getMesh(i);
        ASSERT_NE(mesh, nullptr);

        const ofbx::Geometry* const geometry = mesh->getGeometry();
        ASSERT_NE(geometry, nullptr);

        const ofbx::Vec3* const vertices = geometry->getVertices();

        const int vertex_count = geometry->getVertexCount();
        ASSERT_GE(vertex_count, 0);

        const ofbx::Vec3* const normals = geometry->getNormals();

        const ofbx::Vec2* const uvs = geometry->getUVs();

        const ofbx::Vec4* const colors = geometry->getColors();

        const ofbx::Vec3* const tangents = geometry->getTangents();

        const ofbx::Skin* const skin = geometry->getSkin();

        const int* const materials = geometry->getMaterials();

        const ofbx::Matrix geometric_matrix = mesh->getGeometricMatrix();

        const int material_count = mesh->getMaterialCount();
        ASSERT_GT(material_count, 0);

        for (int j = 0; j < material_count; j++)
        {
            const ofbx::Material* const material = mesh->getMaterial(j);
            ASSERT_NE(material, nullptr);

            const ofbx::Object::Type material_type = material->s_type;
            ASSERT_EQ(material_type, ofbx::Object::Type::MATERIAL);

            const ofbx::Texture* const diffuse_texture = material->getTexture(ofbx::Texture::DIFFUSE);
            if (diffuse_texture != nullptr)
            {
                const ofbx::DataView dataview_filename = diffuse_texture->getFileName();
                const ofbx::DataView dataview_rel_filename = diffuse_texture->getRelativeFileName();
            }

            const ofbx::Texture* const normal_texture = material->getTexture(ofbx::Texture::NORMAL);

            const ofbx::Texture* const count_texture = material->getTexture(ofbx::Texture::COUNT);

            const ofbx::Color color = material->getDiffuseColor();

            const ofbx::Object* const parent = material->getParent();
            ASSERT_NE(parent, nullptr);

            const ofbx::RotationOrder rotation_order = material->getRotationOrder();
            ASSERT_EQ(rotation_order, ofbx::RotationOrder::EULER_XYZ);
        }

        // Base struct `Object` functions for `const ofbx::Mesh* mesh`.

        const ofbx::RotationOrder rotation_order = mesh->getRotationOrder();
        ASSERT_EQ(rotation_order, ofbx::RotationOrder::EULER_XYZ);

        const bool mesh_is_node = mesh->isNode();
        ASSERT_TRUE(mesh_is_node);
    }

    const int ofbx_animation_stack_count = ofbx_iscene->getAnimationStackCount();
    ASSERT_GT(ofbx_mesh_count, 0);

    const ofbx::Object* const* const ofbx_all_objects = ofbx_iscene->getAllObjects();
    ASSERT_NE(ofbx_all_objects, nullptr);

    const int all_object_count = ofbx_iscene->getAllObjectCount();
    ASSERT_GT(all_object_count, 0);
}

TEST(OpenFBX_must_function_appropriately, turbo_polizei)
{
    const std::string filename = "turbo_polizei.fbx";
    std::vector<uint8_t> data_vector = yli::file::binary_slurp(filename);
    ASSERT_EQ(data_vector.size(), 364972);                                // size of `turbo_polizei.fbx` in bytes.

    const u8* const data = reinterpret_cast<unsigned char*>(data_vector.data());
    ASSERT_NE(data, nullptr);

    const int size = data_vector.size();
    ASSERT_EQ(size, 364972);                                             // size of `turbo_polizei.fbx` in bytes.

    const ofbx::IScene* const ofbx_iscene = ofbx::load(data, size);
    ASSERT_NE(ofbx_iscene, nullptr);

    const ofbx::IElement* const ofbx_ielement = ofbx_iscene->getRootElement();
    ASSERT_NE(ofbx_ielement, nullptr);

    const ofbx::Object* const ofbx_object = ofbx_iscene->getRoot();
    ASSERT_NE(ofbx_object, nullptr);
    const ofbx::Object::Type ofbx_object_type = ofbx_object->getType();
    ASSERT_EQ(ofbx_object_type, ofbx::Object::Type::ROOT);

    const int ofbx_mesh_count = ofbx_iscene->getMeshCount();
    ASSERT_GT(ofbx_mesh_count, 0);

    // FBX file may contain several meshes (`ofbx::Mesh`).
    // Each mesh may have several materials (`ofbx::Material`).
    // Each material may have up to 3 textures (`ofbx::Texture`):
    // `ofbx::Texture::DIFFUSE`,
    // `ofbx::Texture::NORMAL`,
    // `ofbx::Texture::COUNT`.

    for (int i = 0; i < ofbx_mesh_count; i++)
    {
        const ofbx::Mesh* const mesh = ofbx_iscene->getMesh(i);
        ASSERT_NE(mesh, nullptr);

        const ofbx::Geometry* const geometry = mesh->getGeometry();
        ASSERT_NE(geometry, nullptr);

        const ofbx::Vec3* const vertices = geometry->getVertices();

        const int vertex_count = geometry->getVertexCount();
        ASSERT_GE(vertex_count, 0);

        const ofbx::Vec3* const normals = geometry->getNormals();

        const ofbx::Vec2* const uvs = geometry->getUVs();

        const ofbx::Vec4* const colors = geometry->getColors();

        const ofbx::Vec3* const tangents = geometry->getTangents();

        const ofbx::Skin* const skin = geometry->getSkin();

        const int* const materials = geometry->getMaterials();

        const ofbx::Matrix geometric_matrix = mesh->getGeometricMatrix();

        const int material_count = mesh->getMaterialCount();
        ASSERT_GT(material_count, 0);

        for (int j = 0; j < material_count; j++)
        {
            const ofbx::Material* const material = mesh->getMaterial(j);
            ASSERT_NE(material, nullptr);

            const ofbx::Object::Type material_type = material->s_type;
            ASSERT_EQ(material_type, ofbx::Object::Type::MATERIAL);

            const ofbx::Texture* const diffuse_texture = material->getTexture(ofbx::Texture::DIFFUSE);
            if (diffuse_texture != nullptr)
            {
                const ofbx::DataView dataview_filename = diffuse_texture->getFileName();
                const ofbx::DataView dataview_rel_filename = diffuse_texture->getRelativeFileName();
            }

            const ofbx::Texture* const normal_texture = material->getTexture(ofbx::Texture::NORMAL);

            const ofbx::Texture* const count_texture = material->getTexture(ofbx::Texture::COUNT);

            const ofbx::Color color = material->getDiffuseColor();

            const ofbx::Object* const parent = material->getParent();
            ASSERT_NE(parent, nullptr);

            const ofbx::RotationOrder rotation_order = material->getRotationOrder();
            ASSERT_EQ(rotation_order, ofbx::RotationOrder::EULER_XYZ);
        }

        // Base struct `Object` functions for `const ofbx::Mesh* mesh`.

        const ofbx::RotationOrder rotation_order = mesh->getRotationOrder();
        ASSERT_EQ(rotation_order, ofbx::RotationOrder::EULER_XYZ);

        const bool mesh_is_node = mesh->isNode();
        ASSERT_TRUE(mesh_is_node);
    }

    const int ofbx_animation_stack_count = ofbx_iscene->getAnimationStackCount();
    ASSERT_GT(ofbx_mesh_count, 0);

    const ofbx::Object* const* ofbx_all_objects = ofbx_iscene->getAllObjects();
    ASSERT_NE(ofbx_all_objects, nullptr);

    const int all_object_count = ofbx_iscene->getAllObjectCount();
    ASSERT_GT(all_object_count, 0);
}

TEST(fbx_file_must_be_loaded_appropriately, rigged_and_animated_cat)
{
    const std::string filename = "cat.fbx";
    std::vector<glm::vec3> out_vertices;
    std::vector<glm::vec2> out_UVs;
    std::vector<glm::vec3> out_normals;

    const int32_t mesh_i = 0;

    const bool is_debug_mode = false; // Travis fails for too much output.

    const bool result = yli::loaders::load_FBX(filename, mesh_i, out_vertices, out_UVs, out_normals, is_debug_mode);
    ASSERT_TRUE(result);
}

TEST(fbx_file_must_be_loaded_appropriately, freight_train)
{
    const std::string filename = "freight_train.fbx";
    std::vector<uint8_t> data_vector = yli::file::binary_slurp(filename);
    ASSERT_EQ(data_vector.size(), 426124);                                // size of `freight_train.fbx` in bytes.

    const u8* const data = reinterpret_cast<unsigned char*>(data_vector.data());
    ASSERT_NE(data, nullptr);

    const int size = data_vector.size();
    ASSERT_EQ(size, 426124);                                             // size of `freight_train.fbx` in bytes.

    const ofbx::IScene* const ofbx_iscene = ofbx::load(data, size);
    ASSERT_NE(ofbx_iscene, nullptr);

    const ofbx::IElement* const ofbx_ielement = ofbx_iscene->getRootElement();
    ASSERT_NE(ofbx_ielement, nullptr);

    const ofbx::Object* const ofbx_object = ofbx_iscene->getRoot();
    ASSERT_NE(ofbx_object, nullptr);
    const ofbx::Object::Type ofbx_object_type = ofbx_object->getType();
    ASSERT_EQ(ofbx_object_type, ofbx::Object::Type::ROOT);

    const int ofbx_mesh_count = ofbx_iscene->getMeshCount();
    ASSERT_GT(ofbx_mesh_count, 0);

    // FBX file may contain several meshes (`ofbx::Mesh`).
    // Each mesh may have several materials (`ofbx::Material`).
    // Each material may have up to 3 textures (`ofbx::Texture`):
    // `ofbx::Texture::DIFFUSE`,
    // `ofbx::Texture::NORMAL`,
    // `ofbx::Texture::COUNT`.

    for (int i = 0; i < ofbx_mesh_count; i++)
    {
        const ofbx::Mesh* const mesh = ofbx_iscene->getMesh(i);
        ASSERT_NE(mesh, nullptr);

        const ofbx::Geometry* const geometry = mesh->getGeometry();
        ASSERT_NE(geometry, nullptr);

        const ofbx::Vec3* const vertices = geometry->getVertices();

        const int vertex_count = geometry->getVertexCount();
        ASSERT_GE(vertex_count, 0);

        const ofbx::Vec3* const normals = geometry->getNormals();

        const ofbx::Vec2* const uvs = geometry->getUVs();

        const ofbx::Vec4* const colors = geometry->getColors();

        const ofbx::Vec3* const tangents = geometry->getTangents();

        const ofbx::Skin* const skin = geometry->getSkin();

        const int* const materials = geometry->getMaterials();

        const ofbx::Matrix geometric_matrix = mesh->getGeometricMatrix();

        const int material_count = mesh->getMaterialCount();
        ASSERT_GT(material_count, 0);

        for (int j = 0; j < material_count; j++)
        {
            const ofbx::Material* const material = mesh->getMaterial(j);
            ASSERT_NE(material, nullptr);

            const ofbx::Object::Type material_type = material->s_type;
            ASSERT_EQ(material_type, ofbx::Object::Type::MATERIAL);

            const ofbx::Texture* const diffuse_texture = material->getTexture(ofbx::Texture::DIFFUSE);
            if (diffuse_texture != nullptr)
            {
                const ofbx::DataView dataview_filename = diffuse_texture->getFileName();
                const ofbx::DataView dataview_rel_filename = diffuse_texture->getRelativeFileName();
            }

            const ofbx::Texture* const normal_texture = material->getTexture(ofbx::Texture::NORMAL);

            const ofbx::Texture* const count_texture = material->getTexture(ofbx::Texture::COUNT);

            const ofbx::Color color = material->getDiffuseColor();

            const ofbx::Object* const parent = material->getParent();
            ASSERT_NE(parent, nullptr);

            const ofbx::RotationOrder rotation_order = material->getRotationOrder();
            ASSERT_EQ(rotation_order, ofbx::RotationOrder::EULER_XYZ);
        }

        // Base struct `Object` functions for `const ofbx::Mesh* mesh`.

        const ofbx::RotationOrder rotation_order = mesh->getRotationOrder();
        ASSERT_EQ(rotation_order, ofbx::RotationOrder::EULER_XYZ);

        const bool mesh_is_node = mesh->isNode();
        ASSERT_TRUE(mesh_is_node);
    }

    const int ofbx_animation_stack_count = ofbx_iscene->getAnimationStackCount();
    ASSERT_GT(ofbx_mesh_count, 0);

    const ofbx::Object* const* ofbx_all_objects = ofbx_iscene->getAllObjects();
    ASSERT_NE(ofbx_all_objects, nullptr);

    const int all_object_count = ofbx_iscene->getAllObjectCount();
    ASSERT_GT(all_object_count, 0);
}
