#include "callback.hpp"

// Include standard headers
#include <iostream>
#include <string> // std::string
#include <vector> // std::vector

namespace callback_system
{
    CallbackEngine::CallbackEngine()
    {
        // constructor.
    }

    // getter functions for callbacks and callback objects.

    bool CallbackEngine::get_bool(std::string name)
    {
        return this->bool_hashmap[name];
    }

    float CallbackEngine::get_float(std::string name)
    {
        return this->float_hashmap[name];
    }

    double CallbackEngine::get_double(std::string name)
    {
        return this->double_hashmap[name];
    }

    int32_t CallbackEngine::get_int32_t(std::string name)
    {
        return this->int32_t_hashmap[name];
    }

    uint32_t CallbackEngine::get_uint32_t(std::string name)
    {
        return this->uint32_t_hashmap[name];
    }

    void* CallbackEngine::get_void_pointer(std::string name)
    {
        return this->void_pointer_hashmap[name];
    }

    // setter functions for callbacks and callback objects.

    void CallbackEngine::set_bool(std::string name, bool value)
    {
        this->bool_hashmap[name] = value;
    }

    void CallbackEngine::set_float(std::string name, float value)
    {
        this->float_hashmap[name] = value;
    }

    void CallbackEngine::set_double(std::string name, double value)
    {
        this->double_hashmap[name] = value;
    }

    void CallbackEngine::set_int32_t(std::string name, int32_t value)
    {
        this->int32_t_hashmap[name] = value;
    }

    void CallbackEngine::set_uint32_t(std::string name, uint32_t value)
    {
        this->uint32_t_hashmap[name] = value;
    }

    void CallbackEngine::set_void_pointer(std::string name, void* value)
    {
        this->void_pointer_hashmap[name] = value;
    }

    AnyValue CallbackEngine::execute()
    {
        std::cout << "Hello from AnyValue CallbackEngine::execute()\n";

        AnyValue any_value;

        // execute all callbacks.
        for (callback_system::CallbackObject callback_object : this->callback_objects)
        {
            any_value = callback_object.execute();
        }

        return any_value;
    }

    CallbackObject::CallbackObject(InputParametersToAnyValueCallback callback, callback_system::CallbackEngine* callback_engine_pointer)
    {
        this->callback_engine_pointer = callback_engine_pointer;
    }

    void CallbackObject::add_input_parameter(std::string name, AnyValue any_value, bool is_reference)
    {
        this->input_parameters.push_back(new callback_system::CallbackParameter(name, any_value, is_reference, this));
    }

    AnyValue CallbackObject::execute()
    {
        std::cout << "Hello from AnyValue CallbackObject::execute()\n";

        for (callback_system::CallbackParameter* input_parameter : this->input_parameters)
        {
            switch (input_parameter->any_value.type)
            {
                case datatypes::BOOL:
                    this->callback_engine_pointer->set_bool(input_parameter->name, input_parameter->any_value.bool_value);
                    break;
                case datatypes::FLOAT:
                    this->callback_engine_pointer->set_float(input_parameter->name, input_parameter->any_value.float_value);
                    break;
                case datatypes::DOUBLE:
                    this->callback_engine_pointer->set_double(input_parameter->name, input_parameter->any_value.double_value);
                    break;
                case datatypes::INT32_T:
                    this->callback_engine_pointer->set_int32_t(input_parameter->name, input_parameter->any_value.int32_t_value);
                    break;
                case datatypes::UINT32_T:
                    this->callback_engine_pointer->set_uint32_t(input_parameter->name, input_parameter->any_value.uint32_t_value);
                    break;
                case datatypes::VOID_POINTER:
                    this->callback_engine_pointer->set_void_pointer(input_parameter->name, input_parameter->any_value.void_pointer);
                    break;
                default:
                    break;
            }
        }
        return this->callback(this->input_parameters);
    }

    CallbackParameter::CallbackParameter(std::string name, AnyValue any_value, bool is_reference, callback_system::CallbackObject* callback_object)
    {
        // constructor.
        this->name = name;
        this->any_value = any_value;
        this->is_reference = is_reference;
    }
}
