#ifndef __AJOKKI_CALLBACKS_HPP_INCLUDED
#define __AJOKKI_CALLBACKS_HPP_INCLUDED

#include "cpp/ylikuutio/common/any_value.hpp"
#include "cpp/ylikuutio/callback_system/callback_parameter.hpp"
#include "cpp/ylikuutio/callback_system/callback_object.hpp"
#include "cpp/ylikuutio/callback_system/callback_engine.hpp"

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

    datatypes::AnyValue* release_first_turbo(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>);

    datatypes::AnyValue* release_second_turbo(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>);

    datatypes::AnyValue* exit_program(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>);

    datatypes::AnyValue* first_turbo(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>);

    datatypes::AnyValue* second_turbo(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>);

    datatypes::AnyValue* move_forward(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>);

    datatypes::AnyValue* move_backward(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>);

    datatypes::AnyValue* strafe_left(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>);

    datatypes::AnyValue* strafe_right(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>);

    datatypes::AnyValue* ascent(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>);

    datatypes::AnyValue* descent(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>);

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

#endif
