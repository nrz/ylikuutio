#ifndef __AJOKKI_CONSOLE_CALLBACKS_HPP_INCLUDED
#define __AJOKKI_CONSOLE_CALLBACKS_HPP_INCLUDED

// Include standard headers
#include <memory>   // std::make_shared, std::shared_ptr
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli
{
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
        class Entity;
    }
}

namespace ajokki
{
    std::shared_ptr<yli::datatypes::AnyValue> version(
            yli::console::Console* const console,
            yli::ontology::Entity* const,
            const std::vector<std::string>& command_parameters);

    std::shared_ptr<yli::datatypes::AnyValue> quit(
            yli::console::Console* const,
            yli::ontology::Entity* const,
            const std::vector<std::string>& command_parameters);

    std::shared_ptr<yli::datatypes::AnyValue> help(
            yli::console::Console* const,
            yli::ontology::Entity* const,
            const std::vector<std::string>& command_parameters);
}

#endif
