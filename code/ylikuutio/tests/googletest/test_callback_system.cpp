// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2019 Antti Nuortimo.
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
#include "code/ylikuutio/common/any_value.hpp"
#include "code/ylikuutio/callback/callback_engine.hpp"
#include "code/ylikuutio/callback/callback_object.hpp"
#include "code/ylikuutio/callback/callback_parameter.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <iostream> // std::cout, std::cin, std::cerr
#include <memory>   // std::make_shared, std::shared_ptr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli
{
    namespace ontology
    {
        class Universe;
    }
}

std::shared_ptr<yli::common::AnyValue> square(
        yli::ontology::Universe*,
        yli::callback::CallbackEngine*,
        yli::callback::CallbackObject*,
        std::vector<yli::callback::CallbackParameter*>& input_parameters)
{
    if (input_parameters.size() != 1)
    {
        std::cout << "The size of input_parameter is " << input_parameters.size() << "\n";
        return std::make_shared<yli::common::AnyValue>();
    }

    std::shared_ptr<yli::common::AnyValue> any_value = std::make_shared<yli::common::AnyValue>(*input_parameters.at(0)->get_any_value());

    if (any_value->type == yli::common::Datatype::INT32_T)
    {
        const int32_t factor = any_value->int32_t_value;
        const int32_t squared = factor * factor;
        std::cout << "Square of (int32_t) " << factor << " is " << squared << ".\n";
        return std::make_shared<yli::common::AnyValue>(squared);
    }
    else if (any_value->type == yli::common::Datatype::UINT32_T)
    {
        const uint32_t factor = any_value->uint32_t_value;
        const uint32_t squared = factor * factor;
        std::cout << "Square of (uint32_t) " << factor << " is " << squared << ".\n";
        return std::make_shared<yli::common::AnyValue>(squared);
    }
    else if (any_value->type == yli::common::Datatype::FLOAT)
    {
        const float factor = any_value->uint32_t_value;
        const float squared = factor * factor;
        std::cout << "Square of (float) " << factor << " is " << squared << ".\n";
        return std::make_shared<yli::common::AnyValue>(squared);
    }
    else if (any_value->type == yli::common::Datatype::FLOAT)
    {
        const double factor = any_value->uint32_t_value;
        const double squared = factor * factor;
        std::cout << "Square of (double) " << factor << " is " << squared << ".\n";
        return std::make_shared<yli::common::AnyValue>(squared);
    }
    return std::make_shared<yli::common::AnyValue>();
}

std::shared_ptr<yli::common::AnyValue> square_last(
        yli::ontology::Universe*,
        yli::callback::CallbackEngine* callback_engine,
        yli::callback::CallbackObject*,
        std::vector<yli::callback::CallbackParameter*>& input_parameters)
{
    if (input_parameters.size() != 0)
    {
        std::cout << "The size of input_parameter is " << input_parameters.size() << "\n";
        return std::make_shared<yli::common::AnyValue>();
    }

    std::shared_ptr<yli::common::AnyValue> return_value_any_value = callback_engine->get_previous_return_value();

    if (return_value_any_value == nullptr)
    {
        std::cerr << "There is no previous return value!\n";
        return nullptr;
    }

    if (return_value_any_value->type == yli::common::Datatype::INT32_T)
    {
        const int32_t factor = return_value_any_value->int32_t_value;
        const int32_t squared = factor * factor;
        std::cout << "Square of (int32_t) " << factor << " is " << squared << ".\n";
        return std::make_shared<yli::common::AnyValue>(squared);
    }
    else if (return_value_any_value->type == yli::common::Datatype::UINT32_T)
    {
        const uint32_t factor = return_value_any_value->uint32_t_value;
        const uint32_t squared = factor * factor;
        std::cout << "Square of (uint32_t) " << factor << " is " << squared << ".\n";
        return std::make_shared<yli::common::AnyValue>(squared);
    }
    else if (return_value_any_value->type == yli::common::Datatype::FLOAT)
    {
        const float factor = return_value_any_value->uint32_t_value;
        const float squared = factor * factor;
        std::cout << "Square of (float) " << factor << " is " << squared << ".\n";
        return std::make_shared<yli::common::AnyValue>(squared);
    }
    else if (return_value_any_value->type == yli::common::Datatype::FLOAT)
    {
        const double factor = return_value_any_value->uint32_t_value;
        const double squared = factor * factor;
        std::cout << "Square of (double) " << factor << " is " << squared << ".\n";
        return std::make_shared<yli::common::AnyValue>(squared);
    }
    return std::make_shared<yli::common::AnyValue>();
}

