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
#include "code/mock/mock_application.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/callback_engine.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/object.hpp"
#include "code/ylikuutio/ontology/brain.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"
#include "code/ylikuutio/ontology/object_struct.hpp"
#include "code/ylikuutio/ontology/brain_struct.hpp"
#include "code/ylikuutio/ontology/input_parameters_and_any_value_to_any_value_callback_with_universe.hpp"
#include "code/ylikuutio/snippets/brain_snippets.hpp"

// Include GLM
#ifndef GLM_GLM_HPP_INCLUDED
#define GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <numbers> // std::numbers::pi

TEST(rest_brain_must_not_change_location_or_orientation, object_with_speed_1)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    InputParametersAndAnyValueToAnyValueCallbackWithUniverse callback = &yli::snippets::rest;

    yli::ontology::CallbackEngineStruct rest_callback_engine_struct;
    yli::ontology::CallbackEngine* const rest_callback_engine = application.get_generic_entity_factory().create_callback_engine(
            rest_callback_engine_struct);

    rest_callback_engine->create_callback_object(callback);

    yli::ontology::BrainStruct rest_brain_struct;
    rest_brain_struct.parent = scene;
    rest_brain_struct.callback_engine = rest_callback_engine;
    yli::ontology::Brain* const rest_brain = application.get_generic_entity_factory().create_brain(
            rest_brain_struct);

    yli::ontology::ObjectStruct object_struct(rest_brain, scene);
    object_struct.cartesian_coordinates = { 1.0f, 2.0f, 3.0f }; // Whatever except NANs.
    object_struct.orientation =           { 4.0f, 5.0f, 6.0f }; // Whatever except NANs.
    yli::ontology::Object* const object = application.get_generic_entity_factory().create_object(
            object_struct);
    object->speed = 1.0f;

    yli::ontology::CartesianCoordinatesModule original_location(object->location);
    yli::ontology::OrientationModule original_orientation(object->orientation);

    ASSERT_EQ(object->location, original_location);
    ASSERT_EQ(object->orientation, original_orientation);

    rest_brain->act();

    ASSERT_EQ(object->location, original_location);
    ASSERT_EQ(object->orientation, original_orientation);
}

TEST(go_east_brain_must_go_east, object_with_speed_1)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    InputParametersAndAnyValueToAnyValueCallbackWithUniverse callback = &yli::snippets::go_east;

    yli::ontology::CallbackEngineStruct go_east_callback_engine_struct;
    yli::ontology::CallbackEngine* const go_east_callback_engine = application.get_generic_entity_factory().create_callback_engine(
            go_east_callback_engine_struct);

    go_east_callback_engine->create_callback_object(callback);

    yli::ontology::BrainStruct go_east_brain_struct;
    go_east_brain_struct.parent = scene;
    go_east_brain_struct.callback_engine = go_east_callback_engine;
    yli::ontology::Brain* const go_east_brain = application.get_generic_entity_factory().create_brain(
            go_east_brain_struct);

    yli::ontology::ObjectStruct object_struct(go_east_brain, scene);
    object_struct.cartesian_coordinates = { 1.0f, 2.0f, 3.0f }; // Whatever except NANs.
    object_struct.orientation =           { 4.0f, 5.0f, 6.0f }; // Whatever except NANs.
    yli::ontology::Object* const object = application.get_generic_entity_factory().create_object(
            object_struct);
    object->speed = 1.0f;

    yli::ontology::CartesianCoordinatesModule original_location(object->location);
    yli::ontology::OrientationModule original_orientation(object->orientation);

    ASSERT_EQ(object->location, original_location);
    ASSERT_EQ(object->orientation, original_orientation);

    glm::vec3 expected_coordinates { object->location.xyz + glm::vec3(1.0f, 0.0f, 0.0f) };

    go_east_brain->act();

    ASSERT_EQ(object->location.xyz, expected_coordinates);
    ASSERT_EQ(object->orientation, original_orientation);
}

