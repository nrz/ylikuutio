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
#include "code/hirvi/ontology/cat.hpp"
#include "code/ylikuutio/snippets/brain_snippets.hpp"
#include "code/ylikuutio/memory/constructible_module.hpp"
#include "code/ylikuutio/ontology/callback_engine.hpp"
#include "code/ylikuutio/ontology/brain.hpp"
#include "code/ylikuutio/ontology/request.hpp"
#include "code/ylikuutio/ontology/brain_struct.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"

// Include standard headers
#include <cstddef> // uintptr_t

namespace yli::ontology
{
    class Scene;
}

TEST(brain_must_be_initialized_appropriately, hirvi_brain)
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
    ASSERT_NE(rest_brain, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(rest_brain) % alignof(Brain), 0);
    yli::memory::ConstructibleModule brain_constructible_module = rest_brain->get_constructible_module();
    ASSERT_EQ(brain_constructible_module.storage_i, 0);
    ASSERT_EQ(brain_constructible_module.slot_i, 0);
    ASSERT_EQ(brain_constructible_module.alive, true);
}
