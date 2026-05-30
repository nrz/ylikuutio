// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2026 Antti Nuortimo.
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
#include "horizontal_alignment.hpp"
#include "vertical_alignment.hpp"
#include "font_struct.hpp"
#include "print_text_struct.hpp"
#include "print_console_struct.hpp"
#include "texture_file_format.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/load/image_loader_struct.hpp"
#include "code/ylikuutio/load/shader_loader.hpp"
#include "code/ylikuutio/opengl/opengl.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.
#include "code/ylikuutio/render/render_system.hpp"
#include "code/ylikuutio/render/render_text.hpp"

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
#include <algorithm> // std::count
#include <cstddef>   // std::size_t
#include <cstdint>   // std::uint32_t
#include <iostream>  // std::cout, std::cerr
#include <span>      // std::span
#include <stdexcept> // std::runtime_error
#include <string>    // std::string
#include <utility>   // std::pair
#include <vector>    // std::vector

namespace yli::core
{
    class Application;
}

namespace yli::ontology
{
    class Entity;
    class Scene;

    Font2d::Font2d(
            core::Application& application,
            Universe& universe,
            const FontStruct& font_struct,
            GenericParentModule* const universe_parent_module)
        : Entity(application, universe, font_struct),
        child_of_universe(universe_parent_module, *this),
        parent_of_text_2ds(
                *this,
                this->registry,
                "text_2ds"),
        master_of_consoles(*this, &this->registry, "consoles"),
        texture(
                universe,
                &this->registry,
                font_struct.texture_filename,
                font_struct.font_texture_file_format,
                load::ImageLoaderStruct({ std::pair(load::ImageLoadingFlags::SHOULD_CONVERT_GRAYSCALE_TO_RGB, true) }),
                "texture"),
        screen_width  { font_struct.screen_width },
        screen_height { font_struct.screen_height },
        text_size     { font_struct.text_size }
    {
        if (this->texture.get_is_texture_loaded())
        {
            if (this->universe.get_is_opengl_in_use())
            {
                // Initialize VAO.
                glGenVertexArrays(1, &this->vao);
                glBindVertexArray(this->vao);

                // Initialize VBO.
                glGenBuffers(1, &this->vertex_buffer);
                glGenBuffers(1, &this->uv_buffer);

                // Initialize `Pipeline`.
                this->program_id = load::load_shaders("text_vertex_shader.vert", "text_vertex_shader.frag");
                glUseProgram(this->program_id);

                // Get a handle for our buffers.
                this->vertex_position_in_screenspace_id = glGetAttribLocation(this->program_id, "vertex_position_screenspace");
                this->vertex_uv_id = glGetAttribLocation(this->program_id, "vertex_uv");

                // Initialize uniforms' IDs.
                this->text_2d_uniform_id = glGetUniformLocation(this->program_id, "texture_sampler");

                // Initialize uniform window width.
                this->screen_width_uniform_id = glGetUniformLocation(this->program_id, "screen_width");
                opengl::uniform_1i(this->screen_width_uniform_id, this->screen_width);

                // Initialize uniform window height.
                this->screen_height_uniform_id = glGetUniformLocation(this->program_id, "screen_height");
                opengl::uniform_1i(this->screen_height_uniform_id, this->screen_height);
            }
            else if (this->universe.get_is_vulkan_in_use())
            {
                std::cerr << "ERROR: `Font2d::Font2d`: Vulkan is not supported yet!\n";
            }
        }

        // `Entity` member variables begin here.
        this->type_string = "yli::ontology::Font2d*";
    }

    Font2d::~Font2d()
    {
        if (this->universe.get_is_opengl_in_use())
        {
            // Delete buffers.
            glDeleteBuffers(1, &this->vertex_buffer);
            glDeleteBuffers(1, &this->uv_buffer);

            // Delete vertex array.
            glDeleteVertexArrays(1, &this->vao);

            // Delete shader.
            glDeleteProgram(this->program_id);
        }
    }

    Entity* Font2d::get_parent() const
    {
        return this->child_of_universe.get_parent();
    }

    Scene* Font2d::get_scene() const
    {
        // `Font2d` does not belong in any `Scene`.
        return nullptr;
    }

    std::uint32_t Font2d::compute_left_x(const PrintTextStruct& print_text_struct) const
    {
        // Compute string length.
        const std::string& string = print_text_struct.text;
        const std::size_t length = string.size();

        if (print_text_struct.position.horizontal_alignment == LEFT)
        {
            return print_text_struct.position.x;
        }
        if (print_text_struct.position.horizontal_alignment == HORIZONTAL_CENTER)
        {
            return print_text_struct.position.x - 0.5f * length * text_size;
        }
        if (print_text_struct.position.horizontal_alignment == RIGHT)
        {
            return print_text_struct.position.x - length * text_size;
        }
        throw std::runtime_error("ERROR: `Font2d::compute_left_x`: invalid horizontal alignment!");
    }

