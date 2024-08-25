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
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/ontology/callback_engine.hpp"
#include "code/ylikuutio/ontology/callback_object.hpp"
#include "code/ylikuutio/ontology/generic_entity_factory.hpp"
#include "code/ylikuutio/ontology/callback_engine_struct.hpp"
#include "code/ylikuutio/ontology/callback_object_struct.hpp"
#include "code/ylikuutio/snippets/callback_snippets.hpp"

// Include standard headers
#include <optional> // std::optional
#include <stdint.h> // uint32_t etc.
#include <variant>  // std::holds_alternative

namespace yli::ontology
{
    class GenericParentModule;
    class Universe;
}

TEST(callback_engine_must_function_properly, nop)
{
    mock::MockApplication application;

    yli::ontology::CallbackEngineStruct callback_engine_struct;
    auto callback_engine = application.get_generic_entity_factory().create_callback_engine(callback_engine_struct);

    yli::ontology::CallbackObjectStruct callback_object_struct(callback_engine);
    auto callback_object = callback_engine->create_callback_object();
    callback_object->set_new_callback(&yli::snippets::nop);

    std::optional<yli::data::AnyValue> result = callback_engine->execute(yli::data::AnyValue());
    ASSERT_FALSE(result);
}

TEST(callback_engine_must_function_properly, return_uint32_t_deadbeef)
{
    mock::MockApplication application;

    yli::ontology::CallbackEngineStruct callback_engine_struct;
    auto callback_engine = application.get_generic_entity_factory().create_callback_engine(callback_engine_struct);
    yli::ontology::CallbackObject* callback_object = callback_engine->create_callback_object();
    callback_object->set_new_callback(&yli::snippets::return_uint32_t_deadbeef);

    std::optional<yli::data::AnyValue> result = callback_engine->execute(yli::data::AnyValue());
    ASSERT_TRUE(std::holds_alternative<uint32_t>((*result).data));
    ASSERT_EQ(std::get<uint32_t>((*result).data), 0xdeadbeef);
}

TEST(callback_engine_must_function_properly, int32_t_zero_negated_equals_zero)
{
    mock::MockApplication application;

    yli::ontology::CallbackEngineStruct callback_engine_struct;
    auto callback_engine = application.get_generic_entity_factory().create_callback_engine(callback_engine_struct);
    yli::ontology::CallbackObject* callback_object = callback_engine->create_callback_object();
    callback_object->set_new_callback(&yli::snippets::neg);

    const int32_t zero = 0;
    yli::data::AnyValue zero_value(zero);
    callback_object->create_callback_parameter("", zero_value);

    std::optional<yli::data::AnyValue> result = callback_engine->execute(yli::data::AnyValue());
    ASSERT_TRUE(result);
    ASSERT_TRUE(std::holds_alternative<int32_t>((*result).data));
    ASSERT_EQ(std::get<int32_t>((*result).data), 0);
}

TEST(callback_engine_must_function_properly, int32_t_one_negated_equals_minus_one)
{
    mock::MockApplication application;

    yli::ontology::CallbackEngineStruct callback_engine_struct;
    auto callback_engine = application.get_generic_entity_factory().create_callback_engine(callback_engine_struct);
    yli::ontology::CallbackObject* callback_object = callback_engine->create_callback_object();
    callback_object->set_new_callback(&yli::snippets::neg);

    const int32_t one = 1;
    yli::data::AnyValue one_value(one);
    callback_object->create_callback_parameter("", one_value);

    std::optional<yli::data::AnyValue> result = callback_engine->execute(yli::data::AnyValue());
    ASSERT_TRUE(result);
    ASSERT_TRUE(std::holds_alternative<int32_t>((*result).data));
    ASSERT_EQ(std::get<int32_t>((*result).data), -1);
}

TEST(callback_engine_must_function_properly, int32_t_two_negated_equals_minus_two)
{
    mock::MockApplication application;

    yli::ontology::CallbackEngineStruct callback_engine_struct;
    auto callback_engine = application.get_generic_entity_factory().create_callback_engine(callback_engine_struct);
    yli::ontology::CallbackObject* callback_object = callback_engine->create_callback_object();
    callback_object->set_new_callback(&yli::snippets::neg);

    const int32_t two = 2;
    yli::data::AnyValue two_value(two);
    callback_object->create_callback_parameter("", two_value);

    std::optional<yli::data::AnyValue> result = callback_engine->execute(yli::data::AnyValue());
    ASSERT_TRUE(result);
    ASSERT_TRUE(std::holds_alternative<int32_t>((*result).data));
    ASSERT_EQ(std::get<int32_t>((*result).data), -2);
}

