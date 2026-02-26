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
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/ontology/entity.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/variable.hpp"
#include "code/ylikuutio/ontology/lisp_context.hpp"
#include "code/ylikuutio/ontology/console.hpp"
#include "code/ylikuutio/ontology/request.hpp"
#include "code/ylikuutio/ontology/movable_variable_activation.hpp"
#include "code/ylikuutio/ontology/movable_variable_read.hpp"
#include "code/ylikuutio/ontology/variable_struct.hpp"
#include "code/ylikuutio/ontology/console_struct.hpp"

// Include standard headers
#include <string> // std::string
#include <vector> // std::vector

namespace yli::ontology
{
    class GenericLispFunctionOverload;
}

using yli::ontology::LispContext;

TEST(variables_lisp_function_overload_must_function_appropriately, variables)
{
    mock::MockApplication application;

    yli::ontology::ConsoleStruct my_console_struct(0, 39, 15, 0); // Some dummy dimensions.
    yli::ontology::Console* const my_console = application.get_generic_entity_factory().create_console(my_console_struct);
    ASSERT_NE(my_console, nullptr);

    const std::string lisp_function_name = "variables";
    yli::ontology::GenericLispFunctionOverload* const lisp_function_overload = application.get_entity_factory().create_lisp_function_overload(
            lisp_function_name,
            yli::ontology::Request<LispContext>(my_console),
            &yli::ontology::Entity::print_variables0);

    ASSERT_NE(lisp_function_overload, nullptr);
    // `LispfunctionOverload` is allocated in using standard allocator so proper alignment should be guaranteed.

    // TODO: `variables` should return a list of variables and not print them in console!
    // Once that is done create a test that counts the number of variables first from the list, creates a new variable, and
    // and then counts the number of variables first from the list again!
}

TEST(set_lisp_function_overload_must_function_appropriately, set)
{
    mock::MockApplication application;

    yli::ontology::ConsoleStruct my_console_struct(0, 39, 15, 0); // Some dummy dimensions.
    yli::ontology::Console* const my_console = application.get_generic_entity_factory().create_console(my_console_struct);
    ASSERT_NE(my_console, nullptr);

    const std::string lisp_function_name = "set";
    yli::ontology::GenericLispFunctionOverload* const lisp_function_overload = application.get_entity_factory().create_lisp_function_overload(
            lisp_function_name,
            yli::ontology::Request<LispContext>(my_console),
            &yli::ontology::Variable::set_variable_const_std_string);

    ASSERT_NE(lisp_function_overload, nullptr);
}

TEST(set_must_set_global_x, set_x)
{
    mock::MockApplication application;
    yli::ontology::Universe& universe = application.get_universe();

    yli::ontology::ConsoleStruct my_console_struct(0, 39, 15, 0); // Some dummy dimensions.
    yli::ontology::Console* const my_console = application.get_generic_entity_factory().create_console(my_console_struct);

    const std::string lisp_function_name = "set";
    yli::ontology::GenericLispFunctionOverload* const lisp_function_overload = application.get_entity_factory().create_lisp_function_overload(
            lisp_function_name,
            yli::ontology::Request<LispContext>(my_console),
            &yli::ontology::Variable::set_variable_const_std_string);

    yli::ontology::SceneStruct scene_struct;
    // Creating a `Scene` creates a default `Camera` and makes it the currently active `Camera`.
    application.get_generic_entity_factory().create_scene(scene_struct);

    float x = 1234.25f;
    yli::ontology::VariableStruct x_variable_struct(universe, &universe);
    x_variable_struct.local_name = "x";
    x_variable_struct.activate_callback = &yli::ontology::activate_x;
    x_variable_struct.read_callback = &yli::ontology::read_x;
    x_variable_struct.should_call_activate_callback_now = true;
    ASSERT_EQ(universe.get_variable("x"), nullptr);
    universe.create_variable(x_variable_struct, yli::data::AnyValue(x));

    {
        const float x = universe.get_x();
        ASSERT_EQ(x, 1234.25f);
    }

    {
        lisp_function_overload->execute({ "x", "123" });
        const float x = universe.get_x();
        ASSERT_EQ(x, 123.0f);
    }
}

