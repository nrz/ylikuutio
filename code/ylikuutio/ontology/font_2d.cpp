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

#include "font_2d.hpp"
#include "universe.hpp"
#include "text_2d.hpp"
#include "font_struct.hpp"
#include "text_struct.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/core/application.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/load/image_loader_struct.hpp"
#include "code/ylikuutio/load/shader_loader.hpp"
#include "code/ylikuutio/opengl/opengl.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.
#include "code/ylikuutio/render/render_system.hpp"
#include "code/ylikuutio/render/render_templates.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

#ifndef __GLM_GTC_MATRIX_TRANSFORM_HPP_INCLUDED
#define __GLM_GTC_MATRIX_TRANSFORM_HPP_INCLUDED
#include <glm/gtc/matrix_transform.hpp>
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <utility>  // std::pair
#include <vector>   // std::vector

namespace yli::ontology
{
    class Entity;
    class Scene;

    Font2D::Font2D(
            yli::core::Application& application,
            yli::ontology::Universe& universe,
            const yli::ontology::FontStruct& font_struct,
            yli::ontology::GenericParentModule* const parent_module)
        : Entity(application, universe, font_struct),
        child_of_universe(parent_module, this),
        parent_of_text_2ds(
                this,
                &this->registry,
                "text_2ds"),
        master_of_consoles(this, &this->registry, "consoles"),
        texture(
                universe,
                &this->registry,
                font_struct.texture_filename,
                font_struct.font_texture_file_format,
                yli::load::ImageLoaderStruct({ std::pair(yli::load::ImageLoadingFlags::SHOULD_CONVERT_GRAYSCALE_TO_RGB, true) }),
                "texture"),
        screen_width  { font_struct.screen_width },
        screen_height { font_struct.screen_height },
        text_size     { font_struct.text_size },
        font_size     { font_struct.font_size }
    {
        // constructor.

        if (this->texture.get_is_texture_loaded())
        {
            if (this->universe.get_is_opengl_in_use())
            {
                // Initialize VAO.
                glGenVertexArrays(1, &this->vao);
                glBindVertexArray(this->vao);

                // Initialize VBO.
                glGenBuffers(1, &this->vertexbuffer);
                glGenBuffers(1, &this->uvbuffer);

                // Initialize `Pipeline`.
                this->program_id = yli::load::load_shaders("text_vertex_shader.vert", "text_vertex_shader.frag");
                glUseProgram(this->program_id);

                // Get a handle for our buffers.
                this->vertex_position_in_screenspace_id = glGetAttribLocation(this->program_id, "vertex_position_screenspace");
                this->vertex_uv_id = glGetAttribLocation(this->program_id, "vertexUV");

                // Initialize uniforms' IDs.
                this->text_2d_uniform_id = glGetUniformLocation(this->program_id, "texture_sampler");

                // Initialize uniform window width.
                this->screen_width_uniform_id = glGetUniformLocation(this->program_id, "screen_width");
                yli::opengl::uniform_1i(this->screen_width_uniform_id, this->screen_width);

                // Initialize uniform window height.
                this->screen_height_uniform_id = glGetUniformLocation(this->program_id, "screen_height");
                yli::opengl::uniform_1i(this->screen_height_uniform_id, this->screen_height);
            }
            else if (this->universe.get_is_vulkan_in_use())
            {
                std::cerr << "ERROR: `Font2D::Font2D`: Vulkan is not supported yet!\n";
            }
        }

        // `yli::ontology::Entity` member variables begin here.
        this->type_string = "yli::ontology::Font2D*";
    }

    Font2D::~Font2D()
    {
        // destructor.

        if (this->universe.get_is_opengl_in_use())
        {
            // Delete buffers.
            glDeleteBuffers(1, &this->vertexbuffer);
            glDeleteBuffers(1, &this->uvbuffer);

            // Delete vertex array.
            glDeleteVertexArrays(1, &this->vao);

            // Delete shader.
            glDeleteProgram(this->program_id);
        }
    }

