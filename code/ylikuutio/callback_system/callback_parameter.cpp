#include "callback_parameter.hpp"
#include "callback_object.hpp"
#include "code/ylikuutio/common/any_value.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
#include <memory>   // std::make_shared, std::shared_ptr
#include <string>   // std::string

namespace yli
{
    namespace callback_system
    {
        void CallbackParameter::bind_to_parent()
        {
            hierarchy::bind_child_to_parent<yli::callback_system::CallbackParameter*>(this, this->parent->callback_parameter_pointer_vector, this->parent->free_callback_parameterID_queue, &this->parent->number_of_callback_parameters);

            if (!this->name.empty())
            {
                // This is a named variable, so store it in parent's `anyvalue_hashmap`.
                this->parent->set_any_value(this->name, std::make_shared<datatypes::AnyValue>(*this->any_value));
            }
        }

        CallbackParameter::CallbackParameter(const std::string& name, std::shared_ptr<datatypes::AnyValue> any_value, const bool is_reference, yli::callback_system::CallbackObject* const parent)
        {
            // constructor.
            this->name = name;
            this->any_value = any_value;
            this->is_reference = is_reference;
            this->parent = parent;

            // get childID from the CallbackObject and set pointer to this CallbackParameter.
            this->bind_to_parent();
        }

        CallbackParameter::~CallbackParameter()
        {
            // destructor.
            std::cout << "Callback parameter with childID " << this->childID << " will be destroyed.\n";

            // set pointer to this object to nullptr.
            this->parent->set_callback_parameter_pointer(this->childID, nullptr);
        }

        std::shared_ptr<datatypes::AnyValue> CallbackParameter::get_any_value() const
        {
            return std::make_shared<datatypes::AnyValue>(*this->any_value);
        }
    }
}
