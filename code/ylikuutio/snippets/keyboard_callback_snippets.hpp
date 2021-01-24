// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2021 Antti Nuortimo.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef __YLIKUUTIO_SNIPPETS_KEYBOARD_CALLBACK_SNIPPETS_HPP_INCLUDED
#define __YLIKUUTIO_SNIPPETS_KEYBOARD_CALLBACK_SNIPPETS_HPP_INCLUDED

// Include standard headers
#include <memory> // std::make_shared, std::shared_ptr
#include <vector> // std::vector

namespace yli::callback
{
    class CallbackEngine;
    class CallbackObject;
    class CallbackParameter;
}

namespace yli::data
{
    class AnyValue;
}

namespace yli::ontology
{
    class Universe;
}

namespace yli::snippets
{
    /*********************************************************************\
     *  Callback engines for action mode keyreleases begin here.         *
    \*********************************************************************/

    std::shared_ptr<yli::data::AnyValue> release_first_turbo(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::data::AnyValue>);

    std::shared_ptr<yli::data::AnyValue> release_second_turbo(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::data::AnyValue>);

    std::shared_ptr<yli::data::AnyValue> enable_toggle_invert_mouse(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::data::AnyValue>);

    std::shared_ptr<yli::data::AnyValue> enable_toggle_flight_mode(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::data::AnyValue>);

    std::shared_ptr<yli::data::AnyValue> enable_toggle_help_mode(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::data::AnyValue>);

    /*********************************************************************\
     *  Callback engines for action mode keypresses begin here.          *
    \*********************************************************************/

    std::shared_ptr<yli::data::AnyValue> exit_program(
            yli::ontology::Universe*,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::data::AnyValue>);

    std::shared_ptr<yli::data::AnyValue> first_turbo(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::data::AnyValue>);

    std::shared_ptr<yli::data::AnyValue> second_turbo(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::data::AnyValue>);

    std::shared_ptr<yli::data::AnyValue> move_forward(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::data::AnyValue>);

    std::shared_ptr<yli::data::AnyValue> move_backward(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::data::AnyValue>);

    std::shared_ptr<yli::data::AnyValue> strafe_left(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::data::AnyValue>);

    std::shared_ptr<yli::data::AnyValue> strafe_right(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::data::AnyValue>);

    std::shared_ptr<yli::data::AnyValue> ascent(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::data::AnyValue>);

    std::shared_ptr<yli::data::AnyValue> descent(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::data::AnyValue>);

    std::shared_ptr<yli::data::AnyValue> toggle_invert_mouse(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::data::AnyValue>);

    std::shared_ptr<yli::data::AnyValue> toggle_flight_mode(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::data::AnyValue>);

    std::shared_ptr<yli::data::AnyValue> toggle_help_mode(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::data::AnyValue>);

    std::shared_ptr<yli::data::AnyValue> delete_entity(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::data::AnyValue>);

    std::shared_ptr<yli::data::AnyValue> switch_to_new_material(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::data::AnyValue>);

    std::shared_ptr<yli::data::AnyValue> transform_into_new_species(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::data::AnyValue>);
}

#endif
