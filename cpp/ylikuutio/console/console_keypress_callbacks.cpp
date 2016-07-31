#include "console.hpp"
#include "cpp/ylikuutio/callback_system/callback_parameter.hpp"
#include "cpp/ylikuutio/callback_system/callback_object.hpp"
#include "cpp/ylikuutio/callback_system/callback_engine.hpp"
#include "cpp/ylikuutio/callback_system/callback_magic_numbers.hpp"
#include "cpp/ylikuutio/common/any_value.hpp"
#include "cpp/ylikuutio/common/global_variables.hpp"

// Include GLFW
#ifndef __GLFW3_H_INCLUDED
#define __GLFW3_H_INCLUDED
#include <glfw3.h>
#endif

// Include standard headers
#include <vector>   // std::vector

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
        global_console_pointer->add_character(static_cast<char>(codepoint), static_cast<uint32_t>(mods));
    }

    datatypes::AnyValue* enable_enter_console(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>)
    {
        // FIXME: This is a keyrelease callback function with a named parameter (a hash map lookup).
        // It is more efficient to get the input parameters using their index instead of their variable name.

        datatypes::AnyValue* any_value_console = callback_object->get_any_value("console_pointer");

        if (any_value_console->type != datatypes::CONSOLE_POINTER)
        {
            return nullptr;
        }

        console::Console* console = any_value_console->console_pointer;
        console->enable_enter_console();
        return nullptr;
    }

    datatypes::AnyValue* enable_exit_console(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>)
    {
        datatypes::AnyValue* any_value_console = callback_object->get_any_value("console_pointer");

        if (any_value_console->type != datatypes::CONSOLE_POINTER)
        {
            return nullptr;
        }

        console::Console* console = any_value_console->console_pointer;
        console->enable_exit_console();
        return nullptr;
    }

    datatypes::AnyValue* enable_move_to_previous_input(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>)
    {
        datatypes::AnyValue* any_value_console = callback_object->get_any_value("console_pointer");

        if (any_value_console->type != datatypes::CONSOLE_POINTER)
        {
            return nullptr;
        }

        console::Console* console = any_value_console->console_pointer;
        console->enable_move_to_previous_input();
        return nullptr;
    }

    datatypes::AnyValue* enable_move_to_next_input(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>)
    {
        datatypes::AnyValue* any_value_console = callback_object->get_any_value("console_pointer");

        if (any_value_console->type != datatypes::CONSOLE_POINTER)
        {
            return nullptr;
        }

        console::Console* console = any_value_console->console_pointer;
        console->enable_move_to_next_input();
        return nullptr;
    }

    datatypes::AnyValue* enable_backspace(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>)
    {
        datatypes::AnyValue* any_value_console = callback_object->get_any_value("console_pointer");

        if (any_value_console->type != datatypes::CONSOLE_POINTER)
        {
            return nullptr;
        }

        console::Console* console = any_value_console->console_pointer;
        console->enable_backspace();
        return nullptr;
    }

    datatypes::AnyValue* enable_enter_key(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>)
    {
        datatypes::AnyValue* any_value_console = callback_object->get_any_value("console_pointer");

        if (any_value_console->type != datatypes::CONSOLE_POINTER)
        {
            return nullptr;
        }

        console::Console* console = any_value_console->console_pointer;
        console->enable_enter_key();
        return nullptr;
    }

    datatypes::AnyValue* enter_console(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>)
    {
        datatypes::AnyValue* any_value_console = callback_object->get_any_value("console_pointer");

        if (any_value_console->type != datatypes::CONSOLE_POINTER)
        {
            return nullptr;
        }

        console::Console* console = any_value_console->console_pointer;
        bool result = console->enter_console();

        if (result == false)
        {
            // We did not enter the console.
            return nullptr;
        }

        // Signal to caller that we have entered the console.
        uint32_t enter_console_magic_number = ENTER_CONSOLE_MAGIC_NUMBER;
        datatypes::AnyValue* any_value_magic_number = new datatypes::AnyValue(enter_console_magic_number);
        return any_value_magic_number;
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
        bool result = console_pointer->exit_console();

        if (result == false)
        {
            // We did not exit the console.
            return nullptr;
        }

        // Signal to caller that we have exited the console.
        uint32_t exit_console_magic_number = EXIT_CONSOLE_MAGIC_NUMBER;
        datatypes::AnyValue* any_value_magic_number = new datatypes::AnyValue(exit_console_magic_number);
        return any_value_magic_number;
    }

    datatypes::AnyValue* move_to_previous_input(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>)
    {
        datatypes::AnyValue* any_value_console = callback_object->get_any_value("console_pointer");

        if (any_value_console->type != datatypes::CONSOLE_POINTER)
        {
            return nullptr;
        }

        console::Console* console = any_value_console->console_pointer;
        console->move_to_previous_input();
        return nullptr;
    }

    datatypes::AnyValue* move_to_next_input(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>)
    {
        datatypes::AnyValue* any_value_console = callback_object->get_any_value("console_pointer");

        if (any_value_console->type != datatypes::CONSOLE_POINTER)
        {
            return nullptr;
        }

        console::Console* console = any_value_console->console_pointer;
        console->move_to_next_input();
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
