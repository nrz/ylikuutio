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
#include "code/mock/mock_application.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/heightmap.hpp"
#include "code/ylikuutio/ontology/request.hpp"
#include "code/ylikuutio/ontology/heightmap_struct.hpp"

// Include standard headers
#include <cstdint> // uintptr_t
#include <limits>  // std::numeric_limits

TEST(heightmap_must_be_initialized_and_appropriately, scene_parent_provided_as_valid_pointer)
{
    const mock::MockApplication application;
    const yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
        scene_struct);

    const yli::ontology::HeightmapStruct heightmap_struct { yli::ontology::Request(scene) };
    yli::ontology::Heightmap* const heightmap = application.get_generic_entity_factory().create_heightmap(
        heightmap_struct);
    ASSERT_NE(heightmap, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(heightmap) % alignof(yli::ontology::Heightmap), 0);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 2); // Default `Camera`, `Heightmap`.

    // `Entity` member functions.
    ASSERT_EQ(heightmap->get_childID(), 0);
    ASSERT_EQ(heightmap->get_type(), "yli::ontology::Heightmap*");
    ASSERT_TRUE(heightmap->get_can_be_erased());
    ASSERT_EQ(heightmap->get_scene(), scene);
    ASSERT_EQ(heightmap->get_parent(), scene);
    ASSERT_EQ(heightmap->get_number_of_non_variable_children(), 0);
}

TEST(heightmap_must_be_initialized_and_appropriately, scene_parent_provided_as_valid_global_name)
{
    const mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    scene_struct.global_name = "foo";
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
        scene_struct);

    const yli::ontology::HeightmapStruct heightmap_struct(yli::ontology::Request<yli::ontology::Scene>("foo"));
    yli::ontology::Heightmap* const heightmap = application.get_generic_entity_factory().create_heightmap(
        heightmap_struct);
    ASSERT_NE(heightmap, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(heightmap) % alignof(yli::ontology::Heightmap), 0);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 2); // Default `Camera`, `Heightmap`.

    // `Entity` member functions.
    ASSERT_EQ(heightmap->get_childID(), 0);
    ASSERT_EQ(heightmap->get_type(), "yli::ontology::Heightmap*");
    ASSERT_TRUE(heightmap->get_can_be_erased());
    ASSERT_EQ(heightmap->get_scene(), scene);
    ASSERT_EQ(heightmap->get_parent(), scene);
    ASSERT_EQ(heightmap->get_number_of_non_variable_children(), 0);
}

TEST(heightmap_must_be_initialized_appropriately, scene_provided_as_invalid_global_name)
{
    const mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    scene_struct.global_name = "foo";
    const yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(scene_struct);

    const yli::ontology::HeightmapStruct heightmap_struct(yli::ontology::Request<yli::ontology::Scene>("bar"));
    yli::ontology::Heightmap* const heightmap = application.get_generic_entity_factory().create_heightmap(
        heightmap_struct);
    ASSERT_NE(heightmap, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(heightmap) % alignof(yli::ontology::Heightmap), 0);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 1); // Default `Camera`.

    // `Entity` member functions.
    ASSERT_EQ(heightmap->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(heightmap->get_type(), "yli::ontology::Heightmap*");
    ASSERT_TRUE(heightmap->get_can_be_erased());
    ASSERT_EQ(heightmap->get_scene(), nullptr);
    ASSERT_EQ(heightmap->get_parent(), nullptr);
    ASSERT_EQ(heightmap->get_number_of_non_variable_children(), 0);
}
