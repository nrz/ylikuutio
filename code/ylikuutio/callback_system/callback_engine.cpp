#include "callback_engine.hpp"
#include "callback_object.hpp"
#include "code/ylikuutio/common/any_value.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
#include <memory>   // std::make_shared, std::shared_ptr
#include <queue>    // std::queue
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli
{
    namespace callback_system
    {
        CallbackEngine::CallbackEngine()
        {
            // constructor.
            this->number_of_callback_objects = 0;
        }

        CallbackEngine::~CallbackEngine()
        {
            // destructor.
            std::cout << "This callback engine will be destroyed.\n";

            // destroy all callback objects of this callback engine.
            std::cout << "All callback objects of this callback engine will be destroyed.\n";
            hierarchy::delete_children<yli::callback_system::CallbackObject*>(this->callback_object_pointer_vector, &this->number_of_callback_objects);
        }

        void CallbackEngine::set_callback_object_pointer(const int32_t childID, yli::callback_system::CallbackObject* const child_pointer)
        {
            hierarchy::set_child_pointer(childID, child_pointer, this->callback_object_pointer_vector, this->free_callback_objectID_queue, &this->number_of_callback_objects);
        }

        std::shared_ptr<datatypes::AnyValue> CallbackEngine::execute()
        {
            std::shared_ptr<datatypes::AnyValue> any_value = nullptr;

            // execute all callbacks.
            for (uint32_t child_i = 0; child_i < this->callback_object_pointer_vector.size(); child_i++)
            {
                yli::callback_system::CallbackObject* callback_object_pointer = static_cast<yli::callback_system::CallbackObject*>(this->callback_object_pointer_vector[child_i]);

                if (callback_object_pointer != nullptr)
                {
                    any_value = callback_object_pointer->execute();
                    this->return_values.push_back(any_value);
                }
                else
                {
                    this->return_values.push_back(nullptr);
                }
            }

            this->return_values.clear();
            return std::shared_ptr<datatypes::AnyValue>(any_value);
        }

        uint32_t CallbackEngine::get_n_of_return_values() const
        {
            return this->return_values.size();
        }

        std::shared_ptr<datatypes::AnyValue> CallbackEngine::get_nth_return_value(uint32_t n) const
        {
            // note: indexing of `n` begins from 0.

            uint32_t n_of_return_values = this->get_n_of_return_values();

            if (n_of_return_values <= n)
            {
                return nullptr;
            }

            return this->return_values.at(n_of_return_values - 1);
        }

        std::shared_ptr<datatypes::AnyValue> CallbackEngine::get_previous_return_value() const
        {
            uint32_t n_of_return_values = this->get_n_of_return_values();

            if (n_of_return_values == 0)
            {
                return nullptr;
            }

            return this->return_values.at(this->return_values.size() - 1);
        }
    }
}
