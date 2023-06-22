// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2022 Antti Nuortimo.
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
#include "code/mock/mock_application.hpp"
#include "code/ylikuutio/data/datatype.hpp"
#include "code/ylikuutio/memory/memory_allocator.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"

// Include standard headers
#include <cstddef> // std::size_t

TEST(memory_allocator_must_be_initialized_appropriately, universe_memory_allocator)
{
    mock::MockApplication application;
    auto& generic_universe_allocator = application.get_memory_allocator(yli::data::Datatype::UNIVERSE);
    auto& universe_allocator = dynamic_cast<mock::UniverseMemoryAllocator&>(generic_universe_allocator);
    ASSERT_EQ(universe_allocator.get_number_of_storages(), 1);  // `MockApplication` constructor builds `Universe` instance.
    ASSERT_EQ(universe_allocator.get_number_of_instances(), 1); // `MockApplication` constructor builds `Universe` instance.
}

TEST(memory_allocator_must_be_initialized_appropriately, variable_memory_allocator)
{
    mock::MockApplication application;
    auto& generic_variable_allocator = application.get_memory_allocator(yli::data::Datatype::VARIABLE);
    auto& variable_allocator = dynamic_cast<mock::VariableMemoryAllocator&>(generic_variable_allocator);

    // `MockApplication` constructor builds `Universe` instance, that has some variables, which fit in 1 storage.
    ASSERT_EQ(variable_allocator.get_number_of_storages(), 1);  // `Universe` has some variables which fit in 1 storage.
    ASSERT_GT(variable_allocator.get_number_of_instances(), 0); // `Universe` has some variables.
}

TEST(memory_allocator_must_be_initialized_appropriately, ecosystem_memory_allocator)
{
    mock::MockApplication application;
    auto& generic_ecosystem_allocator = application.get_memory_allocator(yli::data::Datatype::ECOSYSTEM);
    auto& ecosystem_allocator = dynamic_cast<mock::EcosystemMemoryAllocator&>(generic_ecosystem_allocator);
    ASSERT_EQ(ecosystem_allocator.get_number_of_storages(), 0);
    ASSERT_EQ(ecosystem_allocator.get_number_of_instances(), 0);
}

TEST(memory_allocator_must_be_initialized_appropriately, scene_memory_allocator)
{
    mock::MockApplication application;
    auto& generic_scene_allocator = application.get_memory_allocator(yli::data::Datatype::SCENE);
    auto& scene_allocator = dynamic_cast<mock::SceneMemoryAllocator&>(generic_scene_allocator);
    ASSERT_EQ(scene_allocator.get_number_of_storages(), 0);
    ASSERT_EQ(scene_allocator.get_number_of_instances(), 0);
}

TEST(memory_allocator_must_build_scene_in_a_memory_storage, scene_memory_storage)
{
    mock::MockApplication application;
    auto& generic_scene_allocator = application.get_memory_allocator(yli::data::Datatype::SCENE);
    auto& scene_allocator = dynamic_cast<mock::SceneMemoryAllocator&>(generic_scene_allocator);

    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* scene = scene_allocator.build_in(
            yli::data::Datatype::SCENE,
            application,
            application.get_universe(),
            scene_struct,
            &application.get_universe().parent_of_scenes);
    ASSERT_EQ(scene_allocator.get_number_of_storages(), 1);
    ASSERT_EQ(scene_allocator.get_number_of_instances(), 1);
    ASSERT_NE(scene, nullptr);
    ASSERT_EQ(scene->get_type(), "yli::ontology::Scene*");
}

TEST(memory_allocator_must_build_2_scenes_in_the_same_memory_region, scenes)
{
    mock::MockApplication application;
    auto& generic_scene_allocator = application.get_memory_allocator(yli::data::Datatype::SCENE);
    auto& scene_allocator = dynamic_cast<mock::SceneMemoryAllocator&>(generic_scene_allocator);
    ASSERT_EQ(scene_allocator.get_number_of_storages(), 0);
    ASSERT_EQ(scene_allocator.get_number_of_instances(), 0);

    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* scene1 = scene_allocator.build_in(
            yli::data::Datatype::SCENE,
            application,
            application.get_universe(),
            scene_struct,
            &application.get_universe().parent_of_scenes);
    yli::ontology::Scene* scene2 = scene_allocator.build_in(
            yli::data::Datatype::SCENE,
            application,
            application.get_universe(),
            scene_struct,
            &application.get_universe().parent_of_scenes);
    ASSERT_EQ(scene_allocator.get_number_of_storages(), 1);
    ASSERT_EQ(scene_allocator.get_number_of_instances(), 2);
    ASSERT_NE(scene1, nullptr);
    ASSERT_NE(scene2, nullptr);
    ASSERT_EQ(scene1->get_type(), "yli::ontology::Scene*");
    ASSERT_EQ(scene2->get_type(), "yli::ontology::Scene*");

    // It is assumed here that `SceneMemoryAllocator` has `DataSize` of at least 2.
    const std::ptrdiff_t address_difference = reinterpret_cast<std::byte*>(scene2) - reinterpret_cast<std::byte*>(scene1);
    ASSERT_EQ(address_difference, sizeof(yli::ontology::Scene));
}

