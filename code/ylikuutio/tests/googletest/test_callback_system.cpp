#include "gtest/gtest.h"
#include "code/ylikuutio/common/any_value.hpp"
#include "code/ylikuutio/callback_system/callback_engine.hpp"
#include "code/ylikuutio/callback_system/callback_object.hpp"
#include "code/ylikuutio/callback_system/callback_parameter.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <memory>   // std::make_shared, std::shared_ptr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <iostream> // std::cout, std::cin, std::cerr

std::shared_ptr<datatypes::AnyValue> square(callback_system::CallbackEngine*, callback_system::CallbackObject*, std::vector<callback_system::CallbackParameter*>& input_parameters)
{
    if (input_parameters.size() != 1)
    {
        std::cout << "The size of input_parameter is " << input_parameters.size() << "\n";
        return std::make_shared<datatypes::AnyValue>();
    }

    std::shared_ptr<datatypes::AnyValue> any_value = std::make_shared<datatypes::AnyValue>(*input_parameters.at(0)->get_any_value());

    if (any_value->type == datatypes::INT32_T)
    {
        const int32_t factor = any_value->int32_t_value;
        const int32_t squared = factor * factor;
        std::cout << "Square of (int32_t) " << factor << " is " << squared << ".\n";
        return std::make_shared<datatypes::AnyValue>(squared);
    }
    else if (any_value->type == datatypes::UINT32_T)
    {
        const uint32_t factor = any_value->uint32_t_value;
        const uint32_t squared = factor * factor;
        std::cout << "Square of (uint32_t) " << factor << " is " << squared << ".\n";
        return std::make_shared<datatypes::AnyValue>(squared);
    }
    else if (any_value->type == datatypes::FLOAT)
    {
        const float factor = any_value->uint32_t_value;
        const float squared = factor * factor;
        std::cout << "Square of (float) " << factor << " is " << squared << ".\n";
        return std::make_shared<datatypes::AnyValue>(squared);
    }
    else if (any_value->type == datatypes::FLOAT)
    {
        const double factor = any_value->uint32_t_value;
        const double squared = factor * factor;
        std::cout << "Square of (double) " << factor << " is " << squared << ".\n";
        return std::make_shared<datatypes::AnyValue>(squared);
    }
    std::cout << "The datatype of any_value->type is " << any_value->type << "\n";
    return std::make_shared<datatypes::AnyValue>();
}

std::shared_ptr<datatypes::AnyValue> square_last(callback_system::CallbackEngine* callback_engine,
        callback_system::CallbackObject*,
        std::vector<callback_system::CallbackParameter*>& input_parameters)
{
    if (input_parameters.size() != 0)
    {
        std::cout << "The size of input_parameter is " << input_parameters.size() << "\n";
        return std::make_shared<datatypes::AnyValue>();
    }

    std::shared_ptr<datatypes::AnyValue> return_value_any_value = callback_engine->get_previous_return_value();

    if (return_value_any_value == nullptr)
    {
        std::cerr << "There is no previous return value!\n";
        return nullptr;
    }

    if (return_value_any_value->type == datatypes::INT32_T)
    {
        const int32_t factor = return_value_any_value->int32_t_value;
        const int32_t squared = factor * factor;
        std::cout << "Square of (int32_t) " << factor << " is " << squared << ".\n";
        return std::make_shared<datatypes::AnyValue>(squared);
    }
    else if (return_value_any_value->type == datatypes::UINT32_T)
    {
        const uint32_t factor = return_value_any_value->uint32_t_value;
        const uint32_t squared = factor * factor;
        std::cout << "Square of (uint32_t) " << factor << " is " << squared << ".\n";
        return std::make_shared<datatypes::AnyValue>(squared);
    }
    else if (return_value_any_value->type == datatypes::FLOAT)
    {
        const float factor = return_value_any_value->uint32_t_value;
        const float squared = factor * factor;
        std::cout << "Square of (float) " << factor << " is " << squared << ".\n";
        return std::make_shared<datatypes::AnyValue>(squared);
    }
    else if (return_value_any_value->type == datatypes::FLOAT)
    {
        const double factor = return_value_any_value->uint32_t_value;
        const double squared = factor * factor;
        std::cout << "Square of (double) " << factor << " is " << squared << ".\n";
        return std::make_shared<datatypes::AnyValue>(squared);
    }
    std::cout << "The datatype of any_value->type is " << return_value_any_value->type << "\n";
    return std::make_shared<datatypes::AnyValue>();
}

