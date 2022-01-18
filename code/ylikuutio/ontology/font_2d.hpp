// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2022 Antti Nuortimo.
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

#ifndef __YLIKUUTIO_ONTOLOGY_FONT_2D_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_FONT_2D_HPP_INCLUDED

#include "entity.hpp"
#include "child_module.hpp"
#include "generic_parent_module.hpp"
#include "generic_master_module.hpp"
#include "texture_module.hpp"
#include "universe.hpp"
#include "font_struct.hpp"
#include "text_struct.hpp"
#include "code/ylikuutio/load/image_loader_struct.hpp"
#include "code/ylikuutio/load/shader_loader.hpp"
#include "code/ylikuutio/load/common_texture_loader.hpp"
#include "code/ylikuutio/opengl/opengl.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.
#include "code/ylikuutio/render/graphics_api_backend.hpp"

// Include standard headers
#include <cstddef>   // std::size_t
#include <iostream>  // std::cout, std::cin, std::cerr
#include <stdint.h>  // uint32_t etc.
#include <string>    // std::string
#include <utility>   // std::pair

namespace yli::ontology
{
    class Scene;

    class Font2D: public yli::ontology::Entity
    {
        public:
            Font2D(
                    yli::ontology::Universe* const universe,
                    const yli::ontology::FontStruct& font_struct,
                    yli::ontology::GenericParentModule* const parent_module)
                : Entity(universe, font_struct),
                child_of_universe(parent_module, this),
                parent_of_text_2ds(this, &this->registry, "text_2ds"),
                master_of_consoles(this, &this->registry, "consoles"),
                texture(
                        universe,
                        &this->registry,
                        font_struct.texture_filename,
                        font_struct.font_texture_file_format,
                        yli::load::ImageLoaderStruct({ std::pair(yli::load::ImageLoadingFlags::SHOULD_CONVERT_GRAYSCALE_TO_RGB, true) }),
                        "texture")
        {
                // constructor.
                this->screen_width = font_struct.screen_width;
                this->screen_height = font_struct.screen_height;
                this->text_size = font_struct.text_size;
                this->font_size = font_struct.font_size;

                // Initialize class members with some dummy values.
                this->vao                               = 0;
                this->vertexbuffer                      = 0;
                this->uvbuffer                          = 0;
                this->program_id                        = 0;
                this->vertex_position_in_screenspace_id = 0;
                this->vertex_uv_id                      = 0;
                this->text_2d_uniform_id                = 0;
                this->screen_width_uniform_id           = 0;
                this->screen_height_uniform_id          = 0;

                if (this->texture.get_is_texture_loaded())
                {
                    if (this->universe->get_is_opengl_in_use())
                    {
                        // Initialize VAO.
                        glGenVertexArrays(1, &this->vao);
                        glBindVertexArray(this->vao);

                        // Initialize VBO.
                        glGenBuffers(1, &this->vertexbuffer);
                        glGenBuffers(1, &this->uvbuffer);

                        // Initialize `Shader`.
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
                    else if (this->universe->get_is_vulkan_in_use())
                    {
                        std::cerr << "ERROR: `Font2D::Font2D`: Vulkan is not supported yet!\n";
                    }
                }

                // `yli::ontology::Entity` member variables begin here.
                this->type_string = "yli::ontology::Font2D*";
            }

            Font2D(const Font2D&) = delete;            // Delete copy constructor.
            Font2D& operator=(const Font2D&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~Font2D();

            yli::ontology::Entity* get_parent() const override;

            uint32_t get_text_size() const;
            uint32_t get_font_size() const;
            const std::string& get_font_texture_file_format() const;
            uint32_t get_program_id() const;

            void prepare_to_print() const;

            void render();

            void print_text_2d(
                    const uint32_t x,
                    const uint32_t y,
                    const uint32_t text_size,
                    const uint32_t font_size,
                    const std::string& text,
                    const std::string& font_texture_file_format,
                    const std::string& horizontal_alignment,
                    const std::string& vertical_alignment) const;

            void print_text_2d(const yli::ontology::TextStruct& text_struct) const;

            void print_text_2d(
                    const uint32_t x,
                    const uint32_t y,
                    const uint32_t text_size,
                    const uint32_t font_size,
                    const std::string& text,
                    const std::string& font_texture_file_format) const;

            yli::ontology::ChildModule child_of_universe;
            yli::ontology::GenericParentModule parent_of_text_2ds;
            yli::ontology::GenericMasterModule master_of_consoles;
            yli::ontology::TextureModule texture;

            yli::ontology::Scene* get_scene() const override;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            GLuint vao;
            GLuint vertexbuffer;                     // Buffer containing the vertices.
            GLuint uvbuffer;                         // Buffer containing the UVs.
            GLuint program_id;                       // The `program_id` of the shader used to display the text, returned by `load_shaders`.
            GLint vertex_position_in_screenspace_id; // Location of the program's `vertex_position_screenspace` attribute.
            GLint vertex_uv_id;                      // Location of the program's `vertexUV` attribute.
            GLint text_2d_uniform_id;                // Location of the program's texture attribute.
            GLint screen_width_uniform_id;           // Location of the program's window width uniform.
            GLint screen_height_uniform_id;          // Location of the program's window height uniform.

            uint32_t screen_width;
            uint32_t screen_height;
            uint32_t text_size;
            uint32_t font_size;
    };
}

#endif
