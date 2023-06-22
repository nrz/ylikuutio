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
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/ontology/callback_engine.hpp"
#include "code/ylikuutio/ontology/callback_object.hpp"
#include "code/ylikuutio/ontology/callback_parameter.hpp"
#include "code/ylikuutio/ontology/generic_entity_factory.hpp"
#include "code/ylikuutio/ontology/callback_engine_struct.hpp"
#include "code/ylikuutio/ontology/callback_object_struct.hpp"

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <iostream> // std::cout, std::cin, std::cerr
#include <optional> // std::optional
#include <stdint.h> // uint32_t etc.
#include <variant>  // std::holds_alternative, std::variant
#include <vector>   // std::vector

namespace yli::ontology
{
    class GenericParentModule;
    class Universe;
}

std::optional<yli::data::AnyValue> square(
        yli::ontology::Universe&,
        yli::ontology::CallbackEngine*,
        yli::ontology::CallbackObject*,
        yli::ontology::GenericParentModule& input_parameters,
        const yli::data::AnyValue&)
{
    if (input_parameters.get_number_of_children() != 1)
    {
        std::cout << "The size of input_parameter is " << input_parameters.get_number_of_children() << "\n";
        return std::nullopt;
    }

    const yli::data::AnyValue& any_value = static_cast<yli::ontology::CallbackParameter*>(input_parameters.get(0))->get_any_value();

    if (std::holds_alternative<int32_t>(any_value.data))
    {
        const int32_t factor = std::get<int32_t>(any_value.data);
        const int32_t squared = factor * factor;
        std::cout << "Square of (int32_t) " << factor << " is " << squared << ".\n";
        return yli::data::AnyValue(squared);
    }
    else if (std::holds_alternative<uint32_t>(any_value.data))
    {
        const uint32_t factor = std::get<uint32_t>(any_value.data);
        const uint32_t squared = factor * factor;
        std::cout << "Square of (uint32_t) " << factor << " is " << squared << ".\n";
        return yli::data::AnyValue(squared);
    }
    else if (std::holds_alternative<float>(any_value.data))
    {
        const float factor = std::get<float>(any_value.data);
        const float squared = factor * factor;
        std::cout << "Square of (float) " << factor << " is " << squared << ".\n";
        return yli::data::AnyValue(squared);
    }
    else if (std::holds_alternative<double>(any_value.data))
    {
        const double factor = std::get<double>(any_value.data);
        const double squared = factor * factor;
        std::cout << "Square of (double) " << factor << " is " << squared << ".\n";
        return yli::data::AnyValue(squared);
    }
    return std::nullopt;
}

