// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
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
#include "code/ylikuutio/data/any_value.hpp"
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
#include <variant>  // std::holds_alternative, std::variant
#include <vector>   // std::vector

namespace yli::ontology
{
    class Universe;
}

std::shared_ptr<yli::data::AnyValue> square(
        yli::ontology::Universe*,
        yli::callback::CallbackEngine*,
        yli::callback::CallbackObject*,
        std::vector<yli::callback::CallbackParameter*>& input_parameters,
        std::shared_ptr<yli::data::AnyValue>)
{
    if (input_parameters.size() != 1)
    {
        std::cout << "The size of input_parameter is " << input_parameters.size() << "\n";
        return std::make_shared<yli::data::AnyValue>();
    }

    std::shared_ptr<yli::data::AnyValue> any_value = std::make_shared<yli::data::AnyValue>(*input_parameters.at(0)->get_any_value());

    if (std::holds_alternative<int32_t>(any_value->data))
    {
        const int32_t factor = std::get<int32_t>(any_value->data);
        const int32_t squared = factor * factor;
        std::cout << "Square of (int32_t) " << factor << " is " << squared << ".\n";
        return std::make_shared<yli::data::AnyValue>(squared);
    }
    else if (std::holds_alternative<uint32_t>(any_value->data))
    {
        const uint32_t factor = std::get<uint32_t>(any_value->data);
        const uint32_t squared = factor * factor;
        std::cout << "Square of (uint32_t) " << factor << " is " << squared << ".\n";
        return std::make_shared<yli::data::AnyValue>(squared);
    }
    else if (std::holds_alternative<float>(any_value->data))
    {
        const float factor = std::get<float>(any_value->data);
        const float squared = factor * factor;
        std::cout << "Square of (float) " << factor << " is " << squared << ".\n";
        return std::make_shared<yli::data::AnyValue>(squared);
    }
    else if (std::holds_alternative<double>(any_value->data))
    {
        const double factor = std::get<double>(any_value->data);
        const double squared = factor * factor;
        std::cout << "Square of (double) " << factor << " is " << squared << ".\n";
        return std::make_shared<yli::data::AnyValue>(squared);
    }
    return std::make_shared<yli::data::AnyValue>();
}

std::shared_ptr<yli::data::AnyValue> square_last(
        yli::ontology::Universe*,
        yli::callback::CallbackEngine* callback_engine,
        yli::callback::CallbackObject*,
        std::vector<yli::callback::CallbackParameter*>& input_parameters,
        std::shared_ptr<yli::data::AnyValue>)
{
    if (input_parameters.size() != 0)
    {
        std::cout << "The size of input_parameter is " << input_parameters.size() << "\n";
        return std::make_shared<yli::data::AnyValue>();
    }

    std::shared_ptr<yli::data::AnyValue> return_value_any_value = callback_engine->get_previous_return_value();

    if (return_value_any_value == nullptr)
    {
        std::cerr << "There is no previous return value!\n";
        return nullptr;
    }

    if (std::holds_alternative<int32_t>(return_value_any_value->data))
    {
        const int32_t factor = std::get<int32_t>(return_value_any_value->data);
        const int32_t squared = factor * factor;
        std::cout << "Square of (int32_t) " << factor << " is " << squared << ".\n";
        return std::make_shared<yli::data::AnyValue>(squared);
    }
    else if (std::holds_alternative<uint32_t>(return_value_any_value->data))
    {
        const uint32_t factor = std::get<uint32_t>(return_value_any_value->data);
        const uint32_t squared = factor * factor;
        std::cout << "Square of (uint32_t) " << factor << " is " << squared << ".\n";
        return std::make_shared<yli::data::AnyValue>(squared);
    }
    else if (std::holds_alternative<float>(return_value_any_value->data))
    {
        const float factor = std::get<float>(return_value_any_value->data);
        const float squared = factor * factor;
        std::cout << "Square of (float) " << factor << " is " << squared << ".\n";
        return std::make_shared<yli::data::AnyValue>(squared);
    }
    else if (std::holds_alternative<double>(return_value_any_value->data))
    {
        const double factor = std::get<double>(return_value_any_value->data);
        const double squared = factor * factor;
        std::cout << "Square of (double) " << factor << " is " << squared << ".\n";
        return std::make_shared<yli::data::AnyValue>(squared);
    }
    return std::make_shared<yli::data::AnyValue>();
}

