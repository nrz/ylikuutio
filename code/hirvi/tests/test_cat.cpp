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
#include "code/hirvi/data/datatype.hpp"
#include "code/hirvi/ontology/cat.hpp"
#include "code/ylikuutio/snippets/brain_snippets.hpp"
#include "code/ylikuutio/memory/constructible_module.hpp"
#include "code/ylikuutio/ontology/cartesian_coordinates_module.hpp"
#include "code/ylikuutio/ontology/callback_engine.hpp"
#include "code/ylikuutio/ontology/object.hpp"
#include "code/ylikuutio/ontology/request.hpp"
#include "code/ylikuutio/ontology/brain_struct.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"
#include "code/ylikuutio/ontology/pipeline_struct.hpp"
#include "code/ylikuutio/ontology/material_struct.hpp"
#include "code/ylikuutio/ontology/species_struct.hpp"
#include "code/ylikuutio/ontology/object_struct.hpp"
#include "code/ylikuutio/ontology/locomotion_module_struct.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef> // uintptr_t
#include <numbers> // std::numbers::pi

namespace yli::ontology
{
    class Brain;
    class Scene;
    class Pipeline;
    class Material;
    class Species;
}

TEST(cat_must_be_initialized_appropriately, hirvi_cat)
{
    using namespace yli::ontology; 

    const int argc { 0 };
    const char** const argv { nullptr };
    hirvi::HirviApplication hirvi_application(argc, argv);

    SceneStruct scene_struct;
    scene_struct.global_name = "helsinki_scene";
    scene_struct.light_position = { 0.0f, -100000.0f, 100000.0f, 1.0f };
    scene_struct.water_level = 0.9f;
    Scene* const helsinki_scene = hirvi_application.entity_factory.create_scene(scene_struct);

    CallbackEngineStruct rest_callback_engine_struct;
    auto rest_callback_engine = hirvi_application.entity_factory.create_callback_engine(rest_callback_engine_struct);
    rest_callback_engine->create_callback_object(&yli::snippets::rest);

    BrainStruct rest_brain_struct { Request(helsinki_scene), Request(rest_callback_engine) };
    rest_brain_struct.global_name = "rest_brain";
    rest_brain_struct.local_name = "rest";
    Brain* const rest_brain = hirvi_application.entity_factory.create_brain(rest_brain_struct);

    PipelineStruct helsinki_pipeline_struct { Request(helsinki_scene) };
    helsinki_pipeline_struct.global_name = "helsinki_pipeline";
    helsinki_pipeline_struct.local_name = "helsinki_regular_pipeline";
    helsinki_pipeline_struct.vertex_shader = "standard_shading.vert";
    helsinki_pipeline_struct.fragment_shader = "standard_shading.frag";
    Pipeline* const helsinki_pipeline = hirvi_application.entity_factory.create_pipeline(helsinki_pipeline_struct);

    MaterialStruct orange_fur_material_struct { Request(helsinki_scene), Request(helsinki_pipeline) };
    orange_fur_material_struct.texture_file_format = "png";
    orange_fur_material_struct.texture_filename = "orange_fur_texture.png";
    Material* const orange_fur_material = hirvi_application.entity_factory.create_material(orange_fur_material_struct);

    SpeciesStruct cat_species_struct { Request(helsinki_scene), Request(orange_fur_material) };
    cat_species_struct.global_name = "cat_species";
    cat_species_struct.local_name = "cat";
    cat_species_struct.model_loader_struct.model_file_format = "fbx";
    cat_species_struct.model_loader_struct.model_filename = "cat.fbx";
    Species* const cat_species = hirvi_application.entity_factory.create_species(cat_species_struct);

    ObjectStruct cat1_object_struct { Request(helsinki_scene), Request(rest_brain), Request(cat_species) };
    cat1_object_struct.global_name = "cat1";
    cat1_object_struct.local_name = "kissa1";
    cat1_object_struct.initial_rotate_vectors = { glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f) };
    cat1_object_struct.initial_rotate_angles = { static_cast<float>(std::numbers::pi), -0.5f * static_cast<float>(std::numbers::pi) };
    cat1_object_struct.original_scale_vector = glm::vec3(10.0f, 10.0f, 10.0f);
    cat1_object_struct.cartesian_coordinates = CartesianCoordinatesModule(500.00f, 100.00f, 1000.00f);

    LocomotionModuleStruct cat1_walk_struct(1.0f); // 3.6 km/h.
    LocomotionModuleStruct cat1_trot_struct(5.0f);
    LocomotionModuleStruct cat1_canter_struct(10.0f);
    LocomotionModuleStruct cat1_gallop_struct(12.5f); // 45 km/h.
    LocomotionModuleStruct cat1_climb_struct;

    ASSERT_FALSE(hirvi_application.has_memory_allocator(hirvi::Datatype::OBJECT));
    ASSERT_FALSE(hirvi_application.has_memory_allocator(hirvi::Datatype::CAT));

    hirvi::Cat* const cat1 = hirvi_application.entity_factory.create_object_derivative<
        hirvi::Cat,
        hirvi::CatMemoryAllocator>(
                hirvi::Datatype::CAT,
                cat1_object_struct,
                cat1_walk_struct,
                cat1_trot_struct,
                cat1_canter_struct,
                cat1_gallop_struct,
                cat1_climb_struct);
    ASSERT_NE(cat1, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(cat1) % alignof(hirvi::Cat), 0);

    ASSERT_TRUE(hirvi_application.has_memory_allocator(hirvi::Datatype::CAT));

    // Even though `Cat` is derived from `Object`. `Cat` should be allocated using its own allocator.
    yli::memory::MemoryAllocator<hirvi::Cat*>& cat_memory_allocator = hirvi_application.get_memory_allocator<hirvi::Cat*>(hirvi::Datatype::CAT);
    ASSERT_EQ(cat_memory_allocator.get_number_of_storages(), 1);
    ASSERT_EQ(cat_memory_allocator.get_number_of_instances(), 1);

    yli::memory::ConstructibleModule cat1_constructible_module = cat1->get_constructible_module();
    ASSERT_EQ(cat1_constructible_module.storage_i, 0);
    ASSERT_EQ(cat1_constructible_module.slot_i, 0);
    ASSERT_EQ(cat1_constructible_module.alive, true);
}
