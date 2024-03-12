// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2023 Antti Nuortimo.
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
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cerr
#include <optional> // std::optional
#include <stdexcept> // std::runtime_error
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::core
{
    class Application;
}

namespace yli::ontology
{
    class Entity;
    class Scene;

    std::optional<yli::data::AnyValue> Text2D::bind_to_new_font_2d_parent(
            yli::ontology::Text2D& text_2d,
            yli::ontology::Font2D& new_parent)
    {
        // Set pointer to `text_2d` to `nullptr`, set parent according to the input,
        // and request a new childID from `new_parent`.

        const yli::ontology::Entity* const font_2d = text_2d.get_parent();

        if (font_2d == nullptr)
        {
            throw std::runtime_error("ERROR: `Text2D::bind_to_new_font_2d_parent`: `font_2d` is `nullptr`!");
        }

        if (new_parent.has_child(text_2d.local_name))
        {
            std::cerr << "ERROR: `Text2D::bind_to_new_font_2d_parent`: local name is already in use!\n";
            return std::nullopt;
        }

        text_2d.child_of_font_2d.unbind_and_bind_to_new_parent(
                &new_parent.parent_of_text_2ds);

        return std::nullopt;
    }

    Text2D::Text2D(
            yli::core::Application& application,
            yli::ontology::Universe& universe,
            const yli::ontology::TextStruct& text_struct,
            yli::ontology::GenericParentModule* const font_2d_parent_module)
        : Entity(application, universe, text_struct),
        child_of_font_2d(font_2d_parent_module, *this)
    {
        // constructor.

        this->text = text_struct.text;
        this->horizontal_alignment = text_struct.horizontal_alignment;
        this->vertical_alignment = text_struct.vertical_alignment;
        this->screen_height = text_struct.screen_height;
        this->screen_width = text_struct.screen_width;
        this->x = text_struct.x;
        this->y = text_struct.y;
        this->text_size = text_struct.text_size;
        this->font_size = text_struct.font_size;

        // Initialize class members with some dummy values.
        this->vao                               = 0;
        this->vertexbuffer                      = 0;
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
            glGenBuffers(1, &this->vertexbuffer);
            glGenBuffers(1, &this->uvbuffer);

            // Get a handle for our buffers.
            const yli::ontology::Font2D* const font_2d = static_cast<yli::ontology::Font2D*>(this->get_parent());

            if (font_2d != nullptr)
            {
                this->vertex_position_in_screenspace_id = glGetAttribLocation(
                        font_2d->get_program_id(),
                        "vertex_position_screenspace");
                this->vertex_uv_id = glGetAttribLocation(font_2d->get_program_id(), "vertexUV");
            }

            this->vertices_and_uvs_loaded = true;
        }

