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

#include "entity.hpp"
#include "universe.hpp"
#include "brain.hpp"
#include "movable.hpp"
#include "scene.hpp"
#include "shader.hpp"
#include "material.hpp"
#include "species.hpp"
#include "symbiosis.hpp"
#include "font_2d.hpp"
#include "console.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/map/ylikuutio_map.hpp"
#include "code/ylikuutio/opengl/opengl.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <cstdint>  // std::uintptr_t
#include <cstddef>  // std::size_t
#include <ios>      // std::defaultfloat, std::dec, std::fixed, std::hex, std::ios
#include <iostream> // std::cout, std::cin, std::cerr
#include <optional> // std::optional
#include <sstream>  // std::istringstream, std::ostringstream, std::stringstream
#include <string>   // std::string, std::getline
#include <utility>  // std::pair
#include <vector>   // std::vector

namespace yli::ontology
{
    // Public callbacks.

    // Public `Entity` bind callbacks.

    std::optional<yli::data::AnyValue> Universe::bind(
            yli::ontology::Universe& universe,
            yli::ontology::Entity& child_or_apprentice_entity,
            yli::ontology::Entity& parent_or_master_entity)
    {
        yli::ontology::Shader* const child_or_apprentice_shader = dynamic_cast<yli::ontology::Shader*>(&child_or_apprentice_entity);
        yli::ontology::Scene* const parent_or_master_scene = dynamic_cast<yli::ontology::Scene*>(&parent_or_master_entity);

        yli::ontology::Material* const child_or_apprentice_material = dynamic_cast<yli::ontology::Material*>(&child_or_apprentice_entity);
        yli::ontology::Symbiosis* const child_or_apprentice_symbiosis = dynamic_cast<yli::ontology::Symbiosis*>(&child_or_apprentice_entity);
        yli::ontology::Shader* const parent_or_master_shader = dynamic_cast<yli::ontology::Shader*>(&parent_or_master_entity);

        yli::ontology::Species* const child_or_apprentice_species = dynamic_cast<yli::ontology::Species*>(&child_or_apprentice_entity);
        yli::ontology::Material* const parent_or_master_material = dynamic_cast<yli::ontology::Material*>(&parent_or_master_entity);

        yli::ontology::Movable* const child_or_apprentice_movable = dynamic_cast<yli::ontology::Movable*>(&child_or_apprentice_entity);
        yli::ontology::Brain* const parent_or_master_brain = dynamic_cast<yli::ontology::Brain*>(&parent_or_master_entity);

        yli::ontology::Console* const child_or_apprentice_console = dynamic_cast<yli::ontology::Console*>(&child_or_apprentice_entity);
        yli::ontology::Font2D* const parent_or_master_font_2d = dynamic_cast<yli::ontology::Font2D*>(&parent_or_master_entity);

        if (child_or_apprentice_shader != nullptr && parent_or_master_scene != nullptr)
        {
            child_or_apprentice_shader->bind_to_new_scene_parent(parent_or_master_scene);
        }
        else if (child_or_apprentice_material != nullptr && parent_or_master_shader != nullptr)
        {
            child_or_apprentice_material->bind_to_new_shader(parent_or_master_shader);
        }
        else if (child_or_apprentice_species != nullptr && parent_or_master_material != nullptr)
        {
            child_or_apprentice_species->bind_to_new_material(parent_or_master_material);
        }
        else if (child_or_apprentice_movable != nullptr && parent_or_master_brain != nullptr)
        {
            child_or_apprentice_movable->bind_to_new_brain(parent_or_master_brain);
        }
        else if (child_or_apprentice_symbiosis != nullptr && parent_or_master_shader != nullptr)
        {
            child_or_apprentice_symbiosis->bind_to_new_shader(parent_or_master_shader);
        }
        else if (child_or_apprentice_console != nullptr && parent_or_master_font_2d != nullptr)
        {
            child_or_apprentice_console->bind_to_new_font_2d(parent_or_master_font_2d);
        }
        else
        {
            child_or_apprentice_entity.bind_to_new_parent(&parent_or_master_entity);
        }

        return std::nullopt;
    }

    // Public `Entity` create callbacks.

    // Public `Entity` delete callbacks.

    std::optional<yli::data::AnyValue> Universe::delete_entity(
            yli::ontology::Universe& universe,
            yli::ontology::Entity& entity)
    {
        if (entity.get_can_be_erased())
        {
            yli::ontology::Entity* const parent = entity.get_parent();

            if (parent != nullptr)
            {
                // Erase the local name.
                parent->registry.erase_entity(entity.get_local_name());
            }

            // Erase the global name.
            universe.registry.erase_entity(entity.get_global_name());
            delete &entity;
        }

        return std::nullopt;
    }

    // Public `Entity` naming callbacks.

