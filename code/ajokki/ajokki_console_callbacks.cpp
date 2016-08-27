#include "ajokki_console_callbacks.hpp"
#include "code/ylikuutio/console/command_and_callback_struct.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
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
            ontology::Universe*,
            std::vector<std::string>& command_parameters)
    {
        return nullptr;
    }

    datatypes::AnyValue* quit(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>& input_parameters,
            console::Console*,
            ontology::Universe*,
            std::vector<std::string>& command_parameters)
    {
        return new datatypes::AnyValue(EXIT_PROGRAM_MAGIC_NUMBER);
    }

    datatypes::AnyValue* red(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>& input_parameters,
            console::Console*,
            ontology::Universe* universe,
            std::vector<std::string>& command_parameters)
    {
        universe->set_background_color(1.0f, 0.0f, 0.0f, 0.0f);
        return nullptr;
    }

    datatypes::AnyValue* green(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>& input_parameters,
            console::Console*,
            ontology::Universe* universe,
            std::vector<std::string>& command_parameters)
    {
        universe->set_background_color(0.0f, 1.0f, 0.0f, 0.0f);
        return nullptr;
    }

    datatypes::AnyValue* blue(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>& input_parameters,
            console::Console*,
            ontology::Universe* universe,
            std::vector<std::string>& command_parameters)
    {
        universe->set_background_color(0.0f, 0.0f, 1.0f, 0.0f);
        return nullptr;
    }
}
