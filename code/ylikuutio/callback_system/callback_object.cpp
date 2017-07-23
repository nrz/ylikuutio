#include "callback_object.hpp"
#include "callback_parameter.hpp"
#include "code/ylikuutio/common/any_value.hpp"
#include "code/ylikuutio/common/globals.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace callback_system
{
    // getter function for callbacks and callback objects.
    datatypes::AnyValue* CallbackObject::get_any_value(std::string name)
    {
        return &this->anyvalue_hashmap[name];
    }

    datatypes::AnyValue* CallbackObject::get_arg(uint32_t arg_i)
    {
        if (arg_i >= this->callback_parameter_pointer_vector.size())
        {
            std::cerr << "virhe 1!";
            return nullptr;
        }

        callback_system::CallbackParameter* callback_parameter = this->callback_parameter_pointer_vector.at(arg_i);

        if (callback_parameter == nullptr)
        {
            std::cerr << "virhe 2!";
            return nullptr;
        }

        return callback_parameter->any_value;
    }

    // setter function for callbacks and callback objects.
    void CallbackObject::set_any_value(const std::string name, const datatypes::AnyValue* const any_value)
    {
        this->anyvalue_hashmap[name] = *any_value;
    }

    void CallbackObject::bind_to_parent()
    {
        hierarchy::bind_child_to_parent<callback_system::CallbackObject*>(this, this->parent_pointer->callback_object_pointer_vector, this->parent_pointer->free_callback_objectID_queue, &this->parent_pointer->number_of_callback_objects);
    }

    void CallbackObject::set_new_callback(InputParametersToAnyValueCallback callback)
    {
        this->callback = callback;
    }

    CallbackObject::CallbackObject(callback_system::CallbackEngine* parent_pointer)
    {
        // constructor.
        this->parent_pointer = parent_pointer;

        // get childID from the CallbackEngine and set pointer to this CallbackObject.
        this->bind_to_parent();
    }

    CallbackObject::CallbackObject(InputParametersToAnyValueCallback callback, callback_system::CallbackEngine* parent_pointer)
    {
        // constructor.
        this->callback = callback;
        this->parent_pointer = parent_pointer;

        this->number_of_callback_parameters = 0;

        // get childID from the CallbackEngine and set pointer to this CallbackObject.
        this->bind_to_parent();
    }

    CallbackObject::~CallbackObject()
    {
        std::cout << "Callback object with childID " << this->childID << " will be destroyed.\n";

        // destroy all callback parameters of this callback object.
        std::cout << "All callback parameters of this callback object will be destroyed.\n";
        for (uint32_t child_i = 0; child_i < this->callback_parameter_pointer_vector.size(); child_i++)
        {
            delete this->callback_parameter_pointer_vector[child_i];
        }
    }

    void CallbackObject::set_callback_parameter_pointer(const uint32_t childID, callback_system::CallbackParameter* const child_pointer)
    {
        this->callback_parameter_pointer_vector[childID] = child_pointer;

        if (child_pointer == nullptr)
        {
            if (childID == this->callback_parameter_pointer_vector.size() - 1)
            {
                // OK, this is the biggest childID of all childID's of this 'object'.
                // We can reduce the size of the child pointer vector at least by 1.
                while ((!this->callback_parameter_pointer_vector.empty()) && (this->callback_parameter_pointer_vector.back() == nullptr))
                {
                    // Reduce the size of child pointer vector by 1.
                    this->callback_parameter_pointer_vector.pop_back();
                }
            }
        }
    }

    datatypes::AnyValue* CallbackObject::execute()
    {
        if (this->callback != nullptr)
        {
            return this->callback(this->parent_pointer, this, this->callback_parameter_pointer_vector);
        }
        return nullptr;
    }
}
