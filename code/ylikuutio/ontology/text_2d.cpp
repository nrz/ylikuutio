// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2025 Antti Nuortimo.
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

#include "text_2d.hpp"
#include "universe.hpp"
#include "font_2d.hpp"
#include "horizontal_alignment.hpp"
#include "vertical_alignment.hpp"
#include "text_struct.hpp"
#include "print_text_struct.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>   // std::size_t
#include <iostream>  // std::cout, std::cerr
#include <optional>  // std::optional
#include <stdexcept> // std::runtime_error
#include <string>    // std::string
#include <variant>   // std::holds_alternative
#include <vector>    // std::vector

namespace yli::core
{
    class Application;
}

namespace yli::ontology
{
    class Entity;
    class Scene;

    std::optional<yli::data::AnyValue> Text2d::bind_to_new_font_2d_parent(
            Text2d& text_2d,
            Font2d& new_parent)
    {
        // Set pointer to `text_2d` to `nullptr`, set parent according to the input,
        // and request a new childID from `new_parent`.

        const Entity* const old_font_2d_parent = text_2d.get_parent();

        if (old_font_2d_parent == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Text2d::bind_to_new_font_2d_parent`: `old_font_2d_parent` is `nullptr`!");
        }

        if (new_parent.has_child(text_2d.local_name))
        {
            std::cerr << "ERROR: `Text2d::bind_to_new_font_2d_parent`: local name is already in use!\n";
            return std::nullopt;
        }

        text_2d.child_of_font_2d.unbind_and_bind_to_new_parent(
                &new_parent.parent_of_text_2ds);

        return std::nullopt;
    }

    Text2d::Text2d(
            yli::core::Application& application,
            Universe& universe,
            const TextStruct& text_struct,
            GenericParentModule* const font_2d_parent_module)
        : Entity(application, universe, text_struct),
        child_of_font_2d(font_2d_parent_module, *this)
    {
        this->text = text_struct.text;
        this->position = text_struct.position;
        this->text_size = text_struct.text_size;
        this->font_size = text_struct.font_size;

        // If software rendering is in use, the vertices and UVs can not be loaded into GPU memory,
        // but they can still be loaded into CPU memory to be used by the software rendering.
        const bool should_load_vertices_and_uvs =
            this->universe.get_is_opengl_in_use() ||
            this->universe.get_is_vulkan_in_use() ||
            this->universe.get_is_software_rendering_in_use();

        if (this->get_parent() != nullptr && should_load_vertices_and_uvs)
        {
            // Initialize VAO.
            glGenVertexArrays(1, &this->vao);

            // Initialize VBO.
            glGenBuffers(1, &this->vertex_buffer);
            glGenBuffers(1, &this->uv_buffer);

            // Get a handle for our buffers.
            const Font2d* const font_2d_parent = static_cast<Font2d*>(this->get_parent());

            if (font_2d_parent != nullptr)
            {
                this->vertex_position_in_screenspace_id = glGetAttribLocation(
                        font_2d_parent->get_program_id(),
                        "vertex_position_screenspace");
                this->vertex_uv_id = glGetAttribLocation(font_2d_parent->get_program_id(), "vertex_uv");
            }

            this->vertices_and_uvs_loaded = true;
        }

        // `Entity` member variables begin here.
        this->type_string = "yli::ontology::Text2d*";
    }

    Text2d::~Text2d()
    {
        if (this->vertices_and_uvs_loaded)
        {
            // Delete buffers.
            glDeleteBuffers(1, &this->vertex_buffer);
            glDeleteBuffers(1, &this->uv_buffer);
        }
    }

    void Text2d::render()
    {
        PrintTextStruct text_struct { this->universe.get_font_size(), this->universe.get_window_width() / this->universe.get_font_size() };
        text_struct.position = this->position;
        text_struct.text = this->text;
        const Font2d* const font_2d_parent = static_cast<Font2d*>(this->get_parent());
        font_2d_parent->print_text_2d(text_struct);
    }

    Entity* Text2d::get_parent() const
    {
        return this->child_of_font_2d.get_parent();
    }

    Scene* Text2d::get_scene() const
    {
        const Entity* const font_2d_parent = this->get_parent();

        if (font_2d_parent == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Text2d::get_scene`: `font_2d_parent` is `nullptr`!");
        }

        return font_2d_parent->get_scene();
    }

    std::size_t Text2d::get_number_of_children() const
    {
        return 0; // `Text2d` has no children.
    }

    std::size_t Text2d::get_number_of_descendants() const
    {
        return 0; // `Text2d` has no children.
    }

    void Text2d::change_string(const std::string& text)
    {
        this->text = text;
    }
}
