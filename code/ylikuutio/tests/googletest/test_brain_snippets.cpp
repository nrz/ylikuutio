// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2023 Antti Nuortimo.
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
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/callback_engine.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/object.hpp"
#include "code/ylikuutio/ontology/brain.hpp"
#include "code/ylikuutio/ontology/universe_struct.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"
#include "code/ylikuutio/ontology/object_struct.hpp"
#include "code/ylikuutio/ontology/brain_struct.hpp"
#include "code/ylikuutio/ontology/input_parameters_and_any_value_to_any_value_callback_with_universe.hpp"
#include "code/ylikuutio/snippets/brain_snippets.hpp"

TEST(rest_brain_must_not_change_location_or_orientation, object_with_speed_1)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(
            *universe,
            scene_struct,
            &universe->parent_of_scenes);

    InputParametersAndAnyValueToAnyValueCallbackWithUniverse callback = &yli::snippets::rest;
    yli::ontology::CallbackEngine* const rest_callback_engine = new yli::ontology::CallbackEngine(
            *universe,
            &universe->parent_of_callback_engines);
    rest_callback_engine->create_callback_object(callback);

    yli::ontology::BrainStruct rest_brain_struct;
    rest_brain_struct.parent = scene;
    rest_brain_struct.callback_engine = rest_callback_engine;
    yli::ontology::Brain* const rest_brain = new yli::ontology::Brain(
            *universe,
            rest_brain_struct,
            &scene->parent_of_brains);

    yli::ontology::ObjectStruct object_struct(scene);
    object_struct.cartesian_coordinates = { 1.0f, 2.0f, 3.0f }; // Whatever except NANs.
    object_struct.orientation =           { 4.0f, 5.0f, 6.0f }; // Whatever except NANs.
    yli::ontology::Object* const object = new yli::ontology::Object(
            *universe,
            object_struct,
            &scene->parent_of_objects,
            nullptr,
            &rest_brain->master_of_movables);

    yli::ontology::CartesianCoordinatesModule original_location(object->location);
    yli::ontology::OrientationModule original_orientation(object->orientation);

    ASSERT_EQ(object->location, original_location);
    ASSERT_EQ(object->orientation, original_orientation);

    rest_brain->act();

    ASSERT_EQ(object->location, original_location);
    ASSERT_EQ(object->orientation, original_orientation);
}
