// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2022 Antti Nuortimo.
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

#ifndef __YLIKUUTIO_CALLBACK_CALLBACK_OBJECT_HPP_INCLUDED
#define __YLIKUUTIO_CALLBACK_CALLBACK_OBJECT_HPP_INCLUDED

#include "callback_engine.hpp"
#include "input_parameters_and_any_value_to_any_value_callback_with_universe.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef>       // std::size_t
#include <limits>        // std::numeric_limits
#include <optional>      // std::optional
#include <queue>         // std::queue
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

namespace yli::callback
{
    class CallbackParameter;

    class CallbackObject
    {
        // CallbackObject is an object that contains a single callback.

        public:
            void bind_callback_parameter(yli::callback::CallbackParameter* const callback_parameter);
            void unbind_callback_parameter(const std::size_t childID);

            // destructor.
            virtual ~CallbackObject();

            yli::callback::CallbackParameter* create_callback_parameter(
                    const std::string& name,
                    const yli::data::AnyValue& any_value,
                    const bool is_reference);

            // this method changes the callback without changing the parameters of CallbackObject.
            void set_new_callback(const InputParametersAndAnyValueToAnyValueCallbackWithUniverse callback);

            // getter functions for callbacks and callback objects.
            std::optional<yli::data::AnyValue> get_any_value(const std::string& name) const;
            std::optional<yli::data::AnyValue> get_arg(const std::size_t arg_i) const;

            // setter function for callbacks and callback objects.
            void set_any_value(const std::string& name, const yli::data::AnyValue& any_value);

            friend class yli::callback::CallbackEngine;
            friend class yli::callback::CallbackParameter;
            template<typename T1>
                friend void yli::hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue, std::size_t& number_of_children);

        protected:
            yli::callback::CallbackEngine* parent { nullptr }; // pointer to the callback engine.

            std::vector<yli::callback::CallbackParameter*> callback_parameter_pointer_vector;
            std::queue<std::size_t> free_callback_parameterID_queue;
            std::size_t number_of_callback_parameters { 0 };

            InputParametersAndAnyValueToAnyValueCallbackWithUniverse callback { nullptr };

            // constructor.
            explicit CallbackObject(yli::callback::CallbackEngine* const parent);

            // constructor.
            CallbackObject(const InputParametersAndAnyValueToAnyValueCallbackWithUniverse callback, yli::callback::CallbackEngine* const parent);

        private:
            void bind_to_parent();

            // this method sets a callback parameter pointer.
            void set_callback_parameter_pointer(const std::size_t childID, yli::callback::CallbackParameter* const child_pointer);

            void bind_child_to_parent(yli::callback::CallbackParameter* child_pointer);

            // execute this callback with a parameter.
            virtual std::optional<yli::data::AnyValue> execute(const yli::data::AnyValue& any_value);

            std::size_t childID { std::numeric_limits<std::size_t>::max() };

            // A hash map used to store variables.
            std::unordered_map<std::string, yli::data::AnyValue> anyvalue_hashmap;
    };
}

#endif