TEST(set_must_set_global_y, set_y)
{
    mock::MockApplication application;
    yli::ontology::Universe& universe = application.get_universe();

    yli::ontology::ConsoleStruct my_console_struct(0, 39, 15, 0); // Some dummy dimensions.
    yli::ontology::Console* const my_console = application.get_generic_entity_factory().create_console(my_console_struct);

    const std::string lisp_function_name = "set";
    yli::ontology::GenericLispFunctionOverload* const lisp_function_overload = application.get_entity_factory().create_lisp_function_overload(
            lisp_function_name,
            yli::ontology::Request<LispContext>(my_console),
            &yli::ontology::Variable::set_variable_const_std_string);

    yli::ontology::SceneStruct scene_struct;
    // Creating a `Scene` creates a default `Camera` and makes it the currently active `Camera`.
    application.get_generic_entity_factory().create_scene(scene_struct);

    float y = 1234.25f;
    yli::ontology::VariableStruct y_variable_struct(universe, &universe);
    y_variable_struct.local_name = "y";
    y_variable_struct.activate_callback = &yli::ontology::activate_y;
    y_variable_struct.read_callback = &yli::ontology::read_y;
    y_variable_struct.should_call_activate_callback_now = true;
    ASSERT_EQ(universe.get_variable("y"), nullptr);
    universe.create_variable(y_variable_struct, yli::data::AnyValue(y));

    {
        const float y = universe.get_y();
        ASSERT_EQ(y, 1234.25f);
    }

    {
        lisp_function_overload->execute({ "y", "123" });
        const float y = universe.get_y();
        ASSERT_EQ(y, 123.0f);
    }
}

TEST(set_must_set_global_z, set_z)
{
    mock::MockApplication application;
    yli::ontology::Universe& universe = application.get_universe();

    yli::ontology::ConsoleStruct my_console_struct(0, 39, 15, 0); // Some dummy dimensions.
    yli::ontology::Console* const my_console = application.get_generic_entity_factory().create_console(my_console_struct);

    const std::string lisp_function_name = "set";
    yli::ontology::GenericLispFunctionOverload* const lisp_function_overload = application.get_entity_factory().create_lisp_function_overload(
            lisp_function_name,
            yli::ontology::Request<LispContext>(my_console),
            &yli::ontology::Variable::set_variable_const_std_string);

    yli::ontology::SceneStruct scene_struct;
    // Creating a `Scene` creates a default `Camera` and makes it the currently active `Camera`.
    application.get_generic_entity_factory().create_scene(scene_struct);

    float z = 1234.25f;
    yli::ontology::VariableStruct z_variable_struct(universe, &universe);
    z_variable_struct.local_name = "z";
    z_variable_struct.activate_callback = &yli::ontology::activate_z;
    z_variable_struct.read_callback = &yli::ontology::read_z;
    z_variable_struct.should_call_activate_callback_now = true;
    ASSERT_EQ(universe.get_variable("z"), nullptr);
    universe.create_variable(z_variable_struct, yli::data::AnyValue(z));

    {
        const float z = universe.get_z();
        ASSERT_EQ(z, 1234.25f);
    }

    {
        lisp_function_overload->execute({ "z", "123" });
        const float z = universe.get_z();
        ASSERT_EQ(z, 123.0f);
    }
}

TEST(set_must_set_global_roll, set_roll)
{
    mock::MockApplication application;
    yli::ontology::Universe& universe = application.get_universe();

    yli::ontology::ConsoleStruct my_console_struct(0, 39, 15, 0); // Some dummy dimensions.
    yli::ontology::Console* const my_console = application.get_generic_entity_factory().create_console(my_console_struct);

    const std::string lisp_function_name = "set";
    yli::ontology::GenericLispFunctionOverload* const lisp_function_overload = application.get_entity_factory().create_lisp_function_overload(
            lisp_function_name,
            yli::ontology::Request<LispContext>(my_console),
            &yli::ontology::Variable::set_variable_const_std_string);

    yli::ontology::SceneStruct scene_struct;
    // Creating a `Scene` creates a default `Camera` and makes it the currently active `Camera`.
    application.get_generic_entity_factory().create_scene(scene_struct);

    const float roll = 0.0f;
    yli::ontology::VariableStruct roll_variable_struct(universe, &universe);
    roll_variable_struct.local_name = "roll";
    roll_variable_struct.activate_callback = &yli::ontology::activate_roll;
    roll_variable_struct.read_callback = &yli::ontology::read_roll;
    roll_variable_struct.should_call_activate_callback_now = true;
    universe.create_variable(roll_variable_struct, yli::data::AnyValue(roll));

    {
        const float roll = universe.get_roll();
        ASSERT_EQ(roll, 0.0f);
    }

    {
        lisp_function_overload->execute({ "roll", "1.25" });
        const float roll = universe.get_roll();
        ASSERT_EQ(roll, 1.25f);
    }
}

