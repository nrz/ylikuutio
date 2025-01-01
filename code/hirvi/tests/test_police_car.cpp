// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2025 Antti Nuortimo.
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
#include "code/hirvi/ontology/cat.hpp"
#include "code/hirvi/ontology/police_car.hpp"
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
#include "code/ylikuutio/ontology/request.hpp"
#include "code/ylikuutio/ontology/brain_struct.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"
#include "code/ylikuutio/ontology/pipeline_struct.hpp"
#include "code/ylikuutio/ontology/material_struct.hpp"
#include "code/ylikuutio/ontology/symbiosis_struct.hpp"
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
    using namespace yli::ontology;

    const int argc { 0 };
    const char** const argv { nullptr };
    hirvi::HirviApplication hirvi_application(argc, argv);

    SceneStruct scene_struct;
    scene_struct.global_name = "helsinki_scene";
    scene_struct.light_position = { 0.0f, -100000.0f, 100000.0f, 1.0f };
    scene_struct.water_level = 0.9f;
    Scene* const helsinki_scene = hirvi_application.get_entity_factory().create_scene(scene_struct);

    CallbackEngineStruct rest_callback_engine_struct;
    auto rest_callback_engine = hirvi_application.get_entity_factory().create_callback_engine(rest_callback_engine_struct);
    rest_callback_engine->create_callback_object(&yli::snippets::rest);

    BrainStruct rest_brain_struct { Request(helsinki_scene), Request(rest_callback_engine) };
    rest_brain_struct.global_name = "rest_brain";
    rest_brain_struct.local_name = "rest";
    Brain* const rest_brain = hirvi_application.get_entity_factory().create_brain(rest_brain_struct);

    PipelineStruct helsinki_pipeline_struct { Request(helsinki_scene) };
    helsinki_pipeline_struct.global_name = "helsinki_pipeline";
    helsinki_pipeline_struct.local_name = "helsinki_regular_pipeline";
    helsinki_pipeline_struct.vertex_shader = "standard_shading.vert";
    helsinki_pipeline_struct.fragment_shader = "standard_shading.frag";
    Pipeline* const helsinki_pipeline = hirvi_application.get_entity_factory().create_pipeline(helsinki_pipeline_struct);

    SymbiosisStruct turbo_polizei_png_symbiosis_struct { Request(helsinki_scene), Request(helsinki_pipeline) };
    turbo_polizei_png_symbiosis_struct.model_file_format = "fbx";
    turbo_polizei_png_symbiosis_struct.model_filename = "turbo_polizei_png_textures.fbx";
    Symbiosis* const turbo_polizei_png_symbiosis = hirvi_application.get_entity_factory().create_symbiosis(turbo_polizei_png_symbiosis_struct);

    HolobiontStruct turbo_polizei_png_police_car_struct1 { Request(helsinki_scene), Request(rest_brain), Request(turbo_polizei_png_symbiosis) };
    turbo_polizei_png_police_car_struct1.initial_rotate_vectors = { glm::vec3(0.0f, 1.0f, 1.0f) };
    turbo_polizei_png_police_car_struct1.initial_rotate_angles = { static_cast<float>(std::numbers::pi) };
    turbo_polizei_png_police_car_struct1.original_scale_vector = glm::vec3(1.0f, 1.0f, 1.0f);
    turbo_polizei_png_police_car_struct1.cartesian_coordinates = CartesianCoordinatesModule(85.00f, 30.00f, 160.00f);
    LocomotionModuleStruct road_vehicle_struct1;

    ASSERT_FALSE(hirvi_application.has_memory_allocator(hirvi::Datatype::HOLOBIONT));
    ASSERT_FALSE(hirvi_application.has_memory_allocator(hirvi::Datatype::BIONT));
    ASSERT_FALSE(hirvi_application.has_memory_allocator(hirvi::Datatype::POLICE_CAR));

    hirvi::PoliceCar* const turbo_polizei1 = hirvi_application.get_entity_factory().create_holobiont_derivative<
        hirvi::PoliceCar,
        hirvi::PoliceCarMemoryAllocator>(
                hirvi::Datatype::POLICE_CAR,
                turbo_polizei_png_police_car_struct1,
                road_vehicle_struct1);
    ASSERT_NE(turbo_polizei1, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(turbo_polizei1) % alignof(hirvi::PoliceCar), 0);

    ASSERT_TRUE(hirvi_application.has_memory_allocator(hirvi::Datatype::POLICE_CAR));
    ASSERT_TRUE(hirvi_application.has_memory_allocator(yli::data::Datatype::BIONT));

    // Even though `PoliceCar` is derived from `Holobiont`. `PoliceCar` should be allocated using its own allocator.
    yli::memory::MemoryAllocator<hirvi::PoliceCar*>& police_car_memory_allocator = hirvi_application.get_memory_allocator<hirvi::PoliceCar*>(hirvi::Datatype::POLICE_CAR);
    // `PoliceCar` should be allocated using its own allocator.
    ASSERT_EQ(police_car_memory_allocator.get_number_of_storages(), 1);
    ASSERT_EQ(police_car_memory_allocator.get_number_of_instances(), 1);
    // The `Biont`s of the `PoliceCar` should be allocated using the `Biont` allocator.
    // There is 1 body + chassis `Biont`, and 4 wheel `Biont`s.
    yli::memory::MemoryAllocator<Biont*>& biont_memory_allocator = hirvi_application.get_memory_allocator<Biont*>(yli::data::Datatype::BIONT);
    ASSERT_EQ(biont_memory_allocator.get_number_of_storages(), 1);
    ASSERT_EQ(biont_memory_allocator.get_number_of_instances(), 5);

    yli::memory::ConstructibleModule turbo_polizei1_constructible_module = turbo_polizei1->get_constructible_module();
    ASSERT_EQ(turbo_polizei1_constructible_module.storage_i, 0);
    ASSERT_EQ(turbo_polizei1_constructible_module.slot_i, 0);
    ASSERT_EQ(turbo_polizei1_constructible_module.alive, true);
}
