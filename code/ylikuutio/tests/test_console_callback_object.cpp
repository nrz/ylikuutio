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
#include "code/ylikuutio/ontology/console_callback_engine.hpp"
#include "code/ylikuutio/ontology/console_callback_object.hpp"
#include "code/ylikuutio/ontology/request.hpp"
#include "code/ylikuutio/ontology/console_callback_engine_struct.hpp"
#include "code/ylikuutio/ontology/console_callback_object_struct.hpp"

// Include standard headers
#include <cstddef> // std::size_t, uintptr_t
#include <limits>  // std::numeric_limits

namespace yli::ontology
{
    class GenericParentModule;
    class Console;
    class ConsoleCallbackEngine;
    class ConsoleCallbackParameter;
}

TEST(console_callback_object_must_be_initialized_appropriately, headless_with_parent_provided_as_valid_pointer)
{
    mock::MockApplication application;
    yli::ontology::ConsoleCallbackEngineStruct console_callback_engine_struct { yli::ontology::Request<yli::ontology::Console>(nullptr) };
    yli::ontology::ConsoleCallbackEngine* const console_callback_engine = application.get_generic_entity_factory().create_console_callback_engine(
            console_callback_engine_struct);

    const yli::ontology::ConsoleCallbackObjectStruct console_callback_object_struct { yli::ontology::Request(console_callback_engine) };
    yli::ontology::ConsoleCallbackObject* const console_callback_object = application.get_generic_entity_factory().create_console_callback_object(
            console_callback_object_struct);
    ASSERT_NE(console_callback_object, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(console_callback_object) % alignof(yli::ontology::ConsoleCallbackObject), 0);

    const yli::ontology::GenericParentModule* const parent_of_console_callback_parameters =
        console_callback_object->get_generic_parent_module<yli::ontology::ConsoleCallbackParameter>();
    ASSERT_NE(parent_of_console_callback_parameters, nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 0);

    // `Entity` member functions of `ConsoleCallbackEngine`.
    ASSERT_EQ(console_callback_engine->get_scene(), nullptr);
    ASSERT_EQ(console_callback_engine->get_number_of_non_variable_children(), 1); // `console_callback_object`.

    // `Entity` member functions.
    ASSERT_EQ(console_callback_object->get_childID(), 0);
    ASSERT_EQ(console_callback_object->get_type(), "yli::ontology::ConsoleCallbackObject*");
    ASSERT_FALSE(console_callback_object->get_can_be_erased());
    ASSERT_EQ(console_callback_object->get_scene(), nullptr);
    ASSERT_EQ(console_callback_object->get_parent(), console_callback_engine);
    ASSERT_EQ(console_callback_object->get_number_of_non_variable_children(), 0);
}

TEST(console_callback_object_must_be_initialized_appropriately, headless_with_parent_provided_as_nullptr)
{
    mock::MockApplication application;
    yli::ontology::ConsoleCallbackEngineStruct console_callback_engine_struct { yli::ontology::Request<yli::ontology::Console>(nullptr) };
    yli::ontology::ConsoleCallbackEngine* const console_callback_engine = application.get_generic_entity_factory().create_console_callback_engine(
            console_callback_engine_struct);

    const yli::ontology::ConsoleCallbackObjectStruct console_callback_object_struct { yli::ontology::Request<yli::ontology::ConsoleCallbackEngine>(nullptr) };
    yli::ontology::ConsoleCallbackObject* const console_callback_object = application.get_generic_entity_factory().create_console_callback_object(
            console_callback_object_struct);
    ASSERT_NE(console_callback_object, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(console_callback_object) % alignof(yli::ontology::ConsoleCallbackObject), 0);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 0);

    // `Entity` member functions of `ConsoleCallbackEngine`.
    ASSERT_EQ(console_callback_engine->get_scene(), nullptr);
    ASSERT_EQ(console_callback_engine->get_number_of_non_variable_children(), 0);

    // `Entity` member functions.
    ASSERT_EQ(console_callback_object->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(console_callback_object->get_type(), "yli::ontology::ConsoleCallbackObject*");
    ASSERT_FALSE(console_callback_object->get_can_be_erased());
    ASSERT_EQ(console_callback_object->get_scene(), nullptr);
    ASSERT_EQ(console_callback_object->get_parent(), nullptr);
    ASSERT_EQ(console_callback_object->get_number_of_non_variable_children(), 0);
}