TEST(go_west_brain_must_go_west, object_with_speed_1)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    InputParametersAndAnyValueToAnyValueCallbackWithUniverse callback = &yli::snippets::go_west;

    yli::ontology::CallbackEngineStruct go_west_callback_engine_struct;
    yli::ontology::CallbackEngine* const go_west_callback_engine = application.get_generic_entity_factory().create_callback_engine(
            go_west_callback_engine_struct);

    go_west_callback_engine->create_callback_object(callback);

    yli::ontology::BrainStruct go_west_brain_struct;
    go_west_brain_struct.parent = scene;
    go_west_brain_struct.callback_engine = go_west_callback_engine;
    yli::ontology::Brain* const go_west_brain = application.get_generic_entity_factory().create_brain(
            go_west_brain_struct);

    yli::ontology::ObjectStruct object_struct(go_west_brain, scene);
    object_struct.cartesian_coordinates = { 1.0f, 2.0f, 3.0f }; // Whatever except NANs.
    object_struct.orientation =           { 4.0f, 5.0f, 6.0f }; // Whatever except NANs.
    yli::ontology::Object* const object = application.get_generic_entity_factory().create_object(
            object_struct);
    object->speed = 1.0f;

    yli::ontology::CartesianCoordinatesModule original_location(object->location);
    yli::ontology::OrientationModule original_orientation(object->orientation);

    ASSERT_EQ(object->location, original_location);
    ASSERT_EQ(object->orientation, original_orientation);

    glm::vec3 expected_coordinates { object->location.xyz + glm::vec3(-1.0f, 0.0f, 0.0f) };

    go_west_brain->act();

    ASSERT_EQ(object->location.xyz, expected_coordinates);
    ASSERT_EQ(object->orientation, original_orientation);
}

TEST(go_north_brain_must_go_north, object_with_speed_1)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    InputParametersAndAnyValueToAnyValueCallbackWithUniverse callback = &yli::snippets::go_north;

    yli::ontology::CallbackEngineStruct go_north_callback_engine_struct;
    yli::ontology::CallbackEngine* const go_north_callback_engine = application.get_generic_entity_factory().create_callback_engine(
            go_north_callback_engine_struct);

    go_north_callback_engine->create_callback_object(callback);

    yli::ontology::BrainStruct go_north_brain_struct;
    go_north_brain_struct.parent = scene;
    go_north_brain_struct.callback_engine = go_north_callback_engine;
    yli::ontology::Brain* const go_north_brain = application.get_generic_entity_factory().create_brain(
            go_north_brain_struct);

    yli::ontology::ObjectStruct object_struct(go_north_brain, scene);
    object_struct.cartesian_coordinates = { 1.0f, 2.0f, 3.0f }; // Whatever except NANs.
    object_struct.orientation =           { 4.0f, 5.0f, 6.0f }; // Whatever except NANs.
    yli::ontology::Object* const object = application.get_generic_entity_factory().create_object(
            object_struct);
    object->speed = 1.0f;

    yli::ontology::CartesianCoordinatesModule original_location(object->location);
    yli::ontology::OrientationModule original_orientation(object->orientation);

    ASSERT_EQ(object->location, original_location);
    ASSERT_EQ(object->orientation, original_orientation);

    glm::vec3 expected_coordinates { object->location.xyz + glm::vec3(0.0f, 0.0f, -1.0f) };

    go_north_brain->act();

    ASSERT_EQ(object->location.xyz, expected_coordinates);
    ASSERT_EQ(object->orientation, original_orientation);
}

TEST(go_south_brain_must_go_south, object_with_speed_1)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    InputParametersAndAnyValueToAnyValueCallbackWithUniverse callback = &yli::snippets::go_south;

    yli::ontology::CallbackEngineStruct go_south_callback_engine_struct;
    yli::ontology::CallbackEngine* const go_south_callback_engine = application.get_generic_entity_factory().create_callback_engine(
            go_south_callback_engine_struct);

    go_south_callback_engine->create_callback_object(callback);

    yli::ontology::BrainStruct go_south_brain_struct;
    go_south_brain_struct.parent = scene;
    go_south_brain_struct.callback_engine = go_south_callback_engine;
    yli::ontology::Brain* const go_south_brain = application.get_generic_entity_factory().create_brain(
            go_south_brain_struct);

    yli::ontology::ObjectStruct object_struct(go_south_brain, scene);
    object_struct.cartesian_coordinates = { 1.0f, 2.0f, 3.0f }; // Whatever except NANs.
    object_struct.orientation =           { 4.0f, 5.0f, 6.0f }; // Whatever except NANs.
    yli::ontology::Object* const object = application.get_generic_entity_factory().create_object(
            object_struct);
    object->speed = 1.0f;

    yli::ontology::CartesianCoordinatesModule original_location(object->location);
    yli::ontology::OrientationModule original_orientation(object->orientation);

    ASSERT_EQ(object->location, original_location);
    ASSERT_EQ(object->orientation, original_orientation);

    glm::vec3 expected_coordinates { object->location.xyz + glm::vec3(0.0f, 0.0f, 1.0f) };

    go_south_brain->act();

    ASSERT_EQ(object->location.xyz, expected_coordinates);
    ASSERT_EQ(object->orientation, original_orientation);
}

