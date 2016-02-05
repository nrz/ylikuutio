#include "callback_object.hpp"
#include "callback_parameter.hpp"
#include "cpp/ylikuutio/common/any_value.hpp"
#include "cpp/ylikuutio/common/globals.hpp"

// Include standard headers
#include <iostream>
#include <string> // std::string
#include <vector> // std::vector

namespace callback_system
{
    CallbackObject::CallbackObject(InputParametersToAnyValueCallback callback, callback_system::CallbackEngine* callback_engine_pointer)
    {
        this->callback_engine_pointer = callback_engine_pointer;
    }

    AnyValue CallbackObject::execute()
    {
        std::cout << "Hello from AnyValue CallbackObject::execute()\n";

        for (uint32_t child_i = 0; child_i < this->callback_parameter_pointer_vector.size(); child_i++)
        {
            callback_system::CallbackParameter* input_parameter_pointer = this->callback_parameter_pointer_vector.at(child_i);

            switch (input_parameter_pointer->any_value.type)
            {
                case datatypes::BOOL:
                    this->callback_engine_pointer->set_bool(input_parameter_pointer->name, input_parameter_pointer->any_value.bool_value);
                    break;
                case datatypes::FLOAT:
                    this->callback_engine_pointer->set_float(input_parameter_pointer->name, input_parameter_pointer->any_value.float_value);
                    break;
                case datatypes::DOUBLE:
                    this->callback_engine_pointer->set_double(input_parameter_pointer->name, input_parameter_pointer->any_value.double_value);
                    break;
                case datatypes::INT32_T:
                    this->callback_engine_pointer->set_int32_t(input_parameter_pointer->name, input_parameter_pointer->any_value.int32_t_value);
                    break;
                case datatypes::UINT32_T:
                    this->callback_engine_pointer->set_uint32_t(input_parameter_pointer->name, input_parameter_pointer->any_value.uint32_t_value);
                    break;
                case datatypes::VOID_POINTER:
                    this->callback_engine_pointer->set_void_pointer(input_parameter_pointer->name, input_parameter_pointer->any_value.void_pointer);
                    break;
                default:
                    break;
            }
        }
        return this->callback(this->callback_parameter_pointer_vector);
    }
}
