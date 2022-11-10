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

#ifndef YLIKUUTIO_ONTOLOGY_TEXT_2D_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_TEXT_2D_HPP_INCLUDED

#include "entity.hpp"
#include "child_module.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include standard headers
#include <cstddef>  // std::size_t
#include <optional> // std::optional
#include <string>   // std::string

namespace yli::core
{
    class Application;
}

namespace yli::ontology
{
    class GenericParentModule;
    class Universe;
    class Scene;
    class Font2D;
    struct TextStruct;

    class Text2D final : public yli::ontology::Entity
    {
        public:
            // Set pointer to `text_2d` to `nullptr`, set parent according to the input,
            // and request a new childID from `new_parent`.
            static std::optional<yli::data::AnyValue> bind_to_new_font_2d_parent(
                    yli::ontology::Text2D& text_2d,
                    yli::ontology::Font2D& new_parent) noexcept;

            Text2D(
                    yli::core::Application& application,
                    yli::ontology::Universe& universe,
                    const yli::ontology::TextStruct& text_struct,
                    yli::ontology::GenericParentModule* const parent_module);

            ~Text2D();

            Text2D(const Text2D&) = delete;            // Delete copy constructor.
            Text2D& operator=(const Text2D&) = delete; // Delete copy assignment.

            void render();

            yli::ontology::Entity* get_parent() const override;

            void change_string(const std::string& text);

            yli::ontology::ChildModule child_of_font_2d;

            yli::ontology::Scene* get_scene() const override;

        private:
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            GLuint vao;
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
