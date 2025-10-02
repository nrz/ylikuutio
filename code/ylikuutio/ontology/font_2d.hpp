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

#ifndef YLIKUUTIO_ONTOLOGY_FONT_2D_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_FONT_2D_HPP_INCLUDED

#include "entity.hpp"
#include "child_module.hpp"
#include "generic_parent_module.hpp"
#include "generic_master_module.hpp"
#include "texture_module.hpp"
#include "texture_file_format.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <cstddef>   // std::size_t
#include <stdint.h>  // uint32_t etc.

namespace yli::core
{
    class Application;
}

namespace yli::memory
{
    template<typename T1, std::size_t DataSize>
        class MemoryStorage;
}

namespace yli::ontology
{
    class Universe;
    class Scene;
    class Console;
    struct FontStruct;
    struct PrintTextStruct;

    class Font2d final : public Entity
    {
        private:
            Font2d(
                    yli::core::Application& application,
                    Universe& universe,
                    const FontStruct& font_struct,
                    GenericParentModule* const universe_parent_module);

            ~Font2d();

        public:
            Font2d(const Font2d&) = delete;            // Delete copy constructor.
            Font2d& operator=(const Font2d&) = delete; // Delete copy assignment.

            Entity* get_parent() const override;

            uint32_t get_text_size() const;
            uint32_t get_font_size() const;
            TextureFileFormat get_font_texture_file_format() const;
            uint32_t get_program_id() const;

            void prepare_to_print() const;

            void render();

            void print_text_2d(const PrintTextStruct& text_struct) const;

            GenericParentModule* get_generic_parent_module(const int type);

            template<typename ApprenticeType>
                GenericMasterModule* get_generic_master_module() = delete;

            template<typename T1, std::size_t DataSize>
                friend class yli::memory::MemoryStorage;

            ChildModule child_of_universe;
            GenericParentModule parent_of_text_2ds;
            GenericMasterModule master_of_consoles;
            TextureModule texture;

            Scene* get_scene() const override;

        private:
            uint32_t compute_left_x(const PrintTextStruct& text_struct) const;
            uint32_t compute_top_y(const PrintTextStruct& text_struct) const;
            void compute_and_store_glyph_vertices(std::vector<glm::vec2>& vertices, const uint32_t vertex_left_x, const uint32_t vertex_top_y) const;
            void draw(std::vector<glm::vec2>& vertices, std::vector<glm::vec2>& uvs) const;

            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            GLuint vao                               { 0 };
            GLuint vertexbuffer                      { 0 }; // Buffer containing the vertices.
            GLuint uvbuffer                          { 0 }; // Buffer containing the UVs.
            GLuint program_id                        { 0 }; // The `program_id` of the shader used to display the text, returned by `load_shaders`.
            GLint vertex_position_in_screenspace_id  { 0 }; // Location of the program's `vertex_position_screenspace` attribute.
            GLint vertex_uv_id                       { 0 }; // Location of the program's `vertex_uv` attribute.
            GLint text_2d_uniform_id                 { 0 }; // Location of the program's texture attribute.
            GLint screen_width_uniform_id            { 0 }; // Location of the program's window width uniform.
            GLint screen_height_uniform_id           { 0 }; // Location of the program's window height uniform.

            uint32_t screen_width;
            uint32_t screen_height;
            uint32_t text_size;
            uint32_t font_size;
    };

    template<>
        inline GenericMasterModule* Font2d::get_generic_master_module<Console>()
        {
            return &this->master_of_consoles;
        }
}

#endif
