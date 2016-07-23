#ifndef __KEY_AND_CALLBACK_STRUCT_HPP_INCLUDED
#define __KEY_AND_CALLBACK_STRUCT_HPP_INCLUDED

typedef struct
{
    uint32_t keycode;
    callback_system::CallbackEngine* callback_engine;
} KeyAndCallbackStruct;

#endif
