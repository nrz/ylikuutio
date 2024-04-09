// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2024 Antti Nuortimo.
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
#include "code/hirvi/hirvi.hpp"
#include "code/ylikuutio/memory/constructible_module.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"
#include "code/ylikuutio/ontology/pipeline_struct.hpp"
#include "code/ylikuutio/ontology/material_struct.hpp"

// Include standard headers
#include <cstddef> // uintptr_t

namespace yli::ontology
{
    class Scene;
    class Pipeline;
}

TEST(material_must_be_initialized_appropriately, hirvi_material)
{
    const int argc { 0 };
    const char** const argv { nullptr };
    hirvi::HirviApplication hirvi_application(argc, argv);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.global_name = "helsinki_east_downtown_scene";
    scene_struct.light_position = { 0.0f, 100000.0f, 100000.0f, 1.0f };
    scene_struct.water_level = 0.9f;
    yli::ontology::Scene* const helsinki_east_downtown_scene = hirvi_application.entity_factory.create_scene(scene_struct);

    yli::ontology::PipelineStruct helsinki_east_downtown_pipeline_struct;
    helsinki_east_downtown_pipeline_struct.parent = helsinki_east_downtown_scene;
    helsinki_east_downtown_pipeline_struct.global_name = "helsinki_east_downtown_pipeline";
    helsinki_east_downtown_pipeline_struct.local_name = "helsinki_regular_pipeline";
    helsinki_east_downtown_pipeline_struct.vertex_shader = "standard_shading.vert";
    helsinki_east_downtown_pipeline_struct.fragment_shader = "standard_shading.frag";
    yli::ontology::Pipeline* const helsinki_east_downtown_pipeline = hirvi_application.entity_factory.create_pipeline(helsinki_east_downtown_pipeline_struct);

    yli::ontology::MaterialStruct orange_fur_material_struct;
    orange_fur_material_struct.parent = helsinki_east_downtown_scene;
    orange_fur_material_struct.pipeline = helsinki_east_downtown_pipeline;
    orange_fur_material_struct.texture_file_format = "png";
    orange_fur_material_struct.texture_filename = "orange_fur_texture.png";
    yli::ontology::Material* const orange_fur_material = hirvi_application.entity_factory.create_material(orange_fur_material_struct);
    ASSERT_NE(orange_fur_material, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(orange_fur_material) % alignof(yli::ontology::Material), 0);
    yli::memory::ConstructibleModule orange_fur_material_constructible_module = orange_fur_material->get_constructible_module();
    ASSERT_EQ(orange_fur_material_constructible_module.storage_i, 0);
    ASSERT_EQ(orange_fur_material_constructible_module.slot_i, 0);
    ASSERT_EQ(orange_fur_material_constructible_module.alive, true);
}
