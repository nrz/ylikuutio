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
#include "code/hirvi/data/datatype.hpp"
#include "code/hirvi/ontology/hirvi_scene.hpp"
#include "code/hirvi/ontology/police_control_center.hpp"
#include "code/hirvi/ontology/police_train.hpp"
#include "code/hirvi/ontology/hirvi_scene_struct.hpp"
#include "code/hirvi/ontology/police_control_center_struct.hpp"
#include "code/hirvi/ontology/police_train_struct.hpp"
#include "code/ylikuutio/snippets/movable_controller_snippets.hpp"
#include "code/ylikuutio/ontology/callback_engine.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/biont.hpp"
#include "code/ylikuutio/ontology/cartesian_coordinates_module.hpp"
#include "code/ylikuutio/ontology/request.hpp"
#include "code/ylikuutio/ontology/movable_controller_struct.hpp"
#include "code/ylikuutio/ontology/pipeline_struct.hpp"
#include "code/ylikuutio/ontology/symbiosis_struct.hpp"
#include "code/ylikuutio/ontology/locomotion_module_struct.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstdint> // uintptr_t
#include <numbers> // std::numbers::pi

namespace yli::ontology
{
    class MovableController;
    class Movable;
    class Pipeline;
    class Symbiosis;
}

TEST(police_train_must_be_initialized_appropriately, hirvi_police_train)
{
    using namespace hirvi::ontology;
    using namespace yli::ontology;

    constexpr int argc { 0 };
    const char** const argv { nullptr };
    hirvi::HirviApplication hirvi_application(argc, argv);

    PoliceControlCenterStruct helsinki_non_emancipated_control_center_struct;
    helsinki_non_emancipated_control_center_struct.global_name = "helsinki_non_emancipated_control_center";
    helsinki_non_emancipated_control_center_struct.local_name = "non_emancipated_control_center";
    PoliceControlCenterStruct helsinki_emancipated_control_center_struct;
    helsinki_emancipated_control_center_struct.global_name = "helsinki_emancipated_control_center";
    helsinki_emancipated_control_center_struct.local_name = "emancipated_control_center";
    HirviSceneStruct scene_struct;
    scene_struct.global_name = "helsinki_scene";
    scene_struct.light_position = { 0.0f, -100000.0f, 100000.0f, 1.0f };
    scene_struct.water_level = 0.9f;
    scene_struct.police_control_center_structs = {
        helsinki_non_emancipated_control_center_struct, helsinki_emancipated_control_center_struct
    };
    HirviScene* const helsinki_scene = hirvi_application.get_entity_factory().create_scene_derivative<
        HirviScene,
        hirvi::core::HirviSceneMemoryAllocator,
        HirviSceneStruct>(
        hirvi::data::HIRVI_SCENE,
        scene_struct,
        hirvi_application.core);

    const auto helsinki_non_emancipated_control_center = dynamic_cast<PoliceControlCenter*>(
        helsinki_scene->get_entity("non_emancipated_control_center"));

    CallbackEngineStruct rest_callback_engine_struct;
    auto rest_callback_engine = hirvi_application.get_entity_factory().create_callback_engine(
        rest_callback_engine_struct);
    rest_callback_engine->create_callback_object(&yli::snippets::rest);

    MovableControllerStruct rest_movable_controller_struct {
        Request<Scene>(helsinki_scene), Request(rest_callback_engine)
    };
    rest_movable_controller_struct.global_name = "rest_movable_controller";
    rest_movable_controller_struct.local_name = "rest";
    MovableController* const rest_movable_controller = hirvi_application.get_entity_factory().
            create_movable_controller(rest_movable_controller_struct);

    PipelineStruct helsinki_pipeline_struct { Request<Scene>(helsinki_scene) };
    helsinki_pipeline_struct.global_name = "helsinki_pipeline";
    helsinki_pipeline_struct.local_name = "helsinki_regular_pipeline";
    helsinki_pipeline_struct.vertex_shader = "standard_shading.vert";
    helsinki_pipeline_struct.fragment_shader = "standard_shading.frag";
    Pipeline* const helsinki_pipeline =
            hirvi_application.get_entity_factory().create_pipeline(helsinki_pipeline_struct);

    SymbiosisStruct turbo_polizei_png_symbiosis_struct { Request<Scene>(helsinki_scene), Request(helsinki_pipeline) };
    turbo_polizei_png_symbiosis_struct.model_file_format = "fbx";
    turbo_polizei_png_symbiosis_struct.model_filename ="turbo_polizei_png_textures.fbx";
    Symbiosis* const turbo_polizei_png_symbiosis = hirvi_application.get_entity_factory().
            create_symbiosis(turbo_polizei_png_symbiosis_struct);
    ASSERT_EQ(turbo_polizei_png_symbiosis->get_number_of_ufbx_meshes(), 5); // To ensure proper loading of `Symbiosis`.

    const GenericParentModule* const parent_of_symbiont_materials =
            turbo_polizei_png_symbiosis->get_generic_parent_module<SymbiontMaterial>();
    ASSERT_NE(parent_of_symbiont_materials, nullptr);

    PoliceTrainStruct turbo_polizei_png_police_train_struct1 {
        Request<Scene>(helsinki_scene), Request(rest_movable_controller), Request(turbo_polizei_png_symbiosis)
    };
    turbo_polizei_png_police_train_struct1.initial_rotate_vectors = { glm::vec3(0.0f, 1.0f, 1.0f) };
    turbo_polizei_png_police_train_struct1.initial_rotate_angles = { static_cast<float>(std::numbers::pi) };
    turbo_polizei_png_police_train_struct1.original_scale_vector = glm::vec3(1.0f, 1.0f, 1.0f);
    turbo_polizei_png_police_train_struct1.cartesian_coordinates = CartesianCoordinatesModule(85.00f, 30.00f, 160.00f);
    LocomotionModuleStruct road_vehicle_struct1;

    ASSERT_FALSE(hirvi_application.has_memory_allocator(hirvi::data::HOLOBIONT));
    ASSERT_FALSE(hirvi_application.has_memory_allocator(hirvi::data::BIONT));
    ASSERT_FALSE(hirvi_application.has_memory_allocator(hirvi::data::POLICE_TRAIN));

    auto* const turbo_polizei1 = hirvi_application.get_entity_factory().create_holobiont_derivative<
        PoliceTrain,
        hirvi::core::PoliceTrainMemoryAllocator,
        HirviScene,
        PoliceTrainStruct>(
        hirvi::data::POLICE_TRAIN,
        Request(helsinki_scene),
        turbo_polizei_png_police_train_struct1,
        helsinki_non_emancipated_control_center->get_generic_master_module<Movable>(),
        road_vehicle_struct1);
    ASSERT_NE(turbo_polizei1, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(turbo_polizei1) % alignof(hirvi::ontology::PoliceTrain), 0);

    ASSERT_FALSE(hirvi_application.has_memory_allocator(hirvi::data::HOLOBIONT));
    ASSERT_TRUE(hirvi_application.has_memory_allocator(hirvi::data::POLICE_TRAIN));
    ASSERT_TRUE(hirvi_application.has_memory_allocator(hirvi::data::BIONT));

    const GenericParentModule* const parent_of_bionts = turbo_polizei1->get_generic_parent_module<Biont>();
    ASSERT_NE(parent_of_bionts, nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(hirvi_application.get_universe().get_number_of_non_variable_children(), 2); // Helsinki `Scene`, `CallbackEngine`.

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(helsinki_scene->get_scene(), helsinki_scene);
    ASSERT_EQ(helsinki_scene->get_number_of_non_variable_children(),
              7); // Default `Camera`, `MovableController`, `Pipeline`, `Symbiosis`, 2 `PoliceControlCenter`s, `turbo_polizei1`

    // `Entity` member functions of `Pipeline`.
    ASSERT_EQ(helsinki_pipeline->get_scene(), helsinki_scene);
    ASSERT_EQ(helsinki_pipeline->get_number_of_non_variable_children(), 0);

    // `Entity` member functions of `Symbiosis`.
    ASSERT_EQ(turbo_polizei_png_symbiosis->get_scene(), helsinki_scene);
    ASSERT_EQ(turbo_polizei_png_symbiosis->get_number_of_non_variable_children(), 8); // 8 `SymbiontMaterial`s.

    // `Entity` member functions.
    ASSERT_EQ(turbo_polizei1->get_childID(), 0);
    ASSERT_EQ(turbo_polizei1->get_type(), "hirvi::ontology::PoliceTrain*");
    ASSERT_TRUE(turbo_polizei1->get_can_be_erased());
    ASSERT_EQ(turbo_polizei1->get_scene(), helsinki_scene);
    ASSERT_EQ(turbo_polizei1->get_parent(), helsinki_scene);
    ASSERT_EQ(turbo_polizei1->get_number_of_non_variable_children(), 5); // 5 `Biont`s.

    // Even though `PoliceTrain` is derived from `Holobiont`. `PoliceTrain` should be allocated using its own allocator.
    yli::memory::MemoryAllocator<PoliceTrain*>& police_train_memory_allocator =
            hirvi_application.get_memory_allocator<PoliceTrain*>(hirvi::data::POLICE_TRAIN);
    // `PoliceTrain` should be allocated using its own allocator.
    ASSERT_EQ(police_train_memory_allocator.get_number_of_storages(), 1);
    ASSERT_EQ(police_train_memory_allocator.get_number_of_instances(), 1);
    // The `Biont`s of the `PoliceTrain` should be allocated using the `Biont` allocator.
    // There is 1 body + chassis `Biont`, and 4 wheel `Biont`s.
    yli::memory::MemoryAllocator<Biont*>& biont_memory_allocator = hirvi_application.get_memory_allocator<Biont*>(
        hirvi::data::BIONT);
    ASSERT_EQ(biont_memory_allocator.get_number_of_storages(), 1);
    ASSERT_EQ(biont_memory_allocator.get_number_of_instances(), 5);

    const yli::memory::ConstructibleModule turbo_polizei1_constructible_module =
            turbo_polizei1->get_constructible_module();
    ASSERT_EQ(turbo_polizei1_constructible_module.storage_i, 0);
    ASSERT_EQ(turbo_polizei1_constructible_module.slot_i, 0);
    ASSERT_EQ(turbo_polizei1_constructible_module.alive, true);
}