    yli::ontology::Entity* Font2D::get_parent() const
    {
        return this->child_of_universe.get_parent();
    }

    yli::ontology::Scene* Font2D::get_scene() const
    {
        // `Font2D` does not belong in any `Scene`.
        return nullptr;
    }

    std::size_t Font2D::get_number_of_children() const
    {
        return this->parent_of_text_2ds.get_number_of_children();
    }

    std::size_t Font2D::get_number_of_descendants() const
    {
        return yli::ontology::get_number_of_descendants(this->parent_of_text_2ds.child_pointer_vector);
    }

    uint32_t Font2D::get_text_size() const
    {
        return this->text_size;
    }

    uint32_t Font2D::get_font_size() const
    {
        return this->font_size;
    }

    const std::string& Font2D::get_font_texture_file_format() const
    {
        return this->texture.get_texture_file_format();
    }

    uint32_t Font2D::get_program_id() const
    {
        return this->program_id;
    }

    void Font2D::prepare_to_print() const
    {
        if (this->should_be_rendered && this->universe.get_is_opengl_in_use())
        {
            // Bind program.
            glUseProgram(this->program_id);

            // Bind texture.
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, this->texture.get_texture());

            // Set our "texture_sampler" sampler to user Material Unit 0
            yli::opengl::uniform_1i(this->text_2d_uniform_id, 0);

            // Set screen width.
            yli::opengl::uniform_1i(this->screen_width_uniform_id, this->screen_width);

            // Set screen height.
            yli::opengl::uniform_1i(this->screen_height_uniform_id, this->screen_height);

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }
    }

    void Font2D::render()
    {
        if (!this->should_be_rendered || !this->universe.get_is_opengl_in_use())
        {
            return;
        }

        yli::render::RenderSystem* const render_system = this->universe.get_render_system();

        if (render_system == nullptr)
        {
            std::cerr << "ERROR: `Font2D::render`: `render_system` is `nullptr`!\n";
            return;
        }

        this->prepare_to_print();
        render_system->render_text_2ds(this->parent_of_text_2ds);
        render_system->render_consoles(this->master_of_consoles);
        glDisable(GL_BLEND);
    }

    void Font2D::print_text_2d(
            const uint32_t x,
            const uint32_t y,
            const uint32_t text_size,
            const uint32_t font_size,
            const std::string& text,
            const std::string& font_texture_file_format,
            const std::string& horizontal_alignment,
            const std::string& vertical_alignment) const
    {
        if (!this->should_be_rendered)
        {
            return;
        }

        this->prepare_to_print();

        // If horizontal alignment is `"left"`, each line begins from the same x coordinate.
        // If horizontal alignment is `"left"` and vertical alignment is `"top"`,
        // then there is no need to check the text beforehand for newlines.
        // Otherwise newlines need to be checked beforehand.
        //
        // If horizontal alignment is right, each line ends in the same x coordinate.
        // Newlines need to be checked beforehand.
        const std::size_t length = text.size();

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

            if (character == (char) '\\')
            {
                // OK, this character was backslash, so read the next character.
                character = text[i++];

                if (character == 'n')
                {
                    number_of_lines++;
                }
            }
        }

        uint32_t current_left_x;
        uint32_t current_top_y;

        if (horizontal_alignment == "left")
        {
            current_left_x = x;
        }
        else if (horizontal_alignment == "center")
        {
            current_left_x = x - 0.5f * length * text_size;
        }
        else if (horizontal_alignment == "right")
        {
            current_left_x = x - length * text_size;
        }
        else
        {
            std::cerr << "ERROR: `Font2D::print_text_2d`: invalid horizontal alignment: " << horizontal_alignment << "\n";
            return;
        }

        if (vertical_alignment == "top")
        {
            current_top_y = y;
        }
        else if (vertical_alignment == "center")
        {
            current_top_y = y + 0.5f * number_of_lines * text_size;
        }
        else if (vertical_alignment == "bottom")
        {
            current_top_y = y + number_of_lines * text_size;
        }
        else
        {
            std::cerr << "ERROR: `Font2D::print_text_2d`: invalid vertical alignment: " << vertical_alignment << "\n";
            return;
        }

        // Fill buffers.
        std::vector<glm::vec2> vertices;
        std::vector<glm::vec2> UVs;

        i = 0;

        while (i < length)
        {
            // Print to the right side of X (so far there is no check for input length).
            // Print up of Y.
            uint32_t vertex_up_left_x;
            uint32_t vertex_up_left_y;
            uint32_t vertex_up_right_x;
            uint32_t vertex_up_right_y;
            uint32_t vertex_down_left_x;
            uint32_t vertex_down_left_y;
            uint32_t vertex_down_right_x;
            uint32_t vertex_down_right_y;

            char character = text[i++];

            if (character == (char) '\\')
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
                    // Jump to the beginning of the next line.
                    // `"left"` horizontal alignment and `"top"` vertical alignment are assumed.
                    // TODO: implement newline for other horizontal and vertical alignments too!
                    current_left_x = x;
                    current_top_y -= text_size;
                    continue;
                }
            }

            vertex_up_left_x = vertex_down_left_x = current_left_x;
            vertex_up_right_x = vertex_down_right_x = current_left_x + text_size;
            current_left_x += text_size;

            vertex_down_left_y = vertex_down_right_y = current_top_y - text_size;
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

            float uv_x = (character % font_size) / static_cast<float>(font_size);
            float uv_y;

            if (font_texture_file_format == "png" || font_texture_file_format == "PNG")
            {
                uv_y = (character / font_size) / static_cast<float>(font_size);
            }
            else
            {
                std::cerr << "ERROR: `Font2D::print_text_2d`: invalid font_texture_file_format " << font_texture_file_format << "\n";
                return;
            }

            glm::vec2 uv_up_left = glm::vec2(uv_x, uv_y);
            glm::vec2 uv_up_right = glm::vec2(uv_x + (1.0f / static_cast<float>(font_size)), uv_y);
            glm::vec2 uv_down_right;
            glm::vec2 uv_down_left;

            if (font_texture_file_format == "png" || font_texture_file_format == "PNG")
            {
                uv_down_right = glm::vec2(uv_x + (1.0f / static_cast<float>(font_size)), (uv_y + 1.0f / static_cast<float>(font_size)));
                uv_down_left = glm::vec2(uv_x, (uv_y + 1.0f / static_cast<float>(font_size)));
            }
            UVs.emplace_back(uv_up_left);
            UVs.emplace_back(uv_down_left);
            UVs.emplace_back(uv_up_right);

            UVs.emplace_back(uv_down_right);
            UVs.emplace_back(uv_up_right);
            UVs.emplace_back(uv_down_left);
        }

        if (this->universe.get_is_opengl_in_use())
        {
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
    }

    void Font2D::print_text_2d(const yli::ontology::TextStruct& text_struct) const
    {
        if (!this->should_be_rendered)
        {
            return;
        }

        this->print_text_2d(
                text_struct.x,
                text_struct.y,
                text_struct.text_size,
                text_struct.font_size,
                text_struct.text,
                text_struct.font_texture_file_format,
                text_struct.horizontal_alignment,
                text_struct.vertical_alignment);
    }

    void Font2D::print_text_2d(
            const uint32_t x,
            const uint32_t y,
            const uint32_t text_size,
            const uint32_t font_size,
            const std::string& text,
            const std::string& font_texture_file_format) const
    {
        if (!this->should_be_rendered)
        {
            return;
        }

        this->print_text_2d(x, y, text_size, font_size, text, font_texture_file_format, "left", "bottom");
    }
}