std::shared_ptr<yli::common::AnyValue> expt(
        yli::ontology::Universe*,
        yli::callback::CallbackEngine*,
        yli::callback::CallbackObject*,
        std::vector<yli::callback::CallbackParameter*>& input_parameters)
{
    if (input_parameters.size() != 2)
    {
        std::cout << "The size of input_parameter is " << input_parameters.size() << "\n";
        return std::make_shared<yli::common::AnyValue>();
    }

    std::shared_ptr<yli::common::AnyValue> base = std::make_shared<yli::common::AnyValue>(*input_parameters.at(0)->get_any_value());
    std::shared_ptr<yli::common::AnyValue> exponent = std::make_shared<yli::common::AnyValue>(*input_parameters.at(1)->get_any_value());

    if (base->type == yli::common::Datatype::INT32_T && exponent->type == yli::common::Datatype::INT32_T)
    {
        const int32_t power = std::pow(base->int32_t_value, exponent->int32_t_value);
        std::cout << "(int32_t) " << base->int32_t_value << "^" << exponent->int32_t_value << " is " << power << ".\n";
        return std::make_shared<yli::common::AnyValue>(power);
    }
    else if (base->type == yli::common::Datatype::UINT32_T && exponent->type == yli::common::Datatype::UINT32_T)
    {
        const uint32_t power = std::pow(base->uint32_t_value, exponent->uint32_t_value);
        std::cout << "(uint32_t) " << base->uint32_t_value << "^" << exponent->uint32_t_value << " is " << power << ".\n";
        return std::make_shared<yli::common::AnyValue>(power);
    }
    else if (base->type == yli::common::Datatype::FLOAT && exponent->type == yli::common::Datatype::FLOAT)
    {
        const float power = std::pow(base->float_value, exponent->float_value);
        std::cout << "(float) " << base->float_value << "^" << exponent->float_value << " is " << power << ".\n";
        return std::make_shared<yli::common::AnyValue>(power);
    }
    else if (base->type == yli::common::Datatype::DOUBLE && exponent->type == yli::common::Datatype::DOUBLE)
    {
        const double power = std::pow(base->double_value, exponent->double_value);
        std::cout << "(double) " << base->double_value << "^" << exponent->double_value << " is " << power << ".\n";
        return std::make_shared<yli::common::AnyValue>(power);
    }
    return std::make_shared<yli::common::AnyValue>();
}

std::shared_ptr<yli::common::AnyValue> expt_with_named_inputs(
        yli::ontology::Universe*,
        yli::callback::CallbackEngine*,
        yli::callback::CallbackObject* callback_object,
        std::vector<yli::callback::CallbackParameter*>&)
{
    std::shared_ptr<yli::common::AnyValue> base = std::make_shared<yli::common::AnyValue>(*callback_object->get_any_value("base"));
    std::shared_ptr<yli::common::AnyValue> exponent = std::make_shared<yli::common::AnyValue>(*callback_object->get_any_value("exponent"));

    if (base->type == yli::common::Datatype::INT32_T && exponent->type == yli::common::Datatype::INT32_T)
    {
        const int32_t power = std::pow(base->int32_t_value, exponent->int32_t_value);
        std::cout << "(int32_t) " << base->int32_t_value << "^" << exponent->int32_t_value << " is " << power << ".\n";
        return std::make_shared<yli::common::AnyValue>(power);
    }
    else if (base->type == yli::common::Datatype::UINT32_T && exponent->type == yli::common::Datatype::UINT32_T)
    {
        const uint32_t power = std::pow(base->uint32_t_value, exponent->uint32_t_value);
        std::cout << "(uint32_t) " << base->uint32_t_value << "^" << exponent->uint32_t_value << " is " << power << ".\n";
        return std::make_shared<yli::common::AnyValue>(power);
    }
    else if (base->type == yli::common::Datatype::FLOAT && exponent->type == yli::common::Datatype::FLOAT)
    {
        const float power = std::pow(base->float_value, exponent->float_value);
        std::cout << "(float) " << base->float_value << "^" << exponent->float_value << " is " << power << ".\n";
        return std::make_shared<yli::common::AnyValue>(power);
    }
    else if (base->type == yli::common::Datatype::DOUBLE && exponent->type == yli::common::Datatype::DOUBLE)
    {
        const double power = std::pow(base->double_value, exponent->double_value);
        std::cout << "(double) " << base->double_value << "^" << exponent->double_value << " is " << power << ".\n";
        return std::make_shared<yli::common::AnyValue>(power);
    }
    return std::make_shared<yli::common::AnyValue>();
}

