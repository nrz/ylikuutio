#ifndef __CUSTOM_NAMESPACE_HPP_INCLUDED
#define __CUSTOM_NAMESPACE_HPP_INCLUDED

#include "cpp/ylikuutio/common/any_value.hpp"

// Include standard headers
#include <stdint.h>      // uint32_t etc.
#include <string>        // std::string
#include <unordered_map> // std::unordered_map

namespace callback_system
{
    class CustomNamespace
    {
        protected:
            // getter functions for callbacks and callback objects.
            datatypes::AnyValue get_any_value(std::string name);

            // setter functions for callbacks and callback objects.
            void set_any_value(std::string name, datatypes::AnyValue any_value);

            // A hash map used to store variables.
            std::unordered_map<std::string, datatypes::AnyValue> anyvalue_hashmap;
    };
}
#endif