std::shared_ptr<yli::data::AnyValue> expt(
        yli::ontology::Universe*,
        yli::callback::CallbackEngine*,
        yli::callback::CallbackObject*,
        std::vector<yli::callback::CallbackParameter*>& input_parameters,
        std::shared_ptr<yli::data::AnyValue>)
{
    if (input_parameters.size() != 2)
    {
        std::cout << "The size of input_parameter is " << input_parameters.size() << "\n";
        return std::make_shared<yli::data::AnyValue>();
    }

    std::shared_ptr<yli::data::AnyValue> base = std::make_shared<yli::data::AnyValue>(*input_parameters.at(0)->get_any_value());
    std::shared_ptr<yli::data::AnyValue> exponent = std::make_shared<yli::data::AnyValue>(*input_parameters.at(1)->get_any_value());

    if (std::holds_alternative<int32_t>(base->data) && std::holds_alternative<int32_t>(exponent->data))
    {
        const int32_t power = std::pow(std::get<int32_t>(base->data), std::get<int32_t>(exponent->data));
        std::cout << "(int32_t) " << std::get<int32_t>(base->data) << "^" << std::get<int32_t>(exponent->data) << " is " << power << ".\n";
        return std::make_shared<yli::data::AnyValue>(power);
    }
    else if (std::holds_alternative<uint32_t>(base->data) && std::holds_alternative<uint32_t>(exponent->data))
    {
        const uint32_t power = std::pow(std::get<uint32_t>(base->data), std::get<uint32_t>(exponent->data));
        std::cout << "(uint32_t) " << std::get<uint32_t>(base->data) << "^" << std::get<uint32_t>(exponent->data) << " is " << power << ".\n";
        return std::make_shared<yli::data::AnyValue>(power);
    }
    else if (std::holds_alternative<float>(base->data) && std::holds_alternative<float>(exponent->data))
    {
        const float power = std::pow(std::get<float>(base->data), std::get<float>(exponent->data));
        std::cout << "(float) " << std::get<float>(base->data) << "^" << std::get<float>(exponent->data) << " is " << power << ".\n";
        return std::make_shared<yli::data::AnyValue>(power);
    }
    else if (std::holds_alternative<double>(base->data) && std::holds_alternative<double>(exponent->data))
    {
        const double power = std::pow(std::get<double>(base->data), std::get<double>(exponent->data));
        std::cout << "(double) " << std::get<double>(base->data) << "^" << std::get<double>(exponent->data) << " is " << power << ".\n";
        return std::make_shared<yli::data::AnyValue>(power);
    }
    return std::make_shared<yli::data::AnyValue>();
}

std::shared_ptr<yli::data::AnyValue> expt_with_named_inputs(
        yli::ontology::Universe*,
        yli::callback::CallbackEngine*,
        yli::callback::CallbackObject* callback_object,
        std::vector<yli::callback::CallbackParameter*>&,
        std::shared_ptr<yli::data::AnyValue>)
{
    std::shared_ptr<yli::data::AnyValue> base = std::make_shared<yli::data::AnyValue>(*callback_object->get_any_value("base"));
    std::shared_ptr<yli::data::AnyValue> exponent = std::make_shared<yli::data::AnyValue>(*callback_object->get_any_value("exponent"));

    if (std::holds_alternative<int32_t>(base->data) && std::holds_alternative<int32_t>(exponent->data))
    {
        const int32_t power = std::pow(std::get<int32_t>(base->data), std::get<int32_t>(exponent->data));
        std::cout << "(int32_t) " << std::get<int32_t>(base->data) << "^" << std::get<int32_t>(exponent->data) << " is " << power << ".\n";
        return std::make_shared<yli::data::AnyValue>(power);
    }
    else if (std::holds_alternative<uint32_t>(base->data) && std::holds_alternative<uint32_t>(exponent->data))
    {
        const uint32_t power = std::pow(std::get<uint32_t>(base->data), std::get<uint32_t>(exponent->data));
        std::cout << "(uint32_t) " << std::get<uint32_t>(base->data) << "^" << std::get<uint32_t>(exponent->data) << " is " << power << ".\n";
        return std::make_shared<yli::data::AnyValue>(power);
    }
    else if (std::holds_alternative<float>(base->data) && std::holds_alternative<float>(exponent->data))
    {
        const float power = std::pow(std::get<float>(base->data), std::get<float>(exponent->data));
        std::cout << "(float) " << std::get<float>(base->data) << "^" << std::get<float>(exponent->data) << " is " << power << ".\n";
        return std::make_shared<yli::data::AnyValue>(power);
    }
    else if (std::holds_alternative<double>(base->data) && std::holds_alternative<double>(exponent->data))
    {
        const double power = std::pow(std::get<double>(base->data), std::get<double>(exponent->data));
        std::cout << "(double) " << std::get<double>(base->data) << "^" << std::get<double>(exponent->data) << " is " << power << ".\n";
        return std::make_shared<yli::data::AnyValue>(power);
    }
    return std::make_shared<yli::data::AnyValue>();
}

