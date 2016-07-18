#include "custom_namespace.hpp"
#include "cpp/ylikuutio/common/any_value.hpp"

// Include standard headers
#include <stdint.h>      // uint32_t etc.
#include <string>        // std::string

namespace callback_system
{
    // getter functions for callbacks and callback objects.
    datatypes::AnyValue* CustomNamespace::get_any_value(std::string name)
    {
        return &this->anyvalue_hashmap[name];
    }

    bool CustomNamespace::get_bool(std::string name)
    {
        return this->anyvalue_hashmap[name].bool_value;
    }

    float CustomNamespace::get_float(std::string name)
    {
        return this->anyvalue_hashmap[name].float_value;
    }

    double CustomNamespace::get_double(std::string name)
    {
        return this->anyvalue_hashmap[name].double_value;
    }

    int32_t CustomNamespace::get_int32_t(std::string name)
    {
        return this->anyvalue_hashmap[name].int32_t_value;
    }

    uint32_t CustomNamespace::get_uint32_t(std::string name)
    {
        return this->anyvalue_hashmap[name].uint32_t_value;
    }

    void* CustomNamespace::get_void_pointer(std::string name)
    {
        return this->anyvalue_hashmap[name].void_pointer;
    }

    // setter functions for callbacks and callback objects.

    void CustomNamespace::set_bool(std::string name, bool value)
    {
        this->anyvalue_hashmap[name] = datatypes::AnyValue(value);
    }

    void CustomNamespace::set_float(std::string name, float value)
    {
        this->anyvalue_hashmap[name] = datatypes::AnyValue(value);
    }

    void CustomNamespace::set_double(std::string name, double value)
    {
        this->anyvalue_hashmap[name] = datatypes::AnyValue(value);
    }

    void CustomNamespace::set_int32_t(std::string name, int32_t value)
    {
        this->anyvalue_hashmap[name] = datatypes::AnyValue(value);
    }

    void CustomNamespace::set_uint32_t(std::string name, uint32_t value)
    {
        this->anyvalue_hashmap[name] = datatypes::AnyValue(value);
    }

    void CustomNamespace::set_void_pointer(std::string name, void* value)
    {
        this->anyvalue_hashmap[name] = datatypes::AnyValue(value);
    }
}