TEST(callback_engine_must_function_properly, int32_t_minus_one_negated_equals_one)
{
    mock::MockApplication application;

    yli::ontology::CallbackEngineStruct callback_engine_struct;
    auto callback_engine = application.get_generic_entity_factory().create_callback_engine(callback_engine_struct);
    yli::ontology::CallbackObject* callback_object = callback_engine->create_callback_object();
    callback_object->set_new_callback(&yli::snippets::neg);

    const int32_t minus_one = -1;
    yli::data::AnyValue minus_one_value(minus_one);
    callback_object->create_callback_parameter("", minus_one_value);

    std::optional<yli::data::AnyValue> result = callback_engine->execute(yli::data::AnyValue());
    ASSERT_TRUE(result);
    ASSERT_TRUE(std::holds_alternative<int32_t>((*result).data));
    ASSERT_EQ(std::get<int32_t>((*result).data), 1);
}

TEST(callback_engine_must_function_properly, int32_t_minus_two_negated_equals_two)
{
    mock::MockApplication application;

    yli::ontology::CallbackEngineStruct callback_engine_struct;
    auto callback_engine = application.get_generic_entity_factory().create_callback_engine(callback_engine_struct);
    yli::ontology::CallbackObject* callback_object = callback_engine->create_callback_object();
    callback_object->set_new_callback(&yli::snippets::neg);

    const int32_t minus_two = -2;
    yli::data::AnyValue minus_two_value(minus_two);
    callback_object->create_callback_parameter("", minus_two_value);

    std::optional<yli::data::AnyValue> result = callback_engine->execute(yli::data::AnyValue());
    ASSERT_TRUE(result);
    ASSERT_TRUE(std::holds_alternative<int32_t>((*result).data));
    ASSERT_EQ(std::get<int32_t>((*result).data), 2);
}

TEST(callback_engine_must_function_properly, int32_t_three_squared_equals_nine)
{
    mock::MockApplication application;

    yli::ontology::CallbackEngineStruct callback_engine_struct;
    auto callback_engine = application.get_generic_entity_factory().create_callback_engine(callback_engine_struct);
    yli::ontology::CallbackObject* callback_object = callback_engine->create_callback_object();
    callback_object->set_new_callback(&yli::snippets::square);

    const int32_t three = 3;
    yli::data::AnyValue three_value(three);
    callback_object->create_callback_parameter("foo", three_value);

    std::optional<yli::data::AnyValue> result = callback_engine->execute(yli::data::AnyValue());
    ASSERT_TRUE(result);
    ASSERT_TRUE(std::holds_alternative<int32_t>((*result).data));
    ASSERT_EQ(std::get<int32_t>((*result).data), 9);
}

TEST(callback_engine_must_function_properly, uint32_t_three_squared_equals_nine)
{
    mock::MockApplication application;

    yli::ontology::CallbackEngineStruct callback_engine_struct;
    auto callback_engine = application.get_generic_entity_factory().create_callback_engine(callback_engine_struct);
    yli::ontology::CallbackObject* callback_object = callback_engine->create_callback_object();
    callback_object->set_new_callback(&yli::snippets::square);

    const uint32_t three = 3;
    yli::data::AnyValue three_value(three);
    callback_object->create_callback_parameter("foo", three_value);

    std::optional<yli::data::AnyValue> result = callback_engine->execute(yli::data::AnyValue());
    ASSERT_TRUE(result);
    ASSERT_TRUE(std::holds_alternative<uint32_t>((*result).data));
    ASSERT_EQ(std::get<uint32_t>((*result).data), 9);
}

TEST(callback_engine_must_function_properly, uint32_t_5_expt_7_equals_78125)
{
    mock::MockApplication application;

    yli::ontology::CallbackEngineStruct callback_engine_struct;
    auto callback_engine = application.get_generic_entity_factory().create_callback_engine(callback_engine_struct);
    yli::ontology::CallbackObject* callback_object = callback_engine->create_callback_object();
    callback_object->set_new_callback(&yli::snippets::expt);

    const uint32_t five = 5;
    yli::data::AnyValue five_value(five);
    callback_object->create_callback_parameter("foo", five_value);

    const uint32_t seven = 7;
    yli::data::AnyValue seven_value(seven);
    callback_object->create_callback_parameter("foo", seven_value);

    std::optional<yli::data::AnyValue> result = callback_engine->execute(yli::data::AnyValue());
    ASSERT_TRUE(result);
    ASSERT_TRUE(std::holds_alternative<uint32_t>((*result).data));
    ASSERT_EQ(std::get<uint32_t>((*result).data), 78125);
}