TEST(set_must_set_global_yaw, set_yaw)
{
    mock::MockApplication application;
    yli::ontology::Universe& universe = application.get_universe();

    yli::ontology::ConsoleStruct my_console_struct(0, 39, 15, 0); // Some dummy dimensions.
    yli::ontology::Console* const my_console = application.get_generic_entity_factory().create_console(my_console_struct);

    const std::string lisp_function_name = "set";
    yli::ontology::GenericLispFunctionOverload* const lisp_function_overload = application.get_entity_factory().create_lisp_function_overload(
            lisp_function_name,
            yli::ontology::Request<LispContext>(my_console),
            &yli::ontology::Variable::set_variable_const_std_string);

    yli::ontology::SceneStruct scene_struct;
    // Creating a `Scene` creates a default `Camera` and makes it the currently active `Camera`.
    application.get_generic_entity_factory().create_scene(scene_struct);

    const float yaw = 0.0f;
    yli::ontology::VariableStruct yaw_variable_struct(universe, &universe);
    yaw_variable_struct.local_name = "yaw";
    yaw_variable_struct.activate_callback = &yli::ontology::activate_yaw;
    yaw_variable_struct.read_callback = &yli::ontology::read_yaw;
    yaw_variable_struct.should_call_activate_callback_now = true;
    universe.create_variable(yaw_variable_struct, yli::data::AnyValue(yaw));

    {
        const float yaw = universe.get_yaw();
        ASSERT_EQ(yaw, 0.0f);
    }

    {
        lisp_function_overload->execute({ "yaw", "1.25" });
        const float yaw = universe.get_yaw();
        ASSERT_EQ(yaw, 1.25f);
    }
}

TEST(set_must_set_global_pitch, set_pitch)
{
    mock::MockApplication application;
    yli::ontology::Universe& universe = application.get_universe();

    yli::ontology::ConsoleStruct my_console_struct(0, 39, 15, 0); // Some dummy dimensions.
    yli::ontology::Console* const my_console = application.get_generic_entity_factory().create_console(my_console_struct);

    const std::string lisp_function_name = "set";
    yli::ontology::GenericLispFunctionOverload* const lisp_function_overload = application.get_entity_factory().create_lisp_function_overload(
            lisp_function_name,
            yli::ontology::Request<LispContext>(my_console),
            &yli::ontology::Variable::set_variable_const_std_string);

    yli::ontology::SceneStruct scene_struct;
    // Creating a `Scene` creates a default `Camera` and makes it the currently active `Camera`.
    application.get_generic_entity_factory().create_scene(scene_struct);

    const float pitch = 0.0f;
    yli::ontology::VariableStruct pitch_variable_struct(universe, &universe);
    pitch_variable_struct.local_name = "pitch";
    pitch_variable_struct.activate_callback = &yli::ontology::activate_pitch;
    pitch_variable_struct.read_callback = &yli::ontology::read_pitch;
    pitch_variable_struct.should_call_activate_callback_now = true;
    universe.create_variable(pitch_variable_struct, yli::data::AnyValue(pitch));

    {
        const float pitch = universe.get_pitch();
        ASSERT_EQ(pitch, 0.0f);
    }

    {
        lisp_function_overload->execute({ "pitch", "1.25" });
        const float pitch = universe.get_pitch();
        ASSERT_EQ(pitch, 1.25f);
    }
}

TEST(set_must_set_global_azimuth, set_azimuth)
{
    mock::MockApplication application;
    yli::ontology::Universe& universe = application.get_universe();

    yli::ontology::ConsoleStruct my_console_struct(0, 39, 15, 0); // Some dummy dimensions.
    yli::ontology::Console* const my_console = application.get_generic_entity_factory().create_console(my_console_struct);

    const std::string lisp_function_name = "set";
    yli::ontology::GenericLispFunctionOverload* const lisp_function_overload = application.get_entity_factory().create_lisp_function_overload(
            lisp_function_name,
            yli::ontology::Request<LispContext>(my_console),
            &yli::ontology::Variable::set_variable_const_std_string);

    yli::ontology::SceneStruct scene_struct;
    // Creating a `Scene` creates a default `Camera` and makes it the currently active `Camera`.
    application.get_generic_entity_factory().create_scene(scene_struct);

    const float azimuth = 0.0f;
    yli::ontology::VariableStruct azimuth_variable_struct(universe, &universe);
    azimuth_variable_struct.local_name = "azimuth";
    azimuth_variable_struct.activate_callback = &yli::ontology::activate_azimuth;
    azimuth_variable_struct.read_callback = &yli::ontology::read_azimuth;
    azimuth_variable_struct.should_call_activate_callback_now = true;
    universe.create_variable(azimuth_variable_struct, yli::data::AnyValue(azimuth));

    {
        lisp_function_overload->execute({ "azimuth", "0.00" });
        ASSERT_EQ(azimuth, 0.0f);
    }

    {
        lisp_function_overload->execute({ "azimuth", "2.50" });
        const float azimuth = universe.get_azimuth();
        ASSERT_EQ(azimuth, 2.50f);
    }
}
