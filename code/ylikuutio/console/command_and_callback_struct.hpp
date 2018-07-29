#ifndef __COMMAND_AND_CALLBACK_STRUCT_HPP_INCLUDED
#define __COMMAND_AND_CALLBACK_STRUCT_HPP_INCLUDED

// Include standard headers
#include <string>   // std::string

namespace yli
{
    namespace callback_system
    {
        class CallbackEngine;
    }
}

typedef struct
{
    std::string command;
    yli::callback_system::CallbackEngine* callback_engine;
} CommandAndCallbackStruct;

#endif
