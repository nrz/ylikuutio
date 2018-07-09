#ifndef __AJOKKI_KEYBOARD_CALLBACKS_HPP_INCLUDED
#define __AJOKKI_KEYBOARD_CALLBACKS_HPP_INCLUDED

#include "code/ylikuutio/common/any_value.hpp"

// Include standard headers
#include <memory> // std::make_shared, std::shared_ptr
#include <vector> // std::vector

namespace yli
{
    namespace callback_system
    {
        class CallbackEngine;
        class CallbackObject;
        class CallbackParameter;
    }
}

namespace ajokki
{
    /*********************************************************************\
     *  Callback engines for action mode keyreleases begin here.         *
    \*********************************************************************/

    std::shared_ptr<datatypes::AnyValue> release_first_turbo(
            yli::callback_system::CallbackEngine*,
            yli::callback_system::CallbackObject* callback_object,
            std::vector<yli::callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> release_second_turbo(
            yli::callback_system::CallbackEngine*,
            yli::callback_system::CallbackObject* callback_object,
            std::vector<yli::callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> enable_toggle_invert_mouse(
            yli::callback_system::CallbackEngine*,
            yli::callback_system::CallbackObject* callback_object,
            std::vector<yli::callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> enable_toggle_flight_mode(
            yli::callback_system::CallbackEngine*,
            yli::callback_system::CallbackObject* callback_object,
            std::vector<yli::callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> enable_toggle_help_mode(
            yli::callback_system::CallbackEngine*,
            yli::callback_system::CallbackObject* callback_object,
            std::vector<yli::callback_system::CallbackParameter*>&);

    /*********************************************************************\
     *  Callback engines for action mode keypresses begin here.          *
    \*********************************************************************/

    std::shared_ptr<datatypes::AnyValue> exit_program(
            yli::callback_system::CallbackEngine*,
            yli::callback_system::CallbackObject*,
            std::vector<yli::callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> first_turbo(
            yli::callback_system::CallbackEngine*,
            yli::callback_system::CallbackObject* callback_object,
            std::vector<yli::callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> second_turbo(
            yli::callback_system::CallbackEngine*,
            yli::callback_system::CallbackObject* callback_object,
            std::vector<yli::callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> move_forward(
            yli::callback_system::CallbackEngine*,
            yli::callback_system::CallbackObject* callback_object,
            std::vector<yli::callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> move_backward(
            yli::callback_system::CallbackEngine*,
            yli::callback_system::CallbackObject* callback_object,
            std::vector<yli::callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> strafe_left(
            yli::callback_system::CallbackEngine*,
            yli::callback_system::CallbackObject* callback_object,
            std::vector<yli::callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> strafe_right(
            yli::callback_system::CallbackEngine*,
            yli::callback_system::CallbackObject* callback_object,
            std::vector<yli::callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> ascent(
            yli::callback_system::CallbackEngine*,
            yli::callback_system::CallbackObject* callback_object,
            std::vector<yli::callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> descent(
            yli::callback_system::CallbackEngine*,
            yli::callback_system::CallbackObject* callback_object,
            std::vector<yli::callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> toggle_invert_mouse(
            yli::callback_system::CallbackEngine*,
            yli::callback_system::CallbackObject* callback_object,
            std::vector<yli::callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> toggle_flight_mode(
            yli::callback_system::CallbackEngine*,
            yli::callback_system::CallbackObject* callback_object,
            std::vector<yli::callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> toggle_help_mode(
            yli::callback_system::CallbackEngine*,
            yli::callback_system::CallbackObject* callback_object,
            std::vector<yli::callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> delete_entity(
            yli::callback_system::CallbackEngine*,
            yli::callback_system::CallbackObject* callback_object,
            std::vector<yli::callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> switch_to_new_material(
            yli::callback_system::CallbackEngine*,
            yli::callback_system::CallbackObject* callback_object,
            std::vector<yli::callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> transform_into_new_species(
            yli::callback_system::CallbackEngine*,
            yli::callback_system::CallbackObject* callback_object,
            std::vector<yli::callback_system::CallbackParameter*>&);
}

#endif
