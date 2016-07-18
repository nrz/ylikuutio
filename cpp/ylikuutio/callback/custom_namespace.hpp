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
            bool get_bool(std::string name);
            float get_float(std::string name);
            double get_double(std::string name);
            int32_t get_int32_t(std::string name);
            uint32_t get_uint32_t(std::string name);
            void* get_void_pointer(std::string name);

            // setter functions for callbacks and callback objects.
            void set_bool(std::string name, bool value);
            void set_float(std::string name, float value);
            void set_double(std::string name, double value);
            void set_int32_t(std::string name, int32_t value);
            void set_uint32_t(std::string name, uint32_t value);
            void set_void_pointer(std::string name, void* value);

            // A hash map used to store variables.
            std::unordered_map<std::string, datatypes::AnyValue> anyvalue_hashmap;
    };
}
#endif