std::shared_ptr<datatypes::AnyValue> expt(callback_system::CallbackEngine*, callback_system::CallbackObject*, std::vector<callback_system::CallbackParameter*>& input_parameters)
{
    if (input_parameters.size() != 2)
    {
        std::cout << "The size of input_parameter is " << input_parameters.size() << "\n";
        return std::make_shared<datatypes::AnyValue>();
    }

    std::shared_ptr<datatypes::AnyValue> base = std::make_shared<datatypes::AnyValue>(*input_parameters.at(0)->get_any_value());
    std::shared_ptr<datatypes::AnyValue> exponent = std::make_shared<datatypes::AnyValue>(*input_parameters.at(1)->get_any_value());

    if (base->type == datatypes::INT32_T && exponent->type == datatypes::INT32_T)
    {
        const int32_t power = std::pow(base->int32_t_value, exponent->int32_t_value);
        std::cout << "(int32_t) " << base->int32_t_value << "^" << exponent->int32_t_value << " is " << power << ".\n";
        return std::make_shared<datatypes::AnyValue>(power);
    }
    else if (base->type == datatypes::UINT32_T && exponent->type == datatypes::UINT32_T)
    {
        const uint32_t power = std::pow(base->uint32_t_value, exponent->uint32_t_value);
        std::cout << "(uint32_t) " << base->uint32_t_value << "^" << exponent->uint32_t_value << " is " << power << ".\n";
        return std::make_shared<datatypes::AnyValue>(power);
    }
    else if (base->type == datatypes::FLOAT && exponent->type == datatypes::FLOAT)
    {
        const float power = std::pow(base->float_value, exponent->float_value);
        std::cout << "(float) " << base->float_value << "^" << exponent->float_value << " is " << power << ".\n";
        return std::make_shared<datatypes::AnyValue>(power);
    }
    else if (base->type == datatypes::DOUBLE && exponent->type == datatypes::DOUBLE)
    {
        const double power = std::pow(base->double_value, exponent->double_value);
        std::cout << "(double) " << base->double_value << "^" << exponent->double_value << " is " << power << ".\n";
        return std::make_shared<datatypes::AnyValue>(power);
    }
    std::cout << "The datatype of base is " << base->type << "\n";
    std::cout << "The datatype of exponent is " << exponent->type << "\n";
    return std::make_shared<datatypes::AnyValue>();
}

std::shared_ptr<datatypes::AnyValue> expt_with_named_inputs(
        callback_system::CallbackEngine*,
        callback_system::CallbackObject* callback_object,
        std::vector<callback_system::CallbackParameter*>&)
{
    std::shared_ptr<datatypes::AnyValue> base = std::make_shared<datatypes::AnyValue>(*callback_object->get_any_value("base"));
    std::shared_ptr<datatypes::AnyValue> exponent = std::make_shared<datatypes::AnyValue>(*callback_object->get_any_value("exponent"));

    if (base->type == datatypes::INT32_T && exponent->type == datatypes::INT32_T)
    {
        const int32_t power = std::pow(base->int32_t_value, exponent->int32_t_value);
        std::cout << "(int32_t) " << base->int32_t_value << "^" << exponent->int32_t_value << " is " << power << ".\n";
        return std::make_shared<datatypes::AnyValue>(power);
    }
    else if (base->type == datatypes::UINT32_T && exponent->type == datatypes::UINT32_T)
    {
        const uint32_t power = std::pow(base->uint32_t_value, exponent->uint32_t_value);
        std::cout << "(uint32_t) " << base->uint32_t_value << "^" << exponent->uint32_t_value << " is " << power << ".\n";
        return std::make_shared<datatypes::AnyValue>(power);
    }
    else if (base->type == datatypes::FLOAT && exponent->type == datatypes::FLOAT)
    {
        const float power = std::pow(base->float_value, exponent->float_value);
        std::cout << "(float) " << base->float_value << "^" << exponent->float_value << " is " << power << ".\n";
        return std::make_shared<datatypes::AnyValue>(power);
    }
    else if (base->type == datatypes::DOUBLE && exponent->type == datatypes::DOUBLE)
    {
        const double power = std::pow(base->double_value, exponent->double_value);
        std::cout << "(double) " << base->double_value << "^" << exponent->double_value << " is " << power << ".\n";
        return std::make_shared<datatypes::AnyValue>(power);
    }
    std::cout << "The datatype of base is " << base->type << "\n";
    std::cout << "The datatype of exponent is " << exponent->type << "\n";
    return std::make_shared<datatypes::AnyValue>();
}

