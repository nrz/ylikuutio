#ifndef __AJOKKI_CONSOLE_CALLBACKS_HPP_INCLUDED
#define __AJOKKI_CONSOLE_CALLBACKS_HPP_INCLUDED

#include "code/ylikuutio/common/globals.hpp"

namespace ajokki
{
    datatypes::AnyValue* version(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>& input_parameters,
            console::Console*,
            std::vector<std::string>& command_parameters);

    datatypes::AnyValue* quit(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>& input_parameters,
            console::Console*,
            std::vector<std::string>& command_parameters);
}

#endif