TEST(callback_engine_must_function_properly, uint32_t_5_expt_7_equals_78125_with_named_inputs)
{
    mock::MockApplication application;

    yli::ontology::CallbackEngineStruct callback_engine_struct;
    auto callback_engine = application.get_generic_entity_factory().create_callback_engine(callback_engine_struct);
    yli::ontology::CallbackObject* callback_object = callback_engine->create_callback_object();
    callback_object->set_new_callback(&yli::snippets::expt_with_named_inputs);

    const uint32_t five = 5;
    yli::data::AnyValue five_value(five);
    callback_object->create_callback_parameter("base", five_value);
    std::optional<yli::data::AnyValue> anyvalue_base = callback_object->get_any_value("base");
    ASSERT_TRUE(std::holds_alternative<uint32_t>((*anyvalue_base).data));

    const uint32_t seven = 7;
    yli::data::AnyValue seven_value(seven);
    callback_object->create_callback_parameter("exponent", seven_value);

    std::optional<yli::data::AnyValue> result = callback_engine->execute(yli::data::AnyValue());
    ASSERT_TRUE(result);
    ASSERT_TRUE(std::holds_alternative<uint32_t>((*result).data));
    ASSERT_EQ(std::get<uint32_t>((*result).data), 78125);
}

TEST(callback_engine_must_function_properly, uint32_t_7_expt_5_then_squared_equals_282475249)
{
    mock::MockApplication application;

    yli::ontology::CallbackEngineStruct callback_engine_struct;
    auto callback_engine = application.get_generic_entity_factory().create_callback_engine(callback_engine_struct);
    yli::ontology::CallbackObject* callback_object_expt = callback_engine->create_callback_object();
    callback_object_expt->set_new_callback(&yli::snippets::expt);
    yli::ontology::CallbackObject* callback_object_square_last = callback_engine->create_callback_object();
    callback_object_square_last->set_new_callback(&yli::snippets::square_last);

    const uint32_t seven = 7;
    yli::data::AnyValue seven_value(seven);
    callback_object_expt->create_callback_parameter("", seven_value);

    const uint32_t five = 5;
    yli::data::AnyValue five_value(five);
    callback_object_expt->create_callback_parameter("", five_value);

    std::optional<yli::data::AnyValue> result = callback_engine->execute(yli::data::AnyValue());
    ASSERT_TRUE(result);
    ASSERT_TRUE(std::holds_alternative<uint32_t>((*result).data));
    ASSERT_EQ(std::get<uint32_t>((*result).data), 282475249);
}

TEST(callback_engine_must_function_properly, two_squared_four_times_equals_65536)
{
    mock::MockApplication application;

    yli::ontology::CallbackEngineStruct callback_engine_struct;
    auto callback_engine = application.get_generic_entity_factory().create_callback_engine(callback_engine_struct);
    yli::ontology::CallbackObject* callback_object_1st_square = callback_engine->create_callback_object();
    callback_object_1st_square->set_new_callback(&yli::snippets::square);

    const uint32_t two = 2;
    yli::data::AnyValue two_value(two);
    callback_object_1st_square->create_callback_parameter("", two_value);

    yli::ontology::CallbackObject* callback_object_2nd_square = callback_engine->create_callback_object();
    callback_object_2nd_square->set_new_callback(&yli::snippets::square_last);
    yli::ontology::CallbackObject* callback_object_3rd_square = callback_engine->create_callback_object();
    callback_object_3rd_square->set_new_callback(&yli::snippets::square_last);
    yli::ontology::CallbackObject* callback_object_4th_square = callback_engine->create_callback_object();
    callback_object_4th_square->set_new_callback(&yli::snippets::square_last);

    std::optional<yli::data::AnyValue> result = callback_engine->execute(yli::data::AnyValue());
    ASSERT_TRUE(result);
    ASSERT_TRUE(std::holds_alternative<uint32_t>((*result).data));
    ASSERT_EQ(std::get<uint32_t>((*result).data), 65536);
}