std::shared_ptr<yli::data::AnyValue> neg(
        yli::ontology::Universe*,
        yli::callback::CallbackEngine*,
        yli::callback::CallbackObject*,
        std::vector<yli::callback::CallbackParameter*>& input_parameters,
        std::shared_ptr<yli::data::AnyValue>)
{
    if (input_parameters.size() != 1)
    {
        std::cout << "The size of input_parameter is " << input_parameters.size() << "\n";
        return std::make_shared<yli::data::AnyValue>();
    }

    std::shared_ptr<yli::data::AnyValue> any_value = std::make_shared<yli::data::AnyValue>(*input_parameters.at(0)->get_any_value());

    if (std::holds_alternative<int32_t>(any_value->data))
    {
        const int32_t product = -1 * std::get<int32_t>(any_value->data);
        std::cout << "-1 * (int32_t) " << std::get<int32_t>(any_value->data) << " is " << product << ".\n";
        return std::make_shared<yli::data::AnyValue>(product);
    }
    else if (std::holds_alternative<float>(any_value->data))
    {
        const float product = -1.0 * std::get<float>(any_value->data);
        std::cout << "-1 * (float) " << std::get<float>(any_value->data) << " is " << product << ".\n";
        return std::make_shared<yli::data::AnyValue>(product);
    }
    else if (std::holds_alternative<double>(any_value->data))
    {
        const double product = -1.0 * std::get<double>(any_value->data);
        std::cout << "-1 * (double) " << std::get<double>(any_value->data) << " is " << product << ".\n";
        return std::make_shared<yli::data::AnyValue>(product);
    }
    return std::make_shared<yli::data::AnyValue>();
}

TEST(callback_engine_must_function_properly, int32_t_zero_negated_equals_zero)
{
    yli::callback::CallbackEngine callback_engine;
    yli::callback::CallbackObject* callback_object = callback_engine.create_callback_object(nullptr);
    callback_object->set_new_callback(&neg);

    const int32_t zero = 0;
    const bool is_reference_0 = false;
    std::shared_ptr<yli::data::AnyValue> zero_value = std::make_shared<yli::data::AnyValue>(zero);
    callback_object->create_callback_parameter("", zero_value, is_reference_0);

    std::shared_ptr<yli::data::AnyValue> result = callback_engine.execute(nullptr);
    ASSERT_NE(result, nullptr);
    ASSERT_TRUE(std::holds_alternative<int32_t>(result->data));
    ASSERT_EQ(std::get<int32_t>(result->data), 0);
}

TEST(callback_engine_must_function_properly, int32_t_one_negated_equals_minus_one)
{
    yli::callback::CallbackEngine callback_engine;
    yli::callback::CallbackObject* callback_object = callback_engine.create_callback_object(nullptr);
    callback_object->set_new_callback(&neg);

    const int32_t one = 1;
    const bool is_reference_1 = false;
    std::shared_ptr<yli::data::AnyValue> one_value = std::make_shared<yli::data::AnyValue>(one);
    callback_object->create_callback_parameter("", one_value, is_reference_1);

    std::shared_ptr<yli::data::AnyValue> result = callback_engine.execute(nullptr);
    ASSERT_NE(result, nullptr);
    ASSERT_TRUE(std::holds_alternative<int32_t>(result->data));
    ASSERT_EQ(std::get<int32_t>(result->data), -1);
}

TEST(callback_engine_must_function_properly, int32_t_two_negated_equals_minus_two)
{
    yli::callback::CallbackEngine callback_engine;
    yli::callback::CallbackObject* callback_object = callback_engine.create_callback_object(nullptr);
    callback_object->set_new_callback(&neg);

    const int32_t two = 2;
    const bool is_reference_2 = false;
    std::shared_ptr<yli::data::AnyValue> two_value = std::make_shared<yli::data::AnyValue>(two);
    callback_object->create_callback_parameter("", two_value, is_reference_2);

    std::shared_ptr<yli::data::AnyValue> result = callback_engine.execute(nullptr);
    ASSERT_NE(result, nullptr);
    ASSERT_TRUE(std::holds_alternative<int32_t>(result->data));
    ASSERT_EQ(std::get<int32_t>(result->data), -2);
}