std::shared_ptr<yli::common::AnyValue> neg(
        yli::ontology::Universe*,
        yli::callback::CallbackEngine*,
        yli::callback::CallbackObject*,
        std::vector<yli::callback::CallbackParameter*>& input_parameters)
{
    if (input_parameters.size() != 1)
    {
        std::cout << "The size of input_parameter is " << input_parameters.size() << "\n";
        return std::make_shared<yli::common::AnyValue>();
    }

    std::shared_ptr<yli::common::AnyValue> any_value = std::make_shared<yli::common::AnyValue>(*input_parameters.at(0)->get_any_value());

    if (any_value->type == yli::common::Datatype::INT32_T)
    {
        const int32_t product = -1 * any_value->int32_t_value;
        std::cout << "-1 * (int32_t) " << any_value->int32_t_value << " is " << product << ".\n";
        return std::make_shared<yli::common::AnyValue>(product);
    }
    else if (any_value->type == yli::common::Datatype::FLOAT)
    {
        const float product = -1.0 * any_value->float_value;
        std::cout << "-1 * (float) " << any_value->float_value << " is " << product << ".\n";
        return std::make_shared<yli::common::AnyValue>(product);
    }
    else if (any_value->type == yli::common::Datatype::DOUBLE)
    {
        const double product = -1.0 * any_value->double_value;
        std::cout << "-1 * (double) " << any_value->double_value << " is " << product << ".\n";
        return std::make_shared<yli::common::AnyValue>(product);
    }
    return std::make_shared<yli::common::AnyValue>();
}

TEST(callback_engine_must_function_properly, int32_t_zero_negated_equals_zero)
{
    yli::callback::CallbackEngine callback_engine;
    yli::callback::CallbackObject* callback_object = callback_engine.create_CallbackObject(nullptr);
    callback_object->set_new_callback(&neg);

    const int32_t zero = 0;
    const bool is_reference_0 = false;
    std::shared_ptr<yli::common::AnyValue> zero_value = std::make_shared<yli::common::AnyValue>(zero);
    callback_object->create_CallbackParameter("", zero_value, is_reference_0);

    std::shared_ptr<yli::common::AnyValue> result = callback_engine.execute();
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(result->type, yli::common::Datatype::INT32_T);
    ASSERT_EQ(result->int32_t_value, 0);
}

TEST(callback_engine_must_function_properly, int32_t_one_negated_equals_minus_one)
{
    yli::callback::CallbackEngine callback_engine;
    yli::callback::CallbackObject* callback_object = callback_engine.create_CallbackObject(nullptr);
    callback_object->set_new_callback(&neg);

    const int32_t one = 1;
    const bool is_reference_1 = false;
    std::shared_ptr<yli::common::AnyValue> one_value = std::make_shared<yli::common::AnyValue>(one);
    callback_object->create_CallbackParameter("", one_value, is_reference_1);

    std::shared_ptr<yli::common::AnyValue> result = callback_engine.execute();
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(result->type, yli::common::Datatype::INT32_T);
    ASSERT_EQ(result->int32_t_value, -1);
}

TEST(callback_engine_must_function_properly, int32_t_two_negated_equals_minus_two)
{
    yli::callback::CallbackEngine callback_engine;
    yli::callback::CallbackObject* callback_object = callback_engine.create_CallbackObject(nullptr);
    callback_object->set_new_callback(&neg);

    const int32_t two = 2;
    const bool is_reference_2 = false;
    std::shared_ptr<yli::common::AnyValue> two_value = std::make_shared<yli::common::AnyValue>(two);
    callback_object->create_CallbackParameter("", two_value, is_reference_2);

    std::shared_ptr<yli::common::AnyValue> result = callback_engine.execute();
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(result->type, yli::common::Datatype::INT32_T);
    ASSERT_EQ(result->int32_t_value, -2);
}

