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

#include "callback_object.hpp"
#include "callback_parameter.hpp"
#include "input_parameters_and_any_value_to_any_value_callback_with_universe.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <memory>   // std::make_shared, std::shared_ptr
#include <string>   // std::string
#include <unordered_map> // std::unordered_map
#include <vector>   // std::vector

namespace yli::callback
{
    void CallbackObject::bind_callback_parameter(yli::callback::CallbackParameter* const callback_parameter)
    {
        // get `childID` from `CallbackObject` and set pointer to `callback_parameter`.
        yli::hierarchy::bind_child_to_parent<yli::callback::CallbackParameter*>(
                callback_parameter,
                this->callback_parameter_pointer_vector,
                this->free_callback_parameterID_queue,
                this->number_of_callback_parameters);

        if (!callback_parameter->name.empty())
        {
            // This parameter is a named variable, so store it in `anyvalue_hashmap`.
            this->set_any_value(callback_parameter->name, std::make_shared<yli::data::AnyValue>(*callback_parameter->any_value));
        }
    }

    void CallbackObject::unbind_callback_parameter(const std::size_t childID)
    {
        yli::hierarchy::unbind_child_from_parent(
                childID,
                this->callback_parameter_pointer_vector,
                this->free_callback_parameterID_queue,
                this->number_of_callback_parameters);
    }

    yli::callback::CallbackParameter* CallbackObject::create_callback_parameter(
            const std::string& name,
            std::shared_ptr<yli::data::AnyValue> any_value,
            const bool is_reference)
    {
        return new yli::callback::CallbackParameter(name, any_value, is_reference, this);
    }

    // getter function for callbacks and callback objects.
    std::shared_ptr<yli::data::AnyValue> CallbackObject::get_any_value(const std::string& name) const
    {
        if (this->anyvalue_hashmap.count(name) != 1)
        {
            return nullptr;
        }

        return std::make_shared<yli::data::AnyValue>(this->anyvalue_hashmap.at(name));
    }

    std::shared_ptr<yli::data::AnyValue> CallbackObject::get_arg(const std::size_t arg_i) const
    {
        if (arg_i >= this->callback_parameter_pointer_vector.size())
        {
            std::cerr << "error #1 in CallbackObject code.\n";
            return nullptr;
        }

        yli::callback::CallbackParameter* callback_parameter = this->callback_parameter_pointer_vector.at(arg_i);

        if (callback_parameter == nullptr)
        {
            std::cerr << "error #2 in CallbackObject code.\n";
            return nullptr;
        }

        return std::make_shared<yli::data::AnyValue>(*callback_parameter->any_value);
    }

    // setter function for callbacks and callback objects.
    void CallbackObject::set_any_value(const std::string& name, std::shared_ptr<yli::data::AnyValue> any_value)
    {
        this->anyvalue_hashmap[name] = yli::data::AnyValue(*any_value);
    }

    void CallbackObject::bind_to_parent()
    {
        // requirements:
        // `this->parent` must not be `nullptr`.

        yli::callback::CallbackEngine* const callback_engine = this->parent;

        if (callback_engine == nullptr)
        {
            std::cerr << "ERROR: `CallbackObject::bind_to_parent`: `callback_engine` is `nullptr`!\n";
            return;
        }

        callback_engine->bind_callback_object(this);
    }

    void CallbackObject::set_new_callback(const InputParametersAndAnyValueToAnyValueCallbackWithUniverse callback)
    {
        this->callback = callback;
    }

    CallbackObject::CallbackObject(yli::callback::CallbackEngine* const parent)
    {
        // constructor.
        this->childID = -1;
        this->callback = nullptr;
        this->parent = parent;

        this->number_of_callback_parameters = 0;

        // get `childID` from the `CallbackEngine` and set pointer to this `CallbackObject`.
        this->bind_to_parent();
    }

    CallbackObject::CallbackObject(const InputParametersAndAnyValueToAnyValueCallbackWithUniverse callback, yli::callback::CallbackEngine* const parent)
    {
        // constructor.
        this->childID = -1;
        this->callback = callback;
        this->parent = parent;

        this->number_of_callback_parameters = 0;

        // get `childID` from the `CallbackEngine` and set pointer to this `CallbackObject`.
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

    void CallbackObject::set_callback_parameter_pointer(const std::size_t childID, yli::callback::CallbackParameter* const child_pointer)
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

    std::shared_ptr<yli::data::AnyValue> CallbackObject::execute(std::shared_ptr<yli::data::AnyValue> any_value)
    {
        if (this->parent != nullptr && this->callback != nullptr)
        {
            return this->callback(this->parent->get_universe(), this->parent, this, this->callback_parameter_pointer_vector, any_value);
        }
        return nullptr;
    }
}
