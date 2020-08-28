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

#ifndef __YLIKUUTIO_LOAD_FONT_LOADER_HPP_INCLUDED
#define __YLIKUUTIO_LOAD_FONT_LOADER_HPP_INCLUDED

// Include standard headers
#include <cstddef>   // std::size_t
#include <string>    // std::string
#include <vector>    // std::vector

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

namespace yli::load
{
    int32_t extract_value_from_string_with_standard_endings(
            const char* const vertex_base_pointer,
            char*& vertex_data_pointer,
            const std::size_t vertex_data_size,
            const char* const description,
            const bool is_debug_mode);

    bool find_first_glyph_in_svg(const char* SVG_base_pointer, char*& SVG_data_pointer, std::size_t data_size);

    bool load_vertex_data(
            const char* const SVG_base_pointer,
            char*& SVG_data_pointer,
            std::size_t data_size,
            std::vector<std::vector<glm::vec2>>& current_glyph_vertices,
            const bool is_debug_mode);

    bool load_svg_glyph(
            const char* const SVG_base_pointer,
            char*& SVG_data_pointer,
            std::size_t data_size,
            std::vector<std::vector<std::vector<glm::vec2>>>& out_glyph_vertex_data,
            std::vector<std::string>& glyph_names,
            std::vector<std::string>& unicode_strings,
            const bool is_debug_mode);

    bool load_svg_font(
            const std::string& filename,
            std::vector<std::vector<std::vector<glm::vec2>>>& out_glyph_vertex_data,
            std::vector<std::string>& glyph_names,
            std::vector<std::string>& unicode_strings,
            const bool is_debug_mode);
}

#endif
