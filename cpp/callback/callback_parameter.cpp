#include "callback_parameter.hpp"
#include "callback_object.hpp"
#include "cpp/common/any_value.hpp"

// Include standard headers
#include <iostream>
#include <string> // std::string
#include <vector> // std::vector

namespace callback_system
{
    CallbackParameter::CallbackParameter(std::string name, AnyValue any_value, bool is_reference, callback_system::CallbackObject* callback_object)
    {
        // constructor.
        this->name = name;
        this->any_value = any_value;
        this->is_reference = is_reference;
    }
}
