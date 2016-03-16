#ifndef __CALLBACK_PARAMETER_HPP_INCLUDED
#define __CALLBACK_PARAMETER_HPP_INCLUDED

#include "cpp/ylikuutio/common/any_value.hpp"
#include "callback_object.hpp"
#include "cpp/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <string>        // std::string

namespace model
{
    class World;
}

namespace callback_system
{
    class CallbackParameter
    {
        public:

            // constructor.
            CallbackParameter(std::string name, AnyValue any_value, bool is_reference, callback_system::CallbackObject* parent_pointer);

            // destructor.
            ~CallbackParameter();

            friend class CallbackObject;
            template<class T1>
                friend void hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<void*> &child_pointer_vector, std::queue<uint32_t> &free_childID_queue);
            template<class T1, class T2>
                friend void hierarchy::bind_child_to_new_parent(T1 child_pointer, T2 new_parent_pointer, std::vector<void*> &old_child_pointer_vector, std::queue<uint32_t> &old_free_childID_queue);

        private:
            void bind_to_parent();

            uint32_t childID;                      // callback parameter ID, returned by `callback_system::CallbackObject->get_callback_parameterID()`.

            callback_system::CallbackObject* parent_pointer; // pointer to the callback object.

            std::string name;
            AnyValue any_value;
            bool is_reference; // if true, the value is read from the hashmap. if false, then the value is read from the union.
    };

    class BoolCallbackParameter : CallbackParameter
    {
        public:

            // constructor.
            BoolCallbackParameter();
    };
}

#endif
