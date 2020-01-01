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

#ifndef __CALLBACK_ENGINE_HPP_INCLUDED
#define __CALLBACK_ENGINE_HPP_INCLUDED

#include "input_parameters_and_any_value_to_any_value_callback_with_universe.hpp"
#include "code/ylikuutio/common/any_value.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef>       // std::size_t
#include <memory>        // std::make_shared, std::shared_ptr
#include <queue>         // std::queue
#include <string>        // std::string
#include <vector>        // std::vector

namespace yli
{
    namespace ontology
    {
        class Universe;
    }

    namespace callback
    {
        class CallbackObject;

        class CallbackEngine
        {
            // `CallbackEngine` is an object that contains some callbacks and hashmaps that are used for input and output parameters.
            // `CallbackEngine` provides a way to create callback chains.
            //
            // Hierarchy of callbacks:
            //
            //     CallbackEngine
            //           ^
            //     CallbackObject
            //           ^
            //   CallbackParameter
            //
            // How to use.
            // 1. Create a new `CallbackEngine`. No callbacks have been
            //    defined yet. Calling `CallbackEngine.execute(nullptr)` at this
            //    point will simply go through an empty vector and
            //    practically won't do anything interesting.
            // 2. Create a new `CallbackObject`, give pointer to the
            //    recently created `CallbackEngine` as input parameter.
            // 3. If the callback has parameter[s], create a new
            //    `CallbackParameter` for each parameter, give `CallbackObject`
            //    as input parameter for the `CallbackParameter` constructor.

            public:
                void bind_CallbackObject(yli::callback::CallbackObject* const callback_object);

                // constructor.
                CallbackEngine();

                // constructor.
                CallbackEngine(yli::ontology::Universe* const universe);

                // destructor.
                ~CallbackEngine();

                yli::callback::CallbackObject* create_CallbackObject();
                yli::callback::CallbackObject* create_CallbackObject(const InputParametersAndAnyValueToAnyValueCallbackWithUniverse callback);

                // execute all callbacks with a parameter.
                std::shared_ptr<yli::common::AnyValue> execute(std::shared_ptr<yli::common::AnyValue> any_value);

                std::size_t get_n_of_return_values() const;
                std::shared_ptr<yli::common::AnyValue> get_nth_return_value(std::size_t n) const;
                std::shared_ptr<yli::common::AnyValue> get_previous_return_value() const;

                friend class CallbackObject;

            private:
                // `CallbackEngine` is not an `Entity`.
                // Therefore they are not descendants of the `Universe`.
                // Some `CallbackEngine`s just have a pointer to the `Universe`.
                yli::ontology::Universe* universe;

                // this method sets a callback object pointer.
                void set_callback_object_pointer(const std::size_t childID, yli::callback::CallbackObject* const child_pointer);

                std::vector<yli::callback::CallbackObject*> callback_object_pointer_vector;
                std::queue<std::size_t> free_callback_objectID_queue;
                std::size_t number_of_callback_objects;

                std::vector<std::shared_ptr<yli::common::AnyValue>> return_values;
        };
    }
}

#endif
