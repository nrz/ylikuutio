#ifndef __AJOKKI_CLEANUP_CALLBACKS_HPP_INCLUDED
#define __AJOKKI_CLEANUP_CALLBACKS_HPP_INCLUDED

#include "code/ylikuutio/callback_system/callback_parameter.hpp"
#include "code/ylikuutio/callback_system/callback_object.hpp"
#include "code/ylikuutio/callback_system/callback_engine.hpp"
#include "code/ylikuutio/callback_system/callback_magic_numbers.hpp"
#include "code/ylikuutio/common/any_value.hpp"

// Include standard headers
#include <memory>   // std::make_shared, std::shared_ptr
#include <vector>   // std::vector

namespace ajokki
{
    std::shared_ptr<datatypes::AnyValue> glfwTerminate_cleanup(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>& input_parameters);

    std::shared_ptr<datatypes::AnyValue> full_cleanup(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>&);
}

#endif
