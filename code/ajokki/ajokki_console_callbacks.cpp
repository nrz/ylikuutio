#include "ajokki_console_callbacks.hpp"
#include "code/ylikuutio/console/console.hpp"
#include "code/ylikuutio/callback_system/callback_magic_numbers.hpp"
#include "code/ylikuutio/common/any_value.hpp"

// Include standard headers
#include <memory>   // std::make_shared, std::shared_ptr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli
{
    namespace console
    {
        class Console;
    }

    namespace ontology
    {
        class Entity;
    }
}

namespace ajokki
{
    std::shared_ptr<yli::datatypes::AnyValue> version(
            yli::console::Console* console,
            yli::ontology::Entity*,
            std::vector<std::string>& command_parameters)
    {
        console->print_text("Ajokki 0.0.3 / Ylikuutio 0.0.3");
        return nullptr;
    }

    std::shared_ptr<yli::datatypes::AnyValue> quit(
            yli::console::Console*,
            yli::ontology::Entity*,
            std::vector<std::string>& command_parameters)
    {
        uint32_t exit_program_magic_number = EXIT_PROGRAM_MAGIC_NUMBER;
        return std::make_shared<yli::datatypes::AnyValue>(exit_program_magic_number);
    }

    std::shared_ptr<yli::datatypes::AnyValue> help(
            yli::console::Console* console,
            yli::ontology::Entity*,
            std::vector<std::string>& command_parameters)
    {
        console->print_help();
        return nullptr;
    }
}
