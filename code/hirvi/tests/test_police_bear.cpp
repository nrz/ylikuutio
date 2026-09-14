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
#include "code/hirvi/ontology/police_bear.hpp"
#include "code/hirvi/ontology/hirvi_scene_struct.hpp"
#include "code/hirvi/ontology/police_control_center_struct.hpp"
#include "code/hirvi/ontology/police_bear_struct.hpp"
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

TEST(police_bear_must_be_initialized_appropriately, hirvi_police_bear)
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
    MovableController* const rest_movable_controller = hirvi_application.get_entity_factory().create_movable_controller(
        rest_movable_controller_struct);

    PipelineStruct helsinki_pipeline_struct { Request<Scene>(helsinki_scene) };
    helsinki_pipeline_struct.global_name = "helsinki_pipeline";
    helsinki_pipeline_struct.local_name = "helsinki_regular_pipeline";
    helsinki_pipeline_struct.vertex_shader = "standard_shading.vert";
    helsinki_pipeline_struct.fragment_shader = "standard_shading.frag";
    Pipeline* const helsinki_pipeline =
            hirvi_application.get_entity_factory().create_pipeline(helsinki_pipeline_struct);

    SymbiosisStruct police_bear_png_symbiosis_struct { Request<Scene>(helsinki_scene), Request(helsinki_pipeline) };
    police_bear_png_symbiosis_struct.model_file_format = "fbx";
    police_bear_png_symbiosis_struct.model_filename = "bear_animated.fbx";
    Symbiosis* const police_bear_png_symbiosis = hirvi_application.get_entity_factory().create_symbiosis(
        police_bear_png_symbiosis_struct);
    ASSERT_EQ(police_bear_png_symbiosis->get_number_of_ufbx_meshes(), 3); // To ensure proper loading of `Symbiosis`.

    const GenericParentModule* const parent_of_symbiont_materials =
            police_bear_png_symbiosis->get_generic_parent_module<SymbiontMaterial>();
    ASSERT_NE(parent_of_symbiont_materials, nullptr);

    PoliceBearStruct police_bear_png_police_bear_struct1 {
        Request<Scene>(helsinki_scene), Request(rest_movable_controller), Request(police_bear_png_symbiosis)
    };
    police_bear_png_police_bear_struct1.initial_rotate_vectors = { glm::vec3(0.0f, 1.0f, 1.0f) };
    police_bear_png_police_bear_struct1.initial_rotate_angles = { static_cast<float>(std::numbers::pi) };
    police_bear_png_police_bear_struct1.original_scale_vector = glm::vec3(1.0f, 1.0f, 1.0f);
    police_bear_png_police_bear_struct1.cartesian_coordinates = CartesianCoordinatesModule(85.00f, 30.00f, 160.00f);
    LocomotionModuleStruct police_bear1_walk_struct(1.0f); // 3.6 km/h.
    LocomotionModuleStruct police_bear1_trot_struct(5.0f);
    LocomotionModuleStruct police_bear1_canter_struct(10.0f);
    LocomotionModuleStruct police_bear1_gallop_struct(12.5f); // 45 km/h.

    ASSERT_FALSE(hirvi_application.has_memory_allocator(hirvi::data::HOLOBIONT));
    ASSERT_FALSE(hirvi_application.has_memory_allocator(hirvi::data::BIONT));
    ASSERT_FALSE(hirvi_application.has_memory_allocator(hirvi::data::POLICE_BEAR));

    auto* const police_bear1 = hirvi_application.get_entity_factory().create_holobiont_derivative<
        PoliceBear,
        hirvi::core::PoliceBearMemoryAllocator,
        HirviScene,
        PoliceBearStruct>(
        hirvi::data::POLICE_BEAR,
        Request(helsinki_scene),
        police_bear_png_police_bear_struct1,
        helsinki_non_emancipated_control_center->get_generic_master_module<Movable>(),
        police_bear1_walk_struct,
        police_bear1_trot_struct,
        police_bear1_canter_struct,
        police_bear1_gallop_struct);
    ASSERT_NE(police_bear1, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(police_bear1) % alignof(hirvi::ontology::PoliceBear), 0);

    ASSERT_FALSE(hirvi_application.has_memory_allocator(hirvi::data::HOLOBIONT));
    ASSERT_TRUE(hirvi_application.has_memory_allocator(hirvi::data::POLICE_BEAR));
    ASSERT_TRUE(hirvi_application.has_memory_allocator(hirvi::data::BIONT));

    const GenericParentModule* const parent_of_bionts = police_bear1->get_generic_parent_module<Biont>();
    ASSERT_NE(parent_of_bionts, nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(hirvi_application.get_universe().get_number_of_non_variable_children(),
              2); // Helsinki `Scene`, `CallbackEngine`.

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(helsinki_scene->get_scene(), helsinki_scene);
    ASSERT_EQ(helsinki_scene->get_number_of_non_variable_children(),
              7); // Default `Camera`, `MovableController`, `Pipeline`, `Symbiosis`, 2 `PoliceControlCenter`s, `police_bear1`

    // `Entity` member functions of `Pipeline`.
    ASSERT_EQ(helsinki_pipeline->get_scene(), helsinki_scene);
    ASSERT_EQ(helsinki_pipeline->get_number_of_non_variable_children(), 0);

    // `Entity` member functions of `Symbiosis`.
    ASSERT_EQ(police_bear_png_symbiosis->get_scene(), helsinki_scene);
    ASSERT_EQ(police_bear_png_symbiosis->get_number_of_non_variable_children(), 3); // 3 `SymbiontMaterial`s.

    // `Entity` member functions.
    ASSERT_EQ(police_bear1->get_childID(), 0);
    ASSERT_EQ(police_bear1->get_type(), "hirvi::ontology::PoliceBear*");
    ASSERT_TRUE(police_bear1->get_can_be_erased());
    ASSERT_EQ(police_bear1->get_scene(), helsinki_scene);
    ASSERT_EQ(police_bear1->get_parent(), helsinki_scene);
    ASSERT_EQ(police_bear1->get_number_of_non_variable_children(), 3); // 3 `Biont`s.

    // Even though `PoliceBear` is derived from `Holobiont`, `PoliceBear` should be allocated using its own allocator.
    yli::memory::MemoryAllocator<PoliceBear*>& police_bear_memory_allocator =
            hirvi_application.get_memory_allocator<PoliceBear*>(hirvi::data::POLICE_BEAR);
    // `PoliceBear` should be allocated using its own allocator.
    ASSERT_EQ(police_bear_memory_allocator.get_number_of_storages(), 1);
    ASSERT_EQ(police_bear_memory_allocator.get_number_of_instances(), 1);
    // The `Biont`s of the `PoliceBear` should be allocated using the `Biont` allocator.
    yli::memory::MemoryAllocator<Biont*>& biont_memory_allocator = hirvi_application.get_memory_allocator<Biont*>(
        hirvi::data::BIONT);
    ASSERT_EQ(biont_memory_allocator.get_number_of_storages(), 1);
    ASSERT_EQ(biont_memory_allocator.get_number_of_instances(), 3);

    const yli::memory::ConstructibleModule police_bear1_constructible_module =
            police_bear1->get_constructible_module();
    ASSERT_EQ(police_bear1_constructible_module.storage_i, 0);
    ASSERT_EQ(police_bear1_constructible_module.slot_i, 0);
    ASSERT_EQ(police_bear1_constructible_module.alive, true);
}