std::shared_ptr<datatypes::AnyValue> neg(callback_system::CallbackEngine*, callback_system::CallbackObject*, std::vector<callback_system::CallbackParameter*>& input_parameters)
{
    if (input_parameters.size() != 1)
    {
        std::cout << "The size of input_parameter is " << input_parameters.size() << "\n";
        return std::make_shared<datatypes::AnyValue>();
    }

    std::shared_ptr<datatypes::AnyValue> any_value = std::make_shared<datatypes::AnyValue>(*input_parameters.at(0)->get_any_value());

    if (any_value->type == datatypes::INT32_T)
    {
        const int32_t product = -1 * any_value->int32_t_value;
        std::cout << "-1 * (int32_t) " << any_value->int32_t_value << " is " << product << ".\n";
        return std::make_shared<datatypes::AnyValue>(product);
    }
    else if (any_value->type == datatypes::FLOAT)
    {
        const float product = -1.0 * any_value->float_value;
        std::cout << "-1 * (float) " << any_value->float_value << " is " << product << ".\n";
        return std::make_shared<datatypes::AnyValue>(product);
    }
    else if (any_value->type == datatypes::DOUBLE)
    {
        const double product = -1.0 * any_value->double_value;
        std::cout << "-1 * (double) " << any_value->double_value << " is " << product << ".\n";
        return std::make_shared<datatypes::AnyValue>(product);
    }
    std::cout << "The datatype of value is " << any_value->type << "\n";
    return std::make_shared<datatypes::AnyValue>();
}

TEST(callback_engine_must_function_properly, int32_t_zero_negated_equals_zero)
{
    callback_system::CallbackEngine* callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* callback_object = new callback_system::CallbackObject(nullptr, callback_engine);
    callback_object->set_new_callback(&neg);

    const int32_t zero = 0;
    const bool is_reference_0 = false;
    std::shared_ptr<datatypes::AnyValue> zero_value = std::make_shared<datatypes::AnyValue>(zero);
    new callback_system::CallbackParameter("", zero_value, is_reference_0, callback_object);

    std::shared_ptr<datatypes::AnyValue> result = callback_engine->execute();
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(result->type, datatypes::INT32_T);
    ASSERT_EQ(result->int32_t_value, 0);

    delete callback_engine;
}

TEST(callback_engine_must_function_properly, int32_t_one_negated_equals_minus_one)
{
    callback_system::CallbackEngine* callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* callback_object = new callback_system::CallbackObject(nullptr, callback_engine);
    callback_object->set_new_callback(&neg);

    const int32_t one = 1;
    const bool is_reference_1 = false;
    std::shared_ptr<datatypes::AnyValue> one_value = std::make_shared<datatypes::AnyValue>(one);
    new callback_system::CallbackParameter("", one_value, is_reference_1, callback_object);

    std::shared_ptr<datatypes::AnyValue> result = callback_engine->execute();
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(result->type, datatypes::INT32_T);
    ASSERT_EQ(result->int32_t_value, -1);

    delete callback_engine;
}

TEST(callback_engine_must_function_properly, int32_t_two_negated_equals_minus_two)
{
    callback_system::CallbackEngine* callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* callback_object = new callback_system::CallbackObject(nullptr, callback_engine);
    callback_object->set_new_callback(&neg);

    const int32_t two = 2;
    const bool is_reference_2 = false;
    std::shared_ptr<datatypes::AnyValue> two_value = std::make_shared<datatypes::AnyValue>(two);
    new callback_system::CallbackParameter("", two_value, is_reference_2, callback_object);

    std::shared_ptr<datatypes::AnyValue> result = callback_engine->execute();
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(result->type, datatypes::INT32_T);
    ASSERT_EQ(result->int32_t_value, -2);

    delete callback_engine;
}

