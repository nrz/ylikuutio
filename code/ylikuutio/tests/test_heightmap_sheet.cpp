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
#include "code/ylikuutio/ontology/heightmap.hpp"
#include "code/ylikuutio/ontology/heightmap_sheet.hpp"
#include "code/ylikuutio/ontology/request.hpp"
#include "code/ylikuutio/ontology/heightmap_sheet_struct.hpp"
#include "code/ylikuutio/ontology/heightmap_struct.hpp"

// Include standard headers
#include <cstdint> // uintptr_t
#include <limits>  // std::numeric_limits

TEST(heightmap_sheet_must_be_initialized_appropriately, heightmap_provided_as_valid_pointer)
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
    yli::ontology::HeightmapSheetStruct heightmap_sheet_struct {
        yli::ontology::Request(heightmap),
        yli::ontology::Request<yli::ontology::Scene>("foo"),
    };
    yli::ontology::HeightmapSheet* const heightmap_sheet = application.get_generic_entity_factory().
            create_heightmap_sheet(
                heightmap_sheet_struct);
    ASSERT_NE(heightmap_sheet, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(heightmap_sheet) % alignof(yli::ontology::HeightmapSheet), 0);

    // `Entity` member functions of `Heightmap`.
    ASSERT_EQ(heightmap->get_number_of_non_variable_children(), 1);

    // `Entity` member functions.
    ASSERT_EQ(heightmap_sheet->get_childID(), 0);
    ASSERT_EQ(heightmap_sheet->get_type(), "yli::ontology::HeightmapSheet*");
    ASSERT_FALSE(heightmap_sheet->get_can_be_erased());
    ASSERT_EQ(heightmap_sheet->get_scene(), scene);
    ASSERT_EQ(heightmap_sheet->get_parent(), heightmap);
    ASSERT_EQ(heightmap_sheet->get_number_of_non_variable_children(), 0);
}

TEST(heightmap_sheet_must_be_initialized_appropriately, heightmap_provided_as_valid_global_name)
{
    const mock::MockApplication application;
    const yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
        scene_struct);

    yli::ontology::HeightmapStruct heightmap_struct { yli::ontology::Request(scene) };
    heightmap_struct.global_name = "foo";
    yli::ontology::Heightmap* const heightmap = application.get_generic_entity_factory().create_heightmap(
        heightmap_struct);
    ASSERT_NE(heightmap, nullptr);

    yli::ontology::HeightmapSheetStruct heightmap_sheet_struct {
        yli::ontology::Request<yli::ontology::Heightmap>("foo"),
        yli::ontology::Request(scene)
    };
    yli::ontology::HeightmapSheet* const heightmap_sheet = application.get_generic_entity_factory().
            create_heightmap_sheet(
                heightmap_sheet_struct);
    ASSERT_NE(heightmap_sheet, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(heightmap_sheet) % alignof(yli::ontology::HeightmapSheet), 0);

    // `Entity` member functions of `Heightmap`.
    ASSERT_EQ(heightmap->get_number_of_non_variable_children(), 1);

    // `Entity` member functions.
    ASSERT_EQ(heightmap_sheet->get_childID(), 0);
    ASSERT_EQ(heightmap_sheet->get_type(), "yli::ontology::HeightmapSheet*");
    ASSERT_FALSE(heightmap_sheet->get_can_be_erased());
    ASSERT_EQ(heightmap_sheet->get_scene(), scene);
    ASSERT_EQ(heightmap_sheet->get_parent(), heightmap);
    ASSERT_EQ(heightmap_sheet->get_number_of_non_variable_children(), 0);
}

TEST(heightmap_sheet_must_be_initialized_appropriately, heightmap_provided_as_invalid_global_name)
{
    const mock::MockApplication application;
    const yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
        scene_struct);

    yli::ontology::HeightmapStruct heightmap_struct { yli::ontology::Request(scene) };
    heightmap_struct.global_name = "foo";
    yli::ontology::Heightmap* const heightmap = application.get_generic_entity_factory().create_heightmap(
        heightmap_struct);
    ASSERT_NE(heightmap, nullptr);
    yli::ontology::HeightmapSheetStruct heightmap_sheet_struct {
        yli::ontology::Request<yli::ontology::Heightmap>("bar"),
        yli::ontology::Request(scene)
    };
    yli::ontology::HeightmapSheet* const heightmap_sheet = application.get_generic_entity_factory().
            create_heightmap_sheet(
                heightmap_sheet_struct);
    ASSERT_NE(heightmap_sheet, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(heightmap_sheet) % alignof(yli::ontology::HeightmapSheet), 0);

    // `Entity` member functions of `Heightmap`.
    ASSERT_EQ(heightmap->get_number_of_non_variable_children(), 0);

    // `Entity` member functions.
    ASSERT_EQ(heightmap_sheet->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(heightmap_sheet->get_type(), "yli::ontology::HeightmapSheet*");
    ASSERT_FALSE(heightmap_sheet->get_can_be_erased());
    ASSERT_EQ(heightmap_sheet->get_scene(), nullptr);
    ASSERT_EQ(heightmap_sheet->get_parent(), nullptr);
    ASSERT_EQ(heightmap_sheet->get_number_of_non_variable_children(), 0);
}
