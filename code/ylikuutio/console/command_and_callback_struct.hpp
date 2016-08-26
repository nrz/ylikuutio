#ifndef __COMMAND_AND_CALLBACK_STRUCT_HPP_INCLUDED
#define __COMMAND_AND_CALLBACK_STRUCT_HPP_INCLUDED

typedef struct
{
    std::string command;
    callback_system::CallbackEngine* callback_engine;
} CommandAndCallbackStruct;

#endif
