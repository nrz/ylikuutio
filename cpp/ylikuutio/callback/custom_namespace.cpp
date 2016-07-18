#include "custom_namespace.hpp"
#include "cpp/ylikuutio/common/any_value.hpp"

// Include standard headers
#include <stdint.h>      // uint32_t etc.
#include <string>        // std::string

namespace callback_system
{
    // getter function for callbacks and callback objects.
    datatypes::AnyValue* CustomNamespace::get_any_value(std::string name)
    {
        return &this->anyvalue_hashmap[name];
    }

    // setter function for callbacks and callback objects.
    void CustomNamespace::set_any_value(std::string name, datatypes::AnyValue any_value)
    {
        this->anyvalue_hashmap[name] = any_value;
    }
}
