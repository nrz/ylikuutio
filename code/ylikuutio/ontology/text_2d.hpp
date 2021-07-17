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

#ifndef __YLIKUUTIO_ONTOLOGY_TEXT_2D_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_TEXT_2D_HPP_INCLUDED

#include "entity.hpp"
#include "child_module.hpp"
#include "universe.hpp"
#include "font_2d.hpp"
#include "text_struct.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <cstddef>  // std::size_t
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string

namespace yli::ontology
{
    class ParentModule;

    class Text2D: public yli::ontology::Entity
    {
        public:
            // This method sets pointer to this `Text2D` to `nullptr`, sets `parent` according to the input, and requests a new `childID` from the new `Font2D`.
            void bind_to_new_font_2d_parent(yli::ontology::Font2D* const new_parent);
            void bind_to_new_parent(yli::ontology::Entity* const new_parent) override;

            Text2D(
                    yli::ontology::Universe* const universe,
                    const yli::ontology::TextStruct& text_struct,
                    yli::ontology::ParentModule* const parent_module)
                : Entity(universe, text_struct),
                child_of_font_2d(parent_module, this)
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
                this->vertexbuffer                      = 0;
                this->uvbuffer                          = 0;
                this->vertex_position_in_screenspace_id = 0;
                this->vertex_uv_id                      = 0;

                const bool is_headless = (this->universe == nullptr ? true : this->universe->get_is_headless());

                if (!is_headless)
                {
                    // Initialize VBO.
                    glGenBuffers(1, &this->vertexbuffer);
                    glGenBuffers(1, &this->uvbuffer);

                    // Get a handle for our buffers.
                    yli::ontology::Font2D* const font_2d = static_cast<yli::ontology::Font2D*>(this->child_of_font_2d.get_parent());

                    if (font_2d != nullptr)
                    {
                        this->vertex_position_in_screenspace_id = glGetAttribLocation(font_2d->get_program_id(), "vertex_position_screenspace");
                        this->vertex_uv_id = glGetAttribLocation(font_2d->get_program_id(), "vertexUV");
                    }
                }

                // `yli::ontology::Entity` member variables begin here.
                this->type_string = "yli::ontology::Text2D*";
            }

            Text2D(const Text2D&) = delete;            // Delete copy constructor.
            Text2D& operator=(const Text2D&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~Text2D();

            void render();

            yli::ontology::Entity* get_parent() const override;

            void change_string(const std::string& text);

            yli::ontology::ChildModule child_of_font_2d;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            GLuint vertexbuffer;                     // Buffer containing the vertices
            GLuint uvbuffer;                         // Buffer containing the UVs
            GLint vertex_position_in_screenspace_id; // Location of the program's `vertex_position_screenspace` attribute.
            GLint vertex_uv_id;                      // Location of the program's `vertexUV` attribute.

            std::string text;
            std::string horizontal_alignment;
            std::string vertical_alignment;
            std::size_t screen_width;
            std::size_t screen_height;
            std::size_t x;
            std::size_t y;
            std::size_t text_size;
            std::size_t font_size;
    };
}

#endif
