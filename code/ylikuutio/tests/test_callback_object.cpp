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
#include "code/mock/mock_application.hpp"
#include "code/ylikuutio/data/datatype.hpp"
#include "code/ylikuutio/ontology/callback_engine.hpp"
#include "code/ylikuutio/ontology/callback_object.hpp"
#include "code/ylikuutio/ontology/callback_engine_struct.hpp"
#include "code/ylikuutio/ontology/callback_object_struct.hpp"

// Include standard headers
#include <cstddef> // std::size_t, uintptr_t
#include <limits>  // std::numeric_limits

namespace yli::ontology
{
    class GenericParentModule;
    class CallbackEngine;
}

TEST(callback_object_must_be_initialized_appropriately, headless_with_parent_provided_as_valid_pointer)
{
    mock::MockApplication application;
    yli::ontology::CallbackEngineStruct callback_engine_struct;
    yli::ontology::CallbackEngine* const callback_engine = application.get_generic_entity_factory().create_callback_engine(
            callback_engine_struct);

    const yli::ontology::CallbackObjectStruct callback_object_struct(callback_engine);
    yli::ontology::CallbackObject* const callback_object = application.get_generic_entity_factory().create_callback_object(
            callback_object_struct);
    ASSERT_NE(callback_object, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(callback_object) % alignof(yli::ontology::CallbackObject), 0);

    for (int datatype = 0; datatype < yli::data::Datatype::MAX_VALUE; datatype++)
    {
        const yli::ontology::GenericParentModule* const generic_parent_module = callback_object->get_generic_parent_module(datatype);

        if (datatype == yli::data::Datatype::CALLBACK_PARAMETER)
        {
            ASSERT_NE(generic_parent_module, nullptr);
        }
        else
        {
            ASSERT_EQ(generic_parent_module, nullptr);
        }
    }

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1); // `callback_engine`.

    // `Entity` member functions of `CallbackEngine`.
    ASSERT_EQ(callback_engine->get_scene(), nullptr);
    ASSERT_EQ(callback_engine->get_number_of_non_variable_children(), 1); // `callback_object`.

    // `Entity` member functions.
    ASSERT_EQ(callback_object->get_childID(), 0);
    ASSERT_EQ(callback_object->get_type(), "yli::ontology::CallbackObject*");
    ASSERT_FALSE(callback_object->get_can_be_erased());
    ASSERT_EQ(callback_object->get_scene(), nullptr);
    ASSERT_EQ(callback_object->get_parent(), callback_engine);
    ASSERT_EQ(callback_object->get_number_of_non_variable_children(), 0);
}

TEST(callback_object_must_be_initialized_appropriately, headless_with_parent_provided_as_nullptr)
{
    mock::MockApplication application;
    yli::ontology::CallbackEngineStruct callback_engine_struct;
    yli::ontology::CallbackEngine* const callback_engine = application.get_generic_entity_factory().create_callback_engine(
            callback_engine_struct);

    const yli::ontology::CallbackObjectStruct callback_object_struct(static_cast<yli::ontology::CallbackEngine*>(nullptr));
    yli::ontology::CallbackObject* const callback_object = application.get_generic_entity_factory().create_callback_object(
            callback_object_struct);
    ASSERT_NE(callback_object, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(callback_object) % alignof(yli::ontology::CallbackObject), 0);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1); // `callback_engine`.   

    // `Entity` member functions of `CallbackEngine`.
    ASSERT_EQ(callback_engine->get_scene(), nullptr);
    ASSERT_EQ(callback_engine->get_number_of_non_variable_children(), 0);

    // `Entity` member functions.
    ASSERT_EQ(callback_object->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(callback_object->get_type(), "yli::ontology::CallbackObject*");
    ASSERT_FALSE(callback_object->get_can_be_erased());
    ASSERT_EQ(callback_object->get_scene(), nullptr);
    ASSERT_EQ(callback_object->get_parent(), nullptr);
    ASSERT_EQ(callback_object->get_number_of_non_variable_children(), 0);
}

TEST(callback_object_must_be_initialized_appropriately, parent_provided_as_valid_global_name)
{
    mock::MockApplication application;
    yli::ontology::CallbackEngineStruct callback_engine_struct;
    callback_engine_struct.global_name = "foo";
    yli::ontology::CallbackEngine* const callback_engine = application.get_generic_entity_factory().create_callback_engine(
            callback_engine_struct);

    const yli::ontology::CallbackObjectStruct callback_object_struct("foo");
    yli::ontology::CallbackObject* const callback_object = application.get_generic_entity_factory().create_callback_object(
            callback_object_struct);
    ASSERT_NE(callback_object, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(callback_object) % alignof(yli::ontology::CallbackObject), 0);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1); // `callback_engine`.

    // `Entity` member functions of `CallbackEngine`.
    ASSERT_EQ(callback_engine->get_scene(), nullptr);
    ASSERT_EQ(callback_engine->get_number_of_non_variable_children(), 1);

    // `Entity` member functions.
    ASSERT_EQ(callback_object->get_childID(), 0);
    ASSERT_EQ(callback_object->get_type(), "yli::ontology::CallbackObject*");
    ASSERT_FALSE(callback_object->get_can_be_erased());
    ASSERT_EQ(callback_object->get_scene(), nullptr);
    ASSERT_EQ(callback_object->get_parent(), callback_engine);
    ASSERT_EQ(callback_object->get_number_of_non_variable_children(), 0);
}

TEST(callback_object_must_be_initialized_appropriately, parent_provided_as_invalid_global_name)
{
    mock::MockApplication application;
    yli::ontology::CallbackEngineStruct callback_engine_struct;
    callback_engine_struct.global_name = "foo";
    yli::ontology::CallbackEngine* const callback_engine = application.get_generic_entity_factory().create_callback_engine(
            callback_engine_struct);

    const yli::ontology::CallbackObjectStruct callback_object_struct("bar");
    yli::ontology::CallbackObject* const callback_object = application.get_generic_entity_factory().create_callback_object(
            callback_object_struct);
    ASSERT_NE(callback_object, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(callback_object) % alignof(yli::ontology::CallbackObject), 0);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1); // `callback_engine`.

    // `Entity` member functions of `CallbackEngine`.
    ASSERT_EQ(callback_engine->get_scene(), nullptr);
    ASSERT_EQ(callback_engine->get_number_of_non_variable_children(), 0);

    // `Entity` member functions.
    ASSERT_EQ(callback_object->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(callback_object->get_type(), "yli::ontology::CallbackObject*");
    ASSERT_FALSE(callback_object->get_can_be_erased());
    ASSERT_EQ(callback_object->get_scene(), nullptr);
    ASSERT_EQ(callback_object->get_parent(), nullptr);
    ASSERT_EQ(callback_object->get_number_of_non_variable_children(), 0);
}
