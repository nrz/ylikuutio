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
#include "code/hirvi/ontology/hirvi_scene_struct.hpp"
#include "code/hirvi/ontology/police_control_center_struct.hpp"

// Include standard headers
#include <cstdint> // uintptr_t

TEST(police_control_centers_must_be_initialized_appropriately, police_control_centers)
{
    using namespace hirvi::ontology;
    using namespace yli::ontology;

    constexpr int argc { 0 };
    const char** const argv { nullptr };
    hirvi::HirviApplication hirvi_application(argc, argv);

    ASSERT_FALSE(hirvi_application.has_memory_allocator(hirvi::data::SCENE));
    ASSERT_FALSE(hirvi_application.has_memory_allocator(hirvi::data::HOLOBIONT));
    ASSERT_FALSE(hirvi_application.has_memory_allocator(hirvi::data::HIRVI_SCENE));
    ASSERT_FALSE(hirvi_application.has_memory_allocator(hirvi::data::POLICE_CONTROL_CENTER));
    ASSERT_FALSE(hirvi_application.has_memory_allocator(hirvi::data::POLICE_CAR));
    ASSERT_FALSE(hirvi_application.has_memory_allocator(hirvi::data::POLICE_DOG));
    ASSERT_FALSE(hirvi_application.has_memory_allocator(hirvi::data::POLICE_HORSE));

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
    auto* const helsinki_scene = hirvi_application.get_entity_factory().create_scene_derivative<
        HirviScene,
        hirvi::core::HirviSceneMemoryAllocator,
        HirviSceneStruct>(
        hirvi::data::HIRVI_SCENE,
        scene_struct,
        hirvi_application.core);
    ASSERT_FALSE(hirvi_application.has_memory_allocator(hirvi::data::SCENE));
    ASSERT_FALSE(hirvi_application.has_memory_allocator(hirvi::data::HOLOBIONT));
    ASSERT_TRUE(hirvi_application.has_memory_allocator(hirvi::data::HIRVI_SCENE));
    ASSERT_TRUE(hirvi_application.has_memory_allocator(hirvi::data::POLICE_CONTROL_CENTER));
    ASSERT_FALSE(hirvi_application.has_memory_allocator(hirvi::data::POLICE_CAR));
    ASSERT_FALSE(hirvi_application.has_memory_allocator(hirvi::data::POLICE_DOG));
    ASSERT_FALSE(hirvi_application.has_memory_allocator(hirvi::data::POLICE_HORSE));

    // `Entity` member functions of `HirviScene`.
    ASSERT_EQ(helsinki_scene->get_number_of_non_variable_children(), 3);

    auto* non_emancipated_control_center = dynamic_cast<PoliceControlCenter*>(helsinki_scene->
        get_entity("non_emancipated_control_center"));
    auto* emancipated_control_center = dynamic_cast<PoliceControlCenter*>(helsinki_scene->get_entity(
        "emancipated_control_center"));
    ASSERT_NE(non_emancipated_control_center, nullptr);
    ASSERT_NE(emancipated_control_center, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(non_emancipated_control_center) % alignof(hirvi::ontology::PoliceControlCenter), 0);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(emancipated_control_center) % alignof(hirvi::ontology::PoliceControlCenter), 0);

    // `Entity` member functions.
    ASSERT_EQ(non_emancipated_control_center->get_childID(), 0);
    ASSERT_EQ(emancipated_control_center->get_childID(), 1);
    ASSERT_EQ(non_emancipated_control_center->get_type(), "hirvi::ontology::PoliceControlCenter*");
    ASSERT_EQ(emancipated_control_center->get_type(), "hirvi::ontology::PoliceControlCenter*");
    ASSERT_FALSE(non_emancipated_control_center->get_can_be_erased());
    ASSERT_FALSE(emancipated_control_center->get_can_be_erased());
    ASSERT_EQ(non_emancipated_control_center->get_scene(), helsinki_scene);
    ASSERT_EQ(emancipated_control_center->get_scene(), helsinki_scene);
    ASSERT_EQ(non_emancipated_control_center->get_parent(), helsinki_scene);
    ASSERT_EQ(emancipated_control_center->get_parent(), helsinki_scene);
    ASSERT_EQ(non_emancipated_control_center->get_number_of_non_variable_children(), 0);
    ASSERT_EQ(emancipated_control_center->get_number_of_non_variable_children(), 0);
}
