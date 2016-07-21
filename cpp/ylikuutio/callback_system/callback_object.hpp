#ifndef __CALLBACK_OBJECT_HPP_INCLUDED
#define __CALLBACK_OBJECT_HPP_INCLUDED

#include "callback_engine.hpp"
#include "cpp/ylikuutio/common/any_value.hpp"
#include "cpp/ylikuutio/common/globals.hpp"
#include "cpp/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <queue>         // std::queue
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

namespace callback_system
{
    class CallbackParameter;

    class CallbackObject
    {
        // CallbackObject is an object that contains a single callback.

        public:
            // constructor.
            CallbackObject(callback_system::CallbackEngine* parent_pointer);

            // constructor.
            CallbackObject(InputParametersToAnyValueCallback callback, callback_system::CallbackEngine* parent_pointer);

            // destructor.
            ~CallbackObject();

            // this method changes the callback without changing the parameters of CallbackObject.
            void set_new_callback(InputParametersToAnyValueCallback callback);

            // getter function for callbacks and callback objects.
            datatypes::AnyValue* get_any_value(std::string name);

            // setter function for callbacks and callback objects.
            void set_any_value(std::string name, datatypes::AnyValue* any_value);

            friend class CallbackEngine;
            friend class CallbackParameter;
            template<class T1>
                friend void hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1> &child_pointer_vector, std::queue<uint32_t> &free_childID_queue);
            template<class T1, class T2>
                friend void hierarchy::bind_child_to_new_parent(T1 child_pointer, T2 new_parent_pointer, std::vector<T1> &old_child_pointer_vector, std::queue<uint32_t> &old_free_childID_queue);

        private:
            void bind_to_parent();

            uint32_t get_childID();

            // this method sets a callback parameter pointer.
            void set_callback_parameter_pointer(uint32_t childID, callback_system::CallbackParameter* child_pointer);

            void bind_child_to_parent(callback_system::CallbackParameter* child_pointer);

            // execute this callback.
            datatypes::AnyValue* execute();

            uint32_t get_callback_parameterID(std::vector<callback_system::CallbackParameter*> &child_pointer_vector, std::queue<uint32_t> &free_childID_queue);

            callback_system::CallbackEngine* parent_pointer; // pointer to the callback engine.

            uint32_t childID;                     // callback object ID, returned by `callback_system::CallbackEngine->get_callback_objectID()`.

            std::vector<callback_system::CallbackParameter*> callback_parameter_pointer_vector;
            std::queue<uint32_t> free_callback_parameterID_queue;

            InputParametersToAnyValueCallback callback;

            // A hash map used to store variables.
            std::unordered_map<std::string, datatypes::AnyValue> anyvalue_hashmap;
    };
}

#endif
