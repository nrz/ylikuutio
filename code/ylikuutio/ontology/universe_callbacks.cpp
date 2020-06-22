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

#include "universe.hpp"
#include "entity.hpp"
#include "scene.hpp"
#include "camera.hpp"
#include "movable.hpp"
#include "brain.hpp"
#include "console.hpp"
#include "any_value_entity.hpp"
#include "any_struct_entity.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/config/setting_master.hpp"
#include "code/ylikuutio/map/ylikuutio_map.hpp"
#include "code/ylikuutio/opengl/opengl.hpp"

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <cstddef>  // std::size_t
#include <ios>      // std::defaultfloat, std::dec, std::fixed, std::hex, std::ios
#include <iostream> // std::cout, std::cin, std::cerr
#include <memory>   // std::make_shared, std::shared_ptr
#include <sstream>  // std::istringstream, std::ostringstream, std::stringstream
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string, std::getline
#include <utility>  // std::pair
#include <vector>   // std::vector

namespace yli::ontology
{
    // Public callbacks.

    // Public `Entity` bind callbacks.

    std::shared_ptr<yli::data::AnyValue> Universe::bind(
            yli::ontology::Universe* const universe,
            yli::ontology::Entity* const child_or_apprentice_entity,
            yli::ontology::Entity* const parent_or_master_entity)
    {
        if (universe == nullptr || child_or_apprentice_entity == nullptr || parent_or_master_entity == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const child_or_apprentice_movable = dynamic_cast<yli::ontology::Movable*>(child_or_apprentice_entity);
        yli::ontology::Brain* const parent_or_master_brain = dynamic_cast<yli::ontology::Brain*>(parent_or_master_entity);

        if (child_or_apprentice_movable != nullptr && parent_or_master_brain != nullptr)
        {
            child_or_apprentice_movable->bind_to_new_brain(parent_or_master_brain);
        }
        else
        {
            child_or_apprentice_entity->bind_to_new_parent(parent_or_master_entity);
        }

        return nullptr;
    }

    // Public `Entity` create callbacks.

    std::shared_ptr<yli::data::AnyValue> Universe::create_any_value_entity(
            yli::ontology::Universe* const universe,
            std::shared_ptr<std::string> variable_name_shared_ptr,
            std::shared_ptr<std::string> variable_type_shared_ptr,
            std::shared_ptr<std::string> value_string_shared_ptr)
    {
        // usage:
        // `AnyValue <variable_name> <variable_type> <variable_value>`
        //
        // eg.
        // `AnyValue my_pi float 3.1415927`.

        if (universe == nullptr || variable_name_shared_ptr == nullptr || variable_type_shared_ptr == nullptr || value_string_shared_ptr == nullptr)
        {
            return nullptr;
        }

        if (variable_name_shared_ptr->empty())
        {
            return nullptr;
        }

        if (universe->is_entity(*variable_name_shared_ptr))
        {
            return nullptr;
        }

        // OK, variable name is not empty and it is not in use yet either.

        if (variable_type_shared_ptr->empty())
        {
            return nullptr;
        }

        if (value_string_shared_ptr->empty())
        {
            return nullptr;
        }

        std::shared_ptr<yli::data::AnyValue> any_value = std::make_shared<yli::data::AnyValue>(*variable_type_shared_ptr, *value_string_shared_ptr);
        yli::ontology::AnyValueEntity* const any_value_entity = new yli::ontology::AnyValueEntity(universe, any_value);
        any_value_entity->set_global_name(*variable_name_shared_ptr);
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Universe::create_any_struct_entity(
            yli::ontology::Universe* const universe,
            std::shared_ptr<std::string> variable_name_shared_ptr)
    {
        // usage:
        // `AnyStruct <variable_name>`
        //
        // eg.
        // `AnyValue my_struct`.

        if (universe == nullptr || variable_name_shared_ptr == nullptr)
        {
            return nullptr;
        }

        if (variable_name_shared_ptr->empty())
        {
            // Somehow variable name is empty!
            return nullptr;
        }

        if (universe->is_entity(*variable_name_shared_ptr))
        {
            // Variable name is in use already!
            return nullptr;
        }

        // OK, variable name is not empty and it is not in use yet either.

        yli::ontology::AnyStructEntity* const any_struct_entity = new yli::ontology::AnyStructEntity(universe);
        any_struct_entity->set_global_name(*variable_name_shared_ptr);
        return nullptr;
    }

    // Public `Entity` delete callbacks.

    std::shared_ptr<yli::data::AnyValue> Universe::delete_entity(
            yli::ontology::Universe* const universe,
            yli::ontology::Entity* const entity)
    {
        if (universe == nullptr || entity == nullptr)
        {
            return nullptr;
        }

        yli::config::SettingMaster* setting_master = universe->get_setting_master();

        if (setting_master == nullptr)
        {
            return nullptr;
        }

        if (entity->get_can_be_erased())
        {
            universe->entity_map.erase(entity->get_global_name());
            delete entity;
        }

        return nullptr;
    }

    // Public `Entity` naming callbacks.

    std::shared_ptr<yli::data::AnyValue> Universe::set_global_name_for_entity(
            yli::ontology::Universe* const universe,
            yli::ontology::Entity* const entity,
            std::shared_ptr<std::string> global_name)
    {
        if (universe == nullptr || entity == nullptr || global_name == nullptr)
        {
            return nullptr;
        }

        entity->set_global_name(*global_name);

        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Universe::set_local_name_for_entity(
            yli::ontology::Universe* const universe,
            yli::ontology::Entity* const entity,
            std::shared_ptr<std::string> local_name)
    {
        if (universe == nullptr || entity == nullptr || local_name == nullptr)
        {
            return nullptr;
        }

        entity->set_local_name(*local_name);

        return nullptr;
    }

    // Public `Entity` activate callbacks.

    std::shared_ptr<yli::data::AnyValue> Universe::activate(
            yli::ontology::Universe* const universe,
            yli::ontology::Entity* const entity)
    {
        // This function can be used to activate a `Scene`, a `Camera`, or a `Console`.

        if (universe == nullptr || entity == nullptr)
        {
            return nullptr;
        }

        yli::config::SettingMaster* setting_master = universe->get_setting_master();

        if (setting_master == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Scene* const scene = dynamic_cast<yli::ontology::Scene*>(entity);
        yli::ontology::Camera* const camera = dynamic_cast<yli::ontology::Camera*>(entity);
        yli::ontology::Console* const console = dynamic_cast<yli::ontology::Console*>(entity);

        uint32_t number_of_entity_types = 0;
        number_of_entity_types += scene != nullptr ? 1 : 0;
        number_of_entity_types += camera != nullptr ? 1 : 0;
        number_of_entity_types += console != nullptr ? 1 : 0;

        if (number_of_entity_types != 1)
        {
            // The named `Entity` is neither a `Scene`, a `Camera`, nor a `Console`.
            return nullptr;
        }

        if (scene != nullptr)
        {
            // The named `Entity` is a `Scene`.
            universe->set_active_scene(scene);
        }
        else if (camera != nullptr)
        {
            // The named `Entity` is a `Camera`.
            universe->set_active_camera(camera);
        }
        else if (console != nullptr)
        {
            // The named `Entity` is a `Console`.
            if (universe->get_active_console() != nullptr)
            {
                universe->get_active_console()->exit_console();
            }

            universe->set_active_console(console);
            console->enter_console();
        }

        return nullptr;
    }

    // Public AngelScript-related callbacks.

    std::shared_ptr<yli::data::AnyValue> Universe::eval(
            yli::ontology::Console* const console,
            yli::ontology::Entity* const universe_entity,
            const std::vector<std::string>& command_parameters)
    {
        if (universe_entity == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(universe_entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        // Command parameters must form a valid AngelScript expression.

        std::string expression;

        for (std::vector<std::string>::const_iterator it = command_parameters.begin(); it != command_parameters.end(); )
        {
            expression += *it;

            if (++it != command_parameters.end())
            {
                expression += " ";
            }
        }

        const std::string result = universe->eval_string(expression);

        if (console != nullptr)
        {
            console->print_text(result);
        }

        return nullptr;
    }

    // Public data printing callbacks.

    std::shared_ptr<yli::data::AnyValue> Universe::info0(
            yli::ontology::Universe* const universe,
            yli::ontology::Console* const console)
    {
        if (console == nullptr || universe == nullptr)
        {
            return nullptr;
        }

        // Print names of named entities.
        yli::map::print_keys_to_console(universe->entity_map, console);
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Universe::info1(
            yli::ontology::Universe* const universe,
            yli::ontology::Console* const console,
            yli::ontology::Entity* const entity)
    {
        if (console == nullptr || universe == nullptr || entity == nullptr)
        {
            return nullptr;
        }

        // OK, let's find out information about this `Entity`.

        console->print_text(entity->get_type());

        uint64_t memory_address = reinterpret_cast<uint64_t>((void*) entity);
        std::stringstream memory_address_stringstream;
        memory_address_stringstream << "0x" << std::hex << memory_address;

        std::string entity_info = "memory address:   ";
        entity_info += memory_address_stringstream.str();
        console->print_text(entity_info);

        if (entity->get_parent() == nullptr)
        {
            console->print_text("parent's address: nullptr");
        }
        else
        {
            uint64_t parents_memory_address = reinterpret_cast<uint64_t>((void*) entity->get_parent());
            std::stringstream parents_memory_address_stringstream;
            parents_memory_address_stringstream << "0x" << std::hex << parents_memory_address;

            std::string parent_info = "parent's address: ";
            parent_info += parents_memory_address_stringstream.str();
            console->print_text(parent_info);
        }

        std::size_t number_of_children = entity->get_number_of_children();
        std::stringstream number_of_children_stringstream;
        number_of_children_stringstream << number_of_children;

        std::string children_info = "number of children: ";
        children_info += number_of_children_stringstream.str();
        console->print_text(children_info);

        std::size_t number_of_descendants = entity->get_number_of_descendants();
        std::stringstream number_of_descendants_stringstream;
        number_of_descendants_stringstream << number_of_descendants;

        std::string descendants_info = "number of descendants: ";
        descendants_info += number_of_descendants_stringstream.str();
        console->print_text(descendants_info);

        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Universe::print_entities(
            yli::ontology::Universe* const universe,
            yli::ontology::Console* const console)
    {
        if (universe == nullptr || console == nullptr)
        {
            return nullptr;
        }

        std::vector<std::pair<std::string, yli::ontology::Entity*>> key_and_value_vector = yli::map::get_keys_and_values(universe->entity_map);

        for (auto key_and_value : key_and_value_vector)
        {
            uint64_t memory_address = reinterpret_cast<uint64_t>((void*) key_and_value.second); // value.
            std::stringstream memory_address_stringstream;
            memory_address_stringstream << " 0x" << std::hex << memory_address;

            std::string entity_info = key_and_value.first; // key.
            entity_info += memory_address_stringstream.str();
            console->print_text(entity_info);
        }

        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Universe::print_parent(
            yli::ontology::Universe* const universe,
            yli::ontology::Console* const console,
            yli::ontology::Entity* const entity)
    {
        if (universe == nullptr || console == nullptr || entity == nullptr)
        {
            return nullptr;
        }

        // OK, let's find out the parent of this `Entity`.

        if (entity->get_parent() == nullptr)
        {
            console->print_text("parent's address: nullptr");
        }
        else
        {
            uint64_t parents_memory_address = reinterpret_cast<uint64_t>((void*) entity->get_parent());
            std::stringstream parents_memory_address_stringstream;
            parents_memory_address_stringstream << "0x" << std::hex << parents_memory_address;

            std::string parent_info = "parent's address: ";
            parent_info += parents_memory_address_stringstream.str();
            console->print_text(parent_info);
        }

        return nullptr;
    }

    // Other public callbacks.

    std::shared_ptr<yli::data::AnyValue> Universe::screenshot(
            yli::ontology::Universe* const universe,
            std::shared_ptr<std::string> filename)
    {
        if (universe == nullptr || filename == nullptr)
        {
            return nullptr;
        }

        // https://learnopengl.com/Advanced-OpenGL/Framebuffers

        const std::size_t texture_width = universe->framebuffer_width;
        const std::size_t texture_height = universe->framebuffer_height;

        if (!universe->is_framebuffer_initialized)
        {
            // Create an FBO (off-screen framebuffer object).
            glGenFramebuffers(1, &universe->framebuffer);
        }

        // Bind the offscreen buffer.
        glBindFramebuffer(GL_FRAMEBUFFER, universe->framebuffer);

        if (!universe->is_framebuffer_initialized)
        {
            // Create a texture.
            glGenTextures(1, &universe->texture);
            glBindTexture(GL_TEXTURE_2D, universe->texture);

            // Define the texture.
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture_width, texture_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

            yli::opengl::set_filtering_parameters();

            // Attach the texture.
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, universe->texture, 0);

            // Create and bind a render buffer with depth and stencil attachments.
            glGenRenderbuffers(1, &universe->renderbuffer);
            glBindRenderbuffer(GL_RENDERBUFFER, universe->renderbuffer);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, texture_width, texture_height);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, universe->renderbuffer);

            if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            {
                std::cerr << "ERROR: `Universe::screenshot`: framebuffer is not complete!\n";
            }

            // Set background color for the framebuffer.
            universe->set_opengl_background_color();

            universe->is_framebuffer_initialized = true;
        }

        // Clear the framebuffer.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Adjust viewport for the framebuffer.
        glViewport(0, 0, texture_width, texture_height);
        universe->render_without_changing_depth_test(); // Render to framebuffer.

        // Transfer data from the GPU texture to a CPU array and save into a file.
        const bool should_ylikuutio_flip_texture = true;
        yli::opengl::save_data_from_gpu_texture_into_file(
                GL_RGB, GL_UNSIGNED_BYTE, texture_width, texture_height, *filename, should_ylikuutio_flip_texture);

        universe->restore_onscreen_rendering();

        return nullptr;
    }

    // Public callbacks end here.
}