TEST(console_callback_object_must_be_initialized_appropriately, parent_provided_as_valid_global_name)
{
    mock::MockApplication application;
    yli::ontology::ConsoleCallbackEngineStruct console_callback_engine_struct { yli::ontology::Request<yli::ontology::Console>(nullptr) };
    console_callback_engine_struct.global_name = "foo";
    yli::ontology::ConsoleCallbackEngine* const console_callback_engine = application.get_generic_entity_factory().create_console_callback_engine(
            console_callback_engine_struct);

    const yli::ontology::ConsoleCallbackObjectStruct console_callback_object_struct { yli::ontology::Request<yli::ontology::ConsoleCallbackEngine>("foo") };
    yli::ontology::ConsoleCallbackObject* const console_callback_object = application.get_generic_entity_factory().create_console_callback_object(
            console_callback_object_struct);
    ASSERT_NE(console_callback_object, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(console_callback_object) % alignof(yli::ontology::ConsoleCallbackObject), 0);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 0);

    // `Entity` member functions of `ConsoleCallbackEngine`.
    ASSERT_EQ(console_callback_engine->get_scene(), nullptr);
    ASSERT_EQ(console_callback_engine->get_number_of_non_variable_children(), 1);

    // `Entity` member functions.
    ASSERT_EQ(console_callback_object->get_childID(), 0);
    ASSERT_EQ(console_callback_object->get_type(), "yli::ontology::ConsoleCallbackObject*");
    ASSERT_FALSE(console_callback_object->get_can_be_erased());
    ASSERT_EQ(console_callback_object->get_scene(), nullptr);
    ASSERT_EQ(console_callback_object->get_parent(), console_callback_engine);
    ASSERT_EQ(console_callback_object->get_number_of_non_variable_children(), 0);
}

TEST(console_callback_object_must_be_initialized_appropriately, parent_provided_as_invalid_global_name)
{
    mock::MockApplication application;
    yli::ontology::ConsoleCallbackEngineStruct console_callback_engine_struct { yli::ontology::Request<yli::ontology::Console>(nullptr) };
    console_callback_engine_struct.global_name = "foo";
    yli::ontology::ConsoleCallbackEngine* const console_callback_engine = application.get_generic_entity_factory().create_console_callback_engine(
            console_callback_engine_struct);

    const yli::ontology::ConsoleCallbackObjectStruct console_callback_object_struct { yli::ontology::Request<yli::ontology::ConsoleCallbackEngine>("bar") };
    yli::ontology::ConsoleCallbackObject* const console_callback_object = application.get_generic_entity_factory().create_console_callback_object(
            console_callback_object_struct);
    ASSERT_NE(console_callback_object, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(console_callback_object) % alignof(yli::ontology::ConsoleCallbackObject), 0);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 0);

    // `Entity` member functions of `ConsoleCallbackEngine`.
    ASSERT_EQ(console_callback_engine->get_scene(), nullptr);
    ASSERT_EQ(console_callback_engine->get_number_of_non_variable_children(), 0);

    // `Entity` member functions.
    ASSERT_EQ(console_callback_object->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(console_callback_object->get_type(), "yli::ontology::ConsoleCallbackObject*");
    ASSERT_FALSE(console_callback_object->get_can_be_erased());
    ASSERT_EQ(console_callback_object->get_scene(), nullptr);
    ASSERT_EQ(console_callback_object->get_parent(), nullptr);
    ASSERT_EQ(console_callback_object->get_number_of_non_variable_children(), 0);
}
