// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2021 Antti Nuortimo.
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

#include "callback_parameter.hpp"
#include "callback_object.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
#include <memory>   // std::make_shared, std::shared_ptr
#include <string>   // std::string

namespace yli::callback
{
    void CallbackParameter::bind_to_parent()
    {
        // requirements:
        // `this->parent` must not be `nullptr`.
        yli::callback::CallbackObject* const callback_object = this->parent;

        if (callback_object == nullptr)
        {
            std::cerr << "ERROR: `CallbackParameter::bind_to_parent`: `callback_object` is `nullptr`!\n";
            return;
        }

        // note: `CallbackObject::bind_callback_parameter` also stores named variables in its `anyvalue_hashmap`.
        callback_object->bind_callback_parameter(this);
    }

    CallbackParameter::CallbackParameter(const std::string& name, std::shared_ptr<yli::data::AnyValue> any_value, const bool is_reference, yli::callback::CallbackObject* const parent)
        : parent     { parent },
        name         { name },
        any_value    { any_value },
        is_reference { is_reference }
    {
        // constructor.

        // get `childID` from the `CallbackObject` and set pointer to this `CallbackParameter`.
        this->bind_to_parent();
    }

    CallbackParameter::~CallbackParameter()
    {
        // destructor.
        //
        // requirements:
        // `this->parent` must not be `nullptr`.

        std::cout << "Callback parameter with childID " << this->childID << " will be destroyed.\n";

        yli::callback::CallbackObject* const callback_object = this->parent;

        if (callback_object == nullptr)
        {
            std::cerr << "ERROR: `CallbackParameter::~CallbackParameter`: `callback_object` is `nullptr`!\n";
            return;
        }

        // set pointer to this `CallbackParameter` to `nullptr`.
        callback_object->set_callback_parameter_pointer(this->childID, nullptr);
    }

    std::shared_ptr<yli::data::AnyValue> CallbackParameter::get_any_value() const
    {
        return std::make_shared<yli::data::AnyValue>(*this->any_value);
    }
}
