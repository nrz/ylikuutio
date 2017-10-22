#ifndef __CONSOLE_CALLBACK_OBJECT_HPP_INCLUDED
#define __CONSOLE_CALLBACK_OBJECT_HPP_INCLUDED

#include "console.hpp"
#include "code/ylikuutio/callback_system/callback_object.hpp"
#include "code/ylikuutio/callback_system/callback_engine.hpp"
#include "code/ylikuutio/common/globals.hpp"

// Include standard headers
#include <memory>   // std::make_shared, std::shared_ptr

namespace callback_system
{
    class CallbackParameter;
}

namespace console
{
    class ConsoleCallbackObject : public callback_system::CallbackObject
    {
        public:
            // constructor.
            ConsoleCallbackObject(InputParametersToAnyValueCallbackWithConsole console_callback,
                    callback_system::CallbackEngine* parent, console::Console* console_pointer)
                : callback_system::CallbackObject(nullptr, parent)
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
            std::shared_ptr<datatypes::AnyValue> execute();

            InputParametersToAnyValueCallbackWithConsole console_callback;
            console::Console* console_pointer;
    };
}

#endif