std::optional<yli::data::AnyValue> square_last(
        yli::ontology::Universe&,
        yli::ontology::CallbackEngine* callback_engine,
        yli::ontology::CallbackObject*,
        yli::ontology::GenericParentModule& input_parameters,
        const yli::data::AnyValue&)
{
    if (input_parameters.get_number_of_children() != 0)
    {
        std::cout << "The size of input_parameter is " << input_parameters.get_number_of_children() << "\n";
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> return_value_any_value = callback_engine->get_previous_return_value();

    if (!return_value_any_value)
    {
        std::cerr << "There is no previous return value!\n";
        return std::nullopt;
    }

    if (std::holds_alternative<int32_t>((*return_value_any_value).data))
    {
        const int32_t factor = std::get<int32_t>((*return_value_any_value).data);
        const int32_t squared = factor * factor;
        std::cout << "Square of (int32_t) " << factor << " is " << squared << ".\n";
        return yli::data::AnyValue(squared);
    }
    else if (std::holds_alternative<uint32_t>((*return_value_any_value).data))
    {
        const uint32_t factor = std::get<uint32_t>((*return_value_any_value).data);
        const uint32_t squared = factor * factor;
        std::cout << "Square of (uint32_t) " << factor << " is " << squared << ".\n";
        return yli::data::AnyValue(squared);
    }
    else if (std::holds_alternative<float>((*return_value_any_value).data))
    {
        const float factor = std::get<float>((*return_value_any_value).data);
        const float squared = factor * factor;
        std::cout << "Square of (float) " << factor << " is " << squared << ".\n";
        return yli::data::AnyValue(squared);
    }
    else if (std::holds_alternative<double>((*return_value_any_value).data))
    {
        const double factor = std::get<double>((*return_value_any_value).data);
        const double squared = factor * factor;
        std::cout << "Square of (double) " << factor << " is " << squared << ".\n";
        return yli::data::AnyValue(squared);
    }
    return std::nullopt;
}

std::optional<yli::data::AnyValue> expt(
        yli::ontology::Universe&,
        yli::ontology::CallbackEngine*,
        yli::ontology::CallbackObject*,
        yli::ontology::GenericParentModule& input_parameters,
        const yli::data::AnyValue&)
{
    if (input_parameters.get_number_of_children() != 2)
    {
        std::cout << "The size of input_parameter is " << input_parameters.get_number_of_children() << "\n";
        return std::nullopt;
    }

    const yli::data::AnyValue& base = static_cast<yli::ontology::CallbackParameter*>(input_parameters.get(0))->get_any_value();
    const yli::data::AnyValue& exponent = static_cast<yli::ontology::CallbackParameter*>(input_parameters.get(1))->get_any_value();

    if (std::holds_alternative<int32_t>(base.data) && std::holds_alternative<int32_t>(exponent.data))
    {
        const int32_t power = std::pow(std::get<int32_t>(base.data), std::get<int32_t>(exponent.data));
        std::cout << "(int32_t) " << std::get<int32_t>(base.data) << "^" << std::get<int32_t>(exponent.data) << " is " << power << ".\n";
        return yli::data::AnyValue(power);
    }
    else if (std::holds_alternative<uint32_t>(base.data) && std::holds_alternative<uint32_t>(exponent.data))
    {
        const uint32_t power = std::pow(std::get<uint32_t>(base.data), std::get<uint32_t>(exponent.data));
        std::cout << "(uint32_t) " << std::get<uint32_t>(base.data) << "^" << std::get<uint32_t>(exponent.data) << " is " << power << ".\n";
        return yli::data::AnyValue(power);
    }
    else if (std::holds_alternative<float>(base.data) && std::holds_alternative<float>(exponent.data))
    {
        const float power = std::pow(std::get<float>(base.data), std::get<float>(exponent.data));
        std::cout << "(float) " << std::get<float>(base.data) << "^" << std::get<float>(exponent.data) << " is " << power << ".\n";
        return yli::data::AnyValue(power);
    }
    else if (std::holds_alternative<double>(base.data) && std::holds_alternative<double>(exponent.data))
    {
        const double power = std::pow(std::get<double>(base.data), std::get<double>(exponent.data));
        std::cout << "(double) " << std::get<double>(base.data) << "^" << std::get<double>(exponent.data) << " is " << power << ".\n";
        return yli::data::AnyValue(power);
    }
    return std::nullopt;
}

std::optional<yli::data::AnyValue> expt_with_named_inputs(
        yli::ontology::Universe&,
        yli::ontology::CallbackEngine*,
        yli::ontology::CallbackObject* callback_object,
        yli::ontology::GenericParentModule&,
        const yli::data::AnyValue&)
{
    std::optional<yli::data::AnyValue> base = callback_object->get_any_value("base");
    std::optional<yli::data::AnyValue> exponent = callback_object->get_any_value("exponent");

    if (!base)
    {
        std::cout << "`base` does not contain a value!\n";
    }

    if (!exponent)
    {
        std::cout << "`exponent` does not contain a value!\n";
    }

    if (!base || !exponent)
    {
        return std::nullopt;
    }

    if (std::holds_alternative<int32_t>((*base).data) && std::holds_alternative<int32_t>((*exponent).data))
    {
        const int32_t power = std::pow(std::get<int32_t>((*base).data), std::get<int32_t>((*exponent).data));
        std::cout << "(int32_t) " << std::get<int32_t>((*base).data) << "^" << std::get<int32_t>((*exponent).data) << " is " << power << ".\n";
        return yli::data::AnyValue(power);
    }
    else if (std::holds_alternative<uint32_t>((*base).data) && std::holds_alternative<uint32_t>((*exponent).data))
    {
        const uint32_t power = std::pow(std::get<uint32_t>((*base).data), std::get<uint32_t>((*exponent).data));
        std::cout << "(uint32_t) " << std::get<uint32_t>((*base).data) << "^" << std::get<uint32_t>((*exponent).data) << " is " << power << ".\n";
        return yli::data::AnyValue(power);
    }
    else if (std::holds_alternative<float>((*base).data) && std::holds_alternative<float>((*exponent).data))
    {
        const float power = std::pow(std::get<float>((*base).data), std::get<float>((*exponent).data));
        std::cout << "(float) " << std::get<float>((*base).data) << "^" << std::get<float>((*exponent).data) << " is " << power << ".\n";
        return yli::data::AnyValue(power);
    }
    else if (std::holds_alternative<double>((*base).data) && std::holds_alternative<double>((*exponent).data))
    {
        const double power = std::pow(std::get<double>((*base).data), std::get<double>((*exponent).data));
        std::cout << "(double) " << std::get<double>((*base).data) << "^" << std::get<double>((*exponent).data) << " is " << power << ".\n";
        return yli::data::AnyValue(power);
    }
    return std::nullopt;
}

std::optional<yli::data::AnyValue> neg(
        yli::ontology::Universe&,
        yli::ontology::CallbackEngine*,
        yli::ontology::CallbackObject*,
        yli::ontology::GenericParentModule& input_parameters,
        const yli::data::AnyValue&)
{
    if (input_parameters.get_number_of_children() != 1)
    {
        std::cout << "The size of input_parameter is " << input_parameters.get_number_of_children() << "\n";
        return std::nullopt;
    }

    const yli::data::AnyValue& any_value = static_cast<yli::ontology::CallbackParameter*>(input_parameters.get(0))->get_any_value();

    if (std::holds_alternative<int32_t>(any_value.data))
    {
        const int32_t product = -1 * std::get<int32_t>(any_value.data);
        std::cout << "-1 * (int32_t) " << std::get<int32_t>(any_value.data) << " is " << product << ".\n";
        return yli::data::AnyValue(product);
    }
    else if (std::holds_alternative<float>(any_value.data))
    {
        const float product = -1.0 * std::get<float>(any_value.data);
        std::cout << "-1 * (float) " << std::get<float>(any_value.data) << " is " << product << ".\n";
        return yli::data::AnyValue(product);
    }
    else if (std::holds_alternative<double>(any_value.data))
    {
        const double product = -1.0 * std::get<double>(any_value.data);
        std::cout << "-1 * (double) " << std::get<double>(any_value.data) << " is " << product << ".\n";
        return yli::data::AnyValue(product);
    }
    return std::nullopt;
}

std::optional<yli::data::AnyValue> nop(
        yli::ontology::Universe&,
        yli::ontology::CallbackEngine*,
        yli::ontology::CallbackObject*,
        yli::ontology::GenericParentModule& input_parameters,
        const yli::data::AnyValue&)
{
    return std::nullopt;
}

std::optional<yli::data::AnyValue> return_uint32_t_deadbeef(
        yli::ontology::Universe&,
        yli::ontology::CallbackEngine*,
        yli::ontology::CallbackObject*,
        yli::ontology::GenericParentModule& input_parameters,
        const yli::data::AnyValue&)
{
    uint32_t deadbeef { 0xdeadbeef };
    return yli::data::AnyValue(deadbeef);
}

TEST(callback_engine_must_function_properly, nop)
{
    mock::MockApplication application;

    yli::ontology::CallbackEngineStruct callback_engine_struct;
    auto callback_engine = application.get_entity_factory().create_callback_engine(callback_engine_struct);

    yli::ontology::CallbackObjectStruct callback_object_struct;
    auto callback_object = callback_engine->create_callback_object();
    callback_object->set_new_callback(&nop);

    std::optional<yli::data::AnyValue> result = callback_engine->execute(yli::data::AnyValue());
    ASSERT_FALSE(result);
}

TEST(callback_engine_must_function_properly, return_uint32_t_deadbeef)
{
    mock::MockApplication application;

    yli::ontology::CallbackEngineStruct callback_engine_struct;
    auto callback_engine = application.get_entity_factory().create_callback_engine(callback_engine_struct);
    yli::ontology::CallbackObject* callback_object = callback_engine->create_callback_object();
    callback_object->set_new_callback(&return_uint32_t_deadbeef);

    std::optional<yli::data::AnyValue> result = callback_engine->execute(yli::data::AnyValue());
    ASSERT_TRUE(std::holds_alternative<uint32_t>((*result).data));
    ASSERT_EQ(std::get<uint32_t>((*result).data), 0xdeadbeef);
}

TEST(callback_engine_must_function_properly, int32_t_zero_negated_equals_zero)
{
    mock::MockApplication application;

    yli::ontology::CallbackEngineStruct callback_engine_struct;
    auto callback_engine = application.get_entity_factory().create_callback_engine(callback_engine_struct);
    yli::ontology::CallbackObject* callback_object = callback_engine->create_callback_object();
    callback_object->set_new_callback(&neg);

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
    auto callback_engine = application.get_entity_factory().create_callback_engine(callback_engine_struct);
    yli::ontology::CallbackObject* callback_object = callback_engine->create_callback_object();
    callback_object->set_new_callback(&neg);

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
    auto callback_engine = application.get_entity_factory().create_callback_engine(callback_engine_struct);
    yli::ontology::CallbackObject* callback_object = callback_engine->create_callback_object();
    callback_object->set_new_callback(&neg);

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
    auto callback_engine = application.get_entity_factory().create_callback_engine(callback_engine_struct);
    yli::ontology::CallbackObject* callback_object = callback_engine->create_callback_object();
    callback_object->set_new_callback(&neg);

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
    auto callback_engine = application.get_entity_factory().create_callback_engine(callback_engine_struct);
    yli::ontology::CallbackObject* callback_object = callback_engine->create_callback_object();
    callback_object->set_new_callback(&neg);

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
    auto callback_engine = application.get_entity_factory().create_callback_engine(callback_engine_struct);
    yli::ontology::CallbackObject* callback_object = callback_engine->create_callback_object();
    callback_object->set_new_callback(&square);

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
    auto callback_engine = application.get_entity_factory().create_callback_engine(callback_engine_struct);
    yli::ontology::CallbackObject* callback_object = callback_engine->create_callback_object();
    callback_object->set_new_callback(&square);

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
    auto callback_engine = application.get_entity_factory().create_callback_engine(callback_engine_struct);
    yli::ontology::CallbackObject* callback_object = callback_engine->create_callback_object();
    callback_object->set_new_callback(&expt);

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
    auto callback_engine = application.get_entity_factory().create_callback_engine(callback_engine_struct);
    yli::ontology::CallbackObject* callback_object = callback_engine->create_callback_object();
    callback_object->set_new_callback(&expt_with_named_inputs);

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
    auto callback_engine = application.get_entity_factory().create_callback_engine(callback_engine_struct);
    yli::ontology::CallbackObject* callback_object_expt = callback_engine->create_callback_object();
    callback_object_expt->set_new_callback(&expt);
    yli::ontology::CallbackObject* callback_object_square_last = callback_engine->create_callback_object();
    callback_object_square_last->set_new_callback(&square_last);

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
    auto callback_engine = application.get_entity_factory().create_callback_engine(callback_engine_struct);
    yli::ontology::CallbackObject* callback_object_1st_square = callback_engine->create_callback_object();
    callback_object_1st_square->set_new_callback(&square);

    const uint32_t two = 2;
    yli::data::AnyValue two_value(two);
    callback_object_1st_square->create_callback_parameter("", two_value);

    yli::ontology::CallbackObject* callback_object_2nd_square = callback_engine->create_callback_object();
    callback_object_2nd_square->set_new_callback(&square_last);
    yli::ontology::CallbackObject* callback_object_3rd_square = callback_engine->create_callback_object();
    callback_object_3rd_square->set_new_callback(&square_last);
    yli::ontology::CallbackObject* callback_object_4th_square = callback_engine->create_callback_object();
    callback_object_4th_square->set_new_callback(&square_last);

    std::optional<yli::data::AnyValue> result = callback_engine->execute(yli::data::AnyValue());
    ASSERT_TRUE(result);
    ASSERT_TRUE(std::holds_alternative<uint32_t>((*result).data));
    ASSERT_EQ(std::get<uint32_t>((*result).data), 65536);
}
