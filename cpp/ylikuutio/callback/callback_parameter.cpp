#include "callback_parameter.hpp"
#include "callback_object.hpp"
#include "cpp/ylikuutio/common/any_value.hpp"

// Include standard headers
#include <string> // std::string

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
