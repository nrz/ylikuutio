#include "gtest/gtest.h"
#include "cpp/ylikuutio/common/any_value.hpp"
#include "cpp/ylikuutio/callback/callback_engine.hpp"
#include "cpp/ylikuutio/callback/callback_object.hpp"
#include "cpp/ylikuutio/callback/callback_parameter.hpp"
#include "cpp/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <iostream> // std::cout, std::cin, std::cerr

AnyValue square(std::vector<callback_system::CallbackParameter*> input_parameters)
{
    if (input_parameters.size() != 1)
    {
        std::cout << "The size of input_parameter is " << input_parameters.size() << "\n";
        return AnyValue();
    }

    AnyValue any_value = input_parameters.at(0)->get_any_value();

    if (any_value.type == datatypes::INT32_T)
    {
        int32_t factor = any_value.int32_t_value;
        int32_t squared = factor * factor;
        std::cout << "Square of (int32_t) " << factor << " is " << squared << ".\n";
        return AnyValue(squared);
    }
    else if (any_value.type == datatypes::UINT32_T)
    {
        uint32_t factor = any_value.uint32_t_value;
        uint32_t squared = factor * factor;
        std::cout << "Square of (uint32_t) " << factor << " is " << squared << ".\n";
        return AnyValue(squared);
    }
    else if (any_value.type == datatypes::FLOAT)
    {
        float factor = any_value.uint32_t_value;
        float squared = factor * factor;
        std::cout << "Square of (float) " << factor << " is " << squared << ".\n";
        return AnyValue(squared);
    }
    else if (any_value.type == datatypes::FLOAT)
    {
        double factor = any_value.uint32_t_value;
        double squared = factor * factor;
        std::cout << "Square of (double) " << factor << " is " << squared << ".\n";
        return AnyValue(squared);
    }
    std::cout << "The datatype of any_value.type is " << any_value.type << "\n";
    return AnyValue();
}

TEST(callback_engine_must_be_function_properly, int32_t_three_squared_equals_nine)
{
    callback_system::CallbackEngine* callback_engine = new callback_system::CallbackEngine();

    InputParametersToAnyValueCallback square_callback = &square;
    callback_system::CallbackObject* callback_object = new callback_system::CallbackObject(square_callback, callback_engine);

    std::string parameter_name = "foo";
    int32_t three = 3;
    AnyValue three_value = AnyValue(three);

    bool is_reference_3 = false;
    callback_system::CallbackParameter* callback_parameter_3 = new callback_system::CallbackParameter(parameter_name, three, is_reference_3, callback_object);

    AnyValue result = callback_engine->execute();
    ASSERT_EQ(result.type, datatypes::INT32_T);
    ASSERT_EQ(result.int32_t_value, 9);

    delete callback_engine;
}
