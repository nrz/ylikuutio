#include "callback_object.hpp"
#include "callback_parameter.hpp"
#include "code/ylikuutio/common/any_value.hpp"
#include "code/ylikuutio/common/globals.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <memory>   // std::make_shared, std::shared_ptr
#include <string>   // std::string
#include <unordered_map> // std::unordered_map
#include <vector>   // std::vector

namespace yli
{
    namespace callback_system
    {
        // getter function for callbacks and callback objects.
        std::shared_ptr<datatypes::AnyValue> CallbackObject::get_any_value(const std::string& name) const
        {
            if (this->anyvalue_hashmap.count(name) != 1)
            {
                return nullptr;
            }
            return std::make_shared<datatypes::AnyValue>(this->anyvalue_hashmap.at(name));
        }

        std::shared_ptr<datatypes::AnyValue> CallbackObject::get_arg(const std::size_t arg_i) const
        {
            if (arg_i >= this->callback_parameter_pointer_vector.size())
            {
                std::cerr << "error #1 in CallbackObject code.\n";
                return nullptr;
            }

            yli::callback_system::CallbackParameter* callback_parameter = this->callback_parameter_pointer_vector.at(arg_i);

            if (callback_parameter == nullptr)
            {
                std::cerr << "error #2 in CallbackObject code.\n";
                return nullptr;
            }

            return std::make_shared<datatypes::AnyValue>(*callback_parameter->any_value);
        }

        // setter function for callbacks and callback objects.
        void CallbackObject::set_any_value(const std::string& name, std::shared_ptr<datatypes::AnyValue> any_value)
        {
            this->anyvalue_hashmap[name] = *any_value;
        }

        void CallbackObject::bind_to_parent()
        {
            yli::hierarchy::bind_child_to_parent<yli::callback_system::CallbackObject*>(this, this->parent->callback_object_pointer_vector, this->parent->free_callback_objectID_queue, &this->parent->number_of_callback_objects);
        }

        void CallbackObject::set_new_callback(const InputParametersToAnyValueCallback callback)
        {
            this->callback = callback;
        }

        CallbackObject::CallbackObject(yli::callback_system::CallbackEngine* parent)
        {
            // constructor.
            this->childID = -1;
            this->callback = nullptr;
            this->parent = parent;

            this->number_of_callback_parameters = 0;

            // get childID from the CallbackEngine and set pointer to this CallbackObject.
            this->bind_to_parent();
        }

        CallbackObject::CallbackObject(const InputParametersToAnyValueCallback callback, yli::callback_system::CallbackEngine* parent)
        {
            // constructor.
            this->childID = -1;
            this->callback = callback;
            this->parent = parent;

            this->number_of_callback_parameters = 0;

            // get childID from the CallbackEngine and set pointer to this CallbackObject.
            this->bind_to_parent();
        }

        CallbackObject::~CallbackObject()
        {
            std::cout << "Callback object with childID " << this->childID << " will be destroyed.\n";

            // destroy all callback parameters of this callback object.
            std::cout << "All callback parameters of this callback object will be destroyed.\n";
            for (std::size_t child_i = 0; child_i < this->callback_parameter_pointer_vector.size(); child_i++)
            {
                delete this->callback_parameter_pointer_vector[child_i];
            }
        }

        void CallbackObject::set_callback_parameter_pointer(const std::size_t childID, yli::callback_system::CallbackParameter* const child_pointer)
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

        std::shared_ptr<datatypes::AnyValue> CallbackObject::execute()
        {
            if (this->callback != nullptr)
            {
                return this->callback(this->parent, this, this->callback_parameter_pointer_vector);
            }
            return nullptr;
        }
    }
}
