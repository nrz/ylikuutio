#ifndef __CALLBACK_OBJECT_HPP_INCLUDED
#define __CALLBACK_OBJECT_HPP_INCLUDED

#include "callback_engine.hpp"
#include "code/ylikuutio/common/any_value.hpp"
#include "code/ylikuutio/common/globals.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef>       // std::size_t
#include <memory>        // std::make_shared, std::shared_ptr
#include <queue>         // std::queue
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

namespace yli
{
    namespace callback_system
    {
        class CallbackParameter;

        class CallbackObject
        {
            // CallbackObject is an object that contains a single callback.

            public:
                void bind_callback_parameter(yli::callback_system::CallbackParameter* const callback_parameter);
                void unbind_callback_parameter(const std::size_t childID);

                // constructor.
                CallbackObject(yli::callback_system::CallbackEngine* parent);

                // constructor.
                CallbackObject(const InputParametersToAnyValueCallback callback, yli::callback_system::CallbackEngine* parent);

                // destructor.
                virtual ~CallbackObject();

                // this method changes the callback without changing the parameters of CallbackObject.
                void set_new_callback(const InputParametersToAnyValueCallback callback);

                // getter functions for callbacks and callback objects.
                std::shared_ptr<yli::datatypes::AnyValue> get_any_value(const std::string& name) const;
                std::shared_ptr<yli::datatypes::AnyValue> get_arg(const std::size_t arg_i) const;

                // setter function for callbacks and callback objects.
                void set_any_value(const std::string& name, std::shared_ptr<yli::datatypes::AnyValue> any_value);

                friend class CallbackEngine;
                friend class CallbackParameter;
                template<class T1>
                    friend void yli::hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue, std::size_t& number_of_children);

            protected:
                void bind_to_parent();

                // this method sets a callback parameter pointer.
                void set_callback_parameter_pointer(const std::size_t childID, yli::callback_system::CallbackParameter* const child_pointer);

                void bind_child_to_parent(yli::callback_system::CallbackParameter* child_pointer);

                // execute this callback.
                virtual std::shared_ptr<yli::datatypes::AnyValue> execute();

                yli::callback_system::CallbackEngine* parent; // pointer to the callback engine.

                std::size_t childID;                          // callback object ID, returned by `yli::callback_system::CallbackEngine->get_callback_objectID()`.

                std::vector<yli::callback_system::CallbackParameter*> callback_parameter_pointer_vector;
                std::queue<std::size_t> free_callback_parameterID_queue;
                std::size_t number_of_callback_parameters;

                InputParametersToAnyValueCallback callback;

                // A hash map used to store variables.
                std::unordered_map<std::string, yli::datatypes::AnyValue> anyvalue_hashmap;
        };
    }
}

#endif
