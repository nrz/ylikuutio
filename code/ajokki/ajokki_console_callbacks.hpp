#ifndef __AJOKKI_CONSOLE_CALLBACKS_HPP_INCLUDED
#define __AJOKKI_CONSOLE_CALLBACKS_HPP_INCLUDED

#include "code/ylikuutio/console/command_and_callback_struct.hpp"
#include "code/ylikuutio/common/globals.hpp"

// Include standard headers
#include <memory>   // std::make_shared, std::shared_ptr
#include <string>   // std::string
#include <vector>   // std::vector

namespace ajokki
{
    std::shared_ptr<datatypes::AnyValue> version(
            console::Console* console,
            ontology::Universe*,
            std::vector<std::string>& command_parameters);

    std::shared_ptr<datatypes::AnyValue> quit(
            console::Console*,
            ontology::Universe*,
            std::vector<std::string>& command_parameters);

    std::shared_ptr<datatypes::AnyValue> help(
            console::Console*,
            ontology::Universe*,
            std::vector<std::string>& command_parameters);
}

#endif
