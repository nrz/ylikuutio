#ifndef __AJOKKI_KEYBOARD_CALLBACKS_HPP_INCLUDED
#define __AJOKKI_KEYBOARD_CALLBACKS_HPP_INCLUDED

#include "code/ylikuutio/common/any_value.hpp"
#include "code/ylikuutio/callback_system/callback_parameter.hpp"
#include "code/ylikuutio/callback_system/callback_object.hpp"
#include "code/ylikuutio/callback_system/callback_engine.hpp"

// Include standard headers
#include <memory> // std::make_shared, std::shared_ptr

namespace ajokki
{
    /*********************************************************************\
     *  Callback engines for action mode keyreleases begin here.         *
    \*********************************************************************/

    std::shared_ptr<datatypes::AnyValue> release_first_turbo(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> release_second_turbo(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> enable_toggle_invert_mouse(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> enable_toggle_flight_mode(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> enable_toggle_help_mode(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>&);

    /*********************************************************************\
     *  Callback engines for action mode keypresses begin here.          *
    \*********************************************************************/

    std::shared_ptr<datatypes::AnyValue> exit_program(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> first_turbo(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> second_turbo(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> move_forward(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> move_backward(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> strafe_left(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> strafe_right(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> ascent(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> descent(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> toggle_invert_mouse(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> toggle_flight_mode(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> toggle_help_mode(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> delete_suzanne_species(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> switch_to_new_material(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> transform_into_new_species(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>&);
}

#endif
