#include "gtest/gtest.h"
#include "cpp/ylikuutio/common/any_value.hpp"
#include "cpp/ylikuutio/callback_system/callback_engine.hpp"
#include "cpp/ylikuutio/callback_system/callback_object.hpp"
#include "cpp/ylikuutio/callback_system/callback_parameter.hpp"
#include "cpp/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <iostream> // std::cout, std::cin, std::cerr

datatypes::AnyValue* square(callback_system::CallbackEngine*, callback_system::CallbackObject*, std::vector<callback_system::CallbackParameter*> input_parameters)
{
    if (input_parameters.size() != 1)
    {
        std::cout << "The size of input_parameter is " << input_parameters.size() << "\n";
        return new datatypes::AnyValue();
    }

    datatypes::AnyValue* any_value = input_parameters.at(0)->get_any_value();

    if (any_value->type == datatypes::INT32_T)
    {
        int32_t factor = any_value->int32_t_value;
        int32_t squared = factor * factor;
        std::cout << "Square of (int32_t) " << factor << " is " << squared << ".\n";
        return new datatypes::AnyValue(squared);
    }
    else if (any_value->type == datatypes::UINT32_T)
    {
        uint32_t factor = any_value->uint32_t_value;
        uint32_t squared = factor * factor;
        std::cout << "Square of (uint32_t) " << factor << " is " << squared << ".\n";
        return new datatypes::AnyValue(squared);
    }
    else if (any_value->type == datatypes::FLOAT)
    {
        float factor = any_value->uint32_t_value;
        float squared = factor * factor;
        std::cout << "Square of (float) " << factor << " is " << squared << ".\n";
        return new datatypes::AnyValue(squared);
    }
    else if (any_value->type == datatypes::FLOAT)
    {
        double factor = any_value->uint32_t_value;
        double squared = factor * factor;
        std::cout << "Square of (double) " << factor << " is " << squared << ".\n";
        return new datatypes::AnyValue(squared);
    }
    std::cout << "The datatype of any_value->type is " << any_value->type << "\n";
    return new datatypes::AnyValue();
}

datatypes::AnyValue* expt(callback_system::CallbackEngine*, callback_system::CallbackObject*, std::vector<callback_system::CallbackParameter*> input_parameters)
{
    if (input_parameters.size() != 2)
    {
        std::cout << "The size of input_parameter is " << input_parameters.size() << "\n";
        return new datatypes::AnyValue();
    }

    datatypes::AnyValue* base = input_parameters.at(0)->get_any_value();
    datatypes::AnyValue* exponent = input_parameters.at(1)->get_any_value();

    if (base->type == datatypes::INT32_T && exponent->type == datatypes::INT32_T)
    {
        int32_t power = std::pow(base->int32_t_value, exponent->int32_t_value);
        std::cout << "(int32_t) " << base->int32_t_value << "^" << exponent->int32_t_value << " is " << power << ".\n";
        return new datatypes::AnyValue(power);
    }
    else if (base->type == datatypes::UINT32_T && exponent->type == datatypes::UINT32_T)
    {
        uint32_t power = std::pow(base->uint32_t_value, exponent->uint32_t_value);
        std::cout << "(uint32_t) " << base->uint32_t_value << "^" << exponent->uint32_t_value << " is " << power << ".\n";
        return new datatypes::AnyValue(power);
    }
    else if (base->type == datatypes::FLOAT && exponent->type == datatypes::FLOAT)
    {
        float power = std::pow(base->float_value, exponent->float_value);
        std::cout << "(float) " << base->float_value << "^" << exponent->float_value << " is " << power << ".\n";
        return new datatypes::AnyValue(power);
    }
    else if (base->type == datatypes::DOUBLE && exponent->type == datatypes::DOUBLE)
    {
        double power = std::pow(base->double_value, exponent->double_value);
        std::cout << "(double) " << base->double_value << "^" << exponent->double_value << " is " << power << ".\n";
        return new datatypes::AnyValue(power);
    }
    std::cout << "The datatype of base is " << base->type << "\n";
    std::cout << "The datatype of exponent is " << exponent->type << "\n";
    return new datatypes::AnyValue();
}