TEST(callback_engine_must_function_properly, int32_t_minus_one_negated_equals_one)
{
    yli::callback::CallbackEngine callback_engine;
    yli::callback::CallbackObject* callback_object = callback_engine.create_callback_object(nullptr);
    callback_object->set_new_callback(&neg);

    const int32_t minus_one = -1;
    const bool is_reference_minus_1 = false;
    std::shared_ptr<yli::data::AnyValue> minus_one_value = std::make_shared<yli::data::AnyValue>(minus_one);
    callback_object->create_callback_parameter("", minus_one_value, is_reference_minus_1);

    std::shared_ptr<yli::data::AnyValue> result = callback_engine.execute(nullptr);
    ASSERT_NE(result, nullptr);
    ASSERT_TRUE(std::holds_alternative<int32_t>(result->data));
    ASSERT_EQ(std::get<int32_t>(result->data), 1);
}

TEST(callback_engine_must_function_properly, int32_t_minus_two_negated_equals_two)
{
    yli::callback::CallbackEngine callback_engine;
    yli::callback::CallbackObject* callback_object = callback_engine.create_callback_object(nullptr);
    callback_object->set_new_callback(&neg);

    const int32_t minus_two = -2;
    const bool is_reference_minus_2 = false;
    std::shared_ptr<yli::data::AnyValue> minus_two_value = std::make_shared<yli::data::AnyValue>(minus_two);
    callback_object->create_callback_parameter("", minus_two_value, is_reference_minus_2);

    std::shared_ptr<yli::data::AnyValue> result = callback_engine.execute(nullptr);
    ASSERT_NE(result, nullptr);
    ASSERT_TRUE(std::holds_alternative<int32_t>(result->data));
    ASSERT_EQ(std::get<int32_t>(result->data), 2);
}

TEST(callback_engine_must_function_properly, int32_t_three_squared_equals_nine)
{
    yli::callback::CallbackEngine callback_engine;
    yli::callback::CallbackObject* callback_object = callback_engine.create_callback_object(nullptr);
    callback_object->set_new_callback(&square);

    const int32_t three = 3;
    const bool is_reference_3 = false;
    std::shared_ptr<yli::data::AnyValue> three_value = std::make_shared<yli::data::AnyValue>(three);
    callback_object->create_callback_parameter("foo", three_value, is_reference_3);

    std::shared_ptr<yli::data::AnyValue> result = callback_engine.execute(nullptr);
    ASSERT_NE(result, nullptr);
    ASSERT_TRUE(std::holds_alternative<int32_t>(result->data));
    ASSERT_EQ(std::get<int32_t>(result->data), 9);
}

TEST(callback_engine_must_function_properly, uint32_t_three_squared_equals_nine)
{
    yli::callback::CallbackEngine callback_engine;
    yli::callback::CallbackObject* callback_object = callback_engine.create_callback_object(nullptr);
    callback_object->set_new_callback(&square);

    const uint32_t three = 3;
    const bool is_reference_3 = false;
    std::shared_ptr<yli::data::AnyValue> three_value = std::make_shared<yli::data::AnyValue>(three);
    callback_object->create_callback_parameter("foo", three_value, is_reference_3);

    std::shared_ptr<yli::data::AnyValue> result = callback_engine.execute(nullptr);
    ASSERT_NE(result, nullptr);
    ASSERT_TRUE(std::holds_alternative<uint32_t>(result->data));
    ASSERT_EQ(std::get<uint32_t>(result->data), 9);
}

TEST(callback_engine_must_function_properly, uint32_t_5_expt_7_equals_78125)
{
    yli::callback::CallbackEngine callback_engine;
    yli::callback::CallbackObject* callback_object = callback_engine.create_callback_object(nullptr);
    callback_object->set_new_callback(&expt);

    const uint32_t five = 5;
    const bool is_reference_5 = false;
    std::shared_ptr<yli::data::AnyValue> five_value = std::make_shared<yli::data::AnyValue>(five);
    callback_object->create_callback_parameter("foo", five_value, is_reference_5);

    const uint32_t seven = 7;
    const bool is_reference_7 = false;
    std::shared_ptr<yli::data::AnyValue> seven_value = std::make_shared<yli::data::AnyValue>(seven);
    callback_object->create_callback_parameter("foo", seven_value, is_reference_7);

    std::shared_ptr<yli::data::AnyValue> result = callback_engine.execute(nullptr);
    ASSERT_NE(result, nullptr);
    ASSERT_TRUE(std::holds_alternative<uint32_t>(result->data));
    ASSERT_EQ(std::get<uint32_t>(result->data), 78125);
}

