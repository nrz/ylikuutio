#include "console_callback_object.hpp"

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
#include <memory>   // std::make_shared, std::shared_ptr
#include <stdint.h> // uint32_t etc.

namespace yli
{
    namespace console
    {
        ConsoleCallbackObject::~ConsoleCallbackObject()
        {
            std::cout << "Console callback object with childID " << this->childID << " will be destroyed.\n";

            // destroy all callback parameters of this callback object.
            std::cout << "All callback parameters of this console callback object will be destroyed.\n";
            for (uint32_t child_i = 0; child_i < this->callback_parameter_pointer_vector.size(); child_i++)
            {
                delete this->callback_parameter_pointer_vector[child_i];
            }
        }

        std::shared_ptr<datatypes::AnyValue> ConsoleCallbackObject::execute()
        {
            if (this->console_callback != nullptr)
            {
                return std::shared_ptr<datatypes::AnyValue>(this->console_callback(this->parent, this, this->callback_parameter_pointer_vector, this->console_pointer));
            }
            return nullptr;
        }
    }
}
