#ifndef __CONSOLE_STRUCT_HPP_INCLUDED
#define __CONSOLE_STRUCT_HPP_INCLUDED

#include "console_command_callback.hpp"
#include "code/ylikuutio/callback_system/key_and_callback_struct.hpp"

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
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

namespace yli
{
    namespace ontology
    {
        class Universe;
        class Font2D;
    }
}

typedef struct ConsoleStruct
{
    ConsoleStruct()
        : current_keypress_callback_engine_vector_pointer_pointer(nullptr),
        current_keyrelease_callback_engine_vector_pointer_pointer(nullptr),
        command_callback_map_pointer(nullptr),
        universe(nullptr),
        font2D_pointer(nullptr)
    {
        // constructor.
    }
    std::vector<KeyAndCallbackStruct>** current_keypress_callback_engine_vector_pointer_pointer;
    std::vector<KeyAndCallbackStruct>** current_keyrelease_callback_engine_vector_pointer_pointer;
    std::unordered_map<std::string, ConsoleCommandCallback>* command_callback_map_pointer;
    yli::ontology::Universe* universe;
    yli::ontology::Font2D* font2D_pointer;
} ConsoleStruct;

#endif
