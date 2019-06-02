// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2019 Antti Nuortimo.
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

#ifndef __CALLBACK_PARAMETER_HPP_INCLUDED
#define __CALLBACK_PARAMETER_HPP_INCLUDED

#include "callback_object.hpp"
#include "code/ylikuutio/common/any_value.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef>       // std::size_t
#include <memory>        // std::make_shared, std::shared_ptr
#include <string>        // std::string

namespace yli
{
    namespace ontology
    {
        class Universe;
    }

    namespace callback_system
    {
        class CallbackParameter
        {
            public:

                // constructor.
                CallbackParameter(const std::string& name, std::shared_ptr<yli::datatypes::AnyValue> any_value, const bool is_reference, yli::callback_system::CallbackObject* const parent);

                // destructor.
                ~CallbackParameter();

                // getter.
                std::shared_ptr<yli::datatypes::AnyValue> get_any_value() const;

                friend class CallbackObject;

                std::size_t childID;            // callback parameter ID, returned by `yli::callback_system::CallbackObject->get_callback_parameterID()`.

            private:
                void bind_to_parent();

                yli::callback_system::CallbackObject* parent; // pointer to the callback object.

                std::string name;
                std::shared_ptr<yli::datatypes::AnyValue> any_value; // this is `private` to make sure that someone does not overwrite it.
                bool is_reference;              // if true, the value is read from the hashmap. if false, then the value is read from the union.
        };
    }
}

#endif
