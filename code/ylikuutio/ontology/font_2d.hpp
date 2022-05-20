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
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <cstddef>   // std::size_t
#include <stdint.h>  // uint32_t etc.
#include <string>    // std::string

namespace yli::ontology
{
    class Universe;
    class Scene;
    struct FontStruct;
    struct TextStruct;

    class Font2D: public yli::ontology::Entity
    {
        public:
            Font2D(
                    yli::ontology::Universe& universe,
                    const yli::ontology::FontStruct& font_struct,
                    yli::ontology::GenericParentModule* const parent_module);

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

            GLuint vao                               { 0 };
            GLuint vertexbuffer                      { 0 }; // Buffer containing the vertices.
            GLuint uvbuffer                          { 0 }; // Buffer containing the UVs.
            GLuint program_id                        { 0 }; // The `program_id` of the shader used to display the text, returned by `load_shaders`.
            GLint vertex_position_in_screenspace_id  { 0 }; // Location of the program's `vertex_position_screenspace` attribute.
            GLint vertex_uv_id                       { 0 }; // Location of the program's `vertexUV` attribute.
            GLint text_2d_uniform_id                 { 0 }; // Location of the program's texture attribute.
            GLint screen_width_uniform_id            { 0 }; // Location of the program's window width uniform.
            GLint screen_height_uniform_id           { 0 }; // Location of the program's window height uniform.

            uint32_t screen_width;
            uint32_t screen_height;
            uint32_t text_size;
            uint32_t font_size;
    };
}

#endif
