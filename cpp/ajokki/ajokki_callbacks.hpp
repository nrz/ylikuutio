#include "cpp/ylikuutio/common/any_value.hpp"
#include "cpp/ylikuutio/callback/callback_parameter.hpp"
#include "cpp/ylikuutio/callback/callback_object.hpp"
#include "cpp/ylikuutio/callback/callback_engine.hpp"

namespace ajokki
{
    datatypes::AnyValue* glfwTerminate_cleanup(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*> input_parameters);
    datatypes::AnyValue* full_cleanup(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*> input_parameters);
    datatypes::AnyValue* delete_suzanne_species(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*> input_parameters);
    datatypes::AnyValue* switch_to_new_material(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*> input_parameters);
    datatypes::AnyValue* transform_into_new_species(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*> input_parameters);
}

