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

#include "font_2d.hpp"
#include "universe.hpp"
#include "text_2d.hpp"
#include "horizontal_alignment.hpp"
#include "vertical_alignment.hpp"
#include "font_struct.hpp"
#include "text_struct.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/data/datatype.hpp"
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
#include <algorithm> // std::count
#include <cstddef>   // std::size_t
#include <iostream>  // std::cout, std::cerr
#include <stdexcept> // std::runtime_error
#include <stdint.h>  // uint32_t etc.
#include <string>    // std::string
#include <utility>   // std::pair
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

    Font2d::Font2d(
            yli::core::Application& application,
            Universe& universe,
            const FontStruct& font_struct,
            GenericParentModule* const universe_parent_module)
        : Entity(application, universe, font_struct),
        child_of_universe(universe_parent_module, *this),
        parent_of_text_2ds(
                *this,
                this->registry,
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
                this->vertex_uv_id = glGetAttribLocation(this->program_id, "vertex_uv");

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
            glDeleteBuffers(1, &this->vertexbuffer);
            glDeleteBuffers(1, &this->uvbuffer);

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

    void Font2d::draw(std::vector<glm::vec2>& vertices, std::vector<glm::vec2>& uvs) const
    {
        if (this->universe.get_is_opengl_in_use())
        {
            glBindVertexArray(this->vao);
            glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, this->uvbuffer);
            glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

            // 1st attribute buffer: vertices.
            glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
            glVertexAttribPointer(this->vertex_position_in_screenspace_id, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
            yli::opengl::enable_vertex_attrib_array(this->vertex_position_in_screenspace_id);

            // 2nd attribute buffer: uvs.
            glBindBuffer(GL_ARRAY_BUFFER, this->uvbuffer);
            glVertexAttribPointer(this->vertex_uv_id, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
            yli::opengl::enable_vertex_attrib_array(this->vertex_uv_id);

            // Draw call.
            glDrawArrays(GL_TRIANGLES, 0, vertices.size());

            yli::opengl::disable_vertex_attrib_array(this->vertex_position_in_screenspace_id);
            yli::opengl::disable_vertex_attrib_array(this->vertex_uv_id);
        }
    }

    std::size_t Font2d::get_number_of_children() const
    {
        return this->parent_of_text_2ds.get_number_of_children();
    }

    std::size_t Font2d::get_number_of_descendants() const
    {
        return yli::ontology::get_number_of_descendants(this->parent_of_text_2ds.child_pointer_vector);
    }

    uint32_t Font2d::get_text_size() const
    {
        return this->text_size;
    }

    uint32_t Font2d::get_font_size() const
    {
        return this->font_size;
    }

    const std::string& Font2d::get_font_texture_file_format() const
    {
        return this->texture.get_texture_file_format();
    }

    uint32_t Font2d::get_program_id() const
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
            yli::opengl::uniform_1i(this->text_2d_uniform_id, 0);

            // Set screen width.
            yli::opengl::uniform_1i(this->screen_width_uniform_id, this->screen_width);

            // Set screen height.
            yli::opengl::uniform_1i(this->screen_height_uniform_id, this->screen_height);

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

        yli::render::RenderSystem* const render_system = this->universe.get_render_system();

        if (render_system == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `Font2d::render`: `render_system` is `nullptr`!");
        }

        this->prepare_to_print();
        render_system->render_text_2ds(this->parent_of_text_2ds);
        render_system->render_consoles(this->master_of_consoles);
        glDisable(GL_BLEND);
    }

    void Font2d::print_text_2d(const TextStruct& text_struct) const
    {
        if (!this->should_render)
        {
            return;
        }

        this->prepare_to_print();

        // TODO: implement support for `std::vector<std::string>`!
        if (!std::holds_alternative<std::string>(text_struct.text))
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
        const std::size_t length = std::get<std::string>(text_struct.text).size();

        // Count the number of lines.
        const std::string string = std::get<std::string>(text_struct.text);
        std::size_t number_of_lines = std::count(string.begin(), string.end(), '\n');

        uint32_t current_left_x;
        uint32_t current_top_y;

        if (text_struct.position.horizontal_alignment == HorizontalAlignment::LEFT)
        {
            current_left_x = text_struct.position.x;
        }
        else if (text_struct.position.horizontal_alignment == HorizontalAlignment::HORIZONTAL_CENTER)
        {
            current_left_x = text_struct.position.x - 0.5f * length * text_size;
        }
        else if (text_struct.position.horizontal_alignment == HorizontalAlignment::RIGHT)
        {
            current_left_x = text_struct.position.x - length * text_size;
        }
        else
        {
            std::cerr << "ERROR: `Font2d::print_text_2d`: invalid horizontal alignment: " << text_struct.position.horizontal_alignment << "\n";
            return;
        }

        if (text_struct.position.vertical_alignment == VerticalAlignment::TOP)
        {
            current_top_y = text_struct.position.y;
        }
        else if (text_struct.position.vertical_alignment == VerticalAlignment::VERTICAL_CENTER)
        {
            current_top_y = text_struct.position.y + 0.5f * number_of_lines * text_size;
        }
        else if (text_struct.position.vertical_alignment == VerticalAlignment::BOTTOM)
        {
            current_top_y = text_struct.position.y + number_of_lines * text_size;
        }
        else
        {
            std::cerr << "ERROR: `Font2d::print_text_2d`: invalid vertical alignment: " << text_struct.position.vertical_alignment << "\n";
            return;
        }

        // Fill buffers.
        std::vector<glm::vec2> vertices;
        std::vector<glm::vec2> uvs;

        std::size_t i = 0;

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

            const char character = std::get<std::string>(text_struct.text)[i++];

            if (character == '\n')
            {
                // Jump to the beginning of the next line.
                // `"left"` horizontal alignment and `"top"` vertical alignment are assumed.
                // TODO: implement newline for other horizontal and vertical alignments too!
                current_left_x = text_struct.position.x;
                current_top_y -= text_size;
                continue;
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

            float uv_x = (character % text_struct.font_size) / static_cast<float>(text_struct.font_size);
            float uv_y;

            if (text_struct.font_texture_file_format == "png" || text_struct.font_texture_file_format == "PNG")
            {
                uv_y = (character / text_struct.font_size) / static_cast<float>(text_struct.font_size);
            }
            else
            {
                std::cerr << "ERROR: `Font2d::print_text_2d`: invalid font_texture_file_format " << text_struct.font_texture_file_format << "\n";
                return;
            }

            glm::vec2 uv_up_left = glm::vec2(uv_x, uv_y);
            glm::vec2 uv_up_right = glm::vec2(uv_x + (1.0f / static_cast<float>(text_struct.font_size)), uv_y);
            glm::vec2 uv_down_right;
            glm::vec2 uv_down_left;

            if (text_struct.font_texture_file_format == "png" || text_struct.font_texture_file_format == "PNG")
            {
                uv_down_right = glm::vec2(uv_x + (1.0f / static_cast<float>(text_struct.font_size)), (uv_y + 1.0f / static_cast<float>(text_struct.font_size)));
                uv_down_left = glm::vec2(uv_x, (uv_y + 1.0f / static_cast<float>(text_struct.font_size)));
            }
            uvs.emplace_back(uv_up_left);
            uvs.emplace_back(uv_down_left);
            uvs.emplace_back(uv_up_right);

            uvs.emplace_back(uv_down_right);
            uvs.emplace_back(uv_up_right);
            uvs.emplace_back(uv_down_left);
        }

        this->draw(vertices, uvs);
    }

    GenericParentModule* Font2d::get_generic_parent_module(const int type)
    {
        if (type == yli::data::Datatype::TEXT_2D)
        {
            return &this->parent_of_text_2ds;
        }

        return nullptr;
    }
}
