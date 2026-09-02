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
#include "code/hirvi/hirvi.hpp"
#include "code/hirvi/ontology/hirvi_scene.hpp"
#include "code/hirvi/ontology/hirvi_scene_struct.hpp"
#include "code/hirvi/ontology/police_control_center_struct.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/symbiosis.hpp"
#include "code/ylikuutio/ontology/request.hpp"
#include "code/ylikuutio/ontology/pipeline_struct.hpp"
#include "code/ylikuutio/ontology/symbiosis_struct.hpp"

// Include standard headers
#include <cstdint> // uintptr_t

namespace yli::ontology
{
    class Scene;
    class Pipeline;
}

TEST(symbiosis_must_be_initialized_appropriately, hirvi_symbiosis)
{
    using namespace hirvi::ontology;
    using namespace yli::ontology;

    constexpr int argc { 0 };
    const char** const argv { nullptr };
    const hirvi::HirviApplication hirvi_application(argc, argv);

    PoliceControlCenterStruct helsinki_non_emancipated_control_center_struct;
    helsinki_non_emancipated_control_center_struct.global_name = "helsinki_non_emancipated_control_center";
    helsinki_non_emancipated_control_center_struct.local_name = "non_emancipated_control_center";
    PoliceControlCenterStruct helsinki_emancipated_control_center_struct;
    helsinki_emancipated_control_center_struct.global_name = "helsinki_emancipated_control_center";
    helsinki_emancipated_control_center_struct.local_name = "emancipated_control_center";
    HirviSceneStruct hirvi_scene_struct;
    hirvi_scene_struct.global_name = "helsinki_scene";
    hirvi_scene_struct.light_position = { 0.0f, -100000.0f, 100000.0f, 1.0f };
    hirvi_scene_struct.water_level = 0.9f;
    hirvi_scene_struct.police_control_center_structs = {
        helsinki_non_emancipated_control_center_struct, helsinki_emancipated_control_center_struct
    };
    HirviScene* const helsinki_scene = hirvi_application.get_entity_factory().create_scene_derivative<
        HirviScene,
        hirvi::core::HirviSceneMemoryAllocator,
        HirviSceneStruct>(
        hirvi::data::HIRVI_SCENE,
        hirvi_scene_struct,
        hirvi_application.core);

    PipelineStruct helsinki_pipeline_struct { Request<Scene>(helsinki_scene) };
    helsinki_pipeline_struct.global_name = "helsinki_pipeline";
    helsinki_pipeline_struct.local_name = "helsinki_regular_pipeline";
    helsinki_pipeline_struct.vertex_shader = "standard_shading.vert";
    helsinki_pipeline_struct.fragment_shader = "standard_shading.frag";
    Pipeline* const helsinki_pipeline =
            hirvi_application.get_entity_factory().create_pipeline(helsinki_pipeline_struct);

    SymbiosisStruct turbo_polizei_png_symbiosis_struct { Request<Scene>(helsinki_scene), Request(helsinki_pipeline) };
    turbo_polizei_png_symbiosis_struct.model_file_format = "fbx";
    turbo_polizei_png_symbiosis_struct.model_filename = "turbo_polizei_png_textures.fbx";
    Symbiosis* const turbo_polizei_png_symbiosis = hirvi_application.get_entity_factory().create_symbiosis(
        turbo_polizei_png_symbiosis_struct);
    ASSERT_NE(turbo_polizei_png_symbiosis, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(turbo_polizei_png_symbiosis) % alignof(Symbiosis), 0);
    ASSERT_EQ(turbo_polizei_png_symbiosis->get_number_of_ufbx_meshes(), 5);

    const yli::memory::ConstructibleModule symbiosis_constructible_module =
            turbo_polizei_png_symbiosis->get_constructible_module();
    ASSERT_EQ(symbiosis_constructible_module.storage_i, 0);
    ASSERT_EQ(symbiosis_constructible_module.slot_i, 0);
    ASSERT_EQ(symbiosis_constructible_module.alive, true);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(hirvi_application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(hirvi_application.get_universe().get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Pipeline`.
    ASSERT_EQ(helsinki_pipeline->get_scene(), helsinki_scene);
    ASSERT_EQ(helsinki_pipeline->get_number_of_non_variable_children(), 0);

    ASSERT_EQ(turbo_polizei_png_symbiosis->apprentice_of_pipeline.get_master(), helsinki_pipeline);
    ASSERT_EQ(turbo_polizei_png_symbiosis->apprentice_of_pipeline.get_apprenticeID(), 0);

    // `Entity` member functions.
    ASSERT_EQ(turbo_polizei_png_symbiosis->get_childID(), 0);
    ASSERT_EQ(turbo_polizei_png_symbiosis->get_type(), "yli::ontology::Symbiosis*");
    ASSERT_TRUE(turbo_polizei_png_symbiosis->get_can_be_erased());
    ASSERT_EQ(turbo_polizei_png_symbiosis->get_scene(), helsinki_scene);
    ASSERT_EQ(turbo_polizei_png_symbiosis->get_parent(), helsinki_scene);
    ASSERT_EQ(turbo_polizei_png_symbiosis->get_number_of_non_variable_children(), 8);
}
