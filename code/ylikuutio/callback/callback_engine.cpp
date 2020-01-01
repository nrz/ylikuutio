// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "callback_engine.hpp"
#include "callback_object.hpp"
#include "input_parameters_and_any_value_to_any_value_callback_with_universe.hpp"
#include "code/ylikuutio/common/any_value.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <memory>   // std::make_shared, std::shared_ptr
#include <queue>    // std::queue
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli
{
    namespace ontology
    {
        class Universe;
    }

    namespace callback
    {
        void CallbackEngine::bind_CallbackObject(yli::callback::CallbackObject* const callback_object)
        {
            yli::hierarchy::bind_child_to_parent<yli::callback::CallbackObject*>(
                    callback_object,
                    this->callback_object_pointer_vector,
                    this->free_callback_objectID_queue,
                    this->number_of_callback_objects);
        }

        CallbackEngine::CallbackEngine()
        {
            // constructor.
            this->universe = nullptr;
            this->number_of_callback_objects = 0;
        }

        CallbackEngine::CallbackEngine(yli::ontology::Universe* const universe)
        {
            // constructor.
            this->universe = universe;
            this->number_of_callback_objects = 0;
        }

        CallbackEngine::~CallbackEngine()
        {
            // destructor.
            std::cout << "This callback engine will be destroyed.\n";

            // destroy all callback objects of this callback engine.
            std::cout << "All callback objects of this callback engine will be destroyed.\n";
            yli::hierarchy::delete_children<yli::callback::CallbackObject*>(this->callback_object_pointer_vector, this->number_of_callback_objects);
        }

        yli::callback::CallbackObject* CallbackEngine::create_CallbackObject()
        {
            return new yli::callback::CallbackObject(this);
        }

        yli::callback::CallbackObject* CallbackEngine::create_CallbackObject(const InputParametersAndAnyValueToAnyValueCallbackWithUniverse callback)
        {
            return new yli::callback::CallbackObject(callback, this);
        }

        void CallbackEngine::set_callback_object_pointer(const std::size_t childID, yli::callback::CallbackObject* const child_pointer)
        {
            yli::hierarchy::set_child_pointer(childID, child_pointer, this->callback_object_pointer_vector, this->free_callback_objectID_queue, this->number_of_callback_objects);
        }

        std::shared_ptr<yli::common::AnyValue> CallbackEngine::execute(std::shared_ptr<yli::common::AnyValue> any_value)
        {
            std::shared_ptr<yli::common::AnyValue> return_any_value = nullptr;

            // execute all callbacks.
            for (std::size_t child_i = 0; child_i < this->callback_object_pointer_vector.size(); child_i++)
            {
                yli::callback::CallbackObject* callback_object_pointer = static_cast<yli::callback::CallbackObject*>(this->callback_object_pointer_vector[child_i]);

                if (callback_object_pointer != nullptr)
                {
                    return_any_value = callback_object_pointer->execute(any_value);
                    this->return_values.push_back(return_any_value);
                }
                else
                {
                    this->return_values.push_back(nullptr);
                }
            }

            this->return_values.clear();
            return std::shared_ptr<yli::common::AnyValue>(return_any_value);
        }

        std::size_t CallbackEngine::get_n_of_return_values() const
        {
            return this->return_values.size();
        }

        std::shared_ptr<yli::common::AnyValue> CallbackEngine::get_nth_return_value(std::size_t n) const
        {
            // note: indexing of `n` begins from 0.

            std::size_t n_of_return_values = this->get_n_of_return_values();

            if (n_of_return_values <= n)
            {
                return nullptr;
            }

            return this->return_values.at(n_of_return_values - 1);
        }

        std::shared_ptr<yli::common::AnyValue> CallbackEngine::get_previous_return_value() const
        {
            std::size_t n_of_return_values = this->get_n_of_return_values();

            if (n_of_return_values == 0)
            {
                return nullptr;
            }

            return this->return_values.at(this->return_values.size() - 1);
        }
    }
}