    std::uint32_t Font2d::compute_top_y(const PrintTextStruct& print_text_struct) const
    {
        // Count the number of lines.
        const std::string& string = print_text_struct.text;
        const std::size_t number_of_lines = std::count(string.begin(), string.end(), '\n') + 1;

        if (print_text_struct.position.vertical_alignment == TOP)
        {
            return print_text_struct.position.y;
        }
        if (print_text_struct.position.vertical_alignment == VERTICAL_CENTER)
        {
            return print_text_struct.position.y + 0.5f * number_of_lines * text_size;
        }
        if (print_text_struct.position.vertical_alignment == BOTTOM)
        {
            return print_text_struct.position.y + number_of_lines * text_size;
        }
        throw std::runtime_error("ERROR: `Font2d::compute_top_y`: invalid vertical alignment!");
    }

    void Font2d::compute_and_store_glyph_vertices(
            std::vector<glm::vec2>& vertices,
            const std::uint32_t vertex_left_x,
            const std::uint32_t vertex_top_y) const
    {
        const std::uint32_t vertex_right_x = vertex_left_x + this->text_size;

        const glm::vec2 vertex_up_left(vertex_left_x, vertex_top_y);
        const glm::vec2 vertex_up_right(vertex_right_x, vertex_top_y);
        const glm::vec2 vertex_down_left(vertex_left_x, vertex_top_y - this->text_size);
        const glm::vec2 vertex_down_right(vertex_right_x, vertex_top_y - this->text_size);

        vertices.emplace_back(vertex_up_left);
        vertices.emplace_back(vertex_down_left);
        vertices.emplace_back(vertex_up_right);

        vertices.emplace_back(vertex_down_right);
        vertices.emplace_back(vertex_up_right);
        vertices.emplace_back(vertex_down_left);
    }

    std::size_t Font2d::get_number_of_children() const
    {
        return this->parent_of_text_2ds.get_number_of_children();
    }

    std::size_t Font2d::get_number_of_descendants() const
    {
        return ontology::get_number_of_descendants(this->parent_of_text_2ds.child_pointer_vector);
    }

    std::uint32_t Font2d::get_text_size() const
    {
        return this->text_size;
    }

    TextureFileFormat Font2d::get_font_texture_file_format() const
    {
        return this->texture.get_texture_file_format();
    }

    std::uint32_t Font2d::get_program_id() const
    {
        return this->program_id;
    }