datatypes::AnyValue* expt_with_named_inputs(
        callback_system::CallbackEngine*,
        callback_system::CallbackObject* callback_object,
        std::vector<callback_system::CallbackParameter*>)
{
    datatypes::AnyValue* base = callback_object->get_any_value("base");
    datatypes::AnyValue* exponent = callback_object->get_any_value("exponent");

    if (base->type == datatypes::INT32_T && exponent->type == datatypes::INT32_T)
    {
        int32_t power = std::pow(base->int32_t_value, exponent->int32_t_value);
        std::cout << "(int32_t) " << base->int32_t_value << "^" << exponent->int32_t_value << " is " << power << ".\n";
        return new datatypes::AnyValue(power);
    }
    else if (base->type == datatypes::UINT32_T && exponent->type == datatypes::UINT32_T)
    {
        uint32_t power = std::pow(base->uint32_t_value, exponent->uint32_t_value);
        std::cout << "(uint32_t) " << base->uint32_t_value << "^" << exponent->uint32_t_value << " is " << power << ".\n";
        return new datatypes::AnyValue(power);
    }
    else if (base->type == datatypes::FLOAT && exponent->type == datatypes::FLOAT)
    {
        float power = std::pow(base->float_value, exponent->float_value);
        std::cout << "(float) " << base->float_value << "^" << exponent->float_value << " is " << power << ".\n";
        return new datatypes::AnyValue(power);
    }
    else if (base->type == datatypes::DOUBLE && exponent->type == datatypes::DOUBLE)
    {
        double power = std::pow(base->double_value, exponent->double_value);
        std::cout << "(double) " << base->double_value << "^" << exponent->double_value << " is " << power << ".\n";
        return new datatypes::AnyValue(power);
    }
    std::cout << "The datatype of base is " << base->type << "\n";
    std::cout << "The datatype of exponent is " << exponent->type << "\n";
    return new datatypes::AnyValue();
}

TEST(callback_engine_must_function_properly, int32_t_three_squared_equals_nine)
{
    callback_system::CallbackEngine* callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* callback_object = new callback_system::CallbackObject(nullptr, callback_engine);
    callback_object->set_new_callback(&square);

    int32_t three = 3;
    bool is_reference_3 = false;
    datatypes::AnyValue* three_value = new datatypes::AnyValue(three);
    callback_system::CallbackParameter* callback_parameter_3 = new callback_system::CallbackParameter("foo", three_value, is_reference_3, callback_object);

    datatypes::AnyValue* result = callback_engine->execute();
    ASSERT_EQ(result->type, datatypes::INT32_T);
    ASSERT_EQ(result->int32_t_value, 9);

    delete callback_engine;
}
TEST(callback_engine_must_function_properly, uint32_t_three_squared_equals_nine)
{
    callback_system::CallbackEngine* callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* callback_object = new callback_system::CallbackObject(nullptr, callback_engine);
    callback_object->set_new_callback(&square);

    uint32_t three = 3;
    bool is_reference_3 = false;
    datatypes::AnyValue* three_value = new datatypes::AnyValue(three);
    callback_system::CallbackParameter* callback_parameter_3 = new callback_system::CallbackParameter("foo", three_value, is_reference_3, callback_object);

    datatypes::AnyValue* result = callback_engine->execute();
    ASSERT_EQ(result->type, datatypes::UINT32_T);
    ASSERT_EQ(result->uint32_t_value, 9);

    delete callback_engine;
}
TEST(callback_engine_must_function_properly, uint32_t_5_expt_7_equals_78125)
{
    callback_system::CallbackEngine* callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* callback_object = new callback_system::CallbackObject(nullptr, callback_engine);
    callback_object->set_new_callback(&expt);

    uint32_t five = 5;
    bool is_reference_5 = false;
    datatypes::AnyValue* five_value = new datatypes::AnyValue(five);
    callback_system::CallbackParameter* callback_parameter_5 = new callback_system::CallbackParameter("foo", five_value, is_reference_5, callback_object);

    uint32_t seven = 7;
    bool is_reference_7 = false;
    datatypes::AnyValue* seven_value = new datatypes::AnyValue(seven);
    callback_system::CallbackParameter* callback_parameter_3 = new callback_system::CallbackParameter("foo", seven_value, is_reference_7, callback_object);

    datatypes::AnyValue* result = callback_engine->execute();
    ASSERT_EQ(result->type, datatypes::UINT32_T);
    ASSERT_EQ(result->uint32_t_value, 78125);

    delete callback_engine;
}
TEST(callback_engine_must_function_properly, uint32_t_5_expt_7_equals_78125_with_named_inputs)
{
    callback_system::CallbackEngine* callback_engine = new callback_system::CallbackEngine();
    callback_system::CallbackObject* callback_object = new callback_system::CallbackObject(nullptr, callback_engine);
    callback_object->set_new_callback(&expt_with_named_inputs);

    uint32_t five = 5;
    bool is_reference_5 = false;
    datatypes::AnyValue* five_value = new datatypes::AnyValue(five);
    callback_system::CallbackParameter* callback_parameter_5 = new callback_system::CallbackParameter("base", five_value, is_reference_5, callback_object);
    datatypes::AnyValue* anyvalue_base = callback_object->get_any_value("base");
    ASSERT_EQ(anyvalue_base->type, datatypes::UINT32_T);

    uint32_t seven = 7;
    bool is_reference_7 = false;
    datatypes::AnyValue* seven_value = new datatypes::AnyValue(seven);
    callback_system::CallbackParameter* callback_parameter_3 = new callback_system::CallbackParameter("exponent", seven_value, is_reference_7, callback_object);

    datatypes::AnyValue* result = callback_engine->execute();
    ASSERT_EQ(result->type, datatypes::UINT32_T);
    ASSERT_EQ(result->uint32_t_value, 78125);

    delete callback_engine;
}
