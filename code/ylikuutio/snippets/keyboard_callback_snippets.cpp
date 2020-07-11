// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
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

#include "keyboard_callback_snippets.hpp"
#include "code/ylikuutio/callback/callback_parameter.hpp"
#include "code/ylikuutio/callback/callback_object.hpp"
#include "code/ylikuutio/callback/callback_engine.hpp"
#include "code/ylikuutio/callback/callback_magic_numbers.hpp"
#include "code/ylikuutio/ontology/console.hpp"
#include "code/ylikuutio/ontology/object.hpp"
#include "code/ylikuutio/ontology/species.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
#include <memory>   // std::make_shared, std::shared_ptr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <variant>  // std::holds_alternative, std::variant
#include <vector>   // std::vector

// Callbacks' input parameters can be accessed either through
// `yli::callback::CallbackObject* callback_object`or
// `std::vector<yli::callback::CallbackParameter*>& input parameters`.
//
// To access a name input variable:
// `std::shared_ptr<yli::data::AnyValue> some_any_value = callback_object->get_any_value("foo");`
// where `"foo"` is the variable name.
//
// Using a numeric index is more efficient and should be used
// in cases where the input variable order is known beforehand.
// However, the difference may be small.
//
// To access an input variable using a numeric index (this works for named input variables too):
// `std::shared_ptr<yli::data::AnyValue> some_any_value = callback_object->get_arg(0);`
//
// `get_arg` takes the zero-based index of the variable as function parameter.
// First `CallbackParameter` of a `CallbackObject` gets index 0,
// second `CallbackParameter` gets index 1, etc.

namespace yli::snippets
{
    /*********************************************************************\
     * Helper functions for callbacks begin here.                        *
    \*********************************************************************/

    bool move_to_direction(yli::ontology::Universe* const universe, const yli::callback::CallbackObject* const callback_object, const glm::vec3& moving_direction)
    {
        // Movement changes location and orientation variables stored in `yli::ontology::Universe`.
        // This way there is no need to dereference pointer to the current `yli::ontology::Camera`.
        // When the current `Camera` is changed, then the location and orientation data is copied
        // from `Universe` to the previous `Camera`.
        //
        // Also, location and orientation variables' read callbacks need to check if the referred
        // `Scene` is the current `Scene`. If true, then get and return the location or orientation
        // variable in question from the `Universe`, otherwise return the location or orientation
        // variable from the `Scene`'s own member variable.

        if (universe == nullptr)
        {
            std::cerr << "ERROR: `yli::snippets::move_to_direction`: `universe` is `nullptr`!\n";
            return false;
        }

        const yli::ontology::Scene* const scene = universe->get_active_scene();

        if (scene == nullptr)
        {
            // No active scene.
            return false;
        }

        float temp_speed;

        if (universe->is_first_turbo_pressed && universe->is_second_turbo_pressed)
        {
            temp_speed = universe->twin_turbo_factor * universe->speed;
        }
        else if (universe->is_first_turbo_pressed || universe->is_second_turbo_pressed)
        {
            temp_speed = universe->turbo_factor * universe->speed;
        }
        else
        {
            temp_speed = universe->speed;
        }
        universe->current_camera_cartesian_coordinates += temp_speed * universe->get_delta_time() * moving_direction;

        return true;
    }

    /*********************************************************************\
     *  Callback engines for action mode keyreleases begin here.         *
    \*********************************************************************/