TEST(callback_engine_must_function_properly, int32_t_minus_one_negated_equals_one)
{
    yli::callback::CallbackEngine callback_engine;
    yli::callback::CallbackObject* callback_object = callback_engine.create_CallbackObject(nullptr);
    callback_object->set_new_callback(&neg);

    const int32_t minus_one = -1;
    const bool is_reference_minus_1 = false;
    std::shared_ptr<yli::common::AnyValue> minus_one_value = std::make_shared<yli::common::AnyValue>(minus_one);
    callback_object->create_CallbackParameter("", minus_one_value, is_reference_minus_1);

    std::shared_ptr<yli::common::AnyValue> result = callback_engine.execute();
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(result->type, yli::common::Datatype::INT32_T);
    ASSERT_EQ(result->int32_t_value, 1);
}

TEST(callback_engine_must_function_properly, int32_t_minus_two_negated_equals_two)
{
    yli::callback::CallbackEngine callback_engine;
    yli::callback::CallbackObject* callback_object = callback_engine.create_CallbackObject(nullptr);
    callback_object->set_new_callback(&neg);

    const int32_t minus_two = -2;
    const bool is_reference_minus_2 = false;
    std::shared_ptr<yli::common::AnyValue> minus_two_value = std::make_shared<yli::common::AnyValue>(minus_two);
    callback_object->create_CallbackParameter("", minus_two_value, is_reference_minus_2);

    std::shared_ptr<yli::common::AnyValue> result = callback_engine.execute();
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(result->type, yli::common::Datatype::INT32_T);
    ASSERT_EQ(result->int32_t_value, 2);
}

TEST(callback_engine_must_function_properly, int32_t_three_squared_equals_nine)
{
    yli::callback::CallbackEngine callback_engine;
    yli::callback::CallbackObject* callback_object = callback_engine.create_CallbackObject(nullptr);
    callback_object->set_new_callback(&square);

    const int32_t three = 3;
    const bool is_reference_3 = false;
    std::shared_ptr<yli::common::AnyValue> three_value = std::make_shared<yli::common::AnyValue>(three);
    callback_object->create_CallbackParameter("foo", three_value, is_reference_3);

    std::shared_ptr<yli::common::AnyValue> result = callback_engine.execute();
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(result->type, yli::common::Datatype::INT32_T);
    ASSERT_EQ(result->int32_t_value, 9);
}

TEST(callback_engine_must_function_properly, uint32_t_three_squared_equals_nine)
{
    yli::callback::CallbackEngine callback_engine;
    yli::callback::CallbackObject* callback_object = callback_engine.create_CallbackObject(nullptr);
    callback_object->set_new_callback(&square);

    const uint32_t three = 3;
    const bool is_reference_3 = false;
    std::shared_ptr<yli::common::AnyValue> three_value = std::make_shared<yli::common::AnyValue>(three);
    callback_object->create_CallbackParameter("foo", three_value, is_reference_3);

    std::shared_ptr<yli::common::AnyValue> result = callback_engine.execute();
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(result->type, yli::common::Datatype::UINT32_T);
    ASSERT_EQ(result->uint32_t_value, 9);
}

TEST(callback_engine_must_function_properly, uint32_t_5_expt_7_equals_78125)
{
    yli::callback::CallbackEngine callback_engine;
    yli::callback::CallbackObject* callback_object = callback_engine.create_CallbackObject(nullptr);
    callback_object->set_new_callback(&expt);

    const uint32_t five = 5;
    const bool is_reference_5 = false;
    std::shared_ptr<yli::common::AnyValue> five_value = std::make_shared<yli::common::AnyValue>(five);
    callback_object->create_CallbackParameter("foo", five_value, is_reference_5);

    const uint32_t seven = 7;
    const bool is_reference_7 = false;
    std::shared_ptr<yli::common::AnyValue> seven_value = std::make_shared<yli::common::AnyValue>(seven);
    callback_object->create_CallbackParameter("foo", seven_value, is_reference_7);

    std::shared_ptr<yli::common::AnyValue> result = callback_engine.execute();
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(result->type, yli::common::Datatype::UINT32_T);
    ASSERT_EQ(result->uint32_t_value, 78125);
}