TEST(memory_allocator_must_build_3_scenes_in_the_same_memory_region, scenes)
{
    mock::MockApplication application;
    auto& generic_scene_allocator = application.get_memory_allocator(yli::data::Datatype::SCENE);
    auto& scene_allocator = dynamic_cast<mock::SceneMemoryAllocator&>(generic_scene_allocator);

    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* scene1 = scene_allocator.build_in(
            yli::data::Datatype::SCENE,
            application,
            application.get_universe(),
            scene_struct,
            &application.get_universe().parent_of_scenes);
    yli::ontology::Scene* scene2 = scene_allocator.build_in(
            yli::data::Datatype::SCENE,
            application,
            application.get_universe(),
            scene_struct,
            &application.get_universe().parent_of_scenes);
    yli::ontology::Scene* scene3 = scene_allocator.build_in(
            yli::data::Datatype::SCENE,
            application,
            application.get_universe(),
            scene_struct,
            &application.get_universe().parent_of_scenes);
    ASSERT_EQ(scene_allocator.get_number_of_storages(), 1);
    ASSERT_EQ(scene_allocator.get_number_of_instances(), 3);
    ASSERT_NE(scene1, nullptr);
    ASSERT_NE(scene2, nullptr);
    ASSERT_NE(scene3, nullptr);
    ASSERT_EQ(scene1->get_type(), "yli::ontology::Scene*");
    ASSERT_EQ(scene2->get_type(), "yli::ontology::Scene*");
    ASSERT_EQ(scene3->get_type(), "yli::ontology::Scene*");

    // It is assumed here that `SceneMemoryAllocator` has `DataSize` of at least 3.
    const std::ptrdiff_t address_difference1 = reinterpret_cast<std::byte*>(scene2) - reinterpret_cast<std::byte*>(scene1);
    const std::ptrdiff_t address_difference2 = reinterpret_cast<std::byte*>(scene3) - reinterpret_cast<std::byte*>(scene2);
    ASSERT_EQ(address_difference1, sizeof(yli::ontology::Scene));
    ASSERT_EQ(address_difference2, sizeof(yli::ontology::Scene));
}

TEST(memory_allocator_must_build_n_scenes_in_1_memory_storage, scene_memory_storage_of_size_n)
{
    mock::MockApplication application;
    auto& generic_scene_allocator = application.get_memory_allocator(yli::data::Datatype::SCENE);
    auto& scene_allocator = dynamic_cast<mock::SceneMemoryAllocator&>(generic_scene_allocator);

    for (std::size_t scene_i = 0; scene_i < scene_allocator.get_data_size(); scene_i++)
    {
        yli::ontology::SceneStruct scene_struct;
        const yli::ontology::Scene* const scene = scene_allocator.build_in(
                yli::data::Datatype::SCENE,
                application,
                application.get_universe(),
                scene_struct,
                &application.get_universe().parent_of_scenes);

        ASSERT_NE(scene, nullptr);
        ASSERT_EQ(scene->get_type(), "yli::ontology::Scene*");
    }

    ASSERT_EQ(scene_allocator.get_number_of_storages(), 1);
    ASSERT_EQ(scene_allocator.get_number_of_instances(), scene_allocator.get_data_size());
}

TEST(memory_allocator_must_build_n_plus_1_scenes_in_2_memory_storages, scene_memory_storage_of_size_n)
{
    mock::MockApplication application;
    auto& generic_scene_allocator = application.get_memory_allocator(yli::data::Datatype::SCENE);
    auto& scene_allocator = dynamic_cast<mock::SceneMemoryAllocator&>(generic_scene_allocator);

    for (std::size_t scene_i = 0; scene_i < scene_allocator.get_data_size() + 1; scene_i++)
    {
        yli::ontology::SceneStruct scene_struct;
        const yli::ontology::Scene* const scene = scene_allocator.build_in(
                yli::data::Datatype::SCENE,
                application,
                application.get_universe(),
                scene_struct,
                &application.get_universe().parent_of_scenes);

        ASSERT_NE(scene, nullptr);
        ASSERT_EQ(scene->get_type(), "yli::ontology::Scene*");
    }

    ASSERT_EQ(scene_allocator.get_number_of_storages(), 2);
    ASSERT_EQ(scene_allocator.get_number_of_instances(), scene_allocator.get_data_size() + 1);
}

TEST(memory_allocator_must_build_2n_scenes_in_2_memory_storages, scene_memory_storage_of_size_n)
{
    mock::MockApplication application;
    auto& generic_scene_allocator = application.get_memory_allocator(yli::data::Datatype::SCENE);
    auto& scene_allocator = dynamic_cast<mock::SceneMemoryAllocator&>(generic_scene_allocator);

    for (std::size_t scene_i = 0; scene_i < 2 * scene_allocator.get_data_size(); scene_i++)
    {
        yli::ontology::SceneStruct scene_struct;
        const yli::ontology::Scene* const scene = scene_allocator.build_in(
                yli::data::Datatype::SCENE,
                application,
                application.get_universe(),
                scene_struct,
                &application.get_universe().parent_of_scenes);

        ASSERT_NE(scene, nullptr);
        ASSERT_EQ(scene->get_type(), "yli::ontology::Scene*");
    }

    ASSERT_EQ(scene_allocator.get_number_of_storages(), 2);
    ASSERT_EQ(scene_allocator.get_number_of_instances(), 2 * scene_allocator.get_data_size());
}
