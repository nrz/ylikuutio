#include "cpp/ylikuutio/callback_system/callback_parameter.hpp"
#include "cpp/ylikuutio/callback_system/callback_object.hpp"
#include "cpp/ylikuutio/callback_system/callback_engine.hpp"
#include "cpp/ylikuutio/common/any_value.hpp"

// Include standard headers
#include <vector>   // std::vector

namespace console
{
    //void charmods_callback(GLFWwindow* window, unsigned int codepoint, int mods);
    void character_callback(GLFWwindow* window, unsigned int codepoint);

    datatypes::AnyValue* exit_console(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>);

    datatypes::AnyValue* add_character(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>);

    datatypes::AnyValue* backspace(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>);
}