    std::optional<yli::data::AnyValue> Universe::set_global_name_for_entity(
            yli::ontology::Entity& entity,
            const std::string& global_name)
    {
        entity.set_global_name(global_name);

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Universe::set_local_name_for_entity(
            yli::ontology::Entity& entity,
            const std::string& local_name)
    {
        entity.set_local_name(local_name);

        return std::nullopt;
    }

    // Public `Entity` activate callbacks.

    std::optional<yli::data::AnyValue> Universe::activate_entity(yli::ontology::Entity& entity)
    {
        entity.activate();

        return std::nullopt;
    }

    // Public YliLisp-related callbacks.

    std::optional<yli::data::AnyValue> Universe::eval(
            yli::ontology::Console& console,
            yli::ontology::Entity& universe_entity,
            const std::vector<std::string>& command_parameters)
    {
        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(&universe_entity);

        if (universe == nullptr)
        {
            return std::nullopt;
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
        console.print_text(result);

        return std::nullopt;
    }

    // Public data printing callbacks.

    std::optional<yli::data::AnyValue> Universe::info0(
            const yli::ontology::Universe& universe,
            yli::ontology::Console& console)
    {
        // Print names of named entities.
        yli::map::print_keys_to_console(universe.registry.get_entity_map(), &console);
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Universe::info1(
            const yli::ontology::Universe& universe,
            yli::ontology::Console& console,
            const yli::ontology::Entity& entity)
    {
        // OK, let's find out information about this `Entity`.

        console.print_text(entity.get_type());

        const std::uintptr_t memory_address = reinterpret_cast<std::uintptr_t>(&entity);
        std::stringstream memory_address_stringstream;
        memory_address_stringstream << "0x" << std::hex << memory_address;

        const std::string entity_info = "memory address:   " + memory_address_stringstream.str();
        console.print_text(entity_info);

        if (entity.get_parent() == nullptr)
        {
            console.print_text("parent's address: nullptr");
        }
        else
        {
            std::uintptr_t parents_memory_address = reinterpret_cast<std::uintptr_t>(entity.get_parent());
            std::stringstream parents_memory_address_stringstream;
            parents_memory_address_stringstream << "0x" << std::hex << parents_memory_address;

            std::string parent_info = "parent's address: ";
            parent_info += parents_memory_address_stringstream.str();
            console.print_text(parent_info);
        }

        std::size_t number_of_children = entity.get_number_of_all_children();
        std::stringstream number_of_children_stringstream;
        number_of_children_stringstream << number_of_children;

        std::string children_info = "number of children: ";
        children_info += number_of_children_stringstream.str();
        console.print_text(children_info);

        std::size_t number_of_descendants = entity.get_number_of_all_descendants();
        std::stringstream number_of_descendants_stringstream;
        number_of_descendants_stringstream << number_of_descendants;

        std::string descendants_info = "number of descendants: ";
        descendants_info += number_of_descendants_stringstream.str();
        console.print_text(descendants_info);

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Universe::print_entities(
            const yli::ontology::Universe& universe,
            yli::ontology::Console& console)
    {
        std::vector<std::pair<std::string, yli::ontology::Entity*>> key_and_value_vector = yli::map::get_keys_and_values(universe.registry.get_entity_map());

        for (auto& [key, value] : key_and_value_vector)
        {
            const std::uintptr_t memory_address = reinterpret_cast<std::uintptr_t>(value);
            std::stringstream memory_address_stringstream;
            memory_address_stringstream << " 0x" << std::hex << memory_address;

            const std::string entity_info = key + memory_address_stringstream.str();
            console.print_text(entity_info);
        }

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Universe::print_parent(
            const yli::ontology::Universe&,
            yli::ontology::Console& console,
            const yli::ontology::Entity& entity)
    {
        // OK, let's find out the parent of this `Entity`.

        if (entity.get_parent() == nullptr)
        {
            console.print_text("parent's address: nullptr");
        }
        else
        {
            std::uintptr_t parents_memory_address = reinterpret_cast<std::uintptr_t>(entity.get_parent());
            std::stringstream parents_memory_address_stringstream;
            parents_memory_address_stringstream << "0x" << std::hex << parents_memory_address;

            std::string parent_info = "parent's address: ";
            parent_info += parents_memory_address_stringstream.str();
            console.print_text(parent_info);
        }

        return std::nullopt;
    }

    // Other public callbacks.

    std::optional<yli::data::AnyValue> Universe::screenshot(
            yli::ontology::Universe& universe,
            const std::string& filename)
    {
        if (!universe.framebuffer_module.get_in_use())
        {
            return std::nullopt;
        }

        // https://learnopengl.com/Advanced-OpenGL/Framebuffers

        const std::size_t texture_width = universe.framebuffer_module.get_texture_width();
        const std::size_t texture_height = universe.framebuffer_module.get_texture_height();

        if (!universe.framebuffer_module.get_is_initialized())
        {
            universe.framebuffer_module.create_framebuffer_object();
        }

        universe.framebuffer_module.bind();

        if (!universe.framebuffer_module.get_is_initialized())
        {
            universe.framebuffer_module.initialize(universe.background_red, universe.background_green, universe.background_blue, universe.background_alpha);
        }

        // Clear the framebuffer.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Adjust viewport for the framebuffer.
        glViewport(0, 0, texture_width, texture_height);
        universe.render_without_changing_depth_test(); // Render to framebuffer.

        // Transfer data from the GPU texture to a CPU array and save into a file.
        const bool should_flip_texture = true;
        yli::opengl::save_data_from_gpu_texture_into_file(
                GL_RGB, GL_UNSIGNED_BYTE, texture_width, texture_height, filename, should_flip_texture);

        universe.restore_onscreen_rendering();

        return std::nullopt;
    }

    // Public callbacks end here.
}
