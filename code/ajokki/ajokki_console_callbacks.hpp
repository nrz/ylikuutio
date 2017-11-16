#ifndef __AJOKKI_CONSOLE_CALLBACKS_HPP_INCLUDED
#define __AJOKKI_CONSOLE_CALLBACKS_HPP_INCLUDED

// Include standard headers
#include <memory>   // std::make_shared, std::shared_ptr
#include <string>   // std::string
#include <vector>   // std::vector

namespace console
{
    class Console;
}

namespace datatypes
{
    class AnyValue;
}

namespace ontology
{
    class Universe;
}

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
