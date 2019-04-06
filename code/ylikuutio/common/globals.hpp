#ifndef __GLOBALS_HPP_INCLUDED
#define __GLOBALS_HPP_INCLUDED

#include "any_value.hpp"

// GCC (at least g++ 4.7.2) and Visual Studio 2015 do support
// setting default values of a struct using C++11 syntax.
// Clang 3.7.0 and Visual Studio 2013 do not support
// setting default values of a struct using C++11 syntax.
// Visual Studio 2013 fails to compile, whereas Clang-compiled
// executable with code with setting default values of a struct
// causes Segmentation fault upon execution of the program.
// Compilers that don't support setting default values of a struct
// are handled by setting the default values in a macro.
// http://stackoverflow.com/questions/16782103/initializing-default-values-in-a-struct/16783513#16783513
#ifdef __clang__
#elif defined(__GNUC__)
#define __STRUCT_DEFAULT_VALUES_ARE_ACCEPTED
#elif defined(_WIN32)
#if (_MSC_VER >= 1900)
#define __STRUCT_DEFAULT_VALUES_ARE_ACCEPTED
#endif
#endif

// Include standard headers
#include <memory>   // std::make_shared, std::shared_ptr
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace yli
{
    namespace callback_system
    {
        class CallbackEngine;
        class CallbackObject;
        class CallbackParameter;
    }

    namespace console
    {
        class Console;
    }
}

typedef std::shared_ptr<yli::datatypes::AnyValue> (*InputParametersToAnyValueCallback) (
        yli::callback_system::CallbackEngine*,
        yli::callback_system::CallbackObject*,
        std::vector<yli::callback_system::CallbackParameter*>&);

typedef std::shared_ptr<yli::datatypes::AnyValue> (*InputParametersToAnyValueCallbackWithConsole) (
        yli::callback_system::CallbackEngine*,
        yli::callback_system::CallbackObject*,
        std::vector<yli::callback_system::CallbackParameter*>&,
        yli::console::Console*);

typedef std::shared_ptr<yli::datatypes::AnyValue> (*GetContentCallback) (
        yli::callback_system::CallbackEngine*,
        yli::callback_system::CallbackObject*,
        std::vector<yli::callback_system::CallbackParameter*>&,
        uint32_t x_start,
        uint32_t y_start,
        uint32_t z_start,
        uint32_t x_size,
        uint32_t y_size,
        uint32_t z_size);

#endif
