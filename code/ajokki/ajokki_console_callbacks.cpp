#include "ajokki_console_callbacks.hpp"
#include "code/ylikuutio/console/command_and_callback_struct.hpp"
#include "code/ylikuutio/callback_system/callback_magic_numbers.hpp"
#include "code/ylikuutio/common/globals.hpp"

// Include standard headers
#include <string>   // std::string
#include <vector>   // std::vector

namespace ajokki
{
    datatypes::AnyValue* version(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>& input_parameters,
            console::Console*,
            std::vector<std::string>& command_parameters)
    {
        return nullptr;
    }

    datatypes::AnyValue* quit(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>& input_parameters,
            console::Console*,
            std::vector<std::string>& command_parameters)
    {
        return new datatypes::AnyValue(EXIT_PROGRAM_MAGIC_NUMBER);
    }
}
