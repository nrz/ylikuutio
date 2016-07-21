#ifndef __CALLBACK_PARAMETER_HPP_INCLUDED
#define __CALLBACK_PARAMETER_HPP_INCLUDED

#include "cpp/ylikuutio/common/any_value.hpp"
#include "callback_object.hpp"
#include "cpp/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <string>        // std::string

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
            CallbackParameter(std::string name, datatypes::AnyValue* any_value, bool is_reference, callback_system::CallbackObject* parent_pointer);

            // destructor.
            ~CallbackParameter();

            // getter.
            datatypes::AnyValue* get_any_value();

            friend class CallbackObject;

        private:
            void bind_to_parent();

            uint32_t childID;               // callback parameter ID, returned by `callback_system::CallbackObject->get_callback_parameterID()`.

            callback_system::CallbackObject* parent_pointer; // pointer to the callback object.

            std::string name;
            datatypes::AnyValue* any_value; // this is `private` to make sure that someone does not overwrite it.
            bool is_reference;              // if true, the value is read from the hashmap. if false, then the value is read from the union.
    };
}

#endif
