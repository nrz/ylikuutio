#ifndef __COMMAND_AND_CALLBACK_STRUCT_HPP_INCLUDED
#define __COMMAND_AND_CALLBACK_STRUCT_HPP_INCLUDED

#include "code/ylikuutio/callback_system/callback_engine.hpp"

// Include standard headers
#include <string>   // std::string

typedef struct
{
    std::string command;
    yli::callback_system::CallbackEngine* callback_engine;
} CommandAndCallbackStruct;

#endif
