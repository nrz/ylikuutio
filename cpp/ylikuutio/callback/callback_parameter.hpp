#ifndef __CALLBACK_PARAMETER_HPP_INCLUDED
#define __CALLBACK_PARAMETER_HPP_INCLUDED

#include "cpp/ylikuutio/common/any_value.hpp"
#include "callback_object.hpp"

// Include standard headers
#include <string>        // std::string

namespace model
{
    class World;
}

namespace callback_system
{
    class CallbackParameter;
}

namespace callback_system
{
    class CallbackParameter
    {
        public:

            // constructor.
            CallbackParameter(std::string name, AnyValue any_value, bool is_reference, callback_system::CallbackObject* callback_object);

            // destructor.
            ~CallbackParameter();

            friend class CallbackObject;

        private:
            void bind_to_parent();

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