TEST(callback_engine_must_function_properly, int32_t_minus_one_negated_equals_one)
{
    callback_system::CallbackEngine* callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* callback_object = new callback_system::CallbackObject(nullptr, callback_engine);
    callback_object->set_new_callback(&neg);

    const int32_t minus_one = -1;
    const bool is_reference_minus_1 = false;
    std::shared_ptr<datatypes::AnyValue> minus_one_value = std::make_shared<datatypes::AnyValue>(minus_one);
    new callback_system::CallbackParameter("", minus_one_value, is_reference_minus_1, callback_object);

    std::shared_ptr<datatypes::AnyValue> result = callback_engine->execute();
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(result->type, datatypes::INT32_T);
    ASSERT_EQ(result->int32_t_value, 1);

    delete callback_engine;
}

TEST(callback_engine_must_function_properly, int32_t_minus_two_negated_equals_two)
{
    callback_system::CallbackEngine* callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* callback_object = new callback_system::CallbackObject(nullptr, callback_engine);
    callback_object->set_new_callback(&neg);

    const int32_t minus_two = -2;
    const bool is_reference_minus_2 = false;
    std::shared_ptr<datatypes::AnyValue> minus_two_value = std::make_shared<datatypes::AnyValue>(minus_two);
    new callback_system::CallbackParameter("", minus_two_value, is_reference_minus_2, callback_object);

    std::shared_ptr<datatypes::AnyValue> result = callback_engine->execute();
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(result->type, datatypes::INT32_T);
    ASSERT_EQ(result->int32_t_value, 2);

    delete callback_engine;
}

TEST(callback_engine_must_function_properly, int32_t_three_squared_equals_nine)
{
    callback_system::CallbackEngine* callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* callback_object = new callback_system::CallbackObject(nullptr, callback_engine);
    callback_object->set_new_callback(&square);

    const int32_t three = 3;
    const bool is_reference_3 = false;
    std::shared_ptr<datatypes::AnyValue> three_value = std::make_shared<datatypes::AnyValue>(three);
    new callback_system::CallbackParameter("foo", three_value, is_reference_3, callback_object);

    std::shared_ptr<datatypes::AnyValue> result = callback_engine->execute();
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(result->type, datatypes::INT32_T);
    ASSERT_EQ(result->int32_t_value, 9);

    delete callback_engine;
}

TEST(callback_engine_must_function_properly, uint32_t_three_squared_equals_nine)
{
    callback_system::CallbackEngine* callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* callback_object = new callback_system::CallbackObject(nullptr, callback_engine);
    callback_object->set_new_callback(&square);

    const uint32_t three = 3;
    const bool is_reference_3 = false;
    std::shared_ptr<datatypes::AnyValue> three_value = std::make_shared<datatypes::AnyValue>(three);
    new callback_system::CallbackParameter("foo", three_value, is_reference_3, callback_object);

    std::shared_ptr<datatypes::AnyValue> result = callback_engine->execute();
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(result->type, datatypes::UINT32_T);
    ASSERT_EQ(result->uint32_t_value, 9);

    delete callback_engine;
}

TEST(callback_engine_must_function_properly, uint32_t_5_expt_7_equals_78125)
{
    callback_system::CallbackEngine* callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* callback_object = new callback_system::CallbackObject(nullptr, callback_engine);
    callback_object->set_new_callback(&expt);

    const uint32_t five = 5;
    const bool is_reference_5 = false;
    std::shared_ptr<datatypes::AnyValue> five_value = std::make_shared<datatypes::AnyValue>(five);
    new callback_system::CallbackParameter("foo", five_value, is_reference_5, callback_object);

    const uint32_t seven = 7;
    const bool is_reference_7 = false;
    std::shared_ptr<datatypes::AnyValue> seven_value = std::make_shared<datatypes::AnyValue>(seven);
    new callback_system::CallbackParameter("foo", seven_value, is_reference_7, callback_object);

    std::shared_ptr<datatypes::AnyValue> result = callback_engine->execute();
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(result->type, datatypes::UINT32_T);
    ASSERT_EQ(result->uint32_t_value, 78125);

    delete callback_engine;
}

