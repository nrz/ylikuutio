#ifndef __CONSOLE_CALLBACK_OBJECT_HPP_INCLUDED
#define __CONSOLE_CALLBACK_OBJECT_HPP_INCLUDED

#include "console.hpp"
#include "input_parameters_to_any_value_callback_with_console.hpp"
#include "code/ylikuutio/callback_system/callback_object.hpp"

// Include standard headers
#include <memory>   // std::make_shared, std::shared_ptr

namespace yli
{
    namespace callback_system
    {
        class CallbackEngine;
        class CallbackParameter;
    }

    namespace datatypes
    {
        class AnyValue;
    }

    namespace console
    {
        class ConsoleCallbackObject : public yli::callback_system::CallbackObject
        {
            public:
                // constructor.
                ConsoleCallbackObject(InputParametersToAnyValueCallbackWithConsole console_callback,
                        yli::callback_system::CallbackEngine* parent, yli::console::Console* console_pointer)
                    : yli::callback_system::CallbackObject(nullptr, parent)
                {
                    // constructor.
                    this->callback = nullptr;
                    this->console_callback = console_callback;
                    this->console_pointer = console_pointer;
                }

                // destructor.
                ~ConsoleCallbackObject();

            private:
                // execute this callback.
                std::shared_ptr<yli::datatypes::AnyValue> execute();

                InputParametersToAnyValueCallbackWithConsole console_callback;
                yli::console::Console* console_pointer;
        };
    }
}

#endif