TEST(orient_to_east_brain_must_orient_to_east, object_with_speed_1)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    InputParametersAndAnyValueToAnyValueCallbackWithUniverse callback = &yli::snippets::orient_to_east;

    yli::ontology::CallbackEngineStruct orient_to_east_callback_engine_struct;
    yli::ontology::CallbackEngine* const orient_to_east_callback_engine = application.get_generic_entity_factory().create_callback_engine(
            orient_to_east_callback_engine_struct);

    orient_to_east_callback_engine->create_callback_object(callback);

    yli::ontology::BrainStruct orient_to_east_brain_struct;
    orient_to_east_brain_struct.parent = scene;
    orient_to_east_brain_struct.callback_engine = orient_to_east_callback_engine;
    yli::ontology::Brain* const orient_to_east_brain = application.get_generic_entity_factory().create_brain(
            orient_to_east_brain_struct);

    yli::ontology::ObjectStruct object_struct(orient_to_east_brain, scene);
    object_struct.cartesian_coordinates = { 1.0f, 2.0f, 3.0f }; // Whatever except NANs.
    object_struct.orientation =           { 4.0f, 5.0f, 6.0f }; // Whatever except NANs.
    yli::ontology::Object* const object = application.get_generic_entity_factory().create_object(
            object_struct);
    object->speed = 1.0f;

    yli::ontology::CartesianCoordinatesModule original_location(object->location);
    yli::ontology::OrientationModule original_orientation(object->orientation);

    ASSERT_EQ(object->location, original_location);
    ASSERT_EQ(object->orientation, original_orientation);

    glm::vec3 expected_orientation { glm::vec3(object_struct.orientation.roll, 0.0f, object_struct.orientation.pitch) };

    orient_to_east_brain->act();

    ASSERT_EQ(object->location, original_location);
    ASSERT_EQ(object->orientation.get(), expected_orientation);
}

TEST(orient_to_west_brain_must_orient_to_west, object_with_speed_1)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    InputParametersAndAnyValueToAnyValueCallbackWithUniverse callback = &yli::snippets::orient_to_west;

    yli::ontology::CallbackEngineStruct orient_to_west_callback_engine_struct;
    yli::ontology::CallbackEngine* const orient_to_west_callback_engine = application.get_generic_entity_factory().create_callback_engine(
            orient_to_west_callback_engine_struct);

    orient_to_west_callback_engine->create_callback_object(callback);

    yli::ontology::BrainStruct orient_to_west_brain_struct;
    orient_to_west_brain_struct.parent = scene;
    orient_to_west_brain_struct.callback_engine = orient_to_west_callback_engine;
    yli::ontology::Brain* const orient_to_west_brain = application.get_generic_entity_factory().create_brain(
            orient_to_west_brain_struct);

    yli::ontology::ObjectStruct object_struct(orient_to_west_brain, scene);
    object_struct.cartesian_coordinates = { 1.0f, 2.0f, 3.0f }; // Whatever except NANs.
    object_struct.orientation =           { 4.0f, 5.0f, 6.0f }; // Whatever except NANs.
    yli::ontology::Object* const object = application.get_generic_entity_factory().create_object(
            object_struct);
    object->speed = 1.0f;

    yli::ontology::CartesianCoordinatesModule original_location(object->location);
    yli::ontology::OrientationModule original_orientation(object->orientation);

    ASSERT_EQ(object->location, original_location);
    ASSERT_EQ(object->orientation, original_orientation);

    glm::vec3 expected_orientation { glm::vec3(object_struct.orientation.roll, std::numbers::pi, object_struct.orientation.pitch) };

    orient_to_west_brain->act();

    ASSERT_EQ(object->location, original_location);
    ASSERT_EQ(object->orientation.get(), expected_orientation);
}

TEST(orient_to_north_brain_must_orient_to_north, object_with_speed_1)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    InputParametersAndAnyValueToAnyValueCallbackWithUniverse callback = &yli::snippets::orient_to_north;

    yli::ontology::CallbackEngineStruct orient_to_north_callback_engine_struct;
    yli::ontology::CallbackEngine* const orient_to_north_callback_engine = application.get_generic_entity_factory().create_callback_engine(
            orient_to_north_callback_engine_struct);

    orient_to_north_callback_engine->create_callback_object(callback);

    yli::ontology::BrainStruct orient_to_north_brain_struct;
    orient_to_north_brain_struct.parent = scene;
    orient_to_north_brain_struct.callback_engine = orient_to_north_callback_engine;
    yli::ontology::Brain* const orient_to_north_brain = application.get_generic_entity_factory().create_brain(
            orient_to_north_brain_struct);

    yli::ontology::ObjectStruct object_struct(orient_to_north_brain, scene);
    object_struct.cartesian_coordinates = { 1.0f, 2.0f, 3.0f }; // Whatever except NANs.
    object_struct.orientation =           { 4.0f, 5.0f, 6.0f }; // Whatever except NANs.
    yli::ontology::Object* const object = application.get_generic_entity_factory().create_object(
            object_struct);
    object->speed = 1.0f;

    yli::ontology::CartesianCoordinatesModule original_location(object->location);
    yli::ontology::OrientationModule original_orientation(object->orientation);

    ASSERT_EQ(object->location, original_location);
    ASSERT_EQ(object->orientation, original_orientation);

    glm::vec3 expected_orientation { glm::vec3(object_struct.orientation.roll, 0.5f * std::numbers::pi, object_struct.orientation.pitch) };

    orient_to_north_brain->act();

    ASSERT_EQ(object->location, original_location);
    ASSERT_EQ(object->orientation.get(), expected_orientation);
}

