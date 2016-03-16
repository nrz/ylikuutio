#include "callback_parameter.hpp"
#include "callback_object.hpp"
#include "cpp/ylikuutio/common/any_value.hpp"
#include "cpp/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
#include <string>   // std::string

namespace callback_system
{
    CallbackParameter::CallbackParameter(std::string name, AnyValue any_value, bool is_reference, callback_system::CallbackObject* parent_pointer)
    {
        // constructor.
        this->name = name;
        this->any_value = any_value;
        this->is_reference = is_reference;
        this->parent_pointer = parent_pointer;

        // get childID from the CallbackObject and set pointer to this CallbackParameter.
        this->bind_to_parent();
    }

    CallbackParameter::~CallbackParameter()
    {
        // destructor.
        std::cout << "Callback parameter with childID " << this->childID << " will be destroyed.\n";

        // set pointer to this object to nullptr.
        this->parent_pointer->set_callback_parameter_pointer(this->childID, nullptr);
    }

    void CallbackParameter::bind_to_parent()
    {
        callback_system::CallbackObject* parent_pointer;
        parent_pointer = this->parent_pointer;

        std::vector<void*> callback_parameter_void_pointer_vector;
        callback_parameter_void_pointer_vector.assign(parent_pointer->callback_parameter_pointer_vector.begin(), parent_pointer->callback_parameter_pointer_vector.end());
        hierarchy::bind_child_to_parent<callback_system::CallbackParameter*>(this, callback_parameter_void_pointer_vector, parent_pointer->free_callback_parameterID_queue);
    }
}
