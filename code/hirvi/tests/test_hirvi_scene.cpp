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
#include "code/hirvi/ontology/hirvi_scene_struct.hpp"
#include "code/hirvi/ontology/police_control_center_struct.hpp"

// Include standard headers
#include <cstdint> // uintptr_t

namespace yli::ontology
{
    class MovableController;
    class Waypoint;
    class Camera;
    class Pipeline;
    class Material;
    class Species;
    class Object;
    class Symbiosis;
    class Holobiont;
    class Shapeshifter;
    class Text3d;
    class GlyphObject;
}

namespace hirvi::ontology
{
    class PoliceControlCenter;
    class PoliceCar;
    class PoliceDog;
    class PoliceHelicopter;
    class PoliceHorse;
    class PoliceTrain;
    class PoliceTram;
}

TEST(hirvi_scene_must_be_initialized_appropriately, universe_provided_as_valid_pointer)
{
    using namespace hirvi::ontology;
    using namespace yli::ontology;

    constexpr int argc { 0 };
    const char** const argv { nullptr };
    const hirvi::HirviApplication hirvi_application(argc, argv);

    PoliceControlCenterStruct helsinki_non_emancipated_control_center_struct;
    helsinki_non_emancipated_control_center_struct.global_name = "helsinki_non_emancipated_control_center";
    helsinki_non_emancipated_control_center_struct.local_name = "non_emancipated_control_center";
    PoliceControlCenterStruct helsinki_emancipated_control_center_struct;
    helsinki_emancipated_control_center_struct.global_name = "helsinki_emancipated_control_center";
    helsinki_emancipated_control_center_struct.local_name = "emancipated_control_center";
    HirviSceneStruct hirvi_scene_struct;
    hirvi_scene_struct.global_name = "helsinki_scene";
    hirvi_scene_struct.light_position = { 0.0f, -100000.0f, 100000.0f, 1.0f };
    hirvi_scene_struct.water_level = 0.9f;
    hirvi_scene_struct.police_control_center_structs = {
        helsinki_non_emancipated_control_center_struct, helsinki_emancipated_control_center_struct
    };
    HirviScene* const helsinki_scene = hirvi_application.get_entity_factory().create_scene_derivative<
        HirviScene,
        hirvi::core::HirviSceneMemoryAllocator,
        HirviSceneStruct>(
        hirvi::data::HIRVI_SCENE,
        hirvi_scene_struct,
        hirvi_application.core);
    ASSERT_NE(helsinki_scene, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(helsinki_scene) % alignof(hirvi::ontology::HirviScene), 0);

    GenericParentModule* const movable_controller_parent_module =
            helsinki_scene->get_generic_parent_module<MovableController>();
    ASSERT_NE(movable_controller_parent_module, nullptr);

    GenericParentModule* const waypoint_parent_module = helsinki_scene->get_generic_parent_module<Waypoint>();
    ASSERT_NE(waypoint_parent_module, nullptr);
    ASSERT_GT(waypoint_parent_module, movable_controller_parent_module);

    GenericParentModule* const camera_parent_module = helsinki_scene->get_generic_parent_module<Camera>();
    ASSERT_NE(camera_parent_module, nullptr);
    ASSERT_GT(camera_parent_module, waypoint_parent_module);

    GenericParentModule* const pipeline_parent_module = helsinki_scene->get_generic_parent_module<Pipeline>();
    ASSERT_NE(pipeline_parent_module, nullptr);
    ASSERT_GT(pipeline_parent_module, camera_parent_module);

    GenericParentModule* const material_parent_module = helsinki_scene->get_generic_parent_module<Material>();
    ASSERT_NE(material_parent_module, nullptr);
    ASSERT_GT(material_parent_module, pipeline_parent_module);

    GenericParentModule* const species_parent_module = helsinki_scene->get_generic_parent_module<Species>();
    ASSERT_NE(species_parent_module, nullptr);
    ASSERT_GT(species_parent_module, material_parent_module);

    GenericParentModule* const object_parent_module = helsinki_scene->get_generic_parent_module<Object>();
    ASSERT_NE(object_parent_module, nullptr);
    ASSERT_GT(object_parent_module, species_parent_module);

    GenericParentModule* const symbiosis_parent_module = helsinki_scene->get_generic_parent_module<Symbiosis>();
    ASSERT_NE(symbiosis_parent_module, nullptr);
    ASSERT_GT(symbiosis_parent_module, object_parent_module);

    GenericParentModule* const holobiont_parent_module = helsinki_scene->get_generic_parent_module<Holobiont>();
    ASSERT_NE(holobiont_parent_module, nullptr);
    ASSERT_GT(holobiont_parent_module, symbiosis_parent_module);

    GenericParentModule* const shapeshifter_parent_module = helsinki_scene->get_generic_parent_module<Shapeshifter>();
    ASSERT_NE(shapeshifter_parent_module, nullptr);
    ASSERT_GT(shapeshifter_parent_module, holobiont_parent_module);

    GenericParentModule* const text_3d_parent_module = helsinki_scene->get_generic_parent_module<Text3d>();
    ASSERT_NE(text_3d_parent_module, nullptr);
    ASSERT_GT(text_3d_parent_module, shapeshifter_parent_module);

    GenericParentModule* const glyph_object_parent_module = helsinki_scene->get_generic_parent_module<GlyphObject>();
    ASSERT_NE(glyph_object_parent_module, nullptr);
    ASSERT_GT(glyph_object_parent_module, text_3d_parent_module);

    const GenericParentModule* const police_control_center_parent_module =
            helsinki_scene->get_generic_parent_module<PoliceControlCenter>();
    ASSERT_NE(police_control_center_parent_module, nullptr);
    ASSERT_GT(police_control_center_parent_module, glyph_object_parent_module);

    const GenericParentModule* const police_car_parent_module =
            helsinki_scene->get_generic_parent_module<PoliceCar>();
    ASSERT_NE(police_car_parent_module, nullptr);
    ASSERT_GT(police_car_parent_module, police_control_center_parent_module);

    const GenericParentModule* const police_dog_parent_module =
            helsinki_scene->get_generic_parent_module<PoliceDog>();
    ASSERT_NE(police_dog_parent_module, nullptr);
    ASSERT_GT(police_dog_parent_module, police_car_parent_module);

    const GenericParentModule* const police_helicopter_parent_module =
            helsinki_scene->get_generic_parent_module<PoliceHelicopter>();
    ASSERT_NE(police_helicopter_parent_module, nullptr);
    ASSERT_GT(police_helicopter_parent_module, police_dog_parent_module);

    const GenericParentModule* const police_horse_parent_module =
            helsinki_scene->get_generic_parent_module<PoliceHorse>();
    ASSERT_NE(police_horse_parent_module, nullptr);
    ASSERT_GT(police_horse_parent_module, police_helicopter_parent_module);

    const GenericParentModule* const police_train_parent_module =
            helsinki_scene->get_generic_parent_module<PoliceTrain>();
    ASSERT_NE(police_train_parent_module, nullptr);
    ASSERT_GT(police_train_parent_module, police_horse_parent_module);

    const GenericParentModule* const police_tram_parent_module =
            helsinki_scene->get_generic_parent_module<PoliceTram>();
    ASSERT_NE(police_tram_parent_module, nullptr);
    ASSERT_GT(police_tram_parent_module, police_train_parent_module);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(hirvi_application.get_universe().get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(helsinki_scene->get_scene(), helsinki_scene);
    ASSERT_EQ(helsinki_scene->get_number_of_non_variable_children(), 3); // Default `Camera`, 2 `PoliceControlCenter`s.

    // `Entity` member functions.
    ASSERT_EQ(helsinki_scene->get_childID(), 0);
    ASSERT_EQ(helsinki_scene->get_type(), "hirvi::ontology::HirviScene*");
    ASSERT_TRUE(helsinki_scene->get_can_be_erased());
    ASSERT_EQ(helsinki_scene->get_scene(), helsinki_scene);
    ASSERT_EQ(helsinki_scene->get_parent(), &hirvi_application.get_universe());
    ASSERT_EQ(helsinki_scene->get_number_of_non_variable_children(),
              3); // 1 default `Camera` + 2 `PoliceControlCenter`s.
}
