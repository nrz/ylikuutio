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
#include "code/hirvi/ontology/train.hpp"
#include "code/hirvi/ontology/hirvi_scene_struct.hpp"
#include "code/hirvi/ontology/train_struct.hpp"
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
    class AbstractMovable;
    class Pipeline;
    class Symbiosis;
}

TEST(train_must_be_initialized_appropriately, hirvi_train)
{
    using namespace hirvi::ontology;
    using namespace yli::ontology;

    constexpr int argc { 0 };
    const char** const argv { nullptr };
    hirvi::HirviApplication hirvi_application(argc, argv);

    HirviSceneStruct scene_struct;
    scene_struct.global_name = "helsinki_scene";
    scene_struct.light_position = { 0.0f, -100000.0f, 100000.0f, 1.0f };
    scene_struct.water_level = 0.9f;
    HirviScene* const helsinki_scene = hirvi_application.get_entity_factory().create_scene_derivative<
        HirviScene,
        hirvi::core::HirviSceneMemoryAllocator,
        HirviSceneStruct>(
        hirvi::data::HIRVI_SCENE,
        scene_struct,
        hirvi_application.core);

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

    SymbiosisStruct train_symbiosis_struct { Request<Scene>(helsinki_scene), Request(helsinki_pipeline) };
    train_symbiosis_struct.model_file_format = "fbx";
    train_symbiosis_struct.model_filename ="turbo_polizei_png_textures.fbx";
    Symbiosis* const train_symbiosis = hirvi_application.get_entity_factory().
            create_symbiosis(train_symbiosis_struct);
    ASSERT_EQ(train_symbiosis->get_number_of_ufbx_meshes(), 5); // To ensure proper loading of `Symbiosis`.

    const GenericParentModule* const parent_of_symbiont_materials =
            train_symbiosis->get_generic_parent_module<SymbiontMaterial>();
    ASSERT_NE(parent_of_symbiont_materials, nullptr);

    TrainStruct train_struct {
        Request<Scene>(helsinki_scene), Request(rest_movable_controller), Request(train_symbiosis)
    };
    train_struct.initial_rotate_vectors = { glm::vec3(0.0f, 1.0f, 1.0f) };
    train_struct.initial_rotate_angles = { static_cast<float>(std::numbers::pi) };
    train_struct.original_scale_vector = glm::vec3(1.0f, 1.0f, 1.0f);
    train_struct.cartesian_coordinates = CartesianCoordinatesModule(85.00f, 30.00f, 160.00f);
    LocomotionModuleStruct rail_vehicle_struct(100.0f); // 360 km/h.

    ASSERT_FALSE(hirvi_application.has_memory_allocator(hirvi::data::HOLOBIONT));
    ASSERT_FALSE(hirvi_application.has_memory_allocator(hirvi::data::BIONT));
    ASSERT_FALSE(hirvi_application.has_memory_allocator(hirvi::data::TRAIN));

    auto* const train1 = hirvi_application.get_entity_factory().create_holobiont_derivative<
        Train,
        hirvi::core::TrainMemoryAllocator,
        HirviScene,
        TrainStruct>(
        hirvi::data::TRAIN,
        Request(helsinki_scene),
        train_struct,
        rail_vehicle_struct);
    ASSERT_NE(train1, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(train1) % alignof(hirvi::ontology::Train), 0);

    ASSERT_FALSE(hirvi_application.has_memory_allocator(hirvi::data::HOLOBIONT));
    ASSERT_TRUE(hirvi_application.has_memory_allocator(hirvi::data::TRAIN));
    ASSERT_TRUE(hirvi_application.has_memory_allocator(hirvi::data::BIONT));

    const GenericParentModule* const parent_of_bionts = train1->get_generic_parent_module<Biont>();
    ASSERT_NE(parent_of_bionts, nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(hirvi_application.get_universe().get_number_of_non_variable_children(), 2); // Helsinki `Scene`, `CallbackEngine`.

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(helsinki_scene->get_scene(), helsinki_scene);
    ASSERT_EQ(helsinki_scene->get_number_of_non_variable_children(),
              5); // Default `Camera`, `MovableController`, `Pipeline`, `Symbiosis`, `train1`

    // `Entity` member functions of `Pipeline`.
    ASSERT_EQ(helsinki_pipeline->get_scene(), helsinki_scene);
    ASSERT_EQ(helsinki_pipeline->get_number_of_non_variable_children(), 0);

    // `Entity` member functions of `Symbiosis`.
    ASSERT_EQ(train_symbiosis->get_scene(), helsinki_scene);
    ASSERT_EQ(train_symbiosis->get_number_of_non_variable_children(), 4); // 4 `SymbiontMaterial`s.

    // `Entity` member functions.
    ASSERT_EQ(train1->get_childID(), 0);
    ASSERT_EQ(train1->get_type(), "hirvi::ontology::Train*");
    ASSERT_TRUE(train1->get_can_be_erased());
    ASSERT_EQ(train1->get_scene(), helsinki_scene);
    ASSERT_EQ(train1->get_parent(), helsinki_scene);
    ASSERT_EQ(train1->get_number_of_non_variable_children(), 4); // 4 `Biont`s.

    // Even though `Train` is derived from `Holobiont`, `Train` should be allocated using its own allocator.
    yli::memory::MemoryAllocator<Train*>& train_memory_allocator =
            hirvi_application.get_memory_allocator<Train*>(hirvi::data::TRAIN);
    // `Train` should be allocated using its own allocator.
    ASSERT_EQ(train_memory_allocator.get_number_of_instances(), 1);
    // The `Biont`s of the `Train` should be allocated using the `Biont` allocator.
    yli::memory::MemoryAllocator<Biont*>& biont_memory_allocator = hirvi_application.get_memory_allocator<Biont*>(
        hirvi::data::BIONT);
    ASSERT_EQ(biont_memory_allocator.get_number_of_instances(), 4);

    const yli::memory::ConstructibleModule train1_constructible_module =
            train1->get_constructible_module();
    ASSERT_EQ(train1_constructible_module.slot_i, 0);
    ASSERT_EQ(train1_constructible_module.alive, true);
}
