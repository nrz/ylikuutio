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
#include "code/ylikuutio/memory/constructible_module.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"

// Include standard headers
#include <cstdint> // uintptr_t

TEST(scene_must_be_initialized_appropriately, hirvi_scene)
{
    constexpr int argc { 0 };
    const char** const argv { nullptr };
    const hirvi::HirviApplication hirvi_application(argc, argv);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.global_name = "helsinki_scene";
    scene_struct.light_position = { 0.0f, -100000.0f, 100000.0f, 1.0f };
    scene_struct.water_level = 0.9f;
    yli::ontology::Scene* const helsinki_scene = hirvi_application.get_entity_factory().create_scene(scene_struct);
    ASSERT_NE(helsinki_scene, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(helsinki_scene) % alignof(yli::ontology::Scene), 0);
    const yli::memory::ConstructibleModule scene_constructible_module = helsinki_scene->get_constructible_module();
    ASSERT_EQ(scene_constructible_module.storage_i, 0);
    ASSERT_EQ(scene_constructible_module.slot_i, 0);
    ASSERT_EQ(scene_constructible_module.alive, true);

    yli::ontology::GenericParentModule* const movable_controller_parent_module = helsinki_scene->get_generic_parent_module<yli::ontology::MovableController>();
    ASSERT_NE(movable_controller_parent_module, nullptr);

    yli::ontology::GenericParentModule* const waypoint_parent_module = helsinki_scene->get_generic_parent_module<yli::ontology::Waypoint>();
    ASSERT_NE(waypoint_parent_module, nullptr);
    ASSERT_GT(waypoint_parent_module, movable_controller_parent_module);

    yli::ontology::GenericParentModule* const camera_parent_module = helsinki_scene->get_generic_parent_module<yli::ontology::Camera>();
    ASSERT_NE(camera_parent_module, nullptr);
    ASSERT_GT(camera_parent_module, waypoint_parent_module);

    yli::ontology::GenericParentModule* const pipeline_parent_module = helsinki_scene->get_generic_parent_module<yli::ontology::Pipeline>();
    ASSERT_NE(pipeline_parent_module, nullptr);
    ASSERT_GT(pipeline_parent_module, camera_parent_module);

    yli::ontology::GenericParentModule* const material_parent_module = helsinki_scene->get_generic_parent_module<yli::ontology::Material>();
    ASSERT_NE(material_parent_module, nullptr);
    ASSERT_GT(material_parent_module, pipeline_parent_module);

    yli::ontology::GenericParentModule* const species_parent_module = helsinki_scene->get_generic_parent_module<yli::ontology::Species>();
    ASSERT_NE(species_parent_module, nullptr);
    ASSERT_GT(species_parent_module, material_parent_module);

    yli::ontology::GenericParentModule* const object_parent_module = helsinki_scene->get_generic_parent_module<yli::ontology::Object>();
    ASSERT_NE(object_parent_module, nullptr);
    ASSERT_GT(object_parent_module, species_parent_module);

    yli::ontology::GenericParentModule* const symbiosis_parent_module = helsinki_scene->get_generic_parent_module<yli::ontology::Symbiosis>();
    ASSERT_NE(symbiosis_parent_module, nullptr);
    ASSERT_GT(symbiosis_parent_module, object_parent_module);

    yli::ontology::GenericParentModule* const holobiont_parent_module = helsinki_scene->get_generic_parent_module<yli::ontology::Holobiont>();
    ASSERT_NE(holobiont_parent_module, nullptr);
    ASSERT_GT(holobiont_parent_module, symbiosis_parent_module);

    yli::ontology::GenericParentModule* const shapeshifter_parent_module = helsinki_scene->get_generic_parent_module<yli::ontology::Shapeshifter>();
    ASSERT_NE(shapeshifter_parent_module, nullptr);
    ASSERT_GT(shapeshifter_parent_module, holobiont_parent_module);

    yli::ontology::GenericParentModule* const text_3d_parent_module = helsinki_scene->get_generic_parent_module<yli::ontology::Text3d>();
    ASSERT_NE(text_3d_parent_module, nullptr);
    ASSERT_GT(text_3d_parent_module, shapeshifter_parent_module);

    yli::ontology::GenericParentModule* const glyph_object_parent_module = helsinki_scene->get_generic_parent_module<yli::ontology::GlyphObject>();
    ASSERT_NE(glyph_object_parent_module, nullptr);
    ASSERT_GT(glyph_object_parent_module, text_3d_parent_module);
}