    std::shared_ptr<yli::data::AnyValue> release_first_turbo(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::data::AnyValue>)
    {
        if (universe == nullptr)
        {
            std::cerr << "ERROR: `yli::snippets::release_first_turbo`: `universe` is `nullptr`!\n";
            return nullptr;
        }

        universe->is_first_turbo_pressed = false;
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> release_second_turbo(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::data::AnyValue>)
    {
        if (universe == nullptr)
        {
            std::cerr << "ERROR: `yli::snippets::release_second_turbo`: `universe` is `nullptr`!\n";
            return nullptr;
        }

        universe->is_second_turbo_pressed = false;
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> enable_toggle_invert_mouse(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::data::AnyValue>)
    {
        if (universe == nullptr)
        {
            std::cerr << "ERROR: `yli::snippets::enable_toggle_invert_mouse`: `universe` is `nullptr`!\n";
            return nullptr;
        }

        universe->can_toggle_invert_mouse = true;
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> enable_toggle_flight_mode(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::data::AnyValue>)
    {
        if (universe == nullptr)
        {
            std::cerr << "ERROR: `yli::snippets::enable_toggle_flight_mode`: `universe` is `nullptr`!\n";
            return nullptr;
        }

        universe->can_toggle_flight_mode = true;
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> enable_toggle_help_mode(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::data::AnyValue>)
    {
        if (universe == nullptr)
        {
            std::cerr << "ERROR: `yli::snippets::enable_toggle_help_mode`: `universe` is `nullptr`!\n";
            return nullptr;
        }

        universe->can_toggle_help_mode = true;
        return nullptr;
    }

    /*********************************************************************\
     *  Callback engines for action mode keypresses begin here.          *
    \*********************************************************************/

    std::shared_ptr<yli::data::AnyValue> exit_program(
            yli::ontology::Universe*,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::data::AnyValue>)
    {
        const uint32_t exit_program_magic_number = EXIT_PROGRAM_MAGIC_NUMBER;
        return std::make_shared<yli::data::AnyValue>(exit_program_magic_number);
    }

    std::shared_ptr<yli::data::AnyValue> first_turbo(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::data::AnyValue>)
    {
        if (universe == nullptr)
        {
            std::cerr << "ERROR: `yli::snippets::first_turbo`: `universe` is `nullptr`!\n";
            return nullptr;
        }

        universe->is_first_turbo_pressed = true;
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> second_turbo(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::data::AnyValue>)
    {
        if (universe == nullptr)
        {
            std::cerr << "ERROR: `yli::snippets::second_turbo`: `universe` is `nullptr`!\n";
            return nullptr;
        }

        universe->is_second_turbo_pressed = true;
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> move_forward(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::data::AnyValue>)
    {
        if (universe == nullptr)
        {
            std::cerr << "ERROR: `yli::snippets::move_forward`: `universe` is `nullptr`!\n";
            return nullptr;
        }

        yli::snippets::move_to_direction(universe, callback_object, universe->current_camera_direction);
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> move_backward(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::data::AnyValue>)
    {
        if (universe == nullptr)
        {
            std::cerr << "ERROR: `yli::snippets::move_backward`: `universe` is `nullptr`!\n";
            return nullptr;
        }

        yli::snippets::move_to_direction(universe, callback_object, -universe->current_camera_direction);
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> strafe_left(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::data::AnyValue>)
    {
        if (universe == nullptr)
        {
            std::cerr << "ERROR: `yli::snippets::strafe_left`: `universe` is `nullptr`!\n";
            return nullptr;
        }

        yli::snippets::move_to_direction(universe, callback_object, -universe->current_camera_right);
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> strafe_right(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::data::AnyValue>)
    {
        if (universe == nullptr)
        {
            std::cerr << "ERROR: `yli::snippets::strafe_right`: `universe` is `nullptr`!\n";
            return nullptr;
        }

        yli::snippets::move_to_direction(universe, callback_object, universe->current_camera_right);
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> ascent(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::data::AnyValue>)
    {
        if (universe == nullptr)
        {
            std::cerr << "ERROR: `yli::snippets::ascent`: `universe` is `nullptr`!\n";
            return nullptr;
        }

        yli::snippets::move_to_direction(universe, callback_object, universe->current_camera_up);
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> descent(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::data::AnyValue>)
    {
        if (universe == nullptr)
        {
            std::cerr << "ERROR: `yli::snippets::descent`: `universe` is `nullptr`!\n";
            return nullptr;
        }

        yli::snippets::move_to_direction(universe, callback_object, -universe->current_camera_up);
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> toggle_invert_mouse(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::data::AnyValue>)
    {
        if (universe == nullptr)
        {
            std::cerr << "ERROR: `yli::snippets::toggle_invert_mouse`: `universe` is `nullptr`!\n";
            return nullptr;
        }

        if (universe->can_toggle_invert_mouse)
        {
            universe->is_invert_mouse_in_use = !universe->is_invert_mouse_in_use;
            universe->can_toggle_invert_mouse = false;
        }
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> toggle_flight_mode(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::data::AnyValue>)
    {
        if (universe == nullptr)
        {
            std::cerr << "ERROR: `yli::snippets::toggle_flight_mode`: `universe` is `nullptr`!\n";
            return nullptr;
        }

        if (universe->can_toggle_flight_mode)
        {
            yli::ontology::Scene* const scene = universe->get_active_scene();

            if (scene == nullptr)
            {
                return nullptr;
            }

            scene->set_is_flight_mode_in_use(!scene->get_is_flight_mode_in_use());
            scene->set_fall_speed(0.0f);
            universe->can_toggle_flight_mode = false;
        }
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> toggle_help_mode(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::data::AnyValue>)
    {
        if (universe == nullptr)
        {
            std::cerr << "ERROR: `yli::snippets::toggle_help_mode`: `universe` is `nullptr`!\n";
            return nullptr;
        }

        if (universe->can_toggle_help_mode)
        {
            universe->in_help_mode = !universe->in_help_mode;
            universe->can_toggle_help_mode = false;
        }
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> delete_entity(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::data::AnyValue>)
    {
        if (universe == nullptr)
        {
            std::cerr << "ERROR: `yli::snippets::delete_entity`: `universe` is `nullptr`!\n";
            return nullptr;
        }

        const std::shared_ptr<yli::data::AnyValue> entity_name_string_pointer_any_value = callback_object->get_arg(0);

        if (entity_name_string_pointer_any_value == nullptr)
        {
            std::cerr << "ERROR: `yli::snippets::delete_entity`: `entity_string` not found!\n";
            return nullptr;
        }

        if (!std::holds_alternative<std::string*>(entity_name_string_pointer_any_value->data) &&
                !std::holds_alternative<const std::string*>(entity_name_string_pointer_any_value->data))
        {
            std::cerr << "ERROR: `yli::snippets::delete_entity`: invalid datatype.\n";
            std::cerr << "Datatype should be either yli::data::Datatype::STD_STRING_POINTER or yli::data::Datatype::CONST_STD_STRING_POINTER\n";
            return nullptr;
        }

        const std::string* const entity_string_pointer =
            (std::holds_alternative<std::string*>(entity_name_string_pointer_any_value->data) ?
             std::get<std::string*>(entity_name_string_pointer_any_value->data) :
             std::get<const std::string*>(entity_name_string_pointer_any_value->data));

        if (entity_string_pointer == nullptr)
        {
            return nullptr;
        }

        const std::string entity_string = *entity_string_pointer;

        yli::ontology::Entity* const entity = universe->get_entity(entity_string);

        if (entity == nullptr)
        {
            return nullptr;
        }

        delete entity;

        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> switch_to_new_material(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::data::AnyValue>)
    {
        if (universe == nullptr)
        {
            std::cerr << "ERROR: `yli::snippets::switch_to_new_material`: `universe` is `nullptr`!\n";
            return nullptr;
        }

        std::shared_ptr<yli::data::AnyValue> entity_name_string_pointer_any_value = callback_object->get_arg(0);

        if (entity_name_string_pointer_any_value == nullptr)
        {
            std::cerr << "ERROR: `yli::snippets::switch_to_new_material`: `entity_string` not found!\n";
            return nullptr;
        }

        if (!std::holds_alternative<std::string*>(entity_name_string_pointer_any_value->data) &&
                !std::holds_alternative<const std::string*>(entity_name_string_pointer_any_value->data))
        {
            std::cerr << "ERROR: `yli::snippets::switch_to_new_material`: invalid datatype.\n";
            std::cerr << "Datatype should be either yli::data::Datatype::STD_STRING_POINTER or yli::data::Datatype::CONST_STD_STRING_POINTER\n";
            return nullptr;
        }

        const std::string* const entity_string_pointer =
            (std::holds_alternative<std::string*>(entity_name_string_pointer_any_value->data) ?
             std::get<std::string*>(entity_name_string_pointer_any_value->data) :
             std::get<const std::string*>(entity_name_string_pointer_any_value->data));

        if (entity_string_pointer == nullptr)
        {
            return nullptr;
        }

        const std::string entity_string = *entity_string_pointer;

        yli::ontology::Entity* const entity = universe->get_entity(entity_string);

        if (entity == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Species* const species = dynamic_cast<yli::ontology::Species*>(entity);

        if (species == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Entity* const old_material_entity = species->get_parent();

        const yli::ontology::Material* const old_material = dynamic_cast<yli::ontology::Material*>(old_material_entity);

        if (old_material == nullptr)
        {
            return nullptr;
        }

        std::shared_ptr<yli::data::AnyValue> any_value_material_string = callback_object->get_arg(1);

        if (any_value_material_string == nullptr)
        {
            std::cerr << "ERROR: `yli::snippets::switch_to_new_material`: `material_string` not found!\n";
            return nullptr;
        }

        if (!std::holds_alternative<std::string*>(any_value_material_string->data) &&
                !std::holds_alternative<const std::string*>(any_value_material_string->data))
        {
            std::cerr << "ERROR: `yli::snippets::switch_to_new_material`: invalid datatype.\n";
            std::cerr << "Datatype should be either yli::data::Datatype::STD_STRING_POINTER or yli::data::Datatype::CONST_STD_STRING_POINTER\n";
            return nullptr;
        }

        const std::string* const new_material_string_pointer =
            (std::holds_alternative<std::string*>(any_value_material_string->data) ?
             std::get<std::string*>(any_value_material_string->data) :
             std::get<const std::string*>(any_value_material_string->data));

        if (new_material_string_pointer == nullptr)
        {
            return nullptr;
        }

        const std::string new_material_string = *new_material_string_pointer;

        yli::ontology::Entity* const new_material_entity = universe->get_entity(new_material_string);

        if (new_material_entity == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Material* const new_material = dynamic_cast<yli::ontology::Material*>(new_material_entity);

        if (new_material == nullptr)
        {
            return nullptr;
        }

        if (old_material == new_material)
        {
            // New parent is the same as old parent, no changes needed.
            return nullptr;
        }

        species->bind_to_new_parent(new_material);
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> transform_into_new_species(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::data::AnyValue>)
    {
        if (universe == nullptr)
        {
            std::cerr << "ERROR: `yli::snippets::transform_into_new_species`: `universe` is `nullptr`!\n";
            return nullptr;
        }

        std::shared_ptr<yli::data::AnyValue> entity_name_string_pointer_any_value = callback_object->get_arg(0);

        if (entity_name_string_pointer_any_value == nullptr)
        {
            std::cerr << "ERROR: `yli::snippets::transform_into_new_species`: `entity_string` not found!\n";
            return nullptr;
        }

        if (!std::holds_alternative<std::string*>(entity_name_string_pointer_any_value->data) &&
                !std::holds_alternative<const std::string*>(entity_name_string_pointer_any_value->data))
        {
            std::cerr << "ERROR: `yli::snippets::transform_into_new_species`: invalid datatype.\n";
            std::cerr << "Datatype should be either yli::data::Datatype::STD_STRING_POINTER or yli::data::Datatype::CONST_STD_STRING_POINTER\n";
            return nullptr;
        }

        const std::string* const entity_string_pointer =
            (std::holds_alternative<std::string*>(entity_name_string_pointer_any_value->data) ?
             std::get<std::string*>(entity_name_string_pointer_any_value->data) :
             std::get<const std::string*>(entity_name_string_pointer_any_value->data));

        if (entity_string_pointer == nullptr)
        {
            return nullptr;
        }

        const std::string entity_string = *entity_string_pointer;

        yli::ontology::Entity* const entity = universe->get_entity(entity_string);

        if (entity == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Object* const object = dynamic_cast<yli::ontology::Object*>(entity);

        if (object == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Entity* const old_species_entity = object->get_parent();

        const yli::ontology::Species* const old_species = dynamic_cast<yli::ontology::Species*>(old_species_entity);

        if (old_species == nullptr)
        {
            return nullptr;
        }

        std::shared_ptr<yli::data::AnyValue> any_value_species_string = callback_object->get_arg(1);

        if (any_value_species_string == nullptr)
        {
            std::cerr << "ERROR: `yli::snippets::transform_into_new_species`: `species_string` not found!\n";
            return nullptr;
        }

        if (!std::holds_alternative<std::string*>(any_value_species_string->data) &&
                !std::holds_alternative<const std::string*>(any_value_species_string->data))
        {
            std::cerr << "ERROR: `yli::snippets::transform_into_new_species`: invalid datatype.\n";
            std::cerr << "Datatype should be either yli::data::Datatype::STD_STRING_POINTER or yli::data::Datatype::CONST_STD_STRING_POINTER\n";
            return nullptr;
        }

        const std::string* const new_species_string_pointer =
            (std::holds_alternative<std::string*>(any_value_species_string->data) ?
             std::get<std::string*>(any_value_species_string->data) :
             std::get<const std::string*>(any_value_species_string->data));

        if (new_species_string_pointer == nullptr)
        {
            return nullptr;
        }

        const std::string new_species_string = *new_species_string_pointer;

        yli::ontology::Entity* const new_species_entity = universe->get_entity(new_species_string);

        if (new_species_entity == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Species* const new_species = dynamic_cast<yli::ontology::Species*>(new_species_entity);

        if (new_species == nullptr)
        {
            return nullptr;
        }

        if (old_species == new_species)
        {
            // New parent is the same as old parent, no changes needed.
            return nullptr;
        }

        object->bind_to_new_parent(new_species);
        return nullptr;
    }
}