        // `yli::ontology::Entity` member variables begin here.
        this->type_string = "yli::ontology::Text2D*";
    }

    Text2D::~Text2D()
    {
        if (this->vertices_and_uvs_loaded)
        {
            // Delete buffers.
            glDeleteBuffers(1, &this->vertexbuffer);
            glDeleteBuffers(1, &this->uvbuffer);
        }
    }

    void Text2D::render()
    {
        if (!this->should_be_rendered || !this->universe.get_is_opengl_in_use())
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

        if (this->horizontal_alignment == "left")
        {
            current_left_x = this->x;
        }
        else if (this->horizontal_alignment == "center")
        {
            current_left_x = this->x - 0.5f * length * this->text_size;
        }
        else if (this->horizontal_alignment == "right")
        {
            current_left_x = this->x - length * this->text_size;
        }
        else
        {
            std::cerr << "ERROR: `Text2D::render`: invalid horizontal alignment: " << horizontal_alignment << "\n";
            return;
        }

        if (this->vertical_alignment == "top")
        {
            current_top_y = this->y;
        }
        else if (this->vertical_alignment == "center")
        {
            current_top_y = this->y + 0.5f * number_of_lines * this->text_size;
        }
        else if (this->vertical_alignment == "bottom")
        {
            current_top_y = this->y + number_of_lines * this->text_size;
        }
        else
        {
            std::cerr << "ERROR: `Text2D::render`: invalid vertical alignment: " << this->vertical_alignment << "\n";
            return;
        }

        // Fill buffers
        std::vector<glm::vec2> vertices;
        std::vector<glm::vec2> UVs;

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
                    current_left_x = this->x;
                    current_top_y -= this->text_size;
                    continue;
                }
            }
            else if (character == '\n')
            {
                // jump to the beginning of the next line.
                // `"left"` horizontal alignment and `"top"` vertical alignment are assumed.
                // TODO: implement newline for other horizontal and vertical alignments too!
                current_left_x = this->x;
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

            const yli::ontology::Font2D* const font_2d = static_cast<yli::ontology::Font2D*>(this->get_parent());

            const std::string& font_texture_file_format = font_2d->get_font_texture_file_format();

            if (font_texture_file_format == "png" || font_texture_file_format == "PNG")
            {
                uv_y = (character / this->font_size) / static_cast<float>(this->font_size);
            }
            else
            {
                std::cerr << "ERROR: `Text2D::render`: invalid `font_texture_file_format`: " << font_texture_file_format << "\n";
                return;
            }

            glm::vec2 uv_up_left = glm::vec2(uv_x, uv_y);
            glm::vec2 uv_up_right = glm::vec2(uv_x + (1.0f / static_cast<float>(this->font_size)), uv_y);
            glm::vec2 uv_down_right;
            glm::vec2 uv_down_left;

            if (font_texture_file_format == "png" || font_texture_file_format == "PNG")
            {
                uv_down_right = glm::vec2(
                        uv_x + (1.0f / static_cast<float>(this->font_size)),
                        (uv_y + 1.0f / static_cast<float>(this->font_size)));
                uv_down_left = glm::vec2(uv_x, (uv_y + 1.0f / static_cast<float>(this->font_size)));
            }

            UVs.emplace_back(uv_up_left);
            UVs.emplace_back(uv_down_left);
            UVs.emplace_back(uv_up_right);

            UVs.emplace_back(uv_down_right);
            UVs.emplace_back(uv_up_right);
            UVs.emplace_back(uv_down_left);
        }

        glBindVertexArray(this->vao);
        glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, this->uvbuffer);
        glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(glm::vec2), &UVs[0], GL_STATIC_DRAW);

        // 1st attribute buffer: vertices.
        glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
        glVertexAttribPointer(this->vertex_position_in_screenspace_id, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);
        yli::opengl::enable_vertex_attrib_array(this->vertex_position_in_screenspace_id);

        // 2nd attribute buffer: UVs.
        glBindBuffer(GL_ARRAY_BUFFER, this->uvbuffer);
        glVertexAttribPointer(this->vertex_uv_id, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);
        yli::opengl::enable_vertex_attrib_array(this->vertex_uv_id);

        // Draw call.
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());

        yli::opengl::disable_vertex_attrib_array(this->vertex_position_in_screenspace_id);
        yli::opengl::disable_vertex_attrib_array(this->vertex_uv_id);
    }

    yli::ontology::Entity* Text2D::get_parent() const
    {
        return this->child_of_font_2d.get_parent();
    }

    yli::ontology::Scene* Text2D::get_scene() const
    {
        const yli::ontology::Entity* const parent = this->get_parent();

        if (parent != nullptr)
        {
            return parent->get_scene();
        }

        return nullptr;
    }

    std::size_t Text2D::get_number_of_children() const
    {
        return 0; // `Text2D` has no children.
    }

    std::size_t Text2D::get_number_of_descendants() const
    {
        return 0; // `Text2D` has no children.
    }

    void Text2D::change_string(const std::string& text)
    {
        this->text = text;
    }
}