    void Font2d::prepare_to_print() const
    {
        if (this->should_render && this->universe.get_is_opengl_in_use())
        {
            // Bind program.
            glUseProgram(this->program_id);

            // Bind texture.
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, this->texture.get_texture());

            // Set our "texture_sampler" sampler to user Material Unit 0
            opengl::uniform_1i(this->text_2d_uniform_id, 0);

            // Set screen width.
            opengl::uniform_1i(this->screen_width_uniform_id, this->screen_width);

            // Set screen height.
            opengl::uniform_1i(this->screen_height_uniform_id, this->screen_height);

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }
    }

    void Font2d::render()
    {
        if (!this->should_render || !this->universe.get_is_opengl_in_use())
        {
            return;
        }

        render::RenderSystem& render_system = this->universe.get_render_system();

        this->prepare_to_print();
        render_system.render_text_2ds(this->parent_of_text_2ds);
        render_system.render_consoles(this->master_of_consoles);
        glDisable(GL_BLEND);
    }

    void Font2d::print_text_2d(const PrintTextStruct& print_text_struct) const
    {
        if (!this->should_render)
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
        const std::size_t length = print_text_struct.text.size();

        std::uint32_t current_left_x = this->compute_left_x(print_text_struct);
        std::uint32_t current_top_y = this->compute_top_y(print_text_struct);

        // Fill buffers.
        std::vector<glm::vec2> vertices;
        std::vector<glm::vec2> uvs;

        std::size_t i = 0;
        std::uint32_t column_i = 0;

        while (i < length)
        {
            // Print to the right side of X (so far there is no check for input length).
            // Print up of Y.

            const char character = print_text_struct.text[i++];

            if (character == '\n' || column_i >= print_text_struct.n_columns)
            {
                // Jump to the beginning of the next line.
                // `"left"` horizontal alignment and `"top"` vertical alignment are assumed.
                // TODO: implement newline for other horizontal and vertical alignments too!
                current_left_x = print_text_struct.position.x;
                current_top_y -= this->text_size;
                column_i = 0;

                if (character == '\n' )
                {
                    continue;
                }
            }


            this->compute_and_store_glyph_vertices(vertices, current_left_x, current_top_y);
            current_left_x += this->text_size;

            const float uv_x = (character % print_text_struct.font_size) / static_cast<float>(print_text_struct.font_size);
            const float uv_y = (character / print_text_struct.font_size) / static_cast<float>(print_text_struct.font_size);

            const glm::vec2 uv_up_left = glm::vec2(uv_x, uv_y);
            const glm::vec2 uv_up_right = glm::vec2(uv_x + (1.0f / static_cast<float>(print_text_struct.font_size)), uv_y);
            const glm::vec2 uv_down_right = glm::vec2(uv_x + (1.0f / static_cast<float>(print_text_struct.font_size)), (uv_y + 1.0f / static_cast<float>(print_text_struct.font_size)));
            const glm::vec2 uv_down_left = glm::vec2(uv_x, (uv_y + 1.0f / static_cast<float>(print_text_struct.font_size)));

            uvs.emplace_back(uv_up_left);
            uvs.emplace_back(uv_down_left);
            uvs.emplace_back(uv_up_right);

            uvs.emplace_back(uv_down_right);
            uvs.emplace_back(uv_up_right);
            uvs.emplace_back(uv_down_left);

            column_i++;
        }

        render::render_text(
                vertices,
                uvs,
                this->vao,
                this->vertex_buffer,
                this->uv_buffer,
                this->vertex_position_in_screenspace_id,
                this->vertex_uv_id);
    }

    void Font2d::print_console(const PrintConsoleStruct& print_console_struct) const
    {
        if (!this->should_render)
        {
            return;
        }

        this->prepare_to_print();

        std::uint32_t current_left_x = print_console_struct.position.x;
        std::uint32_t current_top_y = print_console_struct.position.y;

        // Fill buffers.
        std::vector<glm::vec2> vertices;
        std::vector<glm::vec2> uvs;

        const std::span<const std::string> view = print_console_struct.buffer_text;

        // Print to the right side of X (so far there is no check for input length).
        // Print up of Y.

        for (std::span<const std::string>::iterator span_it = view.begin(); span_it != view.end(); ++span_it)
        {
            for (std::string::const_iterator text_line_it = span_it->cbegin(); text_line_it != span_it->cend(); ++text_line_it)
            {
                const char character = *text_line_it;

                this->compute_and_store_glyph_vertices(vertices, current_left_x, current_top_y);
                current_left_x += this->text_size;

                const float uv_x = (character % print_console_struct.font_size) / static_cast<float>(print_console_struct.font_size);
                const float uv_y = (character / print_console_struct.font_size) / static_cast<float>(print_console_struct.font_size);

                const glm::vec2 uv_up_left = glm::vec2(uv_x, uv_y);
                const glm::vec2 uv_up_right = glm::vec2(uv_x + (1.0f / static_cast<float>(print_console_struct.font_size)), uv_y);
                const glm::vec2 uv_down_right = glm::vec2(uv_x + (1.0f / static_cast<float>(print_console_struct.font_size)), (uv_y + 1.0f / static_cast<float>(print_console_struct.font_size)));
                const glm::vec2 uv_down_left = glm::vec2(uv_x, (uv_y + 1.0f / static_cast<float>(print_console_struct.font_size)));

                uvs.emplace_back(uv_up_left);
                uvs.emplace_back(uv_down_left);
                uvs.emplace_back(uv_up_right);

                uvs.emplace_back(uv_down_right);
                uvs.emplace_back(uv_up_right);
                uvs.emplace_back(uv_down_left);
            }

            // Jump to the beginning of the next line.
            current_left_x = print_console_struct.position.x;
            current_top_y -= text_size;
        }

        render::render_text(
                vertices,
                uvs,
                this->vao,
                this->vertex_buffer,
                this->uv_buffer,
                this->vertex_position_in_screenspace_id,
                this->vertex_uv_id);

        if (print_console_struct.text_input != nullptr)
        {
            PrintTextStruct print_text_struct { print_console_struct.font_size, this->universe.get_window_width() / this->text_size };
            print_text_struct.position.x = current_left_x;
            print_text_struct.position.y = current_top_y;
            print_text_struct.position.horizontal_alignment = LEFT;
            print_text_struct.position.vertical_alignment = TOP;
            print_text_struct.text = print_console_struct.prompt + print_console_struct.text_input->data();
            this->print_text_2d(print_text_struct);
        }
    }
}
