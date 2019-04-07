#ifndef __GET_CONTENT_CALLBACK_HPP_INCLUDED
#define __GET_CONTENT_CALLBACK_HPP_INCLUDED

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

    namespace datatypes
    {
        class AnyValue;
    }
}

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
