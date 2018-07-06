#ifndef __AJOKKI_KEYBOARD_CALLBACKS_HPP_INCLUDED
#define __AJOKKI_KEYBOARD_CALLBACKS_HPP_INCLUDED

#include "code/ylikuutio/common/any_value.hpp"

// Include standard headers
#include <memory> // std::make_shared, std::shared_ptr
#include <vector> // std::vector

namespace ylikuutio
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
            ylikuutio::callback_system::CallbackEngine*,
            ylikuutio::callback_system::CallbackObject* callback_object,
            std::vector<ylikuutio::callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> release_second_turbo(
            ylikuutio::callback_system::CallbackEngine*,
            ylikuutio::callback_system::CallbackObject* callback_object,
            std::vector<ylikuutio::callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> enable_toggle_invert_mouse(
            ylikuutio::callback_system::CallbackEngine*,
            ylikuutio::callback_system::CallbackObject* callback_object,
            std::vector<ylikuutio::callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> enable_toggle_flight_mode(
            ylikuutio::callback_system::CallbackEngine*,
            ylikuutio::callback_system::CallbackObject* callback_object,
            std::vector<ylikuutio::callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> enable_toggle_help_mode(
            ylikuutio::callback_system::CallbackEngine*,
            ylikuutio::callback_system::CallbackObject* callback_object,
            std::vector<ylikuutio::callback_system::CallbackParameter*>&);

    /*********************************************************************\
     *  Callback engines for action mode keypresses begin here.          *
    \*********************************************************************/

    std::shared_ptr<datatypes::AnyValue> exit_program(
            ylikuutio::callback_system::CallbackEngine*,
            ylikuutio::callback_system::CallbackObject*,
            std::vector<ylikuutio::callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> first_turbo(
            ylikuutio::callback_system::CallbackEngine*,
            ylikuutio::callback_system::CallbackObject* callback_object,
            std::vector<ylikuutio::callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> second_turbo(
            ylikuutio::callback_system::CallbackEngine*,
            ylikuutio::callback_system::CallbackObject* callback_object,
            std::vector<ylikuutio::callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> move_forward(
            ylikuutio::callback_system::CallbackEngine*,
            ylikuutio::callback_system::CallbackObject* callback_object,
            std::vector<ylikuutio::callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> move_backward(
            ylikuutio::callback_system::CallbackEngine*,
            ylikuutio::callback_system::CallbackObject* callback_object,
            std::vector<ylikuutio::callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> strafe_left(
            ylikuutio::callback_system::CallbackEngine*,
            ylikuutio::callback_system::CallbackObject* callback_object,
            std::vector<ylikuutio::callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> strafe_right(
            ylikuutio::callback_system::CallbackEngine*,
            ylikuutio::callback_system::CallbackObject* callback_object,
            std::vector<ylikuutio::callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> ascent(
            ylikuutio::callback_system::CallbackEngine*,
            ylikuutio::callback_system::CallbackObject* callback_object,
            std::vector<ylikuutio::callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> descent(
            ylikuutio::callback_system::CallbackEngine*,
            ylikuutio::callback_system::CallbackObject* callback_object,
            std::vector<ylikuutio::callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> toggle_invert_mouse(
            ylikuutio::callback_system::CallbackEngine*,
            ylikuutio::callback_system::CallbackObject* callback_object,
            std::vector<ylikuutio::callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> toggle_flight_mode(
            ylikuutio::callback_system::CallbackEngine*,
            ylikuutio::callback_system::CallbackObject* callback_object,
            std::vector<ylikuutio::callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> toggle_help_mode(
            ylikuutio::callback_system::CallbackEngine*,
            ylikuutio::callback_system::CallbackObject* callback_object,
            std::vector<ylikuutio::callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> delete_entity(
            ylikuutio::callback_system::CallbackEngine*,
            ylikuutio::callback_system::CallbackObject* callback_object,
            std::vector<ylikuutio::callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> switch_to_new_material(
            ylikuutio::callback_system::CallbackEngine*,
            ylikuutio::callback_system::CallbackObject* callback_object,
            std::vector<ylikuutio::callback_system::CallbackParameter*>&);

    std::shared_ptr<datatypes::AnyValue> transform_into_new_species(
            ylikuutio::callback_system::CallbackEngine*,
            ylikuutio::callback_system::CallbackObject* callback_object,
            std::vector<ylikuutio::callback_system::CallbackParameter*>&);
}

#endif
