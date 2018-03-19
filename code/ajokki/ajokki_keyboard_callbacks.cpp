#include "ajokki_keyboard_callbacks.hpp"
#include "code/ylikuutio/callback_system/callback_parameter.hpp"
#include "code/ylikuutio/callback_system/callback_object.hpp"
#include "code/ylikuutio/callback_system/callback_engine.hpp"
#include "code/ylikuutio/callback_system/callback_magic_numbers.hpp"
#include "code/ylikuutio/console/console.hpp"
#include "code/ylikuutio/ontology/object.hpp"
#include "code/ylikuutio/ontology/species.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/world.hpp"
#include "code/ylikuutio/common/any_value.hpp"
#include "code/ylikuutio/common/globals.hpp"

// Include GLFW
#ifndef __GLFW3_H_INCLUDED
#define __GLFW3_H_INCLUDED
#include <GLFW/glfw3.h>
#endif

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
#include <memory>   // std::make_shared, std::shared_ptr
#include <vector>   // std::vector

namespace ajokki
{
    bool move_to_direction(callback_system::CallbackObject* callback_object, glm::vec3 moving_direction)
    {
        std::shared_ptr<datatypes::AnyValue> any_value_universe = std::make_shared<datatypes::AnyValue>(*callback_object->get_arg(0));

        if (any_value_universe == nullptr)
        {
            std::cerr << "Error: universe not found!\n";
            return false;
        }

        if (any_value_universe->type != datatypes::UNIVERSE_POINTER)
        {
            std::cerr << "Invalid datatype: " << any_value_universe->type << ", should be " << datatypes::UNIVERSE_POINTER << "\n";
            return false;
        }

        ontology::Universe* universe = any_value_universe->universe;

        if (universe == nullptr)
        {
            std::cerr << "Error: universe is nullptr!\n";
            return false;
        }

        ontology::World* world = universe->get_active_world();

        if (world == nullptr)
        {
            // No active `World`.
            return false;
        }

        ontology::Scene* scene = universe->get_active_world()->get_active_scene();

        if (scene == nullptr)
        {
            // No active scene.
            return false;
        }

        GLfloat temp_speed;

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

    std::shared_ptr<datatypes::AnyValue> release_first_turbo(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>&)
    {
        std::shared_ptr<datatypes::AnyValue> any_value_universe = std::make_shared<datatypes::AnyValue>(*callback_object->get_arg(0));

        if (any_value_universe == nullptr)
        {
            std::cerr << "Error: universe not found!\n";
            return nullptr;
        }

        if (any_value_universe->type != datatypes::UNIVERSE_POINTER)
        {
            std::cerr << "Invalid datatype: " << any_value_universe->type << ", should be " << datatypes::UNIVERSE_POINTER << "\n";
            return nullptr;
        }

        ontology::Universe* universe = any_value_universe->universe;

        if (universe == nullptr)
        {
            std::cerr << "Error: universe is nullptr!\n";
            return nullptr;
        }

        universe->is_first_turbo_pressed = false;
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> release_second_turbo(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>&)
    {
        std::shared_ptr<datatypes::AnyValue> any_value_universe = std::make_shared<datatypes::AnyValue>(*callback_object->get_arg(0));

        if (any_value_universe == nullptr)
        {
            std::cerr << "Error: universe not found!\n";
            return nullptr;
        }

        if (any_value_universe->type != datatypes::UNIVERSE_POINTER)
        {
            std::cerr << "Invalid datatype: " << any_value_universe->type << ", should be " << datatypes::UNIVERSE_POINTER << "\n";
            return nullptr;
        }

        ontology::Universe* universe = any_value_universe->universe;

        if (universe == nullptr)
        {
            std::cerr << "Error: universe is nullptr!\n";
            return nullptr;
        }

        universe->is_second_turbo_pressed = false;
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> enable_toggle_invert_mouse(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>&)
    {
        std::shared_ptr<datatypes::AnyValue> any_value_universe = std::make_shared<datatypes::AnyValue>(*callback_object->get_arg(0));

        if (any_value_universe == nullptr)
        {
            std::cerr << "Error: universe not found!\n";
            return nullptr;
        }

        if (any_value_universe->type != datatypes::UNIVERSE_POINTER)
        {
            std::cerr << "Invalid datatype: " << any_value_universe->type << ", should be " << datatypes::UNIVERSE_POINTER << "\n";
            return nullptr;
        }

        ontology::Universe* universe = any_value_universe->universe;

        if (universe == nullptr)
        {
            std::cerr << "Error: universe is nullptr!\n";
            return nullptr;
        }

        universe->can_toggle_invert_mouse = true;
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> enable_toggle_flight_mode(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>&)
    {
        std::shared_ptr<datatypes::AnyValue> any_value_universe = std::make_shared<datatypes::AnyValue>(*callback_object->get_arg(0));

        if (any_value_universe == nullptr)
        {
            std::cerr << "Error: universe not found!\n";
            return nullptr;
        }

        if (any_value_universe->type != datatypes::UNIVERSE_POINTER)
        {
            std::cerr << "Invalid datatype: " << any_value_universe->type << ", should be " << datatypes::UNIVERSE_POINTER << "\n";
            return nullptr;
        }

        ontology::Universe* universe = any_value_universe->universe;

        if (universe == nullptr)
        {
            std::cerr << "Error: universe is nullptr!\n";
            return nullptr;
        }

        universe->can_toggle_flight_mode = true;
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> enable_toggle_help_mode(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>&)
    {
        std::shared_ptr<datatypes::AnyValue> any_value_universe = std::make_shared<datatypes::AnyValue>(*callback_object->get_arg(0));

        if (any_value_universe == nullptr)
        {
            std::cerr << "Error: universe not found!\n";
            return nullptr;
        }

        if (any_value_universe->type != datatypes::UNIVERSE_POINTER)
        {
            std::cerr << "Invalid datatype: " << any_value_universe->type << ", should be " << datatypes::UNIVERSE_POINTER << "\n";
            return nullptr;
        }

        ontology::Universe* universe = any_value_universe->universe;

        if (universe == nullptr)
        {
            std::cerr << "Error: universe is nullptr!\n";
            return nullptr;
        }

        universe->can_toggle_help_mode = true;
        return nullptr;
    }

    /*********************************************************************\
     *  Callback engines for action mode keypresses begin here.          *
    \*********************************************************************/

    std::shared_ptr<datatypes::AnyValue> exit_program(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*>&)
    {
        uint32_t exit_program_magic_number = EXIT_PROGRAM_MAGIC_NUMBER;
        return std::make_shared<datatypes::AnyValue>(exit_program_magic_number);
    }

    std::shared_ptr<datatypes::AnyValue> first_turbo(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>&)
    {
        std::shared_ptr<datatypes::AnyValue> any_value_universe = std::make_shared<datatypes::AnyValue>(*callback_object->get_arg(0));

        if (any_value_universe == nullptr)
        {
            std::cerr << "Error: universe not found!\n";
            return nullptr;
        }

        if (any_value_universe->type != datatypes::UNIVERSE_POINTER)
        {
            std::cerr << "Invalid datatype: " << any_value_universe->type << ", should be " << datatypes::UNIVERSE_POINTER << "\n";
            return nullptr;
        }

        ontology::Universe* universe = any_value_universe->universe;

        if (universe == nullptr)
        {
            std::cerr << "Error: universe is nullptr!\n";
            return nullptr;
        }

        universe->is_first_turbo_pressed = true;
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> second_turbo(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>&)
    {
        std::shared_ptr<datatypes::AnyValue> any_value_universe = std::make_shared<datatypes::AnyValue>(*callback_object->get_arg(0));

        if (any_value_universe == nullptr)
        {
            std::cerr << "Error: universe not found!\n";
            return nullptr;
        }

        if (any_value_universe->type != datatypes::UNIVERSE_POINTER)
        {
            std::cerr << "Invalid datatype: " << any_value_universe->type << ", should be " << datatypes::UNIVERSE_POINTER << "\n";
            return nullptr;
        }

        ontology::Universe* universe = any_value_universe->universe;

        if (universe == nullptr)
        {
            std::cerr << "Error: universe is nullptr!\n";
            return nullptr;
        }

        universe->is_second_turbo_pressed = true;
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> move_forward(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>&)
    {
        std::shared_ptr<datatypes::AnyValue> any_value_universe = std::make_shared<datatypes::AnyValue>(*callback_object->get_arg(0));

        if (any_value_universe == nullptr)
        {
            std::cerr << "Error: universe not found!\n";
            return nullptr;
        }

        if (any_value_universe->type != datatypes::UNIVERSE_POINTER)
        {
            std::cerr << "Invalid datatype: " << any_value_universe->type << ", should be " << datatypes::UNIVERSE_POINTER << "\n";
            return nullptr;
        }

        ontology::Universe* universe = any_value_universe->universe;

        if (universe == nullptr)
        {
            std::cerr << "Error: universe is nullptr!\n";
            return nullptr;
        }

        ajokki::move_to_direction(callback_object, universe->current_camera_direction);
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> move_backward(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>&)
    {
        std::shared_ptr<datatypes::AnyValue> any_value_universe = std::make_shared<datatypes::AnyValue>(*callback_object->get_arg(0));

        if (any_value_universe == nullptr)
        {
            std::cerr << "Error: universe not found!\n";
            return nullptr;
        }

        if (any_value_universe->type != datatypes::UNIVERSE_POINTER)
        {
            std::cerr << "Invalid datatype: " << any_value_universe->type << ", should be " << datatypes::UNIVERSE_POINTER << "\n";
            return nullptr;
        }

        ontology::Universe* universe = any_value_universe->universe;

        if (universe == nullptr)
        {
            std::cerr << "Error: universe is nullptr!\n";
            return nullptr;
        }

        ajokki::move_to_direction(callback_object, -universe->current_camera_direction);
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> strafe_left(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>&)
    {
        std::shared_ptr<datatypes::AnyValue> any_value_universe = std::make_shared<datatypes::AnyValue>(*callback_object->get_arg(0));

        if (any_value_universe == nullptr)
        {
            std::cerr << "Error: universe not found!\n";
            return nullptr;
        }

        if (any_value_universe->type != datatypes::UNIVERSE_POINTER)
        {
            std::cerr << "Invalid datatype: " << any_value_universe->type << ", should be " << datatypes::UNIVERSE_POINTER << "\n";
            return nullptr;
        }

        ontology::Universe* universe = any_value_universe->universe;

        if (universe == nullptr)
        {
            std::cerr << "Error: universe is nullptr!\n";
            return nullptr;
        }

        ajokki::move_to_direction(callback_object, -universe->current_camera_right);
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> strafe_right(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>&)
    {
        std::shared_ptr<datatypes::AnyValue> any_value_universe = std::make_shared<datatypes::AnyValue>(*callback_object->get_arg(0));

        if (any_value_universe == nullptr)
        {
            std::cerr << "Error: universe not found!\n";
            return nullptr;
        }

        if (any_value_universe->type != datatypes::UNIVERSE_POINTER)
        {
            std::cerr << "Invalid datatype: " << any_value_universe->type << ", should be " << datatypes::UNIVERSE_POINTER << "\n";
            return nullptr;
        }

        ontology::Universe* universe = any_value_universe->universe;

        if (universe == nullptr)
        {
            std::cerr << "Error: universe is nullptr!\n";
            return nullptr;
        }

        ajokki::move_to_direction(callback_object, universe->current_camera_right);
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> ascent(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>&)
    {
        std::shared_ptr<datatypes::AnyValue> any_value_universe = std::make_shared<datatypes::AnyValue>(*callback_object->get_arg(0));

        if (any_value_universe == nullptr)
        {
            std::cerr << "Error: universe not found!\n";
            return nullptr;
        }

        if (any_value_universe->type != datatypes::UNIVERSE_POINTER)
        {
            std::cerr << "Invalid datatype: " << any_value_universe->type << ", should be " << datatypes::UNIVERSE_POINTER << "\n";
            return nullptr;
        }

        ontology::Universe* universe = any_value_universe->universe;

        if (universe == nullptr)
        {
            std::cerr << "Error: universe is nullptr!\n";
            return nullptr;
        }

        ajokki::move_to_direction(callback_object, universe->current_camera_up);
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> descent(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>&)
    {
        std::shared_ptr<datatypes::AnyValue> any_value_universe = std::make_shared<datatypes::AnyValue>(*callback_object->get_arg(0));

        if (any_value_universe == nullptr)
        {
            std::cerr << "Error: universe not found!\n";
            return nullptr;
        }

        if (any_value_universe->type != datatypes::UNIVERSE_POINTER)
        {
            std::cerr << "Invalid datatype: " << any_value_universe->type << ", should be " << datatypes::UNIVERSE_POINTER << "\n";
            return nullptr;
        }

        ontology::Universe* universe = any_value_universe->universe;

        if (universe == nullptr)
        {
            std::cerr << "Error: universe is nullptr!\n";
            return nullptr;
        }

        ajokki::move_to_direction(callback_object, -universe->current_camera_up);
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> toggle_invert_mouse(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>&)
    {
        std::shared_ptr<datatypes::AnyValue> any_value_universe = std::make_shared<datatypes::AnyValue>(*callback_object->get_arg(0));

        if (any_value_universe == nullptr)
        {
            std::cerr << "Error: universe not found!\n";
            return nullptr;
        }

        if (any_value_universe->type != datatypes::UNIVERSE_POINTER)
        {
            std::cerr << "Invalid datatype: " << any_value_universe->type << ", should be " << datatypes::UNIVERSE_POINTER << "\n";
            return nullptr;
        }

        ontology::Universe* universe = any_value_universe->universe;

        if (universe == nullptr)
        {
            std::cerr << "Error: universe is nullptr!\n";
            return nullptr;
        }

        if (universe->can_toggle_invert_mouse)
        {
            universe->is_invert_mouse_in_use = !universe->is_invert_mouse_in_use;
            universe->can_toggle_invert_mouse = false;
        }
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> toggle_flight_mode(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>&)
    {
        std::shared_ptr<datatypes::AnyValue> any_value_universe = std::make_shared<datatypes::AnyValue>(*callback_object->get_arg(0));

        if (any_value_universe == nullptr)
        {
            std::cerr << "Error: universe not found!\n";
            return nullptr;
        }

        if (any_value_universe->type != datatypes::UNIVERSE_POINTER)
        {
            std::cerr << "Invalid datatype: " << any_value_universe->type << ", should be " << datatypes::UNIVERSE_POINTER << "\n";
            return nullptr;
        }

        ontology::Universe* universe = any_value_universe->universe;

        if (universe == nullptr)
        {
            std::cerr << "Error: universe is nullptr!\n";
            return nullptr;
        }

        if (universe->can_toggle_flight_mode)
        {
            universe->is_flight_mode_in_use = !universe->is_flight_mode_in_use;
            universe->fall_speed = 0.0f;
            universe->can_toggle_flight_mode = false;
        }
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> toggle_help_mode(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>&)
    {
        std::shared_ptr<datatypes::AnyValue> any_value_universe = std::make_shared<datatypes::AnyValue>(*callback_object->get_arg(0));

        if (any_value_universe == nullptr)
        {
            std::cerr << "Error: universe not found!\n";
            return nullptr;
        }

        if (any_value_universe->type != datatypes::UNIVERSE_POINTER)
        {
            std::cerr << "Invalid datatype: " << any_value_universe->type << ", should be " << datatypes::UNIVERSE_POINTER << "\n";
            return nullptr;
        }

        ontology::Universe* universe = any_value_universe->universe;

        if (universe == nullptr)
        {
            std::cerr << "Error: universe is nullptr!\n";
            return nullptr;
        }

        if (universe->can_toggle_help_mode)
        {
            universe->in_help_mode = !universe->in_help_mode;
            universe->can_toggle_help_mode = false;
        }
        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> delete_entity(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>&)
    {
        // Callbacks' input parameters can be accessed either through
        // `callback_system::CallbackObject* callback_object`or
        // `std::vector<callback_system::CallbackParameter*>& input parameters`.
        //
        // To access named input variables:
        // `datatypes::AnyValue* some_any_value = callback_object->get_any_value("foo");`
        // where `"foo"` is the variable name.
        //
        // To access input variables without name (this works for named input variables too):
        // `datatypes::AnyValue* some_any_value = input_parameters.at(foo)->get_any_value();`
        // where `foo` is the zero-based index of the variable. First `CallbackParameter` of
        // a `CallbackObject` gets index 0, second `CallbackParameter` gets index 1, etc.

        std::shared_ptr<datatypes::AnyValue> any_value_universe = std::make_shared<datatypes::AnyValue>(*callback_object->get_arg(0));

        if (any_value_universe == nullptr)
        {
            std::cerr << "Error: universe not found!\n";
            return nullptr;
        }

        if (any_value_universe->type != datatypes::UNIVERSE_POINTER)
        {
            std::cerr << "Invalid datatype: " << any_value_universe->type << ", should be " << datatypes::UNIVERSE_POINTER << "\n";
            return nullptr;
        }

        ontology::Universe* universe = any_value_universe->universe;

        if (universe == nullptr)
        {
            std::cerr << "Error: universe is nullptr!\n";
            return nullptr;
        }

        std::shared_ptr<datatypes::AnyValue> any_value_entity_string = std::make_shared<datatypes::AnyValue>(*callback_object->get_arg(1));

        if (any_value_entity_string == nullptr)
        {
            std::cerr << "Error: entity_string not found!\n";
            return nullptr;
        }

        if (any_value_entity_string->type != datatypes::STD_STRING_POINTER)
        {
            std::cerr << "Invalid datatype: " << any_value_entity_string->type << ", should be " << datatypes::STD_STRING_POINTER << "\n";
            return nullptr;
        }

        std::string* entity_string_pointer = any_value_entity_string->std_string_pointer;

        if (entity_string_pointer == nullptr)
        {
            return nullptr;
        }

        std::string entity_string = *entity_string_pointer;

        ontology::Entity* entity = universe->get_entity(entity_string);

        if (entity == nullptr)
        {
            return nullptr;
        }

        delete entity;

        return nullptr;
    }

    std::shared_ptr<datatypes::AnyValue> switch_to_new_material(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>&)
    {
        std::shared_ptr<datatypes::AnyValue> any_value_universe = std::make_shared<datatypes::AnyValue>(*callback_object->get_arg(0));

        if (any_value_universe == nullptr)
        {
            std::cerr << "Error: universe not found!\n";
            return nullptr;
        }

        if (any_value_universe->type != datatypes::UNIVERSE_POINTER)
        {
            std::cerr << "Invalid datatype: " << any_value_universe->type << ", should be " << datatypes::UNIVERSE_POINTER << "\n";
            return nullptr;
        }

        ontology::Universe* universe = any_value_universe->universe;

        if (universe == nullptr)
        {
            std::cerr << "Error: universe is nullptr!\n";
            return nullptr;
        }

        std::shared_ptr<datatypes::AnyValue> any_value_entity_string = std::make_shared<datatypes::AnyValue>(*callback_object->get_arg(1));

        if (any_value_entity_string == nullptr)
        {
            std::cerr << "Error: entity_string not found!\n";
            return nullptr;
        }

        if (any_value_entity_string->type != datatypes::STD_STRING_POINTER)
        {
            std::cerr << "Invalid datatype: " << any_value_entity_string->type << ", should be " << datatypes::STD_STRING_POINTER << "\n";
            return nullptr;
        }

        std::string* entity_string_pointer = any_value_entity_string->std_string_pointer;

        if (entity_string_pointer == nullptr)
        {
            return nullptr;
        }

        std::string entity_string = *entity_string_pointer;

        ontology::Entity* entity = universe->get_entity(entity_string);

        if (entity == nullptr)
        {
            return nullptr;
        }

        ontology::Species* species = dynamic_cast<ontology::Species*>(entity);

        if (species == nullptr)
        {
            return nullptr;
        }

        ontology::Entity* old_material_entity = species->get_parent();

        ontology::Material* old_material = dynamic_cast<ontology::Material*>(old_material_entity);

        if (old_material == nullptr)
        {
            return nullptr;
        }

        std::shared_ptr<datatypes::AnyValue> any_value_material_string = std::make_shared<datatypes::AnyValue>(*callback_object->get_arg(2));

        if (any_value_material_string == nullptr)
        {
            std::cerr << "Error: material_string not found!\n";
            return nullptr;
        }

        if (any_value_material_string->type != datatypes::STD_STRING_POINTER)
        {
            std::cerr << "Invalid datatype: " << any_value_material_string->type << ", should be " << datatypes::STD_STRING_POINTER << "\n";
            return nullptr;
        }

        std::string* new_material_string_pointer = any_value_material_string->std_string_pointer;

        if (new_material_string_pointer == nullptr)
        {
            return nullptr;
        }

        std::string new_material_string = *new_material_string_pointer;

        ontology::Entity* new_material_entity = universe->get_entity(new_material_string);

        if (new_material_entity == nullptr)
        {
            return nullptr;
        }

        ontology::Material* new_material = dynamic_cast<ontology::Material*>(new_material_entity);

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

    std::shared_ptr<datatypes::AnyValue> transform_into_new_species(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject* callback_object,
            std::vector<callback_system::CallbackParameter*>&)
    {
        std::shared_ptr<datatypes::AnyValue> any_value_universe = std::make_shared<datatypes::AnyValue>(*callback_object->get_arg(0));

        if (any_value_universe == nullptr)
        {
            std::cerr << "Error: universe not found!\n";
            return nullptr;
        }

        if (any_value_universe->type != datatypes::UNIVERSE_POINTER)
        {
            std::cerr << "Invalid datatype: " << any_value_universe->type << ", should be " << datatypes::UNIVERSE_POINTER << "\n";
            return nullptr;
        }

        ontology::Universe* universe = any_value_universe->universe;

        if (universe == nullptr)
        {
            std::cerr << "Error: universe is nullptr!\n";
            return nullptr;
        }

        std::shared_ptr<datatypes::AnyValue> any_value_entity_string = std::make_shared<datatypes::AnyValue>(*callback_object->get_arg(1));

        if (any_value_entity_string == nullptr)
        {
            std::cerr << "Error: entity_string not found!\n";
            return nullptr;
        }

        if (any_value_entity_string->type != datatypes::STD_STRING_POINTER)
        {
            std::cerr << "Invalid datatype: " << any_value_entity_string->type << ", should be " << datatypes::STD_STRING_POINTER << "\n";
            return nullptr;
        }

        std::string* entity_string_pointer = any_value_entity_string->std_string_pointer;

        if (entity_string_pointer == nullptr)
        {
            return nullptr;
        }

        std::string entity_string = *entity_string_pointer;

        ontology::Entity* entity = universe->get_entity(entity_string);

        if (entity == nullptr)
        {
            return nullptr;
        }

        ontology::Object* object = dynamic_cast<ontology::Object*>(entity);

        if (object == nullptr)
        {
            return nullptr;
        }

        ontology::Entity* old_species_entity = object->get_parent();

        ontology::Species* old_species = dynamic_cast<ontology::Species*>(old_species_entity);

        if (old_species == nullptr)
        {
            return nullptr;
        }

        std::shared_ptr<datatypes::AnyValue> any_value_species_string = std::make_shared<datatypes::AnyValue>(*callback_object->get_arg(2));

        if (any_value_species_string == nullptr)
        {
            std::cerr << "Error: species_string not found!\n";
            return nullptr;
        }

        if (any_value_species_string->type != datatypes::STD_STRING_POINTER)
        {
            std::cerr << "Invalid datatype: " << any_value_species_string->type << ", should be " << datatypes::STD_STRING_POINTER << "\n";
            return nullptr;
        }

        std::string* new_species_string_pointer = any_value_species_string->std_string_pointer;

        if (new_species_string_pointer == nullptr)
        {
            return nullptr;
        }

        std::string new_species_string = *new_species_string_pointer;

        ontology::Entity* new_species_entity = universe->get_entity(new_species_string);

        if (new_species_entity == nullptr)
        {
            return nullptr;
        }

        ontology::Species* new_species = dynamic_cast<ontology::Species*>(new_species_entity);

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