TEST(orient_to_south_brain_must_orient_to_south, object_with_speed_1)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    InputParametersAndAnyValueToAnyValueCallbackWithUniverse callback = &yli::snippets::orient_to_south;

    yli::ontology::CallbackEngineStruct orient_to_south_callback_engine_struct;
    yli::ontology::CallbackEngine* const orient_to_south_callback_engine = application.get_generic_entity_factory().create_callback_engine(
            orient_to_south_callback_engine_struct);

    orient_to_south_callback_engine->create_callback_object(callback);

    yli::ontology::BrainStruct orient_to_south_brain_struct;
    orient_to_south_brain_struct.parent = scene;
    orient_to_south_brain_struct.callback_engine = orient_to_south_callback_engine;
    yli::ontology::Brain* const orient_to_south_brain = application.get_generic_entity_factory().create_brain(
            orient_to_south_brain_struct);

    yli::ontology::ObjectStruct object_struct(orient_to_south_brain, scene);
    object_struct.cartesian_coordinates = { 1.0f, 2.0f, 3.0f }; // Whatever except NANs.
    object_struct.orientation =           { 4.0f, 5.0f, 6.0f }; // Whatever except NANs.
    yli::ontology::Object* const object = application.get_generic_entity_factory().create_object(
            object_struct);
    object->speed = 1.0f;

    yli::ontology::CartesianCoordinatesModule original_location(object->location);
    yli::ontology::OrientationModule original_orientation(object->orientation);

    ASSERT_EQ(object->location, original_location);
    ASSERT_EQ(object->orientation, original_orientation);

    glm::vec3 expected_orientation { glm::vec3(object_struct.orientation.roll, -0.5f * std::numbers::pi, object_struct.orientation.pitch) };

    orient_to_south_brain->act();

    ASSERT_EQ(object->location, original_location);
    ASSERT_EQ(object->orientation.get(), expected_orientation);
}

TEST(orient_and_go_east_brain_must_orient_and_go_east, object_with_speed_1)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    InputParametersAndAnyValueToAnyValueCallbackWithUniverse callback = &yli::snippets::orient_and_go_east;

    yli::ontology::CallbackEngineStruct orient_and_go_east_callback_engine_struct;
    yli::ontology::CallbackEngine* const orient_and_go_east_callback_engine = application.get_generic_entity_factory().create_callback_engine(
            orient_and_go_east_callback_engine_struct);

    orient_and_go_east_callback_engine->create_callback_object(callback);

    yli::ontology::BrainStruct orient_and_go_east_brain_struct;
    orient_and_go_east_brain_struct.parent = scene;
    orient_and_go_east_brain_struct.callback_engine = orient_and_go_east_callback_engine;
    yli::ontology::Brain* const orient_and_go_east_brain = application.get_generic_entity_factory().create_brain(
            orient_and_go_east_brain_struct);

    yli::ontology::ObjectStruct object_struct(orient_and_go_east_brain, scene);
    object_struct.cartesian_coordinates = { 1.0f, 2.0f, 3.0f }; // Whatever except NANs.
    object_struct.orientation =           { 4.0f, 5.0f, 6.0f }; // Whatever except NANs.
    yli::ontology::Object* const object = application.get_generic_entity_factory().create_object(
            object_struct);
    object->speed = 1.0f;

    yli::ontology::CartesianCoordinatesModule original_location(object->location);
    yli::ontology::OrientationModule original_orientation(object->orientation);

    ASSERT_EQ(object->location, original_location);
    ASSERT_EQ(object->orientation, original_orientation);

    glm::vec3 expected_coordinates { object->location.xyz + glm::vec3(1.0f, 0.0f, 0.0f) };
    glm::vec3 expected_orientation { glm::vec3(object_struct.orientation.roll, 0.0f, object_struct.orientation.pitch) };

    orient_and_go_east_brain->act();

    ASSERT_EQ(object->location.xyz, expected_coordinates);
    ASSERT_EQ(object->orientation.get(), expected_orientation);
}
