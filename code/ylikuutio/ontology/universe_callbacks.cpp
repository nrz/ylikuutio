// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2024 Antti Nuortimo.
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
#include "console.hpp"
#include "code/ylikuutio/core/application.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/map/ylikuutio_map.hpp"
#include "code/ylikuutio/memory/generic_memory_system.hpp"
#include "code/ylikuutio/opengl/opengl.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <cstdint>  // std::uintptr_t
#include <cstddef>  // std::size_t
#include <ios>      // std::hex
#include <optional> // std::optional
#include <sstream>  // std::stringstream
#include <string>   // std::string
#include <utility>  // std::pair
#include <vector>   // std::vector

namespace yli::ontology
{
    // Public callbacks.

    // Public `Entity` create callbacks.

    // Public `Entity` delete callbacks.

    std::optional<yli::data::AnyValue> Universe::delete_entity(
            yli::ontology::Universe& universe,
            yli::ontology::Entity& entity)
    {
        if (entity.get_can_be_erased())
        {
            yli::ontology::Entity* const entity_parent_of_entity = entity.get_parent();

            if (entity_parent_of_entity != nullptr)
            {
                // Erase the local name.
                entity_parent_of_entity->registry.erase_entity(entity.get_local_name());
            }

            // Erase the global name.
            universe.registry.erase_entity(entity.get_global_name());

            // Destroy the `Entity`.
            universe.application.get_memory_system().destroy(entity.get_constructible_module());
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
            yli::ontology::Universe& universe,
            const std::vector<std::string>& command_parameters)
    {
        // Command parameters must form a valid YliLisp expression.

        std::string expression;

        for (std::vector<std::string>::const_iterator it = command_parameters.begin(); it != command_parameters.end(); )
        {
            expression += *it;

            if (++it != command_parameters.end())
            {
                expression += " ";
            }
        }

        const std::string result = universe.eval_string(expression);
        console.print_text(result);

        return std::nullopt;
    }

    // Public data printing callbacks.

    std::optional<yli::data::AnyValue> Universe::info0(
            const yli::ontology::Universe& universe,
            yli::ontology::Console& console)
    {
        // Print names of named entities.
        yli::map::print_keys_to_console(universe.registry.get_entity_map(), console);
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Universe::info1(
            const yli::ontology::Universe& /* universe */,
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
