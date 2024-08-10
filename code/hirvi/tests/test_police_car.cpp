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
#include "code/hirvi/cat.hpp"
#include "code/ylikuutio/snippets/brain_snippets.hpp"
#include "code/ylikuutio/ontology/callback_engine.hpp"
#include "code/ylikuutio/ontology/brain.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/pipeline.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/symbiosis.hpp"
#include "code/ylikuutio/ontology/holobiont.hpp"
#include "code/ylikuutio/ontology/biont.hpp"
#include "code/ylikuutio/ontology/cartesian_coordinates_module.hpp"
#include "code/ylikuutio/ontology/brain_struct.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"
#include "code/ylikuutio/ontology/pipeline_struct.hpp"
#include "code/ylikuutio/ontology/material_struct.hpp"
#include "code/ylikuutio/ontology/model_struct.hpp"
#include "code/ylikuutio/ontology/holobiont_struct.hpp"
#include "code/ylikuutio/ontology/locomotion_module_struct.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef> // uintptr_t
#include <numbers> // std::numbers::pi

TEST(police_car_must_be_initialized_appropriately, hirvi_police_car)
{
    const int argc { 0 };
    const char** const argv { nullptr };
    hirvi::HirviApplication hirvi_application(argc, argv);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.global_name = "helsinki_east_downtown_scene";
    scene_struct.light_position = { 0.0f, -100000.0f, 100000.0f, 1.0f };
    scene_struct.water_level = 0.9f;
    yli::ontology::Scene* const helsinki_east_downtown_scene = hirvi_application.entity_factory.create_scene(scene_struct);

    yli::ontology::CallbackEngineStruct rest_callback_engine_struct;
    auto rest_callback_engine = hirvi_application.entity_factory.create_callback_engine(rest_callback_engine_struct);
    rest_callback_engine->create_callback_object(&yli::snippets::rest);

    yli::ontology::BrainStruct rest_brain_struct;
    rest_brain_struct.parent = helsinki_east_downtown_scene;
    rest_brain_struct.global_name = "rest_brain";
    rest_brain_struct.local_name = "rest";
    rest_brain_struct.callback_engine = rest_callback_engine;
    yli::ontology::Brain* const rest_brain = hirvi_application.entity_factory.create_brain(rest_brain_struct);

    yli::ontology::PipelineStruct helsinki_east_downtown_pipeline_struct;
    helsinki_east_downtown_pipeline_struct.parent = helsinki_east_downtown_scene;
    helsinki_east_downtown_pipeline_struct.global_name = "helsinki_east_downtown_pipeline";
    helsinki_east_downtown_pipeline_struct.local_name = "helsinki_regular_pipeline";
    helsinki_east_downtown_pipeline_struct.vertex_shader = "standard_shading.vert";
    helsinki_east_downtown_pipeline_struct.fragment_shader = "standard_shading.frag";
    yli::ontology::Pipeline* const helsinki_east_downtown_pipeline = hirvi_application.entity_factory.create_pipeline(helsinki_east_downtown_pipeline_struct);

    yli::ontology::ModelStruct turbo_polizei_png_model_struct;
    turbo_polizei_png_model_struct.parent = helsinki_east_downtown_scene;
    turbo_polizei_png_model_struct.pipeline = helsinki_east_downtown_pipeline;
    turbo_polizei_png_model_struct.model_file_format = "fbx";
    turbo_polizei_png_model_struct.model_filename = "turbo_polizei_png_textures.fbx";
    yli::ontology::Symbiosis* const turbo_polizei_png_symbiosis = hirvi_application.entity_factory.create_symbiosis(turbo_polizei_png_model_struct);

    yli::ontology::HolobiontStruct turbo_polizei_png_police_car_struct1(*helsinki_east_downtown_scene, *turbo_polizei_png_symbiosis);
    turbo_polizei_png_police_car_struct1.brain = rest_brain;
    turbo_polizei_png_police_car_struct1.initial_rotate_vectors = { glm::vec3(0.0f, 1.0f, 1.0f) };
    turbo_polizei_png_police_car_struct1.initial_rotate_angles = { static_cast<float>(std::numbers::pi) };
    turbo_polizei_png_police_car_struct1.original_scale_vector = glm::vec3(1.0f, 1.0f, 1.0f);
    turbo_polizei_png_police_car_struct1.cartesian_coordinates = yli::ontology::CartesianCoordinatesModule(85.00f, 30.00f, 160.00f);
    yli::ontology::LocomotionModuleStruct road_vehicle_struct1;

    // Ensure that `Holobiont`'s memory allocation has no allocations before allocating this `PoliceCar` instance.
    yli::memory::MemoryAllocator<yli::ontology::Holobiont*>& holobiont_memory_allocator = hirvi_application.get_memory_allocator<yli::ontology::Holobiont*>(hirvi::Datatype::HOLOBIONT);
    ASSERT_EQ(holobiont_memory_allocator.get_number_of_storages(), 0);
    ASSERT_EQ(holobiont_memory_allocator.get_number_of_instances(), 0);
    // There should be no storages nor instances in `PoliceCar`'s memory allocator before the upcoming allocation.
    yli::memory::MemoryAllocator<hirvi::PoliceCar*>& police_car_memory_allocator = hirvi_application.get_memory_allocator<hirvi::PoliceCar*>(hirvi::Datatype::POLICE_CAR);
    ASSERT_EQ(police_car_memory_allocator.get_number_of_storages(), 0);
    ASSERT_EQ(police_car_memory_allocator.get_number_of_instances(), 0);
    // There should be no storages nor instances in `Biont`'s memory allocator before the upcoming allocations.
    yli::memory::MemoryAllocator<yli::ontology::Biont*>& biont_memory_allocator = hirvi_application.get_memory_allocator<yli::ontology::Biont*>(hirvi::Datatype::BIONT);
    ASSERT_EQ(biont_memory_allocator.get_number_of_storages(), 0);
    ASSERT_EQ(biont_memory_allocator.get_number_of_instances(), 0);

    hirvi::PoliceCar* const turbo_polizei1 = hirvi_application.entity_factory.create_holobiont_derivative<
        hirvi::PoliceCar,
        hirvi::PoliceCarMemoryAllocator>(
                hirvi::Datatype::POLICE_CAR,
                turbo_polizei_png_police_car_struct1,
                road_vehicle_struct1);
    ASSERT_NE(turbo_polizei1, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(turbo_polizei1) % alignof(hirvi::PoliceCar), 0);

    // Even though `PoliceCar` is derived from `Holobiont`. `PoliceCar` should be allocated using its own allocator.
    ASSERT_EQ(holobiont_memory_allocator.get_number_of_storages(), 0);
    ASSERT_EQ(holobiont_memory_allocator.get_number_of_instances(), 0);
    // `PoliceCar` should be allocated using its own allocator.
    ASSERT_EQ(police_car_memory_allocator.get_number_of_storages(), 1);
    ASSERT_EQ(police_car_memory_allocator.get_number_of_instances(), 1);
    // The `Biont`s of the `PoliceCar` should be allocated using the `Biont` allocator.
    // There is 1 body + chassis `Biont`, and 4 wheel `Biont`s.
    ASSERT_EQ(biont_memory_allocator.get_number_of_storages(), 1);
    ASSERT_EQ(biont_memory_allocator.get_number_of_instances(), 5);

    yli::memory::ConstructibleModule turbo_polizei1_constructible_module = turbo_polizei1->get_constructible_module();
    ASSERT_EQ(turbo_polizei1_constructible_module.storage_i, 0);
    ASSERT_EQ(turbo_polizei1_constructible_module.slot_i, 0);
    ASSERT_EQ(turbo_polizei1_constructible_module.alive, true);
}
