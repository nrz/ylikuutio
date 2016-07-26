#include "console.hpp"
#include "cpp/ylikuutio/callback_system/callback_parameter.hpp"
#include "cpp/ylikuutio/callback_system/callback_object.hpp"
#include "cpp/ylikuutio/callback_system/callback_engine.hpp"
#include "cpp/ylikuutio/callback_system/callback_magic_numbers.hpp"
#include "cpp/ylikuutio/common/any_value.hpp"

// Include GLFW
#ifndef __GLFW3_H_INCLUDED
#define __GLFW3_H_INCLUDED
#include <glfw3.h>
#endif

// Include standard headers
#include <vector>   // std::vector
#include <iostream> // std::cout, std::cin, std::cerr

namespace console
{
    // Keep these variable types as this is according to GLFW documentation!
    // So: `unsigned int codepoint`, `int mods`.
    void charmods_callback(GLFWwindow* window, unsigned int codepoint, int mods)
    {
        // `int mods` values:
        // No modificators:       0x00
        // Shift (left or right): 0x01
        // Alt (not AltGr):       0x04
        // Shift + Alt:           0x05
        std::cout << "Hello from character_callback! codepoint: 0x" << std::hex << codepoint << ", mods: 0x" << mods << "\n";

        global_console_pointer->add_character(codepoint);
    }

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

    datatypes::AnyValue* enter_key(
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
        console->enter_key();
        return nullptr;
    }
}
