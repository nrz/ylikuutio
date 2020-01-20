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

#ifndef __FONT2D_HPP_INCLUDED
#define __FONT2D_HPP_INCLUDED

#include "entity.hpp"
#include "universe.hpp"
#include "text_struct.hpp"
#include "code/ylikuutio/load/shader_loader.hpp"
#include "code/ylikuutio/load/bmp_texture_loader.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/opengl/opengl.hpp"

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <cstddef>   // std::size_t
#include <iostream>  // std::cout, std::cin, std::cerr
#include <queue>     // std::queue
#include <stdint.h>  // uint32_t etc.
#include <string>    // std::string
#include <vector>    // std::vector

namespace yli
{
    namespace ontology
    {
        class Text2D;

        class Font2D: public yli::ontology::Entity
        {
            public:
                void bind_Text2D(yli::ontology::Text2D* const text2D);
                void unbind_Text2D(const std::size_t childID);

                // constructor.
                Font2D(
                        yli::ontology::Universe* const universe,
                        std::size_t screen_width,
                        std::size_t screen_height,
                        std::size_t text_size,
                        std::size_t font_size,
                        const std::string& texture_filename,
                        const std::string& font_texture_file_format)
                    : Entity(universe)
                {
                    // constructor.
                    this->parent = universe;
                    this->screen_width = screen_width;
                    this->screen_height = screen_height;
                    this->font_texture_file_format = font_texture_file_format;
                    this->text_size = text_size;
                    this->font_size = font_size;

                    this->number_of_text2Ds = 0;

                    // Get `childID` from `Universe` and set pointer to this `Font2D`.
                    this->bind_to_parent();

                    // Initialize class members with some dummy values.
                    this->texture                          = 0;
                    this->vertexbuffer                     = 0;
                    this->uvbuffer                         = 0;
                    this->programID                        = 0;
                    this->vertex_position_in_screenspaceID = 0;
                    this->vertexUVID                       = 0;
                    this->Text2DUniformID                  = 0;
                    this->screen_width_uniform_ID          = 0;
                    this->screen_height_uniform_ID         = 0;
                    this->image_width                      = 0;
                    this->image_height                     = 0;
                    this->image_size                       = 0;

                    const bool is_headless = (this->universe == nullptr ? true : this->universe->get_is_headless());
                    bool is_texture_loading_successful = false;

                    // Initialize texture.
                    if (this->font_texture_file_format == "bmp" || this->font_texture_file_format == "BMP")
                    {
                        is_texture_loading_successful = yli::load::load_BMP_texture(
                                texture_filename,
                                this->image_width,
                                this->image_height,
                                this->image_size,
                                this->texture,
                                is_headless);

                        if (!is_texture_loading_successful)
                        {
                            std::cerr << "ERROR: loading BMP texture failed!\n";
                        }
                    }
                    else
                    {
                        std::cerr << "ERROR: invalid font texture file format: " << this->font_texture_file_format << "\n";
                        std::cerr << "supported font texture file formats: bmp, BMP.\n";
                    }

                    if (!is_headless && is_texture_loading_successful)
                    {
                        // Initialize VBO.
                        glGenBuffers(1, &this->vertexbuffer);
                        glGenBuffers(1, &this->uvbuffer);

                        // Initialize `Shader`.
                        this->programID = yli::load::load_shaders("text_vertex_shader.vert", "text_vertex_shader.frag");

                        // Get a handle for our buffers.
                        this->vertex_position_in_screenspaceID = glGetAttribLocation(this->programID, "vertex_position_screenspace");
                        this->vertexUVID = glGetAttribLocation(this->programID, "vertexUV");

                        // Initialize uniforms' IDs.
                        this->Text2DUniformID = glGetUniformLocation(this->programID, "texture_sampler");

                        // Initialize uniform window width.
                        this->screen_width_uniform_ID = glGetUniformLocation(this->programID, "screen_width");
                        yli::opengl::uniform_1i(this->screen_width_uniform_ID, this->screen_width);

                        // Initialize uniform window height.
                        this->screen_height_uniform_ID = glGetUniformLocation(this->programID, "screen_height");
                        yli::opengl::uniform_1i(this->screen_height_uniform_ID, this->screen_height);
                    }

                    // `yli::ontology::Entity` member variables begin here.
                    this->type_string = "yli::ontology::Font2D*";
                }

                Font2D(const Font2D&) = delete;            // Delete copy constructor.
                Font2D &operator=(const Font2D&) = delete; // Delete copy assignment.

                // destructor.
                virtual ~Font2D();

                yli::ontology::Entity* get_parent() const override;
                std::size_t get_number_of_children() const override;
                std::size_t get_number_of_descendants() const override;

                std::size_t get_text_size() const;
                std::size_t get_font_size() const;
                const std::string& get_font_texture_file_format() const;
                uint32_t get_programID() const;

                void prepare_to_print() const;

                void render() override;

                void print_text2D(
                        const std::size_t x,
                        const std::size_t y,
                        const std::size_t text_size,
                        const std::size_t font_size,
                        const std::string& text,
                        const std::string& font_texture_file_format,
                        const std::string& horizontal_alignment,
                        const std::string& vertical_alignment) const;

                void print_text2D(const yli::ontology::TextStruct& text_struct) const;

                void print_text2D(
                        const std::size_t x,
                        const std::size_t y,
                        const std::size_t text_size,
                        const std::size_t font_size,
                        const std::string& text,
                        const std::string& font_texture_file_format) const;

                template<class T1>
                    friend void yli::hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue, std::size_t& number_of_children);

            private:
                void bind_to_parent();

                yli::ontology::Universe* parent;           // Pointer to the `Universe`.

                std::vector<yli::ontology::Text2D*> text2D_pointer_vector;
                std::queue<std::size_t> free_text2D_ID_queue;
                std::size_t number_of_text2Ds;

                uint32_t texture;                          // Texture containing the glyphs, returned by `load_BMP_texture`,
                                                           // (used for `glGenTextures` etc.).

                uint32_t vertexbuffer;                     // Buffer containing the vertices.
                uint32_t uvbuffer;                         // Buffer containing the UVs.
                uint32_t programID;                        // The `programID` of the shader used to display the text, returned by `load_shaders`.
                GLint vertex_position_in_screenspaceID;    // Location of the program's `vertex_position_screenspace` attribute.
                GLint vertexUVID;                          // Location of the program's `vertexUV` attribute.
                GLint Text2DUniformID;                     // Location of the program's texture attribute.
                GLint screen_width_uniform_ID;             // Location of the program's window width uniform.
                GLint screen_height_uniform_ID;            // Location of the program's window height uniform.

                std::string font_texture_file_format;

                std::size_t screen_width;
                std::size_t screen_height;
                std::size_t image_width;
                std::size_t image_height;
                std::size_t image_size;
                std::size_t text_size;
                std::size_t font_size;
        };
    }
}

#endif