TEST(callback_engine_must_function_properly, uint32_t_5_expt_7_equals_78125_with_named_inputs)
{
    yli::callback::CallbackEngine callback_engine;
    yli::callback::CallbackObject* callback_object = callback_engine.create_callback_object(nullptr);
    callback_object->set_new_callback(&expt_with_named_inputs);

    const uint32_t five = 5;
    const bool is_reference_5 = false;
    std::shared_ptr<yli::data::AnyValue> five_value = std::make_shared<yli::data::AnyValue>(five);
    callback_object->create_callback_parameter("base", five_value, is_reference_5);
    std::shared_ptr<yli::data::AnyValue> anyvalue_base = std::make_shared<yli::data::AnyValue>(*callback_object->get_any_value("base"));
    ASSERT_TRUE(std::holds_alternative<uint32_t>(anyvalue_base->data));

    const uint32_t seven = 7;
    const bool is_reference_7 = false;
    std::shared_ptr<yli::data::AnyValue> seven_value = std::make_shared<yli::data::AnyValue>(seven);
    callback_object->create_callback_parameter("exponent", seven_value, is_reference_7);

    std::shared_ptr<yli::data::AnyValue> result = callback_engine.execute(nullptr);
    ASSERT_NE(result, nullptr);
    ASSERT_TRUE(std::holds_alternative<uint32_t>(result->data));
    ASSERT_EQ(std::get<uint32_t>(result->data), 78125);
}

TEST(callback_engine_must_function_properly, uint32_t_7_expt_5_then_squared_equals_282475249)
{
    yli::callback::CallbackEngine callback_engine;
    yli::callback::CallbackObject* callback_object_expt = callback_engine.create_callback_object(nullptr);
    callback_object_expt->set_new_callback(&expt);
    yli::callback::CallbackObject* callback_object_square_last = callback_engine.create_callback_object(nullptr);
    callback_object_square_last->set_new_callback(&square_last);

    const uint32_t seven = 7;
    const bool is_reference_7 = false;
    std::shared_ptr<yli::data::AnyValue> seven_value = std::make_shared<yli::data::AnyValue>(seven);
    callback_object_expt->create_callback_parameter("", seven_value, is_reference_7);

    const uint32_t five = 5;
    const bool is_reference_5 = false;
    std::shared_ptr<yli::data::AnyValue> five_value = std::make_shared<yli::data::AnyValue>(five);
    callback_object_expt->create_callback_parameter("", five_value, is_reference_5);

    std::shared_ptr<yli::data::AnyValue> result = callback_engine.execute(nullptr);
    ASSERT_NE(result, nullptr);
    ASSERT_TRUE(std::holds_alternative<uint32_t>(result->data));
    ASSERT_EQ(std::get<uint32_t>(result->data), 282475249);
}

TEST(callback_engine_must_function_properly, two_squared_four_times_equals_65536)
{
    yli::callback::CallbackEngine callback_engine;
    yli::callback::CallbackObject* callback_object_1st_square = callback_engine.create_callback_object(nullptr);
    callback_object_1st_square->set_new_callback(&square);

    const uint32_t two = 2;
    const bool is_reference_2 = false;
    std::shared_ptr<yli::data::AnyValue> two_value = std::make_shared<yli::data::AnyValue>(two);
    callback_object_1st_square->create_callback_parameter("", two_value, is_reference_2);

    yli::callback::CallbackObject* callback_object_2nd_square = callback_engine.create_callback_object(nullptr);
    callback_object_2nd_square->set_new_callback(&square_last);
    yli::callback::CallbackObject* callback_object_3rd_square = callback_engine.create_callback_object(nullptr);
    callback_object_3rd_square->set_new_callback(&square_last);
    yli::callback::CallbackObject* callback_object_4th_square = callback_engine.create_callback_object(nullptr);
    callback_object_4th_square->set_new_callback(&square_last);

    std::shared_ptr<yli::data::AnyValue> result = callback_engine.execute(nullptr);
    ASSERT_NE(result, nullptr);
    ASSERT_TRUE(std::holds_alternative<uint32_t>(result->data));
    ASSERT_EQ(std::get<uint32_t>(result->data), 65536);
}
