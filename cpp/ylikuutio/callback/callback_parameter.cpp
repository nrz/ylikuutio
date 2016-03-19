#include "callback_parameter.hpp"
#include "callback_object.hpp"
#include "cpp/ylikuutio/common/any_value.hpp"
#include "cpp/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
#include <string>   // std::string

namespace callback_system
{
    CallbackParameter::CallbackParameter(std::string name, datatypes::AnyValue any_value, bool is_reference, callback_system::CallbackObject* parent_pointer)
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

    datatypes::AnyValue CallbackParameter::get_any_value()
    {
        return this->any_value;
    }

    void CallbackParameter::bind_to_parent()
    {
        this->childID = this->parent_pointer->get_callback_parameterID(this->parent_pointer->callback_parameter_pointer_vector, this->parent_pointer->free_callback_parameterID_queue);
        // set pointer to the child in parent's child pointer vector so that parent knows about children's whereabouts!
        this->parent_pointer->set_child_pointer(this->childID, this);
    }
}