TEST(callback_engine_must_function_properly, uint32_t_5_expt_7_equals_78125_with_named_inputs)
{
    callback_system::CallbackEngine* callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* callback_object = new callback_system::CallbackObject(nullptr, callback_engine);
    callback_object->set_new_callback(&expt_with_named_inputs);

    const uint32_t five = 5;
    const bool is_reference_5 = false;
    std::shared_ptr<datatypes::AnyValue> five_value = std::make_shared<datatypes::AnyValue>(five);
    new callback_system::CallbackParameter("base", five_value, is_reference_5, callback_object);
    std::shared_ptr<datatypes::AnyValue> anyvalue_base = std::make_shared<datatypes::AnyValue>(*callback_object->get_any_value("base"));
    ASSERT_EQ(anyvalue_base->type, datatypes::UINT32_T);

    const uint32_t seven = 7;
    const bool is_reference_7 = false;
    std::shared_ptr<datatypes::AnyValue> seven_value = std::make_shared<datatypes::AnyValue>(seven);
    new callback_system::CallbackParameter("exponent", seven_value, is_reference_7, callback_object);

    std::shared_ptr<datatypes::AnyValue> result = callback_engine->execute();
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(result->type, datatypes::UINT32_T);
    ASSERT_EQ(result->uint32_t_value, 78125);

    delete callback_engine;
}

TEST(callback_engine_must_function_properly, uint32_t_7_expt_5_then_squared_equals_282475249)
{
    callback_system::CallbackEngine* callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* callback_object_expt = new callback_system::CallbackObject(nullptr, callback_engine);
    callback_object_expt->set_new_callback(&expt);
    callback_system::CallbackObject* callback_object_square_last = new callback_system::CallbackObject(nullptr, callback_engine);
    callback_object_square_last->set_new_callback(&square_last);

    const uint32_t seven = 7;
    const bool is_reference_7 = false;
    std::shared_ptr<datatypes::AnyValue> seven_value = std::make_shared<datatypes::AnyValue>(seven);
    new callback_system::CallbackParameter("", seven_value, is_reference_7, callback_object_expt);

    const uint32_t five = 5;
    const bool is_reference_5 = false;
    std::shared_ptr<datatypes::AnyValue> five_value = std::make_shared<datatypes::AnyValue>(five);
    new callback_system::CallbackParameter("", five_value, is_reference_5, callback_object_expt);

    std::shared_ptr<datatypes::AnyValue> result = callback_engine->execute();
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(result->type, datatypes::UINT32_T);
    ASSERT_EQ(result->uint32_t_value, 282475249);

    delete callback_engine;
}

TEST(callback_engine_must_function_properly, two_squared_four_times_equals_65536)
{
    callback_system::CallbackEngine* callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* callback_object_1st_square = new callback_system::CallbackObject(nullptr, callback_engine);
    callback_object_1st_square->set_new_callback(&square);

    const uint32_t two = 2;
    const bool is_reference_2 = false;
    std::shared_ptr<datatypes::AnyValue> two_value = std::make_shared<datatypes::AnyValue>(two);
    new callback_system::CallbackParameter("", two_value, is_reference_2, callback_object_1st_square);

    callback_system::CallbackObject* callback_object_2nd_square = new callback_system::CallbackObject(nullptr, callback_engine);
    callback_object_2nd_square->set_new_callback(&square_last);
    callback_system::CallbackObject* callback_object_3rd_square = new callback_system::CallbackObject(nullptr, callback_engine);
    callback_object_3rd_square->set_new_callback(&square_last);
    callback_system::CallbackObject* callback_object_4th_square = new callback_system::CallbackObject(nullptr, callback_engine);
    callback_object_4th_square->set_new_callback(&square_last);

    std::shared_ptr<datatypes::AnyValue> result = callback_engine->execute();
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(result->type, datatypes::UINT32_T);
    ASSERT_EQ(result->uint32_t_value, 65536);

    delete callback_engine;
}
