#ifndef __KEY_AND_CALLBACK_STRUCT_HPP_INCLUDED
#define __KEY_AND_CALLBACK_STRUCT_HPP_INCLUDED

// Include standard headers
#include <stdint.h>      // uint32_t etc.

namespace yli
{
    namespace callback_system
    {
        class CallbackEngine;
    }
}

typedef struct
{
    uint32_t keycode;
    yli::callback_system::CallbackEngine* callback_engine;
} KeyAndCallbackStruct;

#endif
