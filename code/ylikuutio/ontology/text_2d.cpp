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
#include "texture_file_format.hpp"
#include "text_struct.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/opengl/opengl.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

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
        this->text = (std::holds_alternative<std::string>(text_struct.text) ?
                std::get<std::string>(text_struct.text) :
                ""); // TODO: add support for `std::vector<std::string>`!
        this->position = text_struct.position;
        this->text_size = text_struct.text_size;
        this->font_size = text_struct.font_size;

        // Initialize class members with some dummy values.
        this->vao                               = 0;
        this->vertex_buffer                     = 0;
        this->uvbuffer                          = 0;
        this->vertex_position_in_screenspace_id = 0;
        this->vertex_uv_id                      = 0;

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
            glGenBuffers(1, &this->uvbuffer);

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
            glDeleteBuffers(1, &this->uvbuffer);
        }
    }

    void Text2d::render()
    {
        if (!this->should_render || !this->universe.get_is_opengl_in_use())
        {
            return;
        }

        if (this->get_parent() == nullptr)
        {
            return;
        }

        // If horizontal alignment is `"left"`, each line begins from the same x coordinate.
        // If horizontal alignment is `"left"` and vertical alignment is `"top"`,
        // then there is no need to check the text beforehand for newlines.
        // Otherwise newlines need to be checked beforehand.
        //
        // If horizontal alignment is right, each line ends in the same x coordinate.
        // Newlines need to be checked beforehand.
        const std::size_t length = this->text.size();

        // Count the number of lines.
        std::size_t number_of_lines = 1;

        std::size_t i = 0;

        while (i < length)
        {
            char character = text[i++];

            if (i >= length)
            {
                // Backslash `\` is the last character of string.
                // End processing to avoid buffer over-read.
                break;
            }

            if (character == '\\')
            {
                // OK, this character was backslash, so read the next character.
                character = text[i++];

                if (character == 'n')
                {
                    number_of_lines++;
                }
            }
            else if (character == '\n')
            {
                number_of_lines++;
            }
        }

        std::size_t current_left_x;
        std::size_t current_top_y;

        if (this->position.horizontal_alignment == HorizontalAlignment::LEFT)
        {
            current_left_x = this->position.x;
        }
        else if (this->position.horizontal_alignment == HorizontalAlignment::HORIZONTAL_CENTER)
        {
            current_left_x = this->position.x - 0.5f * length * this->text_size;
        }
        else if (this->position.horizontal_alignment == HorizontalAlignment::RIGHT)
        {
            current_left_x = this->position.x - length * this->text_size;
        }
        else
        {
            std::cerr << "ERROR: `Text2d::render`: invalid horizontal alignment: " << this->position.horizontal_alignment << "\n";
            return;
        }

        if (this->position.vertical_alignment == VerticalAlignment::TOP)
        {
            current_top_y = this->position.y;
        }
        else if (this->position.vertical_alignment == VerticalAlignment::VERTICAL_CENTER)
        {
            current_top_y = this->position.y + 0.5f * number_of_lines * this->text_size;
        }
        else if (this->position.vertical_alignment == VerticalAlignment::BOTTOM)
        {
            current_top_y = this->position.y + number_of_lines * this->text_size;
        }
        else
        {
            std::cerr << "ERROR: `Text2d::render`: invalid vertical alignment: " << this->position.vertical_alignment << "\n";
            return;
        }

        // Fill buffers
        std::vector<glm::vec2> vertices;
        std::vector<glm::vec2> uvs;

        i = 0;

        while (i < length)
        {
            // Print to the right side of X (so far there is no check for input length).
            // Print up of Y.
            std::size_t vertex_up_left_x;
            std::size_t vertex_up_left_y;
            std::size_t vertex_up_right_x;
            std::size_t vertex_up_right_y;
            std::size_t vertex_down_left_x;
            std::size_t vertex_down_left_y;
            std::size_t vertex_down_right_x;
            std::size_t vertex_down_right_y;

            char character = text[i++];

            if (character == '\\')
            {
                // OK, this character was backslash, so read the next character.
                character = text[i++];

                if (i >= length)
                {
                    // Backslash `\` is the last character of string.
                    // End processing to avoid buffer over-read.
                    break;
                }

                if (character == 'n')
                {
                    // jump to the beginning of the next line.
                    // `"left"` horizontal alignment and `"top"` vertical alignment are assumed.
                    // TODO: implement newline for other horizontal and vertical alignments too!
                    current_left_x = this->position.x;
                    current_top_y -= this->text_size;
                    continue;
                }
            }
            else if (character == '\n')
            {
                // jump to the beginning of the next line.
                // `"left"` horizontal alignment and `"top"` vertical alignment are assumed.
                // TODO: implement newline for other horizontal and vertical alignments too!
                current_left_x = this->position.x;
                current_top_y -= this->text_size;
                continue;
            }

            vertex_up_left_x = vertex_down_left_x = current_left_x;
            vertex_up_right_x = vertex_down_right_x = current_left_x + this->text_size;
            current_left_x += this->text_size;

            vertex_down_left_y = vertex_down_right_y = current_top_y - this->text_size;
            vertex_up_left_y = vertex_up_right_y = current_top_y;

            glm::vec2 vertex_up_left = glm::vec2(vertex_up_left_x, vertex_up_left_y);
            glm::vec2 vertex_up_right = glm::vec2(vertex_up_right_x, vertex_up_right_y);
            glm::vec2 vertex_down_left = glm::vec2(vertex_down_left_x, vertex_down_left_y);
            glm::vec2 vertex_down_right = glm::vec2(vertex_down_right_x, vertex_down_right_y);

            vertices.emplace_back(vertex_up_left);
            vertices.emplace_back(vertex_down_left);
            vertices.emplace_back(vertex_up_right);

            vertices.emplace_back(vertex_down_right);
            vertices.emplace_back(vertex_up_right);
            vertices.emplace_back(vertex_down_left);

            float uv_x = (character % this->font_size) / static_cast<float>(this->font_size);
            float uv_y;

            const Font2d* const font_2d_parent = static_cast<Font2d*>(this->get_parent());

            const TextureFileFormat font_texture_file_format = font_2d_parent->get_font_texture_file_format();

            if (font_texture_file_format == TextureFileFormat::PNG)
            {
                uv_y = (character / this->font_size) / static_cast<float>(this->font_size);
            }
            else
            {
                std::cerr << "ERROR: `Text2d::render`: invalid `font_texture_file_format`!\n";
                return;
            }

            glm::vec2 uv_up_left = glm::vec2(uv_x, uv_y);
            glm::vec2 uv_up_right = glm::vec2(uv_x + (1.0f / static_cast<float>(this->font_size)), uv_y);
            glm::vec2 uv_down_right;
            glm::vec2 uv_down_left;

            if (font_texture_file_format == TextureFileFormat::PNG)
            {
                uv_down_right = glm::vec2(
                        uv_x + (1.0f / static_cast<float>(this->font_size)),
                        (uv_y + 1.0f / static_cast<float>(this->font_size)));
                uv_down_left = glm::vec2(uv_x, (uv_y + 1.0f / static_cast<float>(this->font_size)));
            }

            uvs.emplace_back(uv_up_left);
            uvs.emplace_back(uv_down_left);
            uvs.emplace_back(uv_up_right);

            uvs.emplace_back(uv_down_right);
            uvs.emplace_back(uv_up_right);
            uvs.emplace_back(uv_down_left);
        }

        glBindVertexArray(this->vao);
        glBindBuffer(GL_ARRAY_BUFFER, this->vertex_buffer);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, this->uvbuffer);
        glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

        // 1st attribute buffer: vertices.
        glBindBuffer(GL_ARRAY_BUFFER, this->vertex_buffer);
        glVertexAttribPointer(this->vertex_position_in_screenspace_id, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
        yli::opengl::enable_vertex_attrib_array(this->vertex_position_in_screenspace_id);

        // 2nd attribute buffer: UVs.
        glBindBuffer(GL_ARRAY_BUFFER, this->uvbuffer);
        glVertexAttribPointer(this->vertex_uv_id, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
        yli::opengl::enable_vertex_attrib_array(this->vertex_uv_id);

        // Draw call.
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());

        yli::opengl::disable_vertex_attrib_array(this->vertex_position_in_screenspace_id);
        yli::opengl::disable_vertex_attrib_array(this->vertex_uv_id);
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
