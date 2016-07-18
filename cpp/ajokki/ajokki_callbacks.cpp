#include "ajokki_callbacks.hpp"
#include "cpp/ylikuutio/callback/callback_parameter.hpp"
#include "cpp/ylikuutio/callback/callback_object.hpp"
#include "cpp/ylikuutio/callback/callback_engine.hpp"
#include "cpp/ylikuutio/common/any_value.hpp"
#include "cpp/ylikuutio/ontology/text2D.hpp"
#include "cpp/ylikuutio/ontology/object.hpp"
#include "cpp/ylikuutio/ontology/species.hpp"
#include "cpp/ylikuutio/ontology/material.hpp"
#include "cpp/ylikuutio/ontology/universe.hpp"

// Include GLFW
#ifndef __GLFW3_H_INCLUDED
#define __GLFW3_H_INCLUDED
#include <glfw3.h>
#endif

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
#include <vector>   // std::vector

namespace ajokki
{
    datatypes::AnyValue* glfwTerminate_cleanup(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*> input_parameters)
    {
        glfwTerminate();
        return nullptr;
    }

    datatypes::AnyValue* full_cleanup(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*> input_parameters)
    {
        std::cout << "Cleaning up.\n";

        if (input_parameters.size() != 1)
        {
            std::cerr << "Invalid size of input_parameters: " << input_parameters.size() << ", should be 1.\n";
        }
        else
        {
            datatypes::AnyValue* any_value_void_pointer = input_parameters.at(0)->get_any_value();
            if (any_value_void_pointer->type == datatypes::VOID_POINTER)
            {
                delete static_cast<ontology::Universe*>(any_value_void_pointer->void_pointer);
            }
            else
            {
                std::cerr << "Invalid datatype: " << any_value_void_pointer->type << ", should be " << datatypes::VOID_POINTER << "\n";
            }
        }

        // Delete the text's VBO, the shader and the texture
        text2D::cleanupText2D();

        // Close OpenGL window and terminate GLFW
        glfwTerminate();
        return nullptr;
    }

    datatypes::AnyValue* delete_suzanne_species(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*> input_parameters)
    {
        datatypes::AnyValue* any_value_bool_pointer = input_parameters.at(1)->get_any_value();

        if (any_value_bool_pointer->type != datatypes::BOOL_POINTER)
        {
            // `any_value_bool_pointer` was not `bool*`.
            return nullptr;
        }

        // OK, `any_value_bool_pointer` is a `bool*`.
        bool* does_suzanne_species_exist = any_value_bool_pointer->bool_pointer;

        if (*does_suzanne_species_exist)
        {
            ontology::Species* species = static_cast<ontology::Species*>(input_parameters.at(0)->get_any_value()->void_pointer);
            delete species;

            *does_suzanne_species_exist = false;
        }
        return nullptr;
    }

    datatypes::AnyValue* switch_to_new_material(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*> input_parameters)
    {
        bool* does_suzanne_species_exist = static_cast<bool*>(input_parameters.at(2)->get_any_value()->void_pointer);
        bool* does_suzanne_species_have_original_texture = static_cast<bool*>(input_parameters.at(3)->get_any_value()->void_pointer);
        bool* does_suzanne_species_have_new_texture = static_cast<bool*>(input_parameters.at(4)->get_any_value()->void_pointer);

        if (*does_suzanne_species_exist && *does_suzanne_species_have_original_texture)
        {
            ontology::Species* species = static_cast<ontology::Species*>(input_parameters.at(0)->get_any_value()->void_pointer);
            ontology::Material* material = static_cast<ontology::Material*>(input_parameters.at(1)->get_any_value()->void_pointer);
            species->bind_to_new_parent(material);

            *does_suzanne_species_have_original_texture = false;
            *does_suzanne_species_have_new_texture = true;
        }
        return nullptr;
    }

    datatypes::AnyValue* transform_into_new_species(
            callback_system::CallbackEngine*,
            callback_system::CallbackObject*,
            std::vector<callback_system::CallbackParameter*> input_parameters)
    {
        bool* does_suzanne_species_exist = static_cast<bool*>(input_parameters.at(2)->get_any_value()->void_pointer);
        bool* does_suzanne_species_belong_to_original_species = static_cast<bool*>(input_parameters.at(3)->get_any_value()->void_pointer);
        bool* does_suzanne_species_belong_to_new_species = static_cast<bool*>(input_parameters.at(4)->get_any_value()->void_pointer);

        if (*does_suzanne_species_exist && *does_suzanne_species_belong_to_original_species)
        {
            ontology::Object* object = static_cast<ontology::Object*>(input_parameters.at(0)->get_any_value()->void_pointer);
            ontology::Species* species = static_cast<ontology::Species*>(input_parameters.at(1)->get_any_value()->void_pointer);
            object->bind_to_new_parent(species);

            *does_suzanne_species_belong_to_original_species = false;
            *does_suzanne_species_belong_to_new_species = true;
        }
        return nullptr;
    }
}

