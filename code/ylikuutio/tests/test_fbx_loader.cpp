// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2026 Antti Nuortimo.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "gtest/gtest.h"
#include "code/ylikuutio/load/fbx_model_loader.hpp"
#include "code/ylikuutio/load/fbx_symbiosis_loader.hpp"
#include "code/ylikuutio/load/create_fbx_scene.hpp"
#include "code/ylikuutio/load/fbx_scene.hpp"
#include "code/ylikuutio/load/fbx_material.hpp"
#include "code/ylikuutio/load/fbx_mesh.hpp"
#include <ufbx.h>

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <cstdint>  // std::int32_t
#include <string>   // std::string
#include <vector>   // std::vector

TEST(fbx_file_loading_with_ufbx_must_function_appropriately, rigged_and_animated_cat)
{
    const std::string filename = "cat.fbx";

    constexpr ufbx_load_opts opts {
        .evaluate_skinning = true,
        .load_external_files = true,
        .ignore_missing_external_files = true,
        .generate_missing_normals = true,
        .target_axes = {
            .right = UFBX_COORDINATE_AXIS_NEGATIVE_Y,
            .up = UFBX_COORDINATE_AXIS_POSITIVE_Z,
            .front = UFBX_COORDINATE_AXIS_POSITIVE_X
        },
        .target_unit_meters = 1.0f
    };

    ufbx_error error;
    const ufbx_scene* const scene = ufbx_load_file(filename.c_str(), &opts, &error);

    ASSERT_NE(scene, nullptr);

    constexpr std::size_t subdivision_level { 1 };
    constexpr bool needs_subdivision { true };
    constexpr bool is_debug_mode { false };
    const std::optional<yli::load::FbxScene> maybe_fbx_scene = yli::load::create_fbx_scene(*scene, subdivision_level, needs_subdivision, is_debug_mode);

    ASSERT_TRUE(maybe_fbx_scene.has_value());

    const yli::load::FbxScene& fbx_scene = maybe_fbx_scene.value();

    std::cout << "fbx_scene.nodes.size(): " << fbx_scene.nodes.size() << "\n";

    std::size_t mesh_count = fbx_scene.meshes.size();
    ASSERT_EQ(mesh_count, 1);
}

TEST(ufbx_must_function_appropriately, rigged_and_animated_cat)
{
    const std::string filename = "cat.fbx";
    std::vector<std::vector<glm::vec3>> out_vertices;
    std::vector<std::vector<glm::vec2>> out_uvs;
    std::vector<std::vector<glm::vec3>> out_normals;
    std::unordered_map<std::size_t, std::vector<std::size_t>> fbx_material_mesh_map;
    std::vector<yli::load::FbxMaterial> fbx_materials;
    std::vector<yli::load::FbxMesh> fbx_meshes;
    std::size_t mesh_count { 0 };
    const bool is_debug_mode = true; // Travis fails for too much output.

    const bool result = yli::load::load_fbx(filename, out_vertices, out_uvs, out_normals,
                                            fbx_material_mesh_map, fbx_materials, fbx_meshes, mesh_count, is_debug_mode);
    ASSERT_TRUE(result);
    ASSERT_EQ(fbx_meshes.size(), 1);
    ASSERT_EQ(mesh_count, 1);

    // FBX file may contain several meshes.
    // Each mesh may have several materials (`ofbx::Material`).
    // Each material may have multiple textures, of which ufbx support at least the following:
    // 1. base factor
    // 2. base color
    // 3. specular factor
    // 4. specular color
    // 5. roughness
    // 6. metallic
    // 7. emission factor
    // 8. emission color

    for (std::size_t mesh_i = 0; mesh_i < mesh_count; mesh_i++)
    {
        ASSERT_EQ(mesh_i, 0);
        const yli::load::FbxMesh& mesh = fbx_meshes.at(mesh_i);

        // Mesh parts
        ASSERT_EQ(mesh.num_parts, 0); // `cat.fbx` has exactly 1 mesh that has exactly 0 mesh parts.
        ASSERT_EQ(mesh.parts.size(), 0);

        // AABB
        ASSERT_EQ(mesh.aabb_is_local, false);
        // ASSERT_EQ(mesh.aabb_min, glm::vec3 { 1.0f });
        // ASSERT_EQ(mesh.aabb_max, glm::vec3 { 1.0f });

        // Blend channels
        ASSERT_EQ(mesh.blend_channel_indices.size(), 0);

        // Bones
        ASSERT_EQ(mesh.bone_indices.size(), 0);
        ASSERT_EQ(mesh.bone_matrices.size(), 0);
        ASSERT_EQ(mesh.num_bones, 0); // `cat.fbx` has 0 bones.

        // Instance node indices
        ASSERT_EQ(mesh.instance_node_indices.size(), 0);

        // Checked with Blender, `cat.fbx` has 22648 faces that have indices 0 ... 22647.
        // 22648 * 6 = 135888.
        ASSERT_EQ(mesh.vertices.size(), 135888); // The only mesh of `cat.fbx` has 135888 vertices.
    }
}

TEST(fbx_file_must_be_loaded_appropriately, rigged_and_animated_cat)
{
    const std::string filename = "cat.fbx";
    std::vector<glm::vec3> out_vertices;
    std::vector<glm::vec2> out_uvs;
    std::vector<glm::vec3> out_normals;

    const std::int32_t mesh_i = 0;

    const bool is_debug_mode = true; // Travis fails for too much output.

    const bool result = yli::load::load_fbx(filename, mesh_i, out_vertices, out_uvs, out_normals, is_debug_mode);
    ASSERT_TRUE(result);
}

TEST(fbx_file_must_be_loaded_appropriately, turbo_polizei)
{
    const std::string filename = "turbo_polizei_png_textures.fbx";
    std::vector<glm::vec3> out_vertices;
    std::vector<glm::vec2> out_uvs;
    std::vector<glm::vec3> out_normals;

    const std::int32_t mesh_i = 0;

    const bool is_debug_mode = true; // Travis fails for too much output.

    const bool result = yli::load::load_fbx(filename, mesh_i, out_vertices, out_uvs, out_normals, is_debug_mode);
    ASSERT_TRUE(result);
}
