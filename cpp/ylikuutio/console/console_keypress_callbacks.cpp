#include "console.hpp"
#include "cpp/ylikuutio/callback_system/callback_parameter.hpp"
#include "cpp/ylikuutio/callback_system/callback_object.hpp"
#include "cpp/ylikuutio/callback_system/callback_engine.hpp"
#include "cpp/ylikuutio/callback_system/callback_magic_numbers.hpp"
#include "cpp/ylikuutio/common/any_value.hpp"

// Include standard headers
#include <vector>   // std::vector

namespace console
{
    datatypes::AnyValue* exit_console(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>)
    {
        datatypes::AnyValue* any_value_console_pointer = callback_object->get_any_value("console_pointer");

        if (any_value_console_pointer == nullptr)
        {
            return nullptr;
        }

        if (any_value_console_pointer->type != datatypes::CONSOLE_POINTER)
        {
            return nullptr;
        }

        console::Console* console_pointer = any_value_console_pointer->console_pointer;
        console_pointer->exit_console();

        // Signal to caller that we have exited the console.
        uint32_t exit_console_magic_number = EXIT_CONSOLE_MAGIC_NUMBER;
        datatypes::AnyValue* any_value_magic_number = new datatypes::AnyValue(exit_console_magic_number);
        return any_value_magic_number;
    }

    datatypes::AnyValue* add_character(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>)
    {
        datatypes::AnyValue* any_value_console_pointer = callback_object->get_any_value("console_pointer");
        datatypes::AnyValue* any_value_character = callback_object->get_any_value("character");

        if (any_value_console_pointer == nullptr || any_value_character == nullptr)
        {
            return nullptr;
        }

        if (any_value_console_pointer->type != datatypes::CONSOLE_POINTER)
        {
            return nullptr;
        }

        if (any_value_character->type != datatypes::CHAR)
        {
            return nullptr;
        }

        console::Console* console = any_value_console_pointer->console_pointer;
        char character = any_value_character->char_value;
        console->add_character(character);
        return nullptr;
    }

    datatypes::AnyValue* backspace(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>)
    {
        datatypes::AnyValue* any_value_console_pointer = callback_object->get_any_value("console_pointer");

        if (any_value_console_pointer == nullptr)
        {
            return nullptr;
        }

        if (any_value_console_pointer->type != datatypes::CONSOLE_POINTER)
        {
            return nullptr;
        }

        console::Console* console = any_value_console_pointer->console_pointer;
        console->backspace();
        return nullptr;
    }
}