TEST(callback_engine_must_function_properly, uint32_t_5_expt_7_equals_78125_with_named_inputs)
{
    yli::callback::CallbackEngine callback_engine;
    yli::callback::CallbackObject* callback_object = callback_engine.create_CallbackObject(nullptr);
    callback_object->set_new_callback(&expt_with_named_inputs);

    const uint32_t five = 5;
    const bool is_reference_5 = false;
    std::shared_ptr<yli::common::AnyValue> five_value = std::make_shared<yli::common::AnyValue>(five);
    callback_object->create_CallbackParameter("base", five_value, is_reference_5);
    std::shared_ptr<yli::common::AnyValue> anyvalue_base = std::make_shared<yli::common::AnyValue>(*callback_object->get_any_value("base"));
    ASSERT_EQ(anyvalue_base->type, yli::common::Datatype::UINT32_T);

    const uint32_t seven = 7;
    const bool is_reference_7 = false;
    std::shared_ptr<yli::common::AnyValue> seven_value = std::make_shared<yli::common::AnyValue>(seven);
    callback_object->create_CallbackParameter("exponent", seven_value, is_reference_7);

    std::shared_ptr<yli::common::AnyValue> result = callback_engine.execute();
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(result->type, yli::common::Datatype::UINT32_T);
    ASSERT_EQ(result->uint32_t_value, 78125);
}

TEST(callback_engine_must_function_properly, uint32_t_7_expt_5_then_squared_equals_282475249)
{
    yli::callback::CallbackEngine callback_engine;
    yli::callback::CallbackObject* callback_object_expt = callback_engine.create_CallbackObject(nullptr);
    callback_object_expt->set_new_callback(&expt);
    yli::callback::CallbackObject* callback_object_square_last = callback_engine.create_CallbackObject(nullptr);
    callback_object_square_last->set_new_callback(&square_last);

    const uint32_t seven = 7;
    const bool is_reference_7 = false;
    std::shared_ptr<yli::common::AnyValue> seven_value = std::make_shared<yli::common::AnyValue>(seven);
    callback_object_expt->create_CallbackParameter("", seven_value, is_reference_7);

    const uint32_t five = 5;
    const bool is_reference_5 = false;
    std::shared_ptr<yli::common::AnyValue> five_value = std::make_shared<yli::common::AnyValue>(five);
    callback_object_expt->create_CallbackParameter("", five_value, is_reference_5);

    std::shared_ptr<yli::common::AnyValue> result = callback_engine.execute();
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(result->type, yli::common::Datatype::UINT32_T);
    ASSERT_EQ(result->uint32_t_value, 282475249);
}

TEST(callback_engine_must_function_properly, two_squared_four_times_equals_65536)
{
    yli::callback::CallbackEngine callback_engine;
    yli::callback::CallbackObject* callback_object_1st_square = callback_engine.create_CallbackObject(nullptr);
    callback_object_1st_square->set_new_callback(&square);

    const uint32_t two = 2;
    const bool is_reference_2 = false;
    std::shared_ptr<yli::common::AnyValue> two_value = std::make_shared<yli::common::AnyValue>(two);
    callback_object_1st_square->create_CallbackParameter("", two_value, is_reference_2);

    yli::callback::CallbackObject* callback_object_2nd_square = callback_engine.create_CallbackObject(nullptr);
    callback_object_2nd_square->set_new_callback(&square_last);
    yli::callback::CallbackObject* callback_object_3rd_square = callback_engine.create_CallbackObject(nullptr);
    callback_object_3rd_square->set_new_callback(&square_last);
    yli::callback::CallbackObject* callback_object_4th_square = callback_engine.create_CallbackObject(nullptr);
    callback_object_4th_square->set_new_callback(&square_last);

    std::shared_ptr<yli::common::AnyValue> result = callback_engine.execute();
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(result->type, yli::common::Datatype::UINT32_T);
    ASSERT_EQ(result->uint32_t_value, 65536);
}
