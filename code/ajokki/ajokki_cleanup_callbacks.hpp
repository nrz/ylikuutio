#ifndef __AJOKKI_CLEANUP_CALLBACKS_HPP_INCLUDED
#define __AJOKKI_CLEANUP_CALLBACKS_HPP_INCLUDED

#include "code/ylikuutio/common/any_value.hpp"

// Include standard headers
#include <memory>   // std::make_shared, std::shared_ptr
#include <vector>   // std::vector

namespace yli
{
    namespace callback_system
    {
        class CallbackEngine;
        class CallbackObject;
        class CallbackParameter;
    }
}

namespace ajokki
{
    std::shared_ptr<yli::datatypes::AnyValue> full_cleanup(
            yli::callback_system::CallbackEngine*,
            yli::callback_system::CallbackObject* callback_object,
            std::vector<yli::callback_system::CallbackParameter*>&);
}

#endif
